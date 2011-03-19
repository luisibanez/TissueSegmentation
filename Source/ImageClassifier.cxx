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
#include "itkGaussianMixtureModelComponent.h"
#include "itkMaximumDecisionRule2.h"
#include "itkImageToListSampleAdaptor.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc, char * argv [] )
{
  if( argc < 3 )
    {
    std::cerr << "Missing command line arguments: ";
    std::cerr << argv[0] << "\t" << "InputImage ClassifiedOutputImage" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int MeasurementVectorSize = 3;
  typedef unsigned char MeasurementComponentType;
  const unsigned int numberOfClasses = 2;

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

  ClassLabelVectorType & classLabelVector  = classLabelsObject->Get();

  typedef ImageClassifierFilterType::ClassLabelType        ClassLabelType;

  ClassLabelType  class1 = 0;
  ClassLabelType  class2 = 255;

  classLabelVector.push_back( class1 );
  classLabelVector.push_back( class2 );

  typedef ImageClassifierFilterType::MembershipFunctionVectorObjectType MembershipFunctionVectorObjectType;

  MembershipFunctionVectorObjectType::Pointer membershipFunctionsObject = MembershipFunctionVectorObjectType::New();

  typedef ImageClassifierFilterType::MembershipFunctionVectorType MembershipFunctionVectorType;

  MembershipFunctionVectorType membershipFunctions;

  typedef itk::Statistics::GaussianMembershipFunction< MeasurementVectorType >  GaussianMembershipFunctionType;

  GaussianMembershipFunctionType::Pointer membershipFunction1 = GaussianMembershipFunctionType::New();
  GaussianMembershipFunctionType::Pointer membershipFunction2 = GaussianMembershipFunctionType::New();

  GaussianMembershipFunctionType::MeanType mean1( MeasurementVectorSize );

  mean1[0] = 230.0;
  mean1[1] = 223.5;
  mean1[2] = 230.5;

  membershipFunction1->SetMean( mean1 );


  GaussianMembershipFunctionType::CovarianceType covariance1( MeasurementVectorSize, MeasurementVectorSize );

  covariance1(0,0) = 16.2437;
  covariance1(0,1) = 18.9413;
  covariance1(0,2) = 4.37528;
  covariance1(1,0) = 18.9413;
  covariance1(1,1) = 71.5639;
  covariance1(1,2) = 12.5409;
  covariance1(2,0) = 4.37528;
  covariance1(2,1) = 12.5409;
  covariance1(2,2) = 31.2956;

  membershipFunction1->SetCovariance( covariance1 );


  GaussianMembershipFunctionType::MeanType mean2( MeasurementVectorSize );

  mean2[0] = 0.0;
  mean2[1] = 0.0;
  mean2[2] = 0.0;

  membershipFunction2->SetMean( mean2 );


  GaussianMembershipFunctionType::CovarianceType covariance2( MeasurementVectorSize, MeasurementVectorSize );

  covariance2(0,0) = 1.0;
  covariance2(0,1) = 0.0;
  covariance2(0,2) = 0.0;
  covariance2(1,0) = 0.0;
  covariance2(1,1) = 1.0;
  covariance2(1,2) = 0.0;
  covariance2(2,0) = 0.0;
  covariance2(2,1) = 0.0;
  covariance2(2,2) = 1.0;

  membershipFunction2->SetCovariance( covariance2 );


  membershipFunctions.push_back( membershipFunction1.GetPointer() );
  membershipFunctions.push_back( membershipFunction2.GetPointer() );

  membershipFunctionsObject->Set( membershipFunctions );

  typedef ImageClassifierFilterType::MembershipFunctionsWeightsArrayObjectType  MembershipFunctionsWeightsArrayObjectType;

  MembershipFunctionsWeightsArrayObjectType::Pointer weightArrayObjects = MembershipFunctionsWeightsArrayObjectType::New();

  ImageClassifierFilterType::MembershipFunctionsWeightsArrayType  weightsArray(numberOfClasses);

  weightsArray[0] = 0.5;
  weightsArray[1] = 0.5;

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

  return EXIT_SUCCESS;
}
