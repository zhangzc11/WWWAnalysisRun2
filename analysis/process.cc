#include "process.h"

//_______________________________________________________________________________________________________
int process(const char* input_paths, const char* input_tree_name, const char* output_file_name, int nEvents, TString regions)
{
    // Creating output file where we will put the outputs of the processing
    TFile* ofile = new TFile(output_file_name, "recreate");

    // Create a TChain of the input files
    // The input files can be comma separated (e.g. "file1.root,file2.root")
    TChain* ch = RooUtil::FileUtil::createTChain(input_tree_name, input_paths);

    // Create a Looper object to loop over input files
    RooUtil::Looper<wwwtree> looper(ch, &www, nEvents);

    // Some case-by-case checking needed for WWW_v1.2.2 (should be no longer necessary later on)
    bool is2017 = TString(input_paths).Contains("2017");
    bool isWWW = TString(input_paths).Contains("www_2l_");

    // For fake estimations, we use data-driven method.
    // When looping over data and the output_path is set to have a "fakes" substring included we turn on the fake-weight settings
//    const bool doSystematics = not TString(input_paths).Contains("data_");
    const bool doSystematics = false;
    bool doFakeEstimation = TString(output_file_name).Contains("ddfakes") or TString(output_file_name).Contains("ewksubt");
    bool doEwkSubtraction = TString(output_file_name).Contains("ewksubt");
    bool isData = TString(input_paths).Contains("data_") || TString(input_paths).Contains("Run2017");

    std::cout <<  " Printing configuration " << std::endl;
    std::cout <<  " is2017: " << is2017 <<  std::endl;
    std::cout <<  " isWWW: " << isWWW <<  std::endl;
    std::cout <<  " doSystematics: " << doSystematics <<  std::endl;
    std::cout <<  " doFakeEstimation: " << doFakeEstimation <<  std::endl;
    std::cout <<  " doEwkSubtraction: " << doEwkSubtraction <<  std::endl;
    std::cout <<  " isData: " << isData <<  std::endl;
    std::cout <<  " input_paths: " << input_paths <<  std::endl;
    std::cout <<  " output_file_name: " << output_file_name <<  std::endl;

    // Scale factors tools
    LeptonScaleFactors leptonScaleFactors;
    FakeRates fakerates;
    TheoryWeight theoryweight;
    PileupReweight pileupreweight;

    // Luminosity setting
    float lumi = isData ? 1 : (is2017 == 1 ? 41.3 : 35.9);

    // Cutflow utility object that creates a tree structure of cuts
    RooUtil::Cutflow cutflow(ofile);

    // Histogram utility object that is used to define the histograms
    RooUtil::Histograms histograms;
    histograms.addHistogram("MllSS"                ,  180 , 0.      , 300.   , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllSS_wide"           ,  180 , 0.      , 2000.  , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllZ"                 ,  180 , 60.     , 120.   , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllZZoom"             ,  180 , 80.     , 100.   , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("Mll3L"                ,  180 , 0.      , 300.   , [&]() { return www.Mll3L()                  ; });
    histograms.addHistogram("Mll3L1"               ,  180 , 0.      , 300.   , [&]() { return www.Mll3L1()                 ; });
    histograms.addHistogram("nSFOSinZ"             ,  3   , 0.      , 3.     , [&]() { return www.nSFOSinZ()               ; });
    histograms.addHistogram("M3l"                  ,  180 , 0.      , 150.   , [&]() { return www.M3l()                    ; });
    histograms.addHistogram("Pt3lGCR"              ,  180 , 0.      , 100.   , [&]() { return www.Pt3l()                   ; });
    histograms.addHistogram("Pt3l"                 ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                   ; });
    histograms.addHistogram("Ptll"                 ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                   ; });
    histograms.addHistogram("nvtx"                 ,  60  , 0.      , 60.    , [&]() { return www.nVert()                  ; });
    histograms.addHistogram("Mjj"                  ,  180 , 0.      , 300.   , [&]() { return www.Mjj()                    ; });
    histograms.addHistogram("MjjL"                 ,  180 , 0.      , 750.   , [&]() { return www.MjjL()                   ; });
    histograms.addHistogram("DetajjL"              ,  180 , 0.      , 5.     , [&]() { return www.DetajjL()                ; });
    histograms.addHistogram("MjjVBF"               ,  180 , 0.      , 750.   , [&]() { return www.MjjVBF()                 ; });
    histograms.addHistogram("DetajjVBF"            ,  180 , 0.      , 8.     , [&]() { return www.DetajjVBF()              ; });
    histograms.addHistogram("MET"                  ,  180 , 0.      , 180.   , [&]() { return www.met_pt()                 ; });
    histograms.addHistogram("lep_pt0"              ,  180 , 0.      , 250    , [&]() { return www.lep_pt()[0]              ; });
    histograms.addHistogram("lep_pt1"              ,  180 , 0.      , 150    , [&]() { return www.lep_pt()[1]              ; });
    histograms.addHistogram("lep_pt2"              ,  180 , 0.      , 150    , [&]() { return www.lep_pt()[2]              ; });
    histograms.addHistogram("lep_eta0"             ,  180 , -2.5    , 2.5    , [&]() { return www.lep_eta()[0]             ; });
    histograms.addHistogram("lep_eta1"             ,  180 , -2.5    , 2.5    , [&]() { return www.lep_eta()[1]             ; });
    histograms.addHistogram("lep_phi0"             ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_phi()[0]             ; });
    histograms.addHistogram("lep_phi1"             ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_phi()[1]             ; });
    histograms.addHistogram("lep_relIso03EAv2Lep0" ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[0] ; });
    histograms.addHistogram("lep_relIso03EAv2Lep1" ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[1] ; });
    histograms.addHistogram("lep_relIso03EAv2Lep2" ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[2] ; });
    histograms.addHistogram("nj"                   ,  7   , 0.      , 7.     , [&]() { return www.nj()                     ; });
    histograms.addHistogram("nj30"                 ,  7   , 0.      , 7.     , [&]() { return www.nj30()                   ; });
    histograms.addHistogram("nb"                   ,  5   , 0.      , 5.     , [&]() { return www.nb()                     ; });
    histograms.addHistogram("MTmin"                ,  180 , 0.      , 300.   , [&]() { return www.MTmin()                  ; });
    histograms.addHistogram("MTmax"                ,  180 , 0.      , 300.   , [&]() { return www.MTmax()                  ; });
    histograms.addHistogram("MTmax3L"              ,  180 , 0.      , 300.   , [&]() { return www.MTmax3L()                ; });
    histograms.addHistogram("MT3rd"                ,  180 , 0.      , 300.   , [&]() { return www.MT3rd()                  ; });

    // Fake rate estimation histogram
    const std::vector<float> eta_bounds = {0.0, 1.6, 2.4};
    const std::vector<float> ptcorrcoarse_bounds = {0., 20., 25., 30., 35., 150.};
    histograms.addHistogram("ptcorretarolledcoarse" , 2 * (eta_bounds.size()-1) * (ptcorrcoarse_bounds.size()-1)  , 0  , 2 * (eta_bounds.size()-1) * (ptcorrcoarse_bounds.size()-1),
        [&]() {
            int index = fakerates.getFakeLepIndex();
            float ptcorr = index >= 0 ? fakerates.getPtCorr() : -999;
            float abseta = index >= 0 ? fabs(www.lep_eta()[index]) : -999;
            int ibin = RooUtil::Calc::calcBin2D(ptcorrcoarse_bounds, eta_bounds, ptcorr, abseta);
            const int nbin = (eta_bounds.size()-1) * (ptcorrcoarse_bounds.size()-1);
            return ibin + nbin * (abs(www.lep_pdgId()[index]) == 11 ? 1 : 0);
        }
    );

    // variables
    float ffwgt;
    bool presel;
    bool trigger;
    float weight;
    bool isdilep;
    bool istrilep;
    bool isfakedilep;
    bool isfaketrilep;
    bool iswzcrtrilep;
    bool isfakewzcrtrilep;
    bool osdileppresel;
    float ee_sf, em_sf, mm_sf, threelep_sf;
    float btag_sf;
    float trig_sf;
    bool hasz_ss, hasz_3l;

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
    cutflow.addCutToLastActiveCut("CutWZCRTrilep" , [&]() { return doFakeEstimation ? isfaketrilep : istrilep                   ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutARDilep"    , [&]() { return isfakedilep                                                  ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutTrigger");
    cutflow.addCutToLastActiveCut("CutARTrilep"   , [&]() { return isfaketrilep                                                 ; } , [&]() { return 1                                  ; } );
    cutflow.getCut("CutPresel");
    cutflow.addCutToLastActiveCut("CutOSDilep"    , [&]() { return osdileppresel                                                ; } , [&]() { return 1                                  ; } );

    // Same-sign Mjj on-W region
    cutflow.getCut("CutSRDilep");
    cutflow.addCutToLastActiveCut("SRSSmm"                , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmMET"             , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSmmFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("SRSSem"                , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemMllSS"           , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemMTmax"           , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSemFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("SRSSee"                , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeNj2"             , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeNb0"             , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeMET"             , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSeeFull"            , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Same-sign Mjj off-W region
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("SRSSSidemm"            , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmNb0"         , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSidemmFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("SRSSSideem"            , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemNb0"         , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemMllSS"       , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemMTmax"       , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideemFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("SRSSSideee"            , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeZeeVt"       , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeNj2"         , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeNb0"         , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeMET"         , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SRSSSideeeFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Trilep regions
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("SR0SFOS"               , [&]() { return (www.nSFOS()==0)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSPt3l"           , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSMET"            , [&]() { return www.met_pt()>30.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSMll"            , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSZVt"            , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSMTmax"          , [&]() { return www.MTmax3L()>90.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR0SFOSFull"           , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("SR1SFOS"               , [&]() { return (www.nSFOS()==1)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSMET"            , [&]() { return www.met_pt()>40.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSMll"            , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSMT3rd"          , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR1SFOSFull"           , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("SR2SFOS"               , [&]() { return (www.nSFOS()==2)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSMET"            , [&]() { return www.met_pt()>55.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSMll"            , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("SR2SFOSFull"           , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // Same-sign WZ CR
    cutflow.getCut("CutWZCRDilep")                                                                                                            ;
    cutflow.addCutToLastActiveCut("WZCRSSmm"              , [&]() { return (hasz_ss)*(www.passSSmm())*(www.MllSS()>40.)                       ; }        , [&]() { return threelep_sf ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmMET"           , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmMllSS"         , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSmmFull"          , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutWZCRDilep")                                                                                                            ;
    cutflow.addCutToLastActiveCut("WZCRSSem"              , [&]() { return (hasz_ss)*(www.passSSem())*(www.MllSS()>30.)                       ; }        , [&]() { return threelep_sf ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMET"           , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMllSS"         , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemMTmax"         , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSemFull"          , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutWZCRDilep")                                                                                                            ;
    cutflow.addCutToLastActiveCut("WZCRSSee"              , [&]() { return (hasz_ss)*(www.passSSee())*(1)*(www.MllSS()>40.)                   ; }        , [&]() { return threelep_sf ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeZeeVt"         , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeNj2"           , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeNb0"           , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeMjjL"          , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeDetajjL"       , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeMET"           , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeMllSS"         , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCRSSeeFull"          , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

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
    cutflow.addCutToLastActiveCut("WZCR1SFOSZVt"          , [&]() { return hasz_3l                                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("WZCR1SFOSMT3rd"        , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
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

    // VBS control region
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("VBSCRSSmm"             , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSmmTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSmmNj2"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSmmNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSmmVBF"          , [&]() { return www.MjjL() > 400 or www.DetajjL() > 1.5                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSmmFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("VBSCRSSem"             , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSemTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSemNj2"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSemNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSemVBF"          , [&]() { return www.MjjL() > 400 or www.DetajjL() > 1.5                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSemFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("VBSCRSSee"             , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSeeZeeVt"        , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSeeTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSeeNj2"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSeeNb0"          , [&]() { return www.nb()==0                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSeeVBF"          , [&]() { return www.MjjL() > 400 or www.DetajjL() > 1.5                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("VBSCRSSeeFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // ttW control region mjj window
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("TTWCRSSmm"             , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmNj4"          , [&]() { return www.nj30()>= 2                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmNbgeq1"       , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmMjjW"         , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmMjjL"         , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmDetajjL"      , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmMET"          , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmMllSS"        , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSmmFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("TTWCRSSem"             , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemNj4"          , [&]() { return www.nj30()>= 4                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemNbgeq1"       , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemMjjW"         , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemMjjL"         , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemDetajjL"      , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemMET"          , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemMllSS"        , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemMTmax"        , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSemFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("TTWCRSSee"             , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeZeeVt"        , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeTVeto"        , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeNj4"          , [&]() { return www.nj30()>= 4                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeNbgeq1"       , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeMjjW"         , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeMjjL"         , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeDetajjL"      , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeMET"          , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeMllSS"        , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSeeFull"         , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // ttW control region mjj sideband
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemm"         , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }        , [&]() { return mm_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmTVeto"    , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmNj4"      , [&]() { return www.nj30()>= 4                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmNbgeq1"   , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmMjjW"     , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmMjjL"     , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmDetajjL"  , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmMET"      , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmMllSS"    , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSidemmFull"     , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideem"         , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }        , [&]() { return em_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemTVeto"    , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemNj4"      , [&]() { return www.nj30()>= 4                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemNbgeq1"   , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemMjjW"     , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemMjjL"     , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemDetajjL"  , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemMET"      , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemMllSS"    , [&]() { return www.MllSS()>30.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemMTmax"    , [&]() { return www.MTmax()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideemFull"     , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRDilep")                                                                                                              ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideee"         , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }        , [&]() { return ee_sf                 ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeZeeVt"    , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeTVeto"    , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeNj4"      , [&]() { return www.nj30()>= 4                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeNbgeq1"   , [&]() { return www.nb()>=1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeMjjW"     , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeMjjL"     , [&]() { return www.MjjL()<400.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeDetajjL"  , [&]() { return www.DetajjL()<1.5                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeMET"      , [&]() { return www.met_pt()>60.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeMllSS"    , [&]() { return www.MllSS()>40.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTWCRSSSideeeFull"     , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

    // TTZ control region
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOS"            , [&]() { return (www.nSFOS()==0)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSNj2"         , [&]() { return www.nj()<=2                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSNb1"         , [&]() { return www.nb()==1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSPt3l"        , [&]() { return 1.                                                                 ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSDPhi3lMET"   , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSMET"         , [&]() { return www.met_pt()>30.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSMll"         , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSM3l"         , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSZVt"         , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSMTmax"       , [&]() { return www.MTmax3L()>90.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR0SFOSFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOS"            , [&]() { return (www.nSFOS()==1)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSNj2"         , [&]() { return www.nj()<=2                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSNb1"         , [&]() { return www.nb()==1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSPt3l"        , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSDPhi3lMET"   , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSMET"         , [&]() { return www.met_pt()>40.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSMll"         , [&]() { return www.Mll3L() > 20.                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSM3l"         , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSZVt"         , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSMT3rd"       , [&]() { return www.MT3rd()>90.                                                    ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR1SFOSFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOS"            , [&]() { return (www.nSFOS()==2)                                                   ; }        , [&]() { return threelep_sf           ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSNj2"         , [&]() { return www.nj()<=2                                                        ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSNb1"         , [&]() { return www.nb()==1                                                        ; }        , [&]() { return btag_sf               ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSPt3l"        , [&]() { return www.Pt3l()>60.                                                     ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSDPhi3lMET"   , [&]() { return www.DPhi3lMET()>2.5                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSMET"         , [&]() { return www.met_pt()>55.                                                   ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSMll"         , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSM3l"         , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSZVt"         , [&]() { return www.nSFOSinZ() == 0                                                ; }        , [&]() { return 1                     ; } ) ;
    cutflow.addCutToLastActiveCut("TTZCR2SFOSFull"        , [&]() { return 1                                                                  ; }        , [&]() { return 1                     ; } ) ;

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

    // Gamma control region
    cutflow.getCut("CutSRTrilep")                                                                                                             ;
    cutflow.addCutToLastActiveCut("GCR0SFOS"              , [&]() { return (www.nSFOSinZ()==0)*(www.met_pt()<30)*(fabs(www.M3l()-91.1876)<20) ; } , [&]() { return threelep_sf                  ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSNj1"           , [&]() { return www.nj()<=1                                                        ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSNb0"           , [&]() { return www.nb()==0                                                        ; } , [&]() { return btag_sf                      ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSPt3l"          , [&]() { return 1.                                                                 ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSDPhi3lMET"     , [&]() { return www.DPhi3lMET()>2.5                                                ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSMET"           , [&]() { return www.met_pt()>30.                                                   ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSMll"           , [&]() { return www.Mll3L() > 20.                                                  ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSM3l"           , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSZVt"           , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSMTmax"         , [&]() { return www.MTmax3L()>90.                                                  ; } , [&]() { return 1                            ; } ) ;
    cutflow.addCutToLastActiveCut("GCR0SFOSFull"          , [&]() { return 1                                                                  ; } , [&]() { return 1                            ; } ) ;

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

    // Systematics
    if (doSystematics)
    {
        // Declare cut varying systematics to cuts with the patterns provided in the vector
        cutflow.addCutSyst("JESUp"  , {"jj", "MET", "Nj", "Nb", "VBF"});
        cutflow.addCutSyst("JESDown", {"jj", "MET", "Nj", "Nb", "VBF"});

        cutflow.addWgtSyst("LepSFUp"    , [&]() { return www.lepsf()           == 0                              ? 0 : www.lepsf_up()               / www.lepsf()                                                          ; } );
        cutflow.addWgtSyst("LepSFDown"  , [&]() { return www.lepsf()           == 0                              ? 0 : www.lepsf_dn()               / www.lepsf()                                                          ; } );
        cutflow.addWgtSyst("TrigSFUp"   , [&]() { return www.trigsf()          == 0                              ? 0 : www.trigsf_up()              / www.trigsf()                                                         ; } );
        cutflow.addWgtSyst("TrigSFDown" , [&]() { return www.trigsf()          == 0                              ? 0 : www.trigsf_dn()              / www.trigsf()                                                         ; } );
        cutflow.addWgtSyst("BTagLFUp"   , [&]() { return www.weight_btagsf()   == 0                              ? 0 : www.weight_btagsf_light_DN() / www.weight_btagsf()                                                  ; } );
        cutflow.addWgtSyst("BTagLFDown" , [&]() { return www.weight_btagsf()   == 0                              ? 0 : www.weight_btagsf_light_UP() / www.weight_btagsf()                                                  ; } );
        cutflow.addWgtSyst("BTagHFUp"   , [&]() { return www.weight_btagsf()   == 0                              ? 0 : www.weight_btagsf_heavy_DN() / www.weight_btagsf()                                                  ; } );
        cutflow.addWgtSyst("BTagHFDown" , [&]() { return www.weight_btagsf()   == 0                              ? 0 : www.weight_btagsf_heavy_UP() / www.weight_btagsf()                                                  ; } );
        cutflow.addWgtSyst("PileupUp"   , [&]() { return www.purewgt()         == 0                              ? 0 : www.purewgt_dn()             / www.purewgt()                                                        ; } );
        cutflow.addWgtSyst("PileupDown" , [&]() { return www.purewgt()         == 0                              ? 0 : www.purewgt_up()             / www.purewgt()                                                        ; } );
        cutflow.addWgtSyst("PDFUp"      , [&]() { return www.weight_fr_r1_f1() == 0 or theoryweight.pdfup() == 0 ? 0 : www.weight_pdf_up()          / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.pdfup(); } );
        cutflow.addWgtSyst("PDFDown"    , [&]() { return www.weight_fr_r1_f1() == 0 or theoryweight.pdfdn() == 0 ? 0 : www.weight_pdf_down()        / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.pdfdn(); } );
        cutflow.addWgtSyst("QsqUp"      , [&]() { return www.weight_fr_r1_f1() == 0 or theoryweight.qsqup() == 0 ? 0 : www.weight_fr_r2_f2()        / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.qsqup(); } );
        cutflow.addWgtSyst("QsqDown"    , [&]() { return www.weight_fr_r1_f1() == 0 or theoryweight.qsqdn() == 0 ? 0 : www.weight_fr_r0p5_f0p5()    / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.qsqdn(); } );
        cutflow.addWgtSyst("AlphaSUp"   , [&]() { return www.weight_fr_r1_f1() == 0 or theoryweight.alsup() == 0 ? 0 : www.weight_alphas_up()       / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.alsup(); } );
        cutflow.addWgtSyst("AlphaSDown" , [&]() { return www.weight_fr_r1_f1() == 0 or theoryweight.alsdn() == 0 ? 0 : www.weight_alphas_down()     / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.alsdn(); } );

        if (doFakeEstimation)
        {
            if (!is2017)
            {
                cutflow.addWgtSyst("FakeUp"            , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_full_up()       / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeDown"          , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_full_dn()       / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeRateUp"        , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_up()            / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeRateDown"      , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_dn()            / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeRateElUp"      , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_el_up()         / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeRateElDown"    , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_el_dn()         / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeRateMuUp"      , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_up()         / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeRateMuDown"    , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_dn()         / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureUp"     , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_up()    / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureDown"   , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_dn()    / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureElUp"   , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_up() / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureElDown" , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_dn() / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureMuUp"   , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_up() / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureMuDown" , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_dn() / www.ffwgt(); } );
                cutflow.addWgtSyst("FakeClosureMuDown" , [&]() { return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_dn() / www.ffwgt(); } );
            }
            else
            {
                // TODO
                cutflow.addWgtSyst("FakeUp"            , UNITY );
                cutflow.addWgtSyst("FakeDown"          , UNITY );
                cutflow.addWgtSyst("FakeRateUp"        , UNITY );
                cutflow.addWgtSyst("FakeRateDown"      , UNITY );
                cutflow.addWgtSyst("FakeRateElUp"      , UNITY );
                cutflow.addWgtSyst("FakeRateElDown"    , UNITY );
                cutflow.addWgtSyst("FakeRateMuUp"      , UNITY );
                cutflow.addWgtSyst("FakeRateMuDown"    , UNITY );
                cutflow.addWgtSyst("FakeClosureUp"     , UNITY );
                cutflow.addWgtSyst("FakeClosureDown"   , UNITY );
                cutflow.addWgtSyst("FakeClosureElUp"   , UNITY );
                cutflow.addWgtSyst("FakeClosureElDown" , UNITY );
                cutflow.addWgtSyst("FakeClosureMuUp"   , UNITY );
                cutflow.addWgtSyst("FakeClosureMuDown" , UNITY );
                cutflow.addWgtSyst("FakeClosureMuDown" , UNITY );
            }
        }
    }

    // Systematic variations
    if (doSystematics)
    {

        // Systematics that affect the raw number of events
        cutflow.setCutSyst("SRSSmmMET"                      , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSmmMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSmmMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSmmDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemMET"                      , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeMET"                      , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR0SFOSDPhi3lMET"               , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR0SFOSMET"                     , "JESUp"   , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR1SFOSDPhi3lMET"               , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR1SFOSMET"                     , "JESUp"   , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR2SFOSDPhi3lMET"               , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR2SFOSMET"                     , "JESUp"   , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmMET"                    , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmMjjL"                   , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmDetajjL"                , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemMjjL"                   , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemDetajjL"                , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemMET"                    , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeMjjL"                   , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeDetajjL"                , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeMET"                    , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR1SFOSDPhi3lMET"             , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR1SFOSMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR2SFOSDPhi3lMET"             , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR2SFOSMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmMET"                      , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemMET"                      , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeMET"                      , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR0SFOSDPhi3lMET"               , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR0SFOSMET"                     , "JESUp"   , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR1SFOSDPhi3lMET"               , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR1SFOSMET"                     , "JESUp"   , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR2SFOSDPhi3lMET"               , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR2SFOSMET"                     , "JESUp"   , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmMjjW"                   , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmMjjL"                   , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmDetajjL"                , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemMjjW"                   , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemMjjL"                   , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemDetajjL"                , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeMjjW"                   , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeMjjL"                   , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeDetajjL"                , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmMjjW"               , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmMjjL"               , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmDetajjL"            , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemMjjW"               , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemMjjL"               , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemDetajjL"            , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeMjjW"               , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeMjjL"               , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeDetajjL"            , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSmmVBF"                   , "JESUp"   , [&]() { return www.MjjL_up() > 400 or www.DetajjL_up() > 1.5         ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSemVBF"                   , "JESUp"   , [&]() { return www.MjjL_up() > 400 or www.DetajjL_up() > 1.5         ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSeeVBF"                   , "JESUp"   , [&]() { return www.MjjL_up() > 400 or www.DetajjL_up() > 1.5         ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmMjjW"                  , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmMjjL"                  , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmDetajjL"               , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemMjjW"                  , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemMjjL"                  , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemDetajjL"               , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeMjjW"                  , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeMjjL"                  , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeDetajjL"               , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmMjjW"              , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmMjjL"              , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmDetajjL"           , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemMjjW"              , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemMjjL"              , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemDetajjL"           , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeMjjW"              , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeMjjL"              , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeDetajjL"           , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSmmMjjW"                  , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSemMjjW"                  , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSeeMjjW"                  , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmMET"                    , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemMET"                    , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeMET"                    , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmMET"                , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemMET"                , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeMET"                , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR0SFOSDPhi3lMET"             , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR0SFOSMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR1SFOSDPhi3lMET"             , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR1SFOSMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR2SFOSDPhi3lMET"             , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR2SFOSMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmMET"                   , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeMET"                   , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmMET"               , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemMET"               , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeMET"               , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR0SFOSDPhi3lMET"            , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR0SFOSMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR1SFOSDPhi3lMET"            , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR1SFOSMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR2SFOSDPhi3lMET"            , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR2SFOSMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSmmMET"                   , "JESUp"   , [&]() { return www.met_up_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSemMET"                   , "JESUp"   , [&]() { return www.met_up_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSeeMET"                   , "JESUp"   , [&]() { return www.met_up_pt()<60. and fabs(www.MllSS()-91.1876)>10. ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("GCR0SFOSDPhi3lMET"              , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("GCR0SFOSMET"                    , "JESUp"   , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmMET"                  , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeMjjW"                 , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeMjjL"                 , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeDetajjL"              , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeMET"                  , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmMjjW"             , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmMjjL"             , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmDetajjL"          , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmMET"              , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemMjjW"             , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemMjjL"             , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemDetajjL"          , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemMET"              , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeMjjW"             , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeMjjL"             , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeDetajjL"          , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeMET"              , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR0SFOSDPhi3lMET"           , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR0SFOSMET"                 , "JESUp"   , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR1SFOSDPhi3lMET"           , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR1SFOSMET"                 , "JESUp"   , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR2SFOSDPhi3lMET"           , "JESUp"   , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR2SFOSMET"                 , "JESUp"   , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSmmMjjW"                , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSemMjjW"                , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSeeMjjW"                , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSmmMET"                 , "JESUp"   , [&]() { return www.met_up_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSemMET"                 , "JESUp"   , [&]() { return www.met_up_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSeeMET"                 , "JESUp"   , [&]() { return www.met_up_pt()<60. and fabs(www.MllSS()-91.1876)>10. ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmMET"                      , "JESUp"   , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemMET"                      , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeMjjW"                     , "JESUp"   , [&]() { return fabs(www.Mjj_up()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeMjjL"                     , "JESUp"   , [&]() { return www.MjjL_up()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeDetajjL"                  , "JESUp"   , [&]() { return www.DetajjL_up()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeMET"                      , "JESUp"   , [&]() { return www.met_up_pt()>60.                                   ;} , [&]() { return 1 ;} );

        cutflow.setCutSyst("SRSSmmMET"                      , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSmmMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSmmMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSmmDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemMET"                      , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeMET"                      , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR0SFOSDPhi3lMET"               , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR0SFOSMET"                     , "JESDown" , [&]() { return www.met_dn_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR1SFOSDPhi3lMET"               , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR1SFOSMET"                     , "JESDown" , [&]() { return www.met_dn_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR2SFOSDPhi3lMET"               , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR2SFOSMET"                     , "JESDown" , [&]() { return www.met_dn_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmMET"                    , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmMjjL"                   , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmDetajjL"                , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemMjjL"                   , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemDetajjL"                , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemMET"                    , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeMjjL"                   , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeDetajjL"                , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeMET"                    , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR1SFOSDPhi3lMET"             , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR1SFOSMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR2SFOSDPhi3lMET"             , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR2SFOSMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmMET"                      , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemMET"                      , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeMET"                      , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR0SFOSDPhi3lMET"               , "JESDown" , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR0SFOSMET"                     , "JESDown" , [&]() { return www.met_up_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR1SFOSDPhi3lMET"               , "JESDown" , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR1SFOSMET"                     , "JESDown" , [&]() { return www.met_up_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR2SFOSDPhi3lMET"               , "JESDown" , [&]() { return www.DPhi3lMET_up()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR2SFOSMET"                     , "JESDown" , [&]() { return www.met_up_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmMjjW"                   , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmMjjL"                   , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmDetajjL"                , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemMjjW"                   , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemMjjL"                   , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemDetajjL"                , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeMjjW"                   , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeMjjL"                   , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeDetajjL"                , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmMjjW"               , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmMjjL"               , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmDetajjL"            , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemMjjW"               , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemMjjL"               , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemDetajjL"            , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeMjjW"               , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeMjjL"               , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeDetajjL"            , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSmmVBF"                   , "JESDown" , [&]() { return www.MjjL_dn() > 400 or www.DetajjL_dn() > 1.5         ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSemVBF"                   , "JESDown" , [&]() { return www.MjjL_dn() > 400 or www.DetajjL_dn() > 1.5         ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSeeVBF"                   , "JESDown" , [&]() { return www.MjjL_dn() > 400 or www.DetajjL_dn() > 1.5         ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmMjjW"                  , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmMjjL"                  , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmDetajjL"               , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemMjjW"                  , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemMjjL"                  , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemDetajjL"               , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeMjjW"                  , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeMjjL"                  , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeDetajjL"               , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmMjjW"              , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmMjjL"              , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmDetajjL"           , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemMjjW"              , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemMjjL"              , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemDetajjL"           , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeMjjW"              , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeMjjL"              , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeDetajjL"           , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSmmMjjW"                  , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSemMjjW"                  , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSeeMjjW"                  , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmMET"                    , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemMET"                    , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeMET"                    , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmMET"                , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemMET"                , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeMET"                , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR0SFOSDPhi3lMET"             , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR0SFOSMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR1SFOSDPhi3lMET"             , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR1SFOSMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR2SFOSDPhi3lMET"             , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR2SFOSMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmMET"                   , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeMET"                   , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmMET"               , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemMET"               , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeMET"               , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR0SFOSDPhi3lMET"            , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR0SFOSMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR1SFOSDPhi3lMET"            , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR1SFOSMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR2SFOSDPhi3lMET"            , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR2SFOSMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSmmMET"                   , "JESDown" , [&]() { return www.met_dn_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSemMET"                   , "JESDown" , [&]() { return www.met_dn_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSeeMET"                   , "JESDown" , [&]() { return www.met_dn_pt()<60. and fabs(www.MllSS()-91.1876)>10. ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("GCR0SFOSDPhi3lMET"              , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("GCR0SFOSMET"                    , "JESDown" , [&]() { return www.met_dn_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmMET"                  , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeMjjW"                 , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeMjjL"                 , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeDetajjL"              , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeMET"                  , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmMjjW"             , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmMjjL"             , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmDetajjL"          , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmMET"              , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemMjjW"             , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemMjjL"             , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemDetajjL"          , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemMET"              , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeMjjW"             , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeMjjL"             , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeDetajjL"          , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeMET"              , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR0SFOSDPhi3lMET"           , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR0SFOSMET"                 , "JESDown" , [&]() { return www.met_dn_pt()>30.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR1SFOSDPhi3lMET"           , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR1SFOSMET"                 , "JESDown" , [&]() { return www.met_dn_pt()>40.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR2SFOSDPhi3lMET"           , "JESDown" , [&]() { return www.DPhi3lMET_dn()>2.5                                ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR2SFOSMET"                 , "JESDown" , [&]() { return www.met_dn_pt()>55.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSmmMjjW"                , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSemMjjW"                , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSeeMjjW"                , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)>=15.                           ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSmmMET"                 , "JESDown" , [&]() { return www.met_dn_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSemMET"                 , "JESDown" , [&]() { return www.met_dn_pt()<60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSeeMET"                 , "JESDown" , [&]() { return www.met_dn_pt()<60. and fabs(www.MllSS()-91.1876)>10. ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmMET"                      , "JESDown" , [&]() { return 1.                                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemMET"                      , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeMjjW"                     , "JESDown" , [&]() { return fabs(www.Mjj_dn()-80.)<15.                            ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeMjjL"                     , "JESDown" , [&]() { return www.MjjL_dn()<400.                                    ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeDetajjL"                  , "JESDown" , [&]() { return www.DetajjL_dn()<1.5                                  ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeMET"                      , "JESDown" , [&]() { return www.met_dn_pt()>60.                                   ;} , [&]() { return 1 ;} );

        cutflow.setCutSyst("SRSSmmNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR0SFOSNj1"                     , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR1SFOSNj1"                     , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR2SFOSNj1"                     , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmNj2"                    , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemNj2"                    , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeNj2"                    , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR1SFOSNj1"                   , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR2SFOSNj1"                   , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR0SFOSNj1"                     , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR1SFOSNj1"                     , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR2SFOSNj1"                     , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmNj2"                    , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemNj2"                    , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeNj2"                    , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmNj2"                , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemNj2"                , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeNj2"                , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR0SFOSNj1"                   , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR1SFOSNj1"                   , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR2SFOSNj1"                   , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSmmNj2"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSemNj2"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSeeNj2"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmNj4"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemNj4"                   , "JESUp"   , [&]() { return www.nj30_up()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeNj4"                   , "JESUp"   , [&]() { return www.nj30_up()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmNj4"               , "JESUp"   , [&]() { return www.nj30_up()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemNj4"               , "JESUp"   , [&]() { return www.nj30_up()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeNj4"               , "JESUp"   , [&]() { return www.nj30_up()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR0SFOSNj2"                  , "JESUp"   , [&]() { return www.nj_up()<=2                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR1SFOSNj2"                  , "JESUp"   , [&]() { return www.nj_up()<=2                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR2SFOSNj2"                  , "JESUp"   , [&]() { return www.nj_up()<=2                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSmmNj2"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSemNj2"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSeeNj2"                   , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("GCR0SFOSNj1"                    , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeNj2"                  , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmNj2"              , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemNj2"              , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeNj2"              , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR0SFOSNj1"                 , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR1SFOSNj1"                 , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR2SFOSNj1"                 , "JESUp"   , [&]() { return www.nj_up()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSmmNj2"                 , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSemNj2"                 , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSeeNj2"                 , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeNj2"                      , "JESUp"   , [&]() { return www.nj30_up()>= 2                                     ;} , [&]() { return 1 ;} );

        cutflow.setCutSyst("SRSSmmNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSemNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSeeNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSidemmNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideemNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SRSSSideeeNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR0SFOSNj1"                     , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR1SFOSNj1"                     , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("SR2SFOSNj1"                     , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSmmNj2"                    , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSemNj2"                    , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCRSSeeNj2"                    , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR1SFOSNj1"                   , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("WZCR2SFOSNj1"                   , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSmmNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSemNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSeeNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSidemmNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideemNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("ARSSSideeeNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR0SFOSNj1"                     , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR1SFOSNj1"                     , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("AR2SFOSNj1"                     , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSmmNj2"                    , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSemNj2"                    , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSeeNj2"                    , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSidemmNj2"                , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideemNj2"                , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCRSSSideeeNj2"                , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR0SFOSNj1"                   , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR1SFOSNj1"                   , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTCR2SFOSNj1"                   , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSmmNj2"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSemNj2"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("VBSCRSSeeNj2"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSmmNj4"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSemNj4"                   , "JESDown" , [&]() { return www.nj30_dn()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSeeNj4"                   , "JESDown" , [&]() { return www.nj30_dn()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSidemmNj4"               , "JESDown" , [&]() { return www.nj30_dn()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideemNj4"               , "JESDown" , [&]() { return www.nj30_dn()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTWCRSSSideeeNj4"               , "JESDown" , [&]() { return www.nj30_dn()>= 4                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR0SFOSNj2"                  , "JESDown" , [&]() { return www.nj_dn()<=2                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR1SFOSNj2"                  , "JESDown" , [&]() { return www.nj_dn()<=2                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("TTZCR2SFOSNj2"                  , "JESDown" , [&]() { return www.nj_dn()<=2                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSmmNj2"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSemNj2"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXECRSSeeNj2"                   , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("GCR0SFOSNj1"                    , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSmmNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSemNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSeeNj2"                  , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSidemmNj2"              , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideemNj2"              , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCRSSSideeeNj2"              , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR0SFOSNj1"                 , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR1SFOSNj1"                 , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("BTARCR2SFOSNj1"                 , "JESDown" , [&]() { return www.nj_dn()<=1                                        ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSmmNj2"                 , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSemNj2"                 , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("LXEARCRSSeeNj2"                 , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRmmNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCRemNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );
        cutflow.setCutSyst("OSCReeNj2"                      , "JESDown" , [&]() { return www.nj30_dn()>= 2                                     ;} , [&]() { return 1 ;} );

        cutflow.setCutSyst("SRSSmmNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSemNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSeeNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSSidemmNb0"                  , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSSideemNb0"                  , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSSideeeNb0"                  , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SR0SFOSNb0"                     , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SR1SFOSNb0"                     , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SR2SFOSNb0"                     , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCRSSmmNb0"                    , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCRSSemNb0"                    , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCRSSeeNb0"                    , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCR1SFOSNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCR2SFOSNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSmmNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSemNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSeeNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSSidemmNb0"                  , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSSideemNb0"                  , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSSideeeNb0"                  , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("AR0SFOSNb0"                     , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("AR1SFOSNb0"                     , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("AR2SFOSNb0"                     , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSmmNbgeq1"                 , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSemNbgeq1"                 , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSeeNbgeq1"                 , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSSidemmNbgeq1"             , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSSideemNbgeq1"             , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSSideeeNbgeq1"             , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCR0SFOSNbgeq1"                , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCR1SFOSNbgeq1"                , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCR2SFOSNbgeq1"                , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("VBSCRSSmmNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("VBSCRSSemNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("VBSCRSSeeNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSmmNbgeq1"                , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSemNbgeq1"                , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSeeNbgeq1"                , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSSidemmNbgeq1"            , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSSideemNbgeq1"            , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSSideeeNbgeq1"            , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTZCR0SFOSNb1"                  , "JESUp"   , [&]() { return www.nb_up()==1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTZCR1SFOSNb1"                  , "JESUp"   , [&]() { return www.nb_up()==1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTZCR2SFOSNb1"                  , "JESUp"   , [&]() { return www.nb_up()==1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXECRSSmmNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXECRSSemNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXECRSSeeNb0"                   , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("GCR0SFOSNb0"                    , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSmmNbgeq1"               , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSemNbgeq1"               , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSeeNbgeq1"               , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSSidemmNbgeq1"           , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSSideemNbgeq1"           , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSSideeeNbgeq1"           , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCR0SFOSNbgeq1"              , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCR1SFOSNbgeq1"              , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCR2SFOSNbgeq1"              , "JESUp"   , [&]() { return www.nb_up()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXEARCRSSmmNb0"                 , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXEARCRSSemNb0"                 , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXEARCRSSeeNb0"                 , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("OSCRmmNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("OSCRemNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("OSCReeNb0"                      , "JESUp"   , [&]() { return www.nb_up()==0                                        ;} , [&]() { return btag_sf ;} );

        cutflow.setCutSyst("SRSSmmNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSemNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSeeNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSSidemmNb0"                  , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSSideemNb0"                  , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SRSSSideeeNb0"                  , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SR0SFOSNb0"                     , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SR1SFOSNb0"                     , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("SR2SFOSNb0"                     , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCRSSmmNb0"                    , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCRSSemNb0"                    , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCRSSeeNb0"                    , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCR1SFOSNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("WZCR2SFOSNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSmmNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSemNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSeeNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSSidemmNb0"                  , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSSideemNb0"                  , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("ARSSSideeeNb0"                  , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("AR0SFOSNb0"                     , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("AR1SFOSNb0"                     , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("AR2SFOSNb0"                     , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSmmNbgeq1"                 , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSemNbgeq1"                 , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSeeNbgeq1"                 , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSSidemmNbgeq1"             , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSSideemNbgeq1"             , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCRSSSideeeNbgeq1"             , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCR0SFOSNbgeq1"                , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCR1SFOSNbgeq1"                , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTCR2SFOSNbgeq1"                , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("VBSCRSSmmNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("VBSCRSSemNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("VBSCRSSeeNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSmmNbgeq1"                , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSemNbgeq1"                , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSeeNbgeq1"                , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSSidemmNbgeq1"            , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSSideemNbgeq1"            , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTWCRSSSideeeNbgeq1"            , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTZCR0SFOSNb1"                  , "JESDown" , [&]() { return www.nb_dn()==1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTZCR1SFOSNb1"                  , "JESDown" , [&]() { return www.nb_dn()==1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("TTZCR2SFOSNb1"                  , "JESDown" , [&]() { return www.nb_dn()==1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXECRSSmmNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXECRSSemNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXECRSSeeNb0"                   , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("GCR0SFOSNb0"                    , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSmmNbgeq1"               , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSemNbgeq1"               , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSeeNbgeq1"               , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSSidemmNbgeq1"           , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSSideemNbgeq1"           , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCRSSSideeeNbgeq1"           , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCR0SFOSNbgeq1"              , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCR1SFOSNbgeq1"              , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("BTARCR2SFOSNbgeq1"              , "JESDown" , [&]() { return www.nb_dn()>=1                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXEARCRSSmmNb0"                 , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXEARCRSSemNb0"                 , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("LXEARCRSSeeNb0"                 , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("OSCRmmNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("OSCRemNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
        cutflow.setCutSyst("OSCReeNb0"                      , "JESDown" , [&]() { return www.nb_dn()==0                                        ;} , [&]() { return btag_sf ;} );
    }

    if (regions.EqualTo("all"))
    {
        // Because I named the end cuts to be "Full" for every one of them, I can use this fact to filter out a chunk more easily
        // {"SRSSeeFull", "SRSSemFull", .... }
        // --> {"SRSSee", "SRSSem", .... }
        std::vector<TString> endcuts = cutflow.cuttree.getEndCuts();
        std::vector<TString> list_of_cuts;
        for (auto& endcut : endcuts)
            list_of_cuts.push_back(endcut.ReplaceAll("Full", ""));
        // Now replace with "SRSSee,SRSSem,SRSSmm,..."
        regions = RooUtil::StringUtil::join(list_of_cuts);
    }

    if (not regions.IsNull()) cutflow.filterCuts(RooUtil::StringUtil::split(regions, ","));

    // Now book cutflows
    cutflow.bookCutflows();

    // Histogram booking is dependent on whether you ask for certain regions
    if (not regions.IsNull())
    {
        // book histogram from the requested region and below
        for (auto& region : RooUtil::StringUtil::split(regions, ","))
        {
            cutflow.bookHistogramsForCutAndBelow(histograms, region);
        }
    }
    else
    {
        // Now book histograms at the end of each cut structures (the CutTree nodes that terminates)
        cutflow.bookHistogramsForEndCuts(histograms);
    }

    // Print the cut structure for review
    cutflow.printCuts();

    //
    //
    // Looping events
    //
    //
    while (looper.nextEvent())
    {

        // PureWgt
        float purewgt = (is2017 == 1) ? pileupreweight.purewgt() : www.purewgt();

        // Fake factor weights
        ffwgt = 1;
        if (doFakeEstimation)
        {
            ffwgt = is2017 == 1 ? fakerates.getFakeFactor() : www.ffwgt();
            if (doEwkSubtraction && !www.bkgtype().EqualTo("fakes")) ffwgt *= -1; // subtracting non-fakes
            if (doEwkSubtraction &&  www.bkgtype().EqualTo("fakes")) ffwgt *=  0; // do not subtract fakes
            if (!doEwkSubtraction) purewgt = 1;
        }

        // Compute preselection
        presel = 1;
        presel &= (www.firstgoodvertex()      == 0);
        presel &= (www.Flag_AllEventFilters() >  0);
        presel &= (www.vetophoton()           == 0);
        presel &= (www.evt_passgoodrunlist()  >  0);
        presel &= (www.nVlep()                >= 2);
        presel &= (www.nLlep()                >= 2);

        // Compute trigger variable (TODO for 2016 baby, the tertiary statement may be outdated)
        trigger = is2017 == 1 ? www.passTrigger() * www.pass_duplicate_ee_em_mm() : passTrigger2016();

        // Event weight
        weight = (isData and !doFakeEstimation) ? 1 : www.evt_scale1fb() * purewgt * lumi * ffwgt;
        if (isWWW and !is2017) weight *= 1.0384615385; // NLO cross section v. MadGraph cross section

        // Lepton counter to define dilep or trilep region
        isdilep          = (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 2);
        istrilep         = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0]>25.);
        isfakedilep      = (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
        isfaketrilep     = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2);
        iswzcrtrilep     = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3);
        isfakewzcrtrilep = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2);
        osdileppresel    = (www.mc_HLT_DoubleEl()||www.mc_HLT_DoubleMu()||www.mc_HLT_MuEG())*(www.nVlep()==2)*(www.nLlep()==2)*(www.nTlep()==2);


        // Compute the scale factors
        std::tie(ee_sf, em_sf, mm_sf, threelep_sf) = leptonScaleFactors.getScaleFactors(is2017, doFakeEstimation, isData);
        btag_sf = isData ? 1 : www.weight_btagsf();
        trig_sf = isData ? 1 : www.trigsf();

        hasz_ss = (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.);
        hasz_3l = (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.);

        // Theory related weights from h_neventsinfile in each input root file but only set files when new file opens
        // NOTE if there was a continue statement prior to this it can mess it up
        if (looper.isNewFileInChain()) theoryweight.setFile(looper.getCurrentFileName());

        // Set the variables used for histogramming
        int index = fakerates.getFakeLepIndex();
        float ptcorr = index >= 0 ? fakerates.getPtCorr() : -999;
        float abseta = index >= 0 ? fabs(www.lep_eta()[index]) : -999;
        int ibin = RooUtil::Calc::calcBin2D(ptcorrcoarse_bounds, eta_bounds, ptcorr, abseta);
        const int nbin = (eta_bounds.size()-1) * (ptcorrcoarse_bounds.size()-1);
        cutflow.setVariable("ptcorretarolledcoarse"    , ibin);
        cutflow.setVariable("ptcorretarolledcoarseemu" , ibin + nbin * (abs(www.lep_pdgId()[index]) == 11 ? 1 : 0));

        // Set the event list variables
        cutflow.setEventID(www.run(), www.lumi(), www.evt());

        // Once every cut bits are set, now fill the cutflows that are booked
        cutflow.fill();
    }

    // Save output
    cutflow.saveOutput();

    return 0;
}

//_______________________________________________________________________________________________________
int help()
{
    // Help function
    std::cout << "Usage:" << std::endl;
    std::cout << std::endl;
    std::cout << "  $ ./process INPUTFILES INPUTTREENAME OUTPUTFILE [NEVENTS]" << std::endl;
    std::cout << std::endl;
    std::cout << "  INPUTFILES      comma separated file list" << std::endl;
    std::cout << "  INPUTTREENAME   tree name in the file" << std::endl;
    std::cout << "  OUTPUTFILE      output file name" << std::endl;
    std::cout << "  [NEVENTS=-1]    # of events to run over" << std::endl;
    std::cout << "  [REGIONS]       comma separated regions" << std::endl;
    std::cout << std::endl;
    return 1;
}

//_______________________________________________________________________________________________________
int main(int argc, char** argv)
{
    if (argc == 4)
    {
        return process(argv[1], argv[2], argv[3], -1, "");
    }
    else if (argc == 5)
    {
        return process(argv[1], argv[2], argv[3], atoi(argv[4]), "");
    }
    else if (argc == 6)
    {
        return process(argv[1], argv[2], argv[3], atoi(argv[4]), argv[5]);
    }
    else
    {
        return help();
    }
}

