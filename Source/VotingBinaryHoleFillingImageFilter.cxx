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
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVotingBinaryHoleFillingImageFilter.h"

int main(int argc, char * argv[])
{
  if( argc < 7 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " InputImage OutputImage Background Foreground Radius Majority" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char       InputPixelType;
  typedef unsigned char       OutputPixelType;

  typedef itk::Image< InputPixelType, Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

  typedef itk::ImageFileReader< InputImageType > ReaderType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  typedef itk::VotingBinaryHoleFillingImageFilter<
    	  InputImageType, OutputImageType > VotingFilterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  VotingFilterType::Pointer filter = VotingFilterType::New();

  reader->SetFileName( argv[1] );
  writer->SetInput( filter->GetOutput() );

  InputImageType::SizeType neighborhoodRadius;
  neighborhoodRadius[0] = atoi( argv[5] );
  neighborhoodRadius[1] = atoi( argv[5] );
  neighborhoodRadius[2] = atoi( argv[5] );

  filter->SetInput( reader->GetOutput() );
  filter->SetBackgroundValue( atoi( argv[3] ) );
  filter->SetForegroundValue( atoi( argv[4] ) );
  filter->SetRadius( neighborhoodRadius );
  filter->SetMajorityThreshold( atoi( argv[6] ) );


  writer->SetFileName( argv[2] );

  try
    {
    writer->Update();
    }
  catch ( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
