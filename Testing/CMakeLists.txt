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
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou.tor5564m12_small_lumen.png
  250
  300
  3.0
  3
  )
