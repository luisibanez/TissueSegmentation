#
#
#
add_executable( HistogramInRGBSpace  HistogramInRGBSpace.cxx )
target_link_libraries( HistogramInRGBSpace ${ITK_LIBRARIES} )

add_executable( VectorConfidenceConnected  VectorConfidenceConnected.cxx )
target_link_libraries( VectorConfidenceConnected ${ITK_LIBRARIES} )

add_executable( ImageClassifier  ImageClassifier.cxx )
target_link_libraries( ImageClassifier ${ITK_LIBRARIES} )

add_executable( MahalanobisClassifier  MahalanobisClassifier.cxx )
target_link_libraries( MahalanobisClassifier ${ITK_LIBRARIES} )

add_executable( MembershipImageFilter  MembershipImageFilter.cxx )
target_link_libraries( MembershipImageFilter ${ITK_LIBRARIES} )
