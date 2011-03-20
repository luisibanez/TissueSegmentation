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
#ifndef __itkMembershipImageFilter_h
#define __itkMembershipImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkMembershipFunctionBase.h"

namespace itk
{
/** \class MembershipImageFilter
 *
 * \brief Compute the the membership function on the pixels of an input image.
 *
 */
namespace Functor
{
template< class TInput, class TOutput >
class Membership
{
public:
  typedef Statistics::MembershipFunctionBase< TInput >   MembershipFunctionType;
  typedef typename NumericTraits< TOutput >::RealType    MagnitudeType;

  Membership()
  {
    m_MembershipFunction = NULL;
    m_Magnitude = static_cast< MagnitudeType >( NumericTraits< TOutput >::max() );
  }

  ~Membership() {}

  void SetMembershipFunction(const MembershipFunctionType * function)
  {
    m_MembershipFunction = function;
  }

  void SetMagnitude(const MagnitudeType & magnitude)
  {
    m_Magnitude = magnitude;
  }

  bool operator!=(const Membership & other) const
  {
    if ( m_MembershipFunction != other.m_MembershipFunction ||
         m_Magnitude != other.m_Magnitude )
      {
      return true;
      }
    return false;
  }

  bool operator==(const Membership & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput & A) const
  {
    return static_cast< TOutput >( m_Magnitude * m_MembershipFunction->Evaluate( A ) );
  }

private:
  typename MembershipFunctionType::ConstPointer  m_MembershipFunction;
  MagnitudeType                                  m_Magnitude;
};
}

template< class TInputImage, class TOutputImage >
class ITK_EXPORT MembershipImageFilter:
  public
  UnaryFunctorImageFilter< TInputImage, TOutputImage,
                           Functor::Membership<
                             typename TInputImage::PixelType,
                             typename TOutputImage::PixelType > >
{
public:
  /** Standard class typedefs. */
  typedef MembershipImageFilter Self;
  typedef UnaryFunctorImageFilter< TInputImage, TOutputImage,
                                   Functor::Membership<
                                     typename TInputImage::PixelType,
                                     typename TOutputImage::PixelType >
                                   >                                   Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MembershipImageFilter, UnaryFunctorImageFilter);

  typedef Functor::Membership<
    typename TInputImage::PixelType,
    typename TOutputImage::PixelType >    FunctorType;

  typedef typename FunctorType::MembershipFunctionType  MembershipFunctionType;
  typedef typename FunctorType::MagnitudeType           MagnitudeType;

  itkSetObjectMacro( MembershipFunction, MembershipFunctionType );
  itkGetObjectMacro( MembershipFunction, MembershipFunctionType );

  itkSetMacro( Magnitude, MagnitudeType );
  itkGetMacro( Magnitude, MagnitudeType );

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  /** End concept checking */
#endif

protected:
  MembershipImageFilter();
  virtual ~MembershipImageFilter() {}
  void PrintSelf(std::ostream & os, Indent indent) const;

  /** This method is used to set the state of the filter before
   * multi-threading. */
  virtual void BeforeThreadedGenerateData();

private:
  MembershipImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);        //purposely not implemented

  typename MembershipFunctionType::Pointer  m_MembershipFunction;
  MagnitudeType                             m_Magnitude;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMembershipImageFilter.txx"
#endif

#endif
