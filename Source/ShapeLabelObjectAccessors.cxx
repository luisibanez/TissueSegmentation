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
#include "itkSimpleFilterWatcher.h"

#include "itkLabelMap.h"

#include "itkShapeKeepNObjectsLabelMapFilter.h"
#include "itkLabelImageToShapeLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"

#include "itkTestingMacros.h"

int main(int argc, char * argv[])
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " input ";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int dim = 2;

  typedef unsigned short                           PixelType;
  typedef itk::Image< PixelType, dim >            ImageType;
  typedef itk::ShapeLabelObject< PixelType, dim > ShapeLabelObjectType;
  typedef itk::LabelMap< ShapeLabelObjectType >   LabelMapType;
  typedef itk::ImageFileReader< ImageType >       ReaderType;

  // Exercise the attribute translation code and verify that
  // translations are correct
  int status = EXIT_SUCCESS;

  std::vector<std::string> attributes;
  attributes.push_back("Label");
  attributes.push_back("NumberOfPixels");
  attributes.push_back("PhysicalSize");
  attributes.push_back("Centroid");
  attributes.push_back("BoundingBox");
  attributes.push_back("NumberOfPixelsOnBorder");
  attributes.push_back("PerimeterOnBorder");
  attributes.push_back("FeretDiameter");
  attributes.push_back("PrincipalMoments");
  attributes.push_back("PrincipalAxes");
  attributes.push_back("Elongation");
  attributes.push_back("Perimeter");
  attributes.push_back("Roundness");
  attributes.push_back("EquivalentSphericalRadius");
  attributes.push_back("EquivalentSphericalPerimeter");
  attributes.push_back("EquivalentEllipsoidDiameter");
  attributes.push_back("Flatness");
  attributes.push_back("PerimeterOnBorderRatio");
  for (size_t a = 0; a < attributes.size(); a++)
    {
    if (ShapeLabelObjectType::GetNameFromAttribute(ShapeLabelObjectType::GetAttributeFromName(attributes[a])) != attributes[a])
      {
      std::cout << "Attribute translation for " << attributes[a] << " failed." << std::endl;
      std::cout << "   Received " << ShapeLabelObjectType::GetNameFromAttribute(ShapeLabelObjectType::GetAttributeFromName(attributes[a])) << " but expected " << attributes[a] << std::endl;
      status = EXIT_FAILURE;
      }
    }
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::LabelImageToShapeLabelMapFilter< ImageType, LabelMapType> I2LType;
  I2LType::Pointer i2l = I2LType::New();
  i2l->SetInput( reader->GetOutput() );
  i2l->SetComputePerimeter(true);
  i2l->Update();

  LabelMapType *labelMap = i2l->GetOutput();
  std::cout << "File " << argv[1] << " has " << labelMap->GetNumberOfLabelObjects() << " labels." << std::endl;

  // Retrieve all attributes
  for (unsigned int n = 0; n < labelMap->GetNumberOfLabelObjects(); n++)
    {
    ShapeLabelObjectType *labelObject = labelMap->GetNthLabelObject(n);
    std::cout << "Label: "
              << itk::NumericTraits<LabelMapType::LabelType>::PrintType(labelObject->GetLabel()) << std::endl;
    /*
    std::cout << "    BoundingBox: "
              << labelObject->GetBoundingBox() << std::endl;
    */
    std::cout << "    NumberOfPixels: "
              << labelObject->GetNumberOfPixels() << std::endl;
    /* 
    std::cout << "    PhysicalSize: "
              << labelObject->GetPhysicalSize() << std::endl;
    std::cout << "    Centroid: "
              << labelObject->GetCentroid() << std::endl;
    std::cout << "    NumberOfPixelsOnBorder: "
              << labelObject->GetNumberOfPixelsOnBorder() << std::endl;
    std::cout << "    PerimeterOnBorder: "
              << labelObject->GetPerimeterOnBorder() << std::endl;
    std::cout << "    FeretDiameter: "
              << labelObject->GetFeretDiameter() << std::endl;
    std::cout << "    PrincipalMoments: "
              << labelObject->GetPrincipalMoments() << std::endl;
    std::cout << "    PrincipalAxes: "
              << labelObject->GetPrincipalAxes() << std::endl;
    */

    std::cout << "    Elongation: "
              << labelObject->GetElongation() << std::endl;

    /*
    std::cout << "    Perimeter: "
              << labelObject->GetPerimeter() << std::endl;

    */

    std::cout << "    Roundness: "
              << labelObject->GetRoundness() << std::endl;

    /*
    std::cout << "    EquivalentSphericalRadius: "
              << labelObject->GetEquivalentSphericalRadius() << std::endl;
    std::cout << "    EquivalentSphericalPerimeter: "
              << labelObject->GetEquivalentSphericalPerimeter() << std::endl;
    std::cout << "    EquivalentEllipsoidDiameter: "
              << labelObject->GetEquivalentEllipsoidDiameter() << std::endl;
    std::cout << "    Flatness: "
              << labelObject->GetFlatness() << std::endl;
    std::cout << "    PerimeterOnBorderRatio: "
              << labelObject->GetPerimeterOnBorderRatio() << std::endl;
    */
    }
  return status;
}
