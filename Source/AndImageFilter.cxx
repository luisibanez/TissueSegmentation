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
#include "itkAndImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"


int main(int argc, char* argv[] )
{
 if( argc < 4 )
  {
    std::cerr << "Missing Arguments" << std::endl;
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImage inputImage2 outputImage " << std::endl;
    return EXIT_FAILURE;
  }

  // Declare the types of the images
  typedef unsigned char myPixelType;
  const int myDimension = 2;

  typedef itk::Image<myPixelType, myDimension>  myImageType1;
  typedef itk::Image<myPixelType, myDimension>  myImageType2;
  typedef itk::Image<myPixelType, myDimension>  myImageType3;

  // Declare the type for the ADD filter
  typedef itk::AndImageFilter<
                                myImageType1,
                                myImageType2,
                                myImageType3  >       myFilterType;


  // Create an ADD Filter
  myFilterType::Pointer filter = myFilterType::New();

  typedef itk::ImageFileReader< myImageType1 > ReaderType;
  ReaderType::Pointer reader1 = ReaderType::New();
  reader1->SetFileName( argv[1] );

  typedef itk::ImageFileReader< myImageType2 > ReaderType2;
  ReaderType2::Pointer reader2 = ReaderType2::New();
  reader2->SetFileName( argv[2] );

  // Connect the input images
  filter->SetInput1( reader1->GetOutput() );
  filter->SetInput2( reader2->GetOutput() );

  // Execute the filter
  filter->Update();

  typedef itk::ImageFileWriter< myImageType3 > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[3] );

  try
    {
  writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception caught ! " << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;

}




