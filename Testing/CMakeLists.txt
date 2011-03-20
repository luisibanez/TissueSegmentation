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
  DATA{ernou.tor5564m12_lumen_seeds.txt}
  4.0
  2
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test4
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  DATA{ernou.tor5564m12_small_lumen_seeds.txt}
  1.5
  3
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
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
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_lumen_Mahalanobis_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test9
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_lumen_Mahalanobis_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test10
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_lumen_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test11
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_lumen_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test12
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_germ_cells.png
  DATA{ernou.tor5564m12_small_germ_cells_seeds.txt}
  3.5
  5
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  )
