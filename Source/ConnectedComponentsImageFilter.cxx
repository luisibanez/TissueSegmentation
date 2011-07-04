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

#include "itkConnectedComponentImageFilter.h"
#include "itkRelabelComponentImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc, char * argv [] )
{
  if( argc < 4 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  outputImage  minimum_object_size" << std::endl;
    return EXIT_FAILURE;
    }

  typedef   unsigned char   InputPixelType;
  typedef   unsigned short  LablePixelType;
  typedef   unsigned char   OutputPixelType;
  const     unsigned int    Dimension = 2;

  typedef itk::Image< InputPixelType, Dimension >  InputImageType;
  typedef itk::Image< LablePixelType, Dimension >  LabelImageType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

  typedef itk::ImageFileReader< InputImageType > ReaderType;
  typedef itk::ImageFileWriter< OutputImageType > WriterType;

  typedef itk::ConnectedComponentImageFilter< InputImageType, LabelImageType > ComponentsFilterType;
  typedef itk::RelabelComponentImageFilter< LabelImageType, OutputImageType > RelabelType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  ComponentsFilterType::Pointer components = ComponentsFilterType::New();
  RelabelType::Pointer relabel = RelabelType::New();

  reader->SetFileName( argv[1] );

  components->SetInput( reader->GetOutput() );
  components->SetFullyConnected( true );
  relabel->SetInput( components->GetOutput() );

  itk::SizeValueType minimumSize = atoi( argv[3] );

  relabel->SetMinimumObjectSize( minimumSize );

  std::cerr << "minimumSize: " << minimumSize << std::endl;

  writer->SetInput( relabel->GetOutput() );
  writer->SetFileName( argv[2] );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }

  unsigned short numObjects = relabel->GetNumberOfObjects();

  std::cout << "Number of Objects = " << numObjects << std::endl;

  typedef RelabelType::ObjectSizeInPixelsContainerType SizeContainer;

  const SizeContainer & objectSizeList = relabel->GetSizeOfObjectsInPixels();

  SizeContainer::const_iterator sitr = objectSizeList.begin();
  SizeContainer::const_iterator send = objectSizeList.end();

  itk::IndexValueType counter = 0;

  while( sitr != send )
    {
    std::cout << counter++ << " " << *sitr++ << std::endl;
    }

  return EXIT_SUCCESS;
}
