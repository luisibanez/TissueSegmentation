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
    std::cerr << argv[0] << " inputFile histogramRGBFile [imageMask] [negatedMask=1/0]" << std::endl;
    return EXIT_FAILURE;
  }

  const unsigned int ImageDimension = 2;
  const unsigned int NumberOfComponents = 3;

  typedef unsigned char                        PixelComponentType;
  typedef itk::RGBPixel<PixelComponentType>    InputPixelType;

  // Ideally this type should be itk::IdentifierType
  // but currently ParaView can't read an image of this type in Linux 64 bits.
  typedef unsigned int    OutputPixelType;

  typedef unsigned char   MaskPixelType;

  typedef itk::Image< InputPixelType,  ImageDimension >   InputImageType;
  typedef itk::Image< MaskPixelType, ImageDimension >     MaskImageType;

  typedef itk::Image< OutputPixelType, NumberOfComponents >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType  > InputReaderType;
  typedef itk::ImageFileReader< MaskImageType   > MaskReaderType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  typedef OutputImageType::RegionType    RegionType;
  typedef OutputImageType::SizeType      SizeType;
  typedef OutputImageType::IndexType     IndexType;

  InputReaderType::Pointer inputReader = InputReaderType::New();

  inputReader->SetFileName( argv[1] );

  try
    {
    inputReader->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  InputImageType::ConstPointer inputImage = inputReader->GetOutput();

  MaskReaderType::Pointer maskReader = MaskReaderType::New();

  bool usingMask = false;
  bool negatedMask = false;

  if( argc > 3 )
    {
    usingMask = true;

    if( argc > 4 )
      {
      negatedMask = atoi( argv[4] );
      }
    }

  if( usingMask )
    {
    maskReader->SetFileName( argv[2] );

    try
      {
      maskReader->Update();
      }
    catch( itk::ExceptionObject & excp )
      {
      std::cerr << excp << std::endl;
      return EXIT_FAILURE;
      }
    }

  MaskImageType::ConstPointer maskImage = maskReader->GetOutput();


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


  typedef itk::ImageRegionConstIterator< InputImageType > InputIteratorType;

  InputIteratorType it( inputImage, inputImage->GetBufferedRegion() );
  it.GoToBegin();


  IndexType index;

  if( usingMask )
    {
    typedef itk::ImageRegionConstIterator< MaskImageType > MaskIteratorType;

    MaskIteratorType mit( maskImage, maskImage->GetBufferedRegion() );
    mit.GoToBegin();


    while( !it.IsAtEnd() )
      {
      MaskPixelType maskPixel = mit.Get();

      if( negatedMask )
        {
        if( maskPixel )
          {
          InputPixelType inputPixel = it.Get();
          const PixelComponentType & red   = inputPixel.GetRed();
          const PixelComponentType & green = inputPixel.GetGreen();
          const PixelComponentType & blue  = inputPixel.GetBlue();
          index[0] = red;
          index[1] = green;
          index[2] = blue;

          OutputPixelType count = histogramImage->GetPixel( index );
          count++;
          histogramImage->SetPixel( index, count );
          }
        }
      else
        {
        if( !maskPixel )
          {
          InputPixelType inputPixel = it.Get();
          const PixelComponentType & red   = inputPixel.GetRed();
          const PixelComponentType & green = inputPixel.GetGreen();
          const PixelComponentType & blue  = inputPixel.GetBlue();
          index[0] = red;
          index[1] = green;
          index[2] = blue;

          OutputPixelType count = histogramImage->GetPixel( index );
          count++;
          histogramImage->SetPixel( index, count );
          }
        }

      ++it;
      ++mit;
      }
    }
  else
    {
    while( !it.IsAtEnd() )
      {
      InputPixelType inputPixel = it.Get();
      const PixelComponentType & red   = inputPixel.GetRed();
      const PixelComponentType & green = inputPixel.GetGreen();
      const PixelComponentType & blue  = inputPixel.GetBlue();
      index[0] = red;
      index[1] = green;
      index[2] = blue;

      OutputPixelType count = histogramImage->GetPixel( index );
      count++;
      histogramImage->SetPixel( index, count );
      ++it;
      }
    }

  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[3] );
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
