#include "main.h"

//_______________________________________________________________________________________________________
int main(int argc, char** argv)
{

//********************************************************************************
//
// 0. Notes on global configuration classes and global TTree reader class
//
//********************************************************************************

    // 1.

    // There is a global variable defined in AnalysisConfig.cc
    //
    //   AnalysisConfig ana;
    //
    // This class instance contains configuration that persists through the entire run time.
    // (e.g. number of events, the input file name list, etc. that will not change through run time)
    // (see AnalysisConfig.h to get a feeling)

    // 2.

    // There is a global variable defined in AnalysisConfig.cc
    //
    //   InputConfig input;
    //
    // This class instance contains configuration that persists only through a single ROOT file in the chain of input ROOT files.
    // Everytime looper loads new file, the configuration in this class is reconfigured to handle sample dependent behaviors.
    // (e.g. is_data? is_sig? is_bkg? etc.)
    // (see InputConfig.h to get a feeling)

    // 3.

    // Then there is a global variable defined in wwwtree.cc
    //
    //    wwwtree www;
    //
    // This is an instance which helps read variables in the WWW baby TTree
    // It is a giant wrapper that facilitates reading TBranch values.
    // e.g. if there is a TBranch named "lep_pt" which is a std::vector<float> then, one can access the branch via
    //
    //    std::vector<float> lep_pt = www.lep_pt();
    //
    // and no need for "SetBranchAddress" and declaring variable shenanigans necessary.
    // This is a standard thing SNT does pretty much every looper we use.

    // 4.

    // The there are a few scale factor reader classes that are also globally defined
    // Those are defined in scalefactors.h
    // They are nothing more than just reading TH's from ROOT files and retrieving the contents in a simpler way

//********************************************************************************
//
// 1. Parsing options
//
//********************************************************************************

    // cxxopts is just a tool to parse argc, and argv easily

    // Grand option setting
    cxxopts::Options options("\n  $ doAnalysis",  "\n         **********************\n         *                    *\n         * Run 2 WWW Analysis *\n         *                    *\n         **********************\n");

    // Read the options
    options.add_options()
        ("i,input"       , "Comma separated input file list OR if just a directory is provided it will glob all in the directory BUT must end with '/' for the path", cxxopts::value<std::string>())
        ("T,tree"        , "Name of the TTree in the input file to loop over"                                                    , cxxopts::value<std::string>())
        ("o,output"      , "Output file name"                                                                                    , cxxopts::value<std::string>())
        ("n,nevents"     , "N events to loop over"                                                                               , cxxopts::value<int>()->default_value("-1"))
        ("t,test"        , "Run test job. i.e. overrides output option to 'test.root' and 'recreate's the file.")
        ("H,hist"        , "Book histogram")
        ("C,cutflow"     , "Book cutflows")
        ("L,eventlist"   , "Book event list")
        ("K,skim"        , "Book ntuple skim")
        ("S,systematics" , "Also consider systematics (NOTE: Generally, this limits the number of histograms and cutflows. use -f,--force to run all.)")
        ("f,force"       , "force process all and not limit any number of histograms and cutflows")
        ("F,fake"        , "The event weight will be multiplied by fake weights")
        ("u,user_study"  , "Enable user_study function for analyzers to make their own studies")
        ("j,nsplit_jobs" , "Enable splitting jobs by N blocks (--job_index must be set)", cxxopts::value<int>())
        ("I,job_index"   , "job_index of split jobs (--nsplit_jobs must be set. index starts from 0. i.e. 0, 1, 2, 3, etc...)", cxxopts::value<int>())
        ("h,help"        , "Print help")
        ;

    auto result = options.parse(argc, argv);

    // NOTE: When an option was provided (e.g. -i or --input), then the result.count("<option name>") is more than 0
    // Therefore, the option can be parsed easily by asking the condition if (result.count("<option name>");
    // That's how the several options are parsed below

    //_______________________________________________________________________________
    // --help
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --input
    if (result.count("input"))
    {
        ana.input_file_list_tstring = result["input"].as<std::string>();
    }
    else
    {
        std::cout << options.help() << std::endl;
        std::cout << "ERROR: Input list is not provided! Check your arguments" << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --nevents
    ana.n_events = result["nevents"].as<int>();

    //_______________________________________________________________________________
    // --test
    if (result.count("test"))
    {
        ana.output_tfile = new TFile("test.root", "recreate");
    }
    else
    {
        //_______________________________________________________________________________
        // --output
        if (result.count("output"))
        {
            ana.output_tfile = new TFile(result["output"].as<std::string>().c_str(), "create");
            if (not ana.output_tfile->IsOpen())
            {
                std::cout << options.help() << std::endl;
                std::cout << "ERROR: output already exists! provide new output name or delete old file. OUTPUTFILE=" << result["output"].as<std::string>() << std::endl;
                exit(1);
            }
        }
        else
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: Output file name is not provided! Check your arguments" << std::endl;
            exit(1);
        }
    }

    //_______________________________________________________________________________
    // --tree
    if (result.count("tree"))
    {
        ana.input_tree_name = result["tree"].as<std::string>();
    }
    else
    {
        std::cout << options.help() << std::endl;
        std::cout << "ERROR: Input tree name is not provided! Check your arguments" << std::endl;
        exit(1);
    }

    //_______________________________________________________________________________
    // --hist
    if (result.count("hist"))
    {
        ana.do_histograms = true;
    }
    else
    {
        ana.do_histograms = false;
    }

    //_______________________________________________________________________________
    // --cutflow
    if (result.count("cutflow"))
    {
        ana.do_cutflow = true;
    }
    else
    {
        ana.do_cutflow = false;
    }

    //_______________________________________________________________________________
    // --eventlist
    if (result.count("eventlist"))
    {
        ana.do_eventlist = true;
    }
    else
    {
        ana.do_eventlist = false;
    }

    //_______________________________________________________________________________
    // --skim
    if (result.count("skim"))
    {
        ana.do_skim = true;
        ana.skim_new_branches_created = false;
    }
    else
    {
        ana.do_skim = false;
        ana.skim_new_branches_created = false;
    }

    //_______________________________________________________________________________
    // --systematics
    if (result.count("systematics"))
    {
        ana.do_systematics = true;
    }
    else
    {
        ana.do_systematics = false;
    }

    //_______________________________________________________________________________
    // --force
    if (result.count("force"))
    {
        ana.do_force = true;
    }
    else
    {
        ana.do_force = false;
    }

    //_______________________________________________________________________________
    // --fake
    if (result.count("fake"))
    {
        ana.do_fake_estimation = true;
    }
    else
    {
        ana.do_fake_estimation = false;
    }

    //_______________________________________________________________________________
    // --user_study
    if (result.count("user_study"))
    {
        ana.do_user_study = true;
    }
    else
    {
        ana.do_user_study = false;
    }

    //_______________________________________________________________________________
    // --nsplit_jobs
    if (result.count("nsplit_jobs"))
    {
        ana.nsplit_jobs = result["nsplit_jobs"].as<int>();
        if (ana.nsplit_jobs <= 0)
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: option string --nsplit_jobs" << ana.nsplit_jobs << " has zero or negative value!" << std::endl;
            std::cout << "I am not sure what this means..." << std::endl;
            exit(1);
        }
    }
    else
    {
        ana.nsplit_jobs = -1;
    }

    //_______________________________________________________________________________
    // --nsplit_jobs
    if (result.count("job_index"))
    {
        ana.job_index = result["job_index"].as<int>();
        if (ana.job_index < 0)
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: option string --job_index" << ana.job_index << " has negative value!" << std::endl;
            std::cout << "I am not sure what this means..." << std::endl;
            exit(1);
        }
    }
    else
    {
        ana.job_index = -1;
    }


    // Sanity check for split jobs (if one is set the other must be set too)
    if (result.count("job_index") or result.count("nsplit_jobs"))
    {
        // If one is not provided then throw error
        if ( not (result.count("job_index") and result.count("nsplit_jobs")))
        {
            std::cout << options.help() << std::endl;
            std::cout << "ERROR: option string --job_index and --nsplit_jobs must be set at the same time!" << std::endl;
            exit(1);
        }
        // If it is set then check for sanity
        else
        {
            if (ana.job_index >= ana.nsplit_jobs)
            {
                std::cout << options.help() << std::endl;
                std::cout << "ERROR: --job_index >= --nsplit_jobs ! This does not make sense..." << std::endl;
                exit(1);
            }
        }
    }

    //
    // Printing out the option settings overview
    //
    std::cout <<  "=========================================================" << std::endl;
    std::cout <<  " Setting of the analysis job based on provided arguments " << std::endl;
    std::cout <<  "---------------------------------------------------------" << std::endl;
    std::cout <<  " ana.input_file_list_tstring: " << ana.input_file_list_tstring <<  std::endl;
    std::cout <<  " ana.output_tfile: " << ana.output_tfile->GetName() <<  std::endl;
    std::cout <<  " ana.n_events: " << ana.n_events <<  std::endl;
    std::cout <<  " ana.do_cutflow: " << ana.do_cutflow <<  std::endl;
    std::cout <<  " ana.do_eventlist: " << ana.do_eventlist <<  std::endl;
    std::cout <<  " ana.do_skim: " << ana.do_skim <<  std::endl;
    std::cout <<  " ana.do_histograms: " << ana.do_histograms <<  std::endl;
    std::cout <<  " ana.do_systematics: " << ana.do_systematics <<  std::endl;
    std::cout <<  " ana.do_force: " << ana.do_force <<  std::endl;
    std::cout <<  " ana.do_fake_estimation: " << ana.do_fake_estimation <<  std::endl;
    std::cout <<  " ana.do_user_study: " << ana.do_user_study <<  std::endl;
    std::cout <<  " ana.nsplit_jobs: " << ana.nsplit_jobs <<  std::endl;
    std::cout <<  " ana.job_index: " << ana.job_index <<  std::endl;
    std::cout <<  "=========================================================" << std::endl;

//********************************************************************************
//
// 2. Opening input baby files
//
//********************************************************************************

    // Create the TChain that holds the TTree's of the baby ntuples
    ana.events_tchain = RooUtil::FileUtil::createTChain(ana.input_tree_name, ana.input_file_list_tstring);

    // Create a Looper object to loop over input files
    // the "www" object is defined in the wwwtree.h/cc
    // This is an instance which helps read variables in the WWW baby TTree
    // It is a giant wrapper that facilitates reading TBranch values.
    // e.g. if there is a TBranch named "lep_pt" which is a std::vector<float> then, one can access the branch via
    //
    //    std::vector<float> lep_pt = www.lep_pt();
    //
    // and no need for "SetBranchAddress" and declaring variable shenanigans necessary
    // This is a standard thing SNT does pretty much every looper we use
    ana.looper.init(ana.events_tchain, &www, ana.n_events);

//********************************************************************************
//
// Interlude... notes on RooUtil framework (This is a custom thing built by P. Chang)
//
//********************************************************************************

    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    // Quick tutorial on RooUtil::Cutflow object cut tree formation
    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //
    // The RooUtil::Cutflow object facilitates creating a tree structure of cuts
    //
    // To add cuts to each node of the tree with cuts defined, use "addCut" or "addCutToLastActiveCut"
    // The "addCut" or "addCutToLastActiveCut" accepts three argument, <name>, and two lambda's that define the cut selection, and the weight to apply to that cut stage
    //
    // e.g. To create following cut-tree structure one does
    //
    //             (Root) <--- Always exists as soon as RooUtil::Cutflow object is created. But this is basically hidden underneath and users do not have to care
    //                |
    //            CutWeight
    //            |       |
    //     CutPreSel1    CutPreSel2
    //       |                  |
    //     CutSel1           CutSel2
    //
    //
    //   code:
    //
    //      // Create the object (Root node is created as soon as the instance is created)
    //      RooUtil::Cutflow cutflow;
    //
    //      cutflow.addCut("CutWeight"                 , <lambda> , <lambda>); // CutWeight is added below "Root"-node
    //      cutflow.addCutToLastActiveCut("CutPresel1" , <lambda> , <lambda>); // The last "active" cut is "CutWeight" since I just added that. So "CutPresel1" is added below "CutWeight"
    //      cutflow.addCutToLastActiveCut("CutSel1"    , <lambda> , <lambda>); // The last "active" cut is "CutPresel1" since I just added that. So "CutSel1" is added below "CutPresel1"
    //
    //      cutflow.getCut("CutWeight"); // By "getting" the cut object, this makes the "CutWeight" the last "active" cut.
    //      cutflow.addCutToLastActiveCut("CutPresel2" , <lambda> , <lambda>); // The last "active" cut is "CutWeight" since I "getCut" on it. So "CutPresel2" is added below "CutWeight"
    //      cutflow.addCutToLastActiveCut("CutSel2"    , <lambda> , <lambda>); // The last "active" cut is "CutPresel2" since I just added that. So "CutSel2" is added below "CutPresel1"
    //
    // (Side note: "UNITY" lambda is defined in the framework to just return 1. This so that use don't have to type [&]() {return 1;} so many times.)
    //
    // Once the cutflow is formed, create cutflow histograms can be created by calling RooUtil::Cutflow::bookCutflows())
    // This function looks through the terminating nodes of the tree structured cut tree. and creates a histogram that will fill the yields
    // For the example above, there are two terminationg nodes, "CutSel1", and "CutSel2"
    // So in this case Root::Cutflow::bookCutflows() will create two histograms. (Actually four histograms.)
    //
    //  - TH1F* type object :  CutSel1_cutflow (4 bins, with first bin labeled "Root", second bin labeled "CutWeight", third bin labeled "CutPreSel1", fourth bin labeled "CutSel1")
    //  - TH1F* type object :  CutSel2_cutflow (...)
    //  - TH1F* type object :  CutSel1_rawcutflow (...)
    //  - TH1F* type object :  CutSel2_rawcutflow (...)
    //                                ^
    //                                |
    // NOTE: There is only one underscore "_" between <CutName>_cutflow or <CutName>_rawcutflow
    //
    // And later in the loop when RooUtil::Cutflow::fill() function is called, the tree structure will be traversed through and the appropriate yields will be filled into the histograms
    //
    // After running the loop check for the histograms in the output root file

    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    // Quick tutorial on RooUtil::Histograms object
    // ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
    //
    // The RooUtil::Histograms object facilitates book keeping histogram definitions
    // And in conjunction with RooUtil::Cutflow object, one can book same histograms across different cut stages easily without copy pasting codes many times by hand.
    //
    // The histogram addition happens in two steps.
    // 1. Defining histograms
    // 2. Booking histograms to cuts
    //
    // Histograms are defined via following functions
    //
    //      RooUtil::Histograms::addHistogram       : Typical 1D histogram (TH1F*) "Fill()" called once per event
    //      RooUtil::Histograms::addVecHistogram    : Typical 1D histogram (TH1F*) "Fill()" called multiple times per event
    //      RooUtil::Histograms::add2DHistogram     : Typical 2D histogram (TH2F*) "Fill()" called once per event
    //      RooUtil::Histograms::add2DVecHistogram  : Typical 2D histogram (TH2F*) "Fill()" called multiple times per event
    // e.g.
    //
    //    RooUtil::Histograms histograms;
    //    histograms.addHistogram   ("MllSS"    , 180 , 0. , 300. , [&]() { return www.MllSS()  ; }); // The lambda returns float
    //    histograms.addVecHistogram("AllLepPt" , 180 , 0. , 300. , [&]() { return www.lep_pt() ; }); // The lambda returns vector<float>
    //
    // The addVecHistogram will have lambda to return vector<float> and it will loop over the values and call TH1F::Fill() for each item
    //
    // To book histograms to cuts one uses
    //
    //      RooUtil::Cutflow::bookHistogramsForCut()
    //      RooUtil::Cutflow::bookHistogramsForCutAndBelow()
    //      RooUtil::Cutflow::bookHistogramsForCutAndAbove()
    //      RooUtil::Cutflow::bookHistogramsForEndCuts()
    //
    // e.g. Given a tree like the following, we can book histograms to various cuts as we want
    //
    //              Root
    //                |
    //            CutWeight
    //            |       |
    //     CutPreSel1    CutPreSel2
    //       |                  |
    //     CutSel1           CutSel2
    //
    // For example,
    //
    //    1. book a set of histograms to one cut:
    //
    //       cutflow.bookHistogramsForCut(histograms, "CutPreSel2")
    //
    //    2. book a set of histograms to a cut and below
    //
    //       cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight") // will book a set of histograms to CutWeight, CutPreSel1, CutPreSel2, CutSel1, and CutSel2
    //
    //    3. book a set of histograms to a cut and above (... useless...?)
    //
    //       cutflow.bookHistogramsForCutAndAbove(histograms, "CutPreSel2") // will book a set of histograms to CutPreSel2, CutWeight (nothing happens to Root node)
    //
    //    4. book a set of histograms to a terminating nodes
    //
    //       cutflow.bookHistogramsForEndCuts(histograms) // will book a set of histograms to CutSel1 and CutSel2
    //
    // The naming convention of the booked histograms are as follows
    //
    //   cutflow.bookHistogramsForCut(histograms, "CutSel1");
    //
    //  - TH1F* type object : CutSel1__MllSS;
    //  - TH1F* type object : CutSel1__AllLepPt;
    //                               ^^
    //                               ||
    // NOTE: There are two underscores "__" between <CutName>__<HistogramName>
    //
    // And later in the loop when RooUtil::CutName::fill() function is called, the tree structure will be traversed through and the appropriate histograms will be filled with appropriate variables
    // After running the loop check for the histograms in the output root file

//********************************************************************************
//
// 3. Defining histograms
//
//********************************************************************************

    // The RooUtil::Histograms class holds the definitions of histograms with the lambda expression for the variable
    // Then this is used in conjunction with RooUtil::Cutflow to book histograms at different cut stage
    // This is so that the users don't have to copy paste a thousands lines of codes if they want to book more histograms at different cut stages
    ana.histograms.addHistogram("MllSS"                    ,  180 , 0.      , 500.   , [&]() { return www.MllSS()                                                                  ; });
    ana.histograms.addHistogram("MllSS_wide"               ,  180 , 0.      , 2000.  , [&]() { return www.MllSS()                                                                  ; });
    ana.histograms.addHistogram("MllZ"                     ,  180 , 60.     , 120.   , [&]() { return www.MllSS()                                                                  ; });
    ana.histograms.addHistogram("MllZZoom"                 ,  180 , 80.     , 100.   , [&]() { return www.MllSS()                                                                  ; });
    ana.histograms.addHistogram("MllOnOff"                 ,  180 , 30.     , 150.   , [&]() { return fabs(www.Mll3L()-91.1876)<fabs(www.Mll3L1()-91.1876)?www.Mll3L():www.Mll3L1(); });
    ana.histograms.addHistogram("Mll3L"                    ,  180 , 0.      , 300.   , [&]() { return www.Mll3L()                                                                  ; });
    ana.histograms.addHistogram("Mll3L1"                   ,  180 , 0.      , 300.   , [&]() { return www.Mll3L1()                                                                 ; });
    ana.histograms.addHistogram("nSFOSinZ"                 ,  3   , 0.      , 3.     , [&]() { return www.nSFOSinZ()                                                               ; });
    ana.histograms.addHistogram("M3l"                      ,  180 , 0.      , 150.   , [&]() { return www.M3l()                                                                    ; });
    ana.histograms.addHistogram("Pt3lGCR"                  ,  180 , 0.      , 100.   , [&]() { return www.Pt3l()                                                                   ; });
    ana.histograms.addHistogram("Pt3l"                     ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                                                                   ; });
    ana.histograms.addHistogram("DPhi3lMET"                ,  160 , 0.      , 3.2   , [&]() { return www.DPhi3lMET()                                                               ; });
    ana.histograms.addHistogram("Ptll"                     ,  180 , 0.      , 300.   , [&]() { return (input.oldbaby ? www.Pt3l() : www.Pt2l())                                          ; });
    ana.histograms.addHistogram("nvtx"                     ,  60  , 0.      , 60.    , [&]() { return www.nVert()                                                                  ; });
    ana.histograms.addHistogram("MjjZoom"                  ,  180 , 0.      , 150.   , [&]() { return www.Mjj()                                                                    ; });
    ana.histograms.addHistogram("Mjj"                      ,  180 , 1.      , 300.   , [&]() { return www.Mjj()                                                                    ; });
    ana.histograms.addHistogram("MjjLZoom"                 ,  180 , 0.      , 300.   , [&]() { return www.MjjL()                                                                   ; });
    ana.histograms.addHistogram("MjjL"                     ,  180 , 0.      , 750.   , [&]() { return www.MjjL()                                                                   ; });
    ana.histograms.addHistogram("DetajjL"                  ,  180 , 0.      , 5.     , [&]() { return www.DetajjL()                                                                ; });
    ana.histograms.addHistogram("MjjVBF"                   ,  180 , 0.      , 750.   , [&]() { return www.MjjVBF()                                                                 ; });
    ana.histograms.addHistogram("DetajjVBF"                ,  180 , 0.      , 8.     , [&]() { return www.DetajjVBF()                                                              ; });
    ana.histograms.addHistogram("MjjVBS"                   ,  180 , 0.      , 750.   , [&]() { return www.Mjj()                                                                    ; });
    ana.histograms.addHistogram("DetajjVBS"                ,  180 , 0.      , 3.     , [&]() { return www.DetajjL()                                                                ; });
    ana.histograms.addHistogram("MET"                      ,  180 , 0.      , 180.   , [&]() { return www.met_pt()                                                                 ; });
    ana.histograms.addHistogram("METWide"                  ,  180 , 0.      , 300.   , [&]() { return www.met_pt()                                                                 ; });
    ana.histograms.addHistogram("BDT_lostlep_prompt_SS2J"  ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(0) ; });
    ana.histograms.addHistogram("BDT_lostlep_prompt_SS1J"  ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(1) ; });
    ana.histograms.addHistogram("BDT_lostlep_prompt_SFOS"  ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(2) ; });
    ana.histograms.addHistogram("BDT_photon_fakes_SS2J"    ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(3) ; });
    ana.histograms.addHistogram("BDT_photon_fakes_SS1J"    ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(4) ; });
    ana.histograms.addHistogram("BDT_photon_fakes_SFOS"    ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(5) ; });
    ana.histograms.addHistogram("BDT_photon_fakes_SS2J_noBtag"    ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(6) ; });
    ana.histograms.addHistogram("BDT_photon_fakes_SS1J_noBtag"    ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(7) ; });
    ana.histograms.addHistogram("BDT_photon_fakes_SFOS_noBtag"    ,  180 , 0.      , 1.0    , [&]() { return VarXGBBDT(8) ; });
    ana.histograms.addHistogram("jets_pt0"                 ,  180 , 0.      , 250    , [&]() { return www.jets_p4().size() > 0 ? www.jets_p4()[0].pt()  : -999                     ; });
    ana.histograms.addHistogram("jets_pt1"                 ,  180 , 0.      , 150    , [&]() { return www.jets_p4().size() > 1 ? www.jets_p4()[1].pt()  : -999                     ; });
    ana.histograms.addHistogram("jets_pt2"                 ,  180 , 0.      , 150    , [&]() { return www.jets_p4().size() > 2 ? www.jets_p4()[2].pt()  : -999                     ; });
    ana.histograms.addHistogram("jet0_btag_score"          ,  180 , 0.      , 1.0    , [&]() { return www.jets_btag_score().size() > 0 ? www.jets_btag_score()[0]  : -999                     ; });
    ana.histograms.addHistogram("jet1_btag_score"          ,  180 , 0.      , 1.0    , [&]() { return www.jets_btag_score().size() > 1 ? www.jets_btag_score()[1]  : -999                     ; });
    ana.histograms.addHistogram("jet2_btag_score"          ,  180 , 0.      , 1.0    , [&]() { return www.jets_btag_score().size() > 2 ? www.jets_btag_score()[2]  : -999                     ; });
    ana.histograms.addHistogram("jets_eta0"                ,  180 , -5.0    , 5.0    , [&]() { return www.jets_p4().size() > 0 ? www.jets_p4()[0].eta() : -999                     ; });
    ana.histograms.addHistogram("jets_eta1"                ,  180 , -5.0    , 5.0    , [&]() { return www.jets_p4().size() > 1 ? www.jets_p4()[1].eta() : -999                     ; });
    ana.histograms.addHistogram("jets_eta2"                ,  180 , -5.0    , 5.0    , [&]() { return www.jets_p4().size() > 2 ? www.jets_p4()[2].eta() : -999                     ; });
    ana.histograms.addHistogram("lep_pt0"                  ,  180 , 0.      , 250    , [&]() { return www.lep_pt().size() > 0 ? www.lep_pt()[0]  : -999                            ; });
    ana.histograms.addHistogram("lep_pt1"                  ,  180 , 0.      , 150    , [&]() { return www.lep_pt().size() > 1 ? www.lep_pt()[1]  : -999                            ; });
    ana.histograms.addHistogram("lep_pt2"                  ,  180 , 0.      , 150    , [&]() { return www.lep_pt().size() > 2 ? www.lep_pt()[2]  : -999                            ; });
    ana.histograms.addHistogram("el_pt2"                   ,  180 , 0.      , 150    , [&]() { return www.lep_pt().size() > 2 and abs(www.lep_pdgId()[2]) == 11 ? www.lep_pt()[2] : -999; });
    ana.histograms.addHistogram("mu_pt2"                   ,  180 , 0.      , 150    , [&]() { return www.lep_pt().size() > 2 and abs(www.lep_pdgId()[2]) == 13 ? www.lep_pt()[2] : -999; });
    ana.histograms.addHistogram("lep_eta0"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_pt().size() > 0 ? www.lep_eta()[0] : -999                            ; });
    ana.histograms.addHistogram("lep_eta1"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_pt().size() > 1 ? www.lep_eta()[1] : -999                            ; });
    ana.histograms.addHistogram("lep_eta2"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_pt().size() > 2 ? www.lep_eta()[2] : -999                            ; });
    ana.histograms.addHistogram("lep_eta_fwd"              ,  {0., 1.6, 2.4}         , [&]() { return www.lep_pt().size() > 2 ? std::max(std::max(fabs(www.lep_eta()[0]), fabs(www.lep_eta()[1])), fabs(www.lep_eta()[2])) : -999; });
    ana.histograms.addHistogram("el_eta2"                  ,  180 , -2.5    , 2.5    , [&]() { return www.lep_pt().size() > 2 and abs(www.lep_pdgId()[2]) == 11 ? www.lep_eta()[2] : -999; });
    ana.histograms.addHistogram("mu_eta2"                  ,  180 , -2.5    , 2.5    , [&]() { return www.lep_pt().size() > 2 and abs(www.lep_pdgId()[2]) == 13 ? www.lep_eta()[2] : -999; });
    ana.histograms.addHistogram("lep_phi0"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_pt().size() > 0 ? www.lep_phi()[0] : -999                            ; });
    ana.histograms.addHistogram("lep_phi1"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_pt().size() > 1 ? www.lep_phi()[1] : -999                            ; });
    ana.histograms.addHistogram("lep_phi2"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_pt().size() > 2 ? www.lep_phi()[2] : -999                            ; });
    ana.histograms.addHistogram("el_phi2"                  ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_pt().size() > 2 and abs(www.lep_pdgId()[2]) == 11 ? www.lep_phi()[2] : -999                            ; });
    ana.histograms.addHistogram("mu_phi2"                  ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_pt().size() > 2 and abs(www.lep_pdgId()[2]) == 13 ? www.lep_phi()[2] : -999                            ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Lep0"     ,  180 , 0.0     , 0.4    , [&]() { return www.lep_pt().size() > 0 ? www.lep_relIso03EAv2Lep()[0] : -999                ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Lep1"     ,  180 , 0.0     , 0.4    , [&]() { return www.lep_pt().size() > 1 ? www.lep_relIso03EAv2Lep()[1] : -999                ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Lep2"     ,  180 , 0.0     , 0.4    , [&]() { return www.lep_pt().size() > 2 ? www.lep_relIso03EAv2Lep()[2] : -999                ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Max"      ,  180 , 0.0     , 0.4    , [&]() { return www.lep_pt().size() > 2 ? std::max(std::max(fabs(www.lep_relIso03EAv2Lep()[0]), fabs(www.lep_relIso03EAv2Lep()[1])), fabs(www.lep_relIso03EAv2Lep()[2])) : -999; });
    ana.histograms.addHistogram("lep_ptcorr"               ,  180 , 0.      , 150    , [&]() { return fakerates.getPtCorr()                                                        ; });
    ana.histograms.addHistogram("el_ptcorr"                ,  {0., 20., 25., 30., 35., 50., 150.}, [&]() { return abs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) == 11 ? fakerates.getPtCorr() : 0; });
    ana.histograms.addHistogram("mu_ptcorr"                ,  {0., 20., 25., 30., 35., 50., 150.}, [&]() { return abs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) == 13 ? fakerates.getPtCorr() : 0; });
    ana.histograms.addHistogram("el_ptcorr_cen"            ,  {0., 20., 25., 30., 35., 50., 150.}, [&]() { return abs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) == 11 and fabs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) < 1.6 ? fakerates.getPtCorr() : 0; });
    ana.histograms.addHistogram("mu_ptcorr_cen"            ,  {0., 20., 25., 30., 35., 50., 150.}, [&]() { return abs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) == 13 and fabs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) < 1.6 ? fakerates.getPtCorr() : 0; });
    ana.histograms.addHistogram("el_ptcorr_fwd"            ,  {0., 20., 25., 30., 35., 50., 150.}, [&]() { return abs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) == 11 and fabs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) >=1.6 ? fakerates.getPtCorr() : 0; });
    ana.histograms.addHistogram("mu_ptcorr_fwd"            ,  {0., 20., 25., 30., 35., 50., 150.}, [&]() { return abs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) == 13 and fabs(www.lep_pdgId()[fakerates.getFakeLepIndex()]) >=1.6 ? fakerates.getPtCorr() : 0; });
    ana.histograms.addHistogram("nj"                       ,  7   , 0.      , 7.     , [&]() { return www.nj()                                                                     ; });
    ana.histograms.addHistogram("nj30"                     ,  7   , 0.      , 7.     , [&]() { return www.nj30()                                                                   ; });
    ana.histograms.addHistogram("nb"                       ,  5   , 0.      , 5.     , [&]() { return www.nb()                                                                     ; });
    ana.histograms.addHistogram("MTmin"                    ,  180 , 0.      , 300.   , [&]() { return www.MTmin()                                                                  ; });
    ana.histograms.addHistogram("MTmax"                    ,  180 , 0.      , 300.   , [&]() { return www.MTmax()                                                                  ; });
    ana.histograms.addHistogram("MTmax3L"                  ,  180 , 0.      , 300.   , [&]() { return www.MTmax3L()                                                                ; });
    ana.histograms.addHistogram("MT3rd"                    ,  180 , 0.      , 300.   , [&]() { return www.MT3rd()                                                                  ; });
    ana.histograms.addHistogram("dEtall"                   ,  180 , 0.      , 5.     , [&]() { return www.lep_eta().size() > 1 ? fabs(www.lep_eta()[0] - www.lep_eta()[1]) : -999  ; });
    ana.histograms.addHistogram("dRll"                     ,  180 , 0.      , 8.     , [&]() { return www.lep_p4().size() > 1 ? RooUtil::Calc::DeltaR(www.lep_p4()[0], www.lep_p4()[1]) : -999  ; });
    ana.histograms.addHistogram("dPhill"                   ,  180 , 0.      , 3.1416 , [&]() { return www.lep_p4().size() > 1 ? fabs(RooUtil::Calc::DeltaPhi(www.lep_p4()[0], www.lep_p4()[1])) : -999  ; });
    ana.histograms.addHistogram("JetCentrality"            ,  180 , 0.      , 10.    , [&]()
            {
                if (www.lep_eta().size() > 1 and www.jets_p4().size() > 0)
                {
                    float detall = fabs(www.lep_eta()[0] - www.lep_eta()[1]);
                    float avgeta = (www.lep_eta()[0] + www.lep_eta()[1]) / 2.;
                    float cen = fabs(www.jets_p4()[0].eta() - avgeta) / (detall / 2.);
                    return cen;
                }
                else
                {
                    return float(-999);
                }
            });
    ana.histograms.addHistogram("MljMin" , 180 , 0. , 300. , [&]()
            {
                if (not input.oldbaby)
                    return www.Mljmin();
                if (not (www.lep_p4().size() > 0 and www.jets_p4().size() > 0))
                    return float(-999);
                float minMlj=9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float Mtemp = (www.lep_p4()[i] + www.jets30_p4()[j]).M();
                    if(Mtemp<minMlj) minMlj = Mtemp;
                  }
                }
                return minMlj;
            });
    ana.histograms.addHistogram("MljMax" , 180 , 0. , 600. , [&]()
            {
                if (not input.oldbaby)
                    return www.Mljmax();
                if (not (www.lep_p4().size() > 1 and www.jets_p4().size() > 0))
                    return float(-999);
                float maxMlj=-9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float Mtemp = (www.lep_p4()[i] + www.jets30_p4()[j]).M();
                    if(Mtemp>maxMlj) maxMlj = Mtemp;
                  }
                }
                return maxMlj;
            });
    ana.histograms.addHistogram("DRljMin" , 180 , 0. , 6.   , [&]()
            {
               if (not input.oldbaby)
                    return www.DRljmin();
                if (not (www.lep_p4().size() > 0 and www.jets_p4().size() > 0))
                    return float(-999);
                float minDRlj=9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float DRtemp = fabs(RooUtil::Calc::DeltaR(www.lep_p4()[i], www.jets30_p4()[j]));
                    if(DRtemp<minDRlj) minDRlj = DRtemp;
                  }
                }
                return minDRlj;
            });
    ana.histograms.addHistogram("DRljMax" , 180 , 0. , 6.   , [&]()
            {
               if (not input.oldbaby)
                    return www.DRljmax();
                if (not (www.lep_p4().size() > 0 and www.jets_p4().size() > 0))
                    return float(-999);
                float maxDRlj=-9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float DRtemp = fabs(RooUtil::Calc::DeltaR(www.lep_p4()[i], www.jets30_p4()[j]));
                    if(DRtemp>maxDRlj) maxDRlj = DRtemp;
                  }
                }
                return maxDRlj;
            });
        ana.histograms.addHistogram("MljMin3L" , 180 , 0. , 300. , [&]()
            {
                if (not input.oldbaby)
                    return www.Mljmin3L();
                if (not (www.lep_p4().size() > 0 and www.jets_p4().size() > 0))
                    return float(-999);
                float minMlj=9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float Mtemp = (www.lep_p4()[i] + www.jets30_p4()[j]).M();
                    if(Mtemp<minMlj) minMlj = Mtemp;
                  }
                }
                return minMlj;
            });
    ana.histograms.addHistogram("MljMax3L" , 180 , 0. , 600. , [&]()
            {
                if (not input.oldbaby)
                    return www.Mljmax3L();
                if (not (www.lep_p4().size() > 1 and www.jets_p4().size() > 0))
                    return float(-999);
                float maxMlj=-9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float Mtemp = (www.lep_p4()[i] + www.jets30_p4()[j]).M();
                    if(Mtemp>maxMlj) maxMlj = Mtemp;
                  }
                }
                return maxMlj;
            });
    ana.histograms.addHistogram("DRljMin3L" , 180 , 0. , 6.   , [&]()
            {
               if (not input.oldbaby)
                    return www.DRljmin3L();
                if (not (www.lep_p4().size() > 0 and www.jets_p4().size() > 0))
                    return float(-999);
                float minDRlj=9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float DRtemp = fabs(RooUtil::Calc::DeltaR(www.lep_p4()[i], www.jets30_p4()[j]));
                    if(DRtemp<minDRlj) minDRlj = DRtemp;
                  }
                }
                return minDRlj;
            });
    ana.histograms.addHistogram("DRljMax3L" , 180 , 0. , 6.   , [&]()
            {
               if (not input.oldbaby)
                    return www.DRljmax3L();
                if (not (www.lep_p4().size() > 0 and www.jets_p4().size() > 0))
                    return float(-999);
                float maxDRlj=-9e5;
                for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
                  for(unsigned int j = 0; j<www.jets30_p4().size(); ++j){//now all jets - that's not what I want
                    float DRtemp = fabs(RooUtil::Calc::DeltaR(www.lep_p4()[i], www.jets30_p4()[j]));
                    if(DRtemp>maxDRlj) maxDRlj = DRtemp;
                  }
                }
                return maxDRlj;
            });
    
    ana.histograms.addHistogram("MTj" , 180 , 0. , 300., [&]()
            {
                if (not (www.jets_p4().size() > 0))
                    return float(-999);
                float phi1 = www.jets_p4()[0].Phi();
                float phi2 = www.met_phi();
                float Et1  = www.jets_p4()[0].Et();
                float Et2  = www.met_pt();
                return float(sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2))));
            });

    // One bin histogram to hold the total yield at this cut stage
    ana.histograms.addHistogram("yield"                    ,  1   , 0.      , 1      , [&]() { return 0                                                                            ; });

    // Because RooUtil::Histograms uses lambda you can compute much more complicated variables on the fly your need
    // Let's define a complex histogram. (This is a variable Yifan is looking into.)
    // This is going to plot a new variable where it plots the minimum DR of the two opposite sign leptons.
    // This is the variable that WH->WW analysis in HIG uses to fit to extract signal.
    ana.histograms.addHistogram("minDRllOS", 180, 0., 4.,
                [&]()
                {

                    // "www" objects contain lepton 4-vectors and pdgID
                    std::vector<LV> lep_p4 = www.lep_p4();
                    std::vector<int> lep_pdgId = www.lep_pdgId();

                    // Loop over and for each opposite sign pair compute DR and choose the smallest
                    float minDR = 999;
                    bool os_pair_found = false;
                    for (unsigned int ii = 0; ii < lep_pdgId.size(); ++ii)
                    {
                        for (unsigned int jj = ii + 1; jj < lep_pdgId.size(); ++jj)
                        {
                            if (lep_pdgId[ii] * lep_pdgId[jj] < 0) // If opposite sign lepton
                            {
                                os_pair_found = true;
                                float thisDR = RooUtil::Calc::DeltaR(lep_p4[ii], lep_p4[jj]);
                                if (thisDR < minDR)
                                {
                                    minDR = thisDR;
                                }
                            }
                        }
                    }

                    if (not os_pair_found) // If same-sign event it will not find anything, then set to -999
                        minDR = -999;

                    return minDR;
                }
            );
    ana.histograms.addVecHistogram("el_photon_pt" , 180 , 0. , 250 , [&]()
            {
                std::vector<float> rtn;
                for (unsigned ilep = 0; ilep < www.lep_pdgId().size(); ++ilep)
                    if (abs(www.lep_pdgId()[ilep]) == 11 and www.lep_motherIdSS()[ilep] == -3)
                        rtn.push_back(www.lep_pt()[ilep]);
                return rtn;
            });

    ana.histograms.addVecHistogram("el_MVA" , 180 , 5 , 8 , [&]()
            {
                std::vector<float> rtn;
                for (unsigned ilep = 0; ilep < www.lep_pdgId().size(); ++ilep)
                    if (abs(www.lep_pdgId()[ilep]) == 11 and www.lep_motherIdSS()[ilep] == -3)
                        rtn.push_back(www.lep_MVA()[ilep]);
                return rtn;
            });
    ana.histograms.addVecHistogram("el_MVA_2017" , 180 , 0.95 , 1 , [&]()
            {
                std::vector<float> rtn;
                for (unsigned ilep = 0; ilep < www.lep_pdgId().size(); ++ilep)
                    // if (abs(www.lep_pdgId()[ilep]) == 11 and www.lep_motherIdSS()[ilep] == -3)
                    //     rtn.push_back(www.lep_MVA()[ilep]);
                    if (abs(www.lep_pdgId()[ilep]) == 11)
                        rtn.push_back(www.lep_MVA()[ilep]);
                return rtn;
            });


//********************************************************************************
//
// 4. Creating the analysis using RooUtil::Cutflow class
//
//********************************************************************************

    // Set the cutflow object output file
    ana.cutflow.setTFile(ana.output_tfile);

    //_______________________________________________________________________________
    //
    // Create cut tree structure
    //_______________________________________________________________________________

    // NOTE: All of the functions that are being called under namespace "Lambdas" are defined in lambdas.cc

    // Event Weights
    // At this stage of the cut, we're passing every event and just setting the event weights
    ana.cutflow.addCut("CutWeight", UNITY,              Lambdas::EventWeight);
    //                              ^^^^^               ^^^^^^^^^^^^^^^^^^^^
    //                           Pass all events        apply event weights (see lambdas.cc)

    // Preliminary selections
    ana.cutflow.addCutToLastActiveCut("CutPreliminary", Lambdas::PreliminarySelection, UNITY);

    // Trigger selection
    ana.cutflow.addCutToLastActiveCut("CutTrigger", Lambdas::TriggerSelection, Lambdas::TriggerScaleFactor);

    //===================
    // N lep requirements
    //===================
    // Now adding various lepton channel categorizations based on number of veto/loose/tight leptons
    // The lepton counters are "nVlep", "nLlep", "nTlep" for (veto, loose, tight)
    // Depending on the input.baby_type the loose may have different pt thresholds (cf. https://github.com/cmstas/VVVBabyMaker/blob/866347c30f4f880031e67534563e5e5e379b98cb/dilepbabymaker/ScanChain_v2.cc#L2375)
    // So it is safer to always require proper pt cuts on each leptons, even if it may be redundant

    // Dilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutSRDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutSRDilep", Lambdas::CutSRDilep, Lambdas::LeptonScaleFactor);

    // Trilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutSRTrilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutSRTrilep", Lambdas::CutSRTrilep, Lambdas::LeptonScaleFactor);

    // Three lepton selection for lost-lepton control regions
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutWZCRTrilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutWZCRTrilep", Lambdas::CutCRTrilep, Lambdas::LeptonScaleFactor);

    // Dilep selection for application region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutARDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutARDilep", Lambdas::CutARDilep, UNITY); // No lepton scale factors applied for the application region. (no proper lepton scale factors for loose leptons derived)

    // Trilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutARDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutARTrilep", Lambdas::CutARTrilep, UNITY); // No lepton scale factors applied for the application region. (no proper lepton scale factors for loose leptons derived)

    auto nominal_analysis = [&]()
    {
        //************************************************************************************************************************************************************************************************
        //
        //
        //TTBarDilep CR
	ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("CRTTbarDilep"     , Lambdas::CutCRTTbarDilep  (Variation::JES, Variation::Nominal), UNITY);

        // SIGNAL REGION CUTS
        //
        //
        //************************************************************************************************************************************************************************************************
	//SS2J, SS1J, SFOS channels
	ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("SRSS"           , Lambdas::isSRSSChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), UNITY);
        //ana.cutflow.addCutToLastActiveCut("SRSSeeLowDetaMjjBDT" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS2J3CATFullBDT"  , Lambdas::SRDilepCutBDT2J                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSS");
        ana.cutflow.addCutToLastActiveCut("SRSS1JPreBDT"  , Lambdas::SS1JPreselectionBDT (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JBDT"  , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1J3CATFullBDT"   , Lambdas::SRDilepCutBDT1J                                                         , UNITY);

        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("SRSFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSFOSBDT"    , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSFOS3CATFullBDT"      , Lambdas::SRTrilepCutBDT                                                        , UNITY);


	//////////	
        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("SRSSee"           , Lambdas::isSRSSeeChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeePreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SRSSeeLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjInFull");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//N-1: Nb
        ana.cutflow.getCut("SRSSee");
        ana.cutflow.addCutToLastActiveCut("SRSSeePreSelNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeLowDetaMjjNoNb" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeKinSelNoNb"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInNoNb"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoNb"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoNbAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjInFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoNbNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 Nb
	//N-1 MTmax
	ana.cutflow.getCut("SRSSeeLowDetaMjj");
        ana.cutflow.addCutToLastActiveCut("SRSSeeKinSelNoMTmax"     , Lambdas::SSKinSelNoMTmax        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInNoMTmax"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoMTmax"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoMTmaxAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjInFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoMTmaxNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MTmax
	//N-1 MET
	ana.cutflow.getCut("SRSSeeLowDetaMjj");
        ana.cutflow.addCutToLastActiveCut("SRSSeeKinSelNoMET"     , Lambdas::SSKinSelNoMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInNoMET"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoMET"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoMETAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjInFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullNoMETNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MET




        ana.cutflow.getCut("SRSSee");
        ana.cutflow.addCutToLastActiveCut("SRSSeePreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        //ana.cutflow.addCutToLastActiveCut("SRSSeeLowDetaMjjBDT" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeKinSel");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullAndBDT" , Lambdas::SRDilepCutBDT2JeeMjjOut                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjOutFull");
 	ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//N-1: Nb
        ana.cutflow.getCut("SRSSeeKinSelNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutNoNb"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoNb"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoNbAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjOutFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoNbNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 Nb
	//N-1: MTmax
        ana.cutflow.getCut("SRSSeeKinSelNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutNoMTmax"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoMTmax"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoMTmaxAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjOutFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoMTmaxNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MTmax
	//N-1: MET
        ana.cutflow.getCut("SRSSeeKinSelNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutNoMET"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoMET"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoMETAndBDT"  , Lambdas::SRDilepCutBDT2JeeMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSeeMjjOutFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullNoMETNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JeeMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MET

        ana.cutflow.getCut("SRSSee");
        ana.cutflow.addCutToLastActiveCut("SRSSeePreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutBDT"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSeeMjjOutFullBDT" , Lambdas::SRDilepCutBDT2JeeMjjOut                                                        , UNITY); // Adding one more node with name "<Region>Full"
	
        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("SRSSem"           , Lambdas::isSRSSemChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SRSSemLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjInFull");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//N-1: Nb
        ana.cutflow.getCut("SRSSem");
        ana.cutflow.addCutToLastActiveCut("SRSSemPreSelNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemLowDetaMjjNoNb" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemKinSelNoNb"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInNoNb"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoNb"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoNbAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjInFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoNbNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 Nb
	//N-1: MTmax
        ana.cutflow.getCut("SRSSemLowDetaMjj");
        ana.cutflow.addCutToLastActiveCut("SRSSemKinSelNoMTmax"     , Lambdas::SSKinSelNoMTmax        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInNoMTmax"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoMTmax"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoMTmaxAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjInFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoMTmaxNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MTmax
	//N-1: MET
        ana.cutflow.getCut("SRSSemLowDetaMjj");
        ana.cutflow.addCutToLastActiveCut("SRSSemKinSelNoMET"     , Lambdas::SSKinSelNoMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInNoMET"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoMET"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoMETAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjInFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullNoMETNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MET



        ana.cutflow.getCut("SRSSem");
        ana.cutflow.addCutToLastActiveCut("SRSSemPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        //ana.cutflow.addCutToLastActiveCut("SRSSemLowDetaMjjBDT" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemKinSel");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullAndBDT" , Lambdas::SRDilepCutBDT2JemMjjOut                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjOutFull");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"

	//N-1: Nb
        ana.cutflow.getCut("SRSSemKinSelNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutNoNb"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoNb"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoNbAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjOutFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoNbNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 Nb
	//N-1: MTmax
        ana.cutflow.getCut("SRSSemKinSelNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutNoMTmax"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoMTmax"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoMTmaxAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjOutFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoMTmaxNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MTmax
	//N-1: MET
        ana.cutflow.getCut("SRSSemKinSelNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutNoMET"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoMET"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoMETAndBDT"  , Lambdas::SRDilepCutBDT2JemMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSemMjjOutFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullNoMETNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JemMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MET

        ana.cutflow.getCut("SRSSem");
        ana.cutflow.addCutToLastActiveCut("SRSSemPreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutBDT"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSemMjjOutFullBDT" , Lambdas::SRDilepCutBDT2JemMjjOut                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("SRSSmm"           , Lambdas::isSRSSmmChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SRSSmmLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjInFull");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//N-1: Nb
        ana.cutflow.getCut("SRSSmm");
        ana.cutflow.addCutToLastActiveCut("SRSSmmPreSelNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmLowDetaMjjNoNb" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmKinSelNoNb"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInNoNb"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoNb"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoNbAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjInFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoNbNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 Nb
	//N-1: MTmax
        ana.cutflow.getCut("SRSSmmLowDetaMjj");
        ana.cutflow.addCutToLastActiveCut("SRSSmmKinSelNoMTmax"     , Lambdas::SSKinSelNoMTmax        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInNoMTmax"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoMTmax"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoMTmaxAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjInFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoMTmaxNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MTmax
	//N-1: MET
        ana.cutflow.getCut("SRSSmmLowDetaMjj");
        ana.cutflow.addCutToLastActiveCut("SRSSmmKinSelNoMET"     , Lambdas::SSKinSelNoMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInNoMET"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoMET"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoMETAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjInFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullNoMETNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjIn();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MET


	ana.cutflow.getCut("SRSSmm");
        ana.cutflow.addCutToLastActiveCut("SRSSmmPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        //ana.cutflow.addCutToLastActiveCut("SRSSmmLowDetaMjjBDT" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmKinSel");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullAndBDT" , Lambdas::SRDilepCutBDT2JmmMjjOut                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjOutFull");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"

	//N-1: Nb
        ana.cutflow.getCut("SRSSmmKinSelNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutNoNb"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoNb"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoNbAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjOutFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoNbNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 Nb
	
	//N-1: MTmax
        ana.cutflow.getCut("SRSSmmKinSelNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutNoMTmax"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoMTmax"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoMTmaxAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjOutFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoMTmaxNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MTmax
	
	//N-1: MET
        ana.cutflow.getCut("SRSSmmKinSelNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutNoMET"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoMET"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoMETAndBDT"  , Lambdas::SRDilepCutBDT2JmmMjjOut                                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("SRSSmmMjjOutFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullNoMETNotBDT"  , [&](){ return not Lambdas::SRDilepCutBDT2JmmMjjOut();}                                                       , UNITY); // Adding one more node with name "<Region>Full"
	//end of N-1 MET

        ana.cutflow.getCut("SRSSmm");
        ana.cutflow.addCutToLastActiveCut("SRSSmmPreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutBDT"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSSmmMjjOutFullBDT" , Lambdas::SRDilepCutBDT2JmmMjjOut                                                        , UNITY); // Adding one more node with name "<Region>Full"
        
        ana.cutflow.getCut("SRSSee");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFull"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullAndBDT"   , Lambdas::SRDilepCutBDT1Jee                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JeeFull");
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jee();}                                                         , UNITY);
	// N-1 Nb
        ana.cutflow.getCut("SRSSee");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JPreNoNb"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JKinNoNb"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoNb"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoNbAndBDT"   , Lambdas::SRDilepCutBDT1Jee                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JeeFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoNbNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jee();}                                                         , UNITY);
	// end of N-1 Nb
	// N-1 MTmax
        ana.cutflow.getCut("SRSS1Jee1JPre");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JKinNoMTmax"  , Lambdas::SS1JNoMTmax             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoMTmax"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoMTmaxAndBDT"   , Lambdas::SRDilepCutBDT1Jee                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JeeFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoMTmaxNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jee();}                                                         , UNITY);
	// end of N-1 MTmax
	// N-1 MET
        ana.cutflow.getCut("SRSS1Jee1JPre");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JKinNoMET"  , Lambdas::SS1JNoMET             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoMET"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoMETAndBDT"   , Lambdas::SRDilepCutBDT1Jee                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JeeFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullNoMETNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jee();}                                                         , UNITY);
	// end of N-1 MET

        ana.cutflow.getCut("SRSSem");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFull"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullAndBDT"   , Lambdas::SRDilepCutBDT1Jem                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JemFull");
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jem();}                                                         , UNITY);
	// N-1 Nb
        ana.cutflow.getCut("SRSSem");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JPreNoNb"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JKinNoNb"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoNb"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoNbAndBDT"   , Lambdas::SRDilepCutBDT1Jem                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JemFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoNbNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jem();}                                                         , UNITY);
	// end of N-1 Nb
	// N-1 MTmax
        ana.cutflow.getCut("SRSS1Jem1JPre");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JKinNoMTmax"  , Lambdas::SS1JNoMTmax             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoMTmax"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoMTmaxAndBDT"   , Lambdas::SRDilepCutBDT1Jem                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JemFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoMTmaxNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jem();}                                                         , UNITY);
	// end of N-1 MTmax
	// N-1 MET
        ana.cutflow.getCut("SRSS1Jem1JPre");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JKinNoMET"  , Lambdas::SS1JNoMET             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoMET"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoMETAndBDT"   , Lambdas::SRDilepCutBDT1Jem                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JemFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullNoMETNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jem();}                                                         , UNITY);
	// end of N-1 MET


        ana.cutflow.getCut("SRSSmm");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFull"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullAndBDT"   , Lambdas::SRDilepCutBDT1Jmm                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JmmFull");
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jmm();}                                                         , UNITY);
	// N-1 Nb
        ana.cutflow.getCut("SRSSmm");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JPreNoNb"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JKinNoNb"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoNb"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoNbAndBDT"   , Lambdas::SRDilepCutBDT1Jmm                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JmmFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoNbNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jmm();}                                                         , UNITY);
	// end of N-1 Nb
 	// N-1 MTmax
        ana.cutflow.getCut("SRSS1Jmm1JPre");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JKinNoMTmax"  , Lambdas::SS1JNoMTmax             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoMTmax"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoMTmaxAndBDT"   , Lambdas::SRDilepCutBDT1Jmm                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JmmFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoMTmaxNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jmm();}                                                         , UNITY);
	// end of N-1 MTmax
  	// N-1 MET
        ana.cutflow.getCut("SRSS1Jmm1JPre");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JKinNoMET"  , Lambdas::SS1JNoMET             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoMET"   , UNITY                                                         , UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoMETAndBDT"   , Lambdas::SRDilepCutBDT1Jmm                                                         , UNITY);
        ana.cutflow.getCut("SRSS1JmmFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullNoMETNotBDT"   , [&](){ return not Lambdas::SRDilepCutBDT1Jmm();}                                                         , UNITY);
	// end of N-1 MET
 
        ana.cutflow.getCut("SRSSee");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jee1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeBDT"  , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JeeFullBDT"   , Lambdas::SRDilepCutBDT1Jee                                                         , UNITY);
        ana.cutflow.getCut("SRSSem");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jem1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemBDT"  , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JemFullBDT"   , Lambdas::SRDilepCutBDT1Jem                                                         , UNITY);
        ana.cutflow.getCut("SRSSmm");
        ana.cutflow.addCutToLastActiveCut("SRSS1Jmm1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmBDT"  , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SRSS1JmmFullBDT"   , Lambdas::SRDilepCutBDT1Jmm                                                         , UNITY);


        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("SR0SFOS"          , Lambdas::is0SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFull"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullAndBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR0SFOSFull");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT0SFOS();}                                                        , UNITY);

	//N-1 Nb
        ana.cutflow.getCut("SR0SFOS");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSPreSelNoNb"    , Lambdas::ThreeLepPreselNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSDYVetoNoNb"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSKinSelNoNb"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoNb"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoNbAndBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR0SFOSFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoNbNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT0SFOS();}                                                        , UNITY);
	//end of N-1 Nb
	//N-1 MTmax
        ana.cutflow.getCut("SR0SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSKinSelNoMTmax"    , Lambdas::KinSel3LNoMTmax        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoMTmax"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoMTmaxAndBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR0SFOSFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoMTmaxNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT0SFOS();}                                                        , UNITY);
	//end of N-1 MTmax
	
	//N-1 DPhi3lMET
        ana.cutflow.getCut("SR0SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSKinSelNoDPhi3lMET"    , Lambdas::KinSel3LNoDPhi3lMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoDPhi3lMET"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoDPhi3lMETAndBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR0SFOSFullNoDPhi3lMET");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoDPhi3lMETNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT0SFOS();}                                                        , UNITY);
	//end of N-1 DPhi3lMET

	//N-1 MET
        ana.cutflow.getCut("SR0SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSKinSelNoMET"    , Lambdas::KinSel3LNoMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoMET"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoMETAndBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR0SFOSFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullNoMETNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT0SFOS();}                                                        , UNITY);
	//end of N-1 MET


        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("SR1SFOS"          , Lambdas::is1SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFull"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullAndBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR1SFOSFull");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT1SFOS();}                                                        , UNITY);

	//N-1 Nb
        ana.cutflow.getCut("SR1SFOS");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSPreSelNoNb"    , Lambdas::ThreeLepPreselNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSDYVetoNoNb"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSKinSelNoNb"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoNb"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoNbAndBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR1SFOSFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoNbNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT1SFOS();}                                                        , UNITY);
	//end of N-1 Nb
	//N-1 MTmax
        ana.cutflow.getCut("SR1SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSKinSelNoMTmax"    , Lambdas::KinSel3LNoMTmax        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoMTmax"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoMTmaxAndBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR1SFOSFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoMTmaxNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT1SFOS();}                                                        , UNITY);
	//end of N-1 MTmax
	//N-1 DPhi3lMET
        ana.cutflow.getCut("SR1SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSKinSelNoDPhi3lMET"    , Lambdas::KinSel3LNoDPhi3lMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoDPhi3lMET"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoDPhi3lMETAndBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR1SFOSFullNoDPhi3lMET");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoDPhi3lMETNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT1SFOS();}                                                        , UNITY);
	//end of N-1 DPhi3lMET

	//N-1 MET
        ana.cutflow.getCut("SR1SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSKinSelNoMET"    , Lambdas::KinSel3LNoMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoMET"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoMETAndBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR1SFOSFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullNoMETNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT1SFOS();}                                                        , UNITY);
	//end of N-1 MET



        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("SR2SFOS"          , Lambdas::is2SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFull"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullAndBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR2SFOSFull");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT2SFOS();}                                                        , UNITY);

	//N-1 Nb
        ana.cutflow.getCut("SR2SFOS");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSPreSelNoNb"    , Lambdas::ThreeLepPreselNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSDYVetoNoNb"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSKinSelNoNb"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoNb"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoNbAndBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR2SFOSFullNoNb");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoNbNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT2SFOS();}                                                        , UNITY);
	//end of N-1 Nb
	//N-1 MTmax
        ana.cutflow.getCut("SR2SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSKinSelNoMTmax"    , Lambdas::KinSel3LNoMTmax        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoMTmax"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoMTmaxAndBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR2SFOSFullNoMTmax");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoMTmaxNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT2SFOS();}                                                        , UNITY);
	//end of N-1 MTmax
	//N-1 DPhi3lMET
        ana.cutflow.getCut("SR2SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSKinSelNoDPhi3lMET"    , Lambdas::KinSel3LNoDPhi3lMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoDPhi3lMET"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoDPhi3lMETAndBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR2SFOSFullNoDPhi3lMET");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoDPhi3lMETNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT2SFOS();}                                                        , UNITY);
	//end of N-1 DPhi3lMET

	//N-1 MET
        ana.cutflow.getCut("SR2SFOSDYVeto");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSKinSelNoMET"    , Lambdas::KinSel3LNoMET        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoMET"      , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoMETAndBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                                        , UNITY);
        ana.cutflow.getCut("SR2SFOSFullNoMET");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullNoMETNotBDT"      , [&](){ return not Lambdas::SRTrilepCutBDT2SFOS();}                                                        , UNITY);
	//end of N-1 MET




        ana.cutflow.getCut("SR0SFOS");
        ana.cutflow.addCutToLastActiveCut("SR0SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSBDT"    , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR0SFOSFullBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                                        , UNITY);

        ana.cutflow.getCut("SR1SFOS");
        ana.cutflow.addCutToLastActiveCut("SR1SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSBDT"    , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR1SFOSFullBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                                        , UNITY);

        ana.cutflow.getCut("SR2SFOS");
        ana.cutflow.addCutToLastActiveCut("SR2SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSBDT"    , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("SR2SFOSFullBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                                        , UNITY);


        //************************************************************************************************************************************************************************************************
        //
        //
        // LOST LEPTON CONTROL REGIONS
        //
        //
        //************************************************************************************************************************************************************************************************

        ana.cutflow.getCut("CutWZCRTrilep");
        ana.cutflow.addCutToLastActiveCut("WZCRSSPresel"      , Lambdas::isWZCRSS                                              , UNITY);
        ana.cutflow.getCut("CutWZCRTrilep");
        ana.cutflow.addCutToLastActiveCut("WZCR3LPresel"      , Lambdas::isWZCR3L                                              , UNITY);

        ana.cutflow.getCut("WZCRSSPresel");
        ana.cutflow.addCutToLastActiveCut("WZCRSSee"           , Lambdas::isSRSSeeChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeePreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeFull"       , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("WZCRSSeeKinSel");
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("WZCRSSPresel");
        ana.cutflow.addCutToLastActiveCut("WZCRSSem"           , Lambdas::isSRSSemChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemFull"       , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("WZCRSSemKinSel");
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("WZCRSSPresel");
        ana.cutflow.addCutToLastActiveCut("WZCRSSmm"           , Lambdas::isSRSSmmChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmFull"       , UNITY                                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("WZCRSSmmKinSel");
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        
        ana.cutflow.getCut("WZCRSSee");
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jee1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jee1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JeeFull"   , UNITY                                                         , UNITY);
        ana.cutflow.getCut("WZCRSSem");
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jem1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jem1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JemFull"   , UNITY                                                         , UNITY);
        ana.cutflow.getCut("WZCRSSmm");
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jmm1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jmm1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JmmFull"   , UNITY                                                         , UNITY);

        ana.cutflow.getCut("WZCR3LPresel");
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOS"          , Lambdas::is0SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSDYVeto"    , Lambdas::DYVetoes                                            , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSFull"      , UNITY                                                        , UNITY);

        ana.cutflow.getCut("WZCR3LPresel");
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOS"          , Lambdas::is1SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSDYVeto"    , Lambdas::DYVetoes                                            , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSFull"      , UNITY                                                        , UNITY);

        ana.cutflow.getCut("WZCR3LPresel");
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOS"          , Lambdas::is2SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSDYVeto"    , Lambdas::DYVetoes                                            , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSFull"      , UNITY                                                        , UNITY);

	//WZCR for BDT method
	
        ana.cutflow.getCut("WZCRSSee");
        ana.cutflow.addCutToLastActiveCut("WZCRSSeePreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                             , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("WZCRSSee");
        ana.cutflow.addCutToLastActiveCut("WZCRSSeePreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjOutBDT"         , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjOutFullBDT"     , Lambdas::SRDilepCutBDT2JeeMjjOut                                            , UNITY); // Adding one more node with name "<Region>Full"
 
        ana.cutflow.getCut("WZCRSSem");
        ana.cutflow.addCutToLastActiveCut("WZCRSSemPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                             , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("WZCRSSem");
        ana.cutflow.addCutToLastActiveCut("WZCRSSemPreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjOutBDT"         , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjOutFullBDT"     , Lambdas::SRDilepCutBDT2JemMjjOut                                            , UNITY); // Adding one more node with name "<Region>Full"
      
        ana.cutflow.getCut("WZCRSSmm");
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                             , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("WZCRSSmm");
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmPreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjOutBDT"         , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjOutFullBDT"     , Lambdas::SRDilepCutBDT2JmmMjjOut                                            , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("WZCRSSee");
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jee1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JeeBDT"     , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JeeFullBDT"   , Lambdas::SRDilepCutBDT1Jee                                             , UNITY);

        ana.cutflow.getCut("WZCRSSem");
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jem1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JemBDT"     , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JemFullBDT"   , Lambdas::SRDilepCutBDT1Jem                                             , UNITY);

        ana.cutflow.getCut("WZCRSSmm");
        ana.cutflow.addCutToLastActiveCut("WZCRSS1Jmm1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JmmBDT"     , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCRSS1JmmFullBDT"   , Lambdas::SRDilepCutBDT1Jmm                                             , UNITY);

        ana.cutflow.getCut("WZCR0SFOS");
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSDYVetoBDT"    , Lambdas::DYVetoes                                            , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSBDT"       , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR0SFOSFullBDT"   , Lambdas::SRTrilepCutBDT0SFOS                                           , UNITY);

        ana.cutflow.getCut("WZCR1SFOS");
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSDYVetoBDT"    , Lambdas::DYVetoes                                            , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSBDT"       , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR1SFOSFullBDT"   , Lambdas::SRTrilepCutBDT1SFOS                                           , UNITY);

        ana.cutflow.getCut("WZCR2SFOS");
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSDYVetoBDT"    , Lambdas::DYVetoes                                            , UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSBDT"       , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WZCR2SFOSFullBDT"   , Lambdas::SRTrilepCutBDT2SFOS                                           , UNITY);

        //************************************************************************************************************************************************************************************************
        //
        //
        // APPLICATION REGIONS
        //
        //
        //************************************************************************************************************************************************************************************************

        ana.cutflow.getCut("CutARDilep");
        ana.cutflow.addCutToLastActiveCut("ARSSee"           , Lambdas::isSRSSeeChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeePreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ARSSeeLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("ARSSeeKinSel");
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("CutARDilep");
        ana.cutflow.addCutToLastActiveCut("ARSSem"           , Lambdas::isSRSSemChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ARSSemLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("ARSSemKinSel");
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("CutARDilep");
        ana.cutflow.addCutToLastActiveCut("ARSSmm"           , Lambdas::isSRSSmmChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ARSSmmLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("ARSSmmKinSel");
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        
        ana.cutflow.getCut("ARSSee");
        ana.cutflow.addCutToLastActiveCut("ARSS1Jee1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1Jee1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JeeFull"   , UNITY                                                         , UNITY);
        ana.cutflow.getCut("ARSSem");
        ana.cutflow.addCutToLastActiveCut("ARSS1Jem1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1Jem1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JemFull"   , UNITY                                                         , UNITY);
        ana.cutflow.getCut("ARSSmm");
        ana.cutflow.addCutToLastActiveCut("ARSS1Jmm1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1Jmm1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JmmFull"   , UNITY                                                         , UNITY);

        ana.cutflow.getCut("CutARTrilep");
        ana.cutflow.addCutToLastActiveCut("AR0SFOS"          , Lambdas::is0SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSFull"      , UNITY                                                        , UNITY);

        ana.cutflow.getCut("CutARTrilep");
        ana.cutflow.addCutToLastActiveCut("AR1SFOS"          , Lambdas::is1SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSFull"      , UNITY                                                        , UNITY);

        ana.cutflow.getCut("CutARTrilep");
        ana.cutflow.addCutToLastActiveCut("AR2SFOS"          , Lambdas::is2SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSFull"      , UNITY                                                        , UNITY);

	//Application region for BDT method
	
        ana.cutflow.getCut("ARSSee");
        ana.cutflow.addCutToLastActiveCut("ARSSeePreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ARSSeeKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JeeMjjIn                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("ARSSee");
        ana.cutflow.addCutToLastActiveCut("ARSSeePreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjOutBDT"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSeeMjjOutFullBDT"  , Lambdas::SRDilepCutBDT2JeeMjjOut                                       , UNITY); // Adding one more node with name "<Region>Full"


        ana.cutflow.getCut("ARSSem");
        ana.cutflow.addCutToLastActiveCut("ARSSemPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ARSSemKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JemMjjIn                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("ARSSem");
        ana.cutflow.addCutToLastActiveCut("ARSSemPreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjOutBDT"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSemMjjOutFullBDT"  , Lambdas::SRDilepCutBDT2JemMjjOut                                       , UNITY); // Adding one more node with name "<Region>Full"


        ana.cutflow.getCut("ARSSmm");
        ana.cutflow.addCutToLastActiveCut("ARSSmmPreSelBDT"     , Lambdas::SSPreSelectionBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ARSSmmKinSelBDT"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjInBDT"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjInFullBDT"  , Lambdas::SRDilepCutBDT2JmmMjjIn                                       , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("ARSSmm");
        ana.cutflow.addCutToLastActiveCut("ARSSmmPreSelBDTNoNb"     , Lambdas::SSPreSelectionNoNb  (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmKinSelBDTNoNb"     , Lambdas::SSKinSelBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjOutBDT"      , Lambdas::SSMjjOut         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSSmmMjjOutFullBDT"  , Lambdas::SRDilepCutBDT2JmmMjjOut                                       , UNITY); // Adding one more node with name "<Region>Full"


        ana.cutflow.getCut("ARSSee");
        ana.cutflow.addCutToLastActiveCut("ARSS1Jee1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JeeBDT"       , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal) , UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JeeFullBDT"   , Lambdas::SRDilepCutBDT1Jee                                        , UNITY);

        ana.cutflow.getCut("ARSSem");
        ana.cutflow.addCutToLastActiveCut("ARSS1Jem1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JemBDT"       , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal) , UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JemFullBDT"   , Lambdas::SRDilepCutBDT1Jem                                        , UNITY);

        ana.cutflow.getCut("ARSSmm");
        ana.cutflow.addCutToLastActiveCut("ARSS1Jmm1JPreBDT"  , Lambdas::SS1JPreselectionNoNb (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JmmBDT"       , Lambdas::SS1JBDT             (Variation::JES, Variation::Nominal) , UNITY);
        ana.cutflow.addCutToLastActiveCut("ARSS1JmmFullBDT"   , Lambdas::SRDilepCutBDT1Jmm                                        , UNITY);

        ana.cutflow.getCut("AR0SFOS");
        ana.cutflow.addCutToLastActiveCut("AR0SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                           , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSBDT"          , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("AR0SFOSFullBDT"      , Lambdas::SRTrilepCutBDT0SFOS                                    , UNITY);

        ana.cutflow.getCut("AR1SFOS");
        ana.cutflow.addCutToLastActiveCut("AR1SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                           , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSBDT"          , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("AR1SFOSFullBDT"      , Lambdas::SRTrilepCutBDT1SFOS                                    , UNITY);

        ana.cutflow.getCut("AR2SFOS");
        ana.cutflow.addCutToLastActiveCut("AR2SFOSPreSelBDT"    , Lambdas::ThreeLepPreselBDT  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSDYVetoBDT"    , Lambdas::DYAndZVetoes                                           , UNITY);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSBDT"          , Lambdas::KinSel3LBDT        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("AR2SFOSFullBDT"      , Lambdas::SRTrilepCutBDT2SFOS                                    , UNITY);

        //************************************************************************************************************************************************************************************************
        //
        //
        // N-btag control region (mainly for fakes)
        //
        //
        //************************************************************************************************************************************************************************************************

        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("CRBTagee"           , Lambdas::isSRSSeeChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTageePreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal,true), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("CRBTageeLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTageeKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTageeFull"       , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("CRBTageeMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTageeMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("CRBTageeKinSel");
        ana.cutflow.addCutToLastActiveCut("CRBTageeMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTageeMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("CRBTagem"           , Lambdas::isSRSSemChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagemPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal,true), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("CRBTagemLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagemKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagemFull"       , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("CRBTagemMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagemMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("CRBTagemKinSel");
        ana.cutflow.addCutToLastActiveCut("CRBTagemMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagemMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"

        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("CRBTagmm"           , Lambdas::isSRSSmmChannel                                     , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagmmPreSel"     , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal,true), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("CRBTagmmLowDetaMjj" , Lambdas::LowDEtaMJJ      (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagmmKinSel"     , Lambdas::SSKinSel        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagmmFull"       , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.addCutToLastActiveCut("CRBTagmmMjjIn"      , Lambdas::SSMjjIn         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagmmMjjInFull"  , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        ana.cutflow.getCut("CRBTagmmKinSel");
        ana.cutflow.addCutToLastActiveCut("CRBTagmmMjjOut"     , Lambdas::SSMjjOut        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTagmmMjjOutFull" , UNITY                                                        , UNITY); // Adding one more node with name "<Region>Full"
        
        ana.cutflow.getCut("CRBTagee");
        ana.cutflow.addCutToLastActiveCut("CRBTag1Jee1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal,true), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1Jee1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal),      UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1JeeFull"   , UNITY                                                              , UNITY);
        ana.cutflow.getCut("CRBTagem");
        ana.cutflow.addCutToLastActiveCut("CRBTag1Jem1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal,true), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1Jem1JKin"  , Lambdas::SS1J             (Variation::JES, Variation::Nominal),      UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1JemFull"   , UNITY                                                              , UNITY);
        ana.cutflow.getCut("CRBTagmm");
        ana.cutflow.addCutToLastActiveCut("CRBTag1Jmm1JPre"  , Lambdas::SS1JPreselection (Variation::JES, Variation::Nominal,true), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1Jmm1JKin"  , Lambdas::SS1J            (Variation::JES, Variation::Nominal),       UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1JmmFull"   , UNITY                                                              , UNITY);

        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("CRBTag0SFOS"          , Lambdas::is0SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag0SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal,true), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("CRBTag0SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag0SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag0SFOSFull"      , UNITY                                                        , UNITY);

        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("CRBTag1SFOS"          , Lambdas::is1SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal,true), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("CRBTag1SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag1SFOSFull"      , UNITY                                                        , UNITY);

        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("CRBTag2SFOS"          , Lambdas::is2SFOS                                             , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag2SFOSPreSel"    , Lambdas::ThreeLepPresel  (Variation::JES, Variation::Nominal,true), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("CRBTag2SFOSDYVeto"    , Lambdas::DYAndZVetoes                                        , UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag2SFOSKinSel"    , Lambdas::KinSel3L        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("CRBTag2SFOSFull"      , UNITY                                                        , UNITY);

        //************************************************************************************************************************************************************************************************
        //
        //
        // Further CR
        //
        //
        //************************************************************************************************************************************************************************************************

        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("GammaCR"         , Lambdas::GammaCR         (Variation::JES, Variation::Nominal), UNITY);//inverted MET cut

        ana.cutflow.getCut("CutSRDilep");
        ana.cutflow.addCutToLastActiveCut("SRSSPresel"      , Lambdas::SSPreSelection  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("WWVBSVRHighMJJ"  , Lambdas::HighMJJ         (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.getCut("SRSSPresel");
        ana.cutflow.addCutToLastActiveCut("WWVBSVRHighDEta" , Lambdas::HighDeta        (Variation::JES, Variation::Nominal), UNITY);
        ana.cutflow.addCutToLastActiveCut("WWVBSVR"         , Lambdas::HighMJJ         (Variation::JES, Variation::Nominal), UNITY);

        ana.cutflow.getCut("SRSSPresel");
        ana.cutflow.addCutToLastActiveCut("ttWVRPresel"     , Lambdas::CenJet30Cut     (Variation::JES, Variation::Nominal,4), UNITY);//geq 4j
        ana.cutflow.addCutToLastActiveCut("ttWVRlNBgeq1"    , Lambdas::NBcut           (Variation::JES, Variation::Nominal,1), Lambdas::BTagScaleFactor);//geq 1b (loose)
        ana.cutflow.addCutToLastActiveCut("ttWVRmNBgeq1"    , Lambdas::NBmedcut        (Variation::JES, Variation::Nominal,1), Lambdas::BTagScaleFactor);
        ana.cutflow.addCutToLastActiveCut("ttWVRlNBgeq2"    , Lambdas::NBcut           (Variation::JES, Variation::Nominal,2), Lambdas::BTagScaleFactor);//geq 2b (loose)
        ana.cutflow.addCutToLastActiveCut("ttWVRmNBgeq2"    , Lambdas::NBmedcut        (Variation::JES, Variation::Nominal,2), Lambdas::BTagScaleFactor);

        ana.cutflow.getCut("CutSRTrilep");
        ana.cutflow.addCutToLastActiveCut("ttZWZfitRegion"  , Lambdas::ttZWZfitRegion  (Variation::JES, Variation::Nominal), Lambdas::BTagScaleFactor);

    };

    // Here I create hook for users to add various cuts and histograms of their choice to make their own studies
    // The separation between the main parts and the user_study helps to not make main analysis code too bloated
    // An example of how to add new cuts are shown in template_user_study.h
    // Copy the file template_user_study.h -> user_study.h after implementing user's additional cutflows
    // Then recompile the code and provide the option -u,--user_study as the option to the ./doAnalysis
    // OR just use process.sh script with option -u which will relay the --user_study option to the ./doAnalysis
    if (ana.do_user_study)
    {

        #if __has_include ("user_study.h")
        #include "user_study.h"
        #endif

    }
    // If --user_study option is not provided, it defaults to main analysis
    else
    {

        nominal_analysis();

    }

//*************************************************************************************************************
//
// 6. Book systematic variations
//
//*************************************************************************************************************

    // The systematics can be booked using various funcitons:
    //
    //   RooUtil::Cutflow::addCutSyst
    //   RooUtil::Cutflow::addWgtSyst
    //
    // There are two types of systematics where one only affects the weighting of each events
    // And another that affects which events passes certain cuts or not
    //
    // 1. Weight variations
    //
    //   The addWgtSyst("NameOfWgtSystUpOrDown", <lambda>);
    //
    //   The lambda is the weight that modifies the event weight (i.e. lepsf_up / lepsf) and not just the up variation weight alone (i.e. not lepsf_up alone)
    //
    // 2. Cut variations
    //
    //   This happens in two steps
    //   First, add a variation to a specific cut that gets affected by it
    //   For example, let's say
    //
    //     - SRSS*Pre, SRSS*Nj2, SRSS*LowDetajj, are affected by it.
    //
    //   then one can call, addCutSyst("JESUp", {"Pre", "Nj2", "LowDetajj", ... });
    //   too let RooUtil::Cutflow object know that there are JESUp variations for these cuts
    //   Later, when printCuts() function is called to print the cut structure user can see the booked systematic variations on the right side of the print out.
    //
    //   Then once these variations are booked to each cut, one defines them later using RooUtil::Cutflow::setCutSyst()
    //
    //   setCutSyst("SRSSmmPre", "JESUp", <lambda for cut>, <lambda for weight>);
    //

    if (ana.do_systematics)
    {
        ana.cutflow.addWgtSyst("LepSFUp"    , Lambdas::LepSFVariation     (Variation::Up   ));
        ana.cutflow.addWgtSyst("LepSFDown"  , Lambdas::LepSFVariation     (Variation::Down ));
        ana.cutflow.addWgtSyst("TrigSFUp"   , Lambdas::TriggerSFVariation (Variation::Up   ));
        ana.cutflow.addWgtSyst("TrigSFDown" , Lambdas::TriggerSFVariation (Variation::Down ));
        ana.cutflow.addWgtSyst("BTagLFUp"   , Lambdas::BTagLFVariation    (Variation::Up   ));
        ana.cutflow.addWgtSyst("BTagLFDown" , Lambdas::BTagLFVariation    (Variation::Down ));
        ana.cutflow.addWgtSyst("BTagHFUp"   , Lambdas::BTagHFVariation    (Variation::Up   ));
        ana.cutflow.addWgtSyst("BTagHFDown" , Lambdas::BTagHFVariation    (Variation::Down ));
        ana.cutflow.addWgtSyst("PileupUp"   , Lambdas::PileupVariation    (Variation::Up   ));
        ana.cutflow.addWgtSyst("PileupDown" , Lambdas::PileupVariation    (Variation::Down ));
        ana.cutflow.addWgtSyst("PDFUp"      , Lambdas::PDFVariation       (Variation::Up   ));
        ana.cutflow.addWgtSyst("PDFDown"    , Lambdas::PDFVariation       (Variation::Down ));
        ana.cutflow.addWgtSyst("QsqUp"      , Lambdas::QsqVariation       (Variation::Up   ));
        ana.cutflow.addWgtSyst("QsqDown"    , Lambdas::QsqVariation       (Variation::Down ));
        ana.cutflow.addWgtSyst("AlphaSUp"   , Lambdas::AlphaSVariation    (Variation::Up   ));
        ana.cutflow.addWgtSyst("AlphaSDown" , Lambdas::AlphaSVariation    (Variation::Down ));

        if (ana.do_fake_estimation)
        {
            ana.cutflow.addWgtSyst("FakeUp"              , Lambdas::FakeFactorVariation(Variation::Full        , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeDown"            , Lambdas::FakeFactorVariation(Variation::Full        , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRateUp"          , Lambdas::FakeFactorVariation(Variation::Rate        , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRateDown"        , Lambdas::FakeFactorVariation(Variation::Rate        , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRateElUp"        , Lambdas::FakeFactorVariation(Variation::RateEl      , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRateElDown"      , Lambdas::FakeFactorVariation(Variation::RateEl      , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRateMuUp"        , Lambdas::FakeFactorVariation(Variation::RateMu      , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRateMuDown"      , Lambdas::FakeFactorVariation(Variation::RateMu      , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosureUp"       , Lambdas::FakeFactorVariation(Variation::Closure     , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosureDown"     , Lambdas::FakeFactorVariation(Variation::Closure     , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosureElUp"     , Lambdas::FakeFactorVariation(Variation::ClosureEl   , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosureElDown"   , Lambdas::FakeFactorVariation(Variation::ClosureEl   , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosureMuUp"     , Lambdas::FakeFactorVariation(Variation::ClosureMu   , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosureMuDown"   , Lambdas::FakeFactorVariation(Variation::ClosureMu   , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRateSSElUp"      , Lambdas::FakeFactorVariation(Variation::RateSSEl    , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRateSSElDown"    , Lambdas::FakeFactorVariation(Variation::RateSSEl    , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRateSSMuUp"      , Lambdas::FakeFactorVariation(Variation::RateSSMu    , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRateSSMuDown"    , Lambdas::FakeFactorVariation(Variation::RateSSMu    , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRate3LElUp"      , Lambdas::FakeFactorVariation(Variation::Rate3LEl    , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRate3LElDown"    , Lambdas::FakeFactorVariation(Variation::Rate3LEl    , Variation::Down));
            ana.cutflow.addWgtSyst("FakeRate3LMuUp"      , Lambdas::FakeFactorVariation(Variation::Rate3LMu    , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeRate3LMuDown"    , Lambdas::FakeFactorVariation(Variation::Rate3LMu    , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosureSSElUp"   , Lambdas::FakeFactorVariation(Variation::ClosureSSEl , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosureSSElDown" , Lambdas::FakeFactorVariation(Variation::ClosureSSEl , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosureSSMuUp"   , Lambdas::FakeFactorVariation(Variation::ClosureSSMu , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosureSSMuDown" , Lambdas::FakeFactorVariation(Variation::ClosureSSMu , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosure3LElUp"   , Lambdas::FakeFactorVariation(Variation::Closure3LEl , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosure3LElDown" , Lambdas::FakeFactorVariation(Variation::Closure3LEl , Variation::Down));
            ana.cutflow.addWgtSyst("FakeClosure3LMuUp"   , Lambdas::FakeFactorVariation(Variation::Closure3LMu , Variation::Up  ));
            ana.cutflow.addWgtSyst("FakeClosure3LMuDown" , Lambdas::FakeFactorVariation(Variation::Closure3LMu , Variation::Down));
        }
        else
        {
            ana.cutflow.addWgtSyst("FakeUp"              , UNITY);
            ana.cutflow.addWgtSyst("FakeDown"            , UNITY);
            ana.cutflow.addWgtSyst("FakeRateUp"          , UNITY);
            ana.cutflow.addWgtSyst("FakeRateDown"        , UNITY);
            ana.cutflow.addWgtSyst("FakeRateElUp"        , UNITY);
            ana.cutflow.addWgtSyst("FakeRateElDown"      , UNITY);
            ana.cutflow.addWgtSyst("FakeRateMuUp"        , UNITY);
            ana.cutflow.addWgtSyst("FakeRateMuDown"      , UNITY);
            ana.cutflow.addWgtSyst("FakeRateSSElUp"      , UNITY);
            ana.cutflow.addWgtSyst("FakeRateSSElDown"    , UNITY);
            ana.cutflow.addWgtSyst("FakeRateSSMuUp"      , UNITY);
            ana.cutflow.addWgtSyst("FakeRateSSMuDown"    , UNITY);
            ana.cutflow.addWgtSyst("FakeRate3LElUp"      , UNITY);
            ana.cutflow.addWgtSyst("FakeRate3LElDown"    , UNITY);
            ana.cutflow.addWgtSyst("FakeRate3LMuUp"      , UNITY);
            ana.cutflow.addWgtSyst("FakeRate3LMuDown"    , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureUp"       , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureDown"     , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureElUp"     , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureElDown"   , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureMuUp"     , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureMuDown"   , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureSSElUp"   , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureSSElDown" , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureSSMuUp"   , UNITY);
            ana.cutflow.addWgtSyst("FakeClosureSSMuDown" , UNITY);
            ana.cutflow.addWgtSyst("FakeClosure3LElUp"   , UNITY);
            ana.cutflow.addWgtSyst("FakeClosure3LElDown" , UNITY);
            ana.cutflow.addWgtSyst("FakeClosure3LMuUp"   , UNITY);
            ana.cutflow.addWgtSyst("FakeClosure3LMuDown" , UNITY);
        }

        // Declare cut varying systematics to cuts with the patterns provided in the vector
        ana.cutflow.addCutSyst("JESUp"    , {"jj", "PreSel", "Nj2", "KinSel", "SidemmMET", "OneJet", "NjLeq1", "DRljMin", "1JPre", "1JKin"}, {"Full"});
        ana.cutflow.addCutSyst("JESDown"  , {"jj", "PreSel", "Nj2", "KinSel", "SidemmMET", "OneJet", "NjLeq1", "DRljMin", "1JPre", "1JKin"}, {"Full"});

        // // 2016 v1.2.2 baby ntuple does not have jer variation
        // ana.cutflow.addCutSyst("JER"      , {"jj", "PreSel", "Nj", "KinSel", "SidemmMET"});
        // ana.cutflow.addCutSyst("JERUp"    , {"jj", "PreSel", "Nj", "KinSel", "SidemmMET"});
        // ana.cutflow.addCutSyst("JERDown"  , {"jj", "PreSel", "Nj", "KinSel", "SidemmMET"});

        // Lambda to add variations
        auto set_syst_cuts = [&](TString systname, Variation::ExpSyst expsyst, Variation::Var var)
        {
        ana.cutflow.setCutSyst("SRSSeePreSel"         , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("SRSSeeLowDetaMjj"     , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSeeKinSel"         , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSeeMjjIn"          , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSeeMjjOut"         , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSemPreSel"         , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("SRSSemLowDetaMjj"     , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSemKinSel"         , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSemMjjIn"          , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSemMjjOut"         , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSmmPreSel"         , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("SRSSmmLowDetaMjj"     , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSmmKinSel"         , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSmmMjjIn"          , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSSmmMjjOut"         , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSS1Jee1JPre"        , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSS1Jee1JKin"        , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSS1Jem1JPre"        , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSS1Jem1JKin"        , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSS1Jmm1JPre"        , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SRSS1Jmm1JKin"        , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SR0SFOSPreSel"        , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("SR0SFOSKinSel"        , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SR1SFOSPreSel"        , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("SR1SFOSKinSel"        , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("SR2SFOSPreSel"        , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("SR2SFOSKinSel"        , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSeePreSel"       , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("WZCRSSeeLowDetaMjj"   , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSeeKinSel"       , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSeeMjjIn"        , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSeeMjjOut"       , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSemPreSel"       , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("WZCRSSemLowDetaMjj"   , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSemKinSel"       , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSemMjjIn"        , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSemMjjOut"       , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSmmPreSel"       , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("WZCRSSmmLowDetaMjj"   , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSmmKinSel"       , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSmmMjjIn"        , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSSmmMjjOut"       , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSS1Jee1JPre"      , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSS1Jee1JKin"      , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSS1Jem1JPre"      , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSS1Jem1JKin"      , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSS1Jmm1JPre"      , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCRSS1Jmm1JKin"      , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCR0SFOSPreSel"      , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("WZCR0SFOSKinSel"      , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCR1SFOSPreSel"      , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("WZCR1SFOSKinSel"      , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("WZCR2SFOSPreSel"      , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("WZCR2SFOSKinSel"      , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSeePreSel"         , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("ARSSeeLowDetaMjj"     , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSeeKinSel"         , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSeeMjjIn"          , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSeeMjjOut"         , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSemPreSel"         , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("ARSSemLowDetaMjj"     , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSemKinSel"         , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSemMjjIn"          , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSemMjjOut"         , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSmmPreSel"         , systname, Lambdas::SSPreSelection  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("ARSSmmLowDetaMjj"     , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSmmKinSel"         , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSmmMjjIn"          , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSSmmMjjOut"         , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSS1Jee1JPre"        , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSS1Jee1JKin"        , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSS1Jem1JPre"        , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSS1Jem1JKin"        , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSS1Jmm1JPre"        , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("ARSS1Jmm1JKin"        , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("AR0SFOSPreSel"        , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("AR0SFOSKinSel"        , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("AR1SFOSPreSel"        , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("AR1SFOSKinSel"        , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("AR2SFOSPreSel"        , systname, Lambdas::ThreeLepPresel  (expsyst, var), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("AR2SFOSKinSel"        , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTageePreSel"       , systname, Lambdas::SSPreSelection  (expsyst, var,true), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("CRBTageeLowDetaMjj"   , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTageeKinSel"       , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTageeMjjIn"        , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTageeMjjOut"       , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagemPreSel"       , systname, Lambdas::SSPreSelection  (expsyst, var,true), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("CRBTagemLowDetaMjj"   , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagemKinSel"       , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagemMjjIn"        , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagemMjjOut"       , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagmmPreSel"       , systname, Lambdas::SSPreSelection  (expsyst, var,true), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("CRBTagmmLowDetaMjj"   , systname, Lambdas::LowDEtaMJJ      (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagmmKinSel"       , systname, Lambdas::SSKinSel        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagmmMjjIn"        , systname, Lambdas::SSMjjIn         (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTagmmMjjOut"       , systname, Lambdas::SSMjjOut        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1Jee1JPre"      , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1Jee1JKin"      , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1Jem1JPre"      , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1Jem1JKin"      , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1Jmm1JPre"      , systname, Lambdas::SS1JPreselection(expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1Jmm1JKin"      , systname, Lambdas::SS1J            (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag0SFOSPreSel"    , systname, Lambdas::ThreeLepPresel  (expsyst, var,true), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("CRBTag0SFOSKinSel"    , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag1SFOSPreSel"    , systname, Lambdas::ThreeLepPresel  (expsyst, var,true), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("CRBTag1SFOSKinSel"    , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        ana.cutflow.setCutSyst("CRBTag2SFOSPreSel"    , systname, Lambdas::ThreeLepPresel  (expsyst, var,true), Lambdas::BTagScaleFactor);
        ana.cutflow.setCutSyst("CRBTag2SFOSKinSel"    , systname, Lambdas::KinSel3L        (expsyst, var), UNITY);
        };

        // Actually set the door
        set_syst_cuts("JESUp", Variation::JES, Variation::Up);
        set_syst_cuts("JESDown", Variation::JES, Variation::Down);

        // // If newer year also set JER
        // set_syst_cuts("JER", Variation::JER, Variation::Nominal);
        // set_syst_cuts("JERUp", Variation::JER, Variation::Up);
        // set_syst_cuts("JERDown", Variation::JER, Variation::Down);

    }



//*************************************************************************************************************
//
// 7. Booking histograms and cutflows
//
//*************************************************************************************************************

    // So far we have defined a tree structure of cuts (RooUtil::Cutflow object)
    // Also we defined a list of histograms (RooUtil::Histograms)

    // Now we need to book the histograms for cutflows and variable distribution histograms
    // So during the loop it actually fills them

    // First of all, if the ana.do_systematics == true, we are not going to run all cutflows, nor all histograms
    // We will only run histograms at the very end of the cuts, this is to speed things up

    // NOTE: Booking cutflows generally take longer than booking a lot of histograms only at the end cut level
    // I haven't fully understood why. I think it might be due to the map look up time. (TString EqualTo calls)

    // If --force was provided skip this special if statement and go to else statement and do things normally
    if (ana.do_systematics and not ana.do_force)
    {
        // Book histograms only at the end cuts
        ana.cutflow.bookHistogramsForEndCuts(ana.histograms);

        // And NO book cutflows!
    }
    else
    {

        // Book histograms
        if (ana.do_histograms)
        {
            ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutSRDilep");
            ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutSRTrilep");
            ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutWZCRTrilep");
            ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutARDilep");
            ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutARTrilep");
        }

        // Book cutflows
        if (ana.do_cutflow)
            ana.cutflow.bookCutflows();

        // Book eventlist
        if (ana.do_eventlist)
            ana.cutflow.bookEventLists();

        // Book skim job
        if (ana.do_skim)
        {
            TString output_file_name =ana.output_tfile->GetName();
            output_file_name.ReplaceAll(".root","");
            ana.looper.setSkim(TString::Format("%s_skim.root", output_file_name.Data()));
        }

    }


    //
    // Print cut structure before starting the loop just to visually see it
    //
    // Print once before starting any loop (at this point, "pass|weight" columns will be entirely empty since it's not showing for a any specific event
    ana.cutflow.printCuts();

    //
    // The following function will print out the tree structure for example
    //
    // RooUtil::Cutflow::printCuts();
    //
    // <Program is running>
    // ...
    // ...
    // ...
    // RooUtil:: Cut name                                                     |pass|weight|systs
    // RooUtil:: ======================================================================================
    // RooUtil:: Root                                                         | 0 | 0.000000|
    // RooUtil::   CutWeight                                                  | 0 | 0.000000|
    // RooUtil::     CutPreliminary                                           | 0 | 0.000000|
    // RooUtil::       CutTrigger                                             | 0 | 0.000000|
    // RooUtil::        +CutSRDilep                                           | 0 | 0.000000|
    // RooUtil::        | +SRSSmm                                             | 0 | 0.000000|
    // RooUtil::        | |  SRSSmmTVeto                                      | 0 | 0.000000|
    // RooUtil::        | |    SRSSmmNj2                                      | 0 | 0.000000|
    // RooUtil::        | |      SRSSmmNb0                                    | 0 | 0.000000|
    // RooUtil::        | |        SRSSmmMjjW                                 | 0 | 0.000000|
    // RooUtil::        | |          SRSSmmMjjL                               | 0 | 0.000000|
    // RooUtil::        | |            SRSSmmDetajjL                          | 0 | 0.000000|
    // RooUtil::        | |              SRSSmmMET                            | 0 | 0.000000|
    // RooUtil::        | |                SRSSmmMllSS                        | 0 | 0.000000|
    // RooUtil::        | |                  SRSSmmFull                       | 0 | 0.000000|
    // RooUtil::        | +SRSSem                                             | 0 | 0.000000|
    // RooUtil::        | |  SRSSemTVeto                                      | 0 | 0.000000|
    // RooUtil::        | |    SRSSemNj2                                      | 0 | 0.000000|
    // RooUtil::        | |      SRSSemNb0                                    | 0 | 0.000000|
    // RooUtil::        | |        SRSSemMjjW                                 | 0 | 0.000000|
    // RooUtil::        | |          SRSSemMjjL                               | 0 | 0.000000|
    // RooUtil::        | |            SRSSemDetajjL                          | 0 | 0.000000|
    // RooUtil::        | |              SRSSemMET                            | 0 | 0.000000|
    // RooUtil::        | |                SRSSemMllSS                        | 0 | 0.000000|
    // RooUtil::        | |                  SRSSemMTmax                      | 0 | 0.000000|
    // RooUtil::        | |                    SRSSemFull                     | 0 | 0.000000|
    // RooUtil::        | +SRSSee                                             | 0 | 0.000000|
    // RooUtil::        | |  SRSSeeZeeVt                                      | 0 | 0.000000|
    // RooUtil::        | |    SRSSeeTVeto                                    | 0 | 0.000000|
    // RooUtil::        | |      SRSSeeNj2                                    | 0 | 0.000000|
    // RooUtil::        | |        SRSSeeNb0                                  | 0 | 0.000000|
    // RooUtil::        | |          SRSSeeMjjW                               | 0 | 0.000000|
    // RooUtil::        | |            SRSSeeMjjL                             | 0 | 0.000000|
    // RooUtil::        | |              SRSSeeDetajjL                        | 0 | 0.000000|
    // RooUtil::        | |                SRSSeeMET                          | 0 | 0.000000|
    // RooUtil::        | |                  SRSSeeMllSS                      | 0 | 0.000000|
    // RooUtil::        | |                    SRSSeeFull                     | 0 | 0.000000|
    // ...
    // ...
    // ...
    //
    // (note, the above printout was from an older version of the code, so the cut structure changed a little bit)
    //
    // Also, for debugging purpose, one could print this per event.
    // If printCuts() is called AFTER "RooUtil::Cutflow::fill()" is called,
    // Then, the "pass|weight" columns on the right will be filled with whether at certain cut stage event passes or not.
    // along with event weights
    //

//*************************************************************************************************************
//
// 8. Looping events
//
//*************************************************************************************************************

    while (ana.looper.nextEvent())
    {

        // If a new file was opened after "looper.nextEvent" was called configure the sample dependent settings in class InputConfig;
        if (ana.looper.isNewFileInChain())
        {
            std::cout << "new file in chain" << std::endl;
            input.determine_input_settings(ana.looper.getCurrentFileName(), ana.input_tree_name);
            if (input.year == 2016) fakerates.load2016(); // Not properly implemented
            if (input.year == 2017) fakerates.load2017();
            if (input.year == 2018) fakerates.load2018();
            // Create new skim branches if necessary
            if (ana.do_skim and not (ana.do_systematics and not ana.do_force))
            {
                if (not ana.skim_new_branches_created)
                {
                    ana.skim_new_branches_created = true;
                    ana.tx = new RooUtil::TTreeX(ana.looper.getSkimTree());
                    ana.tx->createBranch<float>("event_weight");
                    ana.tx->createBranch<float>("trigger_scale_factor");
                    ana.tx->createBranch<float>("lepton_scale_factor");
                    ana.tx->createBranch<float>("btag_scale_factor");
                    ana.tx->createBranch<int>("CutSRDilep");
                    ana.tx->createBranch<int>("CRTTbarDilep");
                    ana.tx->createBranch<int>("CutSRTrilep");
                    ana.tx->createBranch<int>("SRSSee");
                    ana.tx->createBranch<int>("SRSSem");
                    ana.tx->createBranch<int>("SRSSmm");
                    ana.tx->createBranch<int>("SRSSeePreSel");
                    ana.tx->createBranch<int>("SRSSemPreSel");
                    ana.tx->createBranch<int>("SRSSmmPreSel");
                    ana.tx->createBranch<int>("SRSS1Jee1JPre");
                    ana.tx->createBranch<int>("SRSS1Jem1JPre");
                    ana.tx->createBranch<int>("SRSS1Jmm1JPre");
                    ana.tx->createBranch<int>("SR0SFOS");
                    ana.tx->createBranch<int>("SR1SFOS");
                    ana.tx->createBranch<int>("SR2SFOS");
                    ana.tx->createBranch<int>("SR0SFOSPreSel");
                    ana.tx->createBranch<int>("SR1SFOSPreSel");
                    ana.tx->createBranch<int>("SR2SFOSPreSel");
                    ana.tx->createBranch<int>("SRSSeeMjjInFull");
                    ana.tx->createBranch<int>("SRSSemMjjInFull");
                    ana.tx->createBranch<int>("SRSSmmMjjInFull");
                    ana.tx->createBranch<int>("SRSSeeMjjOutFull");
                    ana.tx->createBranch<int>("SRSSemMjjOutFull");
                    ana.tx->createBranch<int>("SRSSmmMjjOutFull");
                    ana.tx->createBranch<int>("SRSS1JeeFull");
                    ana.tx->createBranch<int>("SRSS1JemFull");
                    ana.tx->createBranch<int>("SRSS1JmmFull");
                    ana.tx->createBranch<int>("SR0SFOSFull");
                    ana.tx->createBranch<int>("SR1SFOSFull");
                    ana.tx->createBranch<int>("SR2SFOSFull");
                    ana.tx->createBranch<int>("SRSSeeMjjInBDT");
                    ana.tx->createBranch<int>("SRSSemMjjInBDT");
                    ana.tx->createBranch<int>("SRSSmmMjjInBDT");
                    ana.tx->createBranch<int>("SRSSeeMjjOutBDT");
                    ana.tx->createBranch<int>("SRSSemMjjOutBDT");
                    ana.tx->createBranch<int>("SRSSmmMjjOutBDT");
                    ana.tx->createBranch<int>("SRSS1JeeBDT");
                    ana.tx->createBranch<int>("SRSS1JemBDT");
                    ana.tx->createBranch<int>("SRSS1JmmBDT");
                    ana.tx->createBranch<int>("SR0SFOSBDT");
                    ana.tx->createBranch<int>("SR1SFOSBDT");
                    ana.tx->createBranch<int>("SR2SFOSBDT");
                    ana.tx->createBranch<int>("SRSSeeMjjInFullBDT");
                    ana.tx->createBranch<int>("SRSSemMjjInFullBDT");
                    ana.tx->createBranch<int>("SRSSmmMjjInFullBDT");
                    ana.tx->createBranch<int>("SRSSeeMjjOutFullBDT");
                    ana.tx->createBranch<int>("SRSSemMjjOutFullBDT");
                    ana.tx->createBranch<int>("SRSSmmMjjOutFullBDT");
                    ana.tx->createBranch<int>("SRSS1JeeFullBDT");
                    ana.tx->createBranch<int>("SRSS1JemFullBDT");
                    ana.tx->createBranch<int>("SRSS1JmmFullBDT");
                    ana.tx->createBranch<int>("SR0SFOSFullBDT");
                    ana.tx->createBranch<int>("SR1SFOSFullBDT");
                    ana.tx->createBranch<int>("SR2SFOSFullBDT");
		    //variables for BDT input
                    ana.tx->createBranch<float>("lep1Pt");
                    ana.tx->createBranch<float>("lep2Pt");
                    ana.tx->createBranch<float>("lep3Pt");
                    ana.tx->createBranch<float>("lep1pdgId");
                    ana.tx->createBranch<float>("lep2pdgId");
                    ana.tx->createBranch<float>("lep3pdgId");
                    ana.tx->createBranch<float>("jet1Pt");
                    ana.tx->createBranch<float>("jet2Pt");
                    ana.tx->createBranch<float>("jet3Pt");
                    ana.tx->createBranch<float>("jet1BtagScore");
                    ana.tx->createBranch<float>("jet2BtagScore");
                    ana.tx->createBranch<float>("jet3BtagScore");
                    ana.tx->createBranch<float>("BDT_lostlep_prompt_SS2J");
                    ana.tx->createBranch<float>("BDT_lostlep_prompt_SS1J");
                    ana.tx->createBranch<float>("BDT_lostlep_prompt_SFOS");
                    ana.tx->createBranch<float>("BDT_photon_fakes_SS2J");
                    ana.tx->createBranch<float>("BDT_photon_fakes_SS1J");
                    ana.tx->createBranch<float>("BDT_photon_fakes_SFOS");
                    ana.tx->createBranch<float>("BDT_photon_fakes_SS2J_noBtag");
                    ana.tx->createBranch<float>("BDT_photon_fakes_SS1J_noBtag");
                    ana.tx->createBranch<float>("BDT_photon_fakes_SFOS_noBtag");
                }
            }
        }

        // If splitting jobs are requested then determine whether to process the event or not based on remainder
        if (result.count("job_index") and result.count("nsplit_jobs"))
        {
            if (ana.looper.getNEventsProcessed() % ana.nsplit_jobs != (unsigned int) ana.job_index)
                continue;
        }

        // // For memoize function. This is to cache results for each event. this_run/lumi/evt is a global variable defined in lambdas.cc
        // this_run = www.run();
        // this_lumi = www.lumi();
        // this_evt = www.evt();

        // // Theory related weights from h_neventsinfile in each input root file but only set files when new file opens
        // // NOTE if there was a continue statement prior to this it can mess it up
        // if (looper.isNewFileInChain() and not isData) theoryweight.setFile(looper.getCurrentFileName());

        // Set the event list variables for EventList booking
        if (ana.do_eventlist and not (ana.do_systematics and not ana.do_force))
            ana.cutflow.setEventID(www.run(), www.lumi(), www.evt());

        // This magic "fill()" function will now go through all the cut nodes in the RooUtil::Cutflow and evaluate whether it passes the cut or not
        // And also fill histograms for all the booked histograms and fill all the book cutflows
        ana.cutflow.fill();

        // if (ana.cutflow.getCut("SRSSmmFull").pass)
        // {
        //     std::cout << std::endl;
            // std::cout <<  " www.run(): " << www.run() <<  " www.lumi(): " << www.lumi() <<  " www.evt(): " << www.evt() <<  std::endl;
            // std::cout <<  " www.CMS4path(): " << www.CMS4path() <<  " www.CMS4index(): " << www.CMS4index() <<  std::endl;
            // std::cout <<  " Lambdas::EventWeight(): " << Lambdas::EventWeight() <<  std::endl;
            // std::cout <<  " www.lep_pdgId()[0]: " << www.lep_pdgId()[0] <<  " www.lep_pdgId()[1]: " << www.lep_pdgId()[1] <<  std::endl;
            // std::cout <<  " www.lep_motherIdSS()[0]: " << www.lep_motherIdSS()[0] <<  " www.lep_motherIdSS()[1]: " << www.lep_motherIdSS()[1] <<  std::endl;
            // std::cout <<  " www.lep_convVeto()[0]: " << www.lep_convVeto()[0] <<  " www.lep_convVeto()[1]: " << www.lep_convVeto()[1] <<  std::endl;
            // std::cout <<  " www.lep_lostHits()[0]: " << www.lep_lostHits()[0] <<  " www.lep_lostHits()[1]: " << www.lep_lostHits()[1] <<  std::endl;

#ifdef WITHCORE
            // cms4reader.open();
            // cms4reader.printLeptons();
            // cms4reader.printPartonsWithCondition("===All Particles===");
#endif

        // }

        // if (ana.cutflow.getCut("SRSSmmFull").pass || ana.cutflow.getCut("SRSSemFull").pass || ana.cutflow.getCut("SRSSeeFull").pass)
        // {
        //     std::cout <<  " www.lep_pdgId()[0]: " << www.lep_pdgId()[0] <<  " www.lep_pdgId()[1]: " << www.lep_pdgId()[1] <<  std::endl;
        //     std::cout <<  " www.lep_motherIdSS()[0]: " << www.lep_motherIdSS()[0] <<  " www.lep_motherIdSS()[1]: " << www.lep_motherIdSS()[1] <<  std::endl;
        //     std::cout <<  " www.lep_convVeto()[0]: " << www.lep_convVeto()[0] <<  " www.lep_convVeto()[1]: " << www.lep_convVeto()[1] <<  std::endl;
        //     std::cout <<  " www.lep_lostHits()[0]: " << www.lep_lostHits()[0] <<  " www.lep_lostHits()[1]: " << www.lep_lostHits()[1] <<  std::endl;
        // }

        // // Must come after .fill() so that the cuts are all evaulated
        // if (eventlist.has(www.run(), www.lumi(), www.evt()))
        // {
        //     std::cout <<  "***************************" << std::endl;
        //     std::cout <<  "**** Cutflow Challenge ****" << std::endl;
        //     std::cout <<  "***************************" << std::endl;
        //     std::cout <<  " Checking following events:" << std::endl;
        //     std::cout <<  " www.run(): " << www.run() <<  " www.lumi(): " << www.lumi() <<  " www.evt(): " << www.evt() <<  std::endl;
        //     std::cout <<  " Below shows whether it passes or fails the cuts" << std::endl;
        //     cutflow.printCuts();
        // }

        // if (ana.cutflow.getCut("SRSSmmFull").pass)
        // {

        //     float pt0 = www.lep_p4()[0].pt();
        //     float pt1 = www.lep_p4()[1].pt();
        //     float eta0 = www.lep_p4()[0].eta();
        //     float eta1 = www.lep_p4()[1].eta();
        //     float leadeta  = std::min(fabs(eta0), (float)2.39);
        //     float traileta = std::min(fabs(eta1), (float)2.39);
        //     float leadpt   = std::min(pt0, (float)199.);
        //     float trailpt  = std::min(pt1, (float)199.);

        //     float bigeta   = leadeta > traileta ? leadeta  : traileta;
        //     float smalleta = leadeta > traileta ? traileta : leadeta;

        //     // is mm events
        //     if (abs(www.lep_pdgId()[0]) == 13 && abs(www.lep_pdgId()[1]) == 13)
        //     {
        //         // related to lepton legs
        //         float e_l0 = trigsf_mu_lead(leadpt, leadeta);
        //         float e_t1 = trigsf_mu_trail(trailpt, traileta);
        //         float d_l0 = trigsf_mu_lead(leadpt, leadeta, 1) - trigsf_mu_lead(leadpt, leadeta);
        //         float d_t1 = trigsf_mu_trail(trailpt, traileta, 1) - trigsf_mu_trail(trailpt, traileta);
        //         float tempeff = 1.0;
        //         float temperr = 0.0;
        //         std::tie(tempeff, temperr) = getCombinedTrigEffandError(e_l0, 0., 0., e_t1, d_l0, 0., 0., d_t1);
        //         // dz
        //         float dzeff = 0.241 * trigsf_dimu_dz(smalleta, bigeta) + (1 - 0.241) * 1; // Because DZ filter only affects Period H
        //         float dzerr = 0.241 * (trigsf_dimu_dz(smalleta, bigeta, 1) - trigsf_dimu_dz(smalleta, bigeta));
        //         float eff = tempeff * dzeff;
        //         float err = eff * sqrt(pow(temperr / tempeff, 2) + pow(dzerr / dzeff, 2));
        //         // And the fractino of period H is calculated from here: http://www.t2.ucsd.edu/tastwiki/bin/view/CMS/Run2_Data2016
        //         // 8.636 + 0.221 / 36.814 = 0.241

        //         std::cout <<  " tempeff: " << tempeff <<  " temperr: " << temperr <<  std::endl;
        //         std::cout <<  " dzeff: " << dzeff <<  " dzerr: " << dzerr <<  std::endl;
        //         std::cout <<  " eff: " << eff <<  " err: " << err <<  std::endl;
        //         std::cout <<  " (eff+err)/eff: " << (eff+err)/eff <<  " (eff-err)/eff: " << (eff-err)/eff <<  std::endl;

        //         std::cout <<  " www.lep_p4()[0].pt(): " << www.lep_p4()[0].pt() <<  " www.lep_p4()[0].eta(): " << www.lep_p4()[0].eta() <<  " www.lep_pdgId()[0]: " << www.lep_pdgId()[0] <<  std::endl;
        //         std::cout <<  " www.lep_p4()[1].pt(): " << www.lep_p4()[1].pt() <<  " www.lep_p4()[1].eta(): " << www.lep_p4()[1].eta() <<  " www.lep_pdgId()[1]: " << www.lep_pdgId()[1] <<  std::endl;
        //         float trigsf = Lambdas::TriggerScaleFactor();
        //         float trigsfup = Lambdas::TriggerSFVariation(Variation::Up)();
        //         float trigsfdn = Lambdas::TriggerSFVariation(Variation::Down)();
        //         std::cout <<  " trigsf: " << trigsf <<  " trigsfup: " << trigsfup <<  " trigsfdn: " << trigsfdn <<  std::endl;

        //     }
        // }

        if (ana.do_skim and not (ana.do_systematics and not ana.do_force))
        {
            //if (ana.cutflow.getCut("CutSRDilep").pass || ana.cutflow.getCut("CutSRTrilep").pass)
            //if (ana.cutflow.getCut("CRTTbarDilep").pass)
            if (ana.cutflow.getCut("SRSS1JmmFullBDT").pass  || ana.cutflow.getCut("SRSS1JmmFull").pass)
            {
                ana.tx->setBranch<float>("event_weight", Lambdas::EventWeight());
                ana.tx->setBranch<float>("trigger_scale_factor", Lambdas::TriggerScaleFactor());
                ana.tx->setBranch<float>("lepton_scale_factor", Lambdas::LeptonScaleFactor());
                ana.tx->setBranch<float>("btag_scale_factor", Lambdas::BTagScaleFactor());
                ana.tx->setBranch<int>("CutSRDilep", ana.cutflow.getCut("CutSRDilep").pass);
                ana.tx->setBranch<int>("CRTTbarDilep", ana.cutflow.getCut("CRTTbarDilep").pass);
                ana.tx->setBranch<int>("CutSRTrilep", ana.cutflow.getCut("CutSRTrilep").pass);
                ana.tx->setBranch<int>("SRSSee", ana.cutflow.getCut("SRSSee").pass);
                ana.tx->setBranch<int>("SRSSem", ana.cutflow.getCut("SRSSem").pass);
                ana.tx->setBranch<int>("SRSSmm", ana.cutflow.getCut("SRSSmm").pass);
                ana.tx->setBranch<int>("SRSSeePreSel", ana.cutflow.getCut("SRSSeePreSel").pass);
                ana.tx->setBranch<int>("SRSSemPreSel", ana.cutflow.getCut("SRSSemPreSel").pass);
                ana.tx->setBranch<int>("SRSSmmPreSel", ana.cutflow.getCut("SRSSmmPreSel").pass);
                ana.tx->setBranch<int>("SRSS1Jee1JPre", ana.cutflow.getCut("SRSS1Jee1JPre").pass);
                ana.tx->setBranch<int>("SRSS1Jem1JPre", ana.cutflow.getCut("SRSS1Jem1JPre").pass);
                ana.tx->setBranch<int>("SRSS1Jmm1JPre", ana.cutflow.getCut("SRSS1Jmm1JPre").pass);
                ana.tx->setBranch<int>("SR0SFOS", ana.cutflow.getCut("SR0SFOS").pass);
                ana.tx->setBranch<int>("SR1SFOS", ana.cutflow.getCut("SR1SFOS").pass);
                ana.tx->setBranch<int>("SR2SFOS", ana.cutflow.getCut("SR2SFOS").pass);
                ana.tx->setBranch<int>("SR0SFOSPreSel", ana.cutflow.getCut("SR0SFOSPreSel").pass);
                ana.tx->setBranch<int>("SR1SFOSPreSel", ana.cutflow.getCut("SR1SFOSPreSel").pass);
                ana.tx->setBranch<int>("SR2SFOSPreSel", ana.cutflow.getCut("SR2SFOSPreSel").pass);
                ana.tx->setBranch<int>("SRSSeeMjjInFull", ana.cutflow.getCut("SRSSeeMjjInFull").pass);
                ana.tx->setBranch<int>("SRSSemMjjInFull", ana.cutflow.getCut("SRSSemMjjInFull").pass);
                ana.tx->setBranch<int>("SRSSmmMjjInFull", ana.cutflow.getCut("SRSSmmMjjInFull").pass);
                ana.tx->setBranch<int>("SRSSeeMjjOutFull", ana.cutflow.getCut("SRSSeeMjjOutFull").pass);
                ana.tx->setBranch<int>("SRSSemMjjOutFull", ana.cutflow.getCut("SRSSemMjjOutFull").pass);
                ana.tx->setBranch<int>("SRSSmmMjjOutFull", ana.cutflow.getCut("SRSSmmMjjOutFull").pass);
                ana.tx->setBranch<int>("SRSS1JeeFull", ana.cutflow.getCut("SRSS1JeeFull").pass);
                ana.tx->setBranch<int>("SRSS1JemFull", ana.cutflow.getCut("SRSS1JemFull").pass);
                ana.tx->setBranch<int>("SRSS1JmmFull", ana.cutflow.getCut("SRSS1JmmFull").pass);
                ana.tx->setBranch<int>("SR0SFOSFull", ana.cutflow.getCut("SR0SFOSFull").pass);
                ana.tx->setBranch<int>("SR1SFOSFull", ana.cutflow.getCut("SR1SFOSFull").pass);
                ana.tx->setBranch<int>("SR2SFOSFull", ana.cutflow.getCut("SR2SFOSFull").pass);

                ana.tx->setBranch<int>("SRSSeeMjjInBDT", ana.cutflow.getCut("SRSSeeMjjInBDT").pass);
                ana.tx->setBranch<int>("SRSSemMjjInBDT", ana.cutflow.getCut("SRSSemMjjInBDT").pass);
                ana.tx->setBranch<int>("SRSSmmMjjInBDT", ana.cutflow.getCut("SRSSmmMjjInBDT").pass);
                ana.tx->setBranch<int>("SRSSeeMjjOutBDT", ana.cutflow.getCut("SRSSeeMjjOutBDT").pass);
                ana.tx->setBranch<int>("SRSSemMjjOutBDT", ana.cutflow.getCut("SRSSemMjjOutBDT").pass);
                ana.tx->setBranch<int>("SRSSmmMjjOutBDT", ana.cutflow.getCut("SRSSmmMjjOutBDT").pass);
                ana.tx->setBranch<int>("SRSS1JeeBDT", ana.cutflow.getCut("SRSS1JeeBDT").pass);
                ana.tx->setBranch<int>("SRSS1JemBDT", ana.cutflow.getCut("SRSS1JemBDT").pass);
                ana.tx->setBranch<int>("SRSS1JmmBDT", ana.cutflow.getCut("SRSS1JmmBDT").pass);
                ana.tx->setBranch<int>("SR0SFOSBDT", ana.cutflow.getCut("SR0SFOSBDT").pass);
                ana.tx->setBranch<int>("SR1SFOSBDT", ana.cutflow.getCut("SR1SFOSBDT").pass);
                ana.tx->setBranch<int>("SR2SFOSBDT", ana.cutflow.getCut("SR2SFOSBDT").pass);

                ana.tx->setBranch<int>("SRSSeeMjjInFullBDT", ana.cutflow.getCut("SRSSeeMjjInFullBDT").pass);
                ana.tx->setBranch<int>("SRSSemMjjInFullBDT", ana.cutflow.getCut("SRSSemMjjInFullBDT").pass);
                ana.tx->setBranch<int>("SRSSmmMjjInFullBDT", ana.cutflow.getCut("SRSSmmMjjInFullBDT").pass);
                ana.tx->setBranch<int>("SRSSeeMjjOutFullBDT", ana.cutflow.getCut("SRSSeeMjjOutFullBDT").pass);
                ana.tx->setBranch<int>("SRSSemMjjOutFullBDT", ana.cutflow.getCut("SRSSemMjjOutFullBDT").pass);
                ana.tx->setBranch<int>("SRSSmmMjjOutFullBDT", ana.cutflow.getCut("SRSSmmMjjOutFullBDT").pass);
                ana.tx->setBranch<int>("SRSS1JeeFullBDT", ana.cutflow.getCut("SRSS1JeeFullBDT").pass);
                ana.tx->setBranch<int>("SRSS1JemFullBDT", ana.cutflow.getCut("SRSS1JemFullBDT").pass);
                ana.tx->setBranch<int>("SRSS1JmmFullBDT", ana.cutflow.getCut("SRSS1JmmFullBDT").pass);
                ana.tx->setBranch<int>("SR0SFOSFullBDT", ana.cutflow.getCut("SR0SFOSFullBDT").pass);
                ana.tx->setBranch<int>("SR1SFOSFullBDT", ana.cutflow.getCut("SR1SFOSFullBDT").pass);
                ana.tx->setBranch<int>("SR2SFOSFullBDT", ana.cutflow.getCut("SR2SFOSFullBDT").pass);

		//variables for BDT input
                ana.tx->setBranch<float>("lep1Pt", www.lep_pt().size() > 0 ? www.lep_pt()[0]  : -999);
                ana.tx->setBranch<float>("lep2Pt", www.lep_pt().size() > 1 ? www.lep_pt()[1]  : -999);
                ana.tx->setBranch<float>("lep3Pt", www.lep_pt().size() > 2 ? www.lep_pt()[2]  : -999);
                ana.tx->setBranch<float>("lep1pdgId", www.lep_pdgId().size() > 0 ? www.lep_pdgId()[0]  : -999);
                ana.tx->setBranch<float>("lep2pdgId", www.lep_pdgId().size() > 1 ? www.lep_pdgId()[1]  : -999);
                ana.tx->setBranch<float>("lep3pdgId", www.lep_pdgId().size() > 2 ? www.lep_pdgId()[2]  : -999);
                ana.tx->setBranch<float>("jet1Pt", www.jets_p4().size() > 0 ? www.jets_p4()[0].pt()  : -999);
                ana.tx->setBranch<float>("jet2Pt", www.jets_p4().size() > 1 ? www.jets_p4()[1].pt()  : -999);
                ana.tx->setBranch<float>("jet3Pt", www.jets_p4().size() > 2 ? www.jets_p4()[2].pt()  : -999);
                ana.tx->setBranch<float>("jet1BtagScore", www.jets_btag_score().size() > 0 ? www.jets_btag_score()[0]  : -999);
                ana.tx->setBranch<float>("jet2BtagScore", www.jets_btag_score().size() > 1 ? www.jets_btag_score()[1]  : -999);
                ana.tx->setBranch<float>("jet3BtagScore", www.jets_btag_score().size() > 2 ? www.jets_btag_score()[2]  : -999);
                ana.tx->setBranch<float>("BDT_lostlep_prompt_SS2J", VarXGBBDT(0));
                ana.tx->setBranch<float>("BDT_lostlep_prompt_SS1J", VarXGBBDT(1));
                ana.tx->setBranch<float>("BDT_lostlep_prompt_SFOS", VarXGBBDT(2));
                ana.tx->setBranch<float>("BDT_photon_fakes_SS2J", VarXGBBDT(3));
                ana.tx->setBranch<float>("BDT_photon_fakes_SS1J", VarXGBBDT(4));
                ana.tx->setBranch<float>("BDT_photon_fakes_SFOS", VarXGBBDT(5));
                ana.tx->setBranch<float>("BDT_photon_fakes_SS2J_noBtag", VarXGBBDT(6));
                ana.tx->setBranch<float>("BDT_photon_fakes_SS1J_noBtag", VarXGBBDT(7));
                ana.tx->setBranch<float>("BDT_photon_fakes_SFOS_noBtag", VarXGBBDT(8));
                ana.looper.fillSkim();
            }
        }

    }

    // If bookEventLists has been called then print the event lists into a text file for terminating node cuts (i.e. the final selections applied. e.g. SRSSeeFull, ..., etc.)
    if (ana.do_eventlist and not (ana.do_systematics and not ana.do_force))
    {
        std::vector<TString> regions = ana.cutflow.getCut("Root").getEndCuts();
        for (auto& region : regions)
        {
            TString output_tfile_name = ana.output_tfile->GetName(); // get the output file name
            TString suffix = TString::Format(".%s.txt", region.Data());
            output_tfile_name.ReplaceAll(".root", suffix); // replace .root with suffix if .root exists
            if (not output_tfile_name.Contains(suffix)) output_tfile_name += suffix; // if no suffix exists, then append suffix
            ana.cutflow.getCut(region).writeEventList(output_tfile_name);
        }
    }

    // Once done with the loop, now save all the histograms to the output file
    ana.cutflow.saveOutput();

    if (ana.do_skim and not (ana.do_systematics and not ana.do_force))
    {
        ana.looper.getSkimTree()->SetName("t");
        ana.looper.saveSkim();
    }
}

