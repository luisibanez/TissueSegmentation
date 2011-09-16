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
#include "itkImageRegionIteratorWithIndex.h"
#include "itkGaussianMembershipFunction.h"

int main(int argc, char * argv[] )
{

  if( argc < 3 )
  {
    std::cerr << argv[0] << "membershipFunctionInputFile histogramRGBOutputFile " << std::endl;
    return EXIT_FAILURE;
  }

  const unsigned int NumberOfComponents = 3;

  typedef double                                OutputPixelType;
  typedef unsigned char                         PixelComponentType;
  typedef itk::RGBPixel<PixelComponentType>     InputPixelType;

  typedef itk::Image< OutputPixelType, NumberOfComponents >   OutputImageType;

  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  typedef OutputImageType::RegionType    RegionType;
  typedef OutputImageType::SizeType      SizeType;
  typedef OutputImageType::IndexType     IndexType;

  RegionType region;
  SizeType   size;
  IndexType  start;

  start.Fill( 0 );

  size[0] = 256;
  size[1] = 256;
  size[2] = 256;

  region.SetSize( size );
  region.SetIndex( start );

  OutputImageType::Pointer histogramImage = OutputImageType::New();

  histogramImage->SetRegions( region );
  histogramImage->Allocate();
  histogramImage->FillBuffer( 0 );

  typedef itk::Statistics::GaussianMembershipFunction< InputPixelType >  MembershipFunctionType;

  MembershipFunctionType::Pointer membershipFunction = MembershipFunctionType::New();

  typedef MembershipFunctionType::MeanVectorType         MeanVectorType;
  typedef MembershipFunctionType::CovarianceMatrixType   CovarianceMatrixType;

  MeanVectorType mean(NumberOfComponents);

  CovarianceMatrixType covariance(NumberOfComponents,NumberOfComponents);

  std::ifstream inputMembership;

  inputMembership.open( argv[1] );

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

  membershipFunction->SetMean( mean );
  membershipFunction->SetCovariance( covariance );


  typedef itk::ImageRegionIteratorWithIndex< OutputImageType > OutputIteratorType;

  OutputIteratorType otr( histogramImage, histogramImage->GetBufferedRegion() );
  otr.GoToBegin();


  InputPixelType rgbPixel;

  while( !otr.IsAtEnd() )
    {
    const IndexType & index = otr.GetIndex();

    rgbPixel[0] = index[0];
    rgbPixel[1] = index[1];
    rgbPixel[2] = index[2];

    otr.Set( membershipFunction->Evaluate( rgbPixel ) );

    ++otr;
    }

  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[2] );
  writer->SetInput( histogramImage );

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
