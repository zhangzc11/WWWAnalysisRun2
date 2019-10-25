##!/bin/env python

# This script submits the jobs to condor
# It takes a while and it is not ideal to run over them on a local machine

################
#
# There is only one setting to be aware of which is the job tag
#
################
# The following defines the tag for this round of submission (change it every time you submit)
job_tag = "test_2019_08_28_1020"

#_____________________________________________________________________________________________
# Create the samples mapping between the sample name -> the location of input sample hadoop directory and arguments map for each sample
samples_map = {}
arguments_map = {}
sample_list = []

tag = "v5.2.0"

# 2016
input_fr_ntup_tag = "FR2016_{}".format(tag)
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/merged".format(input_fr_ntup_tag)
samples_map[input_fr_ntup_tag+"_ss"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_ss"] = "0"
sample_list.append(input_fr_ntup_tag+"_ss")
samples_map[input_fr_ntup_tag+"_3l"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_3l"] = "1"
sample_list.append(input_fr_ntup_tag+"_3l")

# 2017
input_fr_ntup_tag = "FR2017_{}".format(tag)
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/merged".format(input_fr_ntup_tag)
samples_map[input_fr_ntup_tag+"_ss"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_ss"] = "0"
sample_list.append(input_fr_ntup_tag+"_ss")
samples_map[input_fr_ntup_tag+"_3l"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_3l"] = "1"
sample_list.append(input_fr_ntup_tag+"_3l")

# 2018
input_fr_ntup_tag = "FR2018_{}".format(tag)
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/merged".format(input_fr_ntup_tag)
samples_map[input_fr_ntup_tag+"_ss"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_ss"] = "0"
sample_list.append(input_fr_ntup_tag+"_ss")
samples_map[input_fr_ntup_tag+"_3l"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_3l"] = "1"
sample_list.append(input_fr_ntup_tag+"_3l")

# Now submit the job!
import pyrootutil as ru
ru.submit_metis(
        job_tag=job_tag,                                            # The tag for this round of submission
        sample_list=sample_list,                                    # The list of samples to submitted (in this case, the sample list is "sample_name"_ss or _3l.)
        samples_map=samples_map,                                    # The dictionary of where the input locations are for a given sample
        arguments_map=arguments_map,                                # The dictionary of whether to run same-sign or three-lepton
        tar_files=["doAnalysis", "setup.sh", "histmap", "rooutil"], # Files/directories to transfer to working nodes
        exec_script="metis.sh",                                     # Executable to run for each condor job
        hadoop_dirname="franalysis")                                # Where the output of the condor jobs will be (i.e. /hadoop/cms/store/user/${USER}/metis/"hadoop_dirname")

import os

# print "Done with {}".format(job_tag)

# os.system("mkdir -p outputs/{}/{}/ss".format(input_fr_ntup_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/dy.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/dy.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/DYJets*_ss*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/data_mu.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/data_mu.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Double*_ss*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/data_el.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/data_el.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Single*_ss*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/tt_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/tt_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Tune*_ss*/*.root"              .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/tt_1l.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/tt_1l.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Single*_ss*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/wj_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/wj_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_TuneCP5_13TeV*_ss*/*.root" .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/wj_ht.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/wj_ht.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_HT*_ss*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/ww.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/ww.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WW_TuneCP5_13TeV*_ss*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/wz.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/wz.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WZ_TuneCP5_13TeV*_ss*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/qcd_mu.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/qcd_mu.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*MuEnriched*_ss*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/qcd_em.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/qcd_em.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*EMEnriched*_ss*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/ss/qcd_bc.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/ss/qcd_bc.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*bcToE*_ss*/*.root"             .format(input_fr_ntup_tag, job_tag, job_tag))

# os.system("mkdir -p outputs/{}/{}/3l".format(input_fr_ntup_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/dy.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/dy.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/DYJets*_3l*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/data_mu.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/data_mu.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Double*_3l*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/data_el.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/data_el.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/Single*_3l*/*.root"                   .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/tt_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/tt_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Tune*_3l*/*.root"              .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/tt_1l.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/tt_1l.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/TTJets_Single*_3l*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/wj_incl.root" .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/wj_incl.root /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_TuneCP5_13TeV*_3l*/*.root" .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/wj_ht.root"   .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/wj_ht.root   /hadoop/cms/store/user/phchang/metis/franalysis/{}/WJetsToLNu_HT*_3l*/*.root"            .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/ww.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/ww.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WW_TuneCP5_13TeV*_3l*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/wz.root"      .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/wz.root      /hadoop/cms/store/user/phchang/metis/franalysis/{}/WZ_TuneCP5_13TeV*_3l*/*.root"         .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/qcd_mu.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/qcd_mu.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*MuEnriched*_3l*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/qcd_em.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/qcd_em.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*EMEnriched*_3l*/*.root"        .format(input_fr_ntup_tag, job_tag, job_tag))
# if not os.path.isfile("outputs/{}/{}/3l/qcd_bc.root"  .format(input_fr_ntup_tag, job_tag)): os.system("hadd outputs/{}/{}/3l/qcd_bc.root  /hadoop/cms/store/user/phchang/metis/franalysis/{}/QCD_Pt*bcToE*_3l*/*.root"             .format(input_fr_ntup_tag, job_tag, job_tag))

# print ""
# print "=============================================="
# print ""
# print ""
# print "Finished processing {} with fake rate baby {}!".format(job_tag, input_fr_ntup_tag)
# print "Your output should be outputs/{}/{}_3l and outputs/{}/{}_ss".format(input_fr_ntup_tag, job_tag, input_fr_ntup_tag, job_tag)
# print ""

#eof
