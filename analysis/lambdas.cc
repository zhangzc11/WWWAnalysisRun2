#include "lambdas.h"


int this_run;
int this_lumi;
unsigned long long this_evt;


//______________________________________________________________________________________________
// NOTE: It seems like, reading run/lumi/evt everytime is making it pretty slow...
// Need a better method
// Memoization to cache lambda results per event in order to save resource
// It checks whether the previous "result" is from the same event via checking run/lumi/evt
// If it is the same then return the cached "result"
// If it is not, then compute and save to "result" and update run/lumi/evt
std::function<float()> memoize(std::function<float()> foo)
{
    return [foo]() {
        // static variable per memoization
        static float result;

#ifdef DOCACHE

        static int run;
        static int lumi;
        static unsigned long long evt;

        // If it is the same then return the cached "result"
        // if (run == www.run() and lumi == www.lumi() and evt == www.evt())
        if (run == this_run and lumi == this_lumi and evt == this_evt)
        {
            return result;
        }

        run = www.run();
        lumi = www.lumi();
        evt = www.evt();

#endif

        // If it is not, then compute and save to "result" and update run/lumi/evt
        result = foo();

        return result;
    };

}

//***************************************************************************************************************
//
//
// Basic event selections
//
//
//***************************************************************************************************************

//______________________________________________________________________________________________
// Event weight
std::function<float()> Lambdas::EventWeight = [&]()
    {

        float weight = 1;

        // First of all, if it's data events and we're not performing fake estimation then it's easy the weight is just 1.
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
            purewgt = 1;
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
            lumi = 1;
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

    };

//______________________________________________________________________________________________
// very basic selections for each event
std::function<float()> Lambdas::PreliminarySelection = [&]()
    {
        bool presel = 1;
        presel &= (www.firstgoodvertex()      == 0);
        presel &= (www.Flag_AllEventFilters() >  0);
        presel &= (www.vetophoton()           == 0);
        presel &= (www.evt_passgoodrunlist()  >  0);
        presel &= (www.nVlep()                >= 2);
        presel &= (www.nLlep()                >= 2);
        return presel;
    };

//______________________________________________________________________________________________
// Trigger selection
std::function<float()> Lambdas::TriggerSelection = [&]()
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

    };




//***************************************************************************************************************
//
//
// Scale Factors
//
//
//***************************************************************************************************************

//______________________________________________________________________________________________
// Trigger scale factor
std::function<float()> Lambdas::TriggerScaleFactor = [&]()
    {
        // 2017 and 2018 trigger scale factors are not available yet (have not done the studies yet)
        // For 2016 the trigsf branch in the TTree holds the proper trigger scalefactors
        // TODO UPDATE THIS for 2017 and 2018
        // For now, using 2016 trigger scale factor for 2017/2018 (these are almost identical to 1 anyways...
        return input.is_data ? 1 : www.trigsf();
    };

//______________________________________________________________________________________________
// Lepton scale factors
std::function<float()> Lambdas::LeptonScaleFactor = [&]()
    {
        // the 2017 and 2018 doesn't have lepton scale factors saved to the branches in the WWW ttree
        if (input.year == 2017 or input.year == 2018)
            return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
        else
            return www.lepsf();
    };

//______________________________________________________________________________________________
// B-tagging scale factors
std::function<float()> Lambdas::BTagScaleFactor = [&]() { return www.weight_btagsf(); };






//***************************************************************************************************************
//
//
// Scale Factors
//
//
//***************************************************************************************************************

//______________________________________________________________________________________________
// Lepton scale factor variations
std::function<float()> Lambdas::LepSFVariation(Variation::Var var)
{
    return [&]()
    {
        if (input.year == 2016)
        {
            if (var == Variation::Up)
                return www.lepsf() == 0 ? 0 : www.lepsf_up() / www.lepsf() ;
            else // else if (var == Variation::Down)
                return www.lepsf() == 0 ? 0 : www.lepsf_dn() / www.lepsf() ;
        }
        else if (input.year == 2017)
        {
            if (var == Variation::Up)
            {
                float lepsf = leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
                return lepsf == 0 ? 0 : leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data, 1) / lepsf ;
            }
            else // else if (var == Variation::Down)
            {
                float lepsf = leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
                return lepsf == 0 ? 0 : leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data, -1) / lepsf ;
            }
        }
        else // else if (input.year == 2018) // TODO 2018 scale factor is not provided yet
        {
            if (var == Variation::Up)
            {
                // TODO UPDATE THIS
                return float(1);
            }
            else // else if (var == Variation::Down)
            {
                // TODO UPDATE THIS
                return float(1);
            }
        }
    };
}

//______________________________________________________________________________________________
// Trigger scale factor variations
std::function<float()> Lambdas::TriggerSFVariation(Variation::Var var)
{
    return [&]()
    {
        if (input.year == 2016)
        {
            if (var == Variation::Up)
                return www.trigsf() == 0 ? 0 : www.trigsf_up() / www.trigsf();
            else // else if (var == Variation::Down)
                return www.trigsf() == 0 ? 0 : www.trigsf_dn() / www.trigsf();
        }
        else if (input.year == 2017)
        {
            if (var == Variation::Up)
            {
                // TODO UPDATE THIS
                return float(1);
            }
            else // else if (var == Variation::Down)
            {
                // TODO UPDATE THIS
                return float(1);
            }
        }
        else // else if (input.year == 2018) // TODO 2018 scale factor is not provided yet
        {
            if (var == Variation::Up)
            {
                // TODO UPDATE THIS
                return float(1);
            }
            else // else if (var == Variation::Down)
            {
                // TODO UPDATE THIS
                return float(1);
            }
        }
    };
}

//______________________________________________________________________________________________
// Btagging LF scale factor variations
std::function<float()> Lambdas::BTagLFVariation(Variation::Var var)
{
    return [&]()
    {
        // Regardless of each year the babymaker uses same structure to put the systematic variations
        if (var == Variation::Up)
            return www.weight_btagsf() == 0 ? 0 : www.weight_btagsf_light_UP() / www.weight_btagsf();
        else // else if (var == Variation::Down)
            return www.weight_btagsf() == 0 ? 0 : www.weight_btagsf_light_DN() / www.weight_btagsf();
    };
}

//______________________________________________________________________________________________
// Btagging HF scale factor variations
std::function<float()> Lambdas::BTagHFVariation(Variation::Var var)
{
    return [&]()
    {
        // Regardless of each year the babymaker uses same structure to put the systematic variations
        if (var == Variation::Up)
            return www.weight_btagsf() == 0 ? 0 : www.weight_btagsf_heavy_UP() / www.weight_btagsf();
        else // else if (var == Variation::Down)
            return www.weight_btagsf() == 0 ? 0 : www.weight_btagsf_heavy_DN() / www.weight_btagsf();
    };
}

//______________________________________________________________________________________________
// Pileup reweighting variations
std::function<float()> Lambdas::PileupVariation(Variation::Var var)
{
    return [&]()
    {
        if (input.year == 2016)
        {
            if (var == Variation::Up)
                return www.purewgt() == 0 ? 0 : www.purewgt_up() / www.purewgt();
            else // else if (var == Variation::Down)
                return www.purewgt() == 0 ? 0 : www.purewgt_dn() / www.purewgt();
        }
        else if (input.year == 2017)
        {
            if (var == Variation::Up)
            {
                return pileupreweight.purewgt() == 0 ? 0 : pileupreweight.purewgt_up() / pileupreweight.purewgt();
            }
            else // else if (var == Variation::Down)
            {
                return pileupreweight.purewgt() == 0 ? 0 : pileupreweight.purewgt_dn() / pileupreweight.purewgt();
            }
        }
        else // else if (input.year == 2018) // TODO 2018 scale factor is not provided yet
        {
            if (var == Variation::Up)
            {
                // TODO UPDATE THIS
                return float(1);
            }
            else // else if (var == Variation::Down)
            {
                // TODO UPDATE THIS
                return float(1);
            }
        }
    };
}

//______________________________________________________________________________________________
// PDF weight variations
std::function<float()> Lambdas::PDFVariation(Variation::Var var)
{
    return [&]()
    {
        if (var == Variation::Up)
            return www.weight_fr_r1_f1() == 0 or theoryweight.pdfup() == 0 ? 0 : www.weight_pdf_up() / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.pdfup();
        else // else if (var == Variation::Down)
            return www.weight_fr_r1_f1() == 0 or theoryweight.pdfdn() == 0 ? 0 : www.weight_pdf_down() / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.pdfdn();
    };
}

//______________________________________________________________________________________________
// Qsq weight variations
std::function<float()> Lambdas::QsqVariation(Variation::Var var)
{
    return [&]()
    {
        if (var == Variation::Up)
            return www.weight_fr_r1_f1() == 0 or theoryweight.qsqup() == 0 ? 0 : www.weight_fr_r2_f2() / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.qsqup();
        else // else if (var == Variation::Down)
            return www.weight_fr_r1_f1() == 0 or theoryweight.qsqdn() == 0 ? 0 : www.weight_fr_r0p5_f0p5() / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.qsqdn();
    };
}

//______________________________________________________________________________________________
// AlphaS weight variations
std::function<float()> Lambdas::AlphaSVariation(Variation::Var var)
{
    return [&]()
    {
        if (var == Variation::Up)
            return www.weight_fr_r1_f1() == 0 or theoryweight.alsup() == 0 ? 0 : www.weight_alphas_up() / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.alsup();
        else // else if (var == Variation::Down)
            return www.weight_fr_r1_f1() == 0 or theoryweight.alsdn() == 0 ? 0 : www.weight_alphas_down() / www.weight_fr_r1_f1() * theoryweight.nominal() / theoryweight.alsdn();
    };
}





//***************************************************************************************************************
//
//
// Lepton multiplicity related selections
//
//
//***************************************************************************************************************

//______________________________________________________________________________________________
// SR Dilepton selection
std::function<float()> Lambdas::CutSRDilep = [&]()
    {
        // If the looper is looping over to do fake estimation, even though it is "SR dilep" selection require nTlep == 1, nLlep = 2. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        if (ana.do_fake_estimation)
            return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
        else
            return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
    };

//______________________________________________________________________________________________
// SR Trilepton selection
std::function<float()> Lambdas::CutSRTrilep = [&]()
    {
        // If the looper is looping over to do fake estimation, even though it is "SR trilep" selection require nTlep == 2, nLlep = 3. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        if (ana.do_fake_estimation)
            return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2) * (www.lep_pt()[0] > 25.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
        else
            return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0] > 25.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
    };

//______________________________________________________________________________________________
// Lost-lepton CR Trilepton selection
std::function<float()> Lambdas::CutCRTrilep = [&]()
    {
        // NOTE: One thing to note here is that even though it is asking for 20/20/20 pt at a later cut stage higher pt cuts will be applied
        // For example, for the lost-lepton control regions for the same-sign channels, out of the 3 leptons it will be required that the two same-sign ones pass same-sign tight ID.
        // When this is required, it will implicitly require that the lep_pt is 25 GeV for the two same-sign leptons. This is a bit vague and could be improved...
        return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0] > 20.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
    };

//______________________________________________________________________________________________
// AR Dilepton selection
std::function<float()> Lambdas::CutARDilep = [&]()
    {
        // Straight up application region selection. No fake factors are gonna be applied and the application region will be checked with data / MC
        return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.);
    };

//______________________________________________________________________________________________
// AR Trilepton selection
std::function<float()> Lambdas::CutARTrilep = [&]()
    {
        // Straight up application region selection. No fake factors are gonna be applied and the application region will be checked with data / MC
        return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>20.) * (www.lep_pt()[2]>20.);
    };




//***************************************************************************************************************
//
//
// Kinematic selections
//
//
//***************************************************************************************************************

std::function<float()> Lambdas::isSRSSeeChannel = [&]() { return (www.passSSee())*(www.MllSS()>40.); };
std::function<float()> Lambdas::isSRSSemChannel = [&]() { return (www.passSSem())*(www.MllSS()>30.); };
std::function<float()> Lambdas::isSRSSmmChannel = [&]() { return (www.passSSmm())*(www.MllSS()>40.); };

std::function<float()> Lambdas::TwoCenJet30 = [&]() { return www.nj30()>= 2; };
std::function<float()> Lambdas::LowDEtajj = [&]() { return www.DetajjL() < 1.5; };
std::function<float()> Lambdas::LowMjj = [&]() { return www.MjjL() < 400.; };

std::function<float()> Lambdas::MjjIn = [&]() { return fabs(www.Mjj()-80.)<15.; };
std::function<float()> Lambdas::MjjOut = [&]() { return fabs(www.Mjj()-80.)>=15.; };

std::function<float()> Lambdas::ZVetoSS = [&]() { return fabs(www.MllSS()-91.1876)>10.; };

std::function<float()> Lambdas::SSPreSelection = [&]()
    {
        if (not (www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 )) return false;
        if (not (www.nb()==0                                      )) return false;
        return true;
    };

std::function<float()> Lambdas::SRSSeeSelection = [&]()
    {
        if (not (www.met_pt()>60. )) return false;
        return true;
    };

std::function<float()> Lambdas::SRSSemSelection = [&]()
    {
        if (not (www.met_pt()>60. )) return false;
        if (not (www.MTmax() >90. )) return false;
        return true;
    };

std::function<float()> Lambdas::SRSSmmSelection = [&]()
    {
        return true;
    };

std::function<float()> Lambdas::SRSSSidemmSel = [&]()
    {
        if (not (www.met_pt()>60.    )) return false;
        return true;
    };

std::function<float()> Lambdas::is0SFOS = [&]() { return www.nSFOS()==0; };
std::function<float()> Lambdas::is1SFOS = [&]() { return www.nSFOS()==1; };
std::function<float()> Lambdas::is2SFOS = [&]() { return www.nSFOS()==2; };

std::function<float()> Lambdas::ThreeLepPresel = [&]()
    {
        if (not (www.nj() <= 1)) return false;
        if (not (www.nb() == 0)) return false;
        return true;
    };

std::function<float()> Lambdas::DYVetoes0SFOS = [&]()
    {
        if (not (www.Mll3L() > 20.             )) return false;
        if (not (abs(www.M3l()-91.1876) > 10.  )) return false;
        if (not (abs(www.Mee3L()-91.1876) > 15.)) return false;
        return true;
    };

std::function<float()> Lambdas::DYVetoes1SFOS = [&]()
    {
        if (not (www.Mll3L() > 20.             )) return false;
        if (not (abs(www.M3l()-91.1876) > 10.  )) return false;
        return true;
    };

std::function<float()> Lambdas::DYVetoes2SFOS = [&]()
    {
        if (not ((www.Mll3L() > 20. && www.Mll3L1() > 20.) )) return false;
        if (not (abs(www.M3l()-91.1876) > 10.              )) return false;
        return true;
    };

std::function<float()> Lambdas::ZVeto3L = [&]() { return www.nSFOSinZ() == 0; };

std::function<float()> Lambdas::KinSel0SFOS = [&]()
    {
        if (not (www.DPhi3lMET()>2.5 )) return false;
        if (not (www.met_pt()>30.    )) return false;
        if (not (www.MTmax3L()>90.   )) return false;
        return true;
    };

std::function<float()> Lambdas::KinSel1SFOS = [&]()
    {
        if (not (www.Pt3l() > 60.    )) return false;
        if (not (www.DPhi3lMET()>2.5 )) return false;
        if (not (www.met_pt()>40.    )) return false;
        if (not (www.MT3rd() > 90.   )) return false;
        return true;
    };

std::function<float()> Lambdas::KinSel2SFOS = [&]()
    {
        if (not (www.Pt3l() > 60.    )) return false;
        if (not (www.DPhi3lMET()>2.5 )) return false;
        if (not (www.met_pt()>55.    )) return false;
        return true;
    };

std::function<float()> Lambdas::HasZ_SS = [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.); };
std::function<float()> Lambdas::HasZ_3L = [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.); };

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

