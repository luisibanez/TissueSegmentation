/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkMahalanobisDistanceImageFilter_h
#define __itkMahalanobisDistanceImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkMahalanobisDistanceMetric.h"

namespace itk
{
/** \class MahalanobisDistanceImageFilter
 *
 * \brief Compute the Mahalanobis distance at every pixel of an input image.
 *
 */
namespace Functor
{
template< class TInput, class TOutput >
class MahalanobisDistance
{
public:
  typedef Statistics::MahalanobisDistanceMetric< TInput >   DistanceMetricType;
  typedef typename DistanceMetricType::MeanVectorType       MeanVectorType;
  typedef typename DistanceMetricType::CovarianceMatrixType CovarianceMatrixType;

  MahalanobisDistance()
  {
    m_DistanceMetric = DistanceMetricType::New();
  }

  ~MahalanobisDistance() {}

  void SetMean(const MeanVectorType & mean)
  {
    m_Mean = mean;
    m_DistanceMetric->SetMean( mean );
  }

  void SetCovariance(const CovarianceMatrixType & covariance)
  {
    m_Covariance = covariance;
    m_DistanceMetric->SetCovariance( covariance );
  }

  bool operator!=(const MahalanobisDistance & other) const
  {
    if ( m_Mean != other.m_Mean ||
         m_Covariance != other.m_Covariance )
      {
      return true;
      }
    return false;
  }

  bool operator==(const MahalanobisDistance & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput & A) const
  {
    return m_DistanceMetric->Evaluate( A );
  }

private:
  typename DistanceMetricType::Pointer    m_DistanceMetric;
  CovarianceMatrixType                    m_Covariance;
  MeanVectorType                          m_Mean;
};
}

template< class TInputImage, class TOutputImage >
class ITK_EXPORT MahalanobisDistanceImageFilter:
  public
  UnaryFunctorImageFilter< TInputImage, TOutputImage,
                           Functor::MahalanobisDistance<
                             typename TInputImage::PixelType,
                             typename TOutputImage::PixelType > >
{
public:
  /** Standard class typedefs. */
  typedef MahalanobisDistanceImageFilter Self;
  typedef UnaryFunctorImageFilter< TInputImage, TOutputImage,
                                   Functor::MahalanobisDistance<
                                     typename TInputImage::PixelType,
                                     typename TOutputImage::PixelType >
                                   >                                   Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MahalanobisDistanceImageFilter, UnaryFunctorImageFilter);

  typedef Functor::MahalanobisDistance<
    typename TInputImage::PixelType,
    typename TOutputImage::PixelType >                        DistanceMetricType;

  typedef typename DistanceMetricType::MeanVectorType         MeanVectorType;
  typedef typename DistanceMetricType::CovarianceMatrixType   CovarianceMatrixType;

  itkSetMacro( Mean, MeanVectorType );
  itkSetMacro( Covariance, CovarianceMatrixType );

  itkGetMacro( Mean, MeanVectorType );
  itkGetMacro( Covariance, CovarianceMatrixType );


#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  /** End concept checking */
#endif

protected:
  MahalanobisDistanceImageFilter();
  virtual ~MahalanobisDistanceImageFilter() {}
  void PrintSelf(std::ostream & os, Indent indent) const;

  /** This method is used to set the state of the filter before
   * multi-threading. */
  virtual void BeforeThreadedGenerateData();

private:
  MahalanobisDistanceImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);             //purposely not implemented

  CovarianceMatrixType    m_Covariance;
  MeanVectorType          m_Mean;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMahalanobisDistanceImageFilter.txx"
#endif

#endif
