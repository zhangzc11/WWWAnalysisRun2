#ifndef scalefactors_h
#define scalefactors_h

#include "wwwtree.h"
#include "rooutil/rooutil.h"

//_______________________________________________________________________________________________________
class LeptonScaleFactors
{
    public:
        RooUtil::HistMap* histmap_lead_mu_recoid_sf;
        RooUtil::HistMap* histmap_subl_mu_recoid_sf;
        RooUtil::HistMap* histmap_lead_el_recoid_sf;
        RooUtil::HistMap* histmap_subl_el_recoid_sf;
        RooUtil::HistMap* histmap_lead_el_mva_sf;
        RooUtil::HistMap* histmap_subl_el_mva_sf;
        RooUtil::HistMap* histmap_emu_mu_recoid_sf;
        RooUtil::HistMap* histmap_emu_el_recoid_sf;
        RooUtil::HistMap* histmap_emu_el_mva_sf;
        RooUtil::HistMap* histmap_lead_mu_recoid_3l_sf;
        RooUtil::HistMap* histmap_subl_mu_recoid_3l_sf;
        RooUtil::HistMap* histmap_lead_el_recoid_3l_sf;
        RooUtil::HistMap* histmap_subl_el_recoid_3l_sf;
        RooUtil::HistMap* histmap_lead_el_mva_3l_sf;
        RooUtil::HistMap* histmap_subl_el_mva_3l_sf;
        RooUtil::HistMap* histmap_tert_mu_recoid_3l_sf;
        RooUtil::HistMap* histmap_tert_el_recoid_3l_sf;
        RooUtil::HistMap* histmap_tert_el_mva_3l_sf;
        RooUtil::HistMap* histmap_lead_mu_isoip_sf;
        RooUtil::HistMap* histmap_subl_mu_isoip_sf;
        RooUtil::HistMap* histmap_lead_el_isoip_sf;
        RooUtil::HistMap* histmap_subl_el_isoip_sf;
        RooUtil::HistMap* histmap_emu_mu_isoip_sf;
        RooUtil::HistMap* histmap_emu_el_isoip_sf;
        RooUtil::HistMap* histmap_lead_mu_isoip_3l_sf;
        RooUtil::HistMap* histmap_subl_mu_isoip_3l_sf;
        RooUtil::HistMap* histmap_lead_el_isoip_3l_sf;
        RooUtil::HistMap* histmap_subl_el_isoip_3l_sf;
        RooUtil::HistMap* histmap_tert_mu_isoip_3l_sf;
        RooUtil::HistMap* histmap_tert_el_isoip_3l_sf;

        LeptonScaleFactors()
        {
            histmap_lead_mu_recoid_sf     = new RooUtil::HistMap("scalefactors/RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta");
            histmap_subl_mu_recoid_sf     = new RooUtil::HistMap("scalefactors/RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta");
            histmap_lead_el_recoid_sf     = new RooUtil::HistMap("scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap_subl_el_recoid_sf     = new RooUtil::HistMap("scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap_lead_el_mva_sf        = new RooUtil::HistMap("scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp80noiso.root:EGamma_SF2D");
            histmap_subl_el_mva_sf        = new RooUtil::HistMap("scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp80noiso.root:EGamma_SF2D");
            histmap_emu_mu_recoid_sf      = new RooUtil::HistMap("scalefactors/RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta");
            histmap_emu_el_recoid_sf      = new RooUtil::HistMap("scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap_emu_el_mva_sf         = new RooUtil::HistMap("scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp80noiso.root:EGamma_SF2D");
            histmap_lead_mu_recoid_3l_sf  = new RooUtil::HistMap("scalefactors/RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta");
            histmap_subl_mu_recoid_3l_sf  = new RooUtil::HistMap("scalefactors/RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta");
            histmap_lead_el_recoid_3l_sf  = new RooUtil::HistMap("scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap_subl_el_recoid_3l_sf  = new RooUtil::HistMap("scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap_lead_el_mva_3l_sf     = new RooUtil::HistMap("scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp90noiso.root:EGamma_SF2D");
            histmap_subl_el_mva_3l_sf     = new RooUtil::HistMap("scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp90noiso.root:EGamma_SF2D");
            histmap_tert_mu_recoid_3l_sf  = new RooUtil::HistMap("scalefactors/RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta");
            histmap_tert_el_recoid_3l_sf  = new RooUtil::HistMap("scalefactors/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D");
            histmap_tert_el_mva_3l_sf     = new RooUtil::HistMap("scalefactors/gammaEffi.txt_EGM2D_runBCDEF_passingMVA94Xwp90noiso.root:EGamma_SF2D");
            histmap_lead_mu_isoip_sf      = new RooUtil::HistMap("scalefactors/isoipsf/MuonID_2017www/muon/MuMediumPOG_MuTightVVV/sf.root:h_sf_pt_vs_eta");
            histmap_subl_mu_isoip_sf      = new RooUtil::HistMap("scalefactors/isoipsf/MuonID_2017www/muon/MuMediumPOG_MuTightVVV/sf.root:h_sf_pt_vs_eta");
            histmap_lead_el_isoip_sf      = new RooUtil::HistMap("scalefactors/isoipsf/ElectronID_2017www/electron/EGammaMVA80POG2017_EGammaTightVVV/sf.root:h_sf_pt_vs_eta");
            histmap_subl_el_isoip_sf      = new RooUtil::HistMap("scalefactors/isoipsf/ElectronID_2017www/electron/EGammaMVA80POG2017_EGammaTightVVV/sf.root:h_sf_pt_vs_eta");
            histmap_emu_mu_isoip_sf       = new RooUtil::HistMap("scalefactors/isoipsf/MuonID_2017www/muon/MuMediumPOG_MuTightVVV/sf.root:h_sf_pt_vs_eta");
            histmap_emu_el_isoip_sf       = new RooUtil::HistMap("scalefactors/isoipsf/ElectronID_2017www/electron/EGammaMVA80POG2017_EGammaTightVVV/sf.root:h_sf_pt_vs_eta");
            histmap_lead_mu_isoip_3l_sf   = new RooUtil::HistMap("scalefactors/isoipsf/MuonID_2017www/muon/MuMediumPOG_MuTightVVV3l/sf.root:h_sf_pt_vs_eta");
            histmap_subl_mu_isoip_3l_sf   = new RooUtil::HistMap("scalefactors/isoipsf/MuonID_2017www/muon/MuMediumPOG_MuTightVVV3l/sf.root:h_sf_pt_vs_eta");
            histmap_lead_el_isoip_3l_sf   = new RooUtil::HistMap("scalefactors/isoipsf/ElectronID_2017www/electron/EGammaMVA90POG2017_EGammaTightVVV3l/sf.root:h_sf_pt_vs_eta");
            histmap_subl_el_isoip_3l_sf   = new RooUtil::HistMap("scalefactors/isoipsf/ElectronID_2017www/electron/EGammaMVA90POG2017_EGammaTightVVV3l/sf.root:h_sf_pt_vs_eta");
            histmap_tert_mu_isoip_3l_sf   = new RooUtil::HistMap("scalefactors/isoipsf/MuonID_2017www/muon/MuMediumPOG_MuTightVVV3l/sf.root:h_sf_pt_vs_eta");
            histmap_tert_el_isoip_3l_sf   = new RooUtil::HistMap("scalefactors/isoipsf/ElectronID_2017www/electron/EGammaMVA90POG2017_EGammaTightVVV3l/sf.root:h_sf_pt_vs_eta");
        }

        ~LeptonScaleFactors()
        {
            delete histmap_lead_mu_recoid_sf;
            delete histmap_subl_mu_recoid_sf;
            delete histmap_lead_el_recoid_sf;
            delete histmap_subl_el_recoid_sf;
            delete histmap_lead_el_mva_sf;
            delete histmap_subl_el_mva_sf;
            delete histmap_emu_mu_recoid_sf;
            delete histmap_emu_el_recoid_sf;
            delete histmap_emu_el_mva_sf;
            delete histmap_lead_mu_recoid_3l_sf;
            delete histmap_subl_mu_recoid_3l_sf;
            delete histmap_lead_el_recoid_3l_sf;
            delete histmap_subl_el_recoid_3l_sf;
            delete histmap_lead_el_mva_3l_sf;
            delete histmap_subl_el_mva_3l_sf;
            delete histmap_tert_mu_recoid_3l_sf;
            delete histmap_tert_el_recoid_3l_sf;
            delete histmap_tert_el_mva_3l_sf;
            delete histmap_lead_mu_isoip_sf;
            delete histmap_subl_mu_isoip_sf;
            delete histmap_lead_el_isoip_sf;
            delete histmap_subl_el_isoip_sf;
            delete histmap_emu_mu_isoip_sf;
            delete histmap_emu_el_isoip_sf;
            delete histmap_lead_mu_isoip_3l_sf;
            delete histmap_subl_mu_isoip_3l_sf;
            delete histmap_lead_el_isoip_3l_sf;
            delete histmap_subl_el_isoip_3l_sf;
            delete histmap_tert_mu_isoip_3l_sf;
            delete histmap_tert_el_isoip_3l_sf;
        }

        //std::tuple<float, float, float, float> getScaleFactors(bool is2017, bool doFakeEstimation, bool isData, int variation=0)
        float getScaleFactors(bool is2017, bool doFakeEstimation, bool isData, int variation=0)
        {
            if (isData)
            {
                return 1;
            }
            else if (is2017)
            {
                const double b500 = 499.9;
                const double b120 = 119.9;
                float lead_mu_recoid_sf    = variation > 0 ? histmap_lead_mu_recoid_sf    -> eval_up(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : variation < 0 ? histmap_lead_mu_recoid_sf    -> eval_down(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : histmap_lead_mu_recoid_sf    -> eval(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     );
                float subl_mu_recoid_sf    = variation > 0 ? histmap_subl_mu_recoid_sf    -> eval_up(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : variation < 0 ? histmap_subl_mu_recoid_sf    -> eval_down(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : histmap_subl_mu_recoid_sf    -> eval(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     );
                float lead_el_recoid_sf    = variation > 0 ? histmap_lead_el_recoid_sf    -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variation < 0 ? histmap_lead_el_recoid_sf    -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap_lead_el_recoid_sf    -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_recoid_sf    = variation > 0 ? histmap_subl_el_recoid_sf    -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variation < 0 ? histmap_subl_el_recoid_sf    -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap_subl_el_recoid_sf    -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float lead_el_mva_sf       = variation > 0 ? histmap_lead_el_mva_sf       -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variation < 0 ? histmap_lead_el_mva_sf       -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap_lead_el_mva_sf       -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_mva_sf       = variation > 0 ? histmap_subl_el_mva_sf       -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variation < 0 ? histmap_subl_el_mva_sf       -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap_subl_el_mva_sf       -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float emu_mu_recoid_sf     = variation > 0 ? histmap_emu_mu_recoid_sf     -> eval_up(min((double)www.mu_pt(),b120)       ,abs((double)www.mu_eta())         ) : variation < 0 ? histmap_emu_mu_recoid_sf     -> eval_down(min((double)www.mu_pt(),b120)       ,abs((double)www.mu_eta())         ) : histmap_emu_mu_recoid_sf     -> eval(min((double)www.mu_pt(),b120)       ,abs((double)www.mu_eta())         );
                float emu_el_recoid_sf     = variation > 0 ? histmap_emu_el_recoid_sf     -> eval_up(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     ) : variation < 0 ? histmap_emu_el_recoid_sf     -> eval_down(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     ) : histmap_emu_el_recoid_sf     -> eval(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     );
                float emu_el_mva_sf        = variation > 0 ? histmap_emu_el_mva_sf        -> eval_up(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     ) : variation < 0 ? histmap_emu_el_mva_sf        -> eval_down(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     ) : histmap_emu_el_mva_sf        -> eval(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     );
                float lead_mu_recoid_3l_sf = variation > 0 ? histmap_lead_mu_recoid_3l_sf -> eval_up(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : variation < 0 ? histmap_lead_mu_recoid_3l_sf -> eval_down(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     ) : histmap_lead_mu_recoid_3l_sf -> eval(min((double)www.lep_pt()[0],b120)   ,abs((double)www.lep_eta()[0])     );
                float subl_mu_recoid_3l_sf = variation > 0 ? histmap_subl_mu_recoid_3l_sf -> eval_up(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : variation < 0 ? histmap_subl_mu_recoid_3l_sf -> eval_down(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     ) : histmap_subl_mu_recoid_3l_sf -> eval(min((double)www.lep_pt()[1],b120)   ,abs((double)www.lep_eta()[1])     );
                float lead_el_recoid_3l_sf = variation > 0 ? histmap_lead_el_recoid_3l_sf -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variation < 0 ? histmap_lead_el_recoid_3l_sf -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap_lead_el_recoid_3l_sf -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_recoid_3l_sf = variation > 0 ? histmap_subl_el_recoid_3l_sf -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variation < 0 ? histmap_subl_el_recoid_3l_sf -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap_subl_el_recoid_3l_sf -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float lead_el_mva_3l_sf    = variation > 0 ? histmap_lead_el_mva_3l_sf    -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variation < 0 ? histmap_lead_el_mva_3l_sf    -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap_lead_el_mva_3l_sf    -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_mva_3l_sf    = variation > 0 ? histmap_subl_el_mva_3l_sf    -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variation < 0 ? histmap_subl_el_mva_3l_sf    -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap_subl_el_mva_3l_sf    -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_mu_recoid_3l_sf = variation > 0 ? histmap_tert_mu_recoid_3l_sf -> eval_up(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     ) : variation < 0 ? histmap_tert_mu_recoid_3l_sf -> eval_down(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     ) : histmap_tert_mu_recoid_3l_sf -> eval(min((double)www.lep_pt()[2],b120)   ,abs((double)www.lep_eta()[2])     );
                float tert_el_recoid_3l_sf = variation > 0 ? histmap_tert_el_recoid_3l_sf -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variation < 0 ? histmap_tert_el_recoid_3l_sf -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap_tert_el_recoid_3l_sf -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float tert_el_mva_3l_sf    = variation > 0 ? histmap_tert_el_mva_3l_sf    -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variation < 0 ? histmap_tert_el_mva_3l_sf    -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap_tert_el_mva_3l_sf    -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );
                float lead_mu_isoip_sf     = variation > 0 ? histmap_lead_mu_isoip_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variation < 0 ? histmap_lead_mu_isoip_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap_lead_mu_isoip_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_isoip_sf     = variation > 0 ? histmap_subl_mu_isoip_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variation < 0 ? histmap_subl_mu_isoip_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap_subl_mu_isoip_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float lead_el_isoip_sf     = variation > 0 ? histmap_lead_el_isoip_sf     -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variation < 0 ? histmap_lead_el_isoip_sf     -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap_lead_el_isoip_sf     -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_isoip_sf     = variation > 0 ? histmap_subl_el_isoip_sf     -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variation < 0 ? histmap_subl_el_isoip_sf     -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap_subl_el_isoip_sf     -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float emu_mu_isoip_sf      = variation > 0 ? histmap_emu_mu_isoip_sf      -> eval_up(abs((double)www.mu_eta())           ,min((double)www.mu_pt(),199.99)   ) : variation < 0 ? histmap_emu_mu_isoip_sf      -> eval_down(abs((double)www.mu_eta())           ,min((double)www.mu_pt(),199.99)   ) : histmap_emu_mu_isoip_sf      -> eval(abs((double)www.mu_eta())           ,min((double)www.mu_pt(),199.99)   );
                float emu_el_isoip_sf      = variation > 0 ? histmap_emu_el_isoip_sf      -> eval_up(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     ) : variation < 0 ? histmap_emu_el_isoip_sf      -> eval_down(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     ) : histmap_emu_el_isoip_sf      -> eval(abs((double)www.el_eta())           ,min((double)www.el_pt(),b500)     );
                float lead_mu_isoip_3l_sf  = variation > 0 ? histmap_lead_mu_isoip_3l_sf  -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : variation < 0 ? histmap_lead_mu_isoip_3l_sf  -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) ) : histmap_lead_mu_isoip_3l_sf  -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b120) );
                float subl_mu_isoip_3l_sf  = variation > 0 ? histmap_subl_mu_isoip_3l_sf  -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : variation < 0 ? histmap_subl_mu_isoip_3l_sf  -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) ) : histmap_subl_mu_isoip_3l_sf  -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b120) );
                float lead_el_isoip_3l_sf  = variation > 0 ? histmap_lead_el_isoip_3l_sf  -> eval_up(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : variation < 0 ? histmap_lead_el_isoip_3l_sf  -> eval_down(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) ) : histmap_lead_el_isoip_3l_sf  -> eval(abs((double)www.lep_eta()[0])       ,min((double)www.lep_pt()[0],b500) );
                float subl_el_isoip_3l_sf  = variation > 0 ? histmap_subl_el_isoip_3l_sf  -> eval_up(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : variation < 0 ? histmap_subl_el_isoip_3l_sf  -> eval_down(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) ) : histmap_subl_el_isoip_3l_sf  -> eval(abs((double)www.lep_eta()[1])       ,min((double)www.lep_pt()[1],b500) );
                float tert_mu_isoip_3l_sf  = variation > 0 ? histmap_tert_mu_isoip_3l_sf  -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : variation < 0 ? histmap_tert_mu_isoip_3l_sf  -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) ) : histmap_tert_mu_isoip_3l_sf  -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b120) );
                float tert_el_isoip_3l_sf  = variation > 0 ? histmap_tert_el_isoip_3l_sf  -> eval_up(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : variation < 0 ? histmap_tert_el_isoip_3l_sf  -> eval_down(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) ) : histmap_tert_el_isoip_3l_sf  -> eval(abs((double)www.lep_eta()[2])       ,min((double)www.lep_pt()[2],b500) );

                // Scale factors
                float ee_sf = lead_el_recoid_sf * lead_el_mva_sf * lead_el_isoip_sf * subl_el_recoid_sf * subl_el_mva_sf * subl_el_isoip_sf;
                float em_sf = emu_mu_recoid_sf * emu_mu_isoip_sf * emu_el_recoid_sf * emu_el_mva_sf * emu_el_isoip_sf;
                float mm_sf = lead_mu_recoid_sf * lead_mu_isoip_sf * subl_mu_recoid_sf * subl_mu_isoip_sf;
                float lead_el = lead_el_recoid_3l_sf * lead_el_mva_3l_sf * lead_el_isoip_3l_sf;
                float subl_el = subl_el_recoid_3l_sf * subl_el_mva_3l_sf * subl_el_isoip_3l_sf;
                float tert_el = tert_el_recoid_3l_sf * tert_el_mva_3l_sf * tert_el_isoip_3l_sf;
                float lead_mu = lead_mu_recoid_3l_sf * lead_mu_isoip_3l_sf;
                float subl_mu = subl_mu_recoid_3l_sf * subl_mu_isoip_3l_sf;
                float tert_mu = tert_mu_recoid_3l_sf * tert_mu_isoip_3l_sf;
                float threelep_sf = ((abs(www.lep_pdgId()[0])==11)*(lead_el)+(abs(www.lep_pdgId()[0])!=11)*(lead_mu))
                    *((abs(www.lep_pdgId()[1])==11)*(subl_el)+(abs(www.lep_pdgId()[1])!=11)*(subl_mu))
                    *((abs(www.lep_pdgId()[2])==11)*(tert_el)+(abs(www.lep_pdgId()[2])!=11)*(tert_mu));

                ee_sf       = doFakeEstimation ? 1 : ee_sf;
                em_sf       = doFakeEstimation ? 1 : em_sf;
                mm_sf       = doFakeEstimation ? 1 : mm_sf;
                threelep_sf = doFakeEstimation ? 1 : threelep_sf;

                if (www.nVlep() == 2)
                {
                    if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 121)
                    {
                        return ee_sf;
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 143)
                    {
                        return em_sf;
                    }
                    else if (abs(www.lep_pdgId()[0]) * abs(www.lep_pdgId()[1]) == 169)
                    {
                        return mm_sf;
                    }
                    else
                    {
                        std::cout << "Error: should not be here " << __FUNCTION__ << std::endl;
                        return 1;
                    }
                }
                else if (www.nVlep() == 3)
                {
                    return threelep_sf;
                }
                else
                {
                    return 1;
                }

            }
            else
            {
                // Set the lepton scale factors based on
                return www.lepsf();
            }
        }
};

//_______________________________________________________________________________________________________
class FakeRates
{
    public:
        RooUtil::HistMap* histmap_fr_ss_el;
        RooUtil::HistMap* histmap_fr_ss_mu;
        RooUtil::HistMap* histmap_fr_3l_el;
        RooUtil::HistMap* histmap_fr_3l_mu;
        RooUtil::HistMap* histmap_fr_ss_el_closure;
        RooUtil::HistMap* histmap_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_fr_3l_el_closure;
        RooUtil::HistMap* histmap_fr_3l_mu_closure;

        RooUtil::HistMap* histmap_2016_fr_ss_el;
        RooUtil::HistMap* histmap_2016_fr_ss_mu;
        RooUtil::HistMap* histmap_2016_fr_3l_el;
        RooUtil::HistMap* histmap_2016_fr_3l_mu;
        RooUtil::HistMap* histmap_2016_fr_ss_el_closure;
        RooUtil::HistMap* histmap_2016_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_2016_fr_3l_el_closure;
        RooUtil::HistMap* histmap_2016_fr_3l_mu_closure;

        RooUtil::HistMap* histmap_2017_fr_ss_el;
        RooUtil::HistMap* histmap_2017_fr_ss_mu;
        RooUtil::HistMap* histmap_2017_fr_3l_el;
        RooUtil::HistMap* histmap_2017_fr_3l_mu;
        RooUtil::HistMap* histmap_2017_fr_ss_el_closure;
        RooUtil::HistMap* histmap_2017_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_2017_fr_3l_el_closure;
        RooUtil::HistMap* histmap_2017_fr_3l_mu_closure;

        RooUtil::HistMap* histmap_2018_fr_ss_el;
        RooUtil::HistMap* histmap_2018_fr_ss_mu;
        RooUtil::HistMap* histmap_2018_fr_3l_el;
        RooUtil::HistMap* histmap_2018_fr_3l_mu;
        RooUtil::HistMap* histmap_2018_fr_ss_el_closure;
        RooUtil::HistMap* histmap_2018_fr_ss_mu_closure;
        RooUtil::HistMap* histmap_2018_fr_3l_el_closure;
        RooUtil::HistMap* histmap_2018_fr_3l_mu_closure;

        const float muiso_ss_thresh = 0.03;
        const float eliso_ss_thresh = 0.03;
        const float muiso_3l_thresh = 0.07;
        const float eliso_3l_thresh = 0.05;

        FakeRates()
        {
            histmap_fr_ss_el = 0;
            histmap_fr_ss_mu = 0;
            histmap_fr_3l_el = 0;
            histmap_fr_3l_mu = 0;
            histmap_fr_ss_el_closure = 0;
            histmap_fr_ss_mu_closure = 0;
            histmap_fr_3l_el_closure = 0;
            histmap_fr_3l_mu_closure = 0;

            histmap_2016_fr_ss_el = 0;
            histmap_2016_fr_ss_mu = 0;
            histmap_2016_fr_3l_el = 0;
            histmap_2016_fr_3l_mu = 0;
            histmap_2016_fr_ss_el_closure = 0;
            histmap_2016_fr_ss_mu_closure = 0;
            histmap_2016_fr_3l_el_closure = 0;
            histmap_2016_fr_3l_mu_closure = 0;

            histmap_2017_fr_ss_el = 0;
            histmap_2017_fr_ss_mu = 0;
            histmap_2017_fr_3l_el = 0;
            histmap_2017_fr_3l_mu = 0;
            histmap_2017_fr_ss_el_closure = 0;
            histmap_2017_fr_ss_mu_closure = 0;
            histmap_2017_fr_3l_el_closure = 0;
            histmap_2017_fr_3l_mu_closure = 0;

            histmap_2018_fr_ss_el = 0;
            histmap_2018_fr_ss_mu = 0;
            histmap_2018_fr_3l_el = 0;
            histmap_2018_fr_3l_mu = 0;
            histmap_2018_fr_ss_el_closure = 0;
            histmap_2018_fr_ss_mu_closure = 0;
            histmap_2018_fr_3l_el_closure = 0;
            histmap_2018_fr_3l_mu_closure = 0;
        }

        ~FakeRates()
        {
            delete histmap_fr_ss_el;
            delete histmap_fr_ss_mu;
            delete histmap_fr_3l_el;
            delete histmap_fr_3l_mu;
            delete histmap_fr_ss_el_closure;
            delete histmap_fr_ss_mu_closure;
            delete histmap_fr_3l_el_closure;
            delete histmap_fr_3l_mu_closure;
        }

        void load2016()
        {
            load2017();
            // if (not histmap_2016_fr_ss_el        ) histmap_2016_fr_ss_el         = new RooUtil::HistMap("scalefactors/fakerate_ss.root:El_ptcorretarolledcoarse_data_fakerate");
            // if (not histmap_2016_fr_ss_mu        ) histmap_2016_fr_ss_mu         = new RooUtil::HistMap("scalefactors/fakerate_ss.root:Mu_ptcorretarolledcoarse_data_fakerate");
            // if (not histmap_2016_fr_3l_el        ) histmap_2016_fr_3l_el         = new RooUtil::HistMap("scalefactors/fakerate_3l.root:El_ptcorretarolledcoarse_data_fakerate");
            // if (not histmap_2016_fr_3l_mu        ) histmap_2016_fr_3l_mu         = new RooUtil::HistMap("scalefactors/fakerate_3l.root:Mu_ptcorretarolledcoarse_data_fakerate");
            // if (not histmap_2016_fr_ss_el_closure) histmap_2016_fr_ss_el_closure = new RooUtil::HistMap("scalefactors/fakerate_ss.root:El_ptcorretarolledcoarse_data_fakerateclosure");
            // if (not histmap_2016_fr_ss_mu_closure) histmap_2016_fr_ss_mu_closure = new RooUtil::HistMap("scalefactors/fakerate_ss.root:Mu_ptcorretarolledcoarse_data_fakerateclosure");
            // if (not histmap_2016_fr_3l_el_closure) histmap_2016_fr_3l_el_closure = new RooUtil::HistMap("scalefactors/fakerate_3l.root:El_ptcorretarolledcoarse_data_fakerateclosure");
            // if (not histmap_2016_fr_3l_mu_closure) histmap_2016_fr_3l_mu_closure = new RooUtil::HistMap("scalefactors/fakerate_3l.root:Mu_ptcorretarolledcoarse_data_fakerateclosure");
            // histmap_fr_ss_el         = histmap_2016_fr_ss_el;
            // histmap_fr_ss_mu         = histmap_2016_fr_ss_mu;
            // histmap_fr_3l_el         = histmap_2016_fr_3l_el;
            // histmap_fr_3l_mu         = histmap_2016_fr_3l_mu;
            // histmap_fr_ss_el_closure = histmap_2016_fr_ss_el_closure;
            // histmap_fr_ss_mu_closure = histmap_2016_fr_ss_mu_closure;
            // histmap_fr_3l_el_closure = histmap_2016_fr_3l_el_closure;
            // histmap_fr_3l_mu_closure = histmap_2016_fr_3l_mu_closure;
        }

        void load2017()
        {
            if (not histmap_2017_fr_ss_el        ) histmap_2017_fr_ss_el         = new RooUtil::HistMap("scalefactors/fakerate_2017_ss_mar2019.root:El_ptcorretarolledcoarse_data_fakerate");
            if (not histmap_2017_fr_ss_mu        ) histmap_2017_fr_ss_mu         = new RooUtil::HistMap("scalefactors/fakerate_2017_ss_mar2019.root:Mu_ptcorretarolledcoarse_data_fakerate");
            if (not histmap_2017_fr_3l_el        ) histmap_2017_fr_3l_el         = new RooUtil::HistMap("scalefactors/fakerate_2017_3l_mar2019.root:El_ptcorretarolledcoarse_data_fakerate");
            if (not histmap_2017_fr_3l_mu        ) histmap_2017_fr_3l_mu         = new RooUtil::HistMap("scalefactors/fakerate_2017_3l_mar2019.root:Mu_ptcorretarolledcoarse_data_fakerate");
            if (not histmap_2017_fr_ss_el_closure) histmap_2017_fr_ss_el_closure = new RooUtil::HistMap("scalefactors/fakerate_2017_ss_mar2019.root:El_ptcorretarolledcoarse_data_fakerateclosure");
            if (not histmap_2017_fr_ss_mu_closure) histmap_2017_fr_ss_mu_closure = new RooUtil::HistMap("scalefactors/fakerate_2017_ss_mar2019.root:Mu_ptcorretarolledcoarse_data_fakerateclosure");
            if (not histmap_2017_fr_3l_el_closure) histmap_2017_fr_3l_el_closure = new RooUtil::HistMap("scalefactors/fakerate_2017_3l_mar2019.root:El_ptcorretarolledcoarse_data_fakerateclosure");
            if (not histmap_2017_fr_3l_mu_closure) histmap_2017_fr_3l_mu_closure = new RooUtil::HistMap("scalefactors/fakerate_2017_3l_mar2019.root:Mu_ptcorretarolledcoarse_data_fakerateclosure");
            histmap_fr_ss_el         = histmap_2017_fr_ss_el;
            histmap_fr_ss_mu         = histmap_2017_fr_ss_mu;
            histmap_fr_3l_el         = histmap_2017_fr_3l_el;
            histmap_fr_3l_mu         = histmap_2017_fr_3l_mu;
            histmap_fr_ss_el_closure = histmap_2017_fr_ss_el_closure;
            histmap_fr_ss_mu_closure = histmap_2017_fr_ss_mu_closure;
            histmap_fr_3l_el_closure = histmap_2017_fr_3l_el_closure;
            histmap_fr_3l_mu_closure = histmap_2017_fr_3l_mu_closure;
        }

        void load2018()
        {
            if (not histmap_2018_fr_ss_el        ) histmap_2018_fr_ss_el         = new RooUtil::HistMap("scalefactors/fakerate_2018_ss.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_ss_mu        ) histmap_2018_fr_ss_mu         = new RooUtil::HistMap("scalefactors/fakerate_2018_ss.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_3l_el        ) histmap_2018_fr_3l_el         = new RooUtil::HistMap("scalefactors/fakerate_2018_3l.root:El_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_3l_mu        ) histmap_2018_fr_3l_mu         = new RooUtil::HistMap("scalefactors/fakerate_2018_3l.root:Mu_ptcorretarolled_data_fakerate");
            if (not histmap_2018_fr_ss_el_closure) histmap_2018_fr_ss_el_closure = new RooUtil::HistMap("scalefactors/fakerate_2018_ss.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_ss_mu_closure) histmap_2018_fr_ss_mu_closure = new RooUtil::HistMap("scalefactors/fakerate_2018_ss.root:Mu_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_3l_el_closure) histmap_2018_fr_3l_el_closure = new RooUtil::HistMap("scalefactors/fakerate_2018_3l.root:El_ptcorretarolled_data_fakerateclosure");
            if (not histmap_2018_fr_3l_mu_closure) histmap_2018_fr_3l_mu_closure = new RooUtil::HistMap("scalefactors/fakerate_2018_3l.root:Mu_ptcorretarolled_data_fakerateclosure");
            histmap_fr_ss_el         = histmap_2018_fr_ss_el;
            histmap_fr_ss_mu         = histmap_2018_fr_ss_mu;
            histmap_fr_3l_el         = histmap_2018_fr_3l_el;
            histmap_fr_3l_mu         = histmap_2018_fr_3l_mu;
            histmap_fr_ss_el_closure = histmap_2018_fr_ss_el_closure;
            histmap_fr_ss_mu_closure = histmap_2018_fr_ss_mu_closure;
            histmap_fr_3l_el_closure = histmap_2018_fr_3l_el_closure;
            histmap_fr_3l_mu_closure = histmap_2018_fr_3l_mu_closure;
        }

        int getFakeLepIndex()
        {
            // Check the number of leptons
            if ((www.nLlep() - 1) != www.nTlep())
                return -1;

            // Retrieve the flags for the lepton ID
            const vector<int>& istight = www.nVlep() == 2 ? www.lep_pass_VVV_cutbased_tight() : www.lep_pass_VVV_cutbased_3l_tight();
            const vector<int>& isloose = www.nVlep() == 2 ? www.lep_pass_VVV_cutbased_fo() : www.lep_pass_VVV_cutbased_3l_fo();

            // Figure out the index by whichever one is the loose but not tight
            int index = -1;
            for (int ilep = 0; ilep < www.nLlep(); ++ilep)
            {
                if (!istight[ilep] && isloose[ilep])
                    index = ilep;
            }

            return index;
        }

        float getPtCorr()
        {
            int index = getFakeLepIndex();

            if (index < 0)
                return 0;

            // Create an int to indicate which lepton id fakerate to use
            int lepversion = 0;
            if (www.nLlep() >= 3)
                lepversion = 1;

            float ptcorr = -1;
            if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 0)
            {
                ptcorr = www.lep_pt()[index] * (1 + max((double) 0. , (double) www.lep_relIso03EAv2Lep()[index]-eliso_ss_thresh));
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 0)
            {
                ptcorr = www.lep_pt()[index] * (1 + max((double) 0. , (double) www.lep_relIso03EAv2Lep()[index]-muiso_ss_thresh));
//                std::cout <<  " ptcorr: " << ptcorr <<  " fabs(www.lep_eta()[index]): " << fabs(www.lep_eta()[index]) <<  " fr: " << fr <<  " muiso_ss_thresh: " << muiso_ss_thresh <<  std::endl;
            }
            else if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 1)
            {
                ptcorr = www.lep_pt()[index] * (1 + max((double) 0. , (double) www.lep_relIso03EAv2Lep()[index]-eliso_3l_thresh));
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 1)
            {
                ptcorr = www.lep_pt()[index] * (1 + max((double) 0. , (double) www.lep_relIso03EAv2Lep()[index]-muiso_3l_thresh));
            }
            return ptcorr;
        }

        float getFakeFactor(int err=0, int lepflav=0, bool doclosureerr=false)
        {
            int index = getFakeLepIndex();
            float ptcorr = getPtCorr();
            float fr = 0;

            // Create an int to indicate which lepton id fakerate to use
            int lepversion = 0;
            if (www.nLlep() >= 3)
                lepversion = 1;

            int lepid = abs(www.lep_pdgId()[index]);
            bool lepidmatchforerror = abs(lepid) == abs(lepflav);

            // The closure error needs a bit of special treatment to properly propagate the error
            // the percentage error used to save the fakerates are in percentage for the fakerate
            // But the properway to do it is to use the percentage error to the fake factors
            float nom_fr = 0;
            float closure_err_pct = 0;
            float closure_ff = 0;

            if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 0)
            {
                if (doclosureerr)
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_ss_el_closure->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_ss_el_closure->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_ss_el_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    nom_fr = histmap_fr_ss_el_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_ss_el->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_ss_el->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_ss_el->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 0)
            {
                if (doclosureerr)
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_ss_mu_closure->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_ss_mu_closure->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_ss_mu_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    nom_fr = histmap_fr_ss_mu_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_ss_mu->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_ss_mu->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_ss_mu->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 11 and lepversion == 1)
            {
                if (doclosureerr)
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el_closure->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el_closure->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_el_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    nom_fr = histmap_fr_3l_el_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_el->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_el->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else if (abs(www.lep_pdgId()[index]) == 13 and lepversion == 1)
            {
                if (doclosureerr)
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu_closure->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu_closure->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_mu_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    nom_fr = histmap_fr_3l_mu_closure->eval(ptcorr, fabs(www.lep_eta()[index]));
                    closure_err_pct = fr / nom_fr;
                    closure_ff = (nom_fr / (1 - nom_fr)) * (closure_err_pct);
                    fr = (closure_ff / (1 + closure_ff));
                }
                else
                {
                    if (err == 1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu->eval_up(ptcorr, fabs(www.lep_eta()[index]));
                    else if (err ==-1 and lepidmatchforerror)
                        fr = histmap_fr_3l_mu->eval_down(ptcorr, fabs(www.lep_eta()[index]));
                    else
                        fr = histmap_fr_3l_mu->eval(ptcorr, fabs(www.lep_eta()[index]));
                }
            }
            else
            {
                return 0;
            }
            return fr / (1 - fr);
        }

};

//_______________________________________________________________________________________________________
class TheoryWeight
{
    public:
        RooUtil::HistMap* histmap_neventsinfile;
        float nominal_;
        float pdfup_;
        float pdfdn_;
        float alsup_;
        float alsdn_;
        float qsqup_;
        float qsqdn_;
        TheoryWeight() : histmap_neventsinfile(0), nominal_(1), pdfup_(1), pdfdn_(1), alsup_(1), alsdn_(1), qsqup_(1), qsqdn_(1) {}
        void setFile(TString fname)
        {
            histmap_neventsinfile = new RooUtil::HistMap(fname + ":h_neventsinfile");
            nominal_ = histmap_neventsinfile->hist->GetBinContent(1+1);
            pdfup_   = histmap_neventsinfile->hist->GetBinContent(1+10);
            pdfdn_   = histmap_neventsinfile->hist->GetBinContent(1+11);
            alsup_   = histmap_neventsinfile->hist->GetBinContent(1+13);
            alsdn_   = histmap_neventsinfile->hist->GetBinContent(1+12);
            qsqup_   = histmap_neventsinfile->hist->GetBinContent(1+5);
            qsqdn_   = histmap_neventsinfile->hist->GetBinContent(1+9);
        }
        float& nominal() { return nominal_; }
        float& pdfup()   { return pdfup_  ; }
        float& pdfdn()   { return pdfdn_  ; }
        float& alsup()   { return alsup_  ; }
        float& alsdn()   { return alsdn_  ; }
        float& qsqup()   { return qsqup_  ; }
        float& qsqdn()   { return qsqdn_  ; }
};

//_______________________________________________________________________________________________________
class PileupReweight
{
    public:
        RooUtil::HistMap* histmap_purwegt;
        RooUtil::HistMap* histmap_purwegt_up;
        RooUtil::HistMap* histmap_purwegt_dn;
        PileupReweight()
        {
            histmap_purwegt    = new RooUtil::HistMap("scalefactors/puw_2017.root:puw_central");
            histmap_purwegt_up = new RooUtil::HistMap("scalefactors/puw_2017.root:puw_up");
            histmap_purwegt_dn = new RooUtil::HistMap("scalefactors/puw_2017.root:puw_down");
        }
        float purewgt()
        {
            return histmap_purwegt->eval(www.nTrueInt());
        }
        float purewgt_up()
        {
            return histmap_purwegt_up->eval(www.nTrueInt());
        }
        float purewgt_dn()
        {
            return histmap_purwegt_dn->eval(www.nTrueInt());
        }
};

#ifndef __CINT__
// Scale factors tools
extern LeptonScaleFactors leptonScaleFactors;
extern FakeRates fakerates;
extern TheoryWeight theoryweight;
extern PileupReweight pileupreweight;
#endif

#endif
