#
#  Configure tests here
#

set(TEMP ${PROJECT_BINARY_DIR}/Testing/Temporary)

ExternalData_Add_Test( UNCTissueData
  NAME Test1
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test2
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test3
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_outer.png
  10
  10
  3.0
  3
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test4
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  250
  300
  3.5
  5
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test5
  COMMAND ImageClassifier
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen_classified.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test6
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_histogram_pure.mhd
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  0
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test7
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_histogram_residual.mhd
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  1
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test8
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_lumen_Mahalanobis_classified.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test9
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_lumen_Mahalanobis_classified.png
  )
