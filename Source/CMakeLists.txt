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

add_executable( HoughTransform2DCirclesImageFilter  HoughTransform2DCirclesImageFilter.cxx )
target_link_libraries( HoughTransform2DCirclesImageFilter ${ITK_LIBRARIES} )

add_executable( JoinMasks  JoinMasks.cxx )
target_link_libraries( JoinMasks ${ITK_LIBRARIES} )

add_executable( WatershedSegmentation  WatershedSegmentation.cxx )
target_link_libraries( WatershedSegmentation ${ITK_LIBRARIES} )

add_executable( SignedDanielssonDistanceMapImageFilter   SignedDanielssonDistanceMapImageFilter.cxx )
target_link_libraries( SignedDanielssonDistanceMapImageFilter ${ITK_LIBRARIES} )

add_executable( SignedMaurerDistanceMapImageFilter   SignedMaurerDistanceMapImageFilter.cxx )
target_link_libraries( SignedMaurerDistanceMapImageFilter ${ITK_LIBRARIES} )

add_executable( ApproximateSignedDistanceMapImageFilter   ApproximateSignedDistanceMapImageFilter.cxx )
target_link_libraries( ApproximateSignedDistanceMapImageFilter ${ITK_LIBRARIES} )

add_executable( InvertFilter   InvertFilter.cxx )
target_link_libraries( InvertFilter ${ITK_LIBRARIES} )

add_executable( ShapeOpeningLabelMapFilter   ShapeOpeningLabelMapFilter.cxx )
target_link_libraries( ShapeOpeningLabelMapFilter ${ITK_LIBRARIES} )

add_executable( ShapeLabelObjectAccessors   ShapeLabelObjectAccessors.cxx )
target_link_libraries( ShapeLabelObjectAccessors ${ITK_LIBRARIES} )

add_executable( BinaryGrindPeakImageFilter   BinaryGrindPeakImageFilter.cxx )
target_link_libraries( BinaryGrindPeakImageFilter ${ITK_LIBRARIES} )

add_executable( AndImageFilter  AndImageFilter.cxx )
target_link_libraries( AndImageFilter ${ITK_LIBRARIES} )

add_executable( BinaryMorphologicalOpeningImageFilter  BinaryMorphologicalOpeningImageFilter.cxx )
target_link_libraries( BinaryMorphologicalOpeningImageFilter ${ITK_LIBRARIES} )










