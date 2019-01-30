#ifndef main_h
#define main_h

#include "wwwtree.h"
#include "rooutil/rooutil.h"

#include "histograms.h"
#include "globalvariables.h"

bool passTrigger2016();
void bookCutflowsAndHistogramsForGivenRegions(RooUtil::Cutflow& cutflow, RooUtil::Histograms& histograms, TString regions);
void setGlobalConfigurationVariables(const char* input_paths, const char* output_file_name);
void setGlobalEventVariables(const char* input_paths, const char* output_file_name);

#endif
