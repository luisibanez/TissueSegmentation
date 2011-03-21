#
#  Configure tests here
#

set(TEMP ${PROJECT_BINARY_DIR}/Testing/Temporary)

ExternalData_Add_Test( UNCTissueData
  NAME Test27
  COMMAND ImageClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_classified_labels.png
  ${TEMP}/ernou.tor5564m12_classified_colors.png
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_epithelium_epithelium_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test26
  COMMAND ImageClassifier
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_classified_labels.png
  ${TEMP}/ernou.tor5564m12_small_classified_colors.png
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_epithelium_epithelium_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test25
  COMMAND HistogramMembership
  ${TEMP}/ernou.tor5564m12_epithelium_epithelium_membership_function.txt
  ${TEMP}/ernou.tor5564m12_epithelium_epithelium_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test24
  COMMAND HistogramMembership
  ${TEMP}/ernou.tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_mature_cells_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test23
  COMMAND HistogramMembership
  ${TEMP}/ernou.tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou.tor5564m12_epithelium_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test22
  COMMAND HistogramMembership
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_lumen_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test21
  COMMAND HistogramMembership
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_germ_cells_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test20
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_germ_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test19
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_germ_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test18
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_mature_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test17
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_mature_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test16
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_mature_cells.png
  DATA{ernou.tor5564m12_small_mature_cells_seeds.txt}
  0.01
  1
  3
  ${TEMP}/ernou.tor5564m12_small_mature_cells_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test15
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou.tor5564m12_epithelium_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test14
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_epithelium_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test13
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_epithelium.tif}
  ${TEMP}/ernou.tor5564m12_epithelium_epithelium.png
  DATA{ernou.tor5564m12_epithelium_seeds.txt}
  1.5
  2
  1
  ${TEMP}/ernou.tor5564m12_epithelium_epithelium_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test12
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_epithelium.png
  DATA{ernou.tor5564m12_small_epithelium_seeds.txt}
  1.5
  2
  1
  ${TEMP}/ernou.tor5564m12_small_epithelium_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test11
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_germ_cells.png
  DATA{ernou.tor5564m12_small_germ_cells_seeds.txt}
  0.001
  1
  2
  ${TEMP}/ernou.tor5564m12_small_germ_cells_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test10
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_lumen_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test09
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_lumen_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test08
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_lumen_Mahalanobis_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test07
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou.tor5564m12_small_lumen_Mahalanobis_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test06
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_histogram_residual.mhd
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  1
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test05
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_histogram_pure.mhd
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  0
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test04
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  DATA{ernou.tor5564m12_small_lumen_seeds.txt}
  1.5
  3
  2
  ${TEMP}/ernou.tor5564m12_small_lumen_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test03
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_outer.png
  DATA{ernou.tor5564m12_lumen_seeds.txt}
  4.0
  2
  3
  ${TEMP}/ernou.tor5564m12_lumen_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test02
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test01
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou.tor5564m12_histogram.mhd
  )

