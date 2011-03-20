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

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRGBPixel.h"
#include "itkMahalanobisDistanceImageFilter.h"

int main(int argc, char * argv[] )
{

  if( argc < 4 )
  {
    std::cerr << argv[0] << " inputImage outputImage inputMembershipFunction" << std::endl;
    return EXIT_FAILURE;
  }

  const unsigned int ImageDimension = 2;
  const unsigned int NumberOfComponents = 3;

  typedef unsigned char                        PixelComponentType;
  typedef itk::RGBPixel<PixelComponentType>    InputPixelType;

  typedef unsigned char                        OutputPixelType;

  typedef itk::Image< InputPixelType,  ImageDimension >   InputImageType;
  typedef itk::Image< OutputPixelType, ImageDimension >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType  > ReaderType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  typedef itk::MahalanobisDistanceImageFilter< InputImageType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();

  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( argv[1] );


  typedef FilterType::MeanVectorType         MeanVectorType;
  typedef FilterType::CovarianceMatrixType   CovarianceMatrixType;

  MeanVectorType mean(NumberOfComponents);

  CovarianceMatrixType covariance(NumberOfComponents,NumberOfComponents);

  std::ifstream inputMembership;

  inputMembership.open( argv[3] );

  for( unsigned int i = 0; i < NumberOfComponents; i++ )
    {
    inputMembership >> mean[i];
    }

  for( unsigned int i = 0; i < NumberOfComponents; i++ )
    {
    for( unsigned int j = 0; j < NumberOfComponents; j++ )
      {
      inputMembership >> covariance(i,j);
      }
    }

  inputMembership.close();

  std::cout << "Mean vector = " << std::endl;
  std::cout << mean << std::endl;

  std::cout << "Covariance matrix = " << std::endl;
  std::cout << covariance << std::endl;


  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[2] );

  filter->SetInput( reader->GetOutput() );
  writer->SetInput( filter->GetOutput() );


  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
