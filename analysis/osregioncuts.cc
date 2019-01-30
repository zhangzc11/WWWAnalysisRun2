#include "osregioncuts.h"

addOppositeSignControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    cutflow.getCut("CutOSDilep");
    cutflow.addCutToLastActiveCut("OSCRmm"                , [&]() { return (www.lep_pdgId()[0]*www.lep_pdgId()[1]==-169)*(www.MllSS()>40.)    ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmMET"             , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRmmFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutOSDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("OSCRem"                , [&]() { return (www.lep_pdgId()[0]*www.lep_pdgId()[1]==-143)*(www.MllSS()>30.)    ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemMllSS"           , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemMTmax"           , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCRemFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutOSDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("OSCRee"                , [&]() { return (www.lep_pdgId()[0]*www.lep_pdgId()[1]==-121)*(1)*(www.MllSS()>40.); }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("OSCReeFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
}
