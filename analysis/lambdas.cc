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
            // if (input.is_bkg && !www.bkgtype().EqualTo("fakes")) ffwgt *=  0; // do not subtract non-fakes
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

        //
        // Xsec error corrections
        //
        if ((input.current_file_name.Contains("wg_lnug_amcatnlo_1.root") or input.current_file_name.Contains("wg_lvg_amcatnlo_1.root")) // Because the short name was different between 2017 and 2018... (stupid of me...)
                and (input.baby_version.EqualTo("5.1.4") or input.baby_version.EqualTo("5.1.6"))
                and (input.baby_type.EqualTo("Loose") or input.baby_type.EqualTo("WWW")))
        {
            weight *= 163. / 405.27;
        }

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
        if (input.baby_type.EqualTo("WWW") and input.baby_version.EqualTo("1.2.2"))
            trigger = passTrigger2016();
        else if (input.year == 2017 or input.year == 2018)
            trigger = www.passTrigger() * www.pass_duplicate_ee_em_mm();
        else if (input.year == 2016)
            trigger = www.passTrigger() * www.pass_duplicate_ee_em_mm();
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
    return [&, var]()
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
    return [&, var]()
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
    return [&, var]()
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
    return [&, var]()
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
    return [&, var]()
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
// Fake factor variation
std::function<float()> Lambdas::FakeFactorVariation(Variation::FakeVar fakevar_, Variation::Var var_)
{

    return [&, fakevar_, var_]()
    {
        static Variation::FakeVar fakevar;
        static Variation::Var var;

        fakevar = fakevar_;
        var = var_;

        if (fakevar == Variation::Full)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_full_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_full_dn() / www.ffwgt();
            }
            else if (input.year == 2017)
            {
                // TODO
                return float(1);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }
        else if (fakevar == Variation::Rate)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_dn() / www.ffwgt();
            }
            else if (input.year == 2017)
            {
                // TODO
                return float(1);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }
        else if (fakevar == Variation::Closure)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_dn() / www.ffwgt();
            }
            else if (input.year == 2017)
            {
                // TODO
                return float(1);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::RateEl)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_el_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_el_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 11) / fakerates.getFakeFactor(0, 11);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 11) / fakerates.getFakeFactor(0, 11);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::RateSSEl)
        {
            if (www.nLlep() >= 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_el_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_el_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 11) / fakerates.getFakeFactor(0, 11);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 11) / fakerates.getFakeFactor(0, 11);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::Rate3LEl)
        {
            if (www.nLlep() < 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_el_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_el_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 11) / fakerates.getFakeFactor(0, 11);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 11) / fakerates.getFakeFactor(0, 11);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::RateMu)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 13) / fakerates.getFakeFactor(0, 13);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 13) / fakerates.getFakeFactor(0, 13);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::RateSSMu)
        {
            if (www.nLlep() >= 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 13) / fakerates.getFakeFactor(0, 13);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 13) / fakerates.getFakeFactor(0, 13);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::Rate3LMu)
        {
            if (www.nLlep() < 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_mu_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 13) / fakerates.getFakeFactor(0, 13);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 13) / fakerates.getFakeFactor(0, 13);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::ClosureEl)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 11, true) / fakerates.getFakeFactor(0, 11);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 11, true) / fakerates.getFakeFactor(0, 11);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::ClosureSSEl)
        {
            if (www.nLlep() >= 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 11, true) / fakerates.getFakeFactor(0, 11);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 11, true) / fakerates.getFakeFactor(0, 11);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::Closure3LEl)
        {
            if (www.nLlep() < 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_el_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 11, true) / fakerates.getFakeFactor(0, 11);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 11, true) / fakerates.getFakeFactor(0, 11);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::ClosureMu)
        {
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 13, true) / fakerates.getFakeFactor(0, 13);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 13, true) / fakerates.getFakeFactor(0, 13);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else if (fakevar == Variation::ClosureSSMu)
        {
            if (www.nLlep() >= 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 13, true) / fakerates.getFakeFactor(0, 13);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 13, true) / fakerates.getFakeFactor(0, 13);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }

        // Split by electron/muons
        else // else if (fakevar == Variation::Closure3LMu)
        {
            if (www.nLlep() < 3) return float(1);
            if (input.year == 2016)
            {
                if (var == Variation::Up)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_up() / www.ffwgt();
                else // else if (var == Variation::Down)
                    return www.ffwgt() == 0 ? 0 : www.ffwgt_closure_mu_dn() / www.ffwgt();
            }
            else if (input.year == 2017 || input.year == 2018)
            {
                if (var == Variation::Up)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor( 1, 13, true) / fakerates.getFakeFactor(0, 13);
                else // else if (var == Variation::Down)
                    return fakerates.getFakeFactor() == 0 ? 0 : fakerates.getFakeFactor(-1, 13, true) / fakerates.getFakeFactor(0, 13);
            }
            else // else if (input.year == 2018) // TODO 2018 fake rate not computed yet
            {
                // TODO
                return float(1);
            }
        }


    };

}

//______________________________________________________________________________________________
// PDF weight variations
std::function<float()> Lambdas::PDFVariation(Variation::Var var)
{
    return [&, var]()
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
    return [&, var]()
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
    return [&, var]()
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
        // Additional cuts for 2018 lepton IDs
        float mva_threshold = input.year == 2018 ? 7 : -1;
        // If the looper is looping over to do fake estimation, even though it is "SR dilep" selection require nTlep == 1, nLlep = 2. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        if (ana.do_fake_estimation)
            return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 1) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.) * (fabs(www.lep_MVA()[0]) > mva_threshold) * (fabs(www.lep_MVA()[1]) > mva_threshold);
        else
            return (www.nVlep() == 2) * (www.nLlep() == 2) * (www.nTlep() == 2) * (www.lep_pt()[0]>25.) * (www.lep_pt()[1]>25.) * (fabs(www.lep_MVA()[0]) > mva_threshold) * (fabs(www.lep_MVA()[1]) > mva_threshold);
    };

//______________________________________________________________________________________________
// SR Trilepton selection
std::function<float()> Lambdas::CutSRTrilep = [&]()
    {
        // If the looper is looping over to do fake estimation, even though it is "SR trilep" selection require nTlep == 2, nLlep = 3. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        if (input.year == 2018)
        {
            if (ana.do_fake_estimation)
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2) * (www.lep_pt()[0] > 25.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
            else
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0] > 25.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
        }
        else
        {
            if (ana.do_fake_estimation)
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 2) * (www.lep_pt()[0] > 25.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
            else
                return (www.nVlep() == 3) * (www.nLlep() == 3) * (www.nTlep() == 3) * (www.lep_pt()[0] > 25.) * (www.lep_pt()[1] > 20.) * (www.lep_pt()[2] > 20.);
        }
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

std::function<float()> Lambdas::jetVar(Variation::ExpSyst expsyst, Variation::Var var,
        std::function<float()> jesup, // JES Up
        std::function<float()> jesdn, // JES Down
        std::function<float()> jes,   // JES
        std::function<float()> jerup, // JER Up
        std::function<float()> jerdn, // JER Down
        std::function<float()> jer    // JER
        )
{
    if (expsyst == Variation::JES)
    {
        if (var == Variation::Up)
            return jesup;
        else if (var == Variation::Down)
            return jesdn;
        else
            return jes;
    }
    else // else if (expsyst == Variation::JER)
    {
        if (var == Variation::Up)
            return jerup;
        else if (var == Variation::Down)
            return jerdn;
        else
            return jer;
    }
}

std::function<LV()> Lambdas::jetVec(Variation::ExpSyst expsyst, Variation::Var var,
        std::function<LV()> jesup, // JES Up
        std::function<LV()> jesdn, // JES Down
        std::function<LV()> jes,   // JES
        std::function<LV()> jerup, // JER Up
        std::function<LV()> jerdn, // JER Down
        std::function<LV()> jer    // JER
        )
{
    if (expsyst == Variation::JES)
    {
        if (var == Variation::Up)
            return jesup;
        else if (var == Variation::Down)
            return jesdn;
        else
            return jes;
    }
    else // else if (expsyst == Variation::JER)
    {
        if (var == Variation::Up)
            return jerup;
        else if (var == Variation::Down)
            return jerdn;
        else
            return jer;
    }
}

std::function<float()> Lambdas::isSRSSeeChannel = [&]() { return (www.passSSee())*(www.MllSS()>40.); };
std::function<float()> Lambdas::isSRSSemChannel = [&]() { return (www.passSSem())*(www.MllSS()>30.); };
std::function<float()> Lambdas::isSRSSmmChannel = [&]() { return (www.passSSmm())*(www.MllSS()>40.); };

std::function<float()> Lambdas::LeqOneJet30(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (www.nj_up()<= 1); },
            [&]() { return (www.nj_up()<= 1); },
            [&]() { return (www.nj()<= 1); },
            [&]() { return (www.nj_jerup()<= 1); },
            [&]() { return (www.nj_jerdn()<= 1); },
            [&]() { return (www.nj_jer()<= 1); }
            );
}

std::function<float()> Lambdas::OneCenJet30(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (www.nj30_up()== 1); },
            [&]() { return (www.nj30_up()== 1); },
            [&]() { return (www.nj30()== 1); },
            [&]() { return (www.nj30_jerup()== 1); },
            [&]() { return (www.nj30_jerdn()== 1); },
            [&]() { return (www.nj30_jer()== 1); }
            );
}

std::function<float()> Lambdas::TwoCenJet30(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (www.nj30_up()>= 2); },
            [&]() { return (www.nj30_up()>= 2); },
            [&]() { return (www.nj30()>= 2); },
            [&]() { return (www.nj30_jerup()>= 2); },
            [&]() { return (www.nj30_jerdn()>= 2); },
            [&]() { return (www.nj30_jer()>= 2); }
            );
}

std::function<float()> Lambdas::LowDEtajj(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (www.DetajjL_up()< 1.5); },
            [&]() { return (www.DetajjL_up()< 1.5); },
            [&]() { return (www.DetajjL()< 1.5); },
            [&]() { return (www.DetajjL_jerup()< 1.5); },
            [&]() { return (www.DetajjL_jerdn()< 1.5); },
            [&]() { return (www.DetajjL_jer()< 1.5); }
            );
}

std::function<float()> Lambdas::LowMjj(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (www.MjjL_up()< 400.); },
            [&]() { return (www.MjjL_up()< 400.); },
            [&]() { return (www.MjjL()< 400.); },
            [&]() { return (www.MjjL_jerup()< 400.); },
            [&]() { return (www.MjjL_jerdn()< 400.); },
            [&]() { return (www.MjjL_jer()< 400.); }
            );
}

std::function<float()> Lambdas::MjjIn(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (fabs(www.Mjj_up()-80.)<15.); },
            [&]() { return (fabs(www.Mjj_dn()-80.)<15.); },
            [&]() { return (fabs(www.Mjj()-80.)<15.); },
            [&]() { return (fabs(www.Mjj_jerup()-80.)<15.); },
            [&]() { return (fabs(www.Mjj_jerdn()-80.)<15.); },
            [&]() { return (fabs(www.Mjj_jer()-80.)<15.); }
            );
}

std::function<float()> Lambdas::MjjOut(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var, 
            [&]() { return (fabs(www.Mjj_up()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj_dn()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj_jerup()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj_jerdn()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj_jer()-80.)>=15.); }
            );
}

std::function<float()> Lambdas::ZVetoSS = [&]() { return fabs(www.MllSS()-91.1876)>10.; };

std::function<float()> Lambdas::SSPreSelection(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag)
{
    return [&, expsyst, var, invert_btag]()
    {
        if (not (www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 )) return false;
        if (not invert_btag)
        {
            if (not (
                        jetVar(expsyst, var,
                            [&]() { return (www.nb_up()==0); },
                            [&]() { return (www.nb_dn()==0); },
                            [&]() { return (www.nb()==0); },
                            [&]() { return (www.nb_jerup()==0); },
                            [&]() { return (www.nb_jerdn()==0); },
                            [&]() { return (www.nb_jer()==0); }
                            )()                                    )) return false;
        }
        else
        {
            if (not (
                        jetVar(expsyst, var,
                            [&]() { return (www.nb_up()!=0); },
                            [&]() { return (www.nb_dn()!=0); },
                            [&]() { return (www.nb()!=0); },
                            [&]() { return (www.nb_jerup()!=0); },
                            [&]() { return (www.nb_jerdn()!=0); },
                            [&]() { return (www.nb_jer()!=0); }
                            )()                                    )) return false;
        }
        return true;
    };
}

std::function<float()> Lambdas::SRSSeeSelection(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()>60.; },
                        [&]() { return www.met_dn_pt()>60.; },
                        [&]() { return www.met_pt()>60.; },
                        [&]() { return www.met_jerup_pt()>60.; },
                        [&]() { return www.met_jerdn_pt()>60.; },
                        [&]() { return www.met_jer_pt()>60.; }
                        )()                                   )) return false;
        return true;
    };
}

std::function<float()> Lambdas::SRSSemSelection(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()>60.; },
                        [&]() { return www.met_dn_pt()>60.; },
                        [&]() { return www.met_pt()>60.; },
                        [&]() { return www.met_jerup_pt()>60.; },
                        [&]() { return www.met_jerdn_pt()>60.; },
                        [&]() { return www.met_jer_pt()>60.; }
                        )()                                  )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.MTmax()>90.; }, // TODO : Need to add to baby maker
                        [&]() { return www.MTmax()>90.; }, // TODO
                        [&]() { return www.MTmax()>90.; }, // TODO
                        [&]() { return www.MTmax()>90.; }, // TODO
                        [&]() { return www.MTmax()>90.; }, // TODO
                        [&]() { return www.MTmax()>90.; }  // TODO
                        )()                                  )) return false;
        return true;
    };
}

std::function<float()> Lambdas::SRSSmmSelection(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        return true;
    };
}

std::function<float()> Lambdas::SRSSSidemmSel(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()>60.; },
                        [&]() { return www.met_dn_pt()>60.; },
                        [&]() { return www.met_pt()>60.; },
                        [&]() { return www.met_jerup_pt()>60.; },
                        [&]() { return www.met_jerdn_pt()>60.; },
                        [&]() { return www.met_jer_pt()>60.; }
                        )()                                  )) return false;
        return true;
    };
}

std::function<float()> Lambdas::is0SFOS = [&]() { return www.nSFOS()==0; };
std::function<float()> Lambdas::is1SFOS = [&]() { return www.nSFOS()==1; };
std::function<float()> Lambdas::is2SFOS = [&]() { return www.nSFOS()==2; };

std::function<float()> Lambdas::ThreeLepPresel(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag)
{
    return [&, expsyst, var, invert_btag]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return (www.nj_up()<=1); },
                        [&]() { return (www.nj_dn()<=1); },
                        [&]() { return (www.nj()<=1); },
                        [&]() { return (www.nj_jerup()<=1); },
                        [&]() { return (www.nj_jerdn()<=1); },
                        [&]() { return (www.nj_jer()<=1); }
                        )()                                       )) return false;
        if (not invert_btag)
        {
            if (not (
                        jetVar(expsyst, var,
                            [&]() { return (www.nb_up()==0); },
                            [&]() { return (www.nb_dn()==0); },
                            [&]() { return (www.nb()==0); },
                            [&]() { return (www.nb_jerup()==0); },
                            [&]() { return (www.nb_jerdn()==0); },
                            [&]() { return (www.nb_jer()==0); }
                            )()                                   )) return false;
        }
        else
        {
            if (not (
                        jetVar(expsyst, var,
                            [&]() { return (www.nb_up()!=0); },
                            [&]() { return (www.nb_dn()!=0); },
                            [&]() { return (www.nb()!=0); },
                            [&]() { return (www.nb_jerup()!=0); },
                            [&]() { return (www.nb_jerdn()!=0); },
                            [&]() { return (www.nb_jer()!=0); }
                            )()                                   )) return false;
        }
        return true;
    };
}

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
        if (not ((www.Mll3L() > 20. and www.Mll3L1() > 20.) )) return false;
        if (not (abs(www.M3l()-91.1876) > 10.               )) return false;
        return true;
    };

std::function<float()> Lambdas::ZVeto3L = [&]() { return www.nSFOSinZ() == 0; };

std::function<float()> Lambdas::KinSel0SFOS(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return (www.DPhi3lMET_up()>2.5); },
                        [&]() { return (www.DPhi3lMET_dn()>2.5); },
                        [&]() { return (www.DPhi3lMET()>2.5); },
                        [&]() { return (www.DPhi3lMET_jerup()>2.5); },
                        [&]() { return (www.DPhi3lMET_jerdn()>2.5); },
                        [&]() { return (www.DPhi3lMET_jer()>2.5); }
                        )()                                       )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()>30.; },
                        [&]() { return www.met_dn_pt()>30.; },
                        [&]() { return www.met_pt()>30.; },
                        [&]() { return www.met_jerup_pt()>30.; },
                        [&]() { return www.met_jerdn_pt()>30.; },
                        [&]() { return www.met_jer_pt()>30.; }
                        )()                                  )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.MTmax3L()>90.; }, // TODO : Need to implement in baby maker
                        [&]() { return www.MTmax3L()>90.; },
                        [&]() { return www.MTmax3L()>90.; },
                        [&]() { return www.MTmax3L()>90.; },
                        [&]() { return www.MTmax3L()>90.; },
                        [&]() { return www.MTmax3L()>90.; }
                        )()                                  )) return false;
        return true;
    };
}

std::function<float()> Lambdas::KinSel1SFOS(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (www.Pt3l() > 60.    )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return (www.DPhi3lMET_up()>2.5); },
                        [&]() { return (www.DPhi3lMET_dn()>2.5); },
                        [&]() { return (www.DPhi3lMET()>2.5); },
                        [&]() { return (www.DPhi3lMET_jerup()>2.5); },
                        [&]() { return (www.DPhi3lMET_jerdn()>2.5); },
                        [&]() { return (www.DPhi3lMET_jer()>2.5); }
                        )()                                       )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()>40.; },
                        [&]() { return www.met_dn_pt()>40.; },
                        [&]() { return www.met_pt()>40.; },
                        [&]() { return www.met_jerup_pt()>40.; },
                        [&]() { return www.met_jerdn_pt()>40.; },
                        [&]() { return www.met_jer_pt()>40.; }
                        )()                                  )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.MT3rd()>90.; }, // TODO : Need to implement in baby maker
                        [&]() { return www.MT3rd()>90.; },
                        [&]() { return www.MT3rd()>90.; },
                        [&]() { return www.MT3rd()>90.; },
                        [&]() { return www.MT3rd()>90.; },
                        [&]() { return www.MT3rd()>90.; }
                        )()                                  )) return false;
        return true;
    };
}

std::function<float()> Lambdas::KinSel2SFOS(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (www.Pt3l() > 60.    )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return (www.DPhi3lMET_up()>2.5); },
                        [&]() { return (www.DPhi3lMET_dn()>2.5); },
                        [&]() { return (www.DPhi3lMET()>2.5); },
                        [&]() { return (www.DPhi3lMET_jerup()>2.5); },
                        [&]() { return (www.DPhi3lMET_jerdn()>2.5); },
                        [&]() { return (www.DPhi3lMET_jer()>2.5); }
                        )()                                       )) return false;
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()>55.; },
                        [&]() { return www.met_dn_pt()>55.; },
                        [&]() { return www.met_pt()>55.; },
                        [&]() { return www.met_jerup_pt()>55.; },
                        [&]() { return www.met_jerdn_pt()>55.; },
                        [&]() { return www.met_jer_pt()>55.; }
                        )()                                  )) return false;
        return true;
    };
}

std::function<float()> Lambdas::HasZ_SS = [&]() { return (abs(www.Mll3L()-91.1876)<10.||abs(www.Mll3L1()-91.1876)<10.); };
std::function<float()> Lambdas::HasZ_3L = [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.); };

std::function<float()> Lambdas::Nj1DRljMin(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {

        if (not (www.lep_p4().size() > 1)) return false;

        if (not (jetVar(expsyst, var,
            [&]() { return www.jets_up_p4().size(); },
            [&]() { return www.jets_dn_p4().size(); },
            [&]() { return www.jets_p4().size(); },
            [&]() { return www.jets_jerup_p4().size(); },
            [&]() { return www.jets_jerdn_p4().size(); },
            [&]() { return www.jets_jer_p4().size(); }
            )() != 1 )) return false;

        LV jet = jetVec(expsyst, var,
            [&]() { return www.jets_up_p4()[0]; },
            [&]() { return www.jets_dn_p4()[0]; },
            [&]() { return www.jets_p4()[0]; },
            [&]() { return www.jets_jerup_p4()[0]; },
            [&]() { return www.jets_jerdn_p4()[0]; },
            [&]() { return www.jets_jer_p4()[0]; }
            )();

        float drlj0 = RooUtil::Calc::DeltaR(www.lep_p4()[0], jet);
        float drlj1 = RooUtil::Calc::DeltaR(www.lep_p4()[1], jet);
        float mindrlj = drlj0 < drlj1 ? drlj0 : drlj1;
        return mindrlj < 1.9;
    };
}

std::function<float()> Lambdas::Nj1CRKinSel(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (www.Mll3L()  > 10.                    )) return false;
        if (not (www.Mll3L1() > 10. or www.Mll3L1() < 0)) return false;
        if (not (
                   ((www.nSFOS() == 0) and
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()<30.; },
                        [&]() { return www.met_dn_pt()<30.; },
                        [&]() { return www.met_pt()<30.; },
                        [&]() { return www.met_jerup_pt()<30.; },
                        [&]() { return www.met_jerdn_pt()<30.; },
                        [&]() { return www.met_jer_pt()<30.; }
                        )()                                   
                   )
                   or
                   ((www.nSFOS() == 1) and
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()<40.; },
                        [&]() { return www.met_dn_pt()<40.; },
                        [&]() { return www.met_pt()<40.; },
                        [&]() { return www.met_jerup_pt()<40.; },
                        [&]() { return www.met_jerdn_pt()<40.; },
                        [&]() { return www.met_jer_pt()<40.; }
                        )()                                   
                   )
                   or
                   ((www.nSFOS() == 2) and
                    jetVar(expsyst, var,
                        [&]() { return www.met_up_pt()<55.; },
                        [&]() { return www.met_dn_pt()<55.; },
                        [&]() { return www.met_pt()<55.; },
                        [&]() { return www.met_jerup_pt()<55.; },
                        [&]() { return www.met_jerdn_pt()<55.; },
                        [&]() { return www.met_jer_pt()<55.; }
                        )()                                   
                   )
                    )) return false;
        return true;
    };
}

std::function<float()> Lambdas::isSSem = [&]() { return (www.lep_pdgId().size() > 1) and (www.lep_pdgId()[0] * www.lep_pdgId()[1] == 143) and (abs(www.lep_pdgId()[1]) == 13); };
std::function<float()> Lambdas::isSSme = [&]() { return (www.lep_pdgId().size() > 1) and (www.lep_pdgId()[0] * www.lep_pdgId()[1] == 143) and (abs(www.lep_pdgId()[1]) == 11); };

std::function<float()> Lambdas::GammaCR = [&]()
{
    
    if (not (www.met_pt() < 50.)) return false;
    return true;
};

std::function<float()> Lambdas::KinSelNj1ee(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&]() { return www.MTmax()>80.; }, // TODO : Need to add to baby maker
                        [&]() { return www.MTmax()>80.; }, // TODO
                        [&]() { return www.MTmax()>80.; }, // TODO
                        [&]() { return www.MTmax()>80.; }, // TODO
                        [&]() { return www.MTmax()>80.; }, // TODO
                        [&]() { return www.MTmax()>80.; }  // TODO
                        )()                                  )) return false;
        return true;
    };
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


