cmake_minimum_required(VERSION 2.8)

if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(TissueSegmentation)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
set(ITK_EXECUTABLE_PATH "${EXECUTABLE_OUTPUT_PATH}")

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

include(${PROJECT_SOURCE_DIR}/CMake/ExternalData.cmake)
list(APPEND ExternalData_URL_TEMPLATES
  "file://local/home/ibanez/data/UNCTissueSegmentation/%(algo)/%(hash)"
  "http://midas.kitware.com/api/rest/midas.bitstream.by.hash?hash=%(hash)&algorithm=%(algo)"
  )

include(CTest)

add_subdirectory( Source )
add_subdirectory( Testing )
add_subdirectory( Documents )

ExternalData_Add_Target(UNCTissueData)
