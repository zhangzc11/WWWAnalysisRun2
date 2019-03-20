#ifndef AnalysisConfig_h
#define AnalysisConfig_h

// ROOT
#include "TChain.h"
#include "TFile.h"
#include "TString.h"

// Analysis
#include "rooutil.h"

// These are configurations that does not change through out the entire loop
class AnalysisConfig
{

public:

    // Nevents to process
    int n_events;

    // Input file list stored as a comma separated strings
    TString input_file_list_tstring;

    // For each baby ntuple file there are several TTrees, the following sets which one to loop over
    TString input_tree_name;

    // Output TFile that will hold histograms and cutflow histograms
    TFile* output_tfile;

    // Boolean flag to whether or not book the histograms
    bool do_histograms;

    // Boolean flag to whether or not book the cutflow histograms
    bool do_cutflow;

    // Boolean flag to whether or not book histograms and cutflows for systematic variations
    bool do_systematics;

    // Boolean flag to determine whether the fake rate weights will be applied to the weights
    bool do_fake_estimation;

    // The TChain that holds the input TTree's
    TChain* events_tchain;

    // The RooUtil::Looper class takes in a list of TChain and loops them over
    // The code can be simpliifed to while (looper.nextEvent()) instead of using a for-based loop
    RooUtil::Looper<wwwtree> looper;

    // The RooUtil::Cutflow class helps user create complex cuttree structure
    // and book appropriate histograms at each cut stage
    RooUtil::Cutflow cutflow;

    // The RooUtil::Histogram class holds the definitions of histograms
    RooUtil::Histograms histograms;

};

#endif
