#include "main.h"

//_______________________________________________________________________________________________________
int process(const char* input_paths, const char* input_tree_name, const char* output_file_name, int nEvents, TString regions)
{
    // Creating output file where we will put the outputs of the processing
    TFile* ofile = new TFile(output_file_name, "recreate");

    // Create a TChain of the input files
    // The input files can be comma separated (e.g. "file1.root,file2.root")
    TChain* ch = RooUtil::FileUtil::createTChain(input_tree_name, input_paths);

    // Create a Looper object to loop over input files
    RooUtil::Looper<wwwtree> looper(ch, &www, nEvents);

    // Based on the input file name and the output file name set the global configuration variables
    setGlobalConfigurationVariables(input_paths, output_file_name);

    // Cutflow utility object that creates a tree structure of cuts
    RooUtil::Cutflow cutflow(ofile);

    // Histogram utility object that is used to define the histograms
    RooUtil::Histograms histograms = createHistograms();

    // Adding a whole bunch of cuts!
    addBaseCuts(cutflow);
    addSignalRegionCuts(cutflow);
    addLostLepControlRegionCuts(cutflow);
    addApplicationRegionCuts(cutflow);
    addBtaggedControlRegionCuts(cutflow);
    addLowMETControlRegionCuts(cutflow);
    addBtaggedApplicationRegionCuts(cutflow);
    addLowMETApplicationRegionCuts(cutflow);
    addPromptControlRegionCuts(cutflow);
    addGammaControlRegionCuts(cutflow);
//    addOppositeSignControlRegionCuts(cutflow); // Not needed for main analysis
//    addLooseLeptonControlRegionCuts(cutflow); // Not needed for main analysis

    // Adding systematic cuts
    addSystematicCuts(cutflow);

    // Now book the cutflow and histogram jobs
    bookCutflowsAndHistogramsForGivenRegions(cutflow, histograms, regions);

    // Print the cut structure for review
    cutflow.printCuts();

    //
    //
    // Looping events
    //
    //
    while (looper.nextEvent())
    {

        setGlobalEventVariables();

        // Theory related weights from h_neventsinfile in each input root file but only set files when new file opens
        // NOTE if there was a continue statement prior to this it can mess it up
        if (looper.isNewFileInChain() and not isData) theoryweight.setFile(looper.getCurrentFileName());

        // Set the event list variables
        cutflow.setEventID(www.run(), www.lumi(), www.evt());

        // Once every cut bits are set, now fill the cutflows that are booked
        cutflow.fill();
    }

    // Save output
    cutflow.saveOutput();

    return 0;
}

//_______________________________________________________________________________________________________
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

//_______________________________________________________________________________________________________
void setGlobalEventVariables()
{

        // PureWgt
        float purewgt = (is2017 == 1) ? pileupreweight.purewgt() : www.purewgt();

        // Fake factor weights
        ffwgt = 1;
        if (doFakeEstimation)
        {
            ffwgt = is2017 == 1 ? fakerates.getFakeFactor() : www.ffwgt();
            if (doEwkSubtraction && !www.bkgtype().EqualTo("fakes")) ffwgt *= -1; // subtracting non-fakes
            if (doEwkSubtraction &&  www.bkgtype().EqualTo("fakes")) ffwgt *=  0; // do not subtract fakes
            if (!doEwkSubtraction) purewgt = 1;
        }

        // Compute preselection
        presel = 1;
        presel &= (www.firstgoodvertex()      == 0);
        presel &= (www.Flag_AllEventFilters() >  0);
        presel &= (www.vetophoton()           == 0);
        presel &= (www.evt_passgoodrunlist()  >  0);
        presel &= (www.nVlep()                >= 2);
        presel &= (www.nLlep()                >= 2);

        // Compute trigger variable (TODO for 2016 baby, the tertiary statement may be outdated)
        trigger  = is2017 == 1 ? www.passTrigger() * www.pass_duplicate_ee_em_mm() : passTrigger2016();
        trigger &= is2017 == 0 ? (is2016_v122 ? 1 : www.pass_duplicate_ee_em_mm()) : 1;

        // Event weight
        weight = (isData and !doFakeEstimation) ? 1 : www.evt_scale1fb() * purewgt * lumi * ffwgt;
        if (isWWW and !is2017 and doWWWXsecScaling) weight *= 1.0384615385; // NLO cross section v. MadGraph cross section

        // Lepton counter to define dilep or trilep region
        isdilep          = (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 2);
        istrilep         = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0]>25.);
        isfakedilep      = (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
        isfaketrilep     = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2);
        isloosedilep     = (www.nVlep() == 2) * (www.nLlep() == 2);
        iswzcrtrilep     = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3);
        isfakewzcrtrilep = (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2);
        osdileppresel    = (www.mc_HLT_DoubleEl()||www.mc_HLT_DoubleMu()||www.mc_HLT_MuEG())*(www.nVlep()==2)*(www.nLlep()==2)*(www.nTlep()==2);


        // Compute the scale factors
        if (is2017)
        {
            float lep_sf = leptonScaleFactors.getScaleFactors(is2017, doFakeEstimation, isData);
            ee_sf = lep_sf;
            em_sf = lep_sf;
            mm_sf = lep_sf;
            threelep_sf = lep_sf;
        }
        else
        {
            ee_sf = www.lepsf();
            em_sf = www.lepsf();
            mm_sf = www.lepsf();
            threelep_sf = www.lepsf();
        }
        btag_sf = isData ? 1 : www.weight_btagsf();
        trig_sf = isData ? 1 : www.trigsf();

        hasz_ss = (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.);
        hasz_3l = (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.);
        passPhotonCRSFOS =
            (www.nSFOS()==1)*(www.Mll3L()<55)*(www.Mll3L()>110) +
            (www.nSFOS()==2)*((fabs(www.Mll3L()-90.)>20.)*(fabs(www.Mll3L1()-90.)>20.));

}

//_______________________________________________________________________________________________________
void setGlobalConfigurationVariables(const char* input_paths, const char* output_file_name)
{
    // Some case-by-case checking needed for WWW_v1.2.2 (should be no longer necessary later on)
    is2017 = TString(input_paths).Contains("2017");
    is2017 = TString(input_paths).Contains("v1.2.2") ? false : is2017;
    is2017 = TString(input_paths).Contains("WWW2016") ? false : is2017;
    isWWW = TString(input_paths).Contains("www_2l_");
    doWWWXsecScaling = TString(input_paths).Contains("v1.2.2"); // The v1.2.2 version had slightly lower xsec.
    is2016_v122 = TString(input_paths).Contains("v1.2.2");

    // For fake estimations, we use data-driven method.
    // When looping over data and the output_path is set to have a "fakes" substring included we turn on the fake-weight settings
    doSystematics = (not TString(input_paths).Contains("data_"));
    doHistogram = true;
    doFakeEstimation = TString(output_file_name).Contains("ddfakes") or TString(output_file_name).Contains("ewksubt");
    doEwkSubtraction = TString(output_file_name).Contains("ewksubt");
    isData = TString(input_paths).Contains("data_") || TString(input_paths).Contains("Run2017");

    // Luminosity setting
    lumi = isData ? 1 : (is2017 == 1 ? 41.3 : 35.9);

    std::cout <<  " Printing configuration " << std::endl;
    std::cout <<  " is2017: " << is2017 <<  std::endl;
    std::cout <<  " isWWW: " << isWWW <<  std::endl;
    std::cout <<  " doSystematics: " << doSystematics <<  std::endl;
    std::cout <<  " doHistogram: " << doHistogram <<  std::endl;
    std::cout <<  " doFakeEstimation: " << doFakeEstimation <<  std::endl;
    std::cout <<  " doEwkSubtraction: " << doEwkSubtraction <<  std::endl;
    std::cout <<  " isData: " << isData <<  std::endl;
    std::cout <<  " input_paths: " << input_paths <<  std::endl;
    std::cout <<  " output_file_name: " << output_file_name <<  std::endl;
    std::cout <<  " lumi: " << lumi <<  std::endl;

}

//_______________________________________________________________________________________________________
void bookCutflowsAndHistogramsForGivenRegions(RooUtil::Cutflow& cutflow, RooUtil::Histograms& histograms, TString regions)
{
    if (regions.EqualTo("all"))
    {
        // Because I named the end cuts to be "Full" for every one of them, I can use this fact to filter out a chunk more easily
        // {"SRSSeeFull", "SRSSemFull", .... }
        // --> {"SRSSee", "SRSSem", .... }
        std::vector<TString> endcuts = cutflow.cuttree.getEndCuts();
        std::vector<TString> list_of_cuts;
        for (auto& endcut : endcuts)
            list_of_cuts.push_back(endcut.ReplaceAll("Full", ""));
        // Now replace with "SRSSee,SRSSem,SRSSmm,..."
        regions = RooUtil::StringUtil::join(list_of_cuts);

        // Also when processing all regios, skip histograms for systematics (to speed things up)
        cutflow.setSkipSystematicHistograms(true);
    }
    else if (not regions.IsNull())
    {
        cutflow.filterCuts(RooUtil::StringUtil::split(regions, ","));
    }

    // Now book cutflows
    cutflow.bookCutflows();

    // Book event lists
    cutflow.bookEventLists();

    // Histogram booking is dependent on whether you ask for certain regions also when systematics is asked, do not run the entire histogramming otherwise too many will be booked (O(20k) histograms!)
    if (doHistogram)
    {
        if (not regions.IsNull())
        {
            // book histogram from the requested region and below
            for (auto& region : RooUtil::StringUtil::split(regions, ","))
            {
                cutflow.bookHistogramsForCutAndBelow(histograms, region);
            }
        }
        else
        {
            // Now book histograms at the end of each cut structures (the CutTree nodes that terminates)
            cutflow.bookHistogramsForEndCuts(histograms);
        }
    }
}


//_______________________________________________________________________________________________________
int help()
{
    // Help function
    std::cout << "Usage:" << std::endl;
    std::cout << std::endl;
    std::cout << "  $ ./process INPUTFILES INPUTTREENAME OUTPUTFILE [NEVENTS]" << std::endl;
    std::cout << std::endl;
    std::cout << "  INPUTFILES      comma separated file list" << std::endl;
    std::cout << "  INPUTTREENAME   tree name in the file" << std::endl;
    std::cout << "  OUTPUTFILE      output file name" << std::endl;
    std::cout << "  [NEVENTS=-1]    # of events to run over" << std::endl;
    std::cout << "  [REGIONS]       comma separated regions" << std::endl;
    std::cout << std::endl;
    return 1;
}

//_______________________________________________________________________________________________________
int main(int argc, char** argv)
{
    if (argc == 4)
    {
        return process(argv[1], argv[2], argv[3], -1, "");
    }
    else if (argc == 5)
    {
        return process(argv[1], argv[2], argv[3], atoi(argv[4]), "");
    }
    else if (argc == 6)
    {
        return process(argv[1], argv[2], argv[3], atoi(argv[4]), argv[5]);
    }
    else
    {
        return help();
    }
}
