#include "histograms.h"

const std::vector<float> eta_bounds = {0.0, 1.6, 2.4};
const std::vector<float> ptcorrcoarse_bounds = {0., 20., 25., 30., 35., 150.};

RooUtil::Histograms createHistograms()
{
    RooUtil::Histograms histograms;
    histograms.addHistogram("MllSS"                    ,  180 , 0.      , 300.   , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllSS_wide"               ,  180 , 0.      , 2000.  , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllZ"                     ,  180 , 60.     , 120.   , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllZZoom"                 ,  180 , 80.     , 100.   , [&]() { return www.MllSS()                  ; });
    histograms.addHistogram("MllOnOff"                 ,  180 , 30.     , 150.   , [&]() { return fabs(www.Mll3L()-91.1876)<fabs(www.Mll3L1()-91.1876)?www.Mll3L():www.Mll3L1(); });
    histograms.addHistogram("Mll3L"                    ,  180 , 0.      , 300.   , [&]() { return www.Mll3L()                  ; });
    histograms.addHistogram("Mll3L1"                   ,  180 , 0.      , 300.   , [&]() { return www.Mll3L1()                 ; });
    histograms.addHistogram("nSFOSinZ"                 ,  3   , 0.      , 3.     , [&]() { return www.nSFOSinZ()               ; });
    histograms.addHistogram("M3l"                      ,  180 , 0.      , 150.   , [&]() { return www.M3l()                    ; });
    histograms.addHistogram("Pt3lGCR"                  ,  180 , 0.      , 100.   , [&]() { return www.Pt3l()                   ; });
    histograms.addHistogram("Pt3l"                     ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                   ; });
    histograms.addHistogram("Ptll"                     ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                   ; });
    histograms.addHistogram("nvtx"                     ,  60  , 0.      , 60.    , [&]() { return www.nVert()                  ; });
    histograms.addHistogram("MjjZoom"                  ,  180 , 0.      , 150.   , [&]() { return www.Mjj()                    ; });
    histograms.addHistogram("Mjj"                      ,  180 , 0.      , 300.   , [&]() { return www.Mjj()                    ; });
    histograms.addHistogram("MjjL"                     ,  180 , 0.      , 750.   , [&]() { return www.MjjL()                   ; });
    histograms.addHistogram("DetajjL"                  ,  180 , 0.      , 5.     , [&]() { return www.DetajjL()                ; });
    histograms.addHistogram("MjjVBF"                   ,  180 , 0.      , 750.   , [&]() { return www.MjjVBF()                 ; });
    histograms.addHistogram("DetajjVBF"                ,  180 , 0.      , 8.     , [&]() { return www.DetajjVBF()              ; });
    histograms.addHistogram("MjjVBS"                   ,  180 , 0.      , 750.   , [&]() { return www.Mjj()                    ; });
    histograms.addHistogram("DetajjVBS"                ,  180 , 0.      , 3.     , [&]() { return www.DetajjL()                ; });
    histograms.addHistogram("MET"                      ,  180 , 0.      , 180.   , [&]() { return www.met_pt()                 ; });
    histograms.addHistogram("METWide"                  ,  180 , 0.      , 300.   , [&]() { return www.met_pt()                 ; });
    histograms.addHistogram("lep_pt0"                  ,  180 , 0.      , 250    , [&]() { return www.lep_pt()[0]              ; });
    histograms.addHistogram("lep_pt1"                  ,  180 , 0.      , 150    , [&]() { return www.lep_pt()[1]              ; });
    histograms.addHistogram("lep_pt2"                  ,  180 , 0.      , 150    , [&]() { return www.lep_pt()[2]              ; });
    histograms.addHistogram("lep_eta0"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_eta()[0]             ; });
    histograms.addHistogram("lep_eta1"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_eta()[1]             ; });
    histograms.addHistogram("lep_phi0"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_phi()[0]             ; });
    histograms.addHistogram("lep_phi1"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_phi()[1]             ; });
    histograms.addHistogram("lep_relIso03EAv2Lep0"     ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[0] ; });
    histograms.addHistogram("lep_relIso03EAv2Lep1"     ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[1] ; });
    histograms.addHistogram("lep_relIso03EAv2Lep2"     ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[2] ; });
    histograms.addHistogram("lep_relIso03EAv2LepMaxSS" ,  180 , 0.0     , 0.2    , [&]() { return std::max(www.lep_relIso03EAv2Lep()[0], www.lep_relIso03EAv2Lep()[1]) ; });
    histograms.addHistogram("nj"                       ,  7   , 0.      , 7.     , [&]() { return www.nj()                     ; });
    histograms.addHistogram("nj30"                     ,  7   , 0.      , 7.     , [&]() { return www.nj30()                   ; });
    histograms.addHistogram("nb"                       ,  5   , 0.      , 5.     , [&]() { return www.nb()                     ; });
    histograms.addHistogram("MTmin"                    ,  180 , 0.      , 300.   , [&]() { return www.MTmin()                  ; });
    histograms.addHistogram("MTmax"                    ,  180 , 0.      , 300.   , [&]() { return www.MTmax()                  ; });
    histograms.addHistogram("MTmax3L"                  ,  180 , 0.      , 300.   , [&]() { return www.MTmax3L()                ; });
    histograms.addHistogram("MT3rd"                    ,  180 , 0.      , 300.   , [&]() { return www.MT3rd()                  ; });
//    histograms.addHistogram("MinMlj"                   ,  180 , 0.      , 300.   , [&]() { return www.MinMlj()                 ; });
//    histograms.addHistogram("MaxMlj"                   ,  180 , 0.      , 1000.  , [&]() { return www.MaxMlj()                 ; });
//    histograms.addHistogram("SumMlj"                   ,  180 , 0.      , 1200.  , [&]() { return www.SumMlj()                 ; });
//    histograms.addHistogram("MinMljj"                  ,  180 , 0.      , 600.   , [&]() { return www.MinMljj()                ; });
//    histograms.addHistogram("MaxMljj"                  ,  180 , 0.      , 1600.  , [&]() { return www.MaxMljj()                ; });
//    histograms.addHistogram("SumMljj"                  ,  180 , 0.      , 1800.  , [&]() { return www.SumMljj()                ; });
    histograms.addHistogram("el_relIso03EAv2Lep"       ,  180 , 0.0     , 0.2    , [&]() { return (abs(www.lep_pdgId()[0]) == 11) * (www.lep_relIso03EAv2Lep()[0]) + (abs(www.lep_pdgId()[1]) == 11) * (www.lep_relIso03EAv2Lep()[1]); });
    histograms.addHistogram("mu_relIso03EAv2Lep"       ,  180 , 0.0     , 0.2    , [&]() { return (abs(www.lep_pdgId()[0]) == 13) * (www.lep_relIso03EAv2Lep()[0]) + (abs(www.lep_pdgId()[1]) == 13) * (www.lep_relIso03EAv2Lep()[1]); });

    // Fake rate estimation histogram
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

    return histograms;

}
