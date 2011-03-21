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

#include "itkImageClassifierFilter.h"
#include "itkFixedArray.h"
#include "itkGaussianMembershipFunction.h"
#include "itkMaximumDecisionRule2.h"
#include "itkImageToListSampleAdaptor.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"

int main(int argc, char * argv [] )
{
  if( argc < 5 )
    {
    std::cerr << "Missing command line arguments: ";
    std::cerr << argv[0] << "\t" << "InputImage ClassifiedOutputImage ColorEncodedClassifiedImage inputMembership1 inputMembership2 ..." << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int MeasurementVectorSize = 3;
  const unsigned int NumberOfComponents = MeasurementVectorSize;
  typedef unsigned char MeasurementComponentType;

  const unsigned int numberOfArgumentsBeforeMemberships = 4;

  const unsigned int numberOfClasses = argc - numberOfArgumentsBeforeMemberships;

  typedef itk::FixedArray< MeasurementComponentType, MeasurementVectorSize > InputPixelType;
  typedef InputPixelType          MeasurementVectorType;

  const unsigned int ImageDimension = 2;
  typedef itk::Image< InputPixelType, ImageDimension > InputImageType;

  typedef unsigned char OutputPixelType;

  typedef itk::Image< OutputPixelType, ImageDimension > OutputImageType;

  typedef itk::ImageFileReader< InputImageType >   ReaderType;
  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( argv[1] );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  InputImageType::ConstPointer image = reader->GetOutput();

  typedef  itk::Statistics::ImageToListSampleAdaptor< InputImageType > ImageToListSampleAdaptorType;

  ImageToListSampleAdaptorType::Pointer sample = ImageToListSampleAdaptorType::New();
  sample->SetImage( image );

  typedef itk::Statistics::ImageClassifierFilter<
    ImageToListSampleAdaptorType, InputImageType, OutputImageType > ImageClassifierFilterType;

  ImageClassifierFilterType::Pointer filter = ImageClassifierFilterType::New();

  typedef ImageClassifierFilterType::ClassLabelVectorObjectType               ClassLabelVectorObjectType;
  typedef ImageClassifierFilterType::ClassLabelVectorType                     ClassLabelVectorType;

  ClassLabelVectorObjectType::Pointer  classLabelsObject = ClassLabelVectorObjectType::New();

  ClassLabelVectorType classLabelVector  = classLabelsObject->Get();

  typedef ImageClassifierFilterType::MembershipFunctionVectorObjectType MembershipFunctionVectorObjectType;

  MembershipFunctionVectorObjectType::Pointer membershipFunctionsObject = MembershipFunctionVectorObjectType::New();

  typedef ImageClassifierFilterType::MembershipFunctionVectorType MembershipFunctionVectorType;

  MembershipFunctionVectorType membershipFunctions;

  typedef itk::Statistics::GaussianMembershipFunction< MeasurementVectorType >  GaussianMembershipFunctionType;
  typedef GaussianMembershipFunctionType::MeanType         MeanVectorType;
  typedef GaussianMembershipFunctionType::CovarianceType   CovarianceMatrixType;

  for( unsigned int j = 0; j < numberOfClasses; j++ )
    {
    classLabelVector.push_back( 100 + j * 50 );

    GaussianMembershipFunctionType::Pointer membershipFunction = GaussianMembershipFunctionType::New();

    MeanVectorType mean(NumberOfComponents);

    CovarianceMatrixType covariance(NumberOfComponents,NumberOfComponents);

    std::ifstream inputMembership;

    const unsigned int numberOfArgument = j + numberOfArgumentsBeforeMemberships;

    inputMembership.open( argv[numberOfArgument] );

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

    membershipFunctions.push_back( membershipFunction.GetPointer() );
    }

  classLabelsObject->Set( classLabelVector );

  membershipFunctionsObject->Set( membershipFunctions );

  typedef ImageClassifierFilterType::MembershipFunctionsWeightsArrayObjectType  MembershipFunctionsWeightsArrayObjectType;

  MembershipFunctionsWeightsArrayObjectType::Pointer weightArrayObjects = MembershipFunctionsWeightsArrayObjectType::New();

  ImageClassifierFilterType::MembershipFunctionsWeightsArrayType  weightsArray(numberOfClasses);

  weightsArray[0] = 0.20;   // Lumen
  weightsArray[1] = 0.25;   // Germ cells
  weightsArray[2] = 0.20;   // Epithelium
  weightsArray[3] = 0.30;   // Mature cells
  weightsArray[4] = 0.05;  // External epithelium

  weightArrayObjects->Set( weightsArray );

  filter->SetImage( image );
  filter->SetNumberOfClasses( numberOfClasses );
  filter->SetClassLabels( classLabelsObject );
  filter->SetMembershipFunctions( membershipFunctionsObject );
  filter->SetMembershipFunctionsWeightsArray( weightArrayObjects );

  typedef itk::Statistics::MaximumDecisionRule2  DecisionRuleType;
  DecisionRuleType::Pointer decisionRule = DecisionRuleType::New();

  filter->SetDecisionRule( decisionRule );

  try
    {
    filter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }


  typedef itk::ImageFileWriter< OutputImageType > OutputImageWriterType;

  OutputImageWriterType::Pointer outputImageWriter = OutputImageWriterType::New();

  outputImageWriter->SetFileName( argv[2] );
  outputImageWriter->SetInput( filter->GetOutput() );

  try
    {
    outputImageWriter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }


  //
  //  Instantiate the filter that will encode the label image
  //  into a color image (random color attribution).
  //
  typedef itk::RGBPixel<unsigned char>      RGBPixelType;

  typedef itk::Image< RGBPixelType, ImageDimension >  RGBImageType;

  typedef  itk::ImageFileWriter< RGBImageType  >      RGBWriterType;

  RGBWriterType::Pointer colorWriter = RGBWriterType::New();


  typedef itk::Functor::ScalarToRGBPixelFunctor< unsigned char > ColorMapFunctorType;

  typedef itk::UnaryFunctorImageFilter<
                                OutputImageType,
                                RGBImageType,
                                ColorMapFunctorType
                                                > ColorMapFilterType;

  ColorMapFilterType::Pointer colorMapFilter = ColorMapFilterType::New();

  colorMapFilter->SetInput(  filter->GetOutput() );

  colorWriter->SetFileName( argv[3] );

  colorWriter->SetInput( colorMapFilter->GetOutput() );

  try
    {
    colorWriter->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << excep << std::endl;
    }

  return EXIT_SUCCESS;
}
