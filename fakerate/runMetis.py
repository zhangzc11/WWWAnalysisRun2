##!/bin/env python

#_____________________________________________________________________________________________
# This script submits the jobs to condor
# It takes a while and it is not ideal to run over them on a local machine

#_____________________________________________________________________________________________
# Job tag and output hadoop path

# The following defines which set of fake rate baby ntuples to run over
input_fr_ntup_tag = "FR2017_v3.0.17"
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/".format(input_fr_ntup_tag)

# The following defines the tag for this round of submission (change it every time you submit)
data_year = "2017"
job_tag = "FR{}_analysis_v0.11.4".format(data_year)

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
        "WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM",
        "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",
        "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM",

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
# Create the samples mapping between the sample name -> the location of input sample hadoop directory
samples_map = {}
for sample in samples:
    samples_map[sample] = base_dir_path + "/MAKER_" + sample + "_" + input_fr_ntup_tag

# Now submit the job!
from rooutil import rooutil as ru
ru.submit_metis(
        job_tag,                                         # The tag for this round of submission
        samples_map,                                     # The dictionary of where the input locations are for a given sample
        tar_files=["doAnalysis", "setup.sh", "histmap"], # Files/directories to transfer to working nodes
        exec_script="metis.sh",                          # Executable to run for each condor job
        hadoop_dirname="franalysis")                     # Where the output of the condor jobs will be (i.e. /hadoop/cms/store/user/${USER}/metis/"hadoop_dirname")

#eof
