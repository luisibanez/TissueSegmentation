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
// The following example illustrates how to preprocess and segment images using
// the \doxygen{WatershedImageFilter} for the particular case of grayscale
// scalar image.
//
// Software Guide : EndLatex

#include "itkWatershedImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"


int main( int argc, char *argv[] )
{


  if( argc < 4 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  GradientOutputImage WatershedOutput [lowerThreshold]  [outputScaleLevel]" << std::endl;
    return 1;
    }

  typedef float                             InternalPixelType;
  typedef itk::RGBPixel<unsigned char>      RGBPixelType;

  const   unsigned int                      Dimension = 2;


  typedef itk::Image< InternalPixelType,  Dimension >  InternalImageType;
  typedef itk::Image< RGBPixelType,       Dimension >  RGBImageType;


  //
  // We instantiate reader and writer types
  //
  typedef  itk::ImageFileReader< InternalImageType   >  ReaderType;

  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( argv[1] );


  //
  //  Instantiate the GradientMagnitude image filter
  //
  typedef   itk::GradientMagnitudeRecursiveGaussianImageFilter<
                                                     InternalImageType,
                                                     InternalImageType
                                                          > GradientMagnitudeFilterType;

  GradientMagnitudeFilterType::Pointer gradienMagnitudeFilter = GradientMagnitudeFilterType::New();

  gradienMagnitudeFilter->SetInput( reader->GetOutput() );
  gradienMagnitudeFilter->SetSigma( 1.0 );

  typedef  itk::ImageFileWriter< InternalImageType  >        EdgeOutputImageWriterType;
  EdgeOutputImageWriterType::Pointer edgeWriter = EdgeOutputImageWriterType::New();
  edgeWriter->SetFileName( argv[2] );
  edgeWriter->SetInput( gradienMagnitudeFilter->GetOutput() );
  edgeWriter->Update();

  //
  //  Instantiate the Watershed filter
  //

  typedef  itk::WatershedImageFilter<
                              InternalImageType
                                            > WatershedFilterType;

  WatershedFilterType::Pointer watershedFilter = WatershedFilterType::New();

  watershedFilter->SetInput( gradienMagnitudeFilter->GetOutput() );

  if ( argc > 4 )
    {
    watershedFilter->SetThreshold( atof( argv[4] ) );
    }

  if ( argc > 5 ) 
    {
    watershedFilter->SetLevel(     atof( argv[5] ) );
    }

  watershedFilter->Update();


  //
  //  Instantiate the filter that will encode the label image
  //  into a color image (random color attribution).
  //

  typedef itk::Functor::ScalarToRGBPixelFunctor<
                                           unsigned long
                                                    > ColorMapFunctorType;

  typedef WatershedFilterType::OutputImageType  LabeledImageType;

  typedef itk::UnaryFunctorImageFilter<
                                LabeledImageType,
                                RGBImageType,
                                ColorMapFunctorType
                                                > ColorMapFilterType;

  ColorMapFilterType::Pointer colorMapFilter = ColorMapFilterType::New();

  colorMapFilter->SetInput(  watershedFilter->GetOutput() );

  typedef  itk::ImageFileWriter< RGBImageType  >        WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[3] );

  writer->SetInput( colorMapFilter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }


  return 0;

}
