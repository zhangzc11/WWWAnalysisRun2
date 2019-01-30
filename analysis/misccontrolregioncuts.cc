#include "misccontrolregioncuts.h"

void addGammaControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Gamma control region
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("PhotonCR"              , [&]() { return (www.met_pt()<50)*(www.Mll3L()>20.)*(fabs(www.Mll3L1())>20.)       ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("PhotonCRNj1"           , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("PhotonCRNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("PhotonCRFull"          , [&]() { return passPhotonCRSFOS                                                   ; }        , [&]() { return 1                     ; } ) ;

}

void addOppositeSignControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Same-sign Mjj on-W region
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

void addLooseLeptonControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Loose lepton regions
    cutflow.getCut("CutLRDilep");
    cutflow.addCutToLastActiveCut("LRSSmm"                , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmMET"             , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSmmFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutLRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LRSSem"                , [&]() { return (www.passSSem())*(www.MllSS()>30.)*( (fabs(www.lep_pdgId()[0])==13) * (www.lep_relIso03EAv2Lep()[0] < 0.03) + (fabs(www.lep_pdgId()[1])==13) * (www.lep_relIso03EAv2Lep()[1] < 0.03) ) ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemMllSS"           , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemMTmax"           , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSemFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutLRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LRSSee"                , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LRSSeeFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
}
