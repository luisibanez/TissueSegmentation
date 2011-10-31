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

// Software Guide : BeginLatex
//
// This example illustrates the use of the
// \doxygen{SignedMaurerDistanceMapImageFilter}.  This filter generates a
// distance map by running Maurer distance map twice, once on the input
// image and once on the flipped image.
//
// \index{itk::Signed\-Maurer\-Distance\-Map\-Image\-Filter!Instantiation}
// \index{itk::Signed\-Maurer\-Distance\-Map\-Image\-Filter!Header}
//
// The first step required to use this filter is to include its header file.
//
// Software Guide : EndLatex

// Software Guide : BeginCodeSnippet
#include "itkSignedMaurerDistanceMapImageFilter.h"
// Software Guide : EndCodeSnippet

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"


int main( int argc, char * argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImageFile outputDistanceMapImageFile ";
    std::cerr << " [outputVoronoiMapImageFilter] ";
    std::cerr << " [outputVectorMapImageFilter] ";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  // Software Guide : BeginLatex
  //
  //  Then we must decide what pixel types to use for the input and output
  //  images. Since the output will contain distances measured in pixels, the
  //  pixel type should be able to represent at least the width of the image,
  //  or said in $N-D$ terms, the maximum extension along all the dimensions.
  //  The input and output image types are now defined using their respective
  //  pixel type and dimension.
  //
  // Software Guide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef  unsigned char   InputPixelType;
  typedef  float           OutputPixelType;
  typedef  unsigned short  VoronoiPixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image< InputPixelType,  Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >   OutputImageType;
  typedef itk::Image< VoronoiPixelType, Dimension >  VoronoiImageType;
  // Software Guide : EndCodeSnippet


  // Software Guide : BeginLatex
  //
  // The only change with respect to the previous example is to replace the
  // MaurerDistanceMapImageFilter with the
  // SignedMaurerDistanceMapImageFilter
  //
  // SoftwareGuide : EndLatex

  // Software Guide : BeginCodeSnippet
  typedef itk::SignedMaurerDistanceMapImageFilter<
                                         InputImageType,
                                         OutputImageType >  FilterType;

  FilterType::Pointer filter = FilterType::New();
  // Software Guide : EndCodeSnippet


  typedef itk::RescaleIntensityImageFilter<
                   OutputImageType, InputImageType > RescalerType;

  RescalerType::Pointer scaler = RescalerType::New();

  // Software Guide : BeginLatex
  //
  // The inside is considered as having negative distances. Outside is
  // treated as having positive distances. To change the convention,
  // use the InsideIsPositive(bool) function.
  //
  // Software Guide : EndLatex

  // Reader and Writer types are instantiated.
  //
  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< InputImageType >  WriterType;
  typedef itk::ImageFileWriter< VoronoiImageType > VoronoiWriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  //  The input to the filter is taken from a reader and its output is passed
  //  to a \doxygen{RescaleIntensityImageFilter} and then to a writer.

  filter->SetInput( reader->GetOutput() );
  scaler->SetInput( filter->GetOutput() );
  writer->SetInput( scaler->GetOutput() );

  scaler->SetOutputMaximum( 255 );
  scaler->SetOutputMinimum( 0 );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject exp )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr <<     exp    << std::endl;
    }

  return EXIT_SUCCESS;
}
