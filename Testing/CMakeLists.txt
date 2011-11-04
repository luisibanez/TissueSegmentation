#
#  Configure tests here
#

set(TEMP ${PROJECT_BINARY_DIR}/Testing/Temporary)


ExternalData_Add_Test( UNCTissueData
  NAME Test01
  COMMAND ImageReadWrite
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test02
  COMMAND ImageReadWrite
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test03
  COMMAND HistogramInRGBSpace
  ${TEMP}/ernou_tor5564m12_small.png
  ${TEMP}/ernou_tor5564m12_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test04
  COMMAND HistogramInRGBSpace
  ${TEMP}/ernou_tor5564m12_small.png
  ${TEMP}/ernou_tor5564m12_small_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test05
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_outer.png
  DATA{ernou.tor5564m12_lumen_seeds.txt}
  4.0
  2
  3
  ${TEMP}/ernou_tor5564m12_lumen_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test06
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_lumen.png
  DATA{ernou.tor5564m12_small_lumen_seeds.txt}
  1.5
  3
  2
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test07
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_histogram_pure.mhd
  ${TEMP}/ernou_tor5564m12_small_lumen.png
  0
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test08
  COMMAND HistogramInRGBSpace
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_histogram_residual.mhd
  ${TEMP}/ernou_tor5564m12_small_lumen.png
  1
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test09
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_lumen_Mahalanobis_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test10
  COMMAND MahalanobisClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_lumen_Mahalanobis_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test11
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_lumen_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test12
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_lumen_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test13
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_germ_cells.png
  DATA{ernou.tor5564m12_small_germ_cells_seeds.txt}
  0.001
  1
  2
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test14
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_epithelium.png
  DATA{ernou.tor5564m12_small_epithelium_seeds.txt}
  1.5
  2
  1
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test15
  COMMAND VectorConfidenceConnected
  DATA{ernou.tor5564m12_epithelium.tif}
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium.png
  DATA{ernou.tor5564m12_epithelium_seeds.txt}
  1.5
  2
  1
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium_membership_function.txt
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test16
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_epithelium_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test17
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_epithelium_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
NAME Test18
COMMAND VectorConfidenceConnected
DATA{ernou.tor5564m12_small.tif}
${TEMP}/ernou_tor5564m12_small_mature_cells.png
DATA{ernou.tor5564m12_small_mature_cells_seeds.txt}
0.01
1
3
${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
)

ExternalData_Add_Test( UNCTissueData
  NAME Test19
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_mature_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test20
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_mature_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test21
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_germ_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test22
  COMMAND MembershipImageFilter
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_germ_cells_Membership_classified.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test23
  COMMAND HistogramMembership
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_germ_cells_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test24
  COMMAND HistogramMembership
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_lumen_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test25
  COMMAND HistogramMembership
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_epithelium_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test26
  COMMAND HistogramMembership
  ${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_mature_cells_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test27
  COMMAND HistogramMembership
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium_histogram.mhd
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test28
  COMMAND ImageClassifier
  DATA{ernou.tor5564m12_small.tif}
  ${TEMP}/ernou_tor5564m12_small_classified_labels.png
  ${TEMP}/ernou_tor5564m12_small_classified_colors.png
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium_membership_function.txt
  0.20   # Lumen
  0.25   # Germ cells
  0.20   # Epithelium
  0.30   # Mature cells
  0.05   # Tunica
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test29
  COMMAND ImageClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_classified_labels.png
  ${TEMP}/ernou_tor5564m12_classified_colors.png
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium_membership_function.txt # Tunica
  0.20   # Lumen
  0.25   # Germ cells
  0.20   # Epithelium
  0.30   # Mature cells
  0.05   # Tunica
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test30
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_small_classified_labels.png
  ${TEMP}/ernou_tor5564m12_small_classified_labels_germ_cells.png
  1
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test31
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_small_classified_labels.png
  ${TEMP}/ernou_tor5564m12_small_classified_labels_lumen.png
  2
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test32
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_small_classified_labels.png
  ${TEMP}/ernou_tor5564m12_small_classified_labels_epithelium.png
  3
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test33
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_small_classified_labels.png
  ${TEMP}/ernou_tor5564m12_small_classified_labels_mature_cells.png
  4
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test34
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_small_classified_labels.png
  ${TEMP}/ernou_tor5564m12_small_classified_labels_epithelium_epithelium.png
  5
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test35
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_classified_labels.png
  ${TEMP}/ernou_tor5564m12_classified_labels_germ_cells.png
  1
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test36
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_classified_labels.png
  ${TEMP}/ernou_tor5564m12_classified_labels_lumen.png
  2
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test37
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_classified_labels.png
  ${TEMP}/ernou_tor5564m12_classified_labels_epithelium.png
  3
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test38
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_classified_labels.png
  ${TEMP}/ernou_tor5564m12_classified_labels_mature_cells.png
  4
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test39
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_classified_labels.png
  ${TEMP}/ernou_tor5564m12_classified_labels_epithelium_epithelium.png
  5
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test40
  COMMAND ImageClassifier
  DATA{ernou.tor5564m12.tif}
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium.png
  ${TEMP}/ernou_tor5564m12_classified_colors_tubules_and_ephitelium.png
  ${TEMP}/ernou_tor5564m12_small_lumen_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_germ_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_epithelium_membership_function.txt
  ${TEMP}/ernou_tor5564m12_small_mature_cells_membership_function.txt
  ${TEMP}/ernou_tor5564m12_epithelium_epithelium_membership_function.txt # Tunica
  0.50000   # Lumen
  0.00001   # Germ cells
  2.00000   # Epithelium
  0.10000   # Mature cells
  0.00000   # Tunica
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test41  # goal = eliminate green speckles inside blue regions
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_01.png
  2   # Background
  3   # Foreground
  2   # Radius
  1   # Majority
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test42  # goal = eliminate green speckles inside blue regions
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_01.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_02.png
  2   # Background
  3   # Foreground
  2   # Radius
  1   # Majority
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test43  # goal = eliminate green speckles inside blue regions
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_02.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_03.png
  2   # Background
  3   # Foreground
  2   # Radius
  1   # Majority
  )
ExternalData_Add_Test( UNCTissueData
  NAME Test44  # goal = eliminate green speckles inside blue regions
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_03.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_04.png
  2   # Background
  3   # Foreground
  2   # Radius
  1   # Majority
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test45  # goal = eliminate green speckles inside blue regions
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_04.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_05.png
  2   # Background
  3   # Foreground
  2   # Radius
  1   # Majority
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test46  # goal = eliminate green speckles inside blue regions
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_05.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_voting_06.png
  2   # Background
  3   # Foreground
  2   # Radius
  1   # Majority
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test50
  COMMAND ExtractLabelAsMask
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_mask.png
  3
  )

ExternalData_Add_Test( UNCTissueData
NAME Test51  # goal = eliminate green speckles inside blue regions
COMMAND VotingBinaryIterativeHoleFillingImageFilter
${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_mask.png
${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_mask_voting.png
  0 # Background
255 # Foreground
  2 # Radius
  1 # Majority
 50 # Maximun number of iterations
)

ExternalData_Add_Test( UNCTissueData
  NAME Test52
  COMMAND ConnectedComponentsImageFilter
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_mask_voting.png
  ${TEMP}/ernou_tor5564m12_classified_labels_tubules_and_ephitelium_mask_voting_components.png
  500  # Minimum Component Size
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test53
  COMMAND JoinMasks
  ${TEMP}/ernou_tor5564m12_classified_labels_mature_cells.png
  ${TEMP}/ernou_tor5564m12_classified_labels_germ_cells.png
  ${TEMP}/ernou_tor5564m12_classified_labels_ALLCells.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test54 #goal is to combine the Epithelium and Germ cells
  COMMAND JoinMasks
  ${TEMP}/ernou_tor5564m12_classified_labels_epithelium.png
  ${TEMP}/ernou_tor5564m12_classified_labels_germ_cells.png
  ${TEMP}/ernou_tor5564m12_solid_mask.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test55  # goal = invert the solid mask 
  COMMAND InvertFilter
  ${TEMP}/ernou_tor5564m12_solid_mask.png
  ${TEMP}/ernou_tor5564m12_solid_mask_inverted.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test56  # goal = fill in the holes in the combined epithelim_Germ cells mask 
  COMMAND VotingBinaryHoleFillingImageFilter
  ${TEMP}/ernou_tor5564m12_solid_mask_inverted.png
  ${TEMP}/ernou_tor5564m12_MaskHoleFilled.png
  0   # Background
  255   # Foreground
  2   # Radius
  1   # Majority
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test57  # goal = apply watershed segmentation to segment the tubules
  COMMAND SignedDanielssonDistanceMapImageFilter
  ${TEMP}/ernou_tor5564m12_MaskHoleFilled.png
  ${TEMP}/ernou_tor5564m12_DistanceMap.png
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test58  # goal = apply watershed segmentation to segment the tubules
  COMMAND WatershedSegmentation
  ${TEMP}/ernou_tor5564m12_DistanceMap.png
  ${TEMP}/ernou_tor5564m12_Gradient.mha
  ${TEMP}/ernou_tor5564m12_Watershed_Color.png
  ${TEMP}/ernou_tor5564m12_Watershed_Labels.mha
  0.01
  0.3
  )

ExternalData_Add_Test( UNCTissueData
  NAME Test59  # goal = geometrical shape analysis to identify the tubules
  COMMAND ShapeOpeningLabelMapFilter
  ${TEMP}/ernou_tor5564m12_Watershed_Label.png
  ${TEMP}/ernou_tor5564m12_detectedTubules.png
  78000 
  1000
  0.45
  )

















































