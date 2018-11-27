#include "wwwtree.h"
wwwtree www;

void wwwtree::Init(TTree *tree) {
  lep_p4_branch = tree->GetBranch("lep_p4");
  if (lep_p4_branch) lep_p4_branch->SetAddress(&lep_p4_);
  jets_p4_branch = tree->GetBranch("jets_p4");
  if (jets_p4_branch) jets_p4_branch->SetAddress(&jets_p4_);
  jets_up_p4_branch = tree->GetBranch("jets_up_p4");
  if (jets_up_p4_branch) jets_up_p4_branch->SetAddress(&jets_up_p4_);
  jets_dn_p4_branch = tree->GetBranch("jets_dn_p4");
  if (jets_dn_p4_branch) jets_dn_p4_branch->SetAddress(&jets_dn_p4_);
  ak8jets_p4_branch = tree->GetBranch("ak8jets_p4");
  if (ak8jets_p4_branch) ak8jets_p4_branch->SetAddress(&ak8jets_p4_);
  genPart_p4_branch = tree->GetBranch("genPart_p4");
  if (genPart_p4_branch) genPart_p4_branch->SetAddress(&genPart_p4_);
  jet0_wtag_p4_branch = tree->GetBranch("jet0_wtag_p4");
  if (jet0_wtag_p4_branch) jet0_wtag_p4_branch->SetAddress(&jet0_wtag_p4_);
  jet0_wtag_p4_up_branch = tree->GetBranch("jet0_wtag_p4_up");
  if (jet0_wtag_p4_up_branch) jet0_wtag_p4_up_branch->SetAddress(&jet0_wtag_p4_up_);
  jet0_wtag_p4_dn_branch = tree->GetBranch("jet0_wtag_p4_dn");
  if (jet0_wtag_p4_dn_branch) jet0_wtag_p4_dn_branch->SetAddress(&jet0_wtag_p4_dn_);
  jet1_wtag_p4_branch = tree->GetBranch("jet1_wtag_p4");
  if (jet1_wtag_p4_branch) jet1_wtag_p4_branch->SetAddress(&jet1_wtag_p4_);
  jet1_wtag_p4_up_branch = tree->GetBranch("jet1_wtag_p4_up");
  if (jet1_wtag_p4_up_branch) jet1_wtag_p4_up_branch->SetAddress(&jet1_wtag_p4_up_);
  jet1_wtag_p4_dn_branch = tree->GetBranch("jet1_wtag_p4_dn");
  if (jet1_wtag_p4_dn_branch) jet1_wtag_p4_dn_branch->SetAddress(&jet1_wtag_p4_dn_);
  jet0_wtag_p4_DR1_branch = tree->GetBranch("jet0_wtag_p4_DR1");
  if (jet0_wtag_p4_DR1_branch) jet0_wtag_p4_DR1_branch->SetAddress(&jet0_wtag_p4_DR1_);
  jet0_wtag_p4_DR1_up_branch = tree->GetBranch("jet0_wtag_p4_DR1_up");
  if (jet0_wtag_p4_DR1_up_branch) jet0_wtag_p4_DR1_up_branch->SetAddress(&jet0_wtag_p4_DR1_up_);
  jet0_wtag_p4_DR1_dn_branch = tree->GetBranch("jet0_wtag_p4_DR1_dn");
  if (jet0_wtag_p4_DR1_dn_branch) jet0_wtag_p4_DR1_dn_branch->SetAddress(&jet0_wtag_p4_DR1_dn_);
  jet1_wtag_p4_DR1_branch = tree->GetBranch("jet1_wtag_p4_DR1");
  if (jet1_wtag_p4_DR1_branch) jet1_wtag_p4_DR1_branch->SetAddress(&jet1_wtag_p4_DR1_);
  jet1_wtag_p4_DR1_up_branch = tree->GetBranch("jet1_wtag_p4_DR1_up");
  if (jet1_wtag_p4_DR1_up_branch) jet1_wtag_p4_DR1_up_branch->SetAddress(&jet1_wtag_p4_DR1_up_);
  jet1_wtag_p4_DR1_dn_branch = tree->GetBranch("jet1_wtag_p4_DR1_dn");
  if (jet1_wtag_p4_DR1_dn_branch) jet1_wtag_p4_DR1_dn_branch->SetAddress(&jet1_wtag_p4_DR1_dn_);

  tree->SetMakeClass(1);

  run_branch = tree->GetBranch("run");
  if (run_branch) run_branch->SetAddress(&run_);
  lumi_branch = tree->GetBranch("lumi");
  if (lumi_branch) lumi_branch->SetAddress(&lumi_);
  evt_branch = tree->GetBranch("evt");
  if (evt_branch) evt_branch->SetAddress(&evt_);
  isData_branch = tree->GetBranch("isData");
  if (isData_branch) isData_branch->SetAddress(&isData_);
  evt_scale1fb_branch = tree->GetBranch("evt_scale1fb");
  if (evt_scale1fb_branch) evt_scale1fb_branch->SetAddress(&evt_scale1fb_);
  xsec_br_branch = tree->GetBranch("xsec_br");
  if (xsec_br_branch) xsec_br_branch->SetAddress(&xsec_br_);
  evt_passgoodrunlist_branch = tree->GetBranch("evt_passgoodrunlist");
  if (evt_passgoodrunlist_branch) evt_passgoodrunlist_branch->SetAddress(&evt_passgoodrunlist_);
  CMS4path_branch = tree->GetBranch("CMS4path");
  if (CMS4path_branch) CMS4path_branch->SetAddress(&CMS4path_);
  CMS4index_branch = tree->GetBranch("CMS4index");
  if (CMS4index_branch) CMS4index_branch->SetAddress(&CMS4index_);
  weight_fr_r1_f1_branch = tree->GetBranch("weight_fr_r1_f1");
  if (weight_fr_r1_f1_branch) weight_fr_r1_f1_branch->SetAddress(&weight_fr_r1_f1_);
  weight_fr_r1_f2_branch = tree->GetBranch("weight_fr_r1_f2");
  if (weight_fr_r1_f2_branch) weight_fr_r1_f2_branch->SetAddress(&weight_fr_r1_f2_);
  weight_fr_r1_f0p5_branch = tree->GetBranch("weight_fr_r1_f0p5");
  if (weight_fr_r1_f0p5_branch) weight_fr_r1_f0p5_branch->SetAddress(&weight_fr_r1_f0p5_);
  weight_fr_r2_f1_branch = tree->GetBranch("weight_fr_r2_f1");
  if (weight_fr_r2_f1_branch) weight_fr_r2_f1_branch->SetAddress(&weight_fr_r2_f1_);
  weight_fr_r2_f2_branch = tree->GetBranch("weight_fr_r2_f2");
  if (weight_fr_r2_f2_branch) weight_fr_r2_f2_branch->SetAddress(&weight_fr_r2_f2_);
  weight_fr_r2_f0p5_branch = tree->GetBranch("weight_fr_r2_f0p5");
  if (weight_fr_r2_f0p5_branch) weight_fr_r2_f0p5_branch->SetAddress(&weight_fr_r2_f0p5_);
  weight_fr_r0p5_f1_branch = tree->GetBranch("weight_fr_r0p5_f1");
  if (weight_fr_r0p5_f1_branch) weight_fr_r0p5_f1_branch->SetAddress(&weight_fr_r0p5_f1_);
  weight_fr_r0p5_f2_branch = tree->GetBranch("weight_fr_r0p5_f2");
  if (weight_fr_r0p5_f2_branch) weight_fr_r0p5_f2_branch->SetAddress(&weight_fr_r0p5_f2_);
  weight_fr_r0p5_f0p5_branch = tree->GetBranch("weight_fr_r0p5_f0p5");
  if (weight_fr_r0p5_f0p5_branch) weight_fr_r0p5_f0p5_branch->SetAddress(&weight_fr_r0p5_f0p5_);
  weight_pdf_up_branch = tree->GetBranch("weight_pdf_up");
  if (weight_pdf_up_branch) weight_pdf_up_branch->SetAddress(&weight_pdf_up_);
  weight_pdf_down_branch = tree->GetBranch("weight_pdf_down");
  if (weight_pdf_down_branch) weight_pdf_down_branch->SetAddress(&weight_pdf_down_);
  weight_alphas_down_branch = tree->GetBranch("weight_alphas_down");
  if (weight_alphas_down_branch) weight_alphas_down_branch->SetAddress(&weight_alphas_down_);
  weight_alphas_up_branch = tree->GetBranch("weight_alphas_up");
  if (weight_alphas_up_branch) weight_alphas_up_branch->SetAddress(&weight_alphas_up_);
  weight_isr_branch = tree->GetBranch("weight_isr");
  if (weight_isr_branch) weight_isr_branch->SetAddress(&weight_isr_);
  weight_isr_up_branch = tree->GetBranch("weight_isr_up");
  if (weight_isr_up_branch) weight_isr_up_branch->SetAddress(&weight_isr_up_);
  weight_isr_down_branch = tree->GetBranch("weight_isr_down");
  if (weight_isr_down_branch) weight_isr_down_branch->SetAddress(&weight_isr_down_);
  HLT_DoubleMu_branch = tree->GetBranch("HLT_DoubleMu");
  if (HLT_DoubleMu_branch) HLT_DoubleMu_branch->SetAddress(&HLT_DoubleMu_);
  HLT_DoubleEl_branch = tree->GetBranch("HLT_DoubleEl");
  if (HLT_DoubleEl_branch) HLT_DoubleEl_branch->SetAddress(&HLT_DoubleEl_);
  HLT_DoubleEl_DZ_branch = tree->GetBranch("HLT_DoubleEl_DZ");
  if (HLT_DoubleEl_DZ_branch) HLT_DoubleEl_DZ_branch->SetAddress(&HLT_DoubleEl_DZ_);
  HLT_DoubleEl_DZ_2_branch = tree->GetBranch("HLT_DoubleEl_DZ_2");
  if (HLT_DoubleEl_DZ_2_branch) HLT_DoubleEl_DZ_2_branch->SetAddress(&HLT_DoubleEl_DZ_2_);
  HLT_MuEG_branch = tree->GetBranch("HLT_MuEG");
  if (HLT_MuEG_branch) HLT_MuEG_branch->SetAddress(&HLT_MuEG_);
  HLT_SingleIsoEl8_branch = tree->GetBranch("HLT_SingleIsoEl8");
  if (HLT_SingleIsoEl8_branch) HLT_SingleIsoEl8_branch->SetAddress(&HLT_SingleIsoEl8_);
  HLT_SingleIsoEl17_branch = tree->GetBranch("HLT_SingleIsoEl17");
  if (HLT_SingleIsoEl17_branch) HLT_SingleIsoEl17_branch->SetAddress(&HLT_SingleIsoEl17_);
  HLT_SingleIsoEl23_branch = tree->GetBranch("HLT_SingleIsoEl23");
  if (HLT_SingleIsoEl23_branch) HLT_SingleIsoEl23_branch->SetAddress(&HLT_SingleIsoEl23_);
  HLT_SingleIsoMu8_branch = tree->GetBranch("HLT_SingleIsoMu8");
  if (HLT_SingleIsoMu8_branch) HLT_SingleIsoMu8_branch->SetAddress(&HLT_SingleIsoMu8_);
  HLT_SingleIsoMu17_branch = tree->GetBranch("HLT_SingleIsoMu17");
  if (HLT_SingleIsoMu17_branch) HLT_SingleIsoMu17_branch->SetAddress(&HLT_SingleIsoMu17_);
  HLT_PFMET140_PFMHT140_IDTight_branch = tree->GetBranch("HLT_PFMET140_PFMHT140_IDTight");
  if (HLT_PFMET140_PFMHT140_IDTight_branch) HLT_PFMET140_PFMHT140_IDTight_branch->SetAddress(&HLT_PFMET140_PFMHT140_IDTight_);
  mc_HLT_DoubleMu_branch = tree->GetBranch("mc_HLT_DoubleMu");
  if (mc_HLT_DoubleMu_branch) mc_HLT_DoubleMu_branch->SetAddress(&mc_HLT_DoubleMu_);
  mc_HLT_DoubleEl_branch = tree->GetBranch("mc_HLT_DoubleEl");
  if (mc_HLT_DoubleEl_branch) mc_HLT_DoubleEl_branch->SetAddress(&mc_HLT_DoubleEl_);
  mc_HLT_DoubleEl_DZ_branch = tree->GetBranch("mc_HLT_DoubleEl_DZ");
  if (mc_HLT_DoubleEl_DZ_branch) mc_HLT_DoubleEl_DZ_branch->SetAddress(&mc_HLT_DoubleEl_DZ_);
  mc_HLT_DoubleEl_DZ_2_branch = tree->GetBranch("mc_HLT_DoubleEl_DZ_2");
  if (mc_HLT_DoubleEl_DZ_2_branch) mc_HLT_DoubleEl_DZ_2_branch->SetAddress(&mc_HLT_DoubleEl_DZ_2_);
  mc_HLT_MuEG_branch = tree->GetBranch("mc_HLT_MuEG");
  if (mc_HLT_MuEG_branch) mc_HLT_MuEG_branch->SetAddress(&mc_HLT_MuEG_);
  mc_HLT_SingleIsoEl8_branch = tree->GetBranch("mc_HLT_SingleIsoEl8");
  if (mc_HLT_SingleIsoEl8_branch) mc_HLT_SingleIsoEl8_branch->SetAddress(&mc_HLT_SingleIsoEl8_);
  mc_HLT_SingleIsoEl17_branch = tree->GetBranch("mc_HLT_SingleIsoEl17");
  if (mc_HLT_SingleIsoEl17_branch) mc_HLT_SingleIsoEl17_branch->SetAddress(&mc_HLT_SingleIsoEl17_);
  mc_HLT_SingleIsoEl23_branch = tree->GetBranch("mc_HLT_SingleIsoEl23");
  if (mc_HLT_SingleIsoEl23_branch) mc_HLT_SingleIsoEl23_branch->SetAddress(&mc_HLT_SingleIsoEl23_);
  mc_HLT_SingleIsoMu8_branch = tree->GetBranch("mc_HLT_SingleIsoMu8");
  if (mc_HLT_SingleIsoMu8_branch) mc_HLT_SingleIsoMu8_branch->SetAddress(&mc_HLT_SingleIsoMu8_);
  mc_HLT_SingleIsoMu17_branch = tree->GetBranch("mc_HLT_SingleIsoMu17");
  if (mc_HLT_SingleIsoMu17_branch) mc_HLT_SingleIsoMu17_branch->SetAddress(&mc_HLT_SingleIsoMu17_);
  mc_HLT_PFMET140_PFMHT140_IDTight_branch = tree->GetBranch("mc_HLT_PFMET140_PFMHT140_IDTight");
  if (mc_HLT_PFMET140_PFMHT140_IDTight_branch) mc_HLT_PFMET140_PFMHT140_IDTight_branch->SetAddress(&mc_HLT_PFMET140_PFMHT140_IDTight_);
  pass_duplicate_ee_em_mm_branch = tree->GetBranch("pass_duplicate_ee_em_mm");
  if (pass_duplicate_ee_em_mm_branch) pass_duplicate_ee_em_mm_branch->SetAddress(&pass_duplicate_ee_em_mm_);
  pass_duplicate_mm_em_ee_branch = tree->GetBranch("pass_duplicate_mm_em_ee");
  if (pass_duplicate_mm_em_ee_branch) pass_duplicate_mm_em_ee_branch->SetAddress(&pass_duplicate_mm_em_ee_);
  is2016_branch = tree->GetBranch("is2016");
  if (is2016_branch) is2016_branch->SetAddress(&is2016_);
  is2017_branch = tree->GetBranch("is2017");
  if (is2017_branch) is2017_branch->SetAddress(&is2017_);
  HLT_MuEG_2016_branch = tree->GetBranch("HLT_MuEG_2016");
  if (HLT_MuEG_2016_branch) HLT_MuEG_2016_branch->SetAddress(&HLT_MuEG_2016_);
  mc_HLT_MuEG_2016_branch = tree->GetBranch("mc_HLT_MuEG_2016");
  if (mc_HLT_MuEG_2016_branch) mc_HLT_MuEG_2016_branch->SetAddress(&mc_HLT_MuEG_2016_);
  pass_duplicate_ee_em2016_mm_branch = tree->GetBranch("pass_duplicate_ee_em2016_mm");
  if (pass_duplicate_ee_em2016_mm_branch) pass_duplicate_ee_em2016_mm_branch->SetAddress(&pass_duplicate_ee_em2016_mm_);
  pass_duplicate_mm_em2016_ee_branch = tree->GetBranch("pass_duplicate_mm_em2016_ee");
  if (pass_duplicate_mm_em2016_ee_branch) pass_duplicate_mm_em2016_ee_branch->SetAddress(&pass_duplicate_mm_em2016_ee_);
  passTrigger_branch = tree->GetBranch("passTrigger");
  if (passTrigger_branch) passTrigger_branch->SetAddress(&passTrigger_);
  lep_pt_branch = tree->GetBranch("lep_pt");
  if (lep_pt_branch) lep_pt_branch->SetAddress(&lep_pt_);
  lep_eta_branch = tree->GetBranch("lep_eta");
  if (lep_eta_branch) lep_eta_branch->SetAddress(&lep_eta_);
  lep_phi_branch = tree->GetBranch("lep_phi");
  if (lep_phi_branch) lep_phi_branch->SetAddress(&lep_phi_);
  lep_coneCorrPt_branch = tree->GetBranch("lep_coneCorrPt");
  if (lep_coneCorrPt_branch) lep_coneCorrPt_branch->SetAddress(&lep_coneCorrPt_);
  lep_ip3d_branch = tree->GetBranch("lep_ip3d");
  if (lep_ip3d_branch) lep_ip3d_branch->SetAddress(&lep_ip3d_);
  lep_ip3derr_branch = tree->GetBranch("lep_ip3derr");
  if (lep_ip3derr_branch) lep_ip3derr_branch->SetAddress(&lep_ip3derr_);
  lep_isTriggerSafe_v1_branch = tree->GetBranch("lep_isTriggerSafe_v1");
  if (lep_isTriggerSafe_v1_branch) lep_isTriggerSafe_v1_branch->SetAddress(&lep_isTriggerSafe_v1_);
  lep_lostHits_branch = tree->GetBranch("lep_lostHits");
  if (lep_lostHits_branch) lep_lostHits_branch->SetAddress(&lep_lostHits_);
  lep_convVeto_branch = tree->GetBranch("lep_convVeto");
  if (lep_convVeto_branch) lep_convVeto_branch->SetAddress(&lep_convVeto_);
  lep_motherIdSS_branch = tree->GetBranch("lep_motherIdSS");
  if (lep_motherIdSS_branch) lep_motherIdSS_branch->SetAddress(&lep_motherIdSS_);
  lep_pass_VVV_cutbased_3l_fo_branch = tree->GetBranch("lep_pass_VVV_cutbased_3l_fo");
  if (lep_pass_VVV_cutbased_3l_fo_branch) lep_pass_VVV_cutbased_3l_fo_branch->SetAddress(&lep_pass_VVV_cutbased_3l_fo_);
  lep_pass_VVV_cutbased_3l_tight_branch = tree->GetBranch("lep_pass_VVV_cutbased_3l_tight");
  if (lep_pass_VVV_cutbased_3l_tight_branch) lep_pass_VVV_cutbased_3l_tight_branch->SetAddress(&lep_pass_VVV_cutbased_3l_tight_);
  lep_pass_VVV_cutbased_fo_branch = tree->GetBranch("lep_pass_VVV_cutbased_fo");
  if (lep_pass_VVV_cutbased_fo_branch) lep_pass_VVV_cutbased_fo_branch->SetAddress(&lep_pass_VVV_cutbased_fo_);
  lep_pass_VVV_cutbased_tight_branch = tree->GetBranch("lep_pass_VVV_cutbased_tight");
  if (lep_pass_VVV_cutbased_tight_branch) lep_pass_VVV_cutbased_tight_branch->SetAddress(&lep_pass_VVV_cutbased_tight_);
  lep_pass_VVV_cutbased_veto_branch = tree->GetBranch("lep_pass_VVV_cutbased_veto");
  if (lep_pass_VVV_cutbased_veto_branch) lep_pass_VVV_cutbased_veto_branch->SetAddress(&lep_pass_VVV_cutbased_veto_);
  lep_pass_VVV_cutbased_fo_noiso_branch = tree->GetBranch("lep_pass_VVV_cutbased_fo_noiso");
  if (lep_pass_VVV_cutbased_fo_noiso_branch) lep_pass_VVV_cutbased_fo_noiso_branch->SetAddress(&lep_pass_VVV_cutbased_fo_noiso_);
  lep_pass_VVV_cutbased_tight_noiso_branch = tree->GetBranch("lep_pass_VVV_cutbased_tight_noiso");
  if (lep_pass_VVV_cutbased_tight_noiso_branch) lep_pass_VVV_cutbased_tight_noiso_branch->SetAddress(&lep_pass_VVV_cutbased_tight_noiso_);
  lep_pass_VVV_cutbased_veto_noiso_branch = tree->GetBranch("lep_pass_VVV_cutbased_veto_noiso");
  if (lep_pass_VVV_cutbased_veto_noiso_branch) lep_pass_VVV_cutbased_veto_noiso_branch->SetAddress(&lep_pass_VVV_cutbased_veto_noiso_);
  lep_pass_POG_veto_branch = tree->GetBranch("lep_pass_POG_veto");
  if (lep_pass_POG_veto_branch) lep_pass_POG_veto_branch->SetAddress(&lep_pass_POG_veto_);
  lep_pass_POG_loose_branch = tree->GetBranch("lep_pass_POG_loose");
  if (lep_pass_POG_loose_branch) lep_pass_POG_loose_branch->SetAddress(&lep_pass_POG_loose_);
  lep_pass_POG_medium_branch = tree->GetBranch("lep_pass_POG_medium");
  if (lep_pass_POG_medium_branch) lep_pass_POG_medium_branch->SetAddress(&lep_pass_POG_medium_);
  lep_pass_POG_tight_branch = tree->GetBranch("lep_pass_POG_tight");
  if (lep_pass_POG_tight_branch) lep_pass_POG_tight_branch->SetAddress(&lep_pass_POG_tight_);
  lep_pdgId_branch = tree->GetBranch("lep_pdgId");
  if (lep_pdgId_branch) lep_pdgId_branch->SetAddress(&lep_pdgId_);
  lep_dxy_branch = tree->GetBranch("lep_dxy");
  if (lep_dxy_branch) lep_dxy_branch->SetAddress(&lep_dxy_);
  lep_dz_branch = tree->GetBranch("lep_dz");
  if (lep_dz_branch) lep_dz_branch->SetAddress(&lep_dz_);
  lep_pterr_branch = tree->GetBranch("lep_pterr");
  if (lep_pterr_branch) lep_pterr_branch->SetAddress(&lep_pterr_);
  lep_relIso04DB_branch = tree->GetBranch("lep_relIso04DB");
  if (lep_relIso04DB_branch) lep_relIso04DB_branch->SetAddress(&lep_relIso04DB_);
  lep_relIso03EA_branch = tree->GetBranch("lep_relIso03EA");
  if (lep_relIso03EA_branch) lep_relIso03EA_branch->SetAddress(&lep_relIso03EA_);
  lep_relIso03EALep_branch = tree->GetBranch("lep_relIso03EALep");
  if (lep_relIso03EALep_branch) lep_relIso03EALep_branch->SetAddress(&lep_relIso03EALep_);
  lep_relIso03EAv2_branch = tree->GetBranch("lep_relIso03EAv2");
  if (lep_relIso03EAv2_branch) lep_relIso03EAv2_branch->SetAddress(&lep_relIso03EAv2_);
  lep_relIso04EAv2_branch = tree->GetBranch("lep_relIso04EAv2");
  if (lep_relIso04EAv2_branch) lep_relIso04EAv2_branch->SetAddress(&lep_relIso04EAv2_);
  lep_relIso03EAv2Lep_branch = tree->GetBranch("lep_relIso03EAv2Lep");
  if (lep_relIso03EAv2Lep_branch) lep_relIso03EAv2Lep_branch->SetAddress(&lep_relIso03EAv2Lep_);
  lep_tightCharge_branch = tree->GetBranch("lep_tightCharge");
  if (lep_tightCharge_branch) lep_tightCharge_branch->SetAddress(&lep_tightCharge_);
  lep_trk_pt_branch = tree->GetBranch("lep_trk_pt");
  if (lep_trk_pt_branch) lep_trk_pt_branch->SetAddress(&lep_trk_pt_);
  lep_charge_branch = tree->GetBranch("lep_charge");
  if (lep_charge_branch) lep_charge_branch->SetAddress(&lep_charge_);
  lep_etaSC_branch = tree->GetBranch("lep_etaSC");
  if (lep_etaSC_branch) lep_etaSC_branch->SetAddress(&lep_etaSC_);
  lep_MVA_branch = tree->GetBranch("lep_MVA");
  if (lep_MVA_branch) lep_MVA_branch->SetAddress(&lep_MVA_);
  lep_isMediumPOG_branch = tree->GetBranch("lep_isMediumPOG");
  if (lep_isMediumPOG_branch) lep_isMediumPOG_branch->SetAddress(&lep_isMediumPOG_);
  lep_isTightPOG_branch = tree->GetBranch("lep_isTightPOG");
  if (lep_isTightPOG_branch) lep_isTightPOG_branch->SetAddress(&lep_isTightPOG_);
  lep_isFromW_branch = tree->GetBranch("lep_isFromW");
  if (lep_isFromW_branch) lep_isFromW_branch->SetAddress(&lep_isFromW_);
  lep_isFromZ_branch = tree->GetBranch("lep_isFromZ");
  if (lep_isFromZ_branch) lep_isFromZ_branch->SetAddress(&lep_isFromZ_);
  lep_isFromB_branch = tree->GetBranch("lep_isFromB");
  if (lep_isFromB_branch) lep_isFromB_branch->SetAddress(&lep_isFromB_);
  lep_isFromC_branch = tree->GetBranch("lep_isFromC");
  if (lep_isFromC_branch) lep_isFromC_branch->SetAddress(&lep_isFromC_);
  lep_isFromL_branch = tree->GetBranch("lep_isFromL");
  if (lep_isFromL_branch) lep_isFromL_branch->SetAddress(&lep_isFromL_);
  lep_isFromLF_branch = tree->GetBranch("lep_isFromLF");
  if (lep_isFromLF_branch) lep_isFromLF_branch->SetAddress(&lep_isFromLF_);
  lep_genPart_index_branch = tree->GetBranch("lep_genPart_index");
  if (lep_genPart_index_branch) lep_genPart_index_branch->SetAddress(&lep_genPart_index_);
  lep_r9_branch = tree->GetBranch("lep_r9");
  if (lep_r9_branch) lep_r9_branch->SetAddress(&lep_r9_);
  lep_nlayers_branch = tree->GetBranch("lep_nlayers");
  if (lep_nlayers_branch) lep_nlayers_branch->SetAddress(&lep_nlayers_);
  el_pt_branch = tree->GetBranch("el_pt");
  if (el_pt_branch) el_pt_branch->SetAddress(&el_pt_);
  el_eta_branch = tree->GetBranch("el_eta");
  if (el_eta_branch) el_eta_branch->SetAddress(&el_eta_);
  el_phi_branch = tree->GetBranch("el_phi");
  if (el_phi_branch) el_phi_branch->SetAddress(&el_phi_);
  el_relIso03EA_branch = tree->GetBranch("el_relIso03EA");
  if (el_relIso03EA_branch) el_relIso03EA_branch->SetAddress(&el_relIso03EA_);
  el_relIso03EALep_branch = tree->GetBranch("el_relIso03EALep");
  if (el_relIso03EALep_branch) el_relIso03EALep_branch->SetAddress(&el_relIso03EALep_);
  el_ip3d_branch = tree->GetBranch("el_ip3d");
  if (el_ip3d_branch) el_ip3d_branch->SetAddress(&el_ip3d_);
  mu_pt_branch = tree->GetBranch("mu_pt");
  if (mu_pt_branch) mu_pt_branch->SetAddress(&mu_pt_);
  mu_eta_branch = tree->GetBranch("mu_eta");
  if (mu_eta_branch) mu_eta_branch->SetAddress(&mu_eta_);
  mu_phi_branch = tree->GetBranch("mu_phi");
  if (mu_phi_branch) mu_phi_branch->SetAddress(&mu_phi_);
  mu_relIso04DB_branch = tree->GetBranch("mu_relIso04DB");
  if (mu_relIso04DB_branch) mu_relIso04DB_branch->SetAddress(&mu_relIso04DB_);
  mu_relIso03EA_branch = tree->GetBranch("mu_relIso03EA");
  if (mu_relIso03EA_branch) mu_relIso03EA_branch->SetAddress(&mu_relIso03EA_);
  mu_relIso03EALep_branch = tree->GetBranch("mu_relIso03EALep");
  if (mu_relIso03EALep_branch) mu_relIso03EALep_branch->SetAddress(&mu_relIso03EALep_);
  mu_ip3d_branch = tree->GetBranch("mu_ip3d");
  if (mu_ip3d_branch) mu_ip3d_branch->SetAddress(&mu_ip3d_);
  lbnt_pt_branch = tree->GetBranch("lbnt_pt");
  if (lbnt_pt_branch) lbnt_pt_branch->SetAddress(&lbnt_pt_);
  lbnt_coneCorrPt_branch = tree->GetBranch("lbnt_coneCorrPt");
  if (lbnt_coneCorrPt_branch) lbnt_coneCorrPt_branch->SetAddress(&lbnt_coneCorrPt_);
  lbnt_abseta_branch = tree->GetBranch("lbnt_abseta");
  if (lbnt_abseta_branch) lbnt_abseta_branch->SetAddress(&lbnt_abseta_);
  lbnt_pdgId_branch = tree->GetBranch("lbnt_pdgId");
  if (lbnt_pdgId_branch) lbnt_pdgId_branch->SetAddress(&lbnt_pdgId_);
  lbnt_el_pt_branch = tree->GetBranch("lbnt_el_pt");
  if (lbnt_el_pt_branch) lbnt_el_pt_branch->SetAddress(&lbnt_el_pt_);
  lbnt_el_coneCorrPt_branch = tree->GetBranch("lbnt_el_coneCorrPt");
  if (lbnt_el_coneCorrPt_branch) lbnt_el_coneCorrPt_branch->SetAddress(&lbnt_el_coneCorrPt_);
  lbnt_el_abseta_branch = tree->GetBranch("lbnt_el_abseta");
  if (lbnt_el_abseta_branch) lbnt_el_abseta_branch->SetAddress(&lbnt_el_abseta_);
  lbnt_mu_pt_branch = tree->GetBranch("lbnt_mu_pt");
  if (lbnt_mu_pt_branch) lbnt_mu_pt_branch->SetAddress(&lbnt_mu_pt_);
  lbnt_mu_coneCorrPt_branch = tree->GetBranch("lbnt_mu_coneCorrPt");
  if (lbnt_mu_coneCorrPt_branch) lbnt_mu_coneCorrPt_branch->SetAddress(&lbnt_mu_coneCorrPt_);
  lbnt_mu_abseta_branch = tree->GetBranch("lbnt_mu_abseta");
  if (lbnt_mu_abseta_branch) lbnt_mu_abseta_branch->SetAddress(&lbnt_mu_abseta_);
  jets_csv_branch = tree->GetBranch("jets_csv");
  if (jets_csv_branch) jets_csv_branch->SetAddress(&jets_csv_);
  jets_up_csv_branch = tree->GetBranch("jets_up_csv");
  if (jets_up_csv_branch) jets_up_csv_branch->SetAddress(&jets_up_csv_);
  jets_dn_csv_branch = tree->GetBranch("jets_dn_csv");
  if (jets_dn_csv_branch) jets_dn_csv_branch->SetAddress(&jets_dn_csv_);
  ak8jets_softdropMass_branch = tree->GetBranch("ak8jets_softdropMass");
  if (ak8jets_softdropMass_branch) ak8jets_softdropMass_branch->SetAddress(&ak8jets_softdropMass_);
  ak8jets_prunedMass_branch = tree->GetBranch("ak8jets_prunedMass");
  if (ak8jets_prunedMass_branch) ak8jets_prunedMass_branch->SetAddress(&ak8jets_prunedMass_);
  ak8jets_trimmedMass_branch = tree->GetBranch("ak8jets_trimmedMass");
  if (ak8jets_trimmedMass_branch) ak8jets_trimmedMass_branch->SetAddress(&ak8jets_trimmedMass_);
  ak8jets_mass_branch = tree->GetBranch("ak8jets_mass");
  if (ak8jets_mass_branch) ak8jets_mass_branch->SetAddress(&ak8jets_mass_);
  ak8jets_nJettinessTau1_branch = tree->GetBranch("ak8jets_nJettinessTau1");
  if (ak8jets_nJettinessTau1_branch) ak8jets_nJettinessTau1_branch->SetAddress(&ak8jets_nJettinessTau1_);
  ak8jets_nJettinessTau2_branch = tree->GetBranch("ak8jets_nJettinessTau2");
  if (ak8jets_nJettinessTau2_branch) ak8jets_nJettinessTau2_branch->SetAddress(&ak8jets_nJettinessTau2_);
  ak8jets_softdropPuppiSubjet1_branch = tree->GetBranch("ak8jets_softdropPuppiSubjet1");
  if (ak8jets_softdropPuppiSubjet1_branch) ak8jets_softdropPuppiSubjet1_branch->SetAddress(&ak8jets_softdropPuppiSubjet1_);
  ak8jets_softdropPuppiSubjet2_branch = tree->GetBranch("ak8jets_softdropPuppiSubjet2");
  if (ak8jets_softdropPuppiSubjet2_branch) ak8jets_softdropPuppiSubjet2_branch->SetAddress(&ak8jets_softdropPuppiSubjet2_);
  ak8jets_puppi_softdropMass_branch = tree->GetBranch("ak8jets_puppi_softdropMass");
  if (ak8jets_puppi_softdropMass_branch) ak8jets_puppi_softdropMass_branch->SetAddress(&ak8jets_puppi_softdropMass_);
  ak8jets_puppi_nJettinessTau1_branch = tree->GetBranch("ak8jets_puppi_nJettinessTau1");
  if (ak8jets_puppi_nJettinessTau1_branch) ak8jets_puppi_nJettinessTau1_branch->SetAddress(&ak8jets_puppi_nJettinessTau1_);
  ak8jets_puppi_nJettinessTau2_branch = tree->GetBranch("ak8jets_puppi_nJettinessTau2");
  if (ak8jets_puppi_nJettinessTau2_branch) ak8jets_puppi_nJettinessTau2_branch->SetAddress(&ak8jets_puppi_nJettinessTau2_);
  ak8jets_puppi_eta_branch = tree->GetBranch("ak8jets_puppi_eta");
  if (ak8jets_puppi_eta_branch) ak8jets_puppi_eta_branch->SetAddress(&ak8jets_puppi_eta_);
  ak8jets_puppi_phi_branch = tree->GetBranch("ak8jets_puppi_phi");
  if (ak8jets_puppi_phi_branch) ak8jets_puppi_phi_branch->SetAddress(&ak8jets_puppi_phi_);
  ak8jets_puppi_pt_branch = tree->GetBranch("ak8jets_puppi_pt");
  if (ak8jets_puppi_pt_branch) ak8jets_puppi_pt_branch->SetAddress(&ak8jets_puppi_pt_);
  ak8jets_puppi_mass_branch = tree->GetBranch("ak8jets_puppi_mass");
  if (ak8jets_puppi_mass_branch) ak8jets_puppi_mass_branch->SetAddress(&ak8jets_puppi_mass_);
  met_pt_branch = tree->GetBranch("met_pt");
  if (met_pt_branch) met_pt_branch->SetAddress(&met_pt_);
  met_phi_branch = tree->GetBranch("met_phi");
  if (met_phi_branch) met_phi_branch->SetAddress(&met_phi_);
  met_up_pt_branch = tree->GetBranch("met_up_pt");
  if (met_up_pt_branch) met_up_pt_branch->SetAddress(&met_up_pt_);
  met_up_phi_branch = tree->GetBranch("met_up_phi");
  if (met_up_phi_branch) met_up_phi_branch->SetAddress(&met_up_phi_);
  met_dn_pt_branch = tree->GetBranch("met_dn_pt");
  if (met_dn_pt_branch) met_dn_pt_branch->SetAddress(&met_dn_pt_);
  met_dn_phi_branch = tree->GetBranch("met_dn_phi");
  if (met_dn_phi_branch) met_dn_phi_branch->SetAddress(&met_dn_phi_);
  met_gen_pt_branch = tree->GetBranch("met_gen_pt");
  if (met_gen_pt_branch) met_gen_pt_branch->SetAddress(&met_gen_pt_);
  met_gen_phi_branch = tree->GetBranch("met_gen_phi");
  if (met_gen_phi_branch) met_gen_phi_branch->SetAddress(&met_gen_phi_);
  firstgoodvertex_branch = tree->GetBranch("firstgoodvertex");
  if (firstgoodvertex_branch) firstgoodvertex_branch->SetAddress(&firstgoodvertex_);
  nTrueInt_branch = tree->GetBranch("nTrueInt");
  if (nTrueInt_branch) nTrueInt_branch->SetAddress(&nTrueInt_);
  nVert_branch = tree->GetBranch("nVert");
  if (nVert_branch) nVert_branch->SetAddress(&nVert_);
  nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch = tree->GetBranch("nisoTrack_mt2_cleaned_VVV_cutbased_veto");
  if (nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch) nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch->SetAddress(&nisoTrack_mt2_cleaned_VVV_cutbased_veto_);
  weight_btagsf_branch = tree->GetBranch("weight_btagsf");
  if (weight_btagsf_branch) weight_btagsf_branch->SetAddress(&weight_btagsf_);
  weight_btagsf_heavy_DN_branch = tree->GetBranch("weight_btagsf_heavy_DN");
  if (weight_btagsf_heavy_DN_branch) weight_btagsf_heavy_DN_branch->SetAddress(&weight_btagsf_heavy_DN_);
  weight_btagsf_heavy_UP_branch = tree->GetBranch("weight_btagsf_heavy_UP");
  if (weight_btagsf_heavy_UP_branch) weight_btagsf_heavy_UP_branch->SetAddress(&weight_btagsf_heavy_UP_);
  weight_btagsf_light_DN_branch = tree->GetBranch("weight_btagsf_light_DN");
  if (weight_btagsf_light_DN_branch) weight_btagsf_light_DN_branch->SetAddress(&weight_btagsf_light_DN_);
  weight_btagsf_light_UP_branch = tree->GetBranch("weight_btagsf_light_UP");
  if (weight_btagsf_light_UP_branch) weight_btagsf_light_UP_branch->SetAddress(&weight_btagsf_light_UP_);
  gen_ht_branch = tree->GetBranch("gen_ht");
  if (gen_ht_branch) gen_ht_branch->SetAddress(&gen_ht_);
  genPart_motherId_branch = tree->GetBranch("genPart_motherId");
  if (genPart_motherId_branch) genPart_motherId_branch->SetAddress(&genPart_motherId_);
  genPart_pdgId_branch = tree->GetBranch("genPart_pdgId");
  if (genPart_pdgId_branch) genPart_pdgId_branch->SetAddress(&genPart_pdgId_);
  genPart_charge_branch = tree->GetBranch("genPart_charge");
  if (genPart_charge_branch) genPart_charge_branch->SetAddress(&genPart_charge_);
  genPart_status_branch = tree->GetBranch("genPart_status");
  if (genPart_status_branch) genPart_status_branch->SetAddress(&genPart_status_);
  ngenLep_branch = tree->GetBranch("ngenLep");
  if (ngenLep_branch) ngenLep_branch->SetAddress(&ngenLep_);
  ngenLepFromTau_branch = tree->GetBranch("ngenLepFromTau");
  if (ngenLepFromTau_branch) ngenLepFromTau_branch->SetAddress(&ngenLepFromTau_);
  Flag_AllEventFilters_branch = tree->GetBranch("Flag_AllEventFilters");
  if (Flag_AllEventFilters_branch) Flag_AllEventFilters_branch->SetAddress(&Flag_AllEventFilters_);
  Flag_EcalDeadCellTriggerPrimitiveFilter_branch = tree->GetBranch("Flag_EcalDeadCellTriggerPrimitiveFilter");
  if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch) Flag_EcalDeadCellTriggerPrimitiveFilter_branch->SetAddress(&Flag_EcalDeadCellTriggerPrimitiveFilter_);
  Flag_HBHEIsoNoiseFilter_branch = tree->GetBranch("Flag_HBHEIsoNoiseFilter");
  if (Flag_HBHEIsoNoiseFilter_branch) Flag_HBHEIsoNoiseFilter_branch->SetAddress(&Flag_HBHEIsoNoiseFilter_);
  Flag_HBHENoiseFilter_branch = tree->GetBranch("Flag_HBHENoiseFilter");
  if (Flag_HBHENoiseFilter_branch) Flag_HBHENoiseFilter_branch->SetAddress(&Flag_HBHENoiseFilter_);
  Flag_badChargedCandidateFilter_branch = tree->GetBranch("Flag_badChargedCandidateFilter");
  if (Flag_badChargedCandidateFilter_branch) Flag_badChargedCandidateFilter_branch->SetAddress(&Flag_badChargedCandidateFilter_);
  Flag_badMuonFilter_branch = tree->GetBranch("Flag_badMuonFilter");
  if (Flag_badMuonFilter_branch) Flag_badMuonFilter_branch->SetAddress(&Flag_badMuonFilter_);
  Flag_badMuonFilterv2_branch = tree->GetBranch("Flag_badMuonFilterv2");
  if (Flag_badMuonFilterv2_branch) Flag_badMuonFilterv2_branch->SetAddress(&Flag_badMuonFilterv2_);
  Flag_badChargedCandidateFilterv2_branch = tree->GetBranch("Flag_badChargedCandidateFilterv2");
  if (Flag_badChargedCandidateFilterv2_branch) Flag_badChargedCandidateFilterv2_branch->SetAddress(&Flag_badChargedCandidateFilterv2_);
  Flag_eeBadScFilter_branch = tree->GetBranch("Flag_eeBadScFilter");
  if (Flag_eeBadScFilter_branch) Flag_eeBadScFilter_branch->SetAddress(&Flag_eeBadScFilter_);
  Flag_ecalBadCalibFilter_branch = tree->GetBranch("Flag_ecalBadCalibFilter");
  if (Flag_ecalBadCalibFilter_branch) Flag_ecalBadCalibFilter_branch->SetAddress(&Flag_ecalBadCalibFilter_);
  Flag_globalTightHalo2016_branch = tree->GetBranch("Flag_globalTightHalo2016");
  if (Flag_globalTightHalo2016_branch) Flag_globalTightHalo2016_branch->SetAddress(&Flag_globalTightHalo2016_);
  Flag_goodVertices_branch = tree->GetBranch("Flag_goodVertices");
  if (Flag_goodVertices_branch) Flag_goodVertices_branch->SetAddress(&Flag_goodVertices_);
  Flag_ecalLaserCorrFilter_branch = tree->GetBranch("Flag_ecalLaserCorrFilter");
  if (Flag_ecalLaserCorrFilter_branch) Flag_ecalLaserCorrFilter_branch->SetAddress(&Flag_ecalLaserCorrFilter_);
  Flag_hcalLaserEventFilter_branch = tree->GetBranch("Flag_hcalLaserEventFilter");
  if (Flag_hcalLaserEventFilter_branch) Flag_hcalLaserEventFilter_branch->SetAddress(&Flag_hcalLaserEventFilter_);
  Flag_trackingFailureFilter_branch = tree->GetBranch("Flag_trackingFailureFilter");
  if (Flag_trackingFailureFilter_branch) Flag_trackingFailureFilter_branch->SetAddress(&Flag_trackingFailureFilter_);
  Flag_CSCTightHaloFilter_branch = tree->GetBranch("Flag_CSCTightHaloFilter");
  if (Flag_CSCTightHaloFilter_branch) Flag_CSCTightHaloFilter_branch->SetAddress(&Flag_CSCTightHaloFilter_);
  Flag_CSCTightHalo2015Filter_branch = tree->GetBranch("Flag_CSCTightHalo2015Filter");
  if (Flag_CSCTightHalo2015Filter_branch) Flag_CSCTightHalo2015Filter_branch->SetAddress(&Flag_CSCTightHalo2015Filter_);
  Flag_badMuons_branch = tree->GetBranch("Flag_badMuons");
  if (Flag_badMuons_branch) Flag_badMuons_branch->SetAddress(&Flag_badMuons_);
  Flag_duplicateMuons_branch = tree->GetBranch("Flag_duplicateMuons");
  if (Flag_duplicateMuons_branch) Flag_duplicateMuons_branch->SetAddress(&Flag_duplicateMuons_);
  Flag_noBadMuons_branch = tree->GetBranch("Flag_noBadMuons");
  if (Flag_noBadMuons_branch) Flag_noBadMuons_branch->SetAddress(&Flag_noBadMuons_);
  fastsimfilt_branch = tree->GetBranch("fastsimfilt");
  if (fastsimfilt_branch) fastsimfilt_branch->SetAddress(&fastsimfilt_);
  nVlep_branch = tree->GetBranch("nVlep");
  if (nVlep_branch) nVlep_branch->SetAddress(&nVlep_);
  nTlep_branch = tree->GetBranch("nTlep");
  if (nTlep_branch) nTlep_branch->SetAddress(&nTlep_);
  nTlepSS_branch = tree->GetBranch("nTlepSS");
  if (nTlepSS_branch) nTlepSS_branch->SetAddress(&nTlepSS_);
  nLlep_branch = tree->GetBranch("nLlep");
  if (nLlep_branch) nLlep_branch->SetAddress(&nLlep_);
  nSFOS_branch = tree->GetBranch("nSFOS");
  if (nSFOS_branch) nSFOS_branch->SetAddress(&nSFOS_);
  nSFOSinZ_branch = tree->GetBranch("nSFOSinZ");
  if (nSFOSinZ_branch) nSFOSinZ_branch->SetAddress(&nSFOSinZ_);
  nj_branch = tree->GetBranch("nj");
  if (nj_branch) nj_branch->SetAddress(&nj_);
  nj_up_branch = tree->GetBranch("nj_up");
  if (nj_up_branch) nj_up_branch->SetAddress(&nj_up_);
  nj_dn_branch = tree->GetBranch("nj_dn");
  if (nj_dn_branch) nj_dn_branch->SetAddress(&nj_dn_);
  nj30_branch = tree->GetBranch("nj30");
  if (nj30_branch) nj30_branch->SetAddress(&nj30_);
  nj30_up_branch = tree->GetBranch("nj30_up");
  if (nj30_up_branch) nj30_up_branch->SetAddress(&nj30_up_);
  nj30_dn_branch = tree->GetBranch("nj30_dn");
  if (nj30_dn_branch) nj30_dn_branch->SetAddress(&nj30_dn_);
  nb_branch = tree->GetBranch("nb");
  if (nb_branch) nb_branch->SetAddress(&nb_);
  nb_up_branch = tree->GetBranch("nb_up");
  if (nb_up_branch) nb_up_branch->SetAddress(&nb_up_);
  nb_dn_branch = tree->GetBranch("nb_dn");
  if (nb_dn_branch) nb_dn_branch->SetAddress(&nb_dn_);
  Mjj_branch = tree->GetBranch("Mjj");
  if (Mjj_branch) Mjj_branch->SetAddress(&Mjj_);
  Mjj_up_branch = tree->GetBranch("Mjj_up");
  if (Mjj_up_branch) Mjj_up_branch->SetAddress(&Mjj_up_);
  Mjj_dn_branch = tree->GetBranch("Mjj_dn");
  if (Mjj_dn_branch) Mjj_dn_branch->SetAddress(&Mjj_dn_);
  DRjj_branch = tree->GetBranch("DRjj");
  if (DRjj_branch) DRjj_branch->SetAddress(&DRjj_);
  DRjj_up_branch = tree->GetBranch("DRjj_up");
  if (DRjj_up_branch) DRjj_up_branch->SetAddress(&DRjj_up_);
  DRjj_dn_branch = tree->GetBranch("DRjj_dn");
  if (DRjj_dn_branch) DRjj_dn_branch->SetAddress(&DRjj_dn_);
  MjjDR1_branch = tree->GetBranch("MjjDR1");
  if (MjjDR1_branch) MjjDR1_branch->SetAddress(&MjjDR1_);
  MjjDR1_up_branch = tree->GetBranch("MjjDR1_up");
  if (MjjDR1_up_branch) MjjDR1_up_branch->SetAddress(&MjjDR1_up_);
  MjjDR1_dn_branch = tree->GetBranch("MjjDR1_dn");
  if (MjjDR1_dn_branch) MjjDR1_dn_branch->SetAddress(&MjjDR1_dn_);
  DRjjDR1_branch = tree->GetBranch("DRjjDR1");
  if (DRjjDR1_branch) DRjjDR1_branch->SetAddress(&DRjjDR1_);
  DRjjDR1_up_branch = tree->GetBranch("DRjjDR1_up");
  if (DRjjDR1_up_branch) DRjjDR1_up_branch->SetAddress(&DRjjDR1_up_);
  DRjjDR1_dn_branch = tree->GetBranch("DRjjDR1_dn");
  if (DRjjDR1_dn_branch) DRjjDR1_dn_branch->SetAddress(&DRjjDR1_dn_);
  MjjVBF_branch = tree->GetBranch("MjjVBF");
  if (MjjVBF_branch) MjjVBF_branch->SetAddress(&MjjVBF_);
  MjjVBF_up_branch = tree->GetBranch("MjjVBF_up");
  if (MjjVBF_up_branch) MjjVBF_up_branch->SetAddress(&MjjVBF_up_);
  MjjVBF_dn_branch = tree->GetBranch("MjjVBF_dn");
  if (MjjVBF_dn_branch) MjjVBF_dn_branch->SetAddress(&MjjVBF_dn_);
  DetajjVBF_branch = tree->GetBranch("DetajjVBF");
  if (DetajjVBF_branch) DetajjVBF_branch->SetAddress(&DetajjVBF_);
  DetajjVBF_up_branch = tree->GetBranch("DetajjVBF_up");
  if (DetajjVBF_up_branch) DetajjVBF_up_branch->SetAddress(&DetajjVBF_up_);
  DetajjVBF_dn_branch = tree->GetBranch("DetajjVBF_dn");
  if (DetajjVBF_dn_branch) DetajjVBF_dn_branch->SetAddress(&DetajjVBF_dn_);
  MjjL_branch = tree->GetBranch("MjjL");
  if (MjjL_branch) MjjL_branch->SetAddress(&MjjL_);
  MjjL_up_branch = tree->GetBranch("MjjL_up");
  if (MjjL_up_branch) MjjL_up_branch->SetAddress(&MjjL_up_);
  MjjL_dn_branch = tree->GetBranch("MjjL_dn");
  if (MjjL_dn_branch) MjjL_dn_branch->SetAddress(&MjjL_dn_);
  DetajjL_branch = tree->GetBranch("DetajjL");
  if (DetajjL_branch) DetajjL_branch->SetAddress(&DetajjL_);
  DetajjL_up_branch = tree->GetBranch("DetajjL_up");
  if (DetajjL_up_branch) DetajjL_up_branch->SetAddress(&DetajjL_up_);
  DetajjL_dn_branch = tree->GetBranch("DetajjL_dn");
  if (DetajjL_dn_branch) DetajjL_dn_branch->SetAddress(&DetajjL_dn_);
  MllSS_branch = tree->GetBranch("MllSS");
  if (MllSS_branch) MllSS_branch->SetAddress(&MllSS_);
  MeeSS_branch = tree->GetBranch("MeeSS");
  if (MeeSS_branch) MeeSS_branch->SetAddress(&MeeSS_);
  Mll3L_branch = tree->GetBranch("Mll3L");
  if (Mll3L_branch) Mll3L_branch->SetAddress(&Mll3L_);
  Mee3L_branch = tree->GetBranch("Mee3L");
  if (Mee3L_branch) Mee3L_branch->SetAddress(&Mee3L_);
  Mll3L1_branch = tree->GetBranch("Mll3L1");
  if (Mll3L1_branch) Mll3L1_branch->SetAddress(&Mll3L1_);
  M3l_branch = tree->GetBranch("M3l");
  if (M3l_branch) M3l_branch->SetAddress(&M3l_);
  Pt3l_branch = tree->GetBranch("Pt3l");
  if (Pt3l_branch) Pt3l_branch->SetAddress(&Pt3l_);
  M01_branch = tree->GetBranch("M01");
  if (M01_branch) M01_branch->SetAddress(&M01_);
  M02_branch = tree->GetBranch("M02");
  if (M02_branch) M02_branch->SetAddress(&M02_);
  M12_branch = tree->GetBranch("M12");
  if (M12_branch) M12_branch->SetAddress(&M12_);
  isSFOS01_branch = tree->GetBranch("isSFOS01");
  if (isSFOS01_branch) isSFOS01_branch->SetAddress(&isSFOS01_);
  isSFOS02_branch = tree->GetBranch("isSFOS02");
  if (isSFOS02_branch) isSFOS02_branch->SetAddress(&isSFOS02_);
  isSFOS12_branch = tree->GetBranch("isSFOS12");
  if (isSFOS12_branch) isSFOS12_branch->SetAddress(&isSFOS12_);
  DPhi3lMET_branch = tree->GetBranch("DPhi3lMET");
  if (DPhi3lMET_branch) DPhi3lMET_branch->SetAddress(&DPhi3lMET_);
  DPhi3lMET_up_branch = tree->GetBranch("DPhi3lMET_up");
  if (DPhi3lMET_up_branch) DPhi3lMET_up_branch->SetAddress(&DPhi3lMET_up_);
  DPhi3lMET_dn_branch = tree->GetBranch("DPhi3lMET_dn");
  if (DPhi3lMET_dn_branch) DPhi3lMET_dn_branch->SetAddress(&DPhi3lMET_dn_);
  DPhi3lMET_gen_branch = tree->GetBranch("DPhi3lMET_gen");
  if (DPhi3lMET_gen_branch) DPhi3lMET_gen_branch->SetAddress(&DPhi3lMET_gen_);
  MTmax_branch = tree->GetBranch("MTmax");
  if (MTmax_branch) MTmax_branch->SetAddress(&MTmax_);
  MTmax_up_branch = tree->GetBranch("MTmax_up");
  if (MTmax_up_branch) MTmax_up_branch->SetAddress(&MTmax_up_);
  MTmax_dn_branch = tree->GetBranch("MTmax_dn");
  if (MTmax_dn_branch) MTmax_dn_branch->SetAddress(&MTmax_dn_);
  MTmax_gen_branch = tree->GetBranch("MTmax_gen");
  if (MTmax_gen_branch) MTmax_gen_branch->SetAddress(&MTmax_gen_);
  MTmin_branch = tree->GetBranch("MTmin");
  if (MTmin_branch) MTmin_branch->SetAddress(&MTmin_);
  MTmin_up_branch = tree->GetBranch("MTmin_up");
  if (MTmin_up_branch) MTmin_up_branch->SetAddress(&MTmin_up_);
  MTmin_dn_branch = tree->GetBranch("MTmin_dn");
  if (MTmin_dn_branch) MTmin_dn_branch->SetAddress(&MTmin_dn_);
  MTmin_gen_branch = tree->GetBranch("MTmin_gen");
  if (MTmin_gen_branch) MTmin_gen_branch->SetAddress(&MTmin_gen_);
  MT3rd_branch = tree->GetBranch("MT3rd");
  if (MT3rd_branch) MT3rd_branch->SetAddress(&MT3rd_);
  MT3rd_up_branch = tree->GetBranch("MT3rd_up");
  if (MT3rd_up_branch) MT3rd_up_branch->SetAddress(&MT3rd_up_);
  MT3rd_dn_branch = tree->GetBranch("MT3rd_dn");
  if (MT3rd_dn_branch) MT3rd_dn_branch->SetAddress(&MT3rd_dn_);
  MT3rd_gen_branch = tree->GetBranch("MT3rd_gen");
  if (MT3rd_gen_branch) MT3rd_gen_branch->SetAddress(&MT3rd_gen_);
  MTmax3L_branch = tree->GetBranch("MTmax3L");
  if (MTmax3L_branch) MTmax3L_branch->SetAddress(&MTmax3L_);
  MTmax3L_up_branch = tree->GetBranch("MTmax3L_up");
  if (MTmax3L_up_branch) MTmax3L_up_branch->SetAddress(&MTmax3L_up_);
  MTmax3L_dn_branch = tree->GetBranch("MTmax3L_dn");
  if (MTmax3L_dn_branch) MTmax3L_dn_branch->SetAddress(&MTmax3L_dn_);
  MTmax3L_gen_branch = tree->GetBranch("MTmax3L_gen");
  if (MTmax3L_gen_branch) MTmax3L_gen_branch->SetAddress(&MTmax3L_gen_);
  passSSee_branch = tree->GetBranch("passSSee");
  if (passSSee_branch) passSSee_branch->SetAddress(&passSSee_);
  passSSem_branch = tree->GetBranch("passSSem");
  if (passSSem_branch) passSSem_branch->SetAddress(&passSSem_);
  passSSmm_branch = tree->GetBranch("passSSmm");
  if (passSSmm_branch) passSSmm_branch->SetAddress(&passSSmm_);
  lep_idx0_SS_branch = tree->GetBranch("lep_idx0_SS");
  if (lep_idx0_SS_branch) lep_idx0_SS_branch->SetAddress(&lep_idx0_SS_);
  lep_idx1_SS_branch = tree->GetBranch("lep_idx1_SS");
  if (lep_idx1_SS_branch) lep_idx1_SS_branch->SetAddress(&lep_idx1_SS_);
  bkgtype_branch = tree->GetBranch("bkgtype");
  if (bkgtype_branch) bkgtype_branch->SetAddress(&bkgtype_);
  vetophoton_branch = tree->GetBranch("vetophoton");
  if (vetophoton_branch) vetophoton_branch->SetAddress(&vetophoton_);
  purewgt_branch = tree->GetBranch("purewgt");
  if (purewgt_branch) purewgt_branch->SetAddress(&purewgt_);
  purewgt_up_branch = tree->GetBranch("purewgt_up");
  if (purewgt_up_branch) purewgt_up_branch->SetAddress(&purewgt_up_);
  purewgt_dn_branch = tree->GetBranch("purewgt_dn");
  if (purewgt_dn_branch) purewgt_dn_branch->SetAddress(&purewgt_dn_);
  ffwgt_branch = tree->GetBranch("ffwgt");
  if (ffwgt_branch) ffwgt_branch->SetAddress(&ffwgt_);
  ffwgt_up_branch = tree->GetBranch("ffwgt_up");
  if (ffwgt_up_branch) ffwgt_up_branch->SetAddress(&ffwgt_up_);
  ffwgt_dn_branch = tree->GetBranch("ffwgt_dn");
  if (ffwgt_dn_branch) ffwgt_dn_branch->SetAddress(&ffwgt_dn_);
  ffwgt_el_up_branch = tree->GetBranch("ffwgt_el_up");
  if (ffwgt_el_up_branch) ffwgt_el_up_branch->SetAddress(&ffwgt_el_up_);
  ffwgt_el_dn_branch = tree->GetBranch("ffwgt_el_dn");
  if (ffwgt_el_dn_branch) ffwgt_el_dn_branch->SetAddress(&ffwgt_el_dn_);
  ffwgt_mu_up_branch = tree->GetBranch("ffwgt_mu_up");
  if (ffwgt_mu_up_branch) ffwgt_mu_up_branch->SetAddress(&ffwgt_mu_up_);
  ffwgt_mu_dn_branch = tree->GetBranch("ffwgt_mu_dn");
  if (ffwgt_mu_dn_branch) ffwgt_mu_dn_branch->SetAddress(&ffwgt_mu_dn_);
  ffwgt_closure_up_branch = tree->GetBranch("ffwgt_closure_up");
  if (ffwgt_closure_up_branch) ffwgt_closure_up_branch->SetAddress(&ffwgt_closure_up_);
  ffwgt_closure_dn_branch = tree->GetBranch("ffwgt_closure_dn");
  if (ffwgt_closure_dn_branch) ffwgt_closure_dn_branch->SetAddress(&ffwgt_closure_dn_);
  ffwgt_closure_el_up_branch = tree->GetBranch("ffwgt_closure_el_up");
  if (ffwgt_closure_el_up_branch) ffwgt_closure_el_up_branch->SetAddress(&ffwgt_closure_el_up_);
  ffwgt_closure_el_dn_branch = tree->GetBranch("ffwgt_closure_el_dn");
  if (ffwgt_closure_el_dn_branch) ffwgt_closure_el_dn_branch->SetAddress(&ffwgt_closure_el_dn_);
  ffwgt_closure_mu_up_branch = tree->GetBranch("ffwgt_closure_mu_up");
  if (ffwgt_closure_mu_up_branch) ffwgt_closure_mu_up_branch->SetAddress(&ffwgt_closure_mu_up_);
  ffwgt_closure_mu_dn_branch = tree->GetBranch("ffwgt_closure_mu_dn");
  if (ffwgt_closure_mu_dn_branch) ffwgt_closure_mu_dn_branch->SetAddress(&ffwgt_closure_mu_dn_);
  ffwgt_full_up_branch = tree->GetBranch("ffwgt_full_up");
  if (ffwgt_full_up_branch) ffwgt_full_up_branch->SetAddress(&ffwgt_full_up_);
  ffwgt_full_dn_branch = tree->GetBranch("ffwgt_full_dn");
  if (ffwgt_full_dn_branch) ffwgt_full_dn_branch->SetAddress(&ffwgt_full_dn_);
  ffwgtqcd_branch = tree->GetBranch("ffwgtqcd");
  if (ffwgtqcd_branch) ffwgtqcd_branch->SetAddress(&ffwgtqcd_);
  ffwgtqcd_up_branch = tree->GetBranch("ffwgtqcd_up");
  if (ffwgtqcd_up_branch) ffwgtqcd_up_branch->SetAddress(&ffwgtqcd_up_);
  ffwgtqcd_dn_branch = tree->GetBranch("ffwgtqcd_dn");
  if (ffwgtqcd_dn_branch) ffwgtqcd_dn_branch->SetAddress(&ffwgtqcd_dn_);
  lepsf_branch = tree->GetBranch("lepsf");
  if (lepsf_branch) lepsf_branch->SetAddress(&lepsf_);
  lepsf_up_branch = tree->GetBranch("lepsf_up");
  if (lepsf_up_branch) lepsf_up_branch->SetAddress(&lepsf_up_);
  lepsf_dn_branch = tree->GetBranch("lepsf_dn");
  if (lepsf_dn_branch) lepsf_dn_branch->SetAddress(&lepsf_dn_);
  trigeff_branch = tree->GetBranch("trigeff");
  if (trigeff_branch) trigeff_branch->SetAddress(&trigeff_);
  trigeff_up_branch = tree->GetBranch("trigeff_up");
  if (trigeff_up_branch) trigeff_up_branch->SetAddress(&trigeff_up_);
  trigeff_dn_branch = tree->GetBranch("trigeff_dn");
  if (trigeff_dn_branch) trigeff_dn_branch->SetAddress(&trigeff_dn_);
  trigsf_branch = tree->GetBranch("trigsf");
  if (trigsf_branch) trigsf_branch->SetAddress(&trigsf_);
  trigsf_up_branch = tree->GetBranch("trigsf_up");
  if (trigsf_up_branch) trigsf_up_branch->SetAddress(&trigsf_up_);
  trigsf_dn_branch = tree->GetBranch("trigsf_dn");
  if (trigsf_dn_branch) trigsf_dn_branch->SetAddress(&trigsf_dn_);
  musmear_sf_branch = tree->GetBranch("musmear_sf");
  if (musmear_sf_branch) musmear_sf_branch->SetAddress(&musmear_sf_);

  tree->SetMakeClass(0);
}

void wwwtree::GetEntry(unsigned int idx) {
  // this only marks branches as not loaded, saving a lot of time
  index = idx;
  run_isLoaded = false;
  lumi_isLoaded = false;
  evt_isLoaded = false;
  isData_isLoaded = false;
  evt_scale1fb_isLoaded = false;
  xsec_br_isLoaded = false;
  evt_passgoodrunlist_isLoaded = false;
  CMS4path_isLoaded = false;
  CMS4index_isLoaded = false;
  weight_fr_r1_f1_isLoaded = false;
  weight_fr_r1_f2_isLoaded = false;
  weight_fr_r1_f0p5_isLoaded = false;
  weight_fr_r2_f1_isLoaded = false;
  weight_fr_r2_f2_isLoaded = false;
  weight_fr_r2_f0p5_isLoaded = false;
  weight_fr_r0p5_f1_isLoaded = false;
  weight_fr_r0p5_f2_isLoaded = false;
  weight_fr_r0p5_f0p5_isLoaded = false;
  weight_pdf_up_isLoaded = false;
  weight_pdf_down_isLoaded = false;
  weight_alphas_down_isLoaded = false;
  weight_alphas_up_isLoaded = false;
  weight_isr_isLoaded = false;
  weight_isr_up_isLoaded = false;
  weight_isr_down_isLoaded = false;
  HLT_DoubleMu_isLoaded = false;
  HLT_DoubleEl_isLoaded = false;
  HLT_DoubleEl_DZ_isLoaded = false;
  HLT_DoubleEl_DZ_2_isLoaded = false;
  HLT_MuEG_isLoaded = false;
  HLT_SingleIsoEl8_isLoaded = false;
  HLT_SingleIsoEl17_isLoaded = false;
  HLT_SingleIsoEl23_isLoaded = false;
  HLT_SingleIsoMu8_isLoaded = false;
  HLT_SingleIsoMu17_isLoaded = false;
  HLT_PFMET140_PFMHT140_IDTight_isLoaded = false;
  mc_HLT_DoubleMu_isLoaded = false;
  mc_HLT_DoubleEl_isLoaded = false;
  mc_HLT_DoubleEl_DZ_isLoaded = false;
  mc_HLT_DoubleEl_DZ_2_isLoaded = false;
  mc_HLT_MuEG_isLoaded = false;
  mc_HLT_SingleIsoEl8_isLoaded = false;
  mc_HLT_SingleIsoEl17_isLoaded = false;
  mc_HLT_SingleIsoEl23_isLoaded = false;
  mc_HLT_SingleIsoMu8_isLoaded = false;
  mc_HLT_SingleIsoMu17_isLoaded = false;
  mc_HLT_PFMET140_PFMHT140_IDTight_isLoaded = false;
  pass_duplicate_ee_em_mm_isLoaded = false;
  pass_duplicate_mm_em_ee_isLoaded = false;
  is2016_isLoaded = false;
  is2017_isLoaded = false;
  HLT_MuEG_2016_isLoaded = false;
  mc_HLT_MuEG_2016_isLoaded = false;
  pass_duplicate_ee_em2016_mm_isLoaded = false;
  pass_duplicate_mm_em2016_ee_isLoaded = false;
  passTrigger_isLoaded = false;
  lep_p4_isLoaded = false;
  lep_pt_isLoaded = false;
  lep_eta_isLoaded = false;
  lep_phi_isLoaded = false;
  lep_coneCorrPt_isLoaded = false;
  lep_ip3d_isLoaded = false;
  lep_ip3derr_isLoaded = false;
  lep_isTriggerSafe_v1_isLoaded = false;
  lep_lostHits_isLoaded = false;
  lep_convVeto_isLoaded = false;
  lep_motherIdSS_isLoaded = false;
  lep_pass_VVV_cutbased_3l_fo_isLoaded = false;
  lep_pass_VVV_cutbased_3l_tight_isLoaded = false;
  lep_pass_VVV_cutbased_fo_isLoaded = false;
  lep_pass_VVV_cutbased_tight_isLoaded = false;
  lep_pass_VVV_cutbased_veto_isLoaded = false;
  lep_pass_VVV_cutbased_fo_noiso_isLoaded = false;
  lep_pass_VVV_cutbased_tight_noiso_isLoaded = false;
  lep_pass_VVV_cutbased_veto_noiso_isLoaded = false;
  lep_pass_POG_veto_isLoaded = false;
  lep_pass_POG_loose_isLoaded = false;
  lep_pass_POG_medium_isLoaded = false;
  lep_pass_POG_tight_isLoaded = false;
  lep_pdgId_isLoaded = false;
  lep_dxy_isLoaded = false;
  lep_dz_isLoaded = false;
  lep_pterr_isLoaded = false;
  lep_relIso04DB_isLoaded = false;
  lep_relIso03EA_isLoaded = false;
  lep_relIso03EALep_isLoaded = false;
  lep_relIso03EAv2_isLoaded = false;
  lep_relIso04EAv2_isLoaded = false;
  lep_relIso03EAv2Lep_isLoaded = false;
  lep_tightCharge_isLoaded = false;
  lep_trk_pt_isLoaded = false;
  lep_charge_isLoaded = false;
  lep_etaSC_isLoaded = false;
  lep_MVA_isLoaded = false;
  lep_isMediumPOG_isLoaded = false;
  lep_isTightPOG_isLoaded = false;
  lep_isFromW_isLoaded = false;
  lep_isFromZ_isLoaded = false;
  lep_isFromB_isLoaded = false;
  lep_isFromC_isLoaded = false;
  lep_isFromL_isLoaded = false;
  lep_isFromLF_isLoaded = false;
  lep_genPart_index_isLoaded = false;
  lep_r9_isLoaded = false;
  lep_nlayers_isLoaded = false;
  el_pt_isLoaded = false;
  el_eta_isLoaded = false;
  el_phi_isLoaded = false;
  el_relIso03EA_isLoaded = false;
  el_relIso03EALep_isLoaded = false;
  el_ip3d_isLoaded = false;
  mu_pt_isLoaded = false;
  mu_eta_isLoaded = false;
  mu_phi_isLoaded = false;
  mu_relIso04DB_isLoaded = false;
  mu_relIso03EA_isLoaded = false;
  mu_relIso03EALep_isLoaded = false;
  mu_ip3d_isLoaded = false;
  lbnt_pt_isLoaded = false;
  lbnt_coneCorrPt_isLoaded = false;
  lbnt_abseta_isLoaded = false;
  lbnt_pdgId_isLoaded = false;
  lbnt_el_pt_isLoaded = false;
  lbnt_el_coneCorrPt_isLoaded = false;
  lbnt_el_abseta_isLoaded = false;
  lbnt_mu_pt_isLoaded = false;
  lbnt_mu_coneCorrPt_isLoaded = false;
  lbnt_mu_abseta_isLoaded = false;
  jets_p4_isLoaded = false;
  jets_up_p4_isLoaded = false;
  jets_dn_p4_isLoaded = false;
  jets_csv_isLoaded = false;
  jets_up_csv_isLoaded = false;
  jets_dn_csv_isLoaded = false;
  ak8jets_p4_isLoaded = false;
  ak8jets_softdropMass_isLoaded = false;
  ak8jets_prunedMass_isLoaded = false;
  ak8jets_trimmedMass_isLoaded = false;
  ak8jets_mass_isLoaded = false;
  ak8jets_nJettinessTau1_isLoaded = false;
  ak8jets_nJettinessTau2_isLoaded = false;
  ak8jets_softdropPuppiSubjet1_isLoaded = false;
  ak8jets_softdropPuppiSubjet2_isLoaded = false;
  ak8jets_puppi_softdropMass_isLoaded = false;
  ak8jets_puppi_nJettinessTau1_isLoaded = false;
  ak8jets_puppi_nJettinessTau2_isLoaded = false;
  ak8jets_puppi_eta_isLoaded = false;
  ak8jets_puppi_phi_isLoaded = false;
  ak8jets_puppi_pt_isLoaded = false;
  ak8jets_puppi_mass_isLoaded = false;
  met_pt_isLoaded = false;
  met_phi_isLoaded = false;
  met_up_pt_isLoaded = false;
  met_up_phi_isLoaded = false;
  met_dn_pt_isLoaded = false;
  met_dn_phi_isLoaded = false;
  met_gen_pt_isLoaded = false;
  met_gen_phi_isLoaded = false;
  firstgoodvertex_isLoaded = false;
  nTrueInt_isLoaded = false;
  nVert_isLoaded = false;
  nisoTrack_mt2_cleaned_VVV_cutbased_veto_isLoaded = false;
  weight_btagsf_isLoaded = false;
  weight_btagsf_heavy_DN_isLoaded = false;
  weight_btagsf_heavy_UP_isLoaded = false;
  weight_btagsf_light_DN_isLoaded = false;
  weight_btagsf_light_UP_isLoaded = false;
  gen_ht_isLoaded = false;
  genPart_p4_isLoaded = false;
  genPart_motherId_isLoaded = false;
  genPart_pdgId_isLoaded = false;
  genPart_charge_isLoaded = false;
  genPart_status_isLoaded = false;
  ngenLep_isLoaded = false;
  ngenLepFromTau_isLoaded = false;
  Flag_AllEventFilters_isLoaded = false;
  Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded = false;
  Flag_HBHEIsoNoiseFilter_isLoaded = false;
  Flag_HBHENoiseFilter_isLoaded = false;
  Flag_badChargedCandidateFilter_isLoaded = false;
  Flag_badMuonFilter_isLoaded = false;
  Flag_badMuonFilterv2_isLoaded = false;
  Flag_badChargedCandidateFilterv2_isLoaded = false;
  Flag_eeBadScFilter_isLoaded = false;
  Flag_ecalBadCalibFilter_isLoaded = false;
  Flag_globalTightHalo2016_isLoaded = false;
  Flag_goodVertices_isLoaded = false;
  Flag_ecalLaserCorrFilter_isLoaded = false;
  Flag_hcalLaserEventFilter_isLoaded = false;
  Flag_trackingFailureFilter_isLoaded = false;
  Flag_CSCTightHaloFilter_isLoaded = false;
  Flag_CSCTightHalo2015Filter_isLoaded = false;
  Flag_badMuons_isLoaded = false;
  Flag_duplicateMuons_isLoaded = false;
  Flag_noBadMuons_isLoaded = false;
  fastsimfilt_isLoaded = false;
  nVlep_isLoaded = false;
  nTlep_isLoaded = false;
  nTlepSS_isLoaded = false;
  nLlep_isLoaded = false;
  nSFOS_isLoaded = false;
  nSFOSinZ_isLoaded = false;
  nj_isLoaded = false;
  nj_up_isLoaded = false;
  nj_dn_isLoaded = false;
  nj30_isLoaded = false;
  nj30_up_isLoaded = false;
  nj30_dn_isLoaded = false;
  nb_isLoaded = false;
  nb_up_isLoaded = false;
  nb_dn_isLoaded = false;
  Mjj_isLoaded = false;
  Mjj_up_isLoaded = false;
  Mjj_dn_isLoaded = false;
  DRjj_isLoaded = false;
  DRjj_up_isLoaded = false;
  DRjj_dn_isLoaded = false;
  jet0_wtag_p4_isLoaded = false;
  jet0_wtag_p4_up_isLoaded = false;
  jet0_wtag_p4_dn_isLoaded = false;
  jet1_wtag_p4_isLoaded = false;
  jet1_wtag_p4_up_isLoaded = false;
  jet1_wtag_p4_dn_isLoaded = false;
  MjjDR1_isLoaded = false;
  MjjDR1_up_isLoaded = false;
  MjjDR1_dn_isLoaded = false;
  DRjjDR1_isLoaded = false;
  DRjjDR1_up_isLoaded = false;
  DRjjDR1_dn_isLoaded = false;
  jet0_wtag_p4_DR1_isLoaded = false;
  jet0_wtag_p4_DR1_up_isLoaded = false;
  jet0_wtag_p4_DR1_dn_isLoaded = false;
  jet1_wtag_p4_DR1_isLoaded = false;
  jet1_wtag_p4_DR1_up_isLoaded = false;
  jet1_wtag_p4_DR1_dn_isLoaded = false;
  MjjVBF_isLoaded = false;
  MjjVBF_up_isLoaded = false;
  MjjVBF_dn_isLoaded = false;
  DetajjVBF_isLoaded = false;
  DetajjVBF_up_isLoaded = false;
  DetajjVBF_dn_isLoaded = false;
  MjjL_isLoaded = false;
  MjjL_up_isLoaded = false;
  MjjL_dn_isLoaded = false;
  DetajjL_isLoaded = false;
  DetajjL_up_isLoaded = false;
  DetajjL_dn_isLoaded = false;
  MllSS_isLoaded = false;
  MeeSS_isLoaded = false;
  Mll3L_isLoaded = false;
  Mee3L_isLoaded = false;
  Mll3L1_isLoaded = false;
  M3l_isLoaded = false;
  Pt3l_isLoaded = false;
  M01_isLoaded = false;
  M02_isLoaded = false;
  M12_isLoaded = false;
  isSFOS01_isLoaded = false;
  isSFOS02_isLoaded = false;
  isSFOS12_isLoaded = false;
  DPhi3lMET_isLoaded = false;
  DPhi3lMET_up_isLoaded = false;
  DPhi3lMET_dn_isLoaded = false;
  DPhi3lMET_gen_isLoaded = false;
  MTmax_isLoaded = false;
  MTmax_up_isLoaded = false;
  MTmax_dn_isLoaded = false;
  MTmax_gen_isLoaded = false;
  MTmin_isLoaded = false;
  MTmin_up_isLoaded = false;
  MTmin_dn_isLoaded = false;
  MTmin_gen_isLoaded = false;
  MT3rd_isLoaded = false;
  MT3rd_up_isLoaded = false;
  MT3rd_dn_isLoaded = false;
  MT3rd_gen_isLoaded = false;
  MTmax3L_isLoaded = false;
  MTmax3L_up_isLoaded = false;
  MTmax3L_dn_isLoaded = false;
  MTmax3L_gen_isLoaded = false;
  passSSee_isLoaded = false;
  passSSem_isLoaded = false;
  passSSmm_isLoaded = false;
  lep_idx0_SS_isLoaded = false;
  lep_idx1_SS_isLoaded = false;
  bkgtype_isLoaded = false;
  vetophoton_isLoaded = false;
  purewgt_isLoaded = false;
  purewgt_up_isLoaded = false;
  purewgt_dn_isLoaded = false;
  ffwgt_isLoaded = false;
  ffwgt_up_isLoaded = false;
  ffwgt_dn_isLoaded = false;
  ffwgt_el_up_isLoaded = false;
  ffwgt_el_dn_isLoaded = false;
  ffwgt_mu_up_isLoaded = false;
  ffwgt_mu_dn_isLoaded = false;
  ffwgt_closure_up_isLoaded = false;
  ffwgt_closure_dn_isLoaded = false;
  ffwgt_closure_el_up_isLoaded = false;
  ffwgt_closure_el_dn_isLoaded = false;
  ffwgt_closure_mu_up_isLoaded = false;
  ffwgt_closure_mu_dn_isLoaded = false;
  ffwgt_full_up_isLoaded = false;
  ffwgt_full_dn_isLoaded = false;
  ffwgtqcd_isLoaded = false;
  ffwgtqcd_up_isLoaded = false;
  ffwgtqcd_dn_isLoaded = false;
  lepsf_isLoaded = false;
  lepsf_up_isLoaded = false;
  lepsf_dn_isLoaded = false;
  trigeff_isLoaded = false;
  trigeff_up_isLoaded = false;
  trigeff_dn_isLoaded = false;
  trigsf_isLoaded = false;
  trigsf_up_isLoaded = false;
  trigsf_dn_isLoaded = false;
  musmear_sf_isLoaded = false;
}

void wwwtree::LoadAllBranches() {
  // load all branches
  if (run_branch != 0) run();
  if (lumi_branch != 0) lumi();
  if (evt_branch != 0) evt();
  if (isData_branch != 0) isData();
  if (evt_scale1fb_branch != 0) evt_scale1fb();
  if (xsec_br_branch != 0) xsec_br();
  if (evt_passgoodrunlist_branch != 0) evt_passgoodrunlist();
  if (CMS4path_branch != 0) CMS4path();
  if (CMS4index_branch != 0) CMS4index();
  if (weight_fr_r1_f1_branch != 0) weight_fr_r1_f1();
  if (weight_fr_r1_f2_branch != 0) weight_fr_r1_f2();
  if (weight_fr_r1_f0p5_branch != 0) weight_fr_r1_f0p5();
  if (weight_fr_r2_f1_branch != 0) weight_fr_r2_f1();
  if (weight_fr_r2_f2_branch != 0) weight_fr_r2_f2();
  if (weight_fr_r2_f0p5_branch != 0) weight_fr_r2_f0p5();
  if (weight_fr_r0p5_f1_branch != 0) weight_fr_r0p5_f1();
  if (weight_fr_r0p5_f2_branch != 0) weight_fr_r0p5_f2();
  if (weight_fr_r0p5_f0p5_branch != 0) weight_fr_r0p5_f0p5();
  if (weight_pdf_up_branch != 0) weight_pdf_up();
  if (weight_pdf_down_branch != 0) weight_pdf_down();
  if (weight_alphas_down_branch != 0) weight_alphas_down();
  if (weight_alphas_up_branch != 0) weight_alphas_up();
  if (weight_isr_branch != 0) weight_isr();
  if (weight_isr_up_branch != 0) weight_isr_up();
  if (weight_isr_down_branch != 0) weight_isr_down();
  if (HLT_DoubleMu_branch != 0) HLT_DoubleMu();
  if (HLT_DoubleEl_branch != 0) HLT_DoubleEl();
  if (HLT_DoubleEl_DZ_branch != 0) HLT_DoubleEl_DZ();
  if (HLT_DoubleEl_DZ_2_branch != 0) HLT_DoubleEl_DZ_2();
  if (HLT_MuEG_branch != 0) HLT_MuEG();
  if (HLT_SingleIsoEl8_branch != 0) HLT_SingleIsoEl8();
  if (HLT_SingleIsoEl17_branch != 0) HLT_SingleIsoEl17();
  if (HLT_SingleIsoEl23_branch != 0) HLT_SingleIsoEl23();
  if (HLT_SingleIsoMu8_branch != 0) HLT_SingleIsoMu8();
  if (HLT_SingleIsoMu17_branch != 0) HLT_SingleIsoMu17();
  if (HLT_PFMET140_PFMHT140_IDTight_branch != 0) HLT_PFMET140_PFMHT140_IDTight();
  if (mc_HLT_DoubleMu_branch != 0) mc_HLT_DoubleMu();
  if (mc_HLT_DoubleEl_branch != 0) mc_HLT_DoubleEl();
  if (mc_HLT_DoubleEl_DZ_branch != 0) mc_HLT_DoubleEl_DZ();
  if (mc_HLT_DoubleEl_DZ_2_branch != 0) mc_HLT_DoubleEl_DZ_2();
  if (mc_HLT_MuEG_branch != 0) mc_HLT_MuEG();
  if (mc_HLT_SingleIsoEl8_branch != 0) mc_HLT_SingleIsoEl8();
  if (mc_HLT_SingleIsoEl17_branch != 0) mc_HLT_SingleIsoEl17();
  if (mc_HLT_SingleIsoEl23_branch != 0) mc_HLT_SingleIsoEl23();
  if (mc_HLT_SingleIsoMu8_branch != 0) mc_HLT_SingleIsoMu8();
  if (mc_HLT_SingleIsoMu17_branch != 0) mc_HLT_SingleIsoMu17();
  if (mc_HLT_PFMET140_PFMHT140_IDTight_branch != 0) mc_HLT_PFMET140_PFMHT140_IDTight();
  if (pass_duplicate_ee_em_mm_branch != 0) pass_duplicate_ee_em_mm();
  if (pass_duplicate_mm_em_ee_branch != 0) pass_duplicate_mm_em_ee();
  if (is2016_branch != 0) is2016();
  if (is2017_branch != 0) is2017();
  if (HLT_MuEG_2016_branch != 0) HLT_MuEG_2016();
  if (mc_HLT_MuEG_2016_branch != 0) mc_HLT_MuEG_2016();
  if (pass_duplicate_ee_em2016_mm_branch != 0) pass_duplicate_ee_em2016_mm();
  if (pass_duplicate_mm_em2016_ee_branch != 0) pass_duplicate_mm_em2016_ee();
  if (passTrigger_branch != 0) passTrigger();
  if (lep_p4_branch != 0) lep_p4();
  if (lep_pt_branch != 0) lep_pt();
  if (lep_eta_branch != 0) lep_eta();
  if (lep_phi_branch != 0) lep_phi();
  if (lep_coneCorrPt_branch != 0) lep_coneCorrPt();
  if (lep_ip3d_branch != 0) lep_ip3d();
  if (lep_ip3derr_branch != 0) lep_ip3derr();
  if (lep_isTriggerSafe_v1_branch != 0) lep_isTriggerSafe_v1();
  if (lep_lostHits_branch != 0) lep_lostHits();
  if (lep_convVeto_branch != 0) lep_convVeto();
  if (lep_motherIdSS_branch != 0) lep_motherIdSS();
  if (lep_pass_VVV_cutbased_3l_fo_branch != 0) lep_pass_VVV_cutbased_3l_fo();
  if (lep_pass_VVV_cutbased_3l_tight_branch != 0) lep_pass_VVV_cutbased_3l_tight();
  if (lep_pass_VVV_cutbased_fo_branch != 0) lep_pass_VVV_cutbased_fo();
  if (lep_pass_VVV_cutbased_tight_branch != 0) lep_pass_VVV_cutbased_tight();
  if (lep_pass_VVV_cutbased_veto_branch != 0) lep_pass_VVV_cutbased_veto();
  if (lep_pass_VVV_cutbased_fo_noiso_branch != 0) lep_pass_VVV_cutbased_fo_noiso();
  if (lep_pass_VVV_cutbased_tight_noiso_branch != 0) lep_pass_VVV_cutbased_tight_noiso();
  if (lep_pass_VVV_cutbased_veto_noiso_branch != 0) lep_pass_VVV_cutbased_veto_noiso();
  if (lep_pass_POG_veto_branch != 0) lep_pass_POG_veto();
  if (lep_pass_POG_loose_branch != 0) lep_pass_POG_loose();
  if (lep_pass_POG_medium_branch != 0) lep_pass_POG_medium();
  if (lep_pass_POG_tight_branch != 0) lep_pass_POG_tight();
  if (lep_pdgId_branch != 0) lep_pdgId();
  if (lep_dxy_branch != 0) lep_dxy();
  if (lep_dz_branch != 0) lep_dz();
  if (lep_pterr_branch != 0) lep_pterr();
  if (lep_relIso04DB_branch != 0) lep_relIso04DB();
  if (lep_relIso03EA_branch != 0) lep_relIso03EA();
  if (lep_relIso03EALep_branch != 0) lep_relIso03EALep();
  if (lep_relIso03EAv2_branch != 0) lep_relIso03EAv2();
  if (lep_relIso04EAv2_branch != 0) lep_relIso04EAv2();
  if (lep_relIso03EAv2Lep_branch != 0) lep_relIso03EAv2Lep();
  if (lep_tightCharge_branch != 0) lep_tightCharge();
  if (lep_trk_pt_branch != 0) lep_trk_pt();
  if (lep_charge_branch != 0) lep_charge();
  if (lep_etaSC_branch != 0) lep_etaSC();
  if (lep_MVA_branch != 0) lep_MVA();
  if (lep_isMediumPOG_branch != 0) lep_isMediumPOG();
  if (lep_isTightPOG_branch != 0) lep_isTightPOG();
  if (lep_isFromW_branch != 0) lep_isFromW();
  if (lep_isFromZ_branch != 0) lep_isFromZ();
  if (lep_isFromB_branch != 0) lep_isFromB();
  if (lep_isFromC_branch != 0) lep_isFromC();
  if (lep_isFromL_branch != 0) lep_isFromL();
  if (lep_isFromLF_branch != 0) lep_isFromLF();
  if (lep_genPart_index_branch != 0) lep_genPart_index();
  if (lep_r9_branch != 0) lep_r9();
  if (lep_nlayers_branch != 0) lep_nlayers();
  if (el_pt_branch != 0) el_pt();
  if (el_eta_branch != 0) el_eta();
  if (el_phi_branch != 0) el_phi();
  if (el_relIso03EA_branch != 0) el_relIso03EA();
  if (el_relIso03EALep_branch != 0) el_relIso03EALep();
  if (el_ip3d_branch != 0) el_ip3d();
  if (mu_pt_branch != 0) mu_pt();
  if (mu_eta_branch != 0) mu_eta();
  if (mu_phi_branch != 0) mu_phi();
  if (mu_relIso04DB_branch != 0) mu_relIso04DB();
  if (mu_relIso03EA_branch != 0) mu_relIso03EA();
  if (mu_relIso03EALep_branch != 0) mu_relIso03EALep();
  if (mu_ip3d_branch != 0) mu_ip3d();
  if (lbnt_pt_branch != 0) lbnt_pt();
  if (lbnt_coneCorrPt_branch != 0) lbnt_coneCorrPt();
  if (lbnt_abseta_branch != 0) lbnt_abseta();
  if (lbnt_pdgId_branch != 0) lbnt_pdgId();
  if (lbnt_el_pt_branch != 0) lbnt_el_pt();
  if (lbnt_el_coneCorrPt_branch != 0) lbnt_el_coneCorrPt();
  if (lbnt_el_abseta_branch != 0) lbnt_el_abseta();
  if (lbnt_mu_pt_branch != 0) lbnt_mu_pt();
  if (lbnt_mu_coneCorrPt_branch != 0) lbnt_mu_coneCorrPt();
  if (lbnt_mu_abseta_branch != 0) lbnt_mu_abseta();
  if (jets_p4_branch != 0) jets_p4();
  if (jets_up_p4_branch != 0) jets_up_p4();
  if (jets_dn_p4_branch != 0) jets_dn_p4();
  if (jets_csv_branch != 0) jets_csv();
  if (jets_up_csv_branch != 0) jets_up_csv();
  if (jets_dn_csv_branch != 0) jets_dn_csv();
  if (ak8jets_p4_branch != 0) ak8jets_p4();
  if (ak8jets_softdropMass_branch != 0) ak8jets_softdropMass();
  if (ak8jets_prunedMass_branch != 0) ak8jets_prunedMass();
  if (ak8jets_trimmedMass_branch != 0) ak8jets_trimmedMass();
  if (ak8jets_mass_branch != 0) ak8jets_mass();
  if (ak8jets_nJettinessTau1_branch != 0) ak8jets_nJettinessTau1();
  if (ak8jets_nJettinessTau2_branch != 0) ak8jets_nJettinessTau2();
  if (ak8jets_softdropPuppiSubjet1_branch != 0) ak8jets_softdropPuppiSubjet1();
  if (ak8jets_softdropPuppiSubjet2_branch != 0) ak8jets_softdropPuppiSubjet2();
  if (ak8jets_puppi_softdropMass_branch != 0) ak8jets_puppi_softdropMass();
  if (ak8jets_puppi_nJettinessTau1_branch != 0) ak8jets_puppi_nJettinessTau1();
  if (ak8jets_puppi_nJettinessTau2_branch != 0) ak8jets_puppi_nJettinessTau2();
  if (ak8jets_puppi_eta_branch != 0) ak8jets_puppi_eta();
  if (ak8jets_puppi_phi_branch != 0) ak8jets_puppi_phi();
  if (ak8jets_puppi_pt_branch != 0) ak8jets_puppi_pt();
  if (ak8jets_puppi_mass_branch != 0) ak8jets_puppi_mass();
  if (met_pt_branch != 0) met_pt();
  if (met_phi_branch != 0) met_phi();
  if (met_up_pt_branch != 0) met_up_pt();
  if (met_up_phi_branch != 0) met_up_phi();
  if (met_dn_pt_branch != 0) met_dn_pt();
  if (met_dn_phi_branch != 0) met_dn_phi();
  if (met_gen_pt_branch != 0) met_gen_pt();
  if (met_gen_phi_branch != 0) met_gen_phi();
  if (firstgoodvertex_branch != 0) firstgoodvertex();
  if (nTrueInt_branch != 0) nTrueInt();
  if (nVert_branch != 0) nVert();
  if (nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch != 0) nisoTrack_mt2_cleaned_VVV_cutbased_veto();
  if (weight_btagsf_branch != 0) weight_btagsf();
  if (weight_btagsf_heavy_DN_branch != 0) weight_btagsf_heavy_DN();
  if (weight_btagsf_heavy_UP_branch != 0) weight_btagsf_heavy_UP();
  if (weight_btagsf_light_DN_branch != 0) weight_btagsf_light_DN();
  if (weight_btagsf_light_UP_branch != 0) weight_btagsf_light_UP();
  if (gen_ht_branch != 0) gen_ht();
  if (genPart_p4_branch != 0) genPart_p4();
  if (genPart_motherId_branch != 0) genPart_motherId();
  if (genPart_pdgId_branch != 0) genPart_pdgId();
  if (genPart_charge_branch != 0) genPart_charge();
  if (genPart_status_branch != 0) genPart_status();
  if (ngenLep_branch != 0) ngenLep();
  if (ngenLepFromTau_branch != 0) ngenLepFromTau();
  if (Flag_AllEventFilters_branch != 0) Flag_AllEventFilters();
  if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch != 0) Flag_EcalDeadCellTriggerPrimitiveFilter();
  if (Flag_HBHEIsoNoiseFilter_branch != 0) Flag_HBHEIsoNoiseFilter();
  if (Flag_HBHENoiseFilter_branch != 0) Flag_HBHENoiseFilter();
  if (Flag_badChargedCandidateFilter_branch != 0) Flag_badChargedCandidateFilter();
  if (Flag_badMuonFilter_branch != 0) Flag_badMuonFilter();
  if (Flag_badMuonFilterv2_branch != 0) Flag_badMuonFilterv2();
  if (Flag_badChargedCandidateFilterv2_branch != 0) Flag_badChargedCandidateFilterv2();
  if (Flag_eeBadScFilter_branch != 0) Flag_eeBadScFilter();
  if (Flag_ecalBadCalibFilter_branch != 0) Flag_ecalBadCalibFilter();
  if (Flag_globalTightHalo2016_branch != 0) Flag_globalTightHalo2016();
  if (Flag_goodVertices_branch != 0) Flag_goodVertices();
  if (Flag_ecalLaserCorrFilter_branch != 0) Flag_ecalLaserCorrFilter();
  if (Flag_hcalLaserEventFilter_branch != 0) Flag_hcalLaserEventFilter();
  if (Flag_trackingFailureFilter_branch != 0) Flag_trackingFailureFilter();
  if (Flag_CSCTightHaloFilter_branch != 0) Flag_CSCTightHaloFilter();
  if (Flag_CSCTightHalo2015Filter_branch != 0) Flag_CSCTightHalo2015Filter();
  if (Flag_badMuons_branch != 0) Flag_badMuons();
  if (Flag_duplicateMuons_branch != 0) Flag_duplicateMuons();
  if (Flag_noBadMuons_branch != 0) Flag_noBadMuons();
  if (fastsimfilt_branch != 0) fastsimfilt();
  if (nVlep_branch != 0) nVlep();
  if (nTlep_branch != 0) nTlep();
  if (nTlepSS_branch != 0) nTlepSS();
  if (nLlep_branch != 0) nLlep();
  if (nSFOS_branch != 0) nSFOS();
  if (nSFOSinZ_branch != 0) nSFOSinZ();
  if (nj_branch != 0) nj();
  if (nj_up_branch != 0) nj_up();
  if (nj_dn_branch != 0) nj_dn();
  if (nj30_branch != 0) nj30();
  if (nj30_up_branch != 0) nj30_up();
  if (nj30_dn_branch != 0) nj30_dn();
  if (nb_branch != 0) nb();
  if (nb_up_branch != 0) nb_up();
  if (nb_dn_branch != 0) nb_dn();
  if (Mjj_branch != 0) Mjj();
  if (Mjj_up_branch != 0) Mjj_up();
  if (Mjj_dn_branch != 0) Mjj_dn();
  if (DRjj_branch != 0) DRjj();
  if (DRjj_up_branch != 0) DRjj_up();
  if (DRjj_dn_branch != 0) DRjj_dn();
  if (jet0_wtag_p4_branch != 0) jet0_wtag_p4();
  if (jet0_wtag_p4_up_branch != 0) jet0_wtag_p4_up();
  if (jet0_wtag_p4_dn_branch != 0) jet0_wtag_p4_dn();
  if (jet1_wtag_p4_branch != 0) jet1_wtag_p4();
  if (jet1_wtag_p4_up_branch != 0) jet1_wtag_p4_up();
  if (jet1_wtag_p4_dn_branch != 0) jet1_wtag_p4_dn();
  if (MjjDR1_branch != 0) MjjDR1();
  if (MjjDR1_up_branch != 0) MjjDR1_up();
  if (MjjDR1_dn_branch != 0) MjjDR1_dn();
  if (DRjjDR1_branch != 0) DRjjDR1();
  if (DRjjDR1_up_branch != 0) DRjjDR1_up();
  if (DRjjDR1_dn_branch != 0) DRjjDR1_dn();
  if (jet0_wtag_p4_DR1_branch != 0) jet0_wtag_p4_DR1();
  if (jet0_wtag_p4_DR1_up_branch != 0) jet0_wtag_p4_DR1_up();
  if (jet0_wtag_p4_DR1_dn_branch != 0) jet0_wtag_p4_DR1_dn();
  if (jet1_wtag_p4_DR1_branch != 0) jet1_wtag_p4_DR1();
  if (jet1_wtag_p4_DR1_up_branch != 0) jet1_wtag_p4_DR1_up();
  if (jet1_wtag_p4_DR1_dn_branch != 0) jet1_wtag_p4_DR1_dn();
  if (MjjVBF_branch != 0) MjjVBF();
  if (MjjVBF_up_branch != 0) MjjVBF_up();
  if (MjjVBF_dn_branch != 0) MjjVBF_dn();
  if (DetajjVBF_branch != 0) DetajjVBF();
  if (DetajjVBF_up_branch != 0) DetajjVBF_up();
  if (DetajjVBF_dn_branch != 0) DetajjVBF_dn();
  if (MjjL_branch != 0) MjjL();
  if (MjjL_up_branch != 0) MjjL_up();
  if (MjjL_dn_branch != 0) MjjL_dn();
  if (DetajjL_branch != 0) DetajjL();
  if (DetajjL_up_branch != 0) DetajjL_up();
  if (DetajjL_dn_branch != 0) DetajjL_dn();
  if (MllSS_branch != 0) MllSS();
  if (MeeSS_branch != 0) MeeSS();
  if (Mll3L_branch != 0) Mll3L();
  if (Mee3L_branch != 0) Mee3L();
  if (Mll3L1_branch != 0) Mll3L1();
  if (M3l_branch != 0) M3l();
  if (Pt3l_branch != 0) Pt3l();
  if (M01_branch != 0) M01();
  if (M02_branch != 0) M02();
  if (M12_branch != 0) M12();
  if (isSFOS01_branch != 0) isSFOS01();
  if (isSFOS02_branch != 0) isSFOS02();
  if (isSFOS12_branch != 0) isSFOS12();
  if (DPhi3lMET_branch != 0) DPhi3lMET();
  if (DPhi3lMET_up_branch != 0) DPhi3lMET_up();
  if (DPhi3lMET_dn_branch != 0) DPhi3lMET_dn();
  if (DPhi3lMET_gen_branch != 0) DPhi3lMET_gen();
  if (MTmax_branch != 0) MTmax();
  if (MTmax_up_branch != 0) MTmax_up();
  if (MTmax_dn_branch != 0) MTmax_dn();
  if (MTmax_gen_branch != 0) MTmax_gen();
  if (MTmin_branch != 0) MTmin();
  if (MTmin_up_branch != 0) MTmin_up();
  if (MTmin_dn_branch != 0) MTmin_dn();
  if (MTmin_gen_branch != 0) MTmin_gen();
  if (MT3rd_branch != 0) MT3rd();
  if (MT3rd_up_branch != 0) MT3rd_up();
  if (MT3rd_dn_branch != 0) MT3rd_dn();
  if (MT3rd_gen_branch != 0) MT3rd_gen();
  if (MTmax3L_branch != 0) MTmax3L();
  if (MTmax3L_up_branch != 0) MTmax3L_up();
  if (MTmax3L_dn_branch != 0) MTmax3L_dn();
  if (MTmax3L_gen_branch != 0) MTmax3L_gen();
  if (passSSee_branch != 0) passSSee();
  if (passSSem_branch != 0) passSSem();
  if (passSSmm_branch != 0) passSSmm();
  if (lep_idx0_SS_branch != 0) lep_idx0_SS();
  if (lep_idx1_SS_branch != 0) lep_idx1_SS();
  if (bkgtype_branch != 0) bkgtype();
  if (vetophoton_branch != 0) vetophoton();
  if (purewgt_branch != 0) purewgt();
  if (purewgt_up_branch != 0) purewgt_up();
  if (purewgt_dn_branch != 0) purewgt_dn();
  if (ffwgt_branch != 0) ffwgt();
  if (ffwgt_up_branch != 0) ffwgt_up();
  if (ffwgt_dn_branch != 0) ffwgt_dn();
  if (ffwgt_el_up_branch != 0) ffwgt_el_up();
  if (ffwgt_el_dn_branch != 0) ffwgt_el_dn();
  if (ffwgt_mu_up_branch != 0) ffwgt_mu_up();
  if (ffwgt_mu_dn_branch != 0) ffwgt_mu_dn();
  if (ffwgt_closure_up_branch != 0) ffwgt_closure_up();
  if (ffwgt_closure_dn_branch != 0) ffwgt_closure_dn();
  if (ffwgt_closure_el_up_branch != 0) ffwgt_closure_el_up();
  if (ffwgt_closure_el_dn_branch != 0) ffwgt_closure_el_dn();
  if (ffwgt_closure_mu_up_branch != 0) ffwgt_closure_mu_up();
  if (ffwgt_closure_mu_dn_branch != 0) ffwgt_closure_mu_dn();
  if (ffwgt_full_up_branch != 0) ffwgt_full_up();
  if (ffwgt_full_dn_branch != 0) ffwgt_full_dn();
  if (ffwgtqcd_branch != 0) ffwgtqcd();
  if (ffwgtqcd_up_branch != 0) ffwgtqcd_up();
  if (ffwgtqcd_dn_branch != 0) ffwgtqcd_dn();
  if (lepsf_branch != 0) lepsf();
  if (lepsf_up_branch != 0) lepsf_up();
  if (lepsf_dn_branch != 0) lepsf_dn();
  if (trigeff_branch != 0) trigeff();
  if (trigeff_up_branch != 0) trigeff_up();
  if (trigeff_dn_branch != 0) trigeff_dn();
  if (trigsf_branch != 0) trigsf();
  if (trigsf_up_branch != 0) trigsf_up();
  if (trigsf_dn_branch != 0) trigsf_dn();
  if (musmear_sf_branch != 0) musmear_sf();
}

const int &wwwtree::run() {
  if (not run_isLoaded) {
    if (run_branch != 0) {
      run_branch->GetEntry(index);
    } else {
      printf("branch run_branch does not exist!\n");
      exit(1);
    }
    run_isLoaded = true;
  }
  return run_;
}

const int &wwwtree::lumi() {
  if (not lumi_isLoaded) {
    if (lumi_branch != 0) {
      lumi_branch->GetEntry(index);
    } else {
      printf("branch lumi_branch does not exist!\n");
      exit(1);
    }
    lumi_isLoaded = true;
  }
  return lumi_;
}

const unsigned long long &wwwtree::evt() {
  if (not evt_isLoaded) {
    if (evt_branch != 0) {
      evt_branch->GetEntry(index);
    } else {
      printf("branch evt_branch does not exist!\n");
      exit(1);
    }
    evt_isLoaded = true;
  }
  return evt_;
}

const int &wwwtree::isData() {
  if (not isData_isLoaded) {
    if (isData_branch != 0) {
      isData_branch->GetEntry(index);
    } else {
      printf("branch isData_branch does not exist!\n");
      exit(1);
    }
    isData_isLoaded = true;
  }
  return isData_;
}

const float &wwwtree::evt_scale1fb() {
  if (not evt_scale1fb_isLoaded) {
    if (evt_scale1fb_branch != 0) {
      evt_scale1fb_branch->GetEntry(index);
    } else {
      printf("branch evt_scale1fb_branch does not exist!\n");
      exit(1);
    }
    evt_scale1fb_isLoaded = true;
  }
  return evt_scale1fb_;
}

const float &wwwtree::xsec_br() {
  if (not xsec_br_isLoaded) {
    if (xsec_br_branch != 0) {
      xsec_br_branch->GetEntry(index);
    } else {
      printf("branch xsec_br_branch does not exist!\n");
      exit(1);
    }
    xsec_br_isLoaded = true;
  }
  return xsec_br_;
}

const int &wwwtree::evt_passgoodrunlist() {
  if (not evt_passgoodrunlist_isLoaded) {
    if (evt_passgoodrunlist_branch != 0) {
      evt_passgoodrunlist_branch->GetEntry(index);
    } else {
      printf("branch evt_passgoodrunlist_branch does not exist!\n");
      exit(1);
    }
    evt_passgoodrunlist_isLoaded = true;
  }
  return evt_passgoodrunlist_;
}

const TString &wwwtree::CMS4path() {
  if (not CMS4path_isLoaded) {
    if (CMS4path_branch != 0) {
      CMS4path_branch->GetEntry(index);
    } else {
      printf("branch CMS4path_branch does not exist!\n");
      exit(1);
    }
    CMS4path_isLoaded = true;
  }
  return *CMS4path_;
}

const int &wwwtree::CMS4index() {
  if (not CMS4index_isLoaded) {
    if (CMS4index_branch != 0) {
      CMS4index_branch->GetEntry(index);
    } else {
      printf("branch CMS4index_branch does not exist!\n");
      exit(1);
    }
    CMS4index_isLoaded = true;
  }
  return CMS4index_;
}

const float &wwwtree::weight_fr_r1_f1() {
  if (not weight_fr_r1_f1_isLoaded) {
    if (weight_fr_r1_f1_branch != 0) {
      weight_fr_r1_f1_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r1_f1_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r1_f1_isLoaded = true;
  }
  return weight_fr_r1_f1_;
}

const float &wwwtree::weight_fr_r1_f2() {
  if (not weight_fr_r1_f2_isLoaded) {
    if (weight_fr_r1_f2_branch != 0) {
      weight_fr_r1_f2_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r1_f2_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r1_f2_isLoaded = true;
  }
  return weight_fr_r1_f2_;
}

const float &wwwtree::weight_fr_r1_f0p5() {
  if (not weight_fr_r1_f0p5_isLoaded) {
    if (weight_fr_r1_f0p5_branch != 0) {
      weight_fr_r1_f0p5_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r1_f0p5_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r1_f0p5_isLoaded = true;
  }
  return weight_fr_r1_f0p5_;
}

const float &wwwtree::weight_fr_r2_f1() {
  if (not weight_fr_r2_f1_isLoaded) {
    if (weight_fr_r2_f1_branch != 0) {
      weight_fr_r2_f1_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r2_f1_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r2_f1_isLoaded = true;
  }
  return weight_fr_r2_f1_;
}

const float &wwwtree::weight_fr_r2_f2() {
  if (not weight_fr_r2_f2_isLoaded) {
    if (weight_fr_r2_f2_branch != 0) {
      weight_fr_r2_f2_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r2_f2_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r2_f2_isLoaded = true;
  }
  return weight_fr_r2_f2_;
}

const float &wwwtree::weight_fr_r2_f0p5() {
  if (not weight_fr_r2_f0p5_isLoaded) {
    if (weight_fr_r2_f0p5_branch != 0) {
      weight_fr_r2_f0p5_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r2_f0p5_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r2_f0p5_isLoaded = true;
  }
  return weight_fr_r2_f0p5_;
}

const float &wwwtree::weight_fr_r0p5_f1() {
  if (not weight_fr_r0p5_f1_isLoaded) {
    if (weight_fr_r0p5_f1_branch != 0) {
      weight_fr_r0p5_f1_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r0p5_f1_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r0p5_f1_isLoaded = true;
  }
  return weight_fr_r0p5_f1_;
}

const float &wwwtree::weight_fr_r0p5_f2() {
  if (not weight_fr_r0p5_f2_isLoaded) {
    if (weight_fr_r0p5_f2_branch != 0) {
      weight_fr_r0p5_f2_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r0p5_f2_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r0p5_f2_isLoaded = true;
  }
  return weight_fr_r0p5_f2_;
}

const float &wwwtree::weight_fr_r0p5_f0p5() {
  if (not weight_fr_r0p5_f0p5_isLoaded) {
    if (weight_fr_r0p5_f0p5_branch != 0) {
      weight_fr_r0p5_f0p5_branch->GetEntry(index);
    } else {
      printf("branch weight_fr_r0p5_f0p5_branch does not exist!\n");
      exit(1);
    }
    weight_fr_r0p5_f0p5_isLoaded = true;
  }
  return weight_fr_r0p5_f0p5_;
}

const float &wwwtree::weight_pdf_up() {
  if (not weight_pdf_up_isLoaded) {
    if (weight_pdf_up_branch != 0) {
      weight_pdf_up_branch->GetEntry(index);
    } else {
      printf("branch weight_pdf_up_branch does not exist!\n");
      exit(1);
    }
    weight_pdf_up_isLoaded = true;
  }
  return weight_pdf_up_;
}

const float &wwwtree::weight_pdf_down() {
  if (not weight_pdf_down_isLoaded) {
    if (weight_pdf_down_branch != 0) {
      weight_pdf_down_branch->GetEntry(index);
    } else {
      printf("branch weight_pdf_down_branch does not exist!\n");
      exit(1);
    }
    weight_pdf_down_isLoaded = true;
  }
  return weight_pdf_down_;
}

const float &wwwtree::weight_alphas_down() {
  if (not weight_alphas_down_isLoaded) {
    if (weight_alphas_down_branch != 0) {
      weight_alphas_down_branch->GetEntry(index);
    } else {
      printf("branch weight_alphas_down_branch does not exist!\n");
      exit(1);
    }
    weight_alphas_down_isLoaded = true;
  }
  return weight_alphas_down_;
}

const float &wwwtree::weight_alphas_up() {
  if (not weight_alphas_up_isLoaded) {
    if (weight_alphas_up_branch != 0) {
      weight_alphas_up_branch->GetEntry(index);
    } else {
      printf("branch weight_alphas_up_branch does not exist!\n");
      exit(1);
    }
    weight_alphas_up_isLoaded = true;
  }
  return weight_alphas_up_;
}

const float &wwwtree::weight_isr() {
  if (not weight_isr_isLoaded) {
    if (weight_isr_branch != 0) {
      weight_isr_branch->GetEntry(index);
    } else {
      printf("branch weight_isr_branch does not exist!\n");
      exit(1);
    }
    weight_isr_isLoaded = true;
  }
  return weight_isr_;
}

const float &wwwtree::weight_isr_up() {
  if (not weight_isr_up_isLoaded) {
    if (weight_isr_up_branch != 0) {
      weight_isr_up_branch->GetEntry(index);
    } else {
      printf("branch weight_isr_up_branch does not exist!\n");
      exit(1);
    }
    weight_isr_up_isLoaded = true;
  }
  return weight_isr_up_;
}

const float &wwwtree::weight_isr_down() {
  if (not weight_isr_down_isLoaded) {
    if (weight_isr_down_branch != 0) {
      weight_isr_down_branch->GetEntry(index);
    } else {
      printf("branch weight_isr_down_branch does not exist!\n");
      exit(1);
    }
    weight_isr_down_isLoaded = true;
  }
  return weight_isr_down_;
}

const int &wwwtree::HLT_DoubleMu() {
  if (not HLT_DoubleMu_isLoaded) {
    if (HLT_DoubleMu_branch != 0) {
      HLT_DoubleMu_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleMu_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleMu_isLoaded = true;
  }
  return HLT_DoubleMu_;
}

const int &wwwtree::HLT_DoubleEl() {
  if (not HLT_DoubleEl_isLoaded) {
    if (HLT_DoubleEl_branch != 0) {
      HLT_DoubleEl_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleEl_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleEl_isLoaded = true;
  }
  return HLT_DoubleEl_;
}

const int &wwwtree::HLT_DoubleEl_DZ() {
  if (not HLT_DoubleEl_DZ_isLoaded) {
    if (HLT_DoubleEl_DZ_branch != 0) {
      HLT_DoubleEl_DZ_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleEl_DZ_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleEl_DZ_isLoaded = true;
  }
  return HLT_DoubleEl_DZ_;
}

const int &wwwtree::HLT_DoubleEl_DZ_2() {
  if (not HLT_DoubleEl_DZ_2_isLoaded) {
    if (HLT_DoubleEl_DZ_2_branch != 0) {
      HLT_DoubleEl_DZ_2_branch->GetEntry(index);
    } else {
      printf("branch HLT_DoubleEl_DZ_2_branch does not exist!\n");
      exit(1);
    }
    HLT_DoubleEl_DZ_2_isLoaded = true;
  }
  return HLT_DoubleEl_DZ_2_;
}

const int &wwwtree::HLT_MuEG() {
  if (not HLT_MuEG_isLoaded) {
    if (HLT_MuEG_branch != 0) {
      HLT_MuEG_branch->GetEntry(index);
    } else {
      printf("branch HLT_MuEG_branch does not exist!\n");
      exit(1);
    }
    HLT_MuEG_isLoaded = true;
  }
  return HLT_MuEG_;
}

const int &wwwtree::HLT_SingleIsoEl8() {
  if (not HLT_SingleIsoEl8_isLoaded) {
    if (HLT_SingleIsoEl8_branch != 0) {
      HLT_SingleIsoEl8_branch->GetEntry(index);
    } else {
      printf("branch HLT_SingleIsoEl8_branch does not exist!\n");
      exit(1);
    }
    HLT_SingleIsoEl8_isLoaded = true;
  }
  return HLT_SingleIsoEl8_;
}

const int &wwwtree::HLT_SingleIsoEl17() {
  if (not HLT_SingleIsoEl17_isLoaded) {
    if (HLT_SingleIsoEl17_branch != 0) {
      HLT_SingleIsoEl17_branch->GetEntry(index);
    } else {
      printf("branch HLT_SingleIsoEl17_branch does not exist!\n");
      exit(1);
    }
    HLT_SingleIsoEl17_isLoaded = true;
  }
  return HLT_SingleIsoEl17_;
}

const int &wwwtree::HLT_SingleIsoEl23() {
  if (not HLT_SingleIsoEl23_isLoaded) {
    if (HLT_SingleIsoEl23_branch != 0) {
      HLT_SingleIsoEl23_branch->GetEntry(index);
    } else {
      printf("branch HLT_SingleIsoEl23_branch does not exist!\n");
      exit(1);
    }
    HLT_SingleIsoEl23_isLoaded = true;
  }
  return HLT_SingleIsoEl23_;
}

const int &wwwtree::HLT_SingleIsoMu8() {
  if (not HLT_SingleIsoMu8_isLoaded) {
    if (HLT_SingleIsoMu8_branch != 0) {
      HLT_SingleIsoMu8_branch->GetEntry(index);
    } else {
      printf("branch HLT_SingleIsoMu8_branch does not exist!\n");
      exit(1);
    }
    HLT_SingleIsoMu8_isLoaded = true;
  }
  return HLT_SingleIsoMu8_;
}

const int &wwwtree::HLT_SingleIsoMu17() {
  if (not HLT_SingleIsoMu17_isLoaded) {
    if (HLT_SingleIsoMu17_branch != 0) {
      HLT_SingleIsoMu17_branch->GetEntry(index);
    } else {
      printf("branch HLT_SingleIsoMu17_branch does not exist!\n");
      exit(1);
    }
    HLT_SingleIsoMu17_isLoaded = true;
  }
  return HLT_SingleIsoMu17_;
}

const int &wwwtree::HLT_PFMET140_PFMHT140_IDTight() {
  if (not HLT_PFMET140_PFMHT140_IDTight_isLoaded) {
    if (HLT_PFMET140_PFMHT140_IDTight_branch != 0) {
      HLT_PFMET140_PFMHT140_IDTight_branch->GetEntry(index);
    } else {
      printf("branch HLT_PFMET140_PFMHT140_IDTight_branch does not exist!\n");
      exit(1);
    }
    HLT_PFMET140_PFMHT140_IDTight_isLoaded = true;
  }
  return HLT_PFMET140_PFMHT140_IDTight_;
}

const int &wwwtree::mc_HLT_DoubleMu() {
  if (not mc_HLT_DoubleMu_isLoaded) {
    if (mc_HLT_DoubleMu_branch != 0) {
      mc_HLT_DoubleMu_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleMu_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleMu_isLoaded = true;
  }
  return mc_HLT_DoubleMu_;
}

const int &wwwtree::mc_HLT_DoubleEl() {
  if (not mc_HLT_DoubleEl_isLoaded) {
    if (mc_HLT_DoubleEl_branch != 0) {
      mc_HLT_DoubleEl_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleEl_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleEl_isLoaded = true;
  }
  return mc_HLT_DoubleEl_;
}

const int &wwwtree::mc_HLT_DoubleEl_DZ() {
  if (not mc_HLT_DoubleEl_DZ_isLoaded) {
    if (mc_HLT_DoubleEl_DZ_branch != 0) {
      mc_HLT_DoubleEl_DZ_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleEl_DZ_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleEl_DZ_isLoaded = true;
  }
  return mc_HLT_DoubleEl_DZ_;
}

const int &wwwtree::mc_HLT_DoubleEl_DZ_2() {
  if (not mc_HLT_DoubleEl_DZ_2_isLoaded) {
    if (mc_HLT_DoubleEl_DZ_2_branch != 0) {
      mc_HLT_DoubleEl_DZ_2_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_DoubleEl_DZ_2_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_DoubleEl_DZ_2_isLoaded = true;
  }
  return mc_HLT_DoubleEl_DZ_2_;
}

const int &wwwtree::mc_HLT_MuEG() {
  if (not mc_HLT_MuEG_isLoaded) {
    if (mc_HLT_MuEG_branch != 0) {
      mc_HLT_MuEG_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_MuEG_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_MuEG_isLoaded = true;
  }
  return mc_HLT_MuEG_;
}

const int &wwwtree::mc_HLT_SingleIsoEl8() {
  if (not mc_HLT_SingleIsoEl8_isLoaded) {
    if (mc_HLT_SingleIsoEl8_branch != 0) {
      mc_HLT_SingleIsoEl8_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_SingleIsoEl8_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_SingleIsoEl8_isLoaded = true;
  }
  return mc_HLT_SingleIsoEl8_;
}

const int &wwwtree::mc_HLT_SingleIsoEl17() {
  if (not mc_HLT_SingleIsoEl17_isLoaded) {
    if (mc_HLT_SingleIsoEl17_branch != 0) {
      mc_HLT_SingleIsoEl17_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_SingleIsoEl17_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_SingleIsoEl17_isLoaded = true;
  }
  return mc_HLT_SingleIsoEl17_;
}

const int &wwwtree::mc_HLT_SingleIsoEl23() {
  if (not mc_HLT_SingleIsoEl23_isLoaded) {
    if (mc_HLT_SingleIsoEl23_branch != 0) {
      mc_HLT_SingleIsoEl23_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_SingleIsoEl23_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_SingleIsoEl23_isLoaded = true;
  }
  return mc_HLT_SingleIsoEl23_;
}

const int &wwwtree::mc_HLT_SingleIsoMu8() {
  if (not mc_HLT_SingleIsoMu8_isLoaded) {
    if (mc_HLT_SingleIsoMu8_branch != 0) {
      mc_HLT_SingleIsoMu8_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_SingleIsoMu8_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_SingleIsoMu8_isLoaded = true;
  }
  return mc_HLT_SingleIsoMu8_;
}

const int &wwwtree::mc_HLT_SingleIsoMu17() {
  if (not mc_HLT_SingleIsoMu17_isLoaded) {
    if (mc_HLT_SingleIsoMu17_branch != 0) {
      mc_HLT_SingleIsoMu17_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_SingleIsoMu17_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_SingleIsoMu17_isLoaded = true;
  }
  return mc_HLT_SingleIsoMu17_;
}

const int &wwwtree::mc_HLT_PFMET140_PFMHT140_IDTight() {
  if (not mc_HLT_PFMET140_PFMHT140_IDTight_isLoaded) {
    if (mc_HLT_PFMET140_PFMHT140_IDTight_branch != 0) {
      mc_HLT_PFMET140_PFMHT140_IDTight_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_PFMET140_PFMHT140_IDTight_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_PFMET140_PFMHT140_IDTight_isLoaded = true;
  }
  return mc_HLT_PFMET140_PFMHT140_IDTight_;
}

const int &wwwtree::pass_duplicate_ee_em_mm() {
  if (not pass_duplicate_ee_em_mm_isLoaded) {
    if (pass_duplicate_ee_em_mm_branch != 0) {
      pass_duplicate_ee_em_mm_branch->GetEntry(index);
    } else {
      printf("branch pass_duplicate_ee_em_mm_branch does not exist!\n");
      exit(1);
    }
    pass_duplicate_ee_em_mm_isLoaded = true;
  }
  return pass_duplicate_ee_em_mm_;
}

const int &wwwtree::pass_duplicate_mm_em_ee() {
  if (not pass_duplicate_mm_em_ee_isLoaded) {
    if (pass_duplicate_mm_em_ee_branch != 0) {
      pass_duplicate_mm_em_ee_branch->GetEntry(index);
    } else {
      printf("branch pass_duplicate_mm_em_ee_branch does not exist!\n");
      exit(1);
    }
    pass_duplicate_mm_em_ee_isLoaded = true;
  }
  return pass_duplicate_mm_em_ee_;
}

const int &wwwtree::is2016() {
  if (not is2016_isLoaded) {
    if (is2016_branch != 0) {
      is2016_branch->GetEntry(index);
    } else {
      printf("branch is2016_branch does not exist!\n");
      exit(1);
    }
    is2016_isLoaded = true;
  }
  return is2016_;
}

const int &wwwtree::is2017() {
  if (not is2017_isLoaded) {
    if (is2017_branch != 0) {
      is2017_branch->GetEntry(index);
    } else {
      printf("branch is2017_branch does not exist!\n");
      exit(1);
    }
    is2017_isLoaded = true;
  }
  return is2017_;
}

const int &wwwtree::HLT_MuEG_2016() {
  if (not HLT_MuEG_2016_isLoaded) {
    if (HLT_MuEG_2016_branch != 0) {
      HLT_MuEG_2016_branch->GetEntry(index);
    } else {
      printf("branch HLT_MuEG_2016_branch does not exist!\n");
      exit(1);
    }
    HLT_MuEG_2016_isLoaded = true;
  }
  return HLT_MuEG_2016_;
}

const int &wwwtree::mc_HLT_MuEG_2016() {
  if (not mc_HLT_MuEG_2016_isLoaded) {
    if (mc_HLT_MuEG_2016_branch != 0) {
      mc_HLT_MuEG_2016_branch->GetEntry(index);
    } else {
      printf("branch mc_HLT_MuEG_2016_branch does not exist!\n");
      exit(1);
    }
    mc_HLT_MuEG_2016_isLoaded = true;
  }
  return mc_HLT_MuEG_2016_;
}

const int &wwwtree::pass_duplicate_ee_em2016_mm() {
  if (not pass_duplicate_ee_em2016_mm_isLoaded) {
    if (pass_duplicate_ee_em2016_mm_branch != 0) {
      pass_duplicate_ee_em2016_mm_branch->GetEntry(index);
    } else {
      printf("branch pass_duplicate_ee_em2016_mm_branch does not exist!\n");
      exit(1);
    }
    pass_duplicate_ee_em2016_mm_isLoaded = true;
  }
  return pass_duplicate_ee_em2016_mm_;
}

const int &wwwtree::pass_duplicate_mm_em2016_ee() {
  if (not pass_duplicate_mm_em2016_ee_isLoaded) {
    if (pass_duplicate_mm_em2016_ee_branch != 0) {
      pass_duplicate_mm_em2016_ee_branch->GetEntry(index);
    } else {
      printf("branch pass_duplicate_mm_em2016_ee_branch does not exist!\n");
      exit(1);
    }
    pass_duplicate_mm_em2016_ee_isLoaded = true;
  }
  return pass_duplicate_mm_em2016_ee_;
}

const int &wwwtree::passTrigger() {
  if (not passTrigger_isLoaded) {
    if (passTrigger_branch != 0) {
      passTrigger_branch->GetEntry(index);
    } else {
      printf("branch passTrigger_branch does not exist!\n");
      exit(1);
    }
    passTrigger_isLoaded = true;
  }
  return passTrigger_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &wwwtree::lep_p4() {
  if (not lep_p4_isLoaded) {
    if (lep_p4_branch != 0) {
      lep_p4_branch->GetEntry(index);
    } else {
      printf("branch lep_p4_branch does not exist!\n");
      exit(1);
    }
    lep_p4_isLoaded = true;
  }
  return *lep_p4_;
}

const vector<float> &wwwtree::lep_pt() {
  if (not lep_pt_isLoaded) {
    if (lep_pt_branch != 0) {
      lep_pt_branch->GetEntry(index);
    } else {
      printf("branch lep_pt_branch does not exist!\n");
      exit(1);
    }
    lep_pt_isLoaded = true;
  }
  return *lep_pt_;
}

const vector<float> &wwwtree::lep_eta() {
  if (not lep_eta_isLoaded) {
    if (lep_eta_branch != 0) {
      lep_eta_branch->GetEntry(index);
    } else {
      printf("branch lep_eta_branch does not exist!\n");
      exit(1);
    }
    lep_eta_isLoaded = true;
  }
  return *lep_eta_;
}

const vector<float> &wwwtree::lep_phi() {
  if (not lep_phi_isLoaded) {
    if (lep_phi_branch != 0) {
      lep_phi_branch->GetEntry(index);
    } else {
      printf("branch lep_phi_branch does not exist!\n");
      exit(1);
    }
    lep_phi_isLoaded = true;
  }
  return *lep_phi_;
}

const vector<float> &wwwtree::lep_coneCorrPt() {
  if (not lep_coneCorrPt_isLoaded) {
    if (lep_coneCorrPt_branch != 0) {
      lep_coneCorrPt_branch->GetEntry(index);
    } else {
      printf("branch lep_coneCorrPt_branch does not exist!\n");
      exit(1);
    }
    lep_coneCorrPt_isLoaded = true;
  }
  return *lep_coneCorrPt_;
}

const vector<float> &wwwtree::lep_ip3d() {
  if (not lep_ip3d_isLoaded) {
    if (lep_ip3d_branch != 0) {
      lep_ip3d_branch->GetEntry(index);
    } else {
      printf("branch lep_ip3d_branch does not exist!\n");
      exit(1);
    }
    lep_ip3d_isLoaded = true;
  }
  return *lep_ip3d_;
}

const vector<float> &wwwtree::lep_ip3derr() {
  if (not lep_ip3derr_isLoaded) {
    if (lep_ip3derr_branch != 0) {
      lep_ip3derr_branch->GetEntry(index);
    } else {
      printf("branch lep_ip3derr_branch does not exist!\n");
      exit(1);
    }
    lep_ip3derr_isLoaded = true;
  }
  return *lep_ip3derr_;
}

const vector<int> &wwwtree::lep_isTriggerSafe_v1() {
  if (not lep_isTriggerSafe_v1_isLoaded) {
    if (lep_isTriggerSafe_v1_branch != 0) {
      lep_isTriggerSafe_v1_branch->GetEntry(index);
    } else {
      printf("branch lep_isTriggerSafe_v1_branch does not exist!\n");
      exit(1);
    }
    lep_isTriggerSafe_v1_isLoaded = true;
  }
  return *lep_isTriggerSafe_v1_;
}

const vector<int> &wwwtree::lep_lostHits() {
  if (not lep_lostHits_isLoaded) {
    if (lep_lostHits_branch != 0) {
      lep_lostHits_branch->GetEntry(index);
    } else {
      printf("branch lep_lostHits_branch does not exist!\n");
      exit(1);
    }
    lep_lostHits_isLoaded = true;
  }
  return *lep_lostHits_;
}

const vector<int> &wwwtree::lep_convVeto() {
  if (not lep_convVeto_isLoaded) {
    if (lep_convVeto_branch != 0) {
      lep_convVeto_branch->GetEntry(index);
    } else {
      printf("branch lep_convVeto_branch does not exist!\n");
      exit(1);
    }
    lep_convVeto_isLoaded = true;
  }
  return *lep_convVeto_;
}

const vector<int> &wwwtree::lep_motherIdSS() {
  if (not lep_motherIdSS_isLoaded) {
    if (lep_motherIdSS_branch != 0) {
      lep_motherIdSS_branch->GetEntry(index);
    } else {
      printf("branch lep_motherIdSS_branch does not exist!\n");
      exit(1);
    }
    lep_motherIdSS_isLoaded = true;
  }
  return *lep_motherIdSS_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_3l_fo() {
  if (not lep_pass_VVV_cutbased_3l_fo_isLoaded) {
    if (lep_pass_VVV_cutbased_3l_fo_branch != 0) {
      lep_pass_VVV_cutbased_3l_fo_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_3l_fo_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_3l_fo_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_3l_fo_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_3l_tight() {
  if (not lep_pass_VVV_cutbased_3l_tight_isLoaded) {
    if (lep_pass_VVV_cutbased_3l_tight_branch != 0) {
      lep_pass_VVV_cutbased_3l_tight_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_3l_tight_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_3l_tight_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_3l_tight_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_fo() {
  if (not lep_pass_VVV_cutbased_fo_isLoaded) {
    if (lep_pass_VVV_cutbased_fo_branch != 0) {
      lep_pass_VVV_cutbased_fo_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_fo_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_fo_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_fo_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_tight() {
  if (not lep_pass_VVV_cutbased_tight_isLoaded) {
    if (lep_pass_VVV_cutbased_tight_branch != 0) {
      lep_pass_VVV_cutbased_tight_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_tight_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_tight_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_tight_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_veto() {
  if (not lep_pass_VVV_cutbased_veto_isLoaded) {
    if (lep_pass_VVV_cutbased_veto_branch != 0) {
      lep_pass_VVV_cutbased_veto_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_veto_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_veto_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_veto_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_fo_noiso() {
  if (not lep_pass_VVV_cutbased_fo_noiso_isLoaded) {
    if (lep_pass_VVV_cutbased_fo_noiso_branch != 0) {
      lep_pass_VVV_cutbased_fo_noiso_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_fo_noiso_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_fo_noiso_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_fo_noiso_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_tight_noiso() {
  if (not lep_pass_VVV_cutbased_tight_noiso_isLoaded) {
    if (lep_pass_VVV_cutbased_tight_noiso_branch != 0) {
      lep_pass_VVV_cutbased_tight_noiso_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_tight_noiso_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_tight_noiso_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_tight_noiso_;
}

const vector<int> &wwwtree::lep_pass_VVV_cutbased_veto_noiso() {
  if (not lep_pass_VVV_cutbased_veto_noiso_isLoaded) {
    if (lep_pass_VVV_cutbased_veto_noiso_branch != 0) {
      lep_pass_VVV_cutbased_veto_noiso_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_VVV_cutbased_veto_noiso_branch does not exist!\n");
      exit(1);
    }
    lep_pass_VVV_cutbased_veto_noiso_isLoaded = true;
  }
  return *lep_pass_VVV_cutbased_veto_noiso_;
}

const vector<int> &wwwtree::lep_pass_POG_veto() {
  if (not lep_pass_POG_veto_isLoaded) {
    if (lep_pass_POG_veto_branch != 0) {
      lep_pass_POG_veto_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_POG_veto_branch does not exist!\n");
      exit(1);
    }
    lep_pass_POG_veto_isLoaded = true;
  }
  return *lep_pass_POG_veto_;
}

const vector<int> &wwwtree::lep_pass_POG_loose() {
  if (not lep_pass_POG_loose_isLoaded) {
    if (lep_pass_POG_loose_branch != 0) {
      lep_pass_POG_loose_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_POG_loose_branch does not exist!\n");
      exit(1);
    }
    lep_pass_POG_loose_isLoaded = true;
  }
  return *lep_pass_POG_loose_;
}

const vector<int> &wwwtree::lep_pass_POG_medium() {
  if (not lep_pass_POG_medium_isLoaded) {
    if (lep_pass_POG_medium_branch != 0) {
      lep_pass_POG_medium_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_POG_medium_branch does not exist!\n");
      exit(1);
    }
    lep_pass_POG_medium_isLoaded = true;
  }
  return *lep_pass_POG_medium_;
}

const vector<int> &wwwtree::lep_pass_POG_tight() {
  if (not lep_pass_POG_tight_isLoaded) {
    if (lep_pass_POG_tight_branch != 0) {
      lep_pass_POG_tight_branch->GetEntry(index);
    } else {
      printf("branch lep_pass_POG_tight_branch does not exist!\n");
      exit(1);
    }
    lep_pass_POG_tight_isLoaded = true;
  }
  return *lep_pass_POG_tight_;
}

const vector<int> &wwwtree::lep_pdgId() {
  if (not lep_pdgId_isLoaded) {
    if (lep_pdgId_branch != 0) {
      lep_pdgId_branch->GetEntry(index);
    } else {
      printf("branch lep_pdgId_branch does not exist!\n");
      exit(1);
    }
    lep_pdgId_isLoaded = true;
  }
  return *lep_pdgId_;
}

const vector<float> &wwwtree::lep_dxy() {
  if (not lep_dxy_isLoaded) {
    if (lep_dxy_branch != 0) {
      lep_dxy_branch->GetEntry(index);
    } else {
      printf("branch lep_dxy_branch does not exist!\n");
      exit(1);
    }
    lep_dxy_isLoaded = true;
  }
  return *lep_dxy_;
}

const vector<float> &wwwtree::lep_dz() {
  if (not lep_dz_isLoaded) {
    if (lep_dz_branch != 0) {
      lep_dz_branch->GetEntry(index);
    } else {
      printf("branch lep_dz_branch does not exist!\n");
      exit(1);
    }
    lep_dz_isLoaded = true;
  }
  return *lep_dz_;
}

const vector<float> &wwwtree::lep_pterr() {
  if (not lep_pterr_isLoaded) {
    if (lep_pterr_branch != 0) {
      lep_pterr_branch->GetEntry(index);
    } else {
      printf("branch lep_pterr_branch does not exist!\n");
      exit(1);
    }
    lep_pterr_isLoaded = true;
  }
  return *lep_pterr_;
}

const vector<float> &wwwtree::lep_relIso04DB() {
  if (not lep_relIso04DB_isLoaded) {
    if (lep_relIso04DB_branch != 0) {
      lep_relIso04DB_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso04DB_branch does not exist!\n");
      exit(1);
    }
    lep_relIso04DB_isLoaded = true;
  }
  return *lep_relIso04DB_;
}

const vector<float> &wwwtree::lep_relIso03EA() {
  if (not lep_relIso03EA_isLoaded) {
    if (lep_relIso03EA_branch != 0) {
      lep_relIso03EA_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso03EA_branch does not exist!\n");
      exit(1);
    }
    lep_relIso03EA_isLoaded = true;
  }
  return *lep_relIso03EA_;
}

const vector<float> &wwwtree::lep_relIso03EALep() {
  if (not lep_relIso03EALep_isLoaded) {
    if (lep_relIso03EALep_branch != 0) {
      lep_relIso03EALep_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso03EALep_branch does not exist!\n");
      exit(1);
    }
    lep_relIso03EALep_isLoaded = true;
  }
  return *lep_relIso03EALep_;
}

const vector<float> &wwwtree::lep_relIso03EAv2() {
  if (not lep_relIso03EAv2_isLoaded) {
    if (lep_relIso03EAv2_branch != 0) {
      lep_relIso03EAv2_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso03EAv2_branch does not exist!\n");
      exit(1);
    }
    lep_relIso03EAv2_isLoaded = true;
  }
  return *lep_relIso03EAv2_;
}

const vector<float> &wwwtree::lep_relIso04EAv2() {
  if (not lep_relIso04EAv2_isLoaded) {
    if (lep_relIso04EAv2_branch != 0) {
      lep_relIso04EAv2_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso04EAv2_branch does not exist!\n");
      exit(1);
    }
    lep_relIso04EAv2_isLoaded = true;
  }
  return *lep_relIso04EAv2_;
}

const vector<float> &wwwtree::lep_relIso03EAv2Lep() {
  if (not lep_relIso03EAv2Lep_isLoaded) {
    if (lep_relIso03EAv2Lep_branch != 0) {
      lep_relIso03EAv2Lep_branch->GetEntry(index);
    } else {
      printf("branch lep_relIso03EAv2Lep_branch does not exist!\n");
      exit(1);
    }
    lep_relIso03EAv2Lep_isLoaded = true;
  }
  return *lep_relIso03EAv2Lep_;
}

const vector<int> &wwwtree::lep_tightCharge() {
  if (not lep_tightCharge_isLoaded) {
    if (lep_tightCharge_branch != 0) {
      lep_tightCharge_branch->GetEntry(index);
    } else {
      printf("branch lep_tightCharge_branch does not exist!\n");
      exit(1);
    }
    lep_tightCharge_isLoaded = true;
  }
  return *lep_tightCharge_;
}

const vector<float> &wwwtree::lep_trk_pt() {
  if (not lep_trk_pt_isLoaded) {
    if (lep_trk_pt_branch != 0) {
      lep_trk_pt_branch->GetEntry(index);
    } else {
      printf("branch lep_trk_pt_branch does not exist!\n");
      exit(1);
    }
    lep_trk_pt_isLoaded = true;
  }
  return *lep_trk_pt_;
}

const vector<int> &wwwtree::lep_charge() {
  if (not lep_charge_isLoaded) {
    if (lep_charge_branch != 0) {
      lep_charge_branch->GetEntry(index);
    } else {
      printf("branch lep_charge_branch does not exist!\n");
      exit(1);
    }
    lep_charge_isLoaded = true;
  }
  return *lep_charge_;
}

const vector<float> &wwwtree::lep_etaSC() {
  if (not lep_etaSC_isLoaded) {
    if (lep_etaSC_branch != 0) {
      lep_etaSC_branch->GetEntry(index);
    } else {
      printf("branch lep_etaSC_branch does not exist!\n");
      exit(1);
    }
    lep_etaSC_isLoaded = true;
  }
  return *lep_etaSC_;
}

const vector<float> &wwwtree::lep_MVA() {
  if (not lep_MVA_isLoaded) {
    if (lep_MVA_branch != 0) {
      lep_MVA_branch->GetEntry(index);
    } else {
      printf("branch lep_MVA_branch does not exist!\n");
      exit(1);
    }
    lep_MVA_isLoaded = true;
  }
  return *lep_MVA_;
}

const vector<int> &wwwtree::lep_isMediumPOG() {
  if (not lep_isMediumPOG_isLoaded) {
    if (lep_isMediumPOG_branch != 0) {
      lep_isMediumPOG_branch->GetEntry(index);
    } else {
      printf("branch lep_isMediumPOG_branch does not exist!\n");
      exit(1);
    }
    lep_isMediumPOG_isLoaded = true;
  }
  return *lep_isMediumPOG_;
}

const vector<int> &wwwtree::lep_isTightPOG() {
  if (not lep_isTightPOG_isLoaded) {
    if (lep_isTightPOG_branch != 0) {
      lep_isTightPOG_branch->GetEntry(index);
    } else {
      printf("branch lep_isTightPOG_branch does not exist!\n");
      exit(1);
    }
    lep_isTightPOG_isLoaded = true;
  }
  return *lep_isTightPOG_;
}

const vector<int> &wwwtree::lep_isFromW() {
  if (not lep_isFromW_isLoaded) {
    if (lep_isFromW_branch != 0) {
      lep_isFromW_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromW_branch does not exist!\n");
      exit(1);
    }
    lep_isFromW_isLoaded = true;
  }
  return *lep_isFromW_;
}

const vector<int> &wwwtree::lep_isFromZ() {
  if (not lep_isFromZ_isLoaded) {
    if (lep_isFromZ_branch != 0) {
      lep_isFromZ_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromZ_branch does not exist!\n");
      exit(1);
    }
    lep_isFromZ_isLoaded = true;
  }
  return *lep_isFromZ_;
}

const vector<int> &wwwtree::lep_isFromB() {
  if (not lep_isFromB_isLoaded) {
    if (lep_isFromB_branch != 0) {
      lep_isFromB_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromB_branch does not exist!\n");
      exit(1);
    }
    lep_isFromB_isLoaded = true;
  }
  return *lep_isFromB_;
}

const vector<int> &wwwtree::lep_isFromC() {
  if (not lep_isFromC_isLoaded) {
    if (lep_isFromC_branch != 0) {
      lep_isFromC_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromC_branch does not exist!\n");
      exit(1);
    }
    lep_isFromC_isLoaded = true;
  }
  return *lep_isFromC_;
}

const vector<int> &wwwtree::lep_isFromL() {
  if (not lep_isFromL_isLoaded) {
    if (lep_isFromL_branch != 0) {
      lep_isFromL_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromL_branch does not exist!\n");
      exit(1);
    }
    lep_isFromL_isLoaded = true;
  }
  return *lep_isFromL_;
}

const vector<int> &wwwtree::lep_isFromLF() {
  if (not lep_isFromLF_isLoaded) {
    if (lep_isFromLF_branch != 0) {
      lep_isFromLF_branch->GetEntry(index);
    } else {
      printf("branch lep_isFromLF_branch does not exist!\n");
      exit(1);
    }
    lep_isFromLF_isLoaded = true;
  }
  return *lep_isFromLF_;
}

const vector<int> &wwwtree::lep_genPart_index() {
  if (not lep_genPart_index_isLoaded) {
    if (lep_genPart_index_branch != 0) {
      lep_genPart_index_branch->GetEntry(index);
    } else {
      printf("branch lep_genPart_index_branch does not exist!\n");
      exit(1);
    }
    lep_genPart_index_isLoaded = true;
  }
  return *lep_genPart_index_;
}

const vector<float> &wwwtree::lep_r9() {
  if (not lep_r9_isLoaded) {
    if (lep_r9_branch != 0) {
      lep_r9_branch->GetEntry(index);
    } else {
      printf("branch lep_r9_branch does not exist!\n");
      exit(1);
    }
    lep_r9_isLoaded = true;
  }
  return *lep_r9_;
}

const vector<int> &wwwtree::lep_nlayers() {
  if (not lep_nlayers_isLoaded) {
    if (lep_nlayers_branch != 0) {
      lep_nlayers_branch->GetEntry(index);
    } else {
      printf("branch lep_nlayers_branch does not exist!\n");
      exit(1);
    }
    lep_nlayers_isLoaded = true;
  }
  return *lep_nlayers_;
}

const float &wwwtree::el_pt() {
  if (not el_pt_isLoaded) {
    if (el_pt_branch != 0) {
      el_pt_branch->GetEntry(index);
    } else {
      printf("branch el_pt_branch does not exist!\n");
      exit(1);
    }
    el_pt_isLoaded = true;
  }
  return el_pt_;
}

const float &wwwtree::el_eta() {
  if (not el_eta_isLoaded) {
    if (el_eta_branch != 0) {
      el_eta_branch->GetEntry(index);
    } else {
      printf("branch el_eta_branch does not exist!\n");
      exit(1);
    }
    el_eta_isLoaded = true;
  }
  return el_eta_;
}

const float &wwwtree::el_phi() {
  if (not el_phi_isLoaded) {
    if (el_phi_branch != 0) {
      el_phi_branch->GetEntry(index);
    } else {
      printf("branch el_phi_branch does not exist!\n");
      exit(1);
    }
    el_phi_isLoaded = true;
  }
  return el_phi_;
}

const float &wwwtree::el_relIso03EA() {
  if (not el_relIso03EA_isLoaded) {
    if (el_relIso03EA_branch != 0) {
      el_relIso03EA_branch->GetEntry(index);
    } else {
      printf("branch el_relIso03EA_branch does not exist!\n");
      exit(1);
    }
    el_relIso03EA_isLoaded = true;
  }
  return el_relIso03EA_;
}

const float &wwwtree::el_relIso03EALep() {
  if (not el_relIso03EALep_isLoaded) {
    if (el_relIso03EALep_branch != 0) {
      el_relIso03EALep_branch->GetEntry(index);
    } else {
      printf("branch el_relIso03EALep_branch does not exist!\n");
      exit(1);
    }
    el_relIso03EALep_isLoaded = true;
  }
  return el_relIso03EALep_;
}

const float &wwwtree::el_ip3d() {
  if (not el_ip3d_isLoaded) {
    if (el_ip3d_branch != 0) {
      el_ip3d_branch->GetEntry(index);
    } else {
      printf("branch el_ip3d_branch does not exist!\n");
      exit(1);
    }
    el_ip3d_isLoaded = true;
  }
  return el_ip3d_;
}

const float &wwwtree::mu_pt() {
  if (not mu_pt_isLoaded) {
    if (mu_pt_branch != 0) {
      mu_pt_branch->GetEntry(index);
    } else {
      printf("branch mu_pt_branch does not exist!\n");
      exit(1);
    }
    mu_pt_isLoaded = true;
  }
  return mu_pt_;
}

const float &wwwtree::mu_eta() {
  if (not mu_eta_isLoaded) {
    if (mu_eta_branch != 0) {
      mu_eta_branch->GetEntry(index);
    } else {
      printf("branch mu_eta_branch does not exist!\n");
      exit(1);
    }
    mu_eta_isLoaded = true;
  }
  return mu_eta_;
}

const float &wwwtree::mu_phi() {
  if (not mu_phi_isLoaded) {
    if (mu_phi_branch != 0) {
      mu_phi_branch->GetEntry(index);
    } else {
      printf("branch mu_phi_branch does not exist!\n");
      exit(1);
    }
    mu_phi_isLoaded = true;
  }
  return mu_phi_;
}

const float &wwwtree::mu_relIso04DB() {
  if (not mu_relIso04DB_isLoaded) {
    if (mu_relIso04DB_branch != 0) {
      mu_relIso04DB_branch->GetEntry(index);
    } else {
      printf("branch mu_relIso04DB_branch does not exist!\n");
      exit(1);
    }
    mu_relIso04DB_isLoaded = true;
  }
  return mu_relIso04DB_;
}

const float &wwwtree::mu_relIso03EA() {
  if (not mu_relIso03EA_isLoaded) {
    if (mu_relIso03EA_branch != 0) {
      mu_relIso03EA_branch->GetEntry(index);
    } else {
      printf("branch mu_relIso03EA_branch does not exist!\n");
      exit(1);
    }
    mu_relIso03EA_isLoaded = true;
  }
  return mu_relIso03EA_;
}

const float &wwwtree::mu_relIso03EALep() {
  if (not mu_relIso03EALep_isLoaded) {
    if (mu_relIso03EALep_branch != 0) {
      mu_relIso03EALep_branch->GetEntry(index);
    } else {
      printf("branch mu_relIso03EALep_branch does not exist!\n");
      exit(1);
    }
    mu_relIso03EALep_isLoaded = true;
  }
  return mu_relIso03EALep_;
}

const float &wwwtree::mu_ip3d() {
  if (not mu_ip3d_isLoaded) {
    if (mu_ip3d_branch != 0) {
      mu_ip3d_branch->GetEntry(index);
    } else {
      printf("branch mu_ip3d_branch does not exist!\n");
      exit(1);
    }
    mu_ip3d_isLoaded = true;
  }
  return mu_ip3d_;
}

const float &wwwtree::lbnt_pt() {
  if (not lbnt_pt_isLoaded) {
    if (lbnt_pt_branch != 0) {
      lbnt_pt_branch->GetEntry(index);
    } else {
      printf("branch lbnt_pt_branch does not exist!\n");
      exit(1);
    }
    lbnt_pt_isLoaded = true;
  }
  return lbnt_pt_;
}

const float &wwwtree::lbnt_coneCorrPt() {
  if (not lbnt_coneCorrPt_isLoaded) {
    if (lbnt_coneCorrPt_branch != 0) {
      lbnt_coneCorrPt_branch->GetEntry(index);
    } else {
      printf("branch lbnt_coneCorrPt_branch does not exist!\n");
      exit(1);
    }
    lbnt_coneCorrPt_isLoaded = true;
  }
  return lbnt_coneCorrPt_;
}

const float &wwwtree::lbnt_abseta() {
  if (not lbnt_abseta_isLoaded) {
    if (lbnt_abseta_branch != 0) {
      lbnt_abseta_branch->GetEntry(index);
    } else {
      printf("branch lbnt_abseta_branch does not exist!\n");
      exit(1);
    }
    lbnt_abseta_isLoaded = true;
  }
  return lbnt_abseta_;
}

const float &wwwtree::lbnt_pdgId() {
  if (not lbnt_pdgId_isLoaded) {
    if (lbnt_pdgId_branch != 0) {
      lbnt_pdgId_branch->GetEntry(index);
    } else {
      printf("branch lbnt_pdgId_branch does not exist!\n");
      exit(1);
    }
    lbnt_pdgId_isLoaded = true;
  }
  return lbnt_pdgId_;
}

const float &wwwtree::lbnt_el_pt() {
  if (not lbnt_el_pt_isLoaded) {
    if (lbnt_el_pt_branch != 0) {
      lbnt_el_pt_branch->GetEntry(index);
    } else {
      printf("branch lbnt_el_pt_branch does not exist!\n");
      exit(1);
    }
    lbnt_el_pt_isLoaded = true;
  }
  return lbnt_el_pt_;
}

const float &wwwtree::lbnt_el_coneCorrPt() {
  if (not lbnt_el_coneCorrPt_isLoaded) {
    if (lbnt_el_coneCorrPt_branch != 0) {
      lbnt_el_coneCorrPt_branch->GetEntry(index);
    } else {
      printf("branch lbnt_el_coneCorrPt_branch does not exist!\n");
      exit(1);
    }
    lbnt_el_coneCorrPt_isLoaded = true;
  }
  return lbnt_el_coneCorrPt_;
}

const float &wwwtree::lbnt_el_abseta() {
  if (not lbnt_el_abseta_isLoaded) {
    if (lbnt_el_abseta_branch != 0) {
      lbnt_el_abseta_branch->GetEntry(index);
    } else {
      printf("branch lbnt_el_abseta_branch does not exist!\n");
      exit(1);
    }
    lbnt_el_abseta_isLoaded = true;
  }
  return lbnt_el_abseta_;
}

const float &wwwtree::lbnt_mu_pt() {
  if (not lbnt_mu_pt_isLoaded) {
    if (lbnt_mu_pt_branch != 0) {
      lbnt_mu_pt_branch->GetEntry(index);
    } else {
      printf("branch lbnt_mu_pt_branch does not exist!\n");
      exit(1);
    }
    lbnt_mu_pt_isLoaded = true;
  }
  return lbnt_mu_pt_;
}

const float &wwwtree::lbnt_mu_coneCorrPt() {
  if (not lbnt_mu_coneCorrPt_isLoaded) {
    if (lbnt_mu_coneCorrPt_branch != 0) {
      lbnt_mu_coneCorrPt_branch->GetEntry(index);
    } else {
      printf("branch lbnt_mu_coneCorrPt_branch does not exist!\n");
      exit(1);
    }
    lbnt_mu_coneCorrPt_isLoaded = true;
  }
  return lbnt_mu_coneCorrPt_;
}

const float &wwwtree::lbnt_mu_abseta() {
  if (not lbnt_mu_abseta_isLoaded) {
    if (lbnt_mu_abseta_branch != 0) {
      lbnt_mu_abseta_branch->GetEntry(index);
    } else {
      printf("branch lbnt_mu_abseta_branch does not exist!\n");
      exit(1);
    }
    lbnt_mu_abseta_isLoaded = true;
  }
  return lbnt_mu_abseta_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &wwwtree::jets_p4() {
  if (not jets_p4_isLoaded) {
    if (jets_p4_branch != 0) {
      jets_p4_branch->GetEntry(index);
    } else {
      printf("branch jets_p4_branch does not exist!\n");
      exit(1);
    }
    jets_p4_isLoaded = true;
  }
  return *jets_p4_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &wwwtree::jets_up_p4() {
  if (not jets_up_p4_isLoaded) {
    if (jets_up_p4_branch != 0) {
      jets_up_p4_branch->GetEntry(index);
    } else {
      printf("branch jets_up_p4_branch does not exist!\n");
      exit(1);
    }
    jets_up_p4_isLoaded = true;
  }
  return *jets_up_p4_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &wwwtree::jets_dn_p4() {
  if (not jets_dn_p4_isLoaded) {
    if (jets_dn_p4_branch != 0) {
      jets_dn_p4_branch->GetEntry(index);
    } else {
      printf("branch jets_dn_p4_branch does not exist!\n");
      exit(1);
    }
    jets_dn_p4_isLoaded = true;
  }
  return *jets_dn_p4_;
}

const vector<float> &wwwtree::jets_csv() {
  if (not jets_csv_isLoaded) {
    if (jets_csv_branch != 0) {
      jets_csv_branch->GetEntry(index);
    } else {
      printf("branch jets_csv_branch does not exist!\n");
      exit(1);
    }
    jets_csv_isLoaded = true;
  }
  return *jets_csv_;
}

const vector<float> &wwwtree::jets_up_csv() {
  if (not jets_up_csv_isLoaded) {
    if (jets_up_csv_branch != 0) {
      jets_up_csv_branch->GetEntry(index);
    } else {
      printf("branch jets_up_csv_branch does not exist!\n");
      exit(1);
    }
    jets_up_csv_isLoaded = true;
  }
  return *jets_up_csv_;
}

const vector<float> &wwwtree::jets_dn_csv() {
  if (not jets_dn_csv_isLoaded) {
    if (jets_dn_csv_branch != 0) {
      jets_dn_csv_branch->GetEntry(index);
    } else {
      printf("branch jets_dn_csv_branch does not exist!\n");
      exit(1);
    }
    jets_dn_csv_isLoaded = true;
  }
  return *jets_dn_csv_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &wwwtree::ak8jets_p4() {
  if (not ak8jets_p4_isLoaded) {
    if (ak8jets_p4_branch != 0) {
      ak8jets_p4_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_p4_branch does not exist!\n");
      exit(1);
    }
    ak8jets_p4_isLoaded = true;
  }
  return *ak8jets_p4_;
}

const vector<float> &wwwtree::ak8jets_softdropMass() {
  if (not ak8jets_softdropMass_isLoaded) {
    if (ak8jets_softdropMass_branch != 0) {
      ak8jets_softdropMass_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_softdropMass_branch does not exist!\n");
      exit(1);
    }
    ak8jets_softdropMass_isLoaded = true;
  }
  return *ak8jets_softdropMass_;
}

const vector<float> &wwwtree::ak8jets_prunedMass() {
  if (not ak8jets_prunedMass_isLoaded) {
    if (ak8jets_prunedMass_branch != 0) {
      ak8jets_prunedMass_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_prunedMass_branch does not exist!\n");
      exit(1);
    }
    ak8jets_prunedMass_isLoaded = true;
  }
  return *ak8jets_prunedMass_;
}

const vector<float> &wwwtree::ak8jets_trimmedMass() {
  if (not ak8jets_trimmedMass_isLoaded) {
    if (ak8jets_trimmedMass_branch != 0) {
      ak8jets_trimmedMass_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_trimmedMass_branch does not exist!\n");
      exit(1);
    }
    ak8jets_trimmedMass_isLoaded = true;
  }
  return *ak8jets_trimmedMass_;
}

const vector<float> &wwwtree::ak8jets_mass() {
  if (not ak8jets_mass_isLoaded) {
    if (ak8jets_mass_branch != 0) {
      ak8jets_mass_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_mass_branch does not exist!\n");
      exit(1);
    }
    ak8jets_mass_isLoaded = true;
  }
  return *ak8jets_mass_;
}

const vector<float> &wwwtree::ak8jets_nJettinessTau1() {
  if (not ak8jets_nJettinessTau1_isLoaded) {
    if (ak8jets_nJettinessTau1_branch != 0) {
      ak8jets_nJettinessTau1_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_nJettinessTau1_branch does not exist!\n");
      exit(1);
    }
    ak8jets_nJettinessTau1_isLoaded = true;
  }
  return *ak8jets_nJettinessTau1_;
}

const vector<float> &wwwtree::ak8jets_nJettinessTau2() {
  if (not ak8jets_nJettinessTau2_isLoaded) {
    if (ak8jets_nJettinessTau2_branch != 0) {
      ak8jets_nJettinessTau2_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_nJettinessTau2_branch does not exist!\n");
      exit(1);
    }
    ak8jets_nJettinessTau2_isLoaded = true;
  }
  return *ak8jets_nJettinessTau2_;
}

const vector<float> &wwwtree::ak8jets_softdropPuppiSubjet1() {
  if (not ak8jets_softdropPuppiSubjet1_isLoaded) {
    if (ak8jets_softdropPuppiSubjet1_branch != 0) {
      ak8jets_softdropPuppiSubjet1_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_softdropPuppiSubjet1_branch does not exist!\n");
      exit(1);
    }
    ak8jets_softdropPuppiSubjet1_isLoaded = true;
  }
  return *ak8jets_softdropPuppiSubjet1_;
}

const vector<float> &wwwtree::ak8jets_softdropPuppiSubjet2() {
  if (not ak8jets_softdropPuppiSubjet2_isLoaded) {
    if (ak8jets_softdropPuppiSubjet2_branch != 0) {
      ak8jets_softdropPuppiSubjet2_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_softdropPuppiSubjet2_branch does not exist!\n");
      exit(1);
    }
    ak8jets_softdropPuppiSubjet2_isLoaded = true;
  }
  return *ak8jets_softdropPuppiSubjet2_;
}

const vector<float> &wwwtree::ak8jets_puppi_softdropMass() {
  if (not ak8jets_puppi_softdropMass_isLoaded) {
    if (ak8jets_puppi_softdropMass_branch != 0) {
      ak8jets_puppi_softdropMass_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_softdropMass_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_softdropMass_isLoaded = true;
  }
  return *ak8jets_puppi_softdropMass_;
}

const vector<float> &wwwtree::ak8jets_puppi_nJettinessTau1() {
  if (not ak8jets_puppi_nJettinessTau1_isLoaded) {
    if (ak8jets_puppi_nJettinessTau1_branch != 0) {
      ak8jets_puppi_nJettinessTau1_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_nJettinessTau1_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_nJettinessTau1_isLoaded = true;
  }
  return *ak8jets_puppi_nJettinessTau1_;
}

const vector<float> &wwwtree::ak8jets_puppi_nJettinessTau2() {
  if (not ak8jets_puppi_nJettinessTau2_isLoaded) {
    if (ak8jets_puppi_nJettinessTau2_branch != 0) {
      ak8jets_puppi_nJettinessTau2_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_nJettinessTau2_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_nJettinessTau2_isLoaded = true;
  }
  return *ak8jets_puppi_nJettinessTau2_;
}

const vector<float> &wwwtree::ak8jets_puppi_eta() {
  if (not ak8jets_puppi_eta_isLoaded) {
    if (ak8jets_puppi_eta_branch != 0) {
      ak8jets_puppi_eta_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_eta_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_eta_isLoaded = true;
  }
  return *ak8jets_puppi_eta_;
}

const vector<float> &wwwtree::ak8jets_puppi_phi() {
  if (not ak8jets_puppi_phi_isLoaded) {
    if (ak8jets_puppi_phi_branch != 0) {
      ak8jets_puppi_phi_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_phi_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_phi_isLoaded = true;
  }
  return *ak8jets_puppi_phi_;
}

const vector<float> &wwwtree::ak8jets_puppi_pt() {
  if (not ak8jets_puppi_pt_isLoaded) {
    if (ak8jets_puppi_pt_branch != 0) {
      ak8jets_puppi_pt_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_pt_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_pt_isLoaded = true;
  }
  return *ak8jets_puppi_pt_;
}

const vector<float> &wwwtree::ak8jets_puppi_mass() {
  if (not ak8jets_puppi_mass_isLoaded) {
    if (ak8jets_puppi_mass_branch != 0) {
      ak8jets_puppi_mass_branch->GetEntry(index);
    } else {
      printf("branch ak8jets_puppi_mass_branch does not exist!\n");
      exit(1);
    }
    ak8jets_puppi_mass_isLoaded = true;
  }
  return *ak8jets_puppi_mass_;
}

const float &wwwtree::met_pt() {
  if (not met_pt_isLoaded) {
    if (met_pt_branch != 0) {
      met_pt_branch->GetEntry(index);
    } else {
      printf("branch met_pt_branch does not exist!\n");
      exit(1);
    }
    met_pt_isLoaded = true;
  }
  return met_pt_;
}

const float &wwwtree::met_phi() {
  if (not met_phi_isLoaded) {
    if (met_phi_branch != 0) {
      met_phi_branch->GetEntry(index);
    } else {
      printf("branch met_phi_branch does not exist!\n");
      exit(1);
    }
    met_phi_isLoaded = true;
  }
  return met_phi_;
}

const float &wwwtree::met_up_pt() {
  if (not met_up_pt_isLoaded) {
    if (met_up_pt_branch != 0) {
      met_up_pt_branch->GetEntry(index);
    } else {
      printf("branch met_up_pt_branch does not exist!\n");
      exit(1);
    }
    met_up_pt_isLoaded = true;
  }
  return met_up_pt_;
}

const float &wwwtree::met_up_phi() {
  if (not met_up_phi_isLoaded) {
    if (met_up_phi_branch != 0) {
      met_up_phi_branch->GetEntry(index);
    } else {
      printf("branch met_up_phi_branch does not exist!\n");
      exit(1);
    }
    met_up_phi_isLoaded = true;
  }
  return met_up_phi_;
}

const float &wwwtree::met_dn_pt() {
  if (not met_dn_pt_isLoaded) {
    if (met_dn_pt_branch != 0) {
      met_dn_pt_branch->GetEntry(index);
    } else {
      printf("branch met_dn_pt_branch does not exist!\n");
      exit(1);
    }
    met_dn_pt_isLoaded = true;
  }
  return met_dn_pt_;
}

const float &wwwtree::met_dn_phi() {
  if (not met_dn_phi_isLoaded) {
    if (met_dn_phi_branch != 0) {
      met_dn_phi_branch->GetEntry(index);
    } else {
      printf("branch met_dn_phi_branch does not exist!\n");
      exit(1);
    }
    met_dn_phi_isLoaded = true;
  }
  return met_dn_phi_;
}

const float &wwwtree::met_gen_pt() {
  if (not met_gen_pt_isLoaded) {
    if (met_gen_pt_branch != 0) {
      met_gen_pt_branch->GetEntry(index);
    } else {
      printf("branch met_gen_pt_branch does not exist!\n");
      exit(1);
    }
    met_gen_pt_isLoaded = true;
  }
  return met_gen_pt_;
}

const float &wwwtree::met_gen_phi() {
  if (not met_gen_phi_isLoaded) {
    if (met_gen_phi_branch != 0) {
      met_gen_phi_branch->GetEntry(index);
    } else {
      printf("branch met_gen_phi_branch does not exist!\n");
      exit(1);
    }
    met_gen_phi_isLoaded = true;
  }
  return met_gen_phi_;
}

const int &wwwtree::firstgoodvertex() {
  if (not firstgoodvertex_isLoaded) {
    if (firstgoodvertex_branch != 0) {
      firstgoodvertex_branch->GetEntry(index);
    } else {
      printf("branch firstgoodvertex_branch does not exist!\n");
      exit(1);
    }
    firstgoodvertex_isLoaded = true;
  }
  return firstgoodvertex_;
}

const int &wwwtree::nTrueInt() {
  if (not nTrueInt_isLoaded) {
    if (nTrueInt_branch != 0) {
      nTrueInt_branch->GetEntry(index);
    } else {
      printf("branch nTrueInt_branch does not exist!\n");
      exit(1);
    }
    nTrueInt_isLoaded = true;
  }
  return nTrueInt_;
}

const int &wwwtree::nVert() {
  if (not nVert_isLoaded) {
    if (nVert_branch != 0) {
      nVert_branch->GetEntry(index);
    } else {
      printf("branch nVert_branch does not exist!\n");
      exit(1);
    }
    nVert_isLoaded = true;
  }
  return nVert_;
}

const int &wwwtree::nisoTrack_mt2_cleaned_VVV_cutbased_veto() {
  if (not nisoTrack_mt2_cleaned_VVV_cutbased_veto_isLoaded) {
    if (nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch != 0) {
      nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch->GetEntry(index);
    } else {
      printf("branch nisoTrack_mt2_cleaned_VVV_cutbased_veto_branch does not exist!\n");
      exit(1);
    }
    nisoTrack_mt2_cleaned_VVV_cutbased_veto_isLoaded = true;
  }
  return nisoTrack_mt2_cleaned_VVV_cutbased_veto_;
}

const float &wwwtree::weight_btagsf() {
  if (not weight_btagsf_isLoaded) {
    if (weight_btagsf_branch != 0) {
      weight_btagsf_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_isLoaded = true;
  }
  return weight_btagsf_;
}

const float &wwwtree::weight_btagsf_heavy_DN() {
  if (not weight_btagsf_heavy_DN_isLoaded) {
    if (weight_btagsf_heavy_DN_branch != 0) {
      weight_btagsf_heavy_DN_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_heavy_DN_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_heavy_DN_isLoaded = true;
  }
  return weight_btagsf_heavy_DN_;
}

const float &wwwtree::weight_btagsf_heavy_UP() {
  if (not weight_btagsf_heavy_UP_isLoaded) {
    if (weight_btagsf_heavy_UP_branch != 0) {
      weight_btagsf_heavy_UP_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_heavy_UP_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_heavy_UP_isLoaded = true;
  }
  return weight_btagsf_heavy_UP_;
}

const float &wwwtree::weight_btagsf_light_DN() {
  if (not weight_btagsf_light_DN_isLoaded) {
    if (weight_btagsf_light_DN_branch != 0) {
      weight_btagsf_light_DN_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_light_DN_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_light_DN_isLoaded = true;
  }
  return weight_btagsf_light_DN_;
}

const float &wwwtree::weight_btagsf_light_UP() {
  if (not weight_btagsf_light_UP_isLoaded) {
    if (weight_btagsf_light_UP_branch != 0) {
      weight_btagsf_light_UP_branch->GetEntry(index);
    } else {
      printf("branch weight_btagsf_light_UP_branch does not exist!\n");
      exit(1);
    }
    weight_btagsf_light_UP_isLoaded = true;
  }
  return weight_btagsf_light_UP_;
}

const float &wwwtree::gen_ht() {
  if (not gen_ht_isLoaded) {
    if (gen_ht_branch != 0) {
      gen_ht_branch->GetEntry(index);
    } else {
      printf("branch gen_ht_branch does not exist!\n");
      exit(1);
    }
    gen_ht_isLoaded = true;
  }
  return gen_ht_;
}

const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &wwwtree::genPart_p4() {
  if (not genPart_p4_isLoaded) {
    if (genPart_p4_branch != 0) {
      genPart_p4_branch->GetEntry(index);
    } else {
      printf("branch genPart_p4_branch does not exist!\n");
      exit(1);
    }
    genPart_p4_isLoaded = true;
  }
  return *genPart_p4_;
}

const vector<int> &wwwtree::genPart_motherId() {
  if (not genPart_motherId_isLoaded) {
    if (genPart_motherId_branch != 0) {
      genPart_motherId_branch->GetEntry(index);
    } else {
      printf("branch genPart_motherId_branch does not exist!\n");
      exit(1);
    }
    genPart_motherId_isLoaded = true;
  }
  return *genPart_motherId_;
}

const vector<int> &wwwtree::genPart_pdgId() {
  if (not genPart_pdgId_isLoaded) {
    if (genPart_pdgId_branch != 0) {
      genPart_pdgId_branch->GetEntry(index);
    } else {
      printf("branch genPart_pdgId_branch does not exist!\n");
      exit(1);
    }
    genPart_pdgId_isLoaded = true;
  }
  return *genPart_pdgId_;
}

const vector<int> &wwwtree::genPart_charge() {
  if (not genPart_charge_isLoaded) {
    if (genPart_charge_branch != 0) {
      genPart_charge_branch->GetEntry(index);
    } else {
      printf("branch genPart_charge_branch does not exist!\n");
      exit(1);
    }
    genPart_charge_isLoaded = true;
  }
  return *genPart_charge_;
}

const vector<int> &wwwtree::genPart_status() {
  if (not genPart_status_isLoaded) {
    if (genPart_status_branch != 0) {
      genPart_status_branch->GetEntry(index);
    } else {
      printf("branch genPart_status_branch does not exist!\n");
      exit(1);
    }
    genPart_status_isLoaded = true;
  }
  return *genPart_status_;
}

const int &wwwtree::ngenLep() {
  if (not ngenLep_isLoaded) {
    if (ngenLep_branch != 0) {
      ngenLep_branch->GetEntry(index);
    } else {
      printf("branch ngenLep_branch does not exist!\n");
      exit(1);
    }
    ngenLep_isLoaded = true;
  }
  return ngenLep_;
}

const int &wwwtree::ngenLepFromTau() {
  if (not ngenLepFromTau_isLoaded) {
    if (ngenLepFromTau_branch != 0) {
      ngenLepFromTau_branch->GetEntry(index);
    } else {
      printf("branch ngenLepFromTau_branch does not exist!\n");
      exit(1);
    }
    ngenLepFromTau_isLoaded = true;
  }
  return ngenLepFromTau_;
}

const int &wwwtree::Flag_AllEventFilters() {
  if (not Flag_AllEventFilters_isLoaded) {
    if (Flag_AllEventFilters_branch != 0) {
      Flag_AllEventFilters_branch->GetEntry(index);
    } else {
      printf("branch Flag_AllEventFilters_branch does not exist!\n");
      exit(1);
    }
    Flag_AllEventFilters_isLoaded = true;
  }
  return Flag_AllEventFilters_;
}

const int &wwwtree::Flag_EcalDeadCellTriggerPrimitiveFilter() {
  if (not Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded) {
    if (Flag_EcalDeadCellTriggerPrimitiveFilter_branch != 0) {
      Flag_EcalDeadCellTriggerPrimitiveFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_EcalDeadCellTriggerPrimitiveFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_EcalDeadCellTriggerPrimitiveFilter_isLoaded = true;
  }
  return Flag_EcalDeadCellTriggerPrimitiveFilter_;
}

const int &wwwtree::Flag_HBHEIsoNoiseFilter() {
  if (not Flag_HBHEIsoNoiseFilter_isLoaded) {
    if (Flag_HBHEIsoNoiseFilter_branch != 0) {
      Flag_HBHEIsoNoiseFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_HBHEIsoNoiseFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_HBHEIsoNoiseFilter_isLoaded = true;
  }
  return Flag_HBHEIsoNoiseFilter_;
}

const int &wwwtree::Flag_HBHENoiseFilter() {
  if (not Flag_HBHENoiseFilter_isLoaded) {
    if (Flag_HBHENoiseFilter_branch != 0) {
      Flag_HBHENoiseFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_HBHENoiseFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_HBHENoiseFilter_isLoaded = true;
  }
  return Flag_HBHENoiseFilter_;
}

const int &wwwtree::Flag_badChargedCandidateFilter() {
  if (not Flag_badChargedCandidateFilter_isLoaded) {
    if (Flag_badChargedCandidateFilter_branch != 0) {
      Flag_badChargedCandidateFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_badChargedCandidateFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_badChargedCandidateFilter_isLoaded = true;
  }
  return Flag_badChargedCandidateFilter_;
}

const int &wwwtree::Flag_badMuonFilter() {
  if (not Flag_badMuonFilter_isLoaded) {
    if (Flag_badMuonFilter_branch != 0) {
      Flag_badMuonFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_badMuonFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_badMuonFilter_isLoaded = true;
  }
  return Flag_badMuonFilter_;
}

const int &wwwtree::Flag_badMuonFilterv2() {
  if (not Flag_badMuonFilterv2_isLoaded) {
    if (Flag_badMuonFilterv2_branch != 0) {
      Flag_badMuonFilterv2_branch->GetEntry(index);
    } else {
      printf("branch Flag_badMuonFilterv2_branch does not exist!\n");
      exit(1);
    }
    Flag_badMuonFilterv2_isLoaded = true;
  }
  return Flag_badMuonFilterv2_;
}

const int &wwwtree::Flag_badChargedCandidateFilterv2() {
  if (not Flag_badChargedCandidateFilterv2_isLoaded) {
    if (Flag_badChargedCandidateFilterv2_branch != 0) {
      Flag_badChargedCandidateFilterv2_branch->GetEntry(index);
    } else {
      printf("branch Flag_badChargedCandidateFilterv2_branch does not exist!\n");
      exit(1);
    }
    Flag_badChargedCandidateFilterv2_isLoaded = true;
  }
  return Flag_badChargedCandidateFilterv2_;
}

const int &wwwtree::Flag_eeBadScFilter() {
  if (not Flag_eeBadScFilter_isLoaded) {
    if (Flag_eeBadScFilter_branch != 0) {
      Flag_eeBadScFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_eeBadScFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_eeBadScFilter_isLoaded = true;
  }
  return Flag_eeBadScFilter_;
}

const int &wwwtree::Flag_ecalBadCalibFilter() {
  if (not Flag_ecalBadCalibFilter_isLoaded) {
    if (Flag_ecalBadCalibFilter_branch != 0) {
      Flag_ecalBadCalibFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_ecalBadCalibFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_ecalBadCalibFilter_isLoaded = true;
  }
  return Flag_ecalBadCalibFilter_;
}

const int &wwwtree::Flag_globalTightHalo2016() {
  if (not Flag_globalTightHalo2016_isLoaded) {
    if (Flag_globalTightHalo2016_branch != 0) {
      Flag_globalTightHalo2016_branch->GetEntry(index);
    } else {
      printf("branch Flag_globalTightHalo2016_branch does not exist!\n");
      exit(1);
    }
    Flag_globalTightHalo2016_isLoaded = true;
  }
  return Flag_globalTightHalo2016_;
}

const int &wwwtree::Flag_goodVertices() {
  if (not Flag_goodVertices_isLoaded) {
    if (Flag_goodVertices_branch != 0) {
      Flag_goodVertices_branch->GetEntry(index);
    } else {
      printf("branch Flag_goodVertices_branch does not exist!\n");
      exit(1);
    }
    Flag_goodVertices_isLoaded = true;
  }
  return Flag_goodVertices_;
}

const int &wwwtree::Flag_ecalLaserCorrFilter() {
  if (not Flag_ecalLaserCorrFilter_isLoaded) {
    if (Flag_ecalLaserCorrFilter_branch != 0) {
      Flag_ecalLaserCorrFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_ecalLaserCorrFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_ecalLaserCorrFilter_isLoaded = true;
  }
  return Flag_ecalLaserCorrFilter_;
}

const int &wwwtree::Flag_hcalLaserEventFilter() {
  if (not Flag_hcalLaserEventFilter_isLoaded) {
    if (Flag_hcalLaserEventFilter_branch != 0) {
      Flag_hcalLaserEventFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_hcalLaserEventFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_hcalLaserEventFilter_isLoaded = true;
  }
  return Flag_hcalLaserEventFilter_;
}

const int &wwwtree::Flag_trackingFailureFilter() {
  if (not Flag_trackingFailureFilter_isLoaded) {
    if (Flag_trackingFailureFilter_branch != 0) {
      Flag_trackingFailureFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_trackingFailureFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_trackingFailureFilter_isLoaded = true;
  }
  return Flag_trackingFailureFilter_;
}

const int &wwwtree::Flag_CSCTightHaloFilter() {
  if (not Flag_CSCTightHaloFilter_isLoaded) {
    if (Flag_CSCTightHaloFilter_branch != 0) {
      Flag_CSCTightHaloFilter_branch->GetEntry(index);
    } else {
      printf("branch Flag_CSCTightHaloFilter_branch does not exist!\n");
      exit(1);
    }
    Flag_CSCTightHaloFilter_isLoaded = true;
  }
  return Flag_CSCTightHaloFilter_;
}

const int &wwwtree::Flag_CSCTightHalo2015Filter() {
  if (not Flag_CSCTightHalo2015Filter_isLoaded) {
    if (Flag_CSCTightHalo2015Filter_branch != 0) {
      Flag_CSCTightHalo2015Filter_branch->GetEntry(index);
    } else {
      printf("branch Flag_CSCTightHalo2015Filter_branch does not exist!\n");
      exit(1);
    }
    Flag_CSCTightHalo2015Filter_isLoaded = true;
  }
  return Flag_CSCTightHalo2015Filter_;
}

const int &wwwtree::Flag_badMuons() {
  if (not Flag_badMuons_isLoaded) {
    if (Flag_badMuons_branch != 0) {
      Flag_badMuons_branch->GetEntry(index);
    } else {
      printf("branch Flag_badMuons_branch does not exist!\n");
      exit(1);
    }
    Flag_badMuons_isLoaded = true;
  }
  return Flag_badMuons_;
}

const int &wwwtree::Flag_duplicateMuons() {
  if (not Flag_duplicateMuons_isLoaded) {
    if (Flag_duplicateMuons_branch != 0) {
      Flag_duplicateMuons_branch->GetEntry(index);
    } else {
      printf("branch Flag_duplicateMuons_branch does not exist!\n");
      exit(1);
    }
    Flag_duplicateMuons_isLoaded = true;
  }
  return Flag_duplicateMuons_;
}

const int &wwwtree::Flag_noBadMuons() {
  if (not Flag_noBadMuons_isLoaded) {
    if (Flag_noBadMuons_branch != 0) {
      Flag_noBadMuons_branch->GetEntry(index);
    } else {
      printf("branch Flag_noBadMuons_branch does not exist!\n");
      exit(1);
    }
    Flag_noBadMuons_isLoaded = true;
  }
  return Flag_noBadMuons_;
}

const int &wwwtree::fastsimfilt() {
  if (not fastsimfilt_isLoaded) {
    if (fastsimfilt_branch != 0) {
      fastsimfilt_branch->GetEntry(index);
    } else {
      printf("branch fastsimfilt_branch does not exist!\n");
      exit(1);
    }
    fastsimfilt_isLoaded = true;
  }
  return fastsimfilt_;
}

const int &wwwtree::nVlep() {
  if (not nVlep_isLoaded) {
    if (nVlep_branch != 0) {
      nVlep_branch->GetEntry(index);
    } else {
      printf("branch nVlep_branch does not exist!\n");
      exit(1);
    }
    nVlep_isLoaded = true;
  }
  return nVlep_;
}

const int &wwwtree::nTlep() {
  if (not nTlep_isLoaded) {
    if (nTlep_branch != 0) {
      nTlep_branch->GetEntry(index);
    } else {
      printf("branch nTlep_branch does not exist!\n");
      exit(1);
    }
    nTlep_isLoaded = true;
  }
  return nTlep_;
}

const int &wwwtree::nTlepSS() {
  if (not nTlepSS_isLoaded) {
    if (nTlepSS_branch != 0) {
      nTlepSS_branch->GetEntry(index);
    } else {
      printf("branch nTlepSS_branch does not exist!\n");
      exit(1);
    }
    nTlepSS_isLoaded = true;
  }
  return nTlepSS_;
}

const int &wwwtree::nLlep() {
  if (not nLlep_isLoaded) {
    if (nLlep_branch != 0) {
      nLlep_branch->GetEntry(index);
    } else {
      printf("branch nLlep_branch does not exist!\n");
      exit(1);
    }
    nLlep_isLoaded = true;
  }
  return nLlep_;
}

const int &wwwtree::nSFOS() {
  if (not nSFOS_isLoaded) {
    if (nSFOS_branch != 0) {
      nSFOS_branch->GetEntry(index);
    } else {
      printf("branch nSFOS_branch does not exist!\n");
      exit(1);
    }
    nSFOS_isLoaded = true;
  }
  return nSFOS_;
}

const int &wwwtree::nSFOSinZ() {
  if (not nSFOSinZ_isLoaded) {
    if (nSFOSinZ_branch != 0) {
      nSFOSinZ_branch->GetEntry(index);
    } else {
      printf("branch nSFOSinZ_branch does not exist!\n");
      exit(1);
    }
    nSFOSinZ_isLoaded = true;
  }
  return nSFOSinZ_;
}

const int &wwwtree::nj() {
  if (not nj_isLoaded) {
    if (nj_branch != 0) {
      nj_branch->GetEntry(index);
    } else {
      printf("branch nj_branch does not exist!\n");
      exit(1);
    }
    nj_isLoaded = true;
  }
  return nj_;
}

const int &wwwtree::nj_up() {
  if (not nj_up_isLoaded) {
    if (nj_up_branch != 0) {
      nj_up_branch->GetEntry(index);
    } else {
      printf("branch nj_up_branch does not exist!\n");
      exit(1);
    }
    nj_up_isLoaded = true;
  }
  return nj_up_;
}

const int &wwwtree::nj_dn() {
  if (not nj_dn_isLoaded) {
    if (nj_dn_branch != 0) {
      nj_dn_branch->GetEntry(index);
    } else {
      printf("branch nj_dn_branch does not exist!\n");
      exit(1);
    }
    nj_dn_isLoaded = true;
  }
  return nj_dn_;
}

const int &wwwtree::nj30() {
  if (not nj30_isLoaded) {
    if (nj30_branch != 0) {
      nj30_branch->GetEntry(index);
    } else {
      printf("branch nj30_branch does not exist!\n");
      exit(1);
    }
    nj30_isLoaded = true;
  }
  return nj30_;
}

const int &wwwtree::nj30_up() {
  if (not nj30_up_isLoaded) {
    if (nj30_up_branch != 0) {
      nj30_up_branch->GetEntry(index);
    } else {
      printf("branch nj30_up_branch does not exist!\n");
      exit(1);
    }
    nj30_up_isLoaded = true;
  }
  return nj30_up_;
}

const int &wwwtree::nj30_dn() {
  if (not nj30_dn_isLoaded) {
    if (nj30_dn_branch != 0) {
      nj30_dn_branch->GetEntry(index);
    } else {
      printf("branch nj30_dn_branch does not exist!\n");
      exit(1);
    }
    nj30_dn_isLoaded = true;
  }
  return nj30_dn_;
}

const int &wwwtree::nb() {
  if (not nb_isLoaded) {
    if (nb_branch != 0) {
      nb_branch->GetEntry(index);
    } else {
      printf("branch nb_branch does not exist!\n");
      exit(1);
    }
    nb_isLoaded = true;
  }
  return nb_;
}

const int &wwwtree::nb_up() {
  if (not nb_up_isLoaded) {
    if (nb_up_branch != 0) {
      nb_up_branch->GetEntry(index);
    } else {
      printf("branch nb_up_branch does not exist!\n");
      exit(1);
    }
    nb_up_isLoaded = true;
  }
  return nb_up_;
}

const int &wwwtree::nb_dn() {
  if (not nb_dn_isLoaded) {
    if (nb_dn_branch != 0) {
      nb_dn_branch->GetEntry(index);
    } else {
      printf("branch nb_dn_branch does not exist!\n");
      exit(1);
    }
    nb_dn_isLoaded = true;
  }
  return nb_dn_;
}

const float &wwwtree::Mjj() {
  if (not Mjj_isLoaded) {
    if (Mjj_branch != 0) {
      Mjj_branch->GetEntry(index);
    } else {
      printf("branch Mjj_branch does not exist!\n");
      exit(1);
    }
    Mjj_isLoaded = true;
  }
  return Mjj_;
}

const float &wwwtree::Mjj_up() {
  if (not Mjj_up_isLoaded) {
    if (Mjj_up_branch != 0) {
      Mjj_up_branch->GetEntry(index);
    } else {
      printf("branch Mjj_up_branch does not exist!\n");
      exit(1);
    }
    Mjj_up_isLoaded = true;
  }
  return Mjj_up_;
}

const float &wwwtree::Mjj_dn() {
  if (not Mjj_dn_isLoaded) {
    if (Mjj_dn_branch != 0) {
      Mjj_dn_branch->GetEntry(index);
    } else {
      printf("branch Mjj_dn_branch does not exist!\n");
      exit(1);
    }
    Mjj_dn_isLoaded = true;
  }
  return Mjj_dn_;
}

const float &wwwtree::DRjj() {
  if (not DRjj_isLoaded) {
    if (DRjj_branch != 0) {
      DRjj_branch->GetEntry(index);
    } else {
      printf("branch DRjj_branch does not exist!\n");
      exit(1);
    }
    DRjj_isLoaded = true;
  }
  return DRjj_;
}

const float &wwwtree::DRjj_up() {
  if (not DRjj_up_isLoaded) {
    if (DRjj_up_branch != 0) {
      DRjj_up_branch->GetEntry(index);
    } else {
      printf("branch DRjj_up_branch does not exist!\n");
      exit(1);
    }
    DRjj_up_isLoaded = true;
  }
  return DRjj_up_;
}

const float &wwwtree::DRjj_dn() {
  if (not DRjj_dn_isLoaded) {
    if (DRjj_dn_branch != 0) {
      DRjj_dn_branch->GetEntry(index);
    } else {
      printf("branch DRjj_dn_branch does not exist!\n");
      exit(1);
    }
    DRjj_dn_isLoaded = true;
  }
  return DRjj_dn_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet0_wtag_p4() {
  if (not jet0_wtag_p4_isLoaded) {
    if (jet0_wtag_p4_branch != 0) {
      jet0_wtag_p4_branch->GetEntry(index);
    } else {
      printf("branch jet0_wtag_p4_branch does not exist!\n");
      exit(1);
    }
    jet0_wtag_p4_isLoaded = true;
  }
  return *jet0_wtag_p4_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet0_wtag_p4_up() {
  if (not jet0_wtag_p4_up_isLoaded) {
    if (jet0_wtag_p4_up_branch != 0) {
      jet0_wtag_p4_up_branch->GetEntry(index);
    } else {
      printf("branch jet0_wtag_p4_up_branch does not exist!\n");
      exit(1);
    }
    jet0_wtag_p4_up_isLoaded = true;
  }
  return *jet0_wtag_p4_up_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet0_wtag_p4_dn() {
  if (not jet0_wtag_p4_dn_isLoaded) {
    if (jet0_wtag_p4_dn_branch != 0) {
      jet0_wtag_p4_dn_branch->GetEntry(index);
    } else {
      printf("branch jet0_wtag_p4_dn_branch does not exist!\n");
      exit(1);
    }
    jet0_wtag_p4_dn_isLoaded = true;
  }
  return *jet0_wtag_p4_dn_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet1_wtag_p4() {
  if (not jet1_wtag_p4_isLoaded) {
    if (jet1_wtag_p4_branch != 0) {
      jet1_wtag_p4_branch->GetEntry(index);
    } else {
      printf("branch jet1_wtag_p4_branch does not exist!\n");
      exit(1);
    }
    jet1_wtag_p4_isLoaded = true;
  }
  return *jet1_wtag_p4_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet1_wtag_p4_up() {
  if (not jet1_wtag_p4_up_isLoaded) {
    if (jet1_wtag_p4_up_branch != 0) {
      jet1_wtag_p4_up_branch->GetEntry(index);
    } else {
      printf("branch jet1_wtag_p4_up_branch does not exist!\n");
      exit(1);
    }
    jet1_wtag_p4_up_isLoaded = true;
  }
  return *jet1_wtag_p4_up_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet1_wtag_p4_dn() {
  if (not jet1_wtag_p4_dn_isLoaded) {
    if (jet1_wtag_p4_dn_branch != 0) {
      jet1_wtag_p4_dn_branch->GetEntry(index);
    } else {
      printf("branch jet1_wtag_p4_dn_branch does not exist!\n");
      exit(1);
    }
    jet1_wtag_p4_dn_isLoaded = true;
  }
  return *jet1_wtag_p4_dn_;
}

const float &wwwtree::MjjDR1() {
  if (not MjjDR1_isLoaded) {
    if (MjjDR1_branch != 0) {
      MjjDR1_branch->GetEntry(index);
    } else {
      printf("branch MjjDR1_branch does not exist!\n");
      exit(1);
    }
    MjjDR1_isLoaded = true;
  }
  return MjjDR1_;
}

const float &wwwtree::MjjDR1_up() {
  if (not MjjDR1_up_isLoaded) {
    if (MjjDR1_up_branch != 0) {
      MjjDR1_up_branch->GetEntry(index);
    } else {
      printf("branch MjjDR1_up_branch does not exist!\n");
      exit(1);
    }
    MjjDR1_up_isLoaded = true;
  }
  return MjjDR1_up_;
}

const float &wwwtree::MjjDR1_dn() {
  if (not MjjDR1_dn_isLoaded) {
    if (MjjDR1_dn_branch != 0) {
      MjjDR1_dn_branch->GetEntry(index);
    } else {
      printf("branch MjjDR1_dn_branch does not exist!\n");
      exit(1);
    }
    MjjDR1_dn_isLoaded = true;
  }
  return MjjDR1_dn_;
}

const float &wwwtree::DRjjDR1() {
  if (not DRjjDR1_isLoaded) {
    if (DRjjDR1_branch != 0) {
      DRjjDR1_branch->GetEntry(index);
    } else {
      printf("branch DRjjDR1_branch does not exist!\n");
      exit(1);
    }
    DRjjDR1_isLoaded = true;
  }
  return DRjjDR1_;
}

const float &wwwtree::DRjjDR1_up() {
  if (not DRjjDR1_up_isLoaded) {
    if (DRjjDR1_up_branch != 0) {
      DRjjDR1_up_branch->GetEntry(index);
    } else {
      printf("branch DRjjDR1_up_branch does not exist!\n");
      exit(1);
    }
    DRjjDR1_up_isLoaded = true;
  }
  return DRjjDR1_up_;
}

const float &wwwtree::DRjjDR1_dn() {
  if (not DRjjDR1_dn_isLoaded) {
    if (DRjjDR1_dn_branch != 0) {
      DRjjDR1_dn_branch->GetEntry(index);
    } else {
      printf("branch DRjjDR1_dn_branch does not exist!\n");
      exit(1);
    }
    DRjjDR1_dn_isLoaded = true;
  }
  return DRjjDR1_dn_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet0_wtag_p4_DR1() {
  if (not jet0_wtag_p4_DR1_isLoaded) {
    if (jet0_wtag_p4_DR1_branch != 0) {
      jet0_wtag_p4_DR1_branch->GetEntry(index);
    } else {
      printf("branch jet0_wtag_p4_DR1_branch does not exist!\n");
      exit(1);
    }
    jet0_wtag_p4_DR1_isLoaded = true;
  }
  return *jet0_wtag_p4_DR1_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet0_wtag_p4_DR1_up() {
  if (not jet0_wtag_p4_DR1_up_isLoaded) {
    if (jet0_wtag_p4_DR1_up_branch != 0) {
      jet0_wtag_p4_DR1_up_branch->GetEntry(index);
    } else {
      printf("branch jet0_wtag_p4_DR1_up_branch does not exist!\n");
      exit(1);
    }
    jet0_wtag_p4_DR1_up_isLoaded = true;
  }
  return *jet0_wtag_p4_DR1_up_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet0_wtag_p4_DR1_dn() {
  if (not jet0_wtag_p4_DR1_dn_isLoaded) {
    if (jet0_wtag_p4_DR1_dn_branch != 0) {
      jet0_wtag_p4_DR1_dn_branch->GetEntry(index);
    } else {
      printf("branch jet0_wtag_p4_DR1_dn_branch does not exist!\n");
      exit(1);
    }
    jet0_wtag_p4_DR1_dn_isLoaded = true;
  }
  return *jet0_wtag_p4_DR1_dn_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet1_wtag_p4_DR1() {
  if (not jet1_wtag_p4_DR1_isLoaded) {
    if (jet1_wtag_p4_DR1_branch != 0) {
      jet1_wtag_p4_DR1_branch->GetEntry(index);
    } else {
      printf("branch jet1_wtag_p4_DR1_branch does not exist!\n");
      exit(1);
    }
    jet1_wtag_p4_DR1_isLoaded = true;
  }
  return *jet1_wtag_p4_DR1_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet1_wtag_p4_DR1_up() {
  if (not jet1_wtag_p4_DR1_up_isLoaded) {
    if (jet1_wtag_p4_DR1_up_branch != 0) {
      jet1_wtag_p4_DR1_up_branch->GetEntry(index);
    } else {
      printf("branch jet1_wtag_p4_DR1_up_branch does not exist!\n");
      exit(1);
    }
    jet1_wtag_p4_DR1_up_isLoaded = true;
  }
  return *jet1_wtag_p4_DR1_up_;
}

const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wwwtree::jet1_wtag_p4_DR1_dn() {
  if (not jet1_wtag_p4_DR1_dn_isLoaded) {
    if (jet1_wtag_p4_DR1_dn_branch != 0) {
      jet1_wtag_p4_DR1_dn_branch->GetEntry(index);
    } else {
      printf("branch jet1_wtag_p4_DR1_dn_branch does not exist!\n");
      exit(1);
    }
    jet1_wtag_p4_DR1_dn_isLoaded = true;
  }
  return *jet1_wtag_p4_DR1_dn_;
}

const float &wwwtree::MjjVBF() {
  if (not MjjVBF_isLoaded) {
    if (MjjVBF_branch != 0) {
      MjjVBF_branch->GetEntry(index);
    } else {
      printf("branch MjjVBF_branch does not exist!\n");
      exit(1);
    }
    MjjVBF_isLoaded = true;
  }
  return MjjVBF_;
}

const float &wwwtree::MjjVBF_up() {
  if (not MjjVBF_up_isLoaded) {
    if (MjjVBF_up_branch != 0) {
      MjjVBF_up_branch->GetEntry(index);
    } else {
      printf("branch MjjVBF_up_branch does not exist!\n");
      exit(1);
    }
    MjjVBF_up_isLoaded = true;
  }
  return MjjVBF_up_;
}

const float &wwwtree::MjjVBF_dn() {
  if (not MjjVBF_dn_isLoaded) {
    if (MjjVBF_dn_branch != 0) {
      MjjVBF_dn_branch->GetEntry(index);
    } else {
      printf("branch MjjVBF_dn_branch does not exist!\n");
      exit(1);
    }
    MjjVBF_dn_isLoaded = true;
  }
  return MjjVBF_dn_;
}

const float &wwwtree::DetajjVBF() {
  if (not DetajjVBF_isLoaded) {
    if (DetajjVBF_branch != 0) {
      DetajjVBF_branch->GetEntry(index);
    } else {
      printf("branch DetajjVBF_branch does not exist!\n");
      exit(1);
    }
    DetajjVBF_isLoaded = true;
  }
  return DetajjVBF_;
}

const float &wwwtree::DetajjVBF_up() {
  if (not DetajjVBF_up_isLoaded) {
    if (DetajjVBF_up_branch != 0) {
      DetajjVBF_up_branch->GetEntry(index);
    } else {
      printf("branch DetajjVBF_up_branch does not exist!\n");
      exit(1);
    }
    DetajjVBF_up_isLoaded = true;
  }
  return DetajjVBF_up_;
}

const float &wwwtree::DetajjVBF_dn() {
  if (not DetajjVBF_dn_isLoaded) {
    if (DetajjVBF_dn_branch != 0) {
      DetajjVBF_dn_branch->GetEntry(index);
    } else {
      printf("branch DetajjVBF_dn_branch does not exist!\n");
      exit(1);
    }
    DetajjVBF_dn_isLoaded = true;
  }
  return DetajjVBF_dn_;
}

const float &wwwtree::MjjL() {
  if (not MjjL_isLoaded) {
    if (MjjL_branch != 0) {
      MjjL_branch->GetEntry(index);
    } else {
      printf("branch MjjL_branch does not exist!\n");
      exit(1);
    }
    MjjL_isLoaded = true;
  }
  return MjjL_;
}

const float &wwwtree::MjjL_up() {
  if (not MjjL_up_isLoaded) {
    if (MjjL_up_branch != 0) {
      MjjL_up_branch->GetEntry(index);
    } else {
      printf("branch MjjL_up_branch does not exist!\n");
      exit(1);
    }
    MjjL_up_isLoaded = true;
  }
  return MjjL_up_;
}

const float &wwwtree::MjjL_dn() {
  if (not MjjL_dn_isLoaded) {
    if (MjjL_dn_branch != 0) {
      MjjL_dn_branch->GetEntry(index);
    } else {
      printf("branch MjjL_dn_branch does not exist!\n");
      exit(1);
    }
    MjjL_dn_isLoaded = true;
  }
  return MjjL_dn_;
}

const float &wwwtree::DetajjL() {
  if (not DetajjL_isLoaded) {
    if (DetajjL_branch != 0) {
      DetajjL_branch->GetEntry(index);
    } else {
      printf("branch DetajjL_branch does not exist!\n");
      exit(1);
    }
    DetajjL_isLoaded = true;
  }
  return DetajjL_;
}

const float &wwwtree::DetajjL_up() {
  if (not DetajjL_up_isLoaded) {
    if (DetajjL_up_branch != 0) {
      DetajjL_up_branch->GetEntry(index);
    } else {
      printf("branch DetajjL_up_branch does not exist!\n");
      exit(1);
    }
    DetajjL_up_isLoaded = true;
  }
  return DetajjL_up_;
}

const float &wwwtree::DetajjL_dn() {
  if (not DetajjL_dn_isLoaded) {
    if (DetajjL_dn_branch != 0) {
      DetajjL_dn_branch->GetEntry(index);
    } else {
      printf("branch DetajjL_dn_branch does not exist!\n");
      exit(1);
    }
    DetajjL_dn_isLoaded = true;
  }
  return DetajjL_dn_;
}

const float &wwwtree::MllSS() {
  if (not MllSS_isLoaded) {
    if (MllSS_branch != 0) {
      MllSS_branch->GetEntry(index);
    } else {
      printf("branch MllSS_branch does not exist!\n");
      exit(1);
    }
    MllSS_isLoaded = true;
  }
  return MllSS_;
}

const float &wwwtree::MeeSS() {
  if (not MeeSS_isLoaded) {
    if (MeeSS_branch != 0) {
      MeeSS_branch->GetEntry(index);
    } else {
      printf("branch MeeSS_branch does not exist!\n");
      exit(1);
    }
    MeeSS_isLoaded = true;
  }
  return MeeSS_;
}

const float &wwwtree::Mll3L() {
  if (not Mll3L_isLoaded) {
    if (Mll3L_branch != 0) {
      Mll3L_branch->GetEntry(index);
    } else {
      printf("branch Mll3L_branch does not exist!\n");
      exit(1);
    }
    Mll3L_isLoaded = true;
  }
  return Mll3L_;
}

const float &wwwtree::Mee3L() {
  if (not Mee3L_isLoaded) {
    if (Mee3L_branch != 0) {
      Mee3L_branch->GetEntry(index);
    } else {
      printf("branch Mee3L_branch does not exist!\n");
      exit(1);
    }
    Mee3L_isLoaded = true;
  }
  return Mee3L_;
}

const float &wwwtree::Mll3L1() {
  if (not Mll3L1_isLoaded) {
    if (Mll3L1_branch != 0) {
      Mll3L1_branch->GetEntry(index);
    } else {
      printf("branch Mll3L1_branch does not exist!\n");
      exit(1);
    }
    Mll3L1_isLoaded = true;
  }
  return Mll3L1_;
}

const float &wwwtree::M3l() {
  if (not M3l_isLoaded) {
    if (M3l_branch != 0) {
      M3l_branch->GetEntry(index);
    } else {
      printf("branch M3l_branch does not exist!\n");
      exit(1);
    }
    M3l_isLoaded = true;
  }
  return M3l_;
}

const float &wwwtree::Pt3l() {
  if (not Pt3l_isLoaded) {
    if (Pt3l_branch != 0) {
      Pt3l_branch->GetEntry(index);
    } else {
      printf("branch Pt3l_branch does not exist!\n");
      exit(1);
    }
    Pt3l_isLoaded = true;
  }
  return Pt3l_;
}

const float &wwwtree::M01() {
  if (not M01_isLoaded) {
    if (M01_branch != 0) {
      M01_branch->GetEntry(index);
    } else {
      printf("branch M01_branch does not exist!\n");
      exit(1);
    }
    M01_isLoaded = true;
  }
  return M01_;
}

const float &wwwtree::M02() {
  if (not M02_isLoaded) {
    if (M02_branch != 0) {
      M02_branch->GetEntry(index);
    } else {
      printf("branch M02_branch does not exist!\n");
      exit(1);
    }
    M02_isLoaded = true;
  }
  return M02_;
}

const float &wwwtree::M12() {
  if (not M12_isLoaded) {
    if (M12_branch != 0) {
      M12_branch->GetEntry(index);
    } else {
      printf("branch M12_branch does not exist!\n");
      exit(1);
    }
    M12_isLoaded = true;
  }
  return M12_;
}

const int &wwwtree::isSFOS01() {
  if (not isSFOS01_isLoaded) {
    if (isSFOS01_branch != 0) {
      isSFOS01_branch->GetEntry(index);
    } else {
      printf("branch isSFOS01_branch does not exist!\n");
      exit(1);
    }
    isSFOS01_isLoaded = true;
  }
  return isSFOS01_;
}

const int &wwwtree::isSFOS02() {
  if (not isSFOS02_isLoaded) {
    if (isSFOS02_branch != 0) {
      isSFOS02_branch->GetEntry(index);
    } else {
      printf("branch isSFOS02_branch does not exist!\n");
      exit(1);
    }
    isSFOS02_isLoaded = true;
  }
  return isSFOS02_;
}

const int &wwwtree::isSFOS12() {
  if (not isSFOS12_isLoaded) {
    if (isSFOS12_branch != 0) {
      isSFOS12_branch->GetEntry(index);
    } else {
      printf("branch isSFOS12_branch does not exist!\n");
      exit(1);
    }
    isSFOS12_isLoaded = true;
  }
  return isSFOS12_;
}

const float &wwwtree::DPhi3lMET() {
  if (not DPhi3lMET_isLoaded) {
    if (DPhi3lMET_branch != 0) {
      DPhi3lMET_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_isLoaded = true;
  }
  return DPhi3lMET_;
}

const float &wwwtree::DPhi3lMET_up() {
  if (not DPhi3lMET_up_isLoaded) {
    if (DPhi3lMET_up_branch != 0) {
      DPhi3lMET_up_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_up_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_up_isLoaded = true;
  }
  return DPhi3lMET_up_;
}

const float &wwwtree::DPhi3lMET_dn() {
  if (not DPhi3lMET_dn_isLoaded) {
    if (DPhi3lMET_dn_branch != 0) {
      DPhi3lMET_dn_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_dn_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_dn_isLoaded = true;
  }
  return DPhi3lMET_dn_;
}

const float &wwwtree::DPhi3lMET_gen() {
  if (not DPhi3lMET_gen_isLoaded) {
    if (DPhi3lMET_gen_branch != 0) {
      DPhi3lMET_gen_branch->GetEntry(index);
    } else {
      printf("branch DPhi3lMET_gen_branch does not exist!\n");
      exit(1);
    }
    DPhi3lMET_gen_isLoaded = true;
  }
  return DPhi3lMET_gen_;
}

const float &wwwtree::MTmax() {
  if (not MTmax_isLoaded) {
    if (MTmax_branch != 0) {
      MTmax_branch->GetEntry(index);
    } else {
      printf("branch MTmax_branch does not exist!\n");
      exit(1);
    }
    MTmax_isLoaded = true;
  }
  return MTmax_;
}

const float &wwwtree::MTmax_up() {
  if (not MTmax_up_isLoaded) {
    if (MTmax_up_branch != 0) {
      MTmax_up_branch->GetEntry(index);
    } else {
      printf("branch MTmax_up_branch does not exist!\n");
      exit(1);
    }
    MTmax_up_isLoaded = true;
  }
  return MTmax_up_;
}

const float &wwwtree::MTmax_dn() {
  if (not MTmax_dn_isLoaded) {
    if (MTmax_dn_branch != 0) {
      MTmax_dn_branch->GetEntry(index);
    } else {
      printf("branch MTmax_dn_branch does not exist!\n");
      exit(1);
    }
    MTmax_dn_isLoaded = true;
  }
  return MTmax_dn_;
}

const float &wwwtree::MTmax_gen() {
  if (not MTmax_gen_isLoaded) {
    if (MTmax_gen_branch != 0) {
      MTmax_gen_branch->GetEntry(index);
    } else {
      printf("branch MTmax_gen_branch does not exist!\n");
      exit(1);
    }
    MTmax_gen_isLoaded = true;
  }
  return MTmax_gen_;
}

const float &wwwtree::MTmin() {
  if (not MTmin_isLoaded) {
    if (MTmin_branch != 0) {
      MTmin_branch->GetEntry(index);
    } else {
      printf("branch MTmin_branch does not exist!\n");
      exit(1);
    }
    MTmin_isLoaded = true;
  }
  return MTmin_;
}

const float &wwwtree::MTmin_up() {
  if (not MTmin_up_isLoaded) {
    if (MTmin_up_branch != 0) {
      MTmin_up_branch->GetEntry(index);
    } else {
      printf("branch MTmin_up_branch does not exist!\n");
      exit(1);
    }
    MTmin_up_isLoaded = true;
  }
  return MTmin_up_;
}

const float &wwwtree::MTmin_dn() {
  if (not MTmin_dn_isLoaded) {
    if (MTmin_dn_branch != 0) {
      MTmin_dn_branch->GetEntry(index);
    } else {
      printf("branch MTmin_dn_branch does not exist!\n");
      exit(1);
    }
    MTmin_dn_isLoaded = true;
  }
  return MTmin_dn_;
}

const float &wwwtree::MTmin_gen() {
  if (not MTmin_gen_isLoaded) {
    if (MTmin_gen_branch != 0) {
      MTmin_gen_branch->GetEntry(index);
    } else {
      printf("branch MTmin_gen_branch does not exist!\n");
      exit(1);
    }
    MTmin_gen_isLoaded = true;
  }
  return MTmin_gen_;
}

const float &wwwtree::MT3rd() {
  if (not MT3rd_isLoaded) {
    if (MT3rd_branch != 0) {
      MT3rd_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_branch does not exist!\n");
      exit(1);
    }
    MT3rd_isLoaded = true;
  }
  return MT3rd_;
}

const float &wwwtree::MT3rd_up() {
  if (not MT3rd_up_isLoaded) {
    if (MT3rd_up_branch != 0) {
      MT3rd_up_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_up_branch does not exist!\n");
      exit(1);
    }
    MT3rd_up_isLoaded = true;
  }
  return MT3rd_up_;
}

const float &wwwtree::MT3rd_dn() {
  if (not MT3rd_dn_isLoaded) {
    if (MT3rd_dn_branch != 0) {
      MT3rd_dn_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_dn_branch does not exist!\n");
      exit(1);
    }
    MT3rd_dn_isLoaded = true;
  }
  return MT3rd_dn_;
}

const float &wwwtree::MT3rd_gen() {
  if (not MT3rd_gen_isLoaded) {
    if (MT3rd_gen_branch != 0) {
      MT3rd_gen_branch->GetEntry(index);
    } else {
      printf("branch MT3rd_gen_branch does not exist!\n");
      exit(1);
    }
    MT3rd_gen_isLoaded = true;
  }
  return MT3rd_gen_;
}

const float &wwwtree::MTmax3L() {
  if (not MTmax3L_isLoaded) {
    if (MTmax3L_branch != 0) {
      MTmax3L_branch->GetEntry(index);
    } else {
      printf("branch MTmax3L_branch does not exist!\n");
      exit(1);
    }
    MTmax3L_isLoaded = true;
  }
  return MTmax3L_;
}

const float &wwwtree::MTmax3L_up() {
  if (not MTmax3L_up_isLoaded) {
    if (MTmax3L_up_branch != 0) {
      MTmax3L_up_branch->GetEntry(index);
    } else {
      printf("branch MTmax3L_up_branch does not exist!\n");
      exit(1);
    }
    MTmax3L_up_isLoaded = true;
  }
  return MTmax3L_up_;
}

const float &wwwtree::MTmax3L_dn() {
  if (not MTmax3L_dn_isLoaded) {
    if (MTmax3L_dn_branch != 0) {
      MTmax3L_dn_branch->GetEntry(index);
    } else {
      printf("branch MTmax3L_dn_branch does not exist!\n");
      exit(1);
    }
    MTmax3L_dn_isLoaded = true;
  }
  return MTmax3L_dn_;
}

const float &wwwtree::MTmax3L_gen() {
  if (not MTmax3L_gen_isLoaded) {
    if (MTmax3L_gen_branch != 0) {
      MTmax3L_gen_branch->GetEntry(index);
    } else {
      printf("branch MTmax3L_gen_branch does not exist!\n");
      exit(1);
    }
    MTmax3L_gen_isLoaded = true;
  }
  return MTmax3L_gen_;
}

const int &wwwtree::passSSee() {
  if (not passSSee_isLoaded) {
    if (passSSee_branch != 0) {
      passSSee_branch->GetEntry(index);
    } else {
      printf("branch passSSee_branch does not exist!\n");
      exit(1);
    }
    passSSee_isLoaded = true;
  }
  return passSSee_;
}

const int &wwwtree::passSSem() {
  if (not passSSem_isLoaded) {
    if (passSSem_branch != 0) {
      passSSem_branch->GetEntry(index);
    } else {
      printf("branch passSSem_branch does not exist!\n");
      exit(1);
    }
    passSSem_isLoaded = true;
  }
  return passSSem_;
}

const int &wwwtree::passSSmm() {
  if (not passSSmm_isLoaded) {
    if (passSSmm_branch != 0) {
      passSSmm_branch->GetEntry(index);
    } else {
      printf("branch passSSmm_branch does not exist!\n");
      exit(1);
    }
    passSSmm_isLoaded = true;
  }
  return passSSmm_;
}

const int &wwwtree::lep_idx0_SS() {
  if (not lep_idx0_SS_isLoaded) {
    if (lep_idx0_SS_branch != 0) {
      lep_idx0_SS_branch->GetEntry(index);
    } else {
      printf("branch lep_idx0_SS_branch does not exist!\n");
      exit(1);
    }
    lep_idx0_SS_isLoaded = true;
  }
  return lep_idx0_SS_;
}

const int &wwwtree::lep_idx1_SS() {
  if (not lep_idx1_SS_isLoaded) {
    if (lep_idx1_SS_branch != 0) {
      lep_idx1_SS_branch->GetEntry(index);
    } else {
      printf("branch lep_idx1_SS_branch does not exist!\n");
      exit(1);
    }
    lep_idx1_SS_isLoaded = true;
  }
  return lep_idx1_SS_;
}

const TString &wwwtree::bkgtype() {
  if (not bkgtype_isLoaded) {
    if (bkgtype_branch != 0) {
      bkgtype_branch->GetEntry(index);
    } else {
      printf("branch bkgtype_branch does not exist!\n");
      exit(1);
    }
    bkgtype_isLoaded = true;
  }
  return *bkgtype_;
}

const int &wwwtree::vetophoton() {
  if (not vetophoton_isLoaded) {
    if (vetophoton_branch != 0) {
      vetophoton_branch->GetEntry(index);
    } else {
      printf("branch vetophoton_branch does not exist!\n");
      exit(1);
    }
    vetophoton_isLoaded = true;
  }
  return vetophoton_;
}

const float &wwwtree::purewgt() {
  if (not purewgt_isLoaded) {
    if (purewgt_branch != 0) {
      purewgt_branch->GetEntry(index);
    } else {
      printf("branch purewgt_branch does not exist!\n");
      exit(1);
    }
    purewgt_isLoaded = true;
  }
  return purewgt_;
}

const float &wwwtree::purewgt_up() {
  if (not purewgt_up_isLoaded) {
    if (purewgt_up_branch != 0) {
      purewgt_up_branch->GetEntry(index);
    } else {
      printf("branch purewgt_up_branch does not exist!\n");
      exit(1);
    }
    purewgt_up_isLoaded = true;
  }
  return purewgt_up_;
}

const float &wwwtree::purewgt_dn() {
  if (not purewgt_dn_isLoaded) {
    if (purewgt_dn_branch != 0) {
      purewgt_dn_branch->GetEntry(index);
    } else {
      printf("branch purewgt_dn_branch does not exist!\n");
      exit(1);
    }
    purewgt_dn_isLoaded = true;
  }
  return purewgt_dn_;
}

const float &wwwtree::ffwgt() {
  if (not ffwgt_isLoaded) {
    if (ffwgt_branch != 0) {
      ffwgt_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_branch does not exist!\n");
      exit(1);
    }
    ffwgt_isLoaded = true;
  }
  return ffwgt_;
}

const float &wwwtree::ffwgt_up() {
  if (not ffwgt_up_isLoaded) {
    if (ffwgt_up_branch != 0) {
      ffwgt_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_up_isLoaded = true;
  }
  return ffwgt_up_;
}

const float &wwwtree::ffwgt_dn() {
  if (not ffwgt_dn_isLoaded) {
    if (ffwgt_dn_branch != 0) {
      ffwgt_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_dn_isLoaded = true;
  }
  return ffwgt_dn_;
}

const float &wwwtree::ffwgt_el_up() {
  if (not ffwgt_el_up_isLoaded) {
    if (ffwgt_el_up_branch != 0) {
      ffwgt_el_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_el_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_el_up_isLoaded = true;
  }
  return ffwgt_el_up_;
}

const float &wwwtree::ffwgt_el_dn() {
  if (not ffwgt_el_dn_isLoaded) {
    if (ffwgt_el_dn_branch != 0) {
      ffwgt_el_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_el_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_el_dn_isLoaded = true;
  }
  return ffwgt_el_dn_;
}

const float &wwwtree::ffwgt_mu_up() {
  if (not ffwgt_mu_up_isLoaded) {
    if (ffwgt_mu_up_branch != 0) {
      ffwgt_mu_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_mu_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_mu_up_isLoaded = true;
  }
  return ffwgt_mu_up_;
}

const float &wwwtree::ffwgt_mu_dn() {
  if (not ffwgt_mu_dn_isLoaded) {
    if (ffwgt_mu_dn_branch != 0) {
      ffwgt_mu_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_mu_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_mu_dn_isLoaded = true;
  }
  return ffwgt_mu_dn_;
}

const float &wwwtree::ffwgt_closure_up() {
  if (not ffwgt_closure_up_isLoaded) {
    if (ffwgt_closure_up_branch != 0) {
      ffwgt_closure_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_closure_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_closure_up_isLoaded = true;
  }
  return ffwgt_closure_up_;
}

const float &wwwtree::ffwgt_closure_dn() {
  if (not ffwgt_closure_dn_isLoaded) {
    if (ffwgt_closure_dn_branch != 0) {
      ffwgt_closure_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_closure_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_closure_dn_isLoaded = true;
  }
  return ffwgt_closure_dn_;
}

const float &wwwtree::ffwgt_closure_el_up() {
  if (not ffwgt_closure_el_up_isLoaded) {
    if (ffwgt_closure_el_up_branch != 0) {
      ffwgt_closure_el_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_closure_el_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_closure_el_up_isLoaded = true;
  }
  return ffwgt_closure_el_up_;
}

const float &wwwtree::ffwgt_closure_el_dn() {
  if (not ffwgt_closure_el_dn_isLoaded) {
    if (ffwgt_closure_el_dn_branch != 0) {
      ffwgt_closure_el_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_closure_el_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_closure_el_dn_isLoaded = true;
  }
  return ffwgt_closure_el_dn_;
}

const float &wwwtree::ffwgt_closure_mu_up() {
  if (not ffwgt_closure_mu_up_isLoaded) {
    if (ffwgt_closure_mu_up_branch != 0) {
      ffwgt_closure_mu_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_closure_mu_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_closure_mu_up_isLoaded = true;
  }
  return ffwgt_closure_mu_up_;
}

const float &wwwtree::ffwgt_closure_mu_dn() {
  if (not ffwgt_closure_mu_dn_isLoaded) {
    if (ffwgt_closure_mu_dn_branch != 0) {
      ffwgt_closure_mu_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_closure_mu_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_closure_mu_dn_isLoaded = true;
  }
  return ffwgt_closure_mu_dn_;
}

const float &wwwtree::ffwgt_full_up() {
  if (not ffwgt_full_up_isLoaded) {
    if (ffwgt_full_up_branch != 0) {
      ffwgt_full_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_full_up_branch does not exist!\n");
      exit(1);
    }
    ffwgt_full_up_isLoaded = true;
  }
  return ffwgt_full_up_;
}

const float &wwwtree::ffwgt_full_dn() {
  if (not ffwgt_full_dn_isLoaded) {
    if (ffwgt_full_dn_branch != 0) {
      ffwgt_full_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgt_full_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgt_full_dn_isLoaded = true;
  }
  return ffwgt_full_dn_;
}

const float &wwwtree::ffwgtqcd() {
  if (not ffwgtqcd_isLoaded) {
    if (ffwgtqcd_branch != 0) {
      ffwgtqcd_branch->GetEntry(index);
    } else {
      printf("branch ffwgtqcd_branch does not exist!\n");
      exit(1);
    }
    ffwgtqcd_isLoaded = true;
  }
  return ffwgtqcd_;
}

const float &wwwtree::ffwgtqcd_up() {
  if (not ffwgtqcd_up_isLoaded) {
    if (ffwgtqcd_up_branch != 0) {
      ffwgtqcd_up_branch->GetEntry(index);
    } else {
      printf("branch ffwgtqcd_up_branch does not exist!\n");
      exit(1);
    }
    ffwgtqcd_up_isLoaded = true;
  }
  return ffwgtqcd_up_;
}

const float &wwwtree::ffwgtqcd_dn() {
  if (not ffwgtqcd_dn_isLoaded) {
    if (ffwgtqcd_dn_branch != 0) {
      ffwgtqcd_dn_branch->GetEntry(index);
    } else {
      printf("branch ffwgtqcd_dn_branch does not exist!\n");
      exit(1);
    }
    ffwgtqcd_dn_isLoaded = true;
  }
  return ffwgtqcd_dn_;
}

const float &wwwtree::lepsf() {
  if (not lepsf_isLoaded) {
    if (lepsf_branch != 0) {
      lepsf_branch->GetEntry(index);
    } else {
      printf("branch lepsf_branch does not exist!\n");
      exit(1);
    }
    lepsf_isLoaded = true;
  }
  return lepsf_;
}

const float &wwwtree::lepsf_up() {
  if (not lepsf_up_isLoaded) {
    if (lepsf_up_branch != 0) {
      lepsf_up_branch->GetEntry(index);
    } else {
      printf("branch lepsf_up_branch does not exist!\n");
      exit(1);
    }
    lepsf_up_isLoaded = true;
  }
  return lepsf_up_;
}

const float &wwwtree::lepsf_dn() {
  if (not lepsf_dn_isLoaded) {
    if (lepsf_dn_branch != 0) {
      lepsf_dn_branch->GetEntry(index);
    } else {
      printf("branch lepsf_dn_branch does not exist!\n");
      exit(1);
    }
    lepsf_dn_isLoaded = true;
  }
  return lepsf_dn_;
}

const float &wwwtree::trigeff() {
  if (not trigeff_isLoaded) {
    if (trigeff_branch != 0) {
      trigeff_branch->GetEntry(index);
    } else {
      printf("branch trigeff_branch does not exist!\n");
      exit(1);
    }
    trigeff_isLoaded = true;
  }
  return trigeff_;
}

const float &wwwtree::trigeff_up() {
  if (not trigeff_up_isLoaded) {
    if (trigeff_up_branch != 0) {
      trigeff_up_branch->GetEntry(index);
    } else {
      printf("branch trigeff_up_branch does not exist!\n");
      exit(1);
    }
    trigeff_up_isLoaded = true;
  }
  return trigeff_up_;
}

const float &wwwtree::trigeff_dn() {
  if (not trigeff_dn_isLoaded) {
    if (trigeff_dn_branch != 0) {
      trigeff_dn_branch->GetEntry(index);
    } else {
      printf("branch trigeff_dn_branch does not exist!\n");
      exit(1);
    }
    trigeff_dn_isLoaded = true;
  }
  return trigeff_dn_;
}

const float &wwwtree::trigsf() {
  if (not trigsf_isLoaded) {
    if (trigsf_branch != 0) {
      trigsf_branch->GetEntry(index);
    } else {
      printf("branch trigsf_branch does not exist!\n");
      exit(1);
    }
    trigsf_isLoaded = true;
  }
  return trigsf_;
}

const float &wwwtree::trigsf_up() {
  if (not trigsf_up_isLoaded) {
    if (trigsf_up_branch != 0) {
      trigsf_up_branch->GetEntry(index);
    } else {
      printf("branch trigsf_up_branch does not exist!\n");
      exit(1);
    }
    trigsf_up_isLoaded = true;
  }
  return trigsf_up_;
}

const float &wwwtree::trigsf_dn() {
  if (not trigsf_dn_isLoaded) {
    if (trigsf_dn_branch != 0) {
      trigsf_dn_branch->GetEntry(index);
    } else {
      printf("branch trigsf_dn_branch does not exist!\n");
      exit(1);
    }
    trigsf_dn_isLoaded = true;
  }
  return trigsf_dn_;
}

const float &wwwtree::musmear_sf() {
  if (not musmear_sf_isLoaded) {
    if (musmear_sf_branch != 0) {
      musmear_sf_branch->GetEntry(index);
    } else {
      printf("branch musmear_sf_branch does not exist!\n");
      exit(1);
    }
    musmear_sf_isLoaded = true;
  }
  return musmear_sf_;
}


void wwwtree::progress( int nEventsTotal, int nEventsChain ){
  int period = 1000;
  if (nEventsTotal%1000 == 0) {
    // xterm magic from L. Vacavant and A. Cerri
    if (isatty(1)) {
      if ((nEventsChain - nEventsTotal) > period) {
        float frac = (float)nEventsTotal/(nEventsChain*0.01);
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
             "\033[0m\033[32m <---\033[0m\015", frac);
        fflush(stdout);
      }
      else {
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", 100.);
        cout << endl;
      }
    }
  }
}

namespace tas {

const int &run() { return www.run(); }
const int &lumi() { return www.lumi(); }
const unsigned long long &evt() { return www.evt(); }
const int &isData() { return www.isData(); }
const float &evt_scale1fb() { return www.evt_scale1fb(); }
const float &xsec_br() { return www.xsec_br(); }
const int &evt_passgoodrunlist() { return www.evt_passgoodrunlist(); }
const TString &CMS4path() { return www.CMS4path(); }
const int &CMS4index() { return www.CMS4index(); }
const float &weight_fr_r1_f1() { return www.weight_fr_r1_f1(); }
const float &weight_fr_r1_f2() { return www.weight_fr_r1_f2(); }
const float &weight_fr_r1_f0p5() { return www.weight_fr_r1_f0p5(); }
const float &weight_fr_r2_f1() { return www.weight_fr_r2_f1(); }
const float &weight_fr_r2_f2() { return www.weight_fr_r2_f2(); }
const float &weight_fr_r2_f0p5() { return www.weight_fr_r2_f0p5(); }
const float &weight_fr_r0p5_f1() { return www.weight_fr_r0p5_f1(); }
const float &weight_fr_r0p5_f2() { return www.weight_fr_r0p5_f2(); }
const float &weight_fr_r0p5_f0p5() { return www.weight_fr_r0p5_f0p5(); }
const float &weight_pdf_up() { return www.weight_pdf_up(); }
const float &weight_pdf_down() { return www.weight_pdf_down(); }
const float &weight_alphas_down() { return www.weight_alphas_down(); }
const float &weight_alphas_up() { return www.weight_alphas_up(); }
const float &weight_isr() { return www.weight_isr(); }
const float &weight_isr_up() { return www.weight_isr_up(); }
const float &weight_isr_down() { return www.weight_isr_down(); }
const int &HLT_DoubleMu() { return www.HLT_DoubleMu(); }
const int &HLT_DoubleEl() { return www.HLT_DoubleEl(); }
const int &HLT_DoubleEl_DZ() { return www.HLT_DoubleEl_DZ(); }
const int &HLT_DoubleEl_DZ_2() { return www.HLT_DoubleEl_DZ_2(); }
const int &HLT_MuEG() { return www.HLT_MuEG(); }
const int &HLT_SingleIsoEl8() { return www.HLT_SingleIsoEl8(); }
const int &HLT_SingleIsoEl17() { return www.HLT_SingleIsoEl17(); }
const int &HLT_SingleIsoEl23() { return www.HLT_SingleIsoEl23(); }
const int &HLT_SingleIsoMu8() { return www.HLT_SingleIsoMu8(); }
const int &HLT_SingleIsoMu17() { return www.HLT_SingleIsoMu17(); }
const int &HLT_PFMET140_PFMHT140_IDTight() { return www.HLT_PFMET140_PFMHT140_IDTight(); }
const int &mc_HLT_DoubleMu() { return www.mc_HLT_DoubleMu(); }
const int &mc_HLT_DoubleEl() { return www.mc_HLT_DoubleEl(); }
const int &mc_HLT_DoubleEl_DZ() { return www.mc_HLT_DoubleEl_DZ(); }
const int &mc_HLT_DoubleEl_DZ_2() { return www.mc_HLT_DoubleEl_DZ_2(); }
const int &mc_HLT_MuEG() { return www.mc_HLT_MuEG(); }
const int &mc_HLT_SingleIsoEl8() { return www.mc_HLT_SingleIsoEl8(); }
const int &mc_HLT_SingleIsoEl17() { return www.mc_HLT_SingleIsoEl17(); }
const int &mc_HLT_SingleIsoEl23() { return www.mc_HLT_SingleIsoEl23(); }
const int &mc_HLT_SingleIsoMu8() { return www.mc_HLT_SingleIsoMu8(); }
const int &mc_HLT_SingleIsoMu17() { return www.mc_HLT_SingleIsoMu17(); }
const int &mc_HLT_PFMET140_PFMHT140_IDTight() { return www.mc_HLT_PFMET140_PFMHT140_IDTight(); }
const int &pass_duplicate_ee_em_mm() { return www.pass_duplicate_ee_em_mm(); }
const int &pass_duplicate_mm_em_ee() { return www.pass_duplicate_mm_em_ee(); }
const int &is2016() { return www.is2016(); }
const int &is2017() { return www.is2017(); }
const int &HLT_MuEG_2016() { return www.HLT_MuEG_2016(); }
const int &mc_HLT_MuEG_2016() { return www.mc_HLT_MuEG_2016(); }
const int &pass_duplicate_ee_em2016_mm() { return www.pass_duplicate_ee_em2016_mm(); }
const int &pass_duplicate_mm_em2016_ee() { return www.pass_duplicate_mm_em2016_ee(); }
const int &passTrigger() { return www.passTrigger(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lep_p4() { return www.lep_p4(); }
const vector<float> &lep_pt() { return www.lep_pt(); }
const vector<float> &lep_eta() { return www.lep_eta(); }
const vector<float> &lep_phi() { return www.lep_phi(); }
const vector<float> &lep_coneCorrPt() { return www.lep_coneCorrPt(); }
const vector<float> &lep_ip3d() { return www.lep_ip3d(); }
const vector<float> &lep_ip3derr() { return www.lep_ip3derr(); }
const vector<int> &lep_isTriggerSafe_v1() { return www.lep_isTriggerSafe_v1(); }
const vector<int> &lep_lostHits() { return www.lep_lostHits(); }
const vector<int> &lep_convVeto() { return www.lep_convVeto(); }
const vector<int> &lep_motherIdSS() { return www.lep_motherIdSS(); }
const vector<int> &lep_pass_VVV_cutbased_3l_fo() { return www.lep_pass_VVV_cutbased_3l_fo(); }
const vector<int> &lep_pass_VVV_cutbased_3l_tight() { return www.lep_pass_VVV_cutbased_3l_tight(); }
const vector<int> &lep_pass_VVV_cutbased_fo() { return www.lep_pass_VVV_cutbased_fo(); }
const vector<int> &lep_pass_VVV_cutbased_tight() { return www.lep_pass_VVV_cutbased_tight(); }
const vector<int> &lep_pass_VVV_cutbased_veto() { return www.lep_pass_VVV_cutbased_veto(); }
const vector<int> &lep_pass_VVV_cutbased_fo_noiso() { return www.lep_pass_VVV_cutbased_fo_noiso(); }
const vector<int> &lep_pass_VVV_cutbased_tight_noiso() { return www.lep_pass_VVV_cutbased_tight_noiso(); }
const vector<int> &lep_pass_VVV_cutbased_veto_noiso() { return www.lep_pass_VVV_cutbased_veto_noiso(); }
const vector<int> &lep_pass_POG_veto() { return www.lep_pass_POG_veto(); }
const vector<int> &lep_pass_POG_loose() { return www.lep_pass_POG_loose(); }
const vector<int> &lep_pass_POG_medium() { return www.lep_pass_POG_medium(); }
const vector<int> &lep_pass_POG_tight() { return www.lep_pass_POG_tight(); }
const vector<int> &lep_pdgId() { return www.lep_pdgId(); }
const vector<float> &lep_dxy() { return www.lep_dxy(); }
const vector<float> &lep_dz() { return www.lep_dz(); }
const vector<float> &lep_pterr() { return www.lep_pterr(); }
const vector<float> &lep_relIso04DB() { return www.lep_relIso04DB(); }
const vector<float> &lep_relIso03EA() { return www.lep_relIso03EA(); }
const vector<float> &lep_relIso03EALep() { return www.lep_relIso03EALep(); }
const vector<float> &lep_relIso03EAv2() { return www.lep_relIso03EAv2(); }
const vector<float> &lep_relIso04EAv2() { return www.lep_relIso04EAv2(); }
const vector<float> &lep_relIso03EAv2Lep() { return www.lep_relIso03EAv2Lep(); }
const vector<int> &lep_tightCharge() { return www.lep_tightCharge(); }
const vector<float> &lep_trk_pt() { return www.lep_trk_pt(); }
const vector<int> &lep_charge() { return www.lep_charge(); }
const vector<float> &lep_etaSC() { return www.lep_etaSC(); }
const vector<float> &lep_MVA() { return www.lep_MVA(); }
const vector<int> &lep_isMediumPOG() { return www.lep_isMediumPOG(); }
const vector<int> &lep_isTightPOG() { return www.lep_isTightPOG(); }
const vector<int> &lep_isFromW() { return www.lep_isFromW(); }
const vector<int> &lep_isFromZ() { return www.lep_isFromZ(); }
const vector<int> &lep_isFromB() { return www.lep_isFromB(); }
const vector<int> &lep_isFromC() { return www.lep_isFromC(); }
const vector<int> &lep_isFromL() { return www.lep_isFromL(); }
const vector<int> &lep_isFromLF() { return www.lep_isFromLF(); }
const vector<int> &lep_genPart_index() { return www.lep_genPart_index(); }
const vector<float> &lep_r9() { return www.lep_r9(); }
const vector<int> &lep_nlayers() { return www.lep_nlayers(); }
const float &el_pt() { return www.el_pt(); }
const float &el_eta() { return www.el_eta(); }
const float &el_phi() { return www.el_phi(); }
const float &el_relIso03EA() { return www.el_relIso03EA(); }
const float &el_relIso03EALep() { return www.el_relIso03EALep(); }
const float &el_ip3d() { return www.el_ip3d(); }
const float &mu_pt() { return www.mu_pt(); }
const float &mu_eta() { return www.mu_eta(); }
const float &mu_phi() { return www.mu_phi(); }
const float &mu_relIso04DB() { return www.mu_relIso04DB(); }
const float &mu_relIso03EA() { return www.mu_relIso03EA(); }
const float &mu_relIso03EALep() { return www.mu_relIso03EALep(); }
const float &mu_ip3d() { return www.mu_ip3d(); }
const float &lbnt_pt() { return www.lbnt_pt(); }
const float &lbnt_coneCorrPt() { return www.lbnt_coneCorrPt(); }
const float &lbnt_abseta() { return www.lbnt_abseta(); }
const float &lbnt_pdgId() { return www.lbnt_pdgId(); }
const float &lbnt_el_pt() { return www.lbnt_el_pt(); }
const float &lbnt_el_coneCorrPt() { return www.lbnt_el_coneCorrPt(); }
const float &lbnt_el_abseta() { return www.lbnt_el_abseta(); }
const float &lbnt_mu_pt() { return www.lbnt_mu_pt(); }
const float &lbnt_mu_coneCorrPt() { return www.lbnt_mu_coneCorrPt(); }
const float &lbnt_mu_abseta() { return www.lbnt_mu_abseta(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4() { return www.jets_p4(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_up_p4() { return www.jets_up_p4(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_dn_p4() { return www.jets_dn_p4(); }
const vector<float> &jets_csv() { return www.jets_csv(); }
const vector<float> &jets_up_csv() { return www.jets_up_csv(); }
const vector<float> &jets_dn_csv() { return www.jets_dn_csv(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ak8jets_p4() { return www.ak8jets_p4(); }
const vector<float> &ak8jets_softdropMass() { return www.ak8jets_softdropMass(); }
const vector<float> &ak8jets_prunedMass() { return www.ak8jets_prunedMass(); }
const vector<float> &ak8jets_trimmedMass() { return www.ak8jets_trimmedMass(); }
const vector<float> &ak8jets_mass() { return www.ak8jets_mass(); }
const vector<float> &ak8jets_nJettinessTau1() { return www.ak8jets_nJettinessTau1(); }
const vector<float> &ak8jets_nJettinessTau2() { return www.ak8jets_nJettinessTau2(); }
const vector<float> &ak8jets_softdropPuppiSubjet1() { return www.ak8jets_softdropPuppiSubjet1(); }
const vector<float> &ak8jets_softdropPuppiSubjet2() { return www.ak8jets_softdropPuppiSubjet2(); }
const vector<float> &ak8jets_puppi_softdropMass() { return www.ak8jets_puppi_softdropMass(); }
const vector<float> &ak8jets_puppi_nJettinessTau1() { return www.ak8jets_puppi_nJettinessTau1(); }
const vector<float> &ak8jets_puppi_nJettinessTau2() { return www.ak8jets_puppi_nJettinessTau2(); }
const vector<float> &ak8jets_puppi_eta() { return www.ak8jets_puppi_eta(); }
const vector<float> &ak8jets_puppi_phi() { return www.ak8jets_puppi_phi(); }
const vector<float> &ak8jets_puppi_pt() { return www.ak8jets_puppi_pt(); }
const vector<float> &ak8jets_puppi_mass() { return www.ak8jets_puppi_mass(); }
const float &met_pt() { return www.met_pt(); }
const float &met_phi() { return www.met_phi(); }
const float &met_up_pt() { return www.met_up_pt(); }
const float &met_up_phi() { return www.met_up_phi(); }
const float &met_dn_pt() { return www.met_dn_pt(); }
const float &met_dn_phi() { return www.met_dn_phi(); }
const float &met_gen_pt() { return www.met_gen_pt(); }
const float &met_gen_phi() { return www.met_gen_phi(); }
const int &firstgoodvertex() { return www.firstgoodvertex(); }
const int &nTrueInt() { return www.nTrueInt(); }
const int &nVert() { return www.nVert(); }
const int &nisoTrack_mt2_cleaned_VVV_cutbased_veto() { return www.nisoTrack_mt2_cleaned_VVV_cutbased_veto(); }
const float &weight_btagsf() { return www.weight_btagsf(); }
const float &weight_btagsf_heavy_DN() { return www.weight_btagsf_heavy_DN(); }
const float &weight_btagsf_heavy_UP() { return www.weight_btagsf_heavy_UP(); }
const float &weight_btagsf_light_DN() { return www.weight_btagsf_light_DN(); }
const float &weight_btagsf_light_UP() { return www.weight_btagsf_light_UP(); }
const float &gen_ht() { return www.gen_ht(); }
const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &genPart_p4() { return www.genPart_p4(); }
const vector<int> &genPart_motherId() { return www.genPart_motherId(); }
const vector<int> &genPart_pdgId() { return www.genPart_pdgId(); }
const vector<int> &genPart_charge() { return www.genPart_charge(); }
const vector<int> &genPart_status() { return www.genPart_status(); }
const int &ngenLep() { return www.ngenLep(); }
const int &ngenLepFromTau() { return www.ngenLepFromTau(); }
const int &Flag_AllEventFilters() { return www.Flag_AllEventFilters(); }
const int &Flag_EcalDeadCellTriggerPrimitiveFilter() { return www.Flag_EcalDeadCellTriggerPrimitiveFilter(); }
const int &Flag_HBHEIsoNoiseFilter() { return www.Flag_HBHEIsoNoiseFilter(); }
const int &Flag_HBHENoiseFilter() { return www.Flag_HBHENoiseFilter(); }
const int &Flag_badChargedCandidateFilter() { return www.Flag_badChargedCandidateFilter(); }
const int &Flag_badMuonFilter() { return www.Flag_badMuonFilter(); }
const int &Flag_badMuonFilterv2() { return www.Flag_badMuonFilterv2(); }
const int &Flag_badChargedCandidateFilterv2() { return www.Flag_badChargedCandidateFilterv2(); }
const int &Flag_eeBadScFilter() { return www.Flag_eeBadScFilter(); }
const int &Flag_ecalBadCalibFilter() { return www.Flag_ecalBadCalibFilter(); }
const int &Flag_globalTightHalo2016() { return www.Flag_globalTightHalo2016(); }
const int &Flag_goodVertices() { return www.Flag_goodVertices(); }
const int &Flag_ecalLaserCorrFilter() { return www.Flag_ecalLaserCorrFilter(); }
const int &Flag_hcalLaserEventFilter() { return www.Flag_hcalLaserEventFilter(); }
const int &Flag_trackingFailureFilter() { return www.Flag_trackingFailureFilter(); }
const int &Flag_CSCTightHaloFilter() { return www.Flag_CSCTightHaloFilter(); }
const int &Flag_CSCTightHalo2015Filter() { return www.Flag_CSCTightHalo2015Filter(); }
const int &Flag_badMuons() { return www.Flag_badMuons(); }
const int &Flag_duplicateMuons() { return www.Flag_duplicateMuons(); }
const int &Flag_noBadMuons() { return www.Flag_noBadMuons(); }
const int &fastsimfilt() { return www.fastsimfilt(); }
const int &nVlep() { return www.nVlep(); }
const int &nTlep() { return www.nTlep(); }
const int &nTlepSS() { return www.nTlepSS(); }
const int &nLlep() { return www.nLlep(); }
const int &nSFOS() { return www.nSFOS(); }
const int &nSFOSinZ() { return www.nSFOSinZ(); }
const int &nj() { return www.nj(); }
const int &nj_up() { return www.nj_up(); }
const int &nj_dn() { return www.nj_dn(); }
const int &nj30() { return www.nj30(); }
const int &nj30_up() { return www.nj30_up(); }
const int &nj30_dn() { return www.nj30_dn(); }
const int &nb() { return www.nb(); }
const int &nb_up() { return www.nb_up(); }
const int &nb_dn() { return www.nb_dn(); }
const float &Mjj() { return www.Mjj(); }
const float &Mjj_up() { return www.Mjj_up(); }
const float &Mjj_dn() { return www.Mjj_dn(); }
const float &DRjj() { return www.DRjj(); }
const float &DRjj_up() { return www.DRjj_up(); }
const float &DRjj_dn() { return www.DRjj_dn(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet0_wtag_p4() { return www.jet0_wtag_p4(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet0_wtag_p4_up() { return www.jet0_wtag_p4_up(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet0_wtag_p4_dn() { return www.jet0_wtag_p4_dn(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1_wtag_p4() { return www.jet1_wtag_p4(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1_wtag_p4_up() { return www.jet1_wtag_p4_up(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1_wtag_p4_dn() { return www.jet1_wtag_p4_dn(); }
const float &MjjDR1() { return www.MjjDR1(); }
const float &MjjDR1_up() { return www.MjjDR1_up(); }
const float &MjjDR1_dn() { return www.MjjDR1_dn(); }
const float &DRjjDR1() { return www.DRjjDR1(); }
const float &DRjjDR1_up() { return www.DRjjDR1_up(); }
const float &DRjjDR1_dn() { return www.DRjjDR1_dn(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet0_wtag_p4_DR1() { return www.jet0_wtag_p4_DR1(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet0_wtag_p4_DR1_up() { return www.jet0_wtag_p4_DR1_up(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet0_wtag_p4_DR1_dn() { return www.jet0_wtag_p4_DR1_dn(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1_wtag_p4_DR1() { return www.jet1_wtag_p4_DR1(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1_wtag_p4_DR1_up() { return www.jet1_wtag_p4_DR1_up(); }
const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &jet1_wtag_p4_DR1_dn() { return www.jet1_wtag_p4_DR1_dn(); }
const float &MjjVBF() { return www.MjjVBF(); }
const float &MjjVBF_up() { return www.MjjVBF_up(); }
const float &MjjVBF_dn() { return www.MjjVBF_dn(); }
const float &DetajjVBF() { return www.DetajjVBF(); }
const float &DetajjVBF_up() { return www.DetajjVBF_up(); }
const float &DetajjVBF_dn() { return www.DetajjVBF_dn(); }
const float &MjjL() { return www.MjjL(); }
const float &MjjL_up() { return www.MjjL_up(); }
const float &MjjL_dn() { return www.MjjL_dn(); }
const float &DetajjL() { return www.DetajjL(); }
const float &DetajjL_up() { return www.DetajjL_up(); }
const float &DetajjL_dn() { return www.DetajjL_dn(); }
const float &MllSS() { return www.MllSS(); }
const float &MeeSS() { return www.MeeSS(); }
const float &Mll3L() { return www.Mll3L(); }
const float &Mee3L() { return www.Mee3L(); }
const float &Mll3L1() { return www.Mll3L1(); }
const float &M3l() { return www.M3l(); }
const float &Pt3l() { return www.Pt3l(); }
const float &M01() { return www.M01(); }
const float &M02() { return www.M02(); }
const float &M12() { return www.M12(); }
const int &isSFOS01() { return www.isSFOS01(); }
const int &isSFOS02() { return www.isSFOS02(); }
const int &isSFOS12() { return www.isSFOS12(); }
const float &DPhi3lMET() { return www.DPhi3lMET(); }
const float &DPhi3lMET_up() { return www.DPhi3lMET_up(); }
const float &DPhi3lMET_dn() { return www.DPhi3lMET_dn(); }
const float &DPhi3lMET_gen() { return www.DPhi3lMET_gen(); }
const float &MTmax() { return www.MTmax(); }
const float &MTmax_up() { return www.MTmax_up(); }
const float &MTmax_dn() { return www.MTmax_dn(); }
const float &MTmax_gen() { return www.MTmax_gen(); }
const float &MTmin() { return www.MTmin(); }
const float &MTmin_up() { return www.MTmin_up(); }
const float &MTmin_dn() { return www.MTmin_dn(); }
const float &MTmin_gen() { return www.MTmin_gen(); }
const float &MT3rd() { return www.MT3rd(); }
const float &MT3rd_up() { return www.MT3rd_up(); }
const float &MT3rd_dn() { return www.MT3rd_dn(); }
const float &MT3rd_gen() { return www.MT3rd_gen(); }
const float &MTmax3L() { return www.MTmax3L(); }
const float &MTmax3L_up() { return www.MTmax3L_up(); }
const float &MTmax3L_dn() { return www.MTmax3L_dn(); }
const float &MTmax3L_gen() { return www.MTmax3L_gen(); }
const int &passSSee() { return www.passSSee(); }
const int &passSSem() { return www.passSSem(); }
const int &passSSmm() { return www.passSSmm(); }
const int &lep_idx0_SS() { return www.lep_idx0_SS(); }
const int &lep_idx1_SS() { return www.lep_idx1_SS(); }
const TString &bkgtype() { return www.bkgtype(); }
const int &vetophoton() { return www.vetophoton(); }
const float &purewgt() { return www.purewgt(); }
const float &purewgt_up() { return www.purewgt_up(); }
const float &purewgt_dn() { return www.purewgt_dn(); }
const float &ffwgt() { return www.ffwgt(); }
const float &ffwgt_up() { return www.ffwgt_up(); }
const float &ffwgt_dn() { return www.ffwgt_dn(); }
const float &ffwgt_el_up() { return www.ffwgt_el_up(); }
const float &ffwgt_el_dn() { return www.ffwgt_el_dn(); }
const float &ffwgt_mu_up() { return www.ffwgt_mu_up(); }
const float &ffwgt_mu_dn() { return www.ffwgt_mu_dn(); }
const float &ffwgt_closure_up() { return www.ffwgt_closure_up(); }
const float &ffwgt_closure_dn() { return www.ffwgt_closure_dn(); }
const float &ffwgt_closure_el_up() { return www.ffwgt_closure_el_up(); }
const float &ffwgt_closure_el_dn() { return www.ffwgt_closure_el_dn(); }
const float &ffwgt_closure_mu_up() { return www.ffwgt_closure_mu_up(); }
const float &ffwgt_closure_mu_dn() { return www.ffwgt_closure_mu_dn(); }
const float &ffwgt_full_up() { return www.ffwgt_full_up(); }
const float &ffwgt_full_dn() { return www.ffwgt_full_dn(); }
const float &ffwgtqcd() { return www.ffwgtqcd(); }
const float &ffwgtqcd_up() { return www.ffwgtqcd_up(); }
const float &ffwgtqcd_dn() { return www.ffwgtqcd_dn(); }
const float &lepsf() { return www.lepsf(); }
const float &lepsf_up() { return www.lepsf_up(); }
const float &lepsf_dn() { return www.lepsf_dn(); }
const float &trigeff() { return www.trigeff(); }
const float &trigeff_up() { return www.trigeff_up(); }
const float &trigeff_dn() { return www.trigeff_dn(); }
const float &trigsf() { return www.trigsf(); }
const float &trigsf_up() { return www.trigsf_up(); }
const float &trigsf_dn() { return www.trigsf_dn(); }
const float &musmear_sf() { return www.musmear_sf(); }

}

#include "rooutil/rooutil.cc"
