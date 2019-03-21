#include "main.h"

//_______________________________________________________________________________________________________
int main(int argc, char** argv)
{

//********************************************************************************
//
// 0. Configuration classes
//
//********************************************************************************

    // The following class instance contains configuration that persists through the entire run time.
    // (e.g. number of events, the input file name list, etc. that will not change through run time)
    // (see AnalysisConfig.h to get a feeling)
    AnalysisConfig ana;

    // The following class instance contains configuration that persists only through a single ROOT file in the chain of input ROOT files.
    // Everytime looper loads new file, the configuration in this class is reconfigured to handle sample dependent behaviors.
    // (e.g. is_data? is_sig? is_bkg? etc.)
    // (see InputConfig.h to get a feeling)
    InputConfig input;

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
        ("S,systematics" , "Also consider systematics")
        ("F,fake"        , "The event weight will be multiplied by fake weights")
        ("u,user_study"  , "Enable user_study function for analyzers to make their own studies")
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
        exit(0);
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
    std::cout <<  " ana.do_histograms: " << ana.do_histograms <<  std::endl;
    std::cout <<  " ana.do_systematics: " << ana.do_systematics <<  std::endl;
    std::cout <<  " ana.do_fake_estimation: " << ana.do_fake_estimation <<  std::endl;
    std::cout <<  " ana.do_user_study: " << ana.do_user_study <<  std::endl;
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
// 3. Creating the analysis using RooUtil::Cutflow class (This is a custom class built by P. Chang)
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

    // Set the cutflow object output file
    ana.cutflow.setTFile(ana.output_tfile);

    //_______________________________________________________________________________
    //
    // Create cut tree structure
    //_______________________________________________________________________________

    //==============
    // Event Weights
    //==============
    ana.cutflow.addCut("CutWeight",
            // Cut definition
            UNITY, // At this stage of the cut, we're passing every event and just setting the event weights
            // Weight definition
            [&]()
            {

                float weight = 1;

                // First of all, if it's data events and we're not performing fake estimation thenit's easy the weight is just 1.
                if (input.is_data and not ana.do_fake_estimation)
                    return weight;

                // Various weights are already saved in the TTree for 2016
                // However for 2017 and 2018 they are not saved at the baby stage and need to be accessed at the looper level.
                // The histograms for the weights are in scalefactors/ directory and there are custom reader classes implemented in scalefactors.h/cc 
                // 
                // e.g. The following are the custom scalefactor-histogram-reader classes
                //  LeptonScaleFactors leptonScaleFactors;
                //  FakeRates fakerates;
                //  TheoryWeight theoryweight;
                //  PileupReweight pileupreweight;

                //
                // Pileup reweighting weights
                //
                float purewgt = 1;
                if (input.is_data)
                {
                    purewgt = 1;
                }
                else
                {
                    if (input.year == 2017 or input.year == 2018)
                        purewgt = pileupreweight.purewgt();
                    if (input.year == 2016)
                        purewgt = www.purewgt(); // 2016 ntuples have the weights already defined in the baby ntuples
                }

                //
                // Fake factor (= fake-rate / (1 - fake-rate)) weights 
                //
                float ffwgt = 1;
                if (ana.do_fake_estimation)
                {

                    if (input.year == 2017 or input.year == 2018)
                        ffwgt = fakerates.getFakeFactor();
                    else
                        ffwgt = www.ffwgt(); // 2016 ntuples have the weights already defined in the baby ntuples

                    // Primarily the fake-factor will be applied to the data events
                    // When we are at this point where the do_fake_estimation = true and we're running over background samples
                    // then, it means that we're trying to do "ewk" subtraction (i.e. subtracting prompt contamination in AR)
                    if (input.is_bkg && !www.bkgtype().EqualTo("fakes")) ffwgt *= -1; // subtracting non-fakes
                    if (input.is_bkg &&  www.bkgtype().EqualTo("fakes")) ffwgt *=  0; // do not subtract fakes

                }

                //
                // Integrated luminosity
                //
                float lumi = 1;
                if (input.is_data)
                {
                    lumi = 1;
                }
                else
                {
                    if (input.year == 2016)
                        lumi = 35.9;
                    if (input.year == 2017)
                        lumi = 41.3;
                    if (input.year == 2018)
                        lumi = 59.74;
                }

                // The final weight is then:
                // n.b. In a lot of the cases, ffwgt = 1. cause this is only set when the looper is trying to estimate fake
                weight = www.evt_scale1fb() * purewgt * lumi * ffwgt;

                // Missing k-factor for v1.2.2 2016 baby ntuples (our first public result)
                if (input.do_www_xsec_scaling)
                    weight *= 1.0384615385; // NLO cross section v. MadGraph cross section

                // Return the object
                return weight;

            });

    //=======================
    // Preliminary selections
    //=======================
    ana.cutflow.addCutToLastActiveCut("CutPreliminary",
            // Cut definintion
            [&]()
            {
                bool presel = 1;
                presel &= (www.firstgoodvertex()      == 0);
                presel &= (www.Flag_AllEventFilters() >  0);
                presel &= (www.vetophoton()           == 0);
                presel &= (www.evt_passgoodrunlist()  >  0);
                presel &= (www.nVlep()                >= 2);
                presel &= (www.nLlep()                >= 2);
                return presel;
            },
            // Weight definition
            UNITY
            );

    //==================
    // Trigger selection
    //==================
    ana.cutflow.addCutToLastActiveCut("CutTrigger",
            // Cut definition
            [&]()
            {

                // NOTE: The pass_duplicate_ee_em_mm() variable is a way to remove data duplicate without doing a skimming of all events
                // It determines priority on the trigger selections so that no same events show up in two differen trigger stream
                // See VVVBabyMaker for how the branch is defined

                // Compute trigger variable (TODO for 2016 baby, the tertiary statement may be outdated)
                bool trigger;
                if (input.year == 2017 or input.year == 2018)
                    trigger = www.passTrigger() * www.pass_duplicate_ee_em_mm();
                // TODO THIS NEEDS TO BE UPDATED ONCE WE MOVE TO NEWER 2016 BABY. THE FOLLOWING LINE ONLY WORKS WITH WWW_v1.2.2
                if (input.year == 2016)
                    trigger = passTrigger2016();
                return trigger;
            },
            // Weight definition
            [&]()
            {
                // 2017 and 2018 trigger scale factors are not available yet (have not done the studies yet)
                // For 2016 the trigsf branch in the TTree holds the proper trigger scalefactors
                // TODO UPDATE THIS for 2017 and 2018
                // For now, using 2016 trigger scale factor for 2017/2018 (these are almost identical to 1 anyways...
                return input.is_data ? 1 : www.trigsf();
            });

    //===================
    // N lep requirements
    //===================
    // Now adding various lepton channel categorizations based on number of veto/loose/tight leptons
    // The lepton counters are "nVlep", "nLlep", "nTlep" for (veto, loose, tight)
    // Depending on the input.baby_type the loose may have different pt thresholds (cf. https://github.com/cmstas/VVVBabyMaker/blob/866347c30f4f880031e67534563e5e5e379b98cb/dilepbabymaker/ScanChain_v2.cc#L2375)
    // So it is safer to always require proper pt cuts on each leptons, even if it may be redundant

    // Dilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutSRDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutSRDilep",
            // Cut definition
            [&]()
            {
                // If the looper is looping over to do fake estimation, even though it is "SR dilep" selection require nTlep == 1, nLlep = 2. (i.e. AR)
                // This is to ensure that the histogram outputs will have the same name with proper fake estimation
                if (ana.do_fake_estimation)
                    return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
                else
                    return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
            },
            // Weight definition (lepton scale factors)
            [&] ()
            {
                // the 2017 and 2018 doesn't have lepton scale factors saved to the branches in the WWW ttree
                if (input.year == 2017 or input.year == 2018)
                    return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
                else
                    return www.lepsf();
            });

    // Trilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutSRTrilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutSRTrilep",
            // Cut definition
            [&]()
            {
                // If the looper is looping over to do fake estimation, even though it is "SR trilep" selection require nTlep == 2, nLlep = 3. (i.e. AR)
                // This is to ensure that the histogram outputs will have the same name with proper fake estimation
                if (ana.do_fake_estimation)
                    return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>20.) * (www.lep_pt()[2]>20.);
                else
                    return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>20.) * (www.lep_pt()[2]>20.);
            },
            // Weight definition (lepton scale factors)
            [&] ()
            {
                // the 2017 and 2018 doesn't have lepton scale factors saved to the branches in the WWW ttree
                if (input.year == 2017 or input.year == 2018)
                    return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
                else
                    return www.lepsf();
            });

    // Three lepton selection for lost-lepton control regions
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutWZCRTrilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutWZCRTrilep",
            // Cut definition
            [&]()
            {
                // NOTE: One thing to note here is that even though it is asking for 20/20/20 pt at a later cut stage higher pt cuts will be applied
                // For example, for the lost-lepton control regions for the same-sign channels, out of the 3 leptons it will be required that the two same-sign ones pass same-sign tight ID.
                // When this is required, it will implicitly require that the lep_pt is 25 GeV for the two same-sign leptons. This is a bit vague and could be improved...
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0]>20.) * (www.lep_pt()[1]>20.) * (www.lep_pt()[2]>20.);
            },
            // Weight definition (lepton scale factors)
            [&] ()
            {
                // the 2017 and 2018 doesn't have lepton scale factors saved to the branches in the WWW ttree
                if (input.year == 2017 or input.year == 2018)
                    return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
                else
                    return www.lepsf();
            });

    // Dilep selection for application region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutARDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutARDilep",
            // Cut definition
            [&]()
            {
                // Straight up application region selection. No fake factors are gonna be applied and the application region will be checked with data / MC
                return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
            },
            // No lepton scale factors applied for the application region. (no proper lepton scale factors for loose leptons derived)
            UNITY);

    // Trilep selection for signal region plots
    ana.cutflow.getCut("CutTrigger"); // Retrieve the CutTrigger and add CutARDilep to the CutTrigger node
    ana.cutflow.addCutToLastActiveCut("CutARTrilep",
            // Cut definition
            [&]()
            {
                // Straight up application region selection. No fake factors are gonna be applied and the application region will be checked with data / MC
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>20.) * (www.lep_pt()[2]>20.);
            },
            // Weight definition
            UNITY);

    //************************************************************************************************************************************************************************************************
    //
    //
    //
    // SIGNAL REGION CUTS
    //
    //
    //
    //************************************************************************************************************************************************************************************************

    // Same-sign Mjj on-W region
    ana.cutflow.getCut("CutSRDilep");
    ana.cutflow.addCutToLastActiveCut("SRSSmm"                , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmNj2"             , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmNb0"             , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SRSSmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmMET"             , [&]() { return 1.                                                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSmmFull"            , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutSRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("SRSSem"                , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemNj2"             , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemNb0"             , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SRSSemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemMET"             , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemMllSS"           , [&]() { return www.MllSS()>30.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemMTmax"           , [&]() { return www.MTmax()>90.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSemFull"            , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutSRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("SRSSee"                , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeNj2"             , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeNb0"             , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SRSSeeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                                            ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeMjjL"            , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeDetajjL"         , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeMET"             , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeMllSS"           , [&]() { return www.MllSS()>40.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSeeFull"            , [&]() { return 1                                                                  ; }, UNITY                                 );

    // Same-sign Mjj off-W region
    ana.cutflow.getCut("CutSRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("SRSSSidemm"            , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmNj2"         , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmNb0"         , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmMET"         , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSidemmFull"        , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutSRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("SRSSSideem"            , [&]() { return (www.passSSem())*(www.MllSS()>30.)                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemNj2"         , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemNb0"         , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemMET"         , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemMllSS"       , [&]() { return www.MllSS()>30.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemMTmax"       , [&]() { return www.MTmax()>90.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideemFull"        , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutSRDilep")                                                                                                              ;
    ana.cutflow.addCutToLastActiveCut("SRSSSideee"            , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                             ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeZeeVt"       , [&]() { return fabs(www.MllSS()-91.1876)>10.                                      ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeNj2"         , [&]() { return www.nj30()>= 2                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeNb0"         , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                                           ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeMjjL"        , [&]() { return www.MjjL()<400.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeDetajjL"     , [&]() { return www.DetajjL()<1.5                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeMET"         , [&]() { return www.met_pt()>60.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeMllSS"       , [&]() { return www.MllSS()>40.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SRSSSideeeFull"        , [&]() { return 1                                                                  ; }, UNITY                                 );

    // Trilep regions
    ana.cutflow.getCut("CutSRTrilep")                                                                                                             ;
    ana.cutflow.addCutToLastActiveCut("SR0SFOS"               , [&]() { return (www.nSFOS()==0)                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSPt3l"           , [&]() { return 1.                                                                 ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSMET"            , [&]() { return www.met_pt()>30.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSMll"            , [&]() { return www.Mll3L() > 20.                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSZVt"            , [&]() { return abs(www.Mee3L()-91.1876) > 15.                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSMTmax"          , [&]() { return www.MTmax3L()>90.                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR0SFOSFull"           , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutSRTrilep")                                                                                                             ;
    ana.cutflow.addCutToLastActiveCut("SR1SFOS"               , [&]() { return (www.nSFOS()==1)                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSMET"            , [&]() { return www.met_pt()>40.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSMll"            , [&]() { return www.Mll3L() > 20.                                                  ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                                                ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSMT3rd"          , [&]() { return www.MT3rd()>90.                                                    ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR1SFOSFull"           , [&]() { return 1                                                                  ; }, UNITY                                 );
    ana.cutflow.getCut("CutSRTrilep")                                                                                                             ;
    ana.cutflow.addCutToLastActiveCut("SR2SFOS"               , [&]() { return (www.nSFOS()==2)                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSNj1"            , [&]() { return www.nj()<=1                                                        ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSNb0"            , [&]() { return www.nb()==0                                                        ; }, [&]() { return www.weight_btagsf(); } );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                                     ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                                                ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSMET"            , [&]() { return www.met_pt()>55.                                                   ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSMll"            , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                          ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                                       ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                                                ; }, UNITY                                 );
    ana.cutflow.addCutToLastActiveCut("SR2SFOSFull"           , [&]() { return 1                                                                  ; }, UNITY                                 );

    //************************************************************************************************************************************************************************************************
    //
    //
    //
    // WZ CONTROL REGION CUTS
    //
    //
    //
    //************************************************************************************************************************************************************************************************

    // Same-sign WZ CR
    ana.cutflow.getCut("CutWZCRTrilep");
    ana.cutflow.addCutToLastActiveCut("WZCRSSmm"              , [&]() { return (www.passSSmm())*(www.MllSS()>40.)                            ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmNj2"           , [&]() { return www.nj30()>= 2                                                ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmNb0"           , [&]() { return www.nb()==0                                                   ; }, [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmMjjL"          , [&]() { return www.MjjL()<400.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmDetajjL"       , [&]() { return www.DetajjL()<1.5                                             ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmMET"           , [&]() { return 1.                                                            ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmMllSS"         , [&]() { return www.MllSS()>40.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSmmFull"          , [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.) ; }, UNITY                                  ); 
    ana.cutflow.getCut("CutWZCRTrilep");
    ana.cutflow.addCutToLastActiveCut("WZCRSSem"              , [&]() { return (www.passSSem())*(www.MllSS()>30.)                            ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemNj2"           , [&]() { return www.nj30()>= 2                                                ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemNb0"           , [&]() { return www.nb()==0                                                   ; }, [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemMjjL"          , [&]() { return www.MjjL()<400.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemDetajjL"       , [&]() { return www.DetajjL()<1.5                                             ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemMET"           , [&]() { return www.met_pt()>60.                                              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemMllSS"         , [&]() { return www.MllSS()>30.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemMTmax"         , [&]() { return www.MTmax()>90.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSemFull"          , [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.) ; }, UNITY                                  ); 
    ana.cutflow.getCut("CutWZCRTrilep");
    ana.cutflow.addCutToLastActiveCut("WZCRSSee"              , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)                        ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeZeeVt"         , [&]() { return fabs(www.MllSS()-91.1876)>10.                                 ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeTVeto"         , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeNj2"           , [&]() { return www.nj30()>= 2                                                ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeNb0"           , [&]() { return www.nb()==0                                                   ; }, [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeMjjL"          , [&]() { return www.MjjL()<400.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeDetajjL"       , [&]() { return www.DetajjL()<1.5                                             ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeMET"           , [&]() { return www.met_pt()>60.                                              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeMllSS"         , [&]() { return www.MllSS()>40.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCRSSeeFull"          , [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.) ; }, UNITY                                  ); 

    // Mjj selection validation region
    ana.cutflow.getCut("WZCRSSeeMllSS");
    ana.cutflow.addCutToLastActiveCut("WZVRSSee"    , [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.);} ,  [&]() { return 1; } );
    ana.cutflow.addCutToLastActiveCut("WZVRSSeeFull", [&]() { return fabs(www.Mjj()-80.)<15.; } ,  [&]() { return 1; } );
    ana.cutflow.getCut("WZCRSSemMTmax");
    ana.cutflow.addCutToLastActiveCut("WZVRSSem"    , [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.);} ,  [&]() { return 1; } );
    ana.cutflow.addCutToLastActiveCut("WZVRSSemFull", [&]() { return fabs(www.Mjj()-80.)<15.; } ,  [&]() { return 1; } );
    ana.cutflow.getCut("WZCRSSmmMllSS");
    ana.cutflow.addCutToLastActiveCut("WZVRSSmm"    , [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.);} ,  [&]() { return 1; } );
    ana.cutflow.addCutToLastActiveCut("WZVRSSmmFull", [&]() { return fabs(www.Mjj()-80.)<15.; } ,  [&]() { return 1; } );

    // Trilep WZ CR
    ana.cutflow.getCut("CutWZCRTrilep");
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOS"             , [&]() { return (www.nSFOS()==1)                                              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSNj1"          , [&]() { return www.nj()<=1                                                   ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSNb0"          , [&]() { return www.nb()==0                                                   ; }, [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSPt3l"         , [&]() { return www.Pt3l()>60.                                                ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                           ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSMET"          , [&]() { return www.met_pt()>40.                                              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSMll"          , [&]() { return www.Mll3L() > 20.                                             ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                  ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSMT3rd"        , [&]() { return www.MT3rd()>90.                                               ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSZVt"          , [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.) ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR1SFOSFull"         , [&]() { return 1                                                             ; }, UNITY                                  ); 
    ana.cutflow.getCut("CutWZCRTrilep");
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOS"             , [&]() { return (www.nSFOS()==2)                                              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSNj1"          , [&]() { return www.nj()<=1                                                   ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSNb0"          , [&]() { return www.nb()==0                                                   ; }, [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSPt3l"         , [&]() { return www.Pt3l()>60.                                                ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSDPhi3lMET"    , [&]() { return www.DPhi3lMET()>2.5                                           ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSMET"          , [&]() { return www.met_pt()>55.                                              ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSMll"          , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)                     ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSM3l"          , [&]() { return abs(www.M3l()-91.1876) > 10.                                  ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSZVt"          , [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.) ; }, UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("WZCR2SFOSFull"         , [&]() { return 1                                                             ; }, UNITY                                  ); 

    // Invert met_pt
    ana.cutflow.getCut("WZCR1SFOSNb0");
    ana.cutflow.addCutToLastActiveCut("WZVR1SFOSMllOnOff"     , [&]() { return ((www.Pt3l()<60.)+(www.DPhi3lMET()<2.5)+(www.met_pt()<40.)+(www.MT3rd()<90.))*(www.Mll3L()>20.)*(abs(www.M3l()-91.1876)>10.) ; } , [&]() { return 1 ; } ) ;
    ana.cutflow.addCutToLastActiveCut("WZVR1SFOSMllOnOffFull" , [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.)                       ; } , [&]() { return 1 ; } ) ;
    ana.cutflow.getCut("WZCR2SFOSNb0");
    ana.cutflow.addCutToLastActiveCut("WZVR2SFOSMllOnOff"     , [&]() { return ((www.Pt3l()<60.)+(www.DPhi3lMET()<2.5)+(www.met_pt()<55.))*((www.Mll3L()>20.&&www.Mll3L1()>20.))*(abs(www.M3l()-91.1876)>10.) ; } , [&]() { return 1 ; } ) ;
    ana.cutflow.addCutToLastActiveCut("WZVR2SFOSMllOnOffFull" , [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.)                         ; } , [&]() { return 1 ; } ) ;

    //************************************************************************************************************************************************************************************************
    //
    //
    //
    // APPLICATION REGION CUTS
    //
    //
    //
    //************************************************************************************************************************************************************************************************

    // Same-sign Mjj on-W region
    ana.cutflow.getCut("CutARDilep");
    ana.cutflow.addCutToLastActiveCut("ARSSmm"                , [&]() { return (www.passSSmm())*(www.MllSS()>40.)               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmNj2"             , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmNb0"             , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                          ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmMjjL"            , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmDetajjL"         , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmMET"             , [&]() { return 1.                                               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmMllSS"           , [&]() { return www.MllSS()>40.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSmmFull"            , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutARDilep");
    ana.cutflow.addCutToLastActiveCut("ARSSem"                , [&]() { return (www.passSSem())*(www.MllSS()>30.)               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemNj2"             , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemNb0"             , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                          ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemMjjL"            , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemDetajjL"         , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemMET"             , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemMllSS"           , [&]() { return www.MllSS()>30.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemMTmax"           , [&]() { return www.MTmax()>90.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSemFull"            , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutARDilep");
    ana.cutflow.addCutToLastActiveCut("ARSSee"                , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)           ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeZeeVt"           , [&]() { return fabs(www.MllSS()-91.1876)>10.                    ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeTVeto"           , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeNj2"             , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeNb0"             , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeMjjW"            , [&]() { return fabs(www.Mjj()-80.)<15.                          ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeMjjL"            , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeDetajjL"         , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeMET"             , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeMllSS"           , [&]() { return www.MllSS()>40.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSeeFull"            , [&]() { return 1                                                ; }        , UNITY                                  ); 

    // Same-sign Mjj off-W region
    ana.cutflow.getCut("CutARDilep");
    ana.cutflow.addCutToLastActiveCut("ARSSSidemm"            , [&]() { return (www.passSSmm())*(www.MllSS()>40.)               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmNj2"         , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmNb0"         , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                         ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmMjjL"        , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmDetajjL"     , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmMET"         , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmMllSS"       , [&]() { return www.MllSS()>40.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSidemmFull"        , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutARDilep");
    ana.cutflow.addCutToLastActiveCut("ARSSSideem"            , [&]() { return (www.passSSem())*(www.MllSS()>30.)               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemNj2"         , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemNb0"         , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                         ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemMjjL"        , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemDetajjL"     , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemMET"         , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemMllSS"       , [&]() { return www.MllSS()>30.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemMTmax"       , [&]() { return www.MTmax()>90.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideemFull"        , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutARDilep");
    ana.cutflow.addCutToLastActiveCut("ARSSSideee"            , [&]() { return (www.passSSee())*(1)*(www.MllSS()>40.)           ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeZeeVt"       , [&]() { return fabs(www.MllSS()-91.1876)>10.                    ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeTVeto"       , [&]() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeNj2"         , [&]() { return www.nj30()>= 2                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeNb0"         , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeMjjW"        , [&]() { return fabs(www.Mjj()-80.)>=15.                         ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeMjjL"        , [&]() { return www.MjjL()<400.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeDetajjL"     , [&]() { return www.DetajjL()<1.5                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeMET"         , [&]() { return www.met_pt()>60.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeMllSS"       , [&]() { return www.MllSS()>40.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("ARSSSideeeFull"        , [&]() { return 1                                                ; }        , UNITY                                  ); 

    // Trilep regions
    ana.cutflow.getCut("CutARTrilep");
    ana.cutflow.addCutToLastActiveCut("AR0SFOS"               , [&]() { return (www.nSFOS()==0)                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSNj1"            , [&]() { return www.nj()<=1                                      ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSNb0"            , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSPt3l"           , [&]() { return 1.                                               ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSMET"            , [&]() { return www.met_pt()>30.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSMll"            , [&]() { return www.Mll3L() > 20.                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                     ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSZVt"            , [&]() { return abs(www.Mee3L()-91.1876) > 15.                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSMTmax"          , [&]() { return www.MTmax3L()>90.                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR0SFOSFull"           , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutARTrilep");
    ana.cutflow.addCutToLastActiveCut("AR1SFOS"               , [&]() { return (www.nSFOS()==1)                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSNj1"            , [&]() { return www.nj()<=1                                      ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSNb0"            , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSMET"            , [&]() { return www.met_pt()>40.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSMll"            , [&]() { return www.Mll3L() > 20.                                ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                     ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSMT3rd"          , [&]() { return www.MT3rd()>90.                                  ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR1SFOSFull"           , [&]() { return 1                                                ; }        , UNITY                                  ); 
    ana.cutflow.getCut("CutARTrilep");
    ana.cutflow.addCutToLastActiveCut("AR2SFOS"               , [&]() { return (www.nSFOS()==2)                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSNj1"            , [&]() { return www.nj()<=1                                      ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSNb0"            , [&]() { return www.nb()==0                                      ; }        , [&]() { return www.weight_btagsf() ; } ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSPt3l"           , [&]() { return www.Pt3l()>60.                                   ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSDPhi3lMET"      , [&]() { return www.DPhi3lMET()>2.5                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSMET"            , [&]() { return www.met_pt()>55.                                 ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSMll"            , [&]() { return (www.Mll3L() > 20. && www.Mll3L1() > 20.)        ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSM3l"            , [&]() { return abs(www.M3l()-91.1876) > 10.                     ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSZVt"            , [&]() { return www.nSFOSinZ() == 0                              ; }        , UNITY                                  ); 
    ana.cutflow.addCutToLastActiveCut("AR2SFOSFull"           , [&]() { return 1                                                ; }        , UNITY                                  ); 


//********************************************************************************
//
// 4. Defining histograms
//
//********************************************************************************

    // The RooUtil::Histograms class holds the definitions of histograms with the lambda expression for the variable
    // Then this is used in conjunction with RooUtil::Cutflow to book histograms at different cut stage
    // This is so that the users don't have to copy paste a thousands lines of codes if they want to book more histograms at different cut stages

    ana.histograms.addHistogram("MllSS"                    ,  180 , 0.      , 300.   , [&]() { return www.MllSS()                  ; });
    ana.histograms.addHistogram("MllSS_wide"               ,  180 , 0.      , 2000.  , [&]() { return www.MllSS()                  ; });
    ana.histograms.addHistogram("MllZ"                     ,  180 , 60.     , 120.   , [&]() { return www.MllSS()                  ; });
    ana.histograms.addHistogram("MllZZoom"                 ,  180 , 80.     , 100.   , [&]() { return www.MllSS()                  ; });
    ana.histograms.addHistogram("MllOnOff"                 ,  180 , 30.     , 150.   , [&]() { return fabs(www.Mll3L()-91.1876)<fabs(www.Mll3L1()-91.1876)?www.Mll3L():www.Mll3L1(); });
    ana.histograms.addHistogram("Mll3L"                    ,  180 , 0.      , 300.   , [&]() { return www.Mll3L()                  ; });
    ana.histograms.addHistogram("Mll3L1"                   ,  180 , 0.      , 300.   , [&]() { return www.Mll3L1()                 ; });
    ana.histograms.addHistogram("nSFOSinZ"                 ,  3   , 0.      , 3.     , [&]() { return www.nSFOSinZ()               ; });
    ana.histograms.addHistogram("M3l"                      ,  180 , 0.      , 150.   , [&]() { return www.M3l()                    ; });
    ana.histograms.addHistogram("Pt3lGCR"                  ,  180 , 0.      , 100.   , [&]() { return www.Pt3l()                   ; });
    ana.histograms.addHistogram("Pt3l"                     ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                   ; });
    ana.histograms.addHistogram("Ptll"                     ,  180 , 0.      , 300.   , [&]() { return www.Pt3l()                   ; });
    ana.histograms.addHistogram("nvtx"                     ,  60  , 0.      , 60.    , [&]() { return www.nVert()                  ; });
    ana.histograms.addHistogram("MjjZoom"                  ,  180 , 0.      , 150.   , [&]() { return www.Mjj()                    ; });
    ana.histograms.addHistogram("Mjj"                      ,  180 , 0.      , 300.   , [&]() { return www.Mjj()                    ; });
    ana.histograms.addHistogram("MjjL"                     ,  180 , 0.      , 750.   , [&]() { return www.MjjL()                   ; });
    ana.histograms.addHistogram("DetajjL"                  ,  180 , 0.      , 5.     , [&]() { return www.DetajjL()                ; });
    ana.histograms.addHistogram("MjjVBF"                   ,  180 , 0.      , 750.   , [&]() { return www.MjjVBF()                 ; });
    ana.histograms.addHistogram("DetajjVBF"                ,  180 , 0.      , 8.     , [&]() { return www.DetajjVBF()              ; });
    ana.histograms.addHistogram("MjjVBS"                   ,  180 , 0.      , 750.   , [&]() { return www.Mjj()                    ; });
    ana.histograms.addHistogram("DetajjVBS"                ,  180 , 0.      , 3.     , [&]() { return www.DetajjL()                ; });
    ana.histograms.addHistogram("MET"                      ,  180 , 0.      , 180.   , [&]() { return www.met_pt()                 ; });
    ana.histograms.addHistogram("METWide"                  ,  180 , 0.      , 300.   , [&]() { return www.met_pt()                 ; });
    ana.histograms.addHistogram("jets_pt0"                 ,  180 , 0.      , 250    , [&]() { return www.jets_p4()[0].pt()        ; });
    ana.histograms.addHistogram("jets_pt1"                 ,  180 , 0.      , 150    , [&]() { return www.jets_p4()[1].pt()        ; });
    ana.histograms.addHistogram("jets_pt2"                 ,  180 , 0.      , 150    , [&]() { return www.jets_p4()[2].pt()        ; });
    ana.histograms.addHistogram("jets_eta0"                ,  180 , -5.0    , 5.0    , [&]() { return www.jets_p4()[0].eta()       ; });
    ana.histograms.addHistogram("jets_eta1"                ,  180 , -5.0    , 5.0    , [&]() { return www.jets_p4()[1].eta()       ; });
    ana.histograms.addHistogram("jets_eta2"                ,  180 , -5.0    , 5.0    , [&]() { return www.jets_p4()[2].eta()       ; });
    ana.histograms.addHistogram("lep_pt0"                  ,  180 , 0.      , 250    , [&]() { return www.lep_pt()[0]              ; });
    ana.histograms.addHistogram("lep_pt1"                  ,  180 , 0.      , 150    , [&]() { return www.lep_pt()[1]              ; });
    ana.histograms.addHistogram("lep_pt2"                  ,  180 , 0.      , 150    , [&]() { return www.lep_pt()[2]              ; });
    ana.histograms.addHistogram("lep_eta0"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_eta()[0]             ; });
    ana.histograms.addHistogram("lep_eta1"                 ,  180 , -2.5    , 2.5    , [&]() { return www.lep_eta()[1]             ; });
    ana.histograms.addHistogram("lep_phi0"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_phi()[0]             ; });
    ana.histograms.addHistogram("lep_phi1"                 ,  180 , -3.1416 , 3.1416 , [&]() { return www.lep_phi()[1]             ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Lep0"     ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[0] ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Lep1"     ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[1] ; });
    ana.histograms.addHistogram("lep_relIso03EAv2Lep2"     ,  180 , 0.0     , 0.2    , [&]() { return www.lep_relIso03EAv2Lep()[2] ; });
    ana.histograms.addHistogram("nj"                       ,  7   , 0.      , 7.     , [&]() { return www.nj()                     ; });
    ana.histograms.addHistogram("nj30"                     ,  7   , 0.      , 7.     , [&]() { return www.nj30()                   ; });
    ana.histograms.addHistogram("nb"                       ,  5   , 0.      , 5.     , [&]() { return www.nb()                     ; });
    ana.histograms.addHistogram("MTmin"                    ,  180 , 0.      , 300.   , [&]() { return www.MTmin()                  ; });
    ana.histograms.addHistogram("MTmax"                    ,  180 , 0.      , 300.   , [&]() { return www.MTmax()                  ; });
    ana.histograms.addHistogram("MTmax3L"                  ,  180 , 0.      , 300.   , [&]() { return www.MTmax3L()                ; });
    ana.histograms.addHistogram("MT3rd"                    ,  180 , 0.      , 300.   , [&]() { return www.MT3rd()                  ; });

    // Because it uses lambda you can compute much more complicated variables on the fly
    // Let's define a complex histogram. (This is a variable Yifan is looking into.)
    // This is going to plot a new variable where it plots the minimum DR of the two opposite sign leptons.
    // This is the variable that WH->WW analysis in HIG uses to fit to extract signal.
    //
    // If the user expects the function to be computationally heavy you can either use memoization or static variables to cache results
    // The example below illustrates this
    ana.histograms.addHistogram("minDRllOS", 180, 0., 4.,
            [&]()
            {
                // To cache result the caching will be determined by run/lumi/evt of the event
                // run/lumi/evt can provide unique identifier per event. (upto within the same sample.)
                // Since this program MAY run over multiple different samples, there is a very very miniscule
                // chance that run/lumi/evt is SAME between the last event of a sample to the first event of another sample.
                // But the rate of such occurence is probably faster than proton decay.... or something like that. idk...
                static float result;
                static int run;
                static int lumi;
                static unsigned long long evt;

                // Check if I can just use cached result
                if (www.run() == run and www.lumi() == lumi and www.evt() == evt)
                {
                    return result;
                }

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

                // Cache result
                result = minDR;
                run = www.run();
                lumi = www.lumi();
                evt = www.evt();

                return result;
            });

//*************************************************************************************************************
//
// 5. User customization on cutflows
//
//*************************************************************************************************************

    // Here I create hook for users to add various cuts and histograms of their choice to make their own studies
    // The separation between the main parts and the user_study helps to not make main analysis code too bloated
    // An example of how to add new cuts are shown in template_user_study.h
    // Copy the file template_user_study.h -> user_study.h after implementing user's additional cutflows
    // Then recompile the code and provide the option -u,--user_study as the option to the ./doAnalysis
    // OR just use process.sh script with option -u which will relay the --user_study option to the ./doAnalysis
    auto user_study = [&] ()
    {
        #if __has_include ("user_study.h")
        #include "user_study.h"
        #endif
    };

    if (ana.do_user_study)
        user_study();

//*************************************************************************************************************
//
// 6. Booking histograms and cutflows
//
//*************************************************************************************************************

    // So far we have defined a tree structure of cuts (RooUtil::Cutflow object)
    // Also we defined a list of histograms (RooUtil::Histograms)

    // Book histograms
    ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutSRDilep");
    ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutSRTrilep");
    ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutWZCRTrilep");
    ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutARDilep");
    ana.cutflow.bookHistogramsForCutAndBelow(ana.histograms, "CutARTrilep");

    //
    // Print cut structure before starting the loop just to visually see it
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
    // Also, for debugging purpose, one could print this per event.
    // If printCuts() is called AFTER "RooUtil::Cutflow::fill()" is called,
    // Then, the "pass|weight" columns on the right will be filled with whether at certain cut stage event passes or not.
    // along with event weights
    //
    // NOTE: TODO: Implement systematic variations
    // The "systs" columns will be more advanced usage when we get to dealing with systematics
    // Right now, I turned this off (March 19) while cleaning up the code since systematics can make the code run a lot more slower.
    //

    // Book cutflows
    ana.cutflow.bookCutflows();

    // Print once before starting any loop (at this point, "pass|weight" columns will be entirely empty since it's not showing for a any specific event
    ana.cutflow.printCuts();

//*************************************************************************************************************
//
// 7. Looping events
//
//*************************************************************************************************************

    while (ana.looper.nextEvent())
    {

        // If a new file was opened after "looper.nextEvent" was called configure the sample dependent settings in class InputConfig;
        if (ana.looper.isNewFileInChain())
        {
            input.determine_input_settings(ana.looper.getCurrentFileName(), ana.input_tree_name);
        }

        // // Theory related weights from h_neventsinfile in each input root file but only set files when new file opens
        // // NOTE if there was a continue statement prior to this it can mess it up
        // if (looper.isNewFileInChain() and not isData) theoryweight.setFile(looper.getCurrentFileName());

        // // Set the event list variables
        // cutflow.setEventID(www.run(), www.lumi(), www.evt());

        // This magic "fill()" function will now go through all the cut nodes in the RooUtil::Cutflow and evaluate whether it passes the cut or not
        // And also fill histograms for all the booked histograms and fill all the book cutflows
        ana.cutflow.fill();

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

    }

    // Once done with the loop, now save all the histograms to the output file
    ana.cutflow.saveOutput();

}

//_______________________________________________________________________________________________________
// The trigger requirement for the 2016 was done in the following way
// This was later moved to the VVVBabyMaker, and is no longer needed
// However for the baby version v1.2.2 which is the version used for the public result didn't have this selection implemented in a TTree branch
// So the looper has this
bool passTrigger2016()
{
    if (www.nLlep() < 2)
        return false;

    const vector<int>& lep_pdgId = www.lep_pdgId();
    const int mc_HLT_DoubleEl    = www.mc_HLT_DoubleEl();
    const int mc_HLT_DoubleEl_DZ = www.mc_HLT_DoubleEl_DZ();
    const int mc_HLT_MuEG        = www.mc_HLT_MuEG();
    const int mc_HLT_DoubleMu    = www.mc_HLT_DoubleMu();
    const int nVlep              = www.nVlep();
    const int nLlep              = www.nLlep();


    if (nVlep != 2 && nVlep != 3)
        return 0;

    if (nLlep != 2 && nLlep != 3)
        return 0;

    if (lep_pdgId.size() < 2)
        return 0;

    if (nVlep == 2 && nLlep == 2)
    {
        int lepprod = lep_pdgId.at(0)*lep_pdgId.at(1);
        if (abs(lepprod) == 121)
            return (mc_HLT_DoubleEl || mc_HLT_DoubleEl_DZ);
        else if (abs(lepprod) == 143)
            return mc_HLT_MuEG;
        else if (abs(lepprod) == 169)
            return mc_HLT_DoubleMu;
        else
            return 0;
    }
    else if (nVlep == 3 && nLlep == 3)
    {
        int lepprod01 = lep_pdgId.at(0)*lep_pdgId.at(1);
        if (abs(lepprod01) == 121 && (mc_HLT_DoubleEl || mc_HLT_DoubleEl_DZ))
            return true;
        else if (abs(lepprod01) == 143 && mc_HLT_MuEG)
            return true;
        else if (abs(lepprod01) == 169 && mc_HLT_DoubleMu)
            return true;

        int lepprod02 = lep_pdgId.at(0)*lep_pdgId.at(2);
        if (abs(lepprod02) == 121 && (mc_HLT_DoubleEl || mc_HLT_DoubleEl_DZ))
            return true;
        else if (abs(lepprod02) == 143 && mc_HLT_MuEG)
            return true;
        else if (abs(lepprod02) == 169 && mc_HLT_DoubleMu)
            return true;

        int lepprod12 = lep_pdgId.at(1)*lep_pdgId.at(2);
        if (abs(lepprod12) == 121 && (mc_HLT_DoubleEl || mc_HLT_DoubleEl_DZ))
            return true;
        else if (abs(lepprod12) == 143 && mc_HLT_MuEG)
            return true;
        else if (abs(lepprod12) == 169 && mc_HLT_DoubleMu)
            return true;

        return false;
    }
    else
    {
        return 0;
    }
}

