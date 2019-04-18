##!/bin/env python

# This script submits the jobs to condor
# It takes a while and it is not ideal to run over them on a local machine

################
#
# There is only one setting to be aware of which is the job tag
#
################
# The following defines the tag for this round of submission (change it every time you submit)
job_tag = "FR2017_analysis_v1.0.0"



#_____________________________________________________________________________________________
# Job tag and output hadoop path

# The following defines which set of fake rate baby ntuples to run over
input_fr_ntup_tag = "FR2017_v3.0.17"
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/".format(input_fr_ntup_tag)

# These are the list of samples that will be submitted
samples = [

        "QCD_Pt_15to20_bcToE_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1_MINIAODSIM",
        "QCD_Pt_20to30_bcToE_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1_MINIAODSIM",
        "QCD_Pt_30to80_bcToE_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1_MINIAODSIM",
        "QCD_Pt_80to170_bcToE_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1_MINIAODSIM",
        "QCD_Pt_170to250_bcToE_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1_MINIAODSIM",
        "QCD_Pt_250toInf_bcToE_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v11-v1_MINIAODSIM",

        "QCD_Pt-15to20_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",

        "QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        # Missing 470
        "QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",

        "TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",

        "WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM",
        "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM",

        "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",

        "WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2_MINIAODSIM",

        "DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",

        "WW_TuneCP5_13TeV-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM",
        "WZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",

        "DoubleMuon_Run2017B-31Mar2018-v1_MINIAOD",
        "DoubleMuon_Run2017C-31Mar2018-v1_MINIAOD",
        "DoubleMuon_Run2017D-31Mar2018-v1_MINIAOD",
        "DoubleMuon_Run2017E-31Mar2018-v1_MINIAOD",
        "DoubleMuon_Run2017F-31Mar2018-v1_MINIAOD",
        "SingleElectron_Run2017B-31Mar2018-v1_MINIAOD",
        "SingleElectron_Run2017C-31Mar2018-v1_MINIAOD",
        "SingleElectron_Run2017D-31Mar2018-v1_MINIAOD",
        "SingleElectron_Run2017E-31Mar2018-v1_MINIAOD",
        "SingleElectron_Run2017F-31Mar2018-v1_MINIAOD",

        ]

#_____________________________________________________________________________________________
# Create the samples mapping between the sample name -> the location of input sample hadoop directory and arguments map for each sample
samples_map = {}
arguments_map = {}
sample_list = []
for sample in samples:
    samples_map[sample+"_ss"] = base_dir_path + "/MAKER_" + sample + "_" + input_fr_ntup_tag
    arguments_map[sample+"_ss"] = "0"
    sample_list.append(sample+"_ss")
    samples_map[sample+"_3l"] = base_dir_path + "/MAKER_" + sample + "_" + input_fr_ntup_tag
    arguments_map[sample+"_3l"] = "1"
    sample_list.append(sample+"_3l")

# Now submit the job!
from rooutil import rooutil as ru
# ru.submit_metis(
#         job_tag=job_tag,                                 # The tag for this round of submission
#         sample_list=sample_list,                         # The list of samples to submitted (in this case, the sample list is "sample_name"_ss or _3l.)
#         samples_map=samples_map,                         # The dictionary of where the input locations are for a given sample
#         arguments_map=arguments_map,                     # The dictionary of whether to run same-sign or three-lepton
#         tar_files=["doAnalysis", "setup.sh", "histmap"], # Files/directories to transfer to working nodes
#         exec_script="metis.sh",                          # Executable to run for each condor job
#         hadoop_dirname="franalysis")                     # Where the output of the condor jobs will be (i.e. /hadoop/cms/store/user/${USER}/metis/"hadoop_dirname")

import os

print "Done with {}".format(job_tag)

os.system("mkdir -p outputs/{}/{}/ss".format(input_fr_ntup_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/dy.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/dy.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/DYJets*_ss*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/data_mu.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/data_mu.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Double*_ss*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/data_el.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/data_el.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Single*_ss*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/tt_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/tt_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Tune*_ss*/*.root"              .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/tt_1l.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/tt_1l.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Single*_ss*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/wj_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/wj_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_TuneCP5_13TeV*_ss*/*.root" .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/wj_ht.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/wj_ht.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_HT*_ss*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/ww.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/ww.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WW_TuneCP5_13TeV*_ss*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/wz.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/wz.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WZ_TuneCP5_13TeV*_ss*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/qcd_mu.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/qcd_mu.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*MuEnriched*_ss*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/qcd_em.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/qcd_em.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*EMEnriched*_ss*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/ss/qcd_bc.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/qcd_bc.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*bcToE*_ss*/*.root"             .format(input_fr_ntup_tag, job_tag, job_tag))

os.system("mkdir -p outputs/{}/{}/3l".format(input_fr_ntup_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/dy.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/dy.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/DYJets*_3l*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/data_mu.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/data_mu.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Double*_3l*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/data_el.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/data_el.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Single*_3l*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/tt_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/tt_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Tune*_3l*/*.root"              .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/tt_1l.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/tt_1l.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Single*_3l*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/wj_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/wj_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_TuneCP5_13TeV*_3l*/*.root" .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/wj_ht.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/wj_ht.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_HT*_3l*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/ww.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/ww.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WW_TuneCP5_13TeV*_3l*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/wz.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/wz.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WZ_TuneCP5_13TeV*_3l*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/qcd_mu.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/qcd_mu.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*MuEnriched*_3l*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/qcd_em.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/qcd_em.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*EMEnriched*_3l*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
if not os.path.isfile("outputs/{}/{}/3l/qcd_bc.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/qcd_bc.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*bcToE*_3l*/*.root"             .format(input_fr_ntup_tag, job_tag, job_tag))

print ""
print "=============================================="
print ""
print ""
print "Finished processing {} with fake rate baby {}!".format(job_tag, input_fr_ntup_tag)
print "Your output should be outputs/{}/{}_3l and outputs/{}/{}_ss".format(input_fr_ntup_tag, job_tag, input_fr_ntup_tag, job_tag)
print ""

#eof
