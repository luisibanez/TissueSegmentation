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

add_executable( HistogramMembership  HistogramMembership.cxx )
target_link_libraries( HistogramMembership ${ITK_LIBRARIES} )

add_executable( ExtractLabelAsMask  ExtractLabelAsMask.cxx )
target_link_libraries( ExtractLabelAsMask ${ITK_LIBRARIES} )

add_executable( ImageReadWrite  ImageReadWrite.cxx )
target_link_libraries( ImageReadWrite ${ITK_LIBRARIES} )

add_executable( VotingBinaryHoleFillingImageFilter  VotingBinaryHoleFillingImageFilter.cxx )
target_link_libraries( VotingBinaryHoleFillingImageFilter ${ITK_LIBRARIES} )

add_executable( VotingBinaryIterativeHoleFillingImageFilter  VotingBinaryIterativeHoleFillingImageFilter.cxx )
target_link_libraries( VotingBinaryIterativeHoleFillingImageFilter ${ITK_LIBRARIES} )

add_executable( ConnectedComponentsImageFilter  ConnectedComponentsImageFilter.cxx )
target_link_libraries( ConnectedComponentsImageFilter ${ITK_LIBRARIES} )
