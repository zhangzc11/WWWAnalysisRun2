#include "globalvariables.h"

// global variables
float ffwgt;
bool presel;
bool trigger;
float weight;
bool isdilep;
bool istrilep;
bool isfakedilep;
bool isfaketrilep;
bool isloosedilep;
bool iswzcrtrilep;
bool isfakewzcrtrilep;
bool osdileppresel;
float ee_sf, em_sf, mm_sf, threelep_sf;
float btag_sf;
float trig_sf;
bool hasz_ss, hasz_3l;
bool passPhotonCRSFOS;

bool doSystematics;
bool is2017;
bool isWWW;
bool doWWWXsecScaling;
bool doHistogram;
bool doFakeEstimation;
bool doEwkSubtraction;
bool isData;
bool is2016_v122;

float lumi;

std::map<TString, std::function<bool()>> systematic_cuts;
std::map<TString, std::function<float()>> systematic_wgts;
