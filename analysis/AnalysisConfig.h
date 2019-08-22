#ifndef AnalysisConfig_h
#define AnalysisConfig_h

// ROOT
#include "TChain.h"
#include "TFile.h"
#include "TString.h"

// Analysis
#include "rooutil.h"
#include "wwwtree.h"

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

    // Boolean flag to whether or not book the eventlist
    bool do_eventlist;

    // Boolean flag to whether or not book the skim job
    bool do_skim;

    // TTreeX to facilitate new skim branches
    RooUtil::TTreeX* tx;

    // Boolean flag to tell whether new branches have been created
    bool skim_new_branches_created;

    // Boolean flag to whether or not book histograms and cutflows for systematic variations
    bool do_systematics;

    // Boolean flag to whether to force all histograms and cutflows and ignore whether do_systematics is true or not
    bool do_force;

    // Boolean flag to determine whether the fake rate weights will be applied to the weights
    bool do_fake_estimation;

    // Boolean flag to determine whether the user_study function will be called
    // The user_study function will be where analyzers can implement new cuts and histograms to make their own studies
    // Once the study shows promising results, we can port them to the main work flow
    bool do_user_study;

    // The TChain that holds the input TTree's
    TChain* events_tchain;

    // Jobs to split (if this number is positive, then we will skip certain number of events)
    // If there are N events, and was asked to split 2 ways, then depending on job_index, it will run over first half or latter half
    int nsplit_jobs;

    // Job index (assuming nsplit_jobs is set, the job_index determine where to loop over)
    int job_index;

    // The RooUtil::Looper class takes in a list of TChain and loops them over
    // The code can be simpliifed to while (looper.nextEvent()) instead of using a for-based loop
    RooUtil::Looper<wwwtree> looper;

    // The RooUtil::Cutflow class helps user create complex cuttree structure
    // and book appropriate histograms at each cut stage
    RooUtil::Cutflow cutflow;

    // The RooUtil::Histogram class holds the definitions of histograms
    RooUtil::Histograms histograms;

};

extern AnalysisConfig ana;

#endif
