#include "fakeratecontrolregioncuts.h"

void addBtaggedControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Btagged CR for Same-sign Mjj on-W region
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTCRSSmm"              , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmNbgeq1"        , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmMjjW"          , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmMET"           , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmMllSS"         , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSmmFull"          , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTCRSSem"              , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemNbgeq1"        , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemMjjW"          , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemMET"           , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemMllSS"         , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemMTmax"         , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSemFull"          , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTCRSSee"              , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeZeeVt"         , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeNbgeq1"        , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeMjjW"          , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeMET"           , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeMllSS"         , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSeeFull"          , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Same-sign Mjj off-W region
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemm"          , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmTVeto"     , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmNj2"       , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmNbgeq1"    , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmMjjW"      , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmMjjL"      , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmDetajjL"   , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmMET"       , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmMllSS"     , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSidemmFull"      , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTCRSSSideem"          , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemTVeto"     , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemNj2"       , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemNbgeq1"    , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemMjjW"      , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemMjjL"      , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemDetajjL"   , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemMET"       , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemMllSS"     , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemMTmax"     , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideemFull"      , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTCRSSSideee"          , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeZeeVt"     , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeTVeto"     , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeNj2"       , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeNbgeq1"    , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeMjjW"      , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeMjjL"      , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeDetajjL"   , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeMET"       , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeMllSS"     , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCRSSSideeeFull"      , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Trilep regions
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("BTCR0SFOS"             , [&]() { return (www.nSFOS()==0)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSNj1"          , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSNbgeq1"       , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSPt3l"         , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSMET"          , [&]() { return www.met_pt()>30.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSMll"          , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSZVt"          , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSMTmax"        , [&]() { return www.MTmax3L()>90.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR0SFOSFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("BTCR1SFOS"             , [&]() { return (www.nSFOS()==1)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSNj1"          , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSNbgeq1"       , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSPt3l"         , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSMET"          , [&]() { return www.met_pt()>40.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSMll"          , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSZVt"          , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSMT3rd"        , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR1SFOSFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("BTCR2SFOS"             , [&]() { return (www.nSFOS()==2)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSNj1"          , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSNbgeq1"       , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSPt3l"         , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSMET"          , [&]() { return www.met_pt()>55.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSMll"          , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSZVt"          , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTCR2SFOSFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

}

void addLowMETControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Low MET mjj side band
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LXECRSSmm"             , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmNj2"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmMjjW"         , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmMET"          , [&]() { return www.met_pt()<60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmMllSS"        , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSmmFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LXECRSSem"             , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemNj2"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemMjjW"         , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemMET"          , [&]() { return www.met_pt()<60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemMllSS"        , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSemFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LXECRSSee"             , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeZeeVt"        , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeNj2"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeMjjW"         , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeMET"          , [&]() { return www.met_pt()<60. and fabs(www.MllSS()-91.1876)>10.                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeMllSS"        , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXECRSSeeFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

}

void addBtaggedApplicationRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Btagged CR for Same-sign Mjj on-W region
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTARCRSSmm"            , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmNbgeq1"      , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmMjjW"        , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmMET"         , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSmmFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTARCRSSem"            , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemNbgeq1"      , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemMjjW"        , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemMllSS"       , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemMTmax"       , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSemFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTARCRSSee"            , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeZeeVt"       , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeNbgeq1"      , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeMjjW"        , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSeeFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // B-tagging CR application region
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemm"        , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmTVeto"   , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmNj2"     , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmNbgeq1"  , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmMjjW"    , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmMjjL"    , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmDetajjL" , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmMET"     , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmMllSS"   , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSidemmFull"    , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideem"        , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemTVeto"   , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemNj2"     , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemNbgeq1"  , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemMjjW"    , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemMjjL"    , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemDetajjL" , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemMET"     , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemMllSS"   , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemMTmax"   , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideemFull"    , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideee"        , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeZeeVt"   , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeTVeto"   , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeNj2"     , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeNbgeq1"  , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeMjjW"    , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeMjjL"    , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeDetajjL" , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeMET"     , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeMllSS"   , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCRSSSideeeFull"    , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Trilep regions
    cutflow.getCut("CutARTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOS"           , [&]() { return (www.nSFOS()==0)                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSNj1"        , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSNbgeq1"     , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSPt3l"       , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSDPhi3lMET"  , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSMET"        , [&]() { return www.met_pt()>30.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSMll"        , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSM3l"        , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSZVt"        , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSMTmax"      , [&]() { return www.MTmax3L()>90.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR0SFOSFull"       , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOS"           , [&]() { return (www.nSFOS()==1)                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSNj1"        , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSNbgeq1"     , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSPt3l"       , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSDPhi3lMET"  , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSMET"        , [&]() { return www.met_pt()>40.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSMll"        , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSM3l"        , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSZVt"        , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSMT3rd"      , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR1SFOSFull"       , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOS"           , [&]() { return (www.nSFOS()==2)                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSNj1"        , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSNbgeq1"     , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSPt3l"       , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSDPhi3lMET"  , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSMET"        , [&]() { return www.met_pt()>55.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSMll"        , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSM3l"        , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSZVt"        , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("BTARCR2SFOSFull"       , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

}

void addLowMETApplicationRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Low MET mjj side band
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmm"           , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmTVeto"      , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmNj2"        , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmNb0"        , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmMjjW"       , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmMET"        , [&]() { return www.met_pt()<60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmMllSS"      , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSmmFull"       , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LXEARCRSSem"           , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemTVeto"      , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemNj2"        , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemNb0"        , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemMjjW"       , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemMET"        , [&]() { return www.met_pt()<60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemMllSS"      , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSemFull"       , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("LXEARCRSSee"           , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeZeeVt"      , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeTVeto"      , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeNj2"        , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeNb0"        , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeMjjW"       , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeMET"        , [&]() { return www.met_pt()<60. and fabs(www.MllSS()-91.1876)>10.                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeMllSS"      , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("LXEARCRSSeeFull"       , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

}
