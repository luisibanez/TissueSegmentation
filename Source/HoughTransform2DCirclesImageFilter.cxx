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

#include "itkHoughTransform2DCirclesImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkImageFileReader.h"
#include "itkCastImageFilter.h"
#include "itkImageFileWriter.h"

int main(int argc, char* argv[])
{

  if ( argc < 3 ) 
    {
    std::cerr << "Invalid argument: " << argv[0] << "\t Input_Image Output_Image " << std::endl;
    return EXIT_FAILURE;
    }
  /** Typedefs */
  typedef   unsigned char                            PixelType;
  typedef   double                                   HoughSpacePixelType;
  typedef   itk::Image< HoughSpacePixelType, 2>      HoughImageType;
  typedef   itk::Image< PixelType, 2>                ImageType;

  const double nPI = 4.0 * vcl_atan( 1.0 );

  typedef  itk::ImageFileReader<  ImageType   > ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  /** Allocate Hough Space image (accumulator) */
  std::cout << "Allocating Hough Space Image" << std::endl;
  ImageType::Pointer m_HoughSpaceImage = ImageType::New();
  m_HoughSpaceImage->SetRegions( reader->GetOutput()->GetLargestPossibleRegion() );
  m_HoughSpaceImage->Allocate();
  m_HoughSpaceImage->FillBuffer(0);


 /** Apply gradient filter to the input image */
  typedef itk::CastImageFilter<
                        ImageType,
                        HoughImageType    >    CastingFilterType;

  CastingFilterType::Pointer caster = CastingFilterType::New();
  caster->SetInput( reader->GetOutput() );
  caster->Update();


  /** Define the HoughTransform filter */
  typedef itk::HoughTransform2DCirclesImageFilter<HoughSpacePixelType,HoughSpacePixelType> HoughTransformFilterType;

  HoughTransformFilterType::Pointer houghFilter = HoughTransformFilterType::New();

  houghFilter->SetInput(caster->GetOutput());
  houghFilter->SetMinimumRadius(0);
  houghFilter->SetMaximumRadius(20);
  houghFilter->SetSigmaGradient(1);
  houghFilter->Update();
  HoughImageType::Pointer m_Accumulator= houghFilter->GetOutput();
  HoughImageType::Pointer m_RadiusImage= houghFilter->GetRadiusImage();

  /** Blur the accumulator in order to find the maximum */
  HoughImageType::Pointer m_PostProcessImage = HoughImageType::New();
  typedef itk::DiscreteGaussianImageFilter<HoughImageType,HoughImageType> GaussianFilterType;
  GaussianFilterType::Pointer gaussianFilter = GaussianFilterType::New();
  gaussianFilter->SetInput(m_Accumulator);
  double variance[2];
  variance[0]=10;
  variance[1]=10;
  gaussianFilter->SetVariance(variance);
  gaussianFilter->SetMaximumError(.01f);
  gaussianFilter->Update();
  m_PostProcessImage = gaussianFilter->GetOutput();

  typedef itk::MinimumMaximumImageCalculator<HoughImageType> MinMaxCalculatorType;
  MinMaxCalculatorType::Pointer minMaxCalculator = MinMaxCalculatorType::New();

  itk::ImageRegionIterator<ImageType> it_output(m_HoughSpaceImage,m_HoughSpaceImage->GetLargestPossibleRegion());
  itk::ImageRegionIterator<HoughImageType> it_input(m_PostProcessImage,m_PostProcessImage->GetLargestPossibleRegion());

 /** Set the number of circles we are looking for. */
  unsigned int numberOfCircles = 3;

  /** Set the disc ratio */
  double discRatio = 1.1;

  /** Search for maxima */
  std::cout << "Search for maxima ..." << std::endl;
  unsigned int center_result[3][2];
  double radius_result[3];
  unsigned int circles=0;
  do{
  minMaxCalculator->SetImage(m_PostProcessImage);
  minMaxCalculator->ComputeMaximum();
  HoughImageType::PixelType   max = minMaxCalculator->GetMaximum();

  it_output.GoToBegin();

  ImageType::IndexType index;
  index.Fill(0);

  for(it_input.GoToBegin();!it_input.IsAtEnd();++it_input)
  {
    if(it_input.Get() == max)
    {
      it_output.Set(255);
      double radius2 = m_RadiusImage->GetPixel(it_output.GetIndex());
      center_result[circles][0]=it_output.GetIndex()[0];
      center_result[circles][1]=it_output.GetIndex()[1];
      radius_result[circles]=radius2;

      /** Draw the circle */
      for(double angle = 0; angle <= 2 * nPI; angle += nPI / 1000)
      {
        index[0] = (long int)(it_output.GetIndex()[0] + radius2 * vcl_cos(angle));
        index[1] = (long int)(it_output.GetIndex()[1] + radius2 * vcl_sin(angle));
        m_HoughSpaceImage->SetPixel(index,255);

        /** Remove the maximum from the accumulator */
        for(double length = 0; length < discRatio*radius2;length+=1)
        {
          index[0] = (long int)(it_output.GetIndex()[0] + length * vcl_cos(angle));
          index[1] = (long int)(it_output.GetIndex()[1] + length * vcl_sin(angle));
          m_PostProcessImage->SetPixel(index,0);
        }
      }

      minMaxCalculator->SetImage(m_PostProcessImage);
      minMaxCalculator->ComputeMaximum();
      max = minMaxCalculator->GetMaximum();

 
      circles++;
      if(circles == numberOfCircles) break;
    }
    ++it_output;
    }
  }
  while(circles<numberOfCircles);

  std::cout << "Done." << std::endl;

  for(unsigned int i=0;i<3;i++)
    {
    std::cout << "Circle #" << i << " [" << center_result[i][0] << ","
                << center_result[i][1] << "] -> radius = " <<  radius_result[i] << std::endl;
    }

  typedef itk::ImageFileWriter<  ImageType >  WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput (  m_HoughSpaceImage );
  writer->SetFileName( argv[2] );
  writer->Update();

  return EXIT_SUCCESS;
}
