#ifndef lambdas_h
#define lambdas_h

#include "AnalysisConfig.h"
#include "InputConfig.h"
#include "wwwtree.h"
#include "scalefactors.h"
#include "rooutil.h"

#define DOCACHE

// Memoization to cache lambda results per event in order to save resource
// It checks whether the previous "result" is from the same event via checking run/lumi/evt
// If it is the same then return the cached "result"
// If it is not, then compute and save to "result" and update run/lumi/evt
std::function<float()> memoize(std::function<float()> foo);

namespace Variation
{
    enum Var
    {
        Up = 1,
        Down = -1
    };
}

namespace Lambdas
{

    //************************************************
    // Basic event selection
    //************************************************

    // Per event weighting
    extern std::function<float()> EventWeight;

    // very basic selections for each event
    extern std::function<float()> PreliminarySelection;

    // Trigger selection
    extern std::function<float()> TriggerSelection;

    //************************************************
    // Scale factors
    //************************************************

    // Trigger scale factor
    extern std::function<float()> TriggerScaleFactor;

    // Lepton scale factor
    extern std::function<float()> LeptonScaleFactor;

    // B-tagging scale factor
    extern std::function<float()> BTagScaleFactor;

    //************************************************
    // Weight systematic variations
    //************************************************
    // Lepton scale factor variations
    std::function<float()> LepSFVariation(Variation::Var var);

    // Trigger scale factor variations
    std::function<float()> TriggerSFVariation(Variation::Var var);

    // Btagging LF scale factor variations
    std::function<float()> BTagLFVariation(Variation::Var var);

    // Btagging HF scale factor variations
    std::function<float()> BTagHFVariation(Variation::Var var);

    // Pileup reweighting variations
    std::function<float()> PileupVariation(Variation::Var var);

    // PDF weight variations
    std::function<float()> PDFVariation(Variation::Var var);

    // Qsq weight variations
    std::function<float()> QsqVariation(Variation::Var var);

    // AlphaS weight variations
    std::function<float()> AlphaSVariation(Variation::Var var);

    //************************************************
    // Lepton multiplicity related selections
    //************************************************

    // This part contains selections related to selecting "two tight leptons", or "one tight + one loose" etc...
    extern std::function<float()> CutSRDilep; // Two tight leptons
    extern std::function<float()> CutSRTrilep; // Three tight leptons
    extern std::function<float()> CutCRTrilep; // Three tight leptons but with slightly different pt...
    extern std::function<float()> CutARDilep; // "AR" = Application region, so two loose and one tight
    extern std::function<float()> CutARTrilep; // "AR" = Application region, so three loose and two tight

    //************************************************
    // Event selections
    //************************************************

    // Split by channel
    extern std::function<float()> isSRSSeeChannel;
    extern std::function<float()> isSRSSemChannel;
    extern std::function<float()> isSRSSmmChannel;

    extern std::function<float()> TwoCenJet30; // Two central jets above 30 GeV 
    extern std::function<float()> LowDEtajj; // Low Detajj
    extern std::function<float()> LowMjj; // Low Mjj

    extern std::function<float()> MjjIn; // Mjj-in ee
    extern std::function<float()> MjjOut; // Mjj-out ee

    extern std::function<float()> ZVetoSS; // Same-sign Mll Z-veto

    extern std::function<float()> SSPreSelection;

    extern std::function<float()> SRSSeeSelection;
    extern std::function<float()> SRSSemSelection;
    extern std::function<float()> SRSSmmSelection;

    extern std::function<float()> SRSSSidemmSel;

    // Split by channel
    extern std::function<float()> is0SFOS;
    extern std::function<float()> is1SFOS;
    extern std::function<float()> is2SFOS;

    extern std::function<float()> ThreeLepPresel;

    extern std::function<float()> ZVeto3L;

    extern std::function<float()> DYVetoes0SFOS;
    extern std::function<float()> DYVetoes1SFOS;
    extern std::function<float()> DYVetoes2SFOS;

    extern std::function<float()> KinSel0SFOS;
    extern std::function<float()> KinSel1SFOS;
    extern std::function<float()> KinSel2SFOS;

    // Inverting z-veto for lost-lepton CR
    extern std::function<float()> HasZ_SS;
    extern std::function<float()> HasZ_3L;

}

bool passTrigger2016();

extern int this_run;
extern int this_lumi;
extern unsigned long long this_evt;

#endif
