#ifndef globalvariables_h
#define globalvariables_h

#include <map>
#include <functional>
#include "TString.h"

// global variables
extern float ffwgt;
extern bool presel;
extern bool trigger;
extern float weight;
extern bool isdilep;
extern bool istrilep;
extern bool isfakedilep;
extern bool isfaketrilep;
extern bool isloosedilep;
extern bool iswzcrtrilep;
extern bool isfakewzcrtrilep;
extern bool osdileppresel;
extern float ee_sf, em_sf, mm_sf, threelep_sf;
extern float btag_sf;
extern float trig_sf;
extern bool hasz_ss, hasz_3l;
extern bool passPhotonCRSFOS;

extern bool doSystematics;
extern bool is2017;
extern bool isWWW;
extern bool doWWWXsecScaling;
extern bool doHistogram;
extern bool doFakeEstimation;
extern bool doEwkSubtraction;
extern bool isData;
extern bool is2016_v122;

extern float lumi;

extern std::map<TString, std::function<bool()>> systematic_cuts;
extern std::map<TString, std::function<float()>> systematic_wgts;

#endif
