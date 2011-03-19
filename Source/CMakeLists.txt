#
#
#
add_executable( HistogramInRGBSpace  HistogramInRGBSpace.cxx )
target_link_libraries( HistogramInRGBSpace ${ITK_LIBRARIES} )

add_executable( VectorConfidenceConnected  VectorConfidenceConnected.cxx )
target_link_libraries( VectorConfidenceConnected ${ITK_LIBRARIES} )
