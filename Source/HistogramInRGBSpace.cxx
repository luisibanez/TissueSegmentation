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
#include "itkImageRegionConstIterator.h"

int main(int argc, char * argv[] )
{

  if( argc < 3 )
  {
    std::cerr << argv[0] << " inputFile histogramRGBFile" << std::endl;
    return EXIT_FAILURE;
  }

  typedef unsigned char                        PixelComponentType;
  typedef itk::RGBPixel<PixelComponentType>    InputPixelType;
  typedef itk::IdentifierType                  OutputPixelType;

  typedef itk::Image< InputPixelType,  3 >   InputImageType;
  typedef itk::Image< OutputPixelType, 3 >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType  > ReaderType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  typedef OutputImageType::RegionType    RegionType;
  typedef OutputImageType::SizeType      SizeType;
  typedef OutputImageType::IndexType     IndexType;

  InputImageType::Pointer inputImage;

  { // local scope for destroying the reader

    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( argv[1] );
    try
      {
      reader->Update();
      }
    catch( itk::ExceptionObject & excp )
      {
      std::cout << excp << std::endl;
      return -1;
      }
    inputImage = reader->GetOutput();
  }

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


  typedef itk::ImageRegionConstIterator< InputImageType > IteratorType;

  IteratorType it( inputImage, inputImage->GetBufferedRegion() );
  it.GoToBegin();

  IndexType index;

  while( !it.IsAtEnd() )
    {
    InputPixelType pixel = it.Get();
    PixelComponentType red   = pixel.GetRed();
    PixelComponentType green = pixel.GetGreen();
    PixelComponentType blue  = pixel.GetBlue();
    index[0] = red;
    index[1] = green;
    index[2] = blue;

    OutputPixelType count = histogramImage->GetPixel( index );
    count++;
    histogramImage->SetPixel( index, count );
    ++it;
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
