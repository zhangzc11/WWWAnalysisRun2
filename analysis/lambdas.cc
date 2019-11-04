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
            pileupreweight.load(input.year);
            purewgt = pileupreweight.purewgt();
            // if (input.year == 2017 or input.year == 2018)
            //     purewgt = pileupreweight.purewgt();
            // if (input.year == 2016)
            //     purewgt = www.purewgt(); // 2016 ntuples have the weights already defined in the baby ntuples
        }

        //
        // Fake factor (= fake-rate / (1 - fake-rate)) weights
        //
        float ffwgt = 1;
        if (ana.do_fake_estimation)
        {
            ffwgt = fakerates.getFakeFactor();
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
            //   and (input.baby_version.EqualTo("5.1.4") or input.baby_version.EqualTo("5.1.6") or input.baby_version.EqualTo("5.1.8") or input.baby_version.EqualTo("5.1.9") or input.baby_version.Contains("5.2."))
            //    and (input.baby_type.EqualTo("Loose") or input.baby_type.EqualTo("WWW"))
            )
        {
            weight *= 163. / 405.27;
        }

        if (input.year == 2017)
        {
            if (input.current_file_name.Contains("www_amcatnlo_1.root") or input.current_file_name.Contains("vh_nonbb_amcatnlo_1.root"))
            {
                unsigned int genelemu = 0;
                for (unsigned int gidx = 0; gidx < www.genPart_pdgId().size(); ++gidx)
                {
                    if (abs(www.genPart_motherId()[gidx]) == 24 and (abs(www.genPart_pdgId()[gidx]) == 11 or abs(www.genPart_pdgId()[gidx]) == 13))
                        ++genelemu;
                }
                if (genelemu >= 2) weight = 0.;
            }
            if (input.current_file_name.Contains("www_2l_amcatnlo_1.root"))
                weight *= 0.119316*4.011538;
            if (input.current_file_name.Contains("vh_nonbb_2l_amcatnlo_"))
                weight *= 0.088057*3.552239;
        }
        if (input.year == 2018)
        {
            if (input.current_file_name.Contains("www_amcatnlo_1.root") or input.current_file_name.Contains("vh_nonbb_amcatnlo_1.root"))
            {
                unsigned int genelemu = 0;
                for (unsigned int gidx = 0; gidx < www.genPart_pdgId().size(); ++gidx)
                {
                    if (abs(www.genPart_motherId()[gidx]) == 24 and (abs(www.genPart_pdgId()[gidx]) == 11 or abs(www.genPart_pdgId()[gidx]) == 13))
                        ++genelemu;
                }
                if (genelemu >= 2) weight = 0.;
            }
            if (input.current_file_name.Contains("www_amcatnlo_dilepfilter_1.root"))
                weight *= 0.119316;
            if (input.current_file_name.Contains("vh_nonbb_amcatnlo_dilepfilter_"))
                weight *= 0.088057;
        }

        if (input.current_file_name.Contains("WWW2018_v5.1.8_v1/skim/grouped/bkgdata/wjets_incl_madgraph_1")) // bkgdata is when it runs over for ddfakes and this has some stupid large weight subtractions if anything this makes it more conservative
        {
            weight *= 0.;
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
        //return input.is_data ? 1 : www.trigsf();
        return 1;
    };

//______________________________________________________________________________________________
// Lepton scale factors
std::function<float()> Lambdas::LeptonScaleFactor = [&]()
    {
        // // the 2017 and 2018 doesn't have lepton scale factors saved to the branches in the WWW ttree
        // if (input.year == 2017 or input.year == 2018)
        //     return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
        // else
        //     return www.lepsf();
        return leptonScaleFactors.getScaleFactors(true, ana.do_fake_estimation, input.is_data);
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
/*        if (input.year == 2016)
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
*/
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
/*        if (input.year == 2016)
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
 */       {
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
      pileupreweight.load(input.year);
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
    /*    static Variation::FakeVar fakevar;
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

*/
                // TODO
                return float(1);
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

std::function<float()> Lambdas::LepPtThresholds(float val1, float val2, float val3)
{
  return [&, val1, val2, val3]()
    {
      if(val1>0 and www.nLlep() < 1) return false;
      if(val2>0 and www.nLlep() < 2) return false;
      if(val3>0 and www.nLlep() < 3) return false;
      if(val1>0 and www.lep_pt()[0] < val1) return false;
      if(val2>0 and www.lep_pt()[1] < val2) return false;
      if(val3>0 and www.lep_pt()[2] < val3) return false;
      return true;
    };
}

std::function<float()> Lambdas::PassCustomIsolation(float eleiso, float muoniso)
//POG: muon: iso < 0.15 has eff = 0.95 | tight WP, egamma: iso (from cutbased) < 0.0478+0.506/pT or 0.0658+0.963/pT for eff = 80% | medium WP recommended for W/Z
//for electrons choose 0.1 which is about 0.0658+0.963/20.
{
  return [&, eleiso, muoniso]()
    {
      int npass = 0;
      if(input.year==2016){
        if(www.nLlep()>=1 && abs(www.lep_pdgId()[0])==11 && www.lep_relIso03EAv2Lep()[0]<eleiso) ++npass;
        if(www.nLlep()>=2 && abs(www.lep_pdgId()[1])==11 && www.lep_relIso03EAv2Lep()[1]<eleiso) ++npass;
        if(www.nLlep()>=3 && abs(www.lep_pdgId()[2])==11 && www.lep_relIso03EAv2Lep()[2]<eleiso) ++npass;
        if(www.nLlep()>=1 && abs(www.lep_pdgId()[0])==13 && www.lep_relIso03EAv2Lep()[0]<muoniso) ++npass;
        if(www.nLlep()>=2 && abs(www.lep_pdgId()[1])==13 && www.lep_relIso03EAv2Lep()[1]<muoniso) ++npass;
        if(www.nLlep()>=3 && abs(www.lep_pdgId()[2])==13 && www.lep_relIso03EAv2Lep()[2]<muoniso) ++npass;
      } else {
        if(www.nLlep()>=1 && abs(www.lep_pdgId()[0])==11 && www.lep_relIso03EALep()[0]<eleiso) ++npass;
        if(www.nLlep()>=2 && abs(www.lep_pdgId()[1])==11 && www.lep_relIso03EALep()[1]<eleiso) ++npass;
        if(www.nLlep()>=3 && abs(www.lep_pdgId()[2])==11 && www.lep_relIso03EALep()[2]<eleiso) ++npass;
        if(www.nLlep()>=1 && abs(www.lep_pdgId()[0])==13 && www.lep_relIso03EALep()[0]<muoniso) ++npass;
        if(www.nLlep()>=2 && abs(www.lep_pdgId()[1])==13 && www.lep_relIso03EALep()[1]<muoniso) ++npass;
        if(www.nLlep()>=3 && abs(www.lep_pdgId()[2])==13 && www.lep_relIso03EALep()[2]<muoniso) ++npass;
      }
      return npass;
    };
}
std::function<float()> Lambdas::PassTightIsolation = [&]()
    {

        // lepton counters for various different kinds
        int ntightele = 0;   // < 0.05
        int nmediumele = 0;  // < 0.10
        int nlooseeleSS = 0; // < 0.40 (w/  3ch_agree)
        int nlooseele3l = 0; // < 0.40 (w/o 3ch_agree)
        int ntightmuo = 0;   // < 0.04
        int nmediummuo = 0;  // < 0.15
        int nloosemuo = 0;   // < 0.40

        // The 2016 version of EA correction uses "version-2"
        const std::vector<float>& reliso = (input.year == 2016) ? www.lep_relIso03EAv2Lep() : www.lep_relIso03EALep();

        // Loop over lepton container and count number of leptons of each category
        for (unsigned int i = 0; i < www.lep_pdgId().size(); ++i)
        {

            // Electron IDs
            if (abs(www.lep_pdgId()[i]) == 11)
            {
                if (www.lep_pass_VVV_fo()[i]    and reliso[i] < 0.05) ++ntightele;
                if (www.lep_pass_VVV_fo()[i]    and reliso[i] < 0.40) ++nlooseeleSS;
                if (www.lep_pass_VVV_3l_fo()[i] and reliso[i] < 0.40) ++nlooseele3l;
                if (www.lep_pass_VVV_3l_fo()[i] and reliso[i] < 0.10) ++nmediumele;
            }

            // Muon IDs
            if (abs(www.lep_pdgId()[i]) == 13)
            {
                if (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.04) ++ntightmuo;
                if (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.40) ++nloosemuo;
                if (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.15) ++nmediummuo;
            }

        }

        // If it is same-sign category
        if (www.nVlep() == 2)
        {

            // For data-driven estimate it will run over as if it's SR and require "loose-but-not-tight" requirements
            if (ana.do_fake_estimation)
            {
                // Passes 2 loose leptons but only 1 passes tight
                if ((nlooseeleSS + nloosemuo) == 2 and (ntightele + ntightmuo) == 1) return true;
            }
            else
            {
                // Passes 2 loose leptons and also 2 passes tight
                if ((nlooseeleSS + nloosemuo) == 2 and (ntightele + ntightmuo) == 2) return true;
            }

        }

        // If it is three lepton category
        if (www.nVlep() == 3)
        {

            // For data-driven estimate it will run over as if it's SR and require "loose-but-not-tight" requirements
            if (ana.do_fake_estimation)
            {

                // 0SFOS region eem
                if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 35) //eem
                {

                    // Of the "ee" in the "eem" leptons, only one electron fails the tight requirement
                    if (nlooseeleSS == 2 and nloosemuo == 1 and ntightele == 1 and nmediummuo == 1) return true;

                }

                // 0SFOS region emm
                else if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 37) //emm
                {

                    // Of the "mm" in the "emm" leptons, only one muon fails the tight requirement
                    if (nlooseele3l == 1 and nloosemuo == 2 and nmediumele == 1 and ntightmuo == 1) return true;

                }

                // The rest (i.e. 1SFOS or 2SFOS)
                else if (www.nSFOS() > 0)
                {

                    // Straight forward 3 loose and 2 tight
                    if ((nlooseele3l + nloosemuo) == 3 and (nmediumele + nmediummuo) == 2) return true;

                }

            }
            else
            {

                // 0SFOS region eem
                if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 35) //eem
                {

                    if ((nlooseeleSS + nloosemuo) == 3 and (ntightele + nmediummuo) == 3) return true;

                }

                // 0SFOS region emm
                else if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 37) //emm
                {

                    if ((nlooseele3l + nloosemuo) == 3 and (nmediumele + ntightmuo) == 3) return true;

                }

                // >=1SFOS region
                else if (www.nSFOS() > 0)
                {

                    if ((nlooseele3l + nloosemuo) == 3 and (nmediumele + nmediummuo) == 3) return true;

                }

            }
        }

        // If it reaches here, it failed to pass tight isolation so reject event
        return false;

    };

std::function<float()> Lambdas::PassTightIsolationAR = [&]()
    {

        // lepton counters for various different kinds
        int ntightele = 0;   // < 0.05
        int nmediumele = 0;  // < 0.10
        int nlooseeleSS = 0; // < 0.40 (w/  3ch_agree)
        int nlooseele3l = 0; // < 0.40 (w/o 3ch_agree)
        int ntightmuo = 0;   // < 0.04
        int nmediummuo = 0;  // < 0.15
        int nloosemuo = 0;   // < 0.40

        // The 2016 version of EA correction uses "version-2"
        const std::vector<float>& reliso = (input.year == 2016) ? www.lep_relIso03EAv2Lep() : www.lep_relIso03EALep();

        // Loop over lepton container and count number of leptons of each category
        for (unsigned int i = 0; i < www.lep_pdgId().size(); ++i)
        {

            // Electron IDs
            if (abs(www.lep_pdgId()[i]) == 11)
            {
                if (www.lep_pass_VVV_fo()[i]    and reliso[i] < 0.05) ++ntightele;
                if (www.lep_pass_VVV_fo()[i]    and reliso[i] < 0.40) ++nlooseeleSS;
                if (www.lep_pass_VVV_3l_fo()[i] and reliso[i] < 0.40) ++nlooseele3l;
                if (www.lep_pass_VVV_3l_fo()[i] and reliso[i] < 0.10) ++nmediumele;
            }

            // Muon IDs
            if (abs(www.lep_pdgId()[i]) == 13)
            {
                if (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.04) ++ntightmuo;
                if (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.40) ++nloosemuo;
                if (www.lep_pass_VVV_fo()[i] and reliso[i] < 0.15) ++nmediummuo;
            }

        }

        // If it is same-sign category
        if (www.nVlep() == 2)
        {

            // Passes 2 loose leptons but only 1 passes tight
            if ((nlooseeleSS + nloosemuo) == 2 and (ntightele + ntightmuo) == 1) return true;

        }

        // If it is three lepton category
        if (www.nVlep() == 3)
        {

            // 0SFOS region eem
            if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 35) //eem
            {

                // Of the "ee" in the "eem" leptons, only one electron fails the tight requirement
                if (nlooseeleSS == 2 and nloosemuo == 1 and ntightele == 1 and nmediummuo == 1) return true;

            }

            // 0SFOS region emm
            else if (www.nSFOS() == 0 and (abs(www.lep_pdgId()[0]) + abs(www.lep_pdgId()[1]) + abs(www.lep_pdgId()[2])) == 37) //emm
            {

                // Of the "mm" in the "emm" leptons, only one muon fails the tight requirement
                if (nlooseele3l == 1 and nloosemuo == 2 and nmediumele == 1 and ntightmuo == 1) return true;

            }

            // The rest (i.e. 1SFOS or 2SFOS)
            else if (www.nSFOS() > 0)
            {

                // Straight forward 3 loose and 2 tight
                if ((nlooseele3l + nloosemuo) == 3 and (nmediumele + nmediummuo) == 2) return true;

            }

        }

        // If it reaches here, it failed to pass tight isolation so reject event
        return false;

    };

//______________________________________________________________________________________________
// SR Dilepton selection
std::function<float()> Lambdas::CutSRDilep = [&]()
    {
        // Additional cuts for 2018 lepton IDs
        float mva_threshold = input.year == 2018 ? 7 : -1;
        // If the looper is looping over to do fake estimation, even though it is "SR dilep" selection require nTlep == 1, nLlep = 2. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        if(not(www.nVlep() == 2 and www.nLlep() == 2))          return false;
        if(not(Lambdas::LepPtThresholds(25.,25.,-1)()))         return false;
        if(not(getRawMVA(fabs(www.lep_MVA()[0])) > mva_threshold and getRawMVA(fabs(www.lep_MVA()[1])) > mva_threshold)) return false; // to be tested
        if (ana.do_fake_estimation){
          if(not(Lambdas::PassTightIsolationAR()))              return false;
          //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==1)) return false;
        }
        else {
          if(not(Lambdas::PassTightIsolation()))                return false;
          //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==2)) return false;
        }
        return true;
    };

//______________________________________________________________________________________________
// SR Trilepton selection
std::function<float()> Lambdas::CutSRTrilep = [&]()
    {
        // If the looper is looping over to do fake estimation, even though it is "SR trilep" selection require nTlep == 2, nLlep = 3. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        //float mva_threshold = input.year == 2018 ? 7 : -1;
        if(not(www.nVlep() == 3 and www.nLlep() == 3))          return false;
        if(not(Lambdas::LepPtThresholds(25.,20.,20.)()))        return false;
        //if(not(getRawMVA(fabs(www.lep_MVA()[0])) > mva_threshold and getRawMVA(fabs(www.lep_MVA()[1])) > mva_threshold) and getRawMVA(fabs(www.lep_MVA()[3])) > mva_threshold)) return false; // to be tested
        if (ana.do_fake_estimation){
          if(not(Lambdas::PassTightIsolationAR()))              return false;
          //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==2)) return false;
        }
        else {
          if(not(Lambdas::PassTightIsolation()))                return false;
          //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==3)) return false;
        }
        return true;
    };

//______________________________________________________________________________________________
// Lost-lepton CR Trilepton selection
std::function<float()> Lambdas::CutCRTrilep = [&]()
    {
        // NOTE: One thing to note here is that even though it is asking for 25/20/20 pt at a later cut stage higher pt cuts will be applied
        // For example, for the lost-lepton control regions for the same-sign channels, out of the 3 leptons it will be required that the two same-sign ones pass same-sign tight ID.
        // When this is required, it will implicitly require that the lep_pt is 25 GeV for the two same-sign leptons. This is a bit vague and could be improved...
        //float mva_threshold = input.year == 2018 ? 7 : -1;
        if(not(www.nVlep() == 3 and www.nLlep() == 3))        return false;
        if(not(Lambdas::LepPtThresholds(25.,20.,20.)()))      return false;
        //if(not(getRawMVA(fabs(www.lep_MVA()[0])) > mva_threshold and getRawMVA(fabs(www.lep_MVA()[1])) > mva_threshold) and getRawMVA(fabs(www.lep_MVA()[3])) > mva_threshold)) return false; // to be tested
        if(not(Lambdas::PassTightIsolation()))                return false;
        //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==3)) return false;
        return true;
    };

//______________________________________________________________________________________________
// AR Dilepton selection
std::function<float()> Lambdas::CutARDilep = [&]()
    {
        // Straight up application region selection. No fake factors are gonna be applied and the application region will be checked with data / MC
        float mva_threshold = input.year == 2018 ? 7 : -1;
        // If the looper is looping over to do fake estimation, even though it is "SR dilep" selection require nTlep == 1, nLlep = 2. (i.e. AR)
        // This is to ensure that the histogram outputs will have the same name with proper fake estimation
        if(not(www.nVlep() == 2 and www.nLlep() == 2))        return false;
        if(not(Lambdas::LepPtThresholds(25.,25.,-1)()))       return false;
        if(not(getRawMVA(fabs(www.lep_MVA()[0])) > mva_threshold and getRawMVA(fabs(www.lep_MVA()[1])) > mva_threshold)) return false; // to be tested
        if(not(Lambdas::PassTightIsolationAR()))              return false;
        //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==1)) return false;
        return true;
    };

//______________________________________________________________________________________________
// AR Trilepton selection
std::function<float()> Lambdas::CutARTrilep = [&]()
    {
        // Straight up application region selection. No fake factors are gonna be applied and the application region will be checked with data / MC
        //float mva_threshold = input.year == 2018 ? 7 : -1;
        if(not(www.nVlep() == 3 and www.nLlep() == 3))        return false;
        if(not(Lambdas::LepPtThresholds(25.,20.,20.)()))      return false;
        //if(not(getRawMVA(fabs(www.lep_MVA()[0])) > mva_threshold and getRawMVA(fabs(www.lep_MVA()[1])) > mva_threshold) and getRawMVA(fabs(www.lep_MVA()[3])) > mva_threshold)) return false; // to be tested
        if(not(Lambdas::PassTightIsolationAR()))              return false;
        //if(not(Lambdas::PassCustomIsolation(0.10,0.15)()==2)) return false;
        return true;
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

std::function<float()> Lambdas::isSRSSeeChannel = [&]() { return (www.passSSee())*(www.MllSS()>20.); };
std::function<float()> Lambdas::isSRSSemChannel = [&]() { return (www.passSSem())*(www.MllSS()>20.); };//2019/07/15: changed 30 --> 40
std::function<float()> Lambdas::isSRSSmmChannel = [&]() { return (www.passSSmm())*(www.MllSS()>20.); };
std::function<float()> Lambdas::isSRSS = [&]() { return (Lambdas::isSRSSeeChannel() or Lambdas::isSRSSemChannel() or Lambdas::isSRSSmmChannel()); };

std::function<float()> Lambdas::LeqOneJet(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var,
            [&]() { return (www.nj_up()<= 1); },
            [&]() { return (www.nj_dn()<= 1); },
            [&]() { return (www.nj()<= 1); },
            [&]() { return (www.nj_jerup()<= 1); },
            [&]() { return (www.nj_jerdn()<= 1); },
            [&]() { return (www.nj_jer()<= 1); }
            );
}

std::function<float()> Lambdas::LeqOneJet30(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var,
            [&]() { return (www.nj30_up()<= 1); },
            [&]() { return (www.nj30_dn()<= 1); },
            [&]() { return (www.nj30()<= 1); },
            [&]() { return (www.nj30_jerup()<= 1); },
            [&]() { return (www.nj30_jerdn()<= 1); },
            [&]() { return (www.nj30_jer()<= 1); }
            );
}

std::function<float()> Lambdas::OneCenJet30(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var,
            [&]() { return (www.nj30_up()== 1); },
            [&]() { return (www.nj30_dn()== 1); },
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
            [&]() { return (www.nj30_dn()>= 2); },
            [&]() { return (www.nj30()>= 2); },
            [&]() { return (www.nj30_jerup()>= 2); },
            [&]() { return (www.nj30_jerdn()>= 2); },
            [&]() { return (www.nj30_jer()>= 2); }
            );
}

std::function<float()> Lambdas::CenJet30Cut(Variation::ExpSyst expsyst, Variation::Var var, int value)
{
    return jetVar(expsyst, var,
            [&, value]() { return (www.nj30_up()>= value); },
            [&, value]() { return (www.nj30_dn()>= value); },
            [&, value]() { return (www.nj30()>= value); },
            [&, value]() { return (www.nj30_jerup()>= value); },
            [&, value]() { return (www.nj30_jerdn()>= value); },
            [&, value]() { return (www.nj30_jer()>= value); }
            );
}

std::function<float()> Lambdas::NumberCenJet30(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var,
            [&]() { return (www.nj30_up()); },
            [&]() { return (www.nj30_dn()); },
            [&]() { return (www.nj30()); },
            [&]() { return (www.nj30_jerup()); },
            [&]() { return (www.nj30_jerdn()); },
            [&]() { return (www.nj30_jer()); }
            );
}


std::function<float()> Lambdas::LowDEtajj(Variation::ExpSyst expsyst, Variation::Var var, float value)
{
    return jetVar(expsyst, var,
            [&, value]() { return (www.DetajjL_up()   < value); },
            [&, value]() { return (www.DetajjL_dn()   < value); },
            [&, value]() { return (www.DetajjL()      < value); },
            [&, value]() { return (www.DetajjL_jerup()< value); },
            [&, value]() { return (www.DetajjL_jerdn()< value); },
            [&, value]() { return (www.DetajjL_jer()  < value); }
            );
}

std::function<float()> Lambdas::LowMjj(Variation::ExpSyst expsyst, Variation::Var var,float value)
{
    return jetVar(expsyst, var,
            [&, value]() { return (www.MjjL_up()   < value); },
            [&, value]() { return (www.MjjL_dn()   < value); },
            [&, value]() { return (www.MjjL()      < value); },
            [&, value]() { return (www.MjjL_jerup()< value); },
            [&, value]() { return (www.MjjL_jerdn()< value); },
            [&, value]() { return (www.MjjL_jer()  < value); }
            );
}

std::function<float()> Lambdas::LowDEtaMJJ(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
      {
        if(not (Lambdas::LowDEtajj(expsyst,var, 2.5)())) return false;//DeltaEta < 2.5 // 2019/07/15: was 1.5  before
        if(not (Lambdas::LowMjj(   expsyst,var,500.)())) return false;//MjjL < 500     // 2019/07/15: was 400. before
        return true;
      };
}

std::function<float()> Lambdas::HighDeta(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
      {
        if( (Lambdas::LowDEtajj(expsyst,var, 2.5)())) return false;//DeltaEta > 2.5
        return true;
      };
}

std::function<float()> Lambdas::HighMJJ(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
      {
        if( (Lambdas::LowMjj(   expsyst,var,500.)())) return false;//MjjL > 500
        return true;
      };
}

std::function<float()> Lambdas::HighMJJDeta(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
      {
        if( (Lambdas::LowDEtajj(expsyst,var, 2.5)())) return false;//DeltaEta > 2.5
        if( (Lambdas::LowMjj(   expsyst,var,500.)())) return false;//MjjL > 500
        return true;
      };
}


std::function<float()> Lambdas::MjjIn(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var,
            [&]() { return (fabs(www.Mjj_up()   -80.)<15.); },
            [&]() { return (fabs(www.Mjj_dn()   -80.)<15.); },
            [&]() { return (fabs(www.Mjj()      -80.)<15.); },
            [&]() { return (fabs(www.Mjj_jerup()-80.)<15.); },
            [&]() { return (fabs(www.Mjj_jerdn()-80.)<15.); },
            [&]() { return (fabs(www.Mjj_jer()  -80.)<15.); }
            );
}

std::function<float()> Lambdas::MjjOut(Variation::ExpSyst expsyst, Variation::Var var)
{
    return jetVar(expsyst, var,
            [&]() { return (fabs(www.Mjj_up()   -80.)>=15.); },
            [&]() { return (fabs(www.Mjj_dn()   -80.)>=15.); },
            [&]() { return (fabs(www.Mjj()      -80.)>=15.); },
            [&]() { return (fabs(www.Mjj_jerup()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj_jerdn()-80.)>=15.); },
            [&]() { return (fabs(www.Mjj_jer()  -80.)>=15.); }
            );
}

std::function<float()> Lambdas::ZVetoSS = [&]() { return fabs(www.MllSS()-91.1876)>20.; };
std::function<float()> Lambdas::NBvetoSoft(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag){// kept the variations in case we need these
    return [&, expsyst, var, invert_btag]()
    {
        int nsoftbtag  = 0;
        for (unsigned int i = 0; i<www.svs_nTrks().size(); ++i)
        {
            bool passID = true;
            if (www.svs_nTrks().at(i) < 3)            passID = false;
            if (www.svs_distXYval().at(i) >= 3.0)     passID = false;
            if (www.svs_dist3Dsig().at(i) <= 4.0)     passID = false;
            if (cos(www.svs_anglePV().at(i)) <= 0.98) passID = false;
            if(passID) nsoftbtag++;
        }
        if((not invert_btag) and nsoftbtag > 0) return false;
        return true;
    };
}

std::function<float()> Lambdas::NBveto(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag){
    return [&, expsyst, var, invert_btag]()
    {
        if (not invert_btag)
        {
            if (not (
                        jetVar(expsyst, var,
                            [&]() { return (www.nb_up()   ==0); },
                            [&]() { return (www.nb_dn()   ==0); },
                            [&]() { return (www.nb()      ==0); },
                            [&]() { return (www.nb_jerup()==0); },
                            [&]() { return (www.nb_jerdn()==0); },
                            [&]() { return (www.nb_jer()  ==0); }
                            )()                                    )) return false;
        }
        else
        {
            if (not (
                        jetVar(expsyst, var,
                            [&]() { return (www.nb_up()   !=0); },
                            [&]() { return (www.nb_dn()   !=0); },
                            [&]() { return (www.nb()      !=0); },
                            [&]() { return (www.nb_jerup()!=0); },
                            [&]() { return (www.nb_jerdn()!=0); },
                            [&]() { return (www.nb_jer()  !=0); }
                            )()                                    )) return false;
        }
        return true;
    };
}

std::function<float()> Lambdas::NBcut(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag, int value){
  return [&, expsyst, var, invert_btag, value]()
    {
        if (invert_btag)
        {
            if (
                        jetVar(expsyst, var,
                            [&, value]() { return (www.nb_up()   >=value); },
                            [&, value]() { return (www.nb_dn()   >=value); },
                            [&, value]() { return (www.nb()      >=value); },
                            [&, value]() { return (www.nb_jerup()>=value); },
                            [&, value]() { return (www.nb_jerdn()>=value); },
                            [&, value]() { return (www.nb_jer()  >=value); }
                            )()                                    ) return false;
        }
        else
        {
            if (
                        jetVar(expsyst, var,
                            [&, value]() { return (www.nb_up()   <value); },
                            [&, value]() { return (www.nb_dn()   <value); },
                            [&, value]() { return (www.nb()      <value); },
                            [&, value]() { return (www.nb_jerup()<value); },
                            [&, value]() { return (www.nb_jerdn()<value); },
                            [&, value]() { return (www.nb_jer()  <value); }
                            )()                                    ) return false;
        }
        return true;
    };
}

std::function<float()> Lambdas::NBmedcut(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag, int value){
  return [&, expsyst, var, invert_btag, value]()
    {

      int nbmed = 0;
      //float cut = input.WP_DEEPCSV_MEDIUM;
      float cut = -999;
      if(input.year==2016) cut = 0.6321;
      if(input.year==2017) cut = 0.4941;
      if(input.year==2018) cut = 0.4184;
      float ptcut = 30.;
      float etacut = 2.4;
      if (expsyst == Variation::JES)
        {
          if (var == Variation::Up){
            for(unsigned int jdx = 0; jdx<www.jets_up_btag_score().size(); ++jdx){
              if(www.jets_up_p4()[jdx].Pt()<ptcut) continue;
              if(abs(www.jets_up_p4()[jdx].Eta())>etacut) continue;
              if(www.jets_up_btag_score()[jdx]>cut) ++nbmed;
            }
          }
          else if (var == Variation::Down){
            for(unsigned int jdx = 0; jdx<www.jets_dn_btag_score().size(); ++jdx){
              if(www.jets_dn_p4()[jdx].Pt()<ptcut) continue;
              if(abs(www.jets_dn_p4()[jdx].Eta())>etacut) continue;
              if(www.jets_dn_btag_score()[jdx]>cut) ++nbmed;
            }
          }
          else {
            for(unsigned int jdx = 0; jdx<www.jets_btag_score().size(); ++jdx){
              if(www.jets_p4()[jdx].Pt()<ptcut) continue;
              if(abs(www.jets_p4()[jdx].Eta())>etacut) continue;
              if(www.jets_btag_score()[jdx]>cut) ++nbmed;
            }
          }
        }
      else // else if (expsyst == Variation::JER)
        {
          if (var == Variation::Up){
            for(unsigned int jdx = 0; jdx<www.jets_jerup_btag_score().size(); ++jdx){
              if(www.jets_jerup_p4()[jdx].Pt()<ptcut) continue;
              if(abs(www.jets_jerup_p4()[jdx].Eta())>etacut) continue;
              if(www.jets_jerup_btag_score()[jdx]>cut) ++nbmed;
            }
          }
          else if (var == Variation::Down){
            for(unsigned int jdx = 0; jdx<www.jets_jerdn_btag_score().size(); ++jdx){
              if(www.jets_jerdn_p4()[jdx].Pt()<ptcut) continue;
              if(abs(www.jets_jerdn_p4()[jdx].Eta())>etacut) continue;
              if(www.jets_jerdn_btag_score()[jdx]>cut) ++nbmed;
            }
          }
          else {
            for(unsigned int jdx = 0; jdx<www.jets_jer_btag_score().size(); ++jdx){
              if(www.jets_jer_p4()[jdx].Pt()<ptcut) continue;
              if(abs(www.jets_jer_p4()[jdx].Eta())>etacut) continue;
              if(www.jets_jer_btag_score()[jdx]>cut) ++nbmed;
            }
          }
        }

        if (invert_btag)
        {
          if (nbmed>=value ) return false;
        }
        else
        {
          if (nbmed< value ) return false;
        }
        return true;
    };
}


std::function<float()> Lambdas::SSPreSelection(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag)
{
    return [&, expsyst, var, invert_btag]()
    {
        if (not (www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 )) return false;
        if (Lambdas::isSRSSeeChannel()){
          if (not Lambdas::ZVetoSS()) return false;
        }
        if(not (Lambdas::NBveto(expsyst,var,invert_btag)())) return false;//nb = 0
//        if(not (Lambdas::NBvetoSoft(expsyst,var)()))         return false;//nb soft = 0
        if(not (Lambdas::TwoCenJet30(expsyst,var)()))        return false;//nj30 >= 2

        return true;
    };
}

std::function<float()> Lambdas::METcut(Variation::ExpSyst expsyst, Variation::Var var,float value)
{
    return [&, expsyst, var, value]()
    {
        if (not (
                    jetVar(expsyst, var,
                           [&, value]() { return (www.met_up_pt()   >value); },
                           [&, value]() { return (www.met_dn_pt()   >value); },
                           [&, value]() { return (www.met_pt()      >value); },
                           [&, value]() { return (www.met_jerup_pt()>value); },
                           [&, value]() { return (www.met_jerdn_pt()>value); },
                           [&, value]() { return (www.met_jer_pt()  >value); }
                           )()                                  )) return false;
        return true;
    };
}
std::function<float()> Lambdas::Mllcut(float value)
{
  return [&, value]()
    { return www.MllSS() > value; };
}

std::function<float()> Lambdas::MTmaxcut(Variation::ExpSyst expsyst, Variation::Var var, float value)
{
    return [&, expsyst, var, value]()
    {
      if(www.nLlep()==2){
       if (not (
                    jetVar(expsyst, var,
                        [&, value]() { return www.MTmax_up()   >value; },
                        [&, value]() { return www.MTmax_dn()   >value; },
                        [&, value]() { return www.MTmax()      >value; },
                        [&, value]() { return www.MTmax_jerup()>value; },
                        [&, value]() { return www.MTmax_jerdn()>value; },
                        [&, value]() { return www.MTmax_jer()  >value; }
                        )()                                  )) return false;
      }
      if(www.nLlep()==3 and www.nSFOS()==1){
       if (not (
                    jetVar(expsyst, var,
                        [&, value]() { return www.MT3rd_up()   >value; },
                        [&, value]() { return www.MT3rd_dn()   >value; },
                        [&, value]() { return www.MT3rd()      >value; },
                        [&, value]() { return www.MT3rd_jerup()>value; },
                        [&, value]() { return www.MT3rd_jerdn()>value; },
                        [&, value]() { return www.MT3rd_jer()  >value; }
                        )()                                  )) return false;
      }
      if(www.nLlep()==3 and (not (www.nSFOS()==1)) ){
       if (not (
                    jetVar(expsyst, var,
                        [&, value]() { return www.MTmax3L_up()   >value; },
                        [&, value]() { return www.MTmax3L_dn()   >value; },
                        [&, value]() { return www.MTmax3L()      >value; },
                        [&, value]() { return www.MTmax3L_jerup()>value; },
                        [&, value]() { return www.MTmax3L_jerdn()>value; },
                        [&, value]() { return www.MTmax3L_jer()  >value; }
                        )()                                  )) return false;
      }
      return true;
    };
}


std::function<float()> Lambdas::MTmax3Lcut(Variation::ExpSyst expsyst, Variation::Var var, float value)
{
    return [&, expsyst, var, value]()
    {
       if (not (
                    jetVar(expsyst, var,
                        [&, value]() { return www.MTmax3L_up()   >value; },
                        [&, value]() { return www.MTmax3L_dn()   >value; },
                        [&, value]() { return www.MTmax3L()      >value; },
                        [&, value]() { return www.MTmax3L_jerup()>value; },
                        [&, value]() { return www.MTmax3L_jerdn()>value; },
                        [&, value]() { return www.MTmax3L_jer()  >value; }
                        )()                                  )) return false;
      return true;
    };
}

std::function<float()> Lambdas::DRljMinCut(Variation::ExpSyst expsyst, Variation::Var var, float value)
{
    return [&, expsyst, var, value]()
    {
      if(input.baby_version.EqualTo("1.2.2") or input.baby_version.EqualTo("3.0.17") or input.baby_version.EqualTo("5.1.4") or input.baby_version.EqualTo("5.1.5") or input.baby_version.EqualTo("5.1.6") or input.baby_version.EqualTo("5.1.7")) {


        if (not (www.lep_p4().size() > 1)) return false;

        if (not (jetVar(expsyst, var,
            [&]() { return www.jets30_up_p4().size(); },
            [&]() { return www.jets30_dn_p4().size(); },
            [&]() { return www.jets30_p4().size(); },
            [&]() { return www.jets30_jerup_p4().size(); },
            [&]() { return www.jets30_jerdn_p4().size(); },
            [&]() { return www.jets30_jer_p4().size(); }
            )() != 1 )) return false;

        float minDRlj=9e5;
        unsigned int numjets = Lambdas::NumberCenJet30(expsyst,var)();
        for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
          for(unsigned int j = 0; j<numjets; ++j){//now all jets - that's not what I want
            LV jet = jetVec(expsyst, var,
                            [&]() { return www.jets30_up_p4()[j]; },
                            [&]() { return www.jets30_dn_p4()[j]; },
                            [&]() { return www.jets30_p4()[j]; },
                            [&]() { return www.jets30_jerup_p4()[j]; },
                            [&]() { return www.jets30_jerdn_p4()[j]; },
                            [&]() { return www.jets30_jer_p4()[j]; }
                            )();
            float DRtemp = fabs(RooUtil::Calc::DeltaR(www.lep_p4()[i], jet));
            if(DRtemp<minDRlj) minDRlj = DRtemp;
          }
        }
        return minDRlj < value;
      }
      if (not (
               jetVar(expsyst, var,
                      [&, value]() { return www.DRljmin_up()   <value; },
                      [&, value]() { return www.DRljmin_dn()   <value; },
                      [&, value]() { return www.DRljmin()      <value; },
                      [&, value]() { return www.DRljmin_jerup()<value; },
                      [&, value]() { return www.DRljmin_jerdn()<value; },
                      [&, value]() { return www.DRljmin_jer()  <value; }
                      )()                                  )) return false;
      return true;

    };
}

std::function<float()> Lambdas::DRljMin3LCut(Variation::ExpSyst expsyst, Variation::Var var, float value)
{
    return [&, expsyst, var, value]()
    {
      if(input.baby_version.EqualTo("1.2.2") or input.baby_version.EqualTo("3.0.17") or input.baby_version.EqualTo("5.1.4") or input.baby_version.EqualTo("5.1.5") or input.baby_version.EqualTo("5.1.6") or input.baby_version.EqualTo("5.1.7")) {


        if (not (www.lep_p4().size() > 1)) return false;

        if (not (jetVar(expsyst, var,
            [&]() { return www.jets30_up_p4().size(); },
            [&]() { return www.jets30_dn_p4().size(); },
            [&]() { return www.jets30_p4().size(); },
            [&]() { return www.jets30_jerup_p4().size(); },
            [&]() { return www.jets30_jerdn_p4().size(); },
            [&]() { return www.jets30_jer_p4().size(); }
            )() != 1 )) return false;

        float minDRlj=9e5;
        unsigned int numjets = Lambdas::NumberCenJet30(expsyst,var)();
        for(unsigned int i = 0; i<www.lep_p4().size(); ++i){
          for(unsigned int j = 0; j<numjets; ++j){//now all jets - that's not what I want
            LV jet = jetVec(expsyst, var,
                            [&]() { return www.jets30_up_p4()[j]; },
                            [&]() { return www.jets30_dn_p4()[j]; },
                            [&]() { return www.jets30_p4()[j]; },
                            [&]() { return www.jets30_jerup_p4()[j]; },
                            [&]() { return www.jets30_jerdn_p4()[j]; },
                            [&]() { return www.jets30_jer_p4()[j]; }
                            )();
            float DRtemp = fabs(RooUtil::Calc::DeltaR(www.lep_p4()[i], jet));
            if(DRtemp<minDRlj) minDRlj = DRtemp;
          }
        }
        return minDRlj < value;
      }
      if (not (
               jetVar(expsyst, var,
                      [&, value]() { return www.DRljmin3L_up()   >value; },
                      [&, value]() { return www.DRljmin3L_dn()   >value; },
                      [&, value]() { return www.DRljmin3L()      >value; },
                      [&, value]() { return www.DRljmin3L_jerup()>value; },
                      [&, value]() { return www.DRljmin3L_jerdn()>value; },
                      [&, value]() { return www.DRljmin3L_jer()  >value; }
                      )()                                  )) return false;
      return true;

    };
}

std::function<float()> Lambdas::SSKinSel(Variation::ExpSyst expsyst, Variation::Var var){
    return [&, expsyst, var]()
    {
        if(not (Lambdas::Mllcut(20.)()))                 return false;
        if(not (Lambdas::METcut(expsyst,var,45.)()))     return false;
        if (not (Lambdas::isSRSSmmChannel())){
          if(not (Lambdas::MTmaxcut(expsyst,var,90.)())) return false;
        }
        return true;
    };
}

std::function<float()> Lambdas::SSMjjIn(Variation::ExpSyst expsyst, Variation::Var var){
    return [&, expsyst, var]()
    {
        if(not (Lambdas::MjjIn(expsyst,var)())) return false;
        return true;
    };
}

std::function<float()> Lambdas::SSMjjOut(Variation::ExpSyst expsyst, Variation::Var var){
    return [&, expsyst, var]()
    {
        if(not (Lambdas::MjjOut(expsyst,var)())) return false;
        return true;
    };
}

std::function<float()> Lambdas::SS1JPreselection(Variation::ExpSyst expsyst, Variation::Var var, bool invert_btag){
    return [&, expsyst, var,invert_btag]()
    {
        if (not (www.nisoTrack_mt2_cleaned_VVV_cutbased_veto()==0 )) return false;
        if (Lambdas::isSRSSeeChannel()){
          if (not Lambdas::ZVetoSS()) return false;
        }
        if(not (Lambdas::NBveto(expsyst,var,invert_btag)())) return false;//nb = 0
        if(not (Lambdas::OneCenJet30(expsyst,var)()))        return false;
//        if(not (Lambdas::NBvetoSoft(expsyst,var)()))         return false;//nb soft = 0
        return true;
    };
}

std::function<float()> Lambdas::SS1J(Variation::ExpSyst expsyst, Variation::Var var){
    return [&, expsyst, var]()
    {
        if(not (Lambdas::Mllcut(20.)()))                 return false;
        if(not (Lambdas::METcut(expsyst,var,45.)()))     return false;
        if(not (Lambdas::MTmaxcut(expsyst,var,90.)()))   return false;
        if(not (Lambdas::DRljMinCut(expsyst,var,1.5)())) return false;
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
        if(not (Lambdas::LeqOneJet30(expsyst,var)()))        return false;
        if(not (Lambdas::NBveto(expsyst,var,invert_btag)())) return false;
//        if(not (Lambdas::NBvetoSoft(expsyst,var)()))         return false;
        if(Lambdas::is0SFOS()){
          if(not (www.lep_p4()[2].Pt()>25.))                 return false;
          if(not (www.lep_p4()[1].Pt()>25.))                 return false;
          if(not (www.lep_p4()[0].Pt()>25.))                 return false;
        }
        if(Lambdas::is1SFOS() or Lambdas::is2SFOS()){
          if(Lambdas::CenJet30Cut(expsyst,var,1)())          return false;
        }
        return true;
    };
}

std::function<float()> Lambdas::DYVetoes = [&]()
{
        if(Lambdas::is0SFOS()){
          if (not (Lambdas::DYVetoes0SFOS())) return false;
        }
        if(Lambdas::is1SFOS()){
          if (not (Lambdas::DYVetoes1SFOS())) return false;
        }
        if(Lambdas::is2SFOS()){
          if (not (Lambdas::DYVetoes2SFOS())) return false;
        }
        return true;
};

std::function<float()> Lambdas::DYAndZVetoes = [&]()
{
  if (not (Lambdas::DYVetoes())) return false;
  if (not (Lambdas::ZVeto3L() )) return false;
  return true;
};


std::function<float()> Lambdas::DYVetoes0SFOS = [&]()
    {
        if (not (www.Mll3L() > 20.             )) return false;
        if (not (abs(www.M3l()-91.1876) > 10.  )) return false;
        if (not (abs(www.Mee3L()-91.1876) > 20.)) return false;
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

std::function<float()> Lambdas::DPhi3lMETcut(Variation::ExpSyst expsyst, Variation::Var var, float value)
{
    return [&, expsyst, var, value]()
    {
        if (not (
                    jetVar(expsyst, var,
                        [&, value]() { return (www.DPhi3lMET_up()   >value); },
                        [&, value]() { return (www.DPhi3lMET_dn()   >value); },
                        [&, value]() { return (www.DPhi3lMET()      >value); },
                        [&, value]() { return (www.DPhi3lMET_jerup()>value); },
                        [&, value]() { return (www.DPhi3lMET_jerdn()>value); },
                        [&, value]() { return (www.DPhi3lMET_jer()  >value); }
                        )()                                       )) return false;
        return true;
    };
}

std::function<float()> Lambdas::KinSel3L(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      if(Lambdas::is0SFOS()){
        return true;//right now I don't apply anything, best option seems to be tightening IDs only
      }
      else {
        //if(not (Lambdas::METcut(expsyst,var,60.)()))       return false;
        if(not (Lambdas::MTmaxcut(expsyst,var,90.)()))     return false;
        if(not (www.Pt3l() > 50.    ))                     return false;
        if(not (Lambdas::DPhi3lMETcut(expsyst,var,2.5)())) return false;
      }
      return true;
    };
}

std::function<float()> Lambdas::KinSel3LInvertMTmax(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      //if(not (Lambdas::METcut(expsyst,var,60.)()))       return false;
      if(    (Lambdas::MTmaxcut(expsyst,var,90.)()))     return false;
      if(not (www.Pt3l() > 50.    ))                     return false;
      if(not (Lambdas::DPhi3lMETcut(expsyst,var,2.5)())) return false;
      return true;
    };
}

std::function<float()> Lambdas::KinSel3LInvertPt3l(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      //if(not (Lambdas::METcut(expsyst,var,60.)()))       return false;
      if(not (Lambdas::MTmaxcut(expsyst,var,90.)()))     return false;
      if(    (www.Pt3l() > 50.    ))                     return false;
      if(not (Lambdas::DPhi3lMETcut(expsyst,var,2.5)())) return false;
      return true;
   };
}

std::function<float()> Lambdas::KinSel3LInvertDPhi(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      //if(not (Lambdas::METcut(expsyst,var,60.)()))       return false;
      if(not (Lambdas::MTmaxcut(expsyst,var,90.)()))     return false;
      if(not (www.Pt3l() > 50.    ))                     return false;
      if(    (Lambdas::DPhi3lMETcut(expsyst,var,2.5)())) return false;
      return true;
    };
}
std::function<float()> Lambdas::KinSel3LInvertExOne(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      if(Lambdas::KinSel3LInvertMTmax(expsyst, var)()) return true;
      if(Lambdas::KinSel3LInvertPt3l( expsyst, var)()) return true;
      if(Lambdas::KinSel3LInvertDPhi( expsyst, var)()) return true;
      return false;
    };
}
std::function<float()> Lambdas::KinSel3LInvertOne(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      if(not (Lambdas::MTmaxcut(expsyst,var,90.)()))     return true;
      if(not (www.Pt3l() > 50.    ))                     return true;
      if(not (Lambdas::DPhi3lMETcut(expsyst,var,2.5)())) return true;
      return false;
    };
}
std::function<float()> Lambdas::KinSel3LInvertAll(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      if(    (Lambdas::MTmaxcut(expsyst,var,90.)()))     return false;
      if(    (www.Pt3l() > 50.    ))                     return false;
      if(    (Lambdas::DPhi3lMETcut(expsyst,var,2.5)())) return false;
      return true;
    };
}


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

std::function<float()> Lambdas::HasZ_SS = [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.); };//2019/07/16: changed this from 10 to 20 GeV to unify things
std::function<float()> Lambdas::HasZ_3L = [&]() { return (abs(www.Mll3L()-91.1876)<20.||abs(www.Mll3L1()-91.1876)<20.); };
std::function<float()> Lambdas::HasZcand_SS = [&]() { return (www.nSFOS()>=1); };//no Z mass window
std::function<float()> Lambdas::HasZcand_3L = [&]() { return (www.nSFOS()>=1); };//no Z mass window

std::function<float()> Lambdas::isWZCRSScand = [&]() {//no Z mass window
        if (not (Lambdas::HasZcand_SS() ))             return false;
        if (www.lep_idx0_SS()<0)                       return false;
        if (www.lep_idx1_SS()<0)                       return false;
        if (www.lep_p4()[www.lep_idx0_SS() ].Pt()<25.) return false;
        if (www.lep_p4()[www.lep_idx1_SS() ].Pt()<25.) return false;
        return true;
};

std::function<float()> Lambdas::isWZCRSS = [&]() {//Z mass window
        if (not (Lambdas::HasZ_SS() ))                 return false;//nSFOS>=1 does not work, so do the lep3idx thing
        if (www.lep_idx0_SS()<0)                       return false;
        if (www.lep_idx1_SS()<0)                       return false;
        if (www.lep_p4()[www.lep_idx0_SS() ].Pt()<25.) return false;
        if (www.lep_p4()[www.lep_idx1_SS() ].Pt()<25.) return false;
        int lep3idx = 0;
        if(www.lep_idx0_SS()==0 || www.lep_idx1_SS()==0) lep3idx = 1;
        if(www.lep_idx0_SS()==1 || www.lep_idx1_SS()==1) lep3idx = 2;
        if( ((www.lep_pdgId()[www.lep_idx0_SS()])!=(-(www.lep_pdgId()[lep3idx]))) and ((www.lep_pdgId()[www.lep_idx1_SS()])!=(-(www.lep_pdgId()[lep3idx]))) ) return false;
        return true;
};

std::function<float()> Lambdas::isWZCR3L = [&]() {
        if (not (Lambdas::HasZcand_3L() ))             return false;
        if (not (Lambdas::HasZ_3L() ))                 return false;
        return true;
};

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
        if (not (www.Mll3L()  > 20.                    )) return false;
        if (not (www.Mll3L1() > 20. or www.Mll3L1() < 0)) return false;
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

std::function<float()> Lambdas::is0SFOSeem = [&]() { return (www.lep_pdgId().size() > 2) and (Lambdas::is0SFOS()) and ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2]))==35); };
std::function<float()> Lambdas::is0SFOSemm = [&]() { return (www.lep_pdgId().size() > 2) and (Lambdas::is0SFOS()) and ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2]))==37); };


std::function<float()> Lambdas::GammaCR(Variation::ExpSyst expsyst, Variation::Var var)//does not work anymore, as we don't have a MET cut
{
    return [&, expsyst, var]()
    {
        if(Lambdas::is0SFOS()){
          if( (Lambdas::METcut(expsyst,var,30.)())) return false;//nb = 0
        }
        if(Lambdas::is1SFOS()){
          if( (Lambdas::METcut(expsyst,var,45.)())) return false;//nb = 0
        }
        if(Lambdas::is2SFOS()){
          if( (Lambdas::METcut(expsyst,var,60.)())) return false;//nb = 0
        }
      return true;
    };
}

std::function<float()> Lambdas::GammaCRLowMT(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
        if(Lambdas::is0SFOS()){
          return false;//need to veto 0 SFOS
        }
        else if(Lambdas::is1SFOS() or Lambdas::is2SFOS()){
          if(Lambdas::MTmaxcut(expsyst,var,90.)())     return false;
        }
        return true;
    };
}
std::function<float()> Lambdas::GammaCRLowPt3l = [&]() { return ((www.nSFOS()>0) and (www.Pt3l() <= 50.)); };//need to veto 0 SFOS


std::function<float()> Lambdas::ttZWZfitRegion(Variation::ExpSyst expsyst, Variation::Var var)
{
    return [&, expsyst, var]()
    {
      if(not (Lambdas::TwoCenJet30(expsyst,var)()))        return false;//nj30 >= 2
      if(    (Lambdas::ZVeto3L() ))                        return false;//has a Z
      return true;
    };
}



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


//_______________________________________________________________________________________________________
// Because EGamma POG decided to be stupid
float getRawMVA(float notraw)
{
    if (notraw >  1.0-1.e-6) notraw =  1.0-1.e-6; // protect against inf, -inf due to FP rounding issues
    if (notraw < -1.0+1.e-6) notraw = -1.0+1.e-6;
    return -0.5*log((2.0/(notraw+1))-1.0);
}

//_______________________________________________________________________________________________________
float Lambdas::fake_iso(int idx, int pdgid)
{
    if (www.lep_pdgId().size() < 1)
        return float(-999.);

    float maxiso = -1;
    bool isfake = false;
    float ptcor = -1;//0: <20, 1: 20-25, 2: 25-30, 3: 30-35, 4: 35-50, 5: 50-inf //+0.5
    float eta = -1;//0: <1.6, +6: for >=6

    const float thresh3l = (abs(pdgid) == 11 ? 0.10 : 0.15);
    const float threshss = (abs(pdgid) == 11 ? 0.05 : 0.04);
    const float thresh = ((www.nVlep() == 2) or (www.nVlep() == 3 and www.nSFOS() == 0)) ? threshss : thresh3l;

    vector<float> reliso = ((input.year == 2016) ? (www.lep_relIso03EAv2Lep()) : (www.lep_relIso03EALep()));

    for (unsigned int i = 0; i < reliso.size(); ++i)
    {

        if (abs(www.lep_pdgId()[i]) != pdgid)
            continue;
        if (www.lep_motherIdSS()[i] >= 0)
            continue;
        if (www.lep_motherIdSS()[i] == (-3))
            continue;

        if (reliso[i] > maxiso)
            maxiso = reliso[i];
        else
            continue;

        isfake = true;

        if (abs(www.lep_p4()[i].Eta()) < 1.6)
            eta = 0.;
        else
            eta = 5.;

        float lepcorpt = www.lep_pt()[i];
        lepcorpt *= (1. + std::max(0., (double) reliso[i] - thresh));

        if (lepcorpt < 20.)
            ptcor = 0;
        else if (lepcorpt < 25.)
            ptcor = 1;
        else if (lepcorpt < 30.)
            ptcor = 2;
        else if (lepcorpt < 35.)
            ptcor = 3;
        else
            ptcor = 4;
    }

    if (isfake)
    {
        if (idx == ptcor + eta)
        {
            return maxiso;
        }
        else
        {
            return -999.;
        }
    }
    else
    {
        return -999.;
    }

}

// ana.histograms.addHistogram("ele_fake_ptcoretahist"      ,  14 , 0.0     , 14.0    , [&]() {
//         if (www.lep_pdgId().size()<1) return float(-999.);
//         vector<float> reliso = ((input.year == 2016) ? (www.lep_relIso03EAv2Lep()) : (www.lep_relIso03EALep()));
//         float maxeleiso = -1;
//         bool fakeele = false;
//         float ptcor = -1;//0: <20, 1: 20-25, 2: 25-30, 3: 30-35, 4: 35-50, 5: 50-inf //+0.5
//         float eta = -1;//0: <1.6, +6: for >=6
//         for(unsigned int i = 0; i<reliso.size(); ++i){
//         if(abs(www.lep_pdgId()[i])!=11)   continue;
//         if(www.lep_motherIdSS()[i]>=0)    continue;
//         if(www.lep_motherIdSS()[i]==(-3)) continue;
//         if(reliso[i]>maxeleiso) maxeleiso = reliso[i];
//         else                    continue;
//         fakeele = true;
//         if(abs(www.lep_p4()[i].Eta())<1.6) eta = 0.;
//         else                               eta = 7.;
//         float lepcorpt = www.lep_pt()[i];
//         if((www.nSFOS()>=1) or (www.nSFOS()==0 and ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2]))==37) ) ) lepcorpt *= (1.+std::max(0.,reliso[i]-0.10));
//         else lepcorpt *= (1.+std::max(0.,reliso[i]-0.05));
//         if(     lepcorpt<20.)  ptcor = 1.5;
//         else if(lepcorpt<25.)  ptcor = 2.5;
//         else if(lepcorpt<30.)  ptcor = 3.5;
//         else if(lepcorpt<35.)  ptcor = 4.5;
//         else if(lepcorpt<50.)  ptcor = 5.5;
//         else                   ptcor = 6.5;
//         }
//         if(fakeele) return ptcor+eta;
//         return float(-999.);
// });
// ana.histograms.addHistogram("muo_fake_ptcoretahist"      ,  14 , 0.0     , 14.0    , [&]() {
//         if (www.lep_pdgId().size()<1) return float(-999.);
//         vector<float> reliso = ((input.year == 2016) ? (www.lep_relIso03EAv2Lep()) : (www.lep_relIso03EALep()));
//         float maxeleiso = -1.;
//         bool fakemuo = false;
//         float ptcor = -1;//0: <20, 1: 20-25, 2: 25-30, 3: 30-35, 4: 35-50, 5: 50-inf //+0.5
//         float eta = -1;//0: <1.6, +6: for >=6
//         for(unsigned int i = 0; i<reliso.size(); ++i){
//         if(abs(www.lep_pdgId()[i])!=13)   continue;
//         if(www.lep_motherIdSS()[i]>=0)    continue;
//         if(www.lep_motherIdSS()[i]==(-3)) continue;
//         if(reliso[i]>maxeleiso) maxeleiso = reliso[i];
//         else                    continue;
//         fakemuo = true;
//         if(abs(www.lep_p4()[i].Eta())<1.6) eta = 0.;
//         else                               eta = 7.;
//         float lepcorpt = www.lep_pt()[i];
//         if((www.nSFOS()>=1) or (www.nSFOS()==0 and ((abs(www.lep_pdgId()[0])+abs(www.lep_pdgId()[1])+abs(www.lep_pdgId()[2]))==35) ) ) lepcorpt *= (1.+std::max(0.,reliso[i]-0.15));
//         else lepcorpt *= (1.+std::max(0.,reliso[i]-0.04));
//         if(     lepcorpt<20.)  ptcor = 1.5;
//         else if(lepcorpt<25.)  ptcor = 2.5;
//         else if(lepcorpt<30.)  ptcor = 3.5;
//         else if(lepcorpt<35.)  ptcor = 4.5;
//         else if(lepcorpt<50.)  ptcor = 5.5;
//         else                   ptcor = 6.5;
//         }
//         if(fakemuo) return ptcor+eta;
//         return float(-999.);
// });

