#ifndef InputConfig_h
#define InputConfig_h

// ROOT
#include "TString.h"

// Analysis
#include "rooutil.h"

// These are configurations that is evaluated every time the input file changes
// This so that you can chain multiple different samples and properly determine technical details of the loop
class InputConfig
{

public:

    // Year of the sample
    int year;

    // input file is data?
    bool is_data;

    // input file is WWW signal sample?
    bool is_www;

    // input file is VH sample?
    bool is_vh;

    // if we're running over t_www tree with is_www or is_vh then these events are signal
    bool is_sig;

    // boolean flag for is_bkg
    bool is_bkg;

    // Do WWW xsec scaling?
    // This is historical. In the future this should be deprecated.
    // For 2016 baby version of v1.2.2 (the public result) WWW had LO cross-section instead of NLO
    bool do_www_xsec_scaling;

    // Current file name that was used to determine the settings in this class
    TString current_file_name;

    // baby type
    // There are several baby types
    // 1. WWW baby (same-sign + 3lepton pre selection applied. Most common type.)
    // 2. FR baby (fake rate baby where it has 1 lepton events included)
    // 3. OS baby (opposite dilepton events are added on top of 1. and the lepton containers contain 3L-loose-ID leptons. While for 1. once the same-sign lepton events are identified, it only writes SS-loose-ID leptons to lep_* containers in the baby)
    // 4. POG baby (baby made with POG ID)
    // These are identifiable by the path names
    // e.g. /hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2018_v5.1.3/*/merged/*.root
    //       ^^^^^^                                      ^^^^^^^^^
    //      or
    //      /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/skim/*.root
    //       ^^^^^                             ^^^^^^^^^
    TString baby_type; // can be "WWW", "FR", "OS", or "POG" etc.

    // The version of the baby
    TString baby_version;

    // Whether or not the baby version has new pre computed variables or not
    bool oldbaby;

    // The function to determine all the configuration above
    void determine_input_settings(TString file_path, TString tree_name);

    // Print input file settings to be clear
    void print_input_settings();

};

extern InputConfig input;

#endif
