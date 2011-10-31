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
#include "itkImageRegionIterator.h"
#include "itkLabelImageToShapeLabelMapFilter.h"
#include "itkShapeOpeningLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"

int main(int argc, char * argv [])
{

  if( argc < 6 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  outputImage number_of_pixels_threshold_high number_of_pixels_threshold_low roundness_threshold" << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::Image<unsigned short, 2>  ImageType;
  typedef itk::Image<unsigned short, 2>  LabelImageType;

  typedef  itk::ImageFileReader< ImageType   >  ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  // Create a ShapeLabelMap from the image
  typedef itk::LabelImageToShapeLabelMapFilter<ImageType> LabelImageToShapeLabelMapFilterType;
  LabelImageToShapeLabelMapFilterType::Pointer binaryImageToShapeLabelMapFilter = LabelImageToShapeLabelMapFilterType::New();
  binaryImageToShapeLabelMapFilter->SetInput( reader->GetOutput() );
  binaryImageToShapeLabelMapFilter->Update();

  // Remove label objects that have NUMBER_OF_PIXELS less than command line argument.
  typedef itk::ShapeOpeningLabelMapFilter< LabelImageToShapeLabelMapFilterType::OutputImageType > ShapeOpeningLabelMapFilterType;

  ShapeOpeningLabelMapFilterType::Pointer shapeOpeningLabelMapFilter1 = ShapeOpeningLabelMapFilterType::New();
  ShapeOpeningLabelMapFilterType::Pointer shapeOpeningLabelMapFilter2 = ShapeOpeningLabelMapFilterType::New();
  ShapeOpeningLabelMapFilterType::Pointer shapeOpeningLabelMapFilter3 = ShapeOpeningLabelMapFilterType::New();

  shapeOpeningLabelMapFilter1->SetInput( binaryImageToShapeLabelMapFilter->GetOutput() );
  shapeOpeningLabelMapFilter1->SetLambda( atoi( argv[3] ) );
  shapeOpeningLabelMapFilter1->ReverseOrderingOn();
  shapeOpeningLabelMapFilter1->SetAttribute( ShapeOpeningLabelMapFilterType::LabelObjectType::NUMBER_OF_PIXELS);
  shapeOpeningLabelMapFilter1->Update();

  shapeOpeningLabelMapFilter2->SetInput( shapeOpeningLabelMapFilter1->GetOutput() );
  shapeOpeningLabelMapFilter2->SetLambda( atoi( argv[4] ) );
  shapeOpeningLabelMapFilter2->ReverseOrderingOff();
  shapeOpeningLabelMapFilter2->SetAttribute( ShapeOpeningLabelMapFilterType::LabelObjectType::NUMBER_OF_PIXELS);
  shapeOpeningLabelMapFilter2->Update();

  shapeOpeningLabelMapFilter3->SetInput( shapeOpeningLabelMapFilter2->GetOutput() );
  shapeOpeningLabelMapFilter3->SetLambda( atoi( argv[5] ) );
  shapeOpeningLabelMapFilter3->ReverseOrderingOff();
  shapeOpeningLabelMapFilter3->SetAttribute( ShapeOpeningLabelMapFilterType::LabelObjectType::ROUNDNESS);
  shapeOpeningLabelMapFilter3->Update();


  // Create a label image
  typedef itk::LabelMapToLabelImageFilter<LabelImageToShapeLabelMapFilterType::OutputImageType, LabelImageType> LabelMapToLabelImageFilterType;
  LabelMapToLabelImageFilterType::Pointer labelMapToLabelImageFilter = LabelMapToLabelImageFilterType::New();
  labelMapToLabelImageFilter->SetInput(shapeOpeningLabelMapFilter3->GetOutput());
  labelMapToLabelImageFilter->Update();

  typedef itk::RGBPixel<unsigned char>   RGBPixelType;
  typedef itk::Image<RGBPixelType, 2>    RGBImageType;

  // Color each label/object a different color
  typedef itk::ScalarToRGBColormapImageFilter<LabelImageType, RGBImageType> RGBFilterType;
  RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetInput(labelMapToLabelImageFilter->GetOutput());
  colormapImageFilter->SetColormap( RGBFilterType::Jet );
  colormapImageFilter->Update();

  // Write the output
  typedef itk::ImageFileWriter< RGBImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( colormapImageFilter->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();

  return EXIT_SUCCESS;
}
