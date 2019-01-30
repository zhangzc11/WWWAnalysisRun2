#include "lostlepcontrolregioncuts.h"

void addLostLepControlRegionCuts(RooUtil::Cutflow& cutflow)
{
    // Same-sign WZ CR
    cutflow.getCut("CutWZCRDilep")                                                                                                            ;
    cutflow.addCutToLastActiveCut("WZCRSSmm"              , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return threelep_sf ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmMET"           , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmMllSS"         , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmFull"          , [&]() { return hasz_ss                                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutWZCRDilep")                                                                                                            ;
    cutflow.addCutToLastActiveCut("WZCRSSem"              , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return threelep_sf ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMET"           , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMllSS"         , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMTmax"         , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemFull"          , [&]() { return hasz_ss                                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutWZCRDilep")                                                                                                            ;
    cutflow.addCutToLastActiveCut("WZCRSSee"              , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return threelep_sf ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeZeeVt"         , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeMET"           , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeMllSS"         , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeFull"          , [&]() { return hasz_ss                                                            ; }        , [&]() { return 1                     ; } ) ;

    // Mjj selection validation region
    cutflow.getCut("WZCRSSeeMllSS");
    cutflow.addCutToLastActiveCut("WZVRSSee"    , [&]() { return hasz_ss;                 } ,  [&]() { return 1; } );
    cutflow.addCutToLastActiveCut("WZVRSSeeFull", [&]() { return fabs(www.Mjj()-80.)<15.; } ,  [&]() { return 1; } );
    cutflow.getCut("WZCRSSemMTmax");
    cutflow.addCutToLastActiveCut("WZVRSSem"    , [&]() { return hasz_ss;                 } ,  [&]() { return 1; } );
    cutflow.addCutToLastActiveCut("WZVRSSemFull", [&]() { return fabs(www.Mjj()-80.)<15.; } ,  [&]() { return 1; } );
    cutflow.getCut("WZCRSSmmMllSS");
    cutflow.addCutToLastActiveCut("WZVRSSmm"    , [&]() { return hasz_ss;                 } ,  [&]() { return 1; } );
    cutflow.addCutToLastActiveCut("WZVRSSmmFull", [&]() { return fabs(www.Mjj()-80.)<15.; } ,  [&]() { return 1; } );

    // Trilep WZ CR
    cutflow.getCut("CutWZCRTrilep")                                                                                                           ;
    cutflow.addCutToLastActiveCut("WZCR1SFOS"             , [&]() { return (www.nSFOS()==1)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSNj1"          , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSPt3l"         , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSMET"          , [&]() { return www.met_pt()>40.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSMll"          , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSMT3rd"        , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSZVt"          , [&]() { return hasz_3l                                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutWZCRTrilep")                                                                                                           ;
    cutflow.addCutToLastActiveCut("WZCR2SFOS"             , [&]() { return (www.nSFOS()==2)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSNj1"          , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSPt3l"         , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSMET"          , [&]() { return www.met_pt()>55.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSMll"          , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSZVt"          , [&]() { return hasz_3l                                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR2SFOSFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Invert met_pt
    cutflow.getCut("WZCR1SFOSNb0");
    cutflow.addCutToLastActiveCut("WZVR1SFOSMllOnOff"     , [&]() { return ((www.Pt3l()<60.)+(www.DPhi3lMET()<2.5)+(www.met_pt()<40.)+(www.MT3rd()<90.))*(www.Mll3L()>20.)*(abs(www.M3l()-91.1876)>10.) ; } , [&]() { return 1 ; } ) ;
    cutflow.addCutToLastActiveCut("WZVR1SFOSMllOnOffFull" , [&]() { return hasz_3l                                                                             ; } , [&]() { return 1 ; } ) ;
    cutflow.getCut("WZCR2SFOSNb0");
    cutflow.addCutToLastActiveCut("WZVR2SFOSMllOnOff"     , [&]() { return ((www.Pt3l()<60.)+(www.DPhi3lMET()<2.5)+(www.met_pt()<55.))*((www.Mll3L()>20.&&www.Mll3L1()>20.))*(abs(www.M3l()-91.1876)>10.) ; } , [&]() { return 1 ; } ) ;
    cutflow.addCutToLastActiveCut("WZVR2SFOSMllOnOffFull" , [&]() { return hasz_3l                                                                               ; } , [&]() { return 1 ; } ) ;
}
