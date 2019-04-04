#include "CMS4Utils.h"

CMS4Reader cms4reader;

void CMS4Reader::open()
{
    cms4_tree = RooUtil::FileUtil::createTChain("Events", www.CMS4path());
    std::cout <<  " cms4_tree->GetEntries(): " << cms4_tree->GetEntries() <<  std::endl;
    std::cout <<  " accessing www.CMS4index(): " << www.CMS4index() <<  std::endl;
    cms3.Init(cms4_tree);
    cms3.GetEntry(www.CMS4index());
    gconf.GetConfigsFromDatasetName(www.CMS4path());
    createAndInitMVA("../wwwbabymaker/CORE", true, false, 80); // for electrons
}

void CMS4Reader::printParticle(int i)
{
    int pdgId = cms3.genps_id()[i];
    int status = cms3.genps_status()[i];
    int motherId = cms3.genps_id_simplemother()[i];
    int grandmaId = cms3.genps_id_simplegrandma()[i];
    LorentzVector p4 = cms3.genps_p4()[i];
    printf("pdgId: %6d motherId: %6d grandmaId: %6d status: %4d p4.pt(): %8.3f p4.eta(): %8.3f p4.phi(): %8.3f p4.mass(): %8.3f p4.energy(): %8.3f\n",
            pdgId, motherId, grandmaId, status, p4.pt(), p4.eta(), p4.phi(), p4.mass(), p4.energy());
}

void CMS4Reader::printPartonsWithCondition(TString message, std::function<bool(int)> pass)
{
    std::cout << message << std::endl;
    for (unsigned int i = 0; i < genPart_idx.size(); ++i)
    {
        int idx = genPart_idx.at(i);
        if (pass)
        {
            if (pass(idx))
            {
                std::cout <<  " i: " << i << " ";
                printParticle(idx);
            }
        }
        else
        {
            std::cout <<  " i: " << i << " ";
            printParticle(idx);
        }
    }
}

void CMS4Reader::printLeptons()
{

    std::cout << "***************************************************" << std::endl;
    std::cout << "*           Printing Leptons from CMS4            *" << std::endl;
    std::cout << "***************************************************" << std::endl;

    std::cout <<  " cms3.genps_weight(): " << cms3.genps_weight() <<  std::endl;
    std::cout <<  " cms3.els_p4().size(): " << cms3.els_p4().size() <<  std::endl;
    std::cout <<  " cms3.mus_p4().size(): " << cms3.mus_p4().size() <<  std::endl;

    for (unsigned int elIdx = 0; elIdx < cms3.els_p4().size(); elIdx++)
    {

        pair<int, int> motherId_genIdx = lepMotherID_v2(Lep(cms3.els_charge()[elIdx] * (-11), elIdx)); //don't forget the sign
        if (motherId_genIdx.first != -3)
            continue;

        std::cout << "Electron Index: " << elIdx << std::endl;
        std::cout << " cms3.els_lost_pixelhits().at(elIdx)         : " << cms3.els_lost_pixelhits().at(elIdx)           << std::endl;
        std::cout << " cms3.els_p4().at(elIdx).pt()                : " << cms3.els_p4().at(elIdx).pt()                  << std::endl;
        std::cout << " cms3.els_p4().at(elIdx).eta()               : " << cms3.els_p4().at(elIdx).eta()                 << std::endl;
        std::cout << " cms3.els_p4().at(elIdx).phi()               : " << cms3.els_p4().at(elIdx).phi()                 << std::endl;
        std::cout << " cms3.els_etaSC().at(elIdx)                  : " << cms3.els_etaSC().at(elIdx)                    << std::endl;
        std::cout << " cms3.els_dxyPV().at(elIdx)                  : " << cms3.els_dxyPV().at(elIdx)                    << std::endl;
        std::cout << " cms3.els_dzPV().at(elIdx)                   : " << cms3.els_dzPV().at(elIdx)                     << std::endl;
        std::cout << " getMVAoutput(elIdx)                         : " << getMVAoutput(elIdx)                           << std::endl;
        std::cout << " getMVAoutput(elIdx,true)                    : " << getMVAoutput(elIdx,true)                      << std::endl;
        std::cout << " isMVAHZZNoIsofall17(elIdx,true)             : " << isMVAHZZNoIsofall17(elIdx,true)               << std::endl;
        std::cout << " els_VIDFall17V2NoIsoMvaValue().at(index)    : " << cms3.els_VIDFall17V2NoIsoMvaValue().at(elIdx) << std::endl;
        float notraw = cms3.els_VIDFall17V2NoIsoMvaValue().at(elIdx);
        if (notraw >  1.0-1.e-7) notraw =  1.0-1.e-7; // protect against inf, -inf due to FP rounding issues
        if (notraw < -1.0+1.e-7) notraw = -1.0+1.e-7;
        std::cout << " raw VIDFall17V2NoIsoMvaValue().at(index)    : " << -0.5*log((2.0/(notraw+1.))-1.0) << std::endl;
        std::cout << " eleRelIso03EA(elIdx,2,true)                 : " << eleRelIso03EA(elIdx,2,true)                   << std::endl;
        std::cout << " eleRelIso03EA(elIdx,2,false)                : " << eleRelIso03EA(elIdx,2,false)                  << std::endl;
        std::cout << " eleRelIso03EA(elIdx,4,true)                 : " << eleRelIso03EA(elIdx,4,true)                   << std::endl;
        std::cout << " eleRelIso03EA(elIdx,4,false)                : " << eleRelIso03EA(elIdx,4,false)                  << std::endl;
        std::cout << " cms3.els_ip3d()[elIdx]                      : " << cms3.els_ip3d()[elIdx]                        << std::endl;
        std::cout << " cms3.els_ip3derr()[elIdx]                   : " << cms3.els_ip3derr()[elIdx]                     << std::endl;
        std::cout << " threeChargeAgree(elIdx)                     : " << threeChargeAgree(elIdx)                       << std::endl;
        std::cout << " isMVAwp80NoIsofall17(elIdx,true)            : " << isMVAwp80NoIsofall17(elIdx,true)              << std::endl;
        std::cout << " isTriggerSafenoIso_v1(elIdx)                : " << isTriggerSafenoIso_v1(elIdx)                  << std::endl;
        std::cout << " cms3.els_conv_vtx_flag().at(elIdx)          : " << cms3.els_conv_vtx_flag().at(elIdx)            << std::endl;
        std::cout << " cms3.els_conv_vtx_prob().at(elIdx)          : " << cms3.els_conv_vtx_prob().at(elIdx)            << std::endl;
        std::cout << " cms3.els_exp_innerlayers().at(elIdx)        : " << cms3.els_exp_innerlayers().at(elIdx)          << std::endl;
        std::cout << " cms3.els_sigmaIEtaIEta_full5x5().at(elIdx)  : " << cms3.els_sigmaIEtaIEta_full5x5().at(elIdx)    << std::endl;
        std::cout << " cms3.els_dEtaIn().at(elIdx)                 : " << cms3.els_dEtaIn().at(elIdx)                   << std::endl;
        std::cout << " cms3.els_dPhiIn().at(elIdx)                 : " << cms3.els_dPhiIn().at(elIdx)                   << std::endl;
        std::cout << " cms3.els_scSeedEta().at(elIdx)              : " << cms3.els_scSeedEta().at(elIdx)                << std::endl;
        std::cout << " cms3.els_hOverE().at(elIdx)                 : " << cms3.els_hOverE().at(elIdx)                   << std::endl;
        std::cout << " cms3.els_ecalEnergy().at(elIdx)             : " << cms3.els_ecalEnergy().at(elIdx)               << std::endl;
        std::cout << " cms3.els_eOverPIn().at(elIdx)               : " << cms3.els_eOverPIn().at(elIdx)                 << std::endl;

        std::cout <<  " cms3.els_ckf_laywithmeas().at(elIdx): " << cms3.els_ckf_laywithmeas().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_sigmaIEtaIEta_full5x5().at(elIdx): " << cms3.els_sigmaIEtaIEta_full5x5().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_sigmaIPhiIPhi_full5x5().at(elIdx): " << cms3.els_sigmaIPhiIPhi_full5x5().at(elIdx) <<  std::endl;
        std::cout <<  " 1.0-cms3.els_e1x5_full5x5().at(elIdx)/cms3.els_e5x5_full5x5().at(elIdx): " << 1.0-cms3.els_e1x5_full5x5().at(elIdx)/cms3.els_e5x5_full5x5().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_r9_full5x5().at(elIdx): " << cms3.els_r9_full5x5().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_etaSCwidth().at(elIdx): " << cms3.els_etaSCwidth().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_phiSCwidth().at(elIdx): " << cms3.els_phiSCwidth().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_hOverE().at(elIdx): " << cms3.els_hOverE().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_hOverE().at(elIdx)*cms3.els_ecalEnergy().at(elIdx)/cms3.els_eSC().at(elIdx): " << cms3.els_hOverE().at(elIdx)*cms3.els_ecalEnergy().at(elIdx)/cms3.els_eSC().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_eSCPresh().at(elIdx)/cms3.els_eSCRaw().at(elIdx): " << cms3.els_eSCPresh().at(elIdx)/cms3.els_eSCRaw().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_ckf_chi2().at(elIdx)/cms3.els_ckf_ndof().at(elIdx): " << cms3.els_ckf_chi2().at(elIdx)/cms3.els_ckf_ndof().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_chi2().at(elIdx)/cms3.els_ndof().at(elIdx): " << cms3.els_chi2().at(elIdx)/cms3.els_ndof().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_fbrem().at(elIdx): " << cms3.els_fbrem().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_eOverPIn().at(elIdx): " << cms3.els_eOverPIn().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_eOverPOut().at(elIdx): " << cms3.els_eOverPOut().at(elIdx) <<  std::endl;
        std::cout <<  " ((cms3.els_ecalEnergy().at(elIdx)!=0&&cms3.els_p4In().at(elIdx).P()!=0)?1.0/cms3.els_ecalEnergy().at(elIdx)-1.0/cms3.els_p4In().at(elIdx).P():999999): " << ((cms3.els_ecalEnergy().at(elIdx)!=0&&cms3.els_p4In().at(elIdx).P()!=0)?1.0/cms3.els_ecalEnergy().at(elIdx)-1.0/cms3.els_p4In().at(elIdx).P():999999) <<  std::endl;
        std::cout <<  " fabs(cms3.els_dEtaIn().at(elIdx)): " << fabs(cms3.els_dEtaIn().at(elIdx)) <<  std::endl;
        std::cout <<  " fabs(cms3.els_dPhiIn().at(elIdx)): " << fabs(cms3.els_dPhiIn().at(elIdx)) <<  std::endl;
        std::cout <<  " fabs(cms3.els_dEtaOut().at(elIdx)): " << fabs(cms3.els_dEtaOut().at(elIdx)) <<  std::endl;
        std::cout <<  " cms3.els_p4().at(elIdx).pt(): " << cms3.els_p4().at(elIdx).pt() <<  std::endl;
        std::cout <<  " (fabs(cms3.els_etaSC().at(elIdx))<1.479?1:0): " << (fabs(cms3.els_etaSC().at(elIdx))<1.479?1:0) <<  std::endl;
        std::cout <<  " (fabs(cms3.els_etaSC().at(elIdx))>1.479?1:0): " << (fabs(cms3.els_etaSC().at(elIdx))>1.479?1:0) <<  std::endl;
        std::cout <<  " cms3.els_etaSC().at(elIdx): " << cms3.els_etaSC().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_nlayers().at(elIdx): " << cms3.els_nlayers().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_exp_innerlayers().at(elIdx): " << cms3.els_exp_innerlayers().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_conv_vtx_prob().at(elIdx): " << cms3.els_conv_vtx_prob().at(elIdx) <<  std::endl;

        std::cout <<  " cms3.els_category().at(elIdx): " << cms3.els_category().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_charge().at(elIdx): " << cms3.els_charge().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_ckf_charge().at(elIdx): " << cms3.els_ckf_charge().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_ckf_laywithmeas().at(elIdx): " << cms3.els_ckf_laywithmeas().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_exp_innerlayers().at(elIdx): " << cms3.els_exp_innerlayers().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_exp_outerlayers().at(elIdx): " << cms3.els_exp_outerlayers().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_lostHits().at(elIdx): " << cms3.els_lostHits().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_lost_pixelhits().at(elIdx): " << cms3.els_lost_pixelhits().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_nlayers().at(elIdx): " << cms3.els_nlayers().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_nlayers3D().at(elIdx): " << cms3.els_nlayers3D().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_nlayersLost().at(elIdx): " << cms3.els_nlayersLost().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_sccharge().at(elIdx): " << cms3.els_sccharge().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_trk_charge().at(elIdx): " << cms3.els_trk_charge().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_type().at(elIdx): " << cms3.els_type().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_validHits().at(elIdx): " << cms3.els_validHits().at(elIdx) <<  std::endl;
        std::cout <<  " cms3.els_valid_pixelhits().at(elIdx): " << cms3.els_valid_pixelhits().at(elIdx) <<  std::endl;

        // std::cout << " cms3.els_conv_vtx_flag().at(elIdx)                 : " << cms3.els_conv_vtx_flag().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_isGsfCtfScPixChargeConsistent().at(elIdx) : " << cms3.els_isGsfCtfScPixChargeConsistent().at(elIdx) << std::endl;
        // std::cout << " cms3.els_passingMvaPreselection().at(elIdx)        : " << cms3.els_passingMvaPreselection().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_passingPflowPreselection().at(elIdx)      : " << cms3.els_passingPflowPreselection().at(elIdx)      << std::endl;
        // std::cout << " cms3.els_VIDFall17NoIsoMvaValue().at(elIdx)        : " << cms3.els_VIDFall17NoIsoMvaValue().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_VIDFall17V2NoIsoMvaValue().at(elIdx)      : " << cms3.els_VIDFall17V2NoIsoMvaValue().at(elIdx)      << std::endl;
        // std::cout << " cms3.els_VIDNonTrigMvaValue().at(elIdx)            : " << cms3.els_VIDNonTrigMvaValue().at(elIdx)            << std::endl;
        // std::cout << " cms3.els_VIDSpring16GPMvaValue().at(elIdx)         : " << cms3.els_VIDSpring16GPMvaValue().at(elIdx)         << std::endl;
        // std::cout << " cms3.els_VIDSpring16HZZMvaValue().at(elIdx)        : " << cms3.els_VIDSpring16HZZMvaValue().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_VIDTrigMvaValue().at(elIdx)               : " << cms3.els_VIDTrigMvaValue().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_bs2d().at(elIdx)                          : " << cms3.els_bs2d().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_bs2derr().at(elIdx)                       : " << cms3.els_bs2derr().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_bs3d().at(elIdx)                          : " << cms3.els_bs3d().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_bs3derr().at(elIdx)                       : " << cms3.els_bs3derr().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_chi2().at(elIdx)                          : " << cms3.els_chi2().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_ckf_chi2().at(elIdx)                      : " << cms3.els_ckf_chi2().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_ckf_ndof().at(elIdx)                      : " << cms3.els_ckf_ndof().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_clusterMaxDR().at(elIdx)                  : " << cms3.els_clusterMaxDR().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_clusterMaxDRDEta().at(elIdx)              : " << cms3.els_clusterMaxDRDEta().at(elIdx)              << std::endl;
        // std::cout << " cms3.els_clusterMaxDRDPhi().at(elIdx)              : " << cms3.els_clusterMaxDRDPhi().at(elIdx)              << std::endl;
        // std::cout << " cms3.els_clusterMaxDRRawEnergy().at(elIdx)         : " << cms3.els_clusterMaxDRRawEnergy().at(elIdx)         << std::endl;
        // std::cout << " cms3.els_clustersMeanDEtaToSeed().at(elIdx)        : " << cms3.els_clustersMeanDEtaToSeed().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_clustersMeanDPhiToSeed().at(elIdx)        : " << cms3.els_clustersMeanDPhiToSeed().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_clustersMeanDRToSeed().at(elIdx)          : " << cms3.els_clustersMeanDRToSeed().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_clustersMeanRawEnergy().at(elIdx)         : " << cms3.els_clustersMeanRawEnergy().at(elIdx)         << std::endl;
        // std::cout << " cms3.els_clustersRMSRawEnergy().at(elIdx)          : " << cms3.els_clustersRMSRawEnergy().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_conv_vtx_prob().at(elIdx)                 : " << cms3.els_conv_vtx_prob().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_d0().at(elIdx)                            : " << cms3.els_d0().at(elIdx)                            << std::endl;
        // std::cout << " cms3.els_d0Err().at(elIdx)                         : " << cms3.els_d0Err().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_d0corr().at(elIdx)                        : " << cms3.els_d0corr().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_d0corrPhi().at(elIdx)                     : " << cms3.els_d0corrPhi().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_d0phiCov().at(elIdx)                      : " << cms3.els_d0phiCov().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_dEtaIn().at(elIdx)                        : " << cms3.els_dEtaIn().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_dEtaOut().at(elIdx)                       : " << cms3.els_dEtaOut().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_dPhiIn().at(elIdx)                        : " << cms3.els_dPhiIn().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_dPhiInPhiOut().at(elIdx)                  : " << cms3.els_dPhiInPhiOut().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_dPhiOut().at(elIdx)                       : " << cms3.els_dPhiOut().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_deltaEtaEleClusterTrackAtCalo().at(elIdx) : " << cms3.els_deltaEtaEleClusterTrackAtCalo().at(elIdx) << std::endl;
        // std::cout << " cms3.els_deltaPhiEleClusterTrackAtCalo().at(elIdx) : " << cms3.els_deltaPhiEleClusterTrackAtCalo().at(elIdx) << std::endl;
        // std::cout << " cms3.els_dxyPV().at(elIdx)                         : " << cms3.els_dxyPV().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_dzPV().at(elIdx)                          : " << cms3.els_dzPV().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_e1x5().at(elIdx)                          : " << cms3.els_e1x5().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_e1x5_full5x5().at(elIdx)                  : " << cms3.els_e1x5_full5x5().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_e2x5Max().at(elIdx)                       : " << cms3.els_e2x5Max().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_e2x5Max_full5x5().at(elIdx)               : " << cms3.els_e2x5Max_full5x5().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_e5x5().at(elIdx)                          : " << cms3.els_e5x5().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_e5x5_full5x5().at(elIdx)                  : " << cms3.els_e5x5_full5x5().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_eOverPIn().at(elIdx)                      : " << cms3.els_eOverPIn().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_eOverPOut().at(elIdx)                     : " << cms3.els_eOverPOut().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_eSC().at(elIdx)                           : " << cms3.els_eSC().at(elIdx)                           << std::endl;
        // std::cout << " cms3.els_eSCPresh().at(elIdx)                      : " << cms3.els_eSCPresh().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_eSCRaw().at(elIdx)                        : " << cms3.els_eSCRaw().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_eSeed().at(elIdx)                         : " << cms3.els_eSeed().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_eSeedOverPIn().at(elIdx)                  : " << cms3.els_eSeedOverPIn().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_eSeedOverPOut().at(elIdx)                 : " << cms3.els_eSeedOverPOut().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_ecalEnergy().at(elIdx)                    : " << cms3.els_ecalEnergy().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_ecalEnergyError().at(elIdx)               : " << cms3.els_ecalEnergyError().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_ecalIso().at(elIdx)                       : " << cms3.els_ecalIso().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_ecalIso04().at(elIdx)                     : " << cms3.els_ecalIso04().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_ecalPFClusterIso().at(elIdx)              : " << cms3.els_ecalPFClusterIso().at(elIdx)              << std::endl;
        // std::cout << " cms3.els_etaErr().at(elIdx)                        : " << cms3.els_etaErr().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_etaSC().at(elIdx)                         : " << cms3.els_etaSC().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_etaSCwidth().at(elIdx)                    : " << cms3.els_etaSCwidth().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_fbrem().at(elIdx)                         : " << cms3.els_fbrem().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_full5x5_hOverE().at(elIdx)                : " << cms3.els_full5x5_hOverE().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_hOverE().at(elIdx)                        : " << cms3.els_hOverE().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_hOverEBC().at(elIdx)                      : " << cms3.els_hOverEBC().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_hcalDepth1OverEcal().at(elIdx)            : " << cms3.els_hcalDepth1OverEcal().at(elIdx)            << std::endl;
        // std::cout << " cms3.els_hcalDepth1TowerSumEt().at(elIdx)          : " << cms3.els_hcalDepth1TowerSumEt().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_hcalDepth1TowerSumEt04().at(elIdx)        : " << cms3.els_hcalDepth1TowerSumEt04().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_hcalDepth2OverEcal().at(elIdx)            : " << cms3.els_hcalDepth2OverEcal().at(elIdx)            << std::endl;
        // std::cout << " cms3.els_hcalDepth2TowerSumEt().at(elIdx)          : " << cms3.els_hcalDepth2TowerSumEt().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_hcalDepth2TowerSumEt04().at(elIdx)        : " << cms3.els_hcalDepth2TowerSumEt04().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_hcalIso().at(elIdx)                       : " << cms3.els_hcalIso().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_hcalIso04().at(elIdx)                     : " << cms3.els_hcalIso04().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_hcalPFClusterIso().at(elIdx)              : " << cms3.els_hcalPFClusterIso().at(elIdx)              << std::endl;
        // std::cout << " cms3.els_ip2d().at(elIdx)                          : " << cms3.els_ip2d().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_ip2derr().at(elIdx)                       : " << cms3.els_ip2derr().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_ip3d().at(elIdx)                          : " << cms3.els_ip3d().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_ip3derr().at(elIdx)                       : " << cms3.els_ip3derr().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_jetBTagCSV().at(elIdx)                    : " << cms3.els_jetBTagCSV().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_mass().at(elIdx)                          : " << cms3.els_mass().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_mc3dr().at(elIdx)                         : " << cms3.els_mc3dr().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_mc_patMatch_dr().at(elIdx)                : " << cms3.els_mc_patMatch_dr().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_mcdr().at(elIdx)                          : " << cms3.els_mcdr().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_miniIso_ch().at(elIdx)                    : " << cms3.els_miniIso_ch().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_miniIso_db().at(elIdx)                    : " << cms3.els_miniIso_db().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_miniIso_em().at(elIdx)                    : " << cms3.els_miniIso_em().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_miniIso_nh().at(elIdx)                    : " << cms3.els_miniIso_nh().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_miniIso_uncor().at(elIdx)                 : " << cms3.els_miniIso_uncor().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_miniRelIso_all().at(elIdx)                : " << cms3.els_miniRelIso_all().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_miniRelIso_chg().at(elIdx)                : " << cms3.els_miniRelIso_chg().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_mva().at(elIdx)                           : " << cms3.els_mva().at(elIdx)                           << std::endl;
        // std::cout << " cms3.els_ndof().at(elIdx)                          : " << cms3.els_ndof().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_pfChargedHadronIso().at(elIdx)            : " << cms3.els_pfChargedHadronIso().at(elIdx)            << std::endl;
        // std::cout << " cms3.els_pfNeutralHadronIso().at(elIdx)            : " << cms3.els_pfNeutralHadronIso().at(elIdx)            << std::endl;
        // std::cout << " cms3.els_pfPUIso().at(elIdx)                       : " << cms3.els_pfPUIso().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_pfPhotonIso().at(elIdx)                   : " << cms3.els_pfPhotonIso().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_phiErr().at(elIdx)                        : " << cms3.els_phiErr().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_phiSC().at(elIdx)                         : " << cms3.els_phiSC().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_phiSCwidth().at(elIdx)                    : " << cms3.els_phiSCwidth().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_ptErr().at(elIdx)                         : " << cms3.els_ptErr().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_ptErrGsf().at(elIdx)                      : " << cms3.els_ptErrGsf().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_ptRatio().at(elIdx)                       : " << cms3.els_ptRatio().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_ptRel().at(elIdx)                         : " << cms3.els_ptRel().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_r9().at(elIdx)                            : " << cms3.els_r9().at(elIdx)                            << std::endl;
        // std::cout << " cms3.els_r9_full5x5().at(elIdx)                    : " << cms3.els_r9_full5x5().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scIsEB().at(elIdx)                        : " << cms3.els_scIsEB().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_scPreshowerEnergyPlane1().at(elIdx)       : " << cms3.els_scPreshowerEnergyPlane1().at(elIdx)       << std::endl;
        // std::cout << " cms3.els_scPreshowerEnergyPlane2().at(elIdx)       : " << cms3.els_scPreshowerEnergyPlane2().at(elIdx)       << std::endl;
        // std::cout << " cms3.els_scR().at(elIdx)                           : " << cms3.els_scR().at(elIdx)                           << std::endl;
        // std::cout << " cms3.els_scSeed2x5LeftRightAsym().at(elIdx)        : " << cms3.els_scSeed2x5LeftRightAsym().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_scSeed2x5TopBottomAsym().at(elIdx)        : " << cms3.els_scSeed2x5TopBottomAsym().at(elIdx)        << std::endl;
        // std::cout << " cms3.els_scSeedCryEta().at(elIdx)                  : " << cms3.els_scSeedCryEta().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_scSeedCryIeta().at(elIdx)                 : " << cms3.els_scSeedCryIeta().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_scSeedCryIphi().at(elIdx)                 : " << cms3.els_scSeedCryIphi().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_scSeedCryIx().at(elIdx)                   : " << cms3.els_scSeedCryIx().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_scSeedCryIy().at(elIdx)                   : " << cms3.els_scSeedCryIy().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_scSeedCryPhi().at(elIdx)                  : " << cms3.els_scSeedCryPhi().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_scSeedCryX().at(elIdx)                    : " << cms3.els_scSeedCryX().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedCryY().at(elIdx)                    : " << cms3.els_scSeedCryY().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedE2nd().at(elIdx)                    : " << cms3.els_scSeedE2nd().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedE2x5Bottom().at(elIdx)              : " << cms3.els_scSeedE2x5Bottom().at(elIdx)              << std::endl;
        // std::cout << " cms3.els_scSeedE2x5Left().at(elIdx)                : " << cms3.els_scSeedE2x5Left().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_scSeedE2x5Right().at(elIdx)               : " << cms3.els_scSeedE2x5Right().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_scSeedE2x5Top().at(elIdx)                 : " << cms3.els_scSeedE2x5Top().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_scSeedE3x3().at(elIdx)                    : " << cms3.els_scSeedE3x3().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedEBottom().at(elIdx)                 : " << cms3.els_scSeedEBottom().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_scSeedELeft().at(elIdx)                   : " << cms3.els_scSeedELeft().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_scSeedERight().at(elIdx)                  : " << cms3.els_scSeedERight().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_scSeedETop().at(elIdx)                    : " << cms3.els_scSeedETop().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedEmax().at(elIdx)                    : " << cms3.els_scSeedEmax().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedEta().at(elIdx)                     : " << cms3.els_scSeedEta().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_scSeedLeftRightAsym().at(elIdx)           : " << cms3.els_scSeedLeftRightAsym().at(elIdx)           << std::endl;
        // std::cout << " cms3.els_scSeedPhi().at(elIdx)                     : " << cms3.els_scSeedPhi().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_scSeedSigmaIetaIphi().at(elIdx)           : " << cms3.els_scSeedSigmaIetaIphi().at(elIdx)           << std::endl;
        // std::cout << " cms3.els_scSeedSize().at(elIdx)                    : " << cms3.els_scSeedSize().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_scSeedTopBottomAsym().at(elIdx)           : " << cms3.els_scSeedTopBottomAsym().at(elIdx)           << std::endl;
        // std::cout << " cms3.els_sigmaEtaEta().at(elIdx)                   : " << cms3.els_sigmaEtaEta().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_sigmaEtaEta_full5x5().at(elIdx)           : " << cms3.els_sigmaEtaEta_full5x5().at(elIdx)           << std::endl;
        // std::cout << " cms3.els_sigmaIEtaIEta().at(elIdx)                 : " << cms3.els_sigmaIEtaIEta().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_sigmaIEtaIEta_full5x5().at(elIdx)         : " << cms3.els_sigmaIEtaIEta_full5x5().at(elIdx)         << std::endl;
        // std::cout << " cms3.els_sigmaIPhiIPhi().at(elIdx)                 : " << cms3.els_sigmaIPhiIPhi().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_sigmaIPhiIPhi_full5x5().at(elIdx)         : " << cms3.els_sigmaIPhiIPhi_full5x5().at(elIdx)         << std::endl;
        // std::cout << " cms3.els_sigmaIphiIphi().at(elIdx)                 : " << cms3.els_sigmaIphiIphi().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_tkIso().at(elIdx)                         : " << cms3.els_tkIso().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_tkIso04().at(elIdx)                       : " << cms3.els_tkIso04().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_trackMomentumError().at(elIdx)            : " << cms3.els_trackMomentumError().at(elIdx)            << std::endl;
        // std::cout << " cms3.els_trkdr().at(elIdx)                         : " << cms3.els_trkdr().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_trkshFrac().at(elIdx)                     : " << cms3.els_trkshFrac().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_z0().at(elIdx)                            : " << cms3.els_z0().at(elIdx)                            << std::endl;
        // std::cout << " cms3.els_z0Err().at(elIdx)                         : " << cms3.els_z0Err().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_z0corr().at(elIdx)                        : " << cms3.els_z0corr().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_N_ECALClusters().at(elIdx)                : " << cms3.els_N_ECALClusters().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_N_PSClusters().at(elIdx)                  : " << cms3.els_N_PSClusters().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_VIDNonTrigMvaCat().at(elIdx)              : " << cms3.els_VIDNonTrigMvaCat().at(elIdx)              << std::endl;
        // std::cout << " cms3.els_VIDSpring16GPMvaCat().at(elIdx)           : " << cms3.els_VIDSpring16GPMvaCat().at(elIdx)           << std::endl;
        // std::cout << " cms3.els_VIDSpring16HZZMvaCat().at(elIdx)          : " << cms3.els_VIDSpring16HZZMvaCat().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_VIDTrigMvaCat().at(elIdx)                 : " << cms3.els_VIDTrigMvaCat().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_category().at(elIdx)                      : " << cms3.els_category().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_charge().at(elIdx)                        : " << cms3.els_charge().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_ckf_charge().at(elIdx)                    : " << cms3.els_ckf_charge().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_ckf_laywithmeas().at(elIdx)               : " << cms3.els_ckf_laywithmeas().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_class().at(elIdx)                         : " << cms3.els_class().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_exp_innerlayers().at(elIdx)               : " << cms3.els_exp_innerlayers().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_exp_outerlayers().at(elIdx)               : " << cms3.els_exp_outerlayers().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_fiduciality().at(elIdx)                   : " << cms3.els_fiduciality().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_isEB().at(elIdx)                          : " << cms3.els_isEB().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_isEcalDriven().at(elIdx)                  : " << cms3.els_isEcalDriven().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_isTrackerDriven().at(elIdx)               : " << cms3.els_isTrackerDriven().at(elIdx)               << std::endl;
        // std::cout << " cms3.els_jetNDauChargedMVASel().at(elIdx)          : " << cms3.els_jetNDauChargedMVASel().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_lostHits().at(elIdx)                      : " << cms3.els_lostHits().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_lost_pixelhits().at(elIdx)                : " << cms3.els_lost_pixelhits().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_mc3_id().at(elIdx)                        : " << cms3.els_mc3_id().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_mc3_motherid().at(elIdx)                  : " << cms3.els_mc3_motherid().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_mc3_motheridx().at(elIdx)                 : " << cms3.els_mc3_motheridx().at(elIdx)                 << std::endl;
        // std::cout << " cms3.els_mc3idx().at(elIdx)                        : " << cms3.els_mc3idx().at(elIdx)                        << std::endl;
        // std::cout << " cms3.els_mc_id().at(elIdx)                         : " << cms3.els_mc_id().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_mc_motherid().at(elIdx)                   : " << cms3.els_mc_motherid().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_mc_patMatch_id().at(elIdx)                : " << cms3.els_mc_patMatch_id().at(elIdx)                << std::endl;
        // std::cout << " cms3.els_mcidx().at(elIdx)                         : " << cms3.els_mcidx().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_nSeed().at(elIdx)                         : " << cms3.els_nSeed().at(elIdx)                         << std::endl;
        // std::cout << " cms3.els_nlayers().at(elIdx)                       : " << cms3.els_nlayers().at(elIdx)                       << std::endl;
        // std::cout << " cms3.els_nlayers3D().at(elIdx)                     : " << cms3.els_nlayers3D().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_nlayersLost().at(elIdx)                   : " << cms3.els_nlayersLost().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_passHEEPId().at(elIdx)                    : " << cms3.els_passHEEPId().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_passLooseId().at(elIdx)                   : " << cms3.els_passLooseId().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_passMediumId().at(elIdx)                  : " << cms3.els_passMediumId().at(elIdx)                  << std::endl;
        // std::cout << " cms3.els_passTightId().at(elIdx)                   : " << cms3.els_passTightId().at(elIdx)                   << std::endl;
        // std::cout << " cms3.els_passVIDNonTrigMvaWP80Id().at(elIdx)       : " << cms3.els_passVIDNonTrigMvaWP80Id().at(elIdx)       << std::endl;
        // std::cout << " cms3.els_passVIDNonTrigMvaWP90Id().at(elIdx)       : " << cms3.els_passVIDNonTrigMvaWP90Id().at(elIdx)       << std::endl;
        // std::cout << " cms3.els_passVIDTrigMvaWP80Id().at(elIdx)          : " << cms3.els_passVIDTrigMvaWP80Id().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_passVIDTrigMvaWP90Id().at(elIdx)          : " << cms3.els_passVIDTrigMvaWP90Id().at(elIdx)          << std::endl;
        // std::cout << " cms3.els_passVetoId().at(elIdx)                    : " << cms3.els_passVetoId().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_sccharge().at(elIdx)                      : " << cms3.els_sccharge().at(elIdx)                      << std::endl;
        // std::cout << " cms3.els_trk_charge().at(elIdx)                    : " << cms3.els_trk_charge().at(elIdx)                    << std::endl;
        // std::cout << " cms3.els_type().at(elIdx)                          : " << cms3.els_type().at(elIdx)                          << std::endl;
        // std::cout << " cms3.els_validHits().at(elIdx)                     : " << cms3.els_validHits().at(elIdx)                     << std::endl;
        // std::cout << " cms3.els_valid_pixelhits().at(elIdx)               : " << cms3.els_valid_pixelhits().at(elIdx)               << std::endl;

    }

}
