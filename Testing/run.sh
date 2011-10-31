#!/bin/bash
MAJORITY=1
 ./bin/VotingBinaryHoleFillingImageFilter ~/Downloads/invertedMask.png      /tmp/invertedMaskHoleFilled1.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled1.png  /tmp/invertedMaskHoleFilled2.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled2.png  /tmp/invertedMaskHoleFilled3.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled3.png  /tmp/invertedMaskHoleFilled4.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled4.png  /tmp/invertedMaskHoleFilled5.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled5.png  /tmp/invertedMaskHoleFilled6.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled6.png  /tmp/invertedMaskHoleFilled7.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled7.png  /tmp/invertedMaskHoleFilled8.png 255 0 2 ${MAJORITY}
 ./bin/VotingBinaryHoleFillingImageFilter /tmp/invertedMaskHoleFilled8.png  /tmp/invertedMaskHoleFilled9.png 255 0 2 ${MAJORITY}
 ./bin/SignedMaurerDistanceMapImageFilter /tmp/invertedMaskHoleFilled9.png  /tmp/invertedMaskDistanceMapMaurer9_${MAJORITY}.png

 ./bin/WatershedSegmentation \
    /tmp/invertedMaskDistanceMapMaurer9_${MAJORITY}.png \
    /tmp/invertedMaskDistanceMapMaurer9_1_Gradient.mha \
    /tmp/invertedMaskDistanceMapMaurer9_Watershed_Color_3.png \
    /tmp/invertedMaskDistanceMapMaurer9_Watershed_Labels_3.mha \
    0.01 0.3

