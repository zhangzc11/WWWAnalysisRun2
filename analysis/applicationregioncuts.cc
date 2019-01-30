#include "applicationregioncuts.h"

void addApplicationRegionCuts(RooUtil::Cutflow& cutflow)
{

    // Same-sign Mjj on-W region
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("ARSSmm"                , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmMET"             , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSmmFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("ARSSem"                , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemMllSS"           , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemMTmax"           , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSemFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("ARSSee"                , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSeeFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Same-sign Mjj off-W region
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("ARSSSidemm"            , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmNb0"         , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSidemmFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("ARSSSideem"            , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemNb0"         , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemMllSS"       , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemMTmax"       , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideemFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("ARSSSideee"            , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeZeeVt"       , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeNb0"         , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("ARSSSideeeFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Trilep regions
    cutflow.getCut("CutARTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("AR0SFOS"               , [&]() { return (www.nSFOS()==0)                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSPt3l"           , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSMET"            , [&]() { return www.met_pt()>30.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSMll"            , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSZVt"            , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSMTmax"          , [&]() { return www.MTmax3L()>90.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR0SFOSFull"           , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("AR1SFOS"               , [&]() { return (www.nSFOS()==1)                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSMET"            , [&]() { return www.met_pt()>40.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSMll"            , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSMT3rd"          , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR1SFOSFull"           , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutARTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("AR2SFOS"               , [&]() { return (www.nSFOS()==2)                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSMET"            , [&]() { return www.met_pt()>55.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSMll"            , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("AR2SFOSFull"           , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

}
