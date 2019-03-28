#ifndef main_h
#define main_h

#include "wwwtree.h"
#include "rooutil.h"
#include "cxxopts.h"
#include "AnalysisConfig.h"
#include "InputConfig.h"
#include "scalefactors.h"
#include "lambdas.h"

#ifdef WITHCORE
#include "CMS4Utils.h"
#endif


// #include "applicationregioncuts.h"
// #include "basecuts.h"
// #include "fakeratecontrolregioncuts.h"
// #include "globalvariables.h"
// #include "histograms.h"
// #include "lostlepcontrolregioncuts.h"
// #include "misccontrolregioncuts.h"
// #include "promptcontrolregioncuts.h"
// #include "signalregioncuts.h"
// #include "systematiccuts.h"

// void bookCutflowsAndHistogramsForGivenRegions(RooUtil::Cutflow& cutflow, RooUtil::Histograms& histograms, TString regions);
// void setGlobalConfigurationVariables(const char* input_paths, const char* output_file_name);
// void setGlobalEventVariables();

#endif
