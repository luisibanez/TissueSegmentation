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
#ifndef __itkMahalanobisDistanceImageFilter_txx
#define __itkMahalanobisDistanceImageFilter_txx

#include "itkMahalanobisDistanceImageFilter.h"

namespace itk
{

template< class TInputImage, class TOutputImage >
MahalanobisDistanceImageFilter< TInputImage, TOutputImage >
::MahalanobisDistanceImageFilter()
{
}

template< class TInputImage, class TOutputImage >
void
MahalanobisDistanceImageFilter< TInputImage, TOutputImage >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Mean: " << m_Mean << std::endl;
  os << indent << "Covariance: " << m_Covariance << std::endl;
}

template< class TInputImage, class TOutputImage >
void
MahalanobisDistanceImageFilter< TInputImage, TOutputImage >
::BeforeThreadedGenerateData()
{
  // Setup up the functor
  this->GetFunctor().SetMean( this->m_Mean );
  this->GetFunctor().SetCovariance( this->m_Covariance );
}
} // end namespace itk

#endif
