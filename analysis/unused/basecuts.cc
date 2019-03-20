#include "basecuts.h"

void addBaseCuts(RooUtil::Cutflow& cutflow)
{
    cutflow.addCut("CutWeight"                    , [&]() { return 1                                                            ; } , [&]() { return weight                             ; } );
    cutflow.addCutToLastActiveCut("CutPresel"     , [&]() { return presel                                                       ; } , [&]() { return 1                                  ; } );
    cutflow.addCutToLastActiveCut("CutTrigger"    , [&]() { return trigger                                                      ; } , [&]() { return trig_sf                            ; } );

    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutSRDilep"    , [&]() { return doFakeEstimation ? isfakedilep : isdilep                     ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutSRTrilep"   , [&]() { return doFakeEstimation ? isfaketrilep : istrilep                   ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutWZCRDilep"  , [&]() { return doFakeEstimation ? isfakewzcrtrilep : iswzcrtrilep           ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutWZCRTrilep" , [&]() { return doFakeEstimation ? isfaketrilep : iswzcrtrilep               ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutARDilep"    , [&]() { return isfakedilep                                                  ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutARTrilep"   , [&]() { return isfaketrilep                                                 ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutPresel");
    cutflow.addCutToLastActiveCut("CutOSDilep"    , [&]() { return osdileppresel                                                ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutLRDilep"    , [&]() { return isloosedilep                                                 ; } , [&]() { return 1                                  ; } );

}
