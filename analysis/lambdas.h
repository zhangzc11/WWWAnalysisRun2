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
        Nominal = 0,
        Up = 1,
        Down = -1
    };

    enum FakeVar
    {
        Full = 1,
        Rate,
        RateEl,
        RateMu,
        RateSSEl,
        RateSSMu,
        Rate3LEl,
        Rate3LMu,
        Closure,
        ClosureEl,
        ClosureMu,
        ClosureSSEl,
        ClosureSSMu,
        Closure3LEl,
        Closure3LMu,
    };

    enum ExpSyst
    {
        JES = 1,
        JER
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

    // Fake factor variation
    std::function<float()> FakeFactorVariation(Variation::FakeVar fakevar, Variation::Var var);

    //************************************************
    // Lepton multiplicity related selections
    //************************************************

    // This part contains selections related to selecting "two tight leptons", or "one tight + one loose" etc...
    std::function<float()> LepPtThresholds(float val1=25., float val2=25., float val3=-1.);
    std::function<float()> PassCustomIsolation(float eleiso=0.10, float muoniso=0.15);

    extern std::function<float()> PassTightIsolation;
    extern std::function<float()> PassTightIsolationAR;
    extern std::function<float()> CutSRDilep; // Two tight leptons
    extern std::function<float()> CutSRTrilep; // Three tight leptons
    extern std::function<float()> CutCRTrilep; // Three tight leptons but with slightly different pt...
    extern std::function<float()> CutARDilep; // "AR" = Application region, so two loose and one tight
    extern std::function<float()> CutARTrilep; // "AR" = Application region, so three loose and two tight

    //************************************************
    // Event selections
    //************************************************

    // Helper functions to concisely define JES/JER variations
    std::function<float()> jetVar(Variation::ExpSyst, Variation::Var,
            std::function<float()>, // Nominal JES
            std::function<float()>, // JES Up
            std::function<float()>, // JES Down
            std::function<float()>, // Nominal JER
            std::function<float()>, // JER Up
            std::function<float()>  // JER Down
            );

    // Helper functions to concisely define JES/JER variations
    std::function<LV()> jetVec(Variation::ExpSyst, Variation::Var,
            std::function<LV()>, // Nominal JES
            std::function<LV()>, // JES Up
            std::function<LV()>, // JES Down
            std::function<LV()>, // Nominal JER
            std::function<LV()>, // JER Up
            std::function<LV()>  // JER Down
            );

    // Split by channel
    extern std::function<float()> isSRSSeeChannel;
    extern std::function<float()> isSRSSemChannel;
    extern std::function<float()> isSRSSmmChannel;
    extern std::function<float()> isSRSS;

    std::function<float()> CenJet30Cut(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, int value = 0);
    std::function<float()> LeqOneJet(     Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); 
    std::function<float()> LeqOneJet30(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // Less than or equal to One jets above 30 GeV 
    std::function<float()> OneCenJet30(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // One central jets above 30 GeV 
    std::function<float()> TwoCenJet30(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // Two central jets above 30 GeV 
    std::function<float()> NumberCenJet30(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);  
    std::function<float()> NBveto(        Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false);
    std::function<float()> NBvetoSoft(    Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false);
    std::function<float()> NBcut(         Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false, int value = 1);
    std::function<float()> NBmedcut(      Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false, int value = 1);
    std::function<float()> LowDEtajj(     Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, float value = 2.5); // Low Detajj
    std::function<float()> LowMjj(        Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, float value = 500.); // Low Mjj
    std::function<float()> LowDEtaMJJ(    Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // Low Mjj and Detajj
    std::function<float()> HighDeta(      Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // High Detajj
    std::function<float()> HighMJJ(       Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // High Mjj
    std::function<float()> HighMJJDeta(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // High Mjj and Detajj

    std::function<float()> MjjIn(         Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // Mjj-in ee
    std::function<float()> MjjOut(        Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal); // Mjj-out ee

    extern std::function<float()> ZVetoSS; // Same-sign Mll Z-veto
    std::function<float()> METcut(      Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, float value=60.);
    std::function<float()> Mllcut(      float value);
    std::function<float()> MTmaxcut(    Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal,float value=90.);
    std::function<float()> MTmax3Lcut(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal,float value=90.);
    std::function<float()> DRljMinCut(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, float value = 1.5); // Low Mjj
    std::function<float()> DRljMin3LCut(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, float value = 1.5); // Low Mjj

    std::function<float()> SSPreSelection(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false);
    std::function<float()> SSKinSel(        Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> SSMjjIn(         Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> SSMjjOut(        Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> SS1JPreselection(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false);
    std::function<float()> SS1J(            Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);

    std::function<float()> SRSSeeSelection( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> SRSSemSelection( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> SRSSmmSelection( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);

    std::function<float()> SRSSSidemmSel(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);

    // Split by channel
    extern std::function<float()> is0SFOS;
    extern std::function<float()> is1SFOS;
    extern std::function<float()> is2SFOS;

    std::function<float()> ThreeLepPresel(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, bool invert_btag=false);

    extern std::function<float()> ZVeto3L;
    extern std::function<float()> DYAndZVetoes;
    extern std::function<float()> DYVetoes;
    extern std::function<float()> DYVetoes0SFOS;
    extern std::function<float()> DYVetoes1SFOS;
    extern std::function<float()> DYVetoes2SFOS;
    std::function<float()> DPhi3lMETcut(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal, float value=2.1);
    std::function<float()> KinSel3L(    Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel0SFOS( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel1SFOS( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel2SFOS( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel3LInvertExOne(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel3LInvertOne(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel3LInvertMTmax(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel3LInvertDPhi( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel3LInvertPt3l( Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> KinSel3LInvertAll(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);

    
    // Inverting z-veto for lost-lepton CR
    extern std::function<float()> HasZ_SS;
    extern std::function<float()> HasZ_3L;
    extern std::function<float()> HasZcand_SS;
    extern std::function<float()> HasZcand_3L;

    // Split by channel
    extern std::function<float()> isSSem;
    extern std::function<float()> isSSme;
    extern std::function<float()> is0SFOSeem;
    extern std::function<float()> is0SFOSemm;

    extern std::function<float()> isWZCRSS;
    extern std::function<float()> isWZCRSScand;
    extern std::function<float()> isWZCR3L;
    
    std::function<float()> Nj1DRljMin(   Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()> Nj1CRKinSel(  Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);

    // Gamma CR
    std::function<float()>        GammaCR(     Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    std::function<float()>        GammaCRLowMT(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);
    extern std::function<float()> GammaCRLowPt3l;

    std::function<float()> ttZWZfitRegion(Variation::ExpSyst expsyst=Variation::JES, Variation::Var var=Variation::Nominal);

    std::function<float()> KinSelNj1ee(   Variation::ExpSyst expsyst, Variation::Var var);

    float fake_iso(int idx, int pdgid);
}

bool passTrigger2016();

extern int this_run;
extern int this_lumi;
extern unsigned long long this_evt;

float getRawMVA(float raw);

#endif
