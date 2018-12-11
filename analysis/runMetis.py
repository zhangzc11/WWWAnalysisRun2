##!/bin/env python

from rooutil import rooutil as ru
import glob
import os

def main():

    data_year = "2017"
    job_tag = "test21"
    input_ntup_tag = "WWW_v1.2.2"
    input_ntup_tag = "OS2017_v4.0.5"
    input_ntup_tag = "WWW2016_v4.0.5"
    input_ntup_tag = "WWW2016_v4.0.6"
    input_ntup_tag = "WWW2017_v4.0.5"
    base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/".format(input_ntup_tag)
    tar_files = ["doAnalysis", "setup.sh", "scalefactors/*.root", "scalefactors/*/*/*/*/sf.root"]
    hadoop_dirname = "wwwanalysis"
    trees = ["t"] if "OS" in input_ntup_tag else ["t_lostlep", "t_fakes", "t_prompt", "t_qflip", "t_photon"]

    regions="SRSSee,SRSSem,SRSSmm,SRSSSideee,SRSSSideem,SRSSSidemm,SR0SFOS,SR1SFOS,SR2SFOS,WZCRSSee,WZCRSSem,WZCRSSmm,WZCR1SFOS,WZCR2SFOS,OSCRee,OSCRem,OSCRmm"
    regions="all"

    dohist = ""

    all_samples = glob.glob("{}/*".format(base_dir_path))

    samples_map = {}
    arguments_map = {}

    # Filter for defining good background sample
    def is_good_bkg_sample(x):
        bad_patterns = ["tZq", "WZTo3LNu_0Jets", "WZTo3LNu_1Jets", "WZTo3LNu_2Jets", "WZTo3LNu_3Jets", "WZTo3LNu_13TeV", "WZ_Tune", "Wprime", "Photophobic", "SMS", "Doubly", "PrivateWWW"]
        for bad_pattern in bad_patterns:
            if bad_pattern in x:
                return False
        return True

    # Filter for defining good signal sample
    def is_good_sig_sample(x):
        good_patterns = ["MAKER_WWW_4", "VHToNonbb", "PrivateWWW"]
        for good_pattern in good_patterns:
            if good_pattern in x:
                return True
        return False

    # Bkg sample
    for sample_dir_path in [ x for x in all_samples if "MAKER_WWW_" not in x and "_Run201" not in x and is_good_bkg_sample(x) ]:
        for tree in trees + ["t_ss"]:
            sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
            samples_map[sample_name] = sample_dir_path
            arguments_map[sample_name] = "{} {} {} {}".format(tree, tree, regions, dohist)

    # Signal sample
    for sample_dir_path in [ x for x in all_samples if is_good_sig_sample(x) ]:
        tree = "t" if "OS" in input_ntup_tag else "t_www"
        sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
        samples_map[sample_name] = sample_dir_path
        arguments_map[sample_name] = "{} {} {} {}".format(tree, tree, regions, dohist)

    # Data sample
    for sample_dir_path in [ x for x in all_samples if "_Run201" in x ]:
        tree = "t" if "OS" in input_ntup_tag else "t_ss"
        sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
        samples_map[sample_name] = sample_dir_path
        arguments_map[sample_name] = "{} {} {} {}".format(tree, tree, regions, dohist)

    # Data-driven fake estimate and ewksubtraction only for SS analysis and not for opposite sign (OS)
    if "OS" not in input_ntup_tag:
        # Data-driven fake sample
        for sample_dir_path in [ x for x in all_samples if "_Run201" in x ]:
            tree = "t_ddfakes"
            sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
            samples_map[sample_name] = sample_dir_path
            arguments_map[sample_name] = "{} {} {} {}".format("t_ss", tree, regions, dohist)

        # Electroweak subtraction in data-drivek fake estimate
        for sample_dir_path in [ x for x in all_samples if "_Run201" not in x and is_good_bkg_sample(x) ]:
            tree = "t_ewksubt"
            sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
            samples_map[sample_name] = sample_dir_path
            arguments_map[sample_name] = "{} {} {} {}".format("t_ss", tree, regions, dohist)

    for sample in sorted(samples_map.keys()):
        print sample, arguments_map[sample]

    ru.submit_metis(job_tag, samples_map, arguments_map=arguments_map, tar_files=tar_files, hadoop_dirname=hadoop_dirname+"/"+input_ntup_tag, files_per_output=1, globber="merged/*.root" if "OS" not in input_ntup_tag else "*.root", sites="T2_US_UCSD")

    os.system("mkdir -p outputs/condor/{}/{}/".format(input_ntup_tag, job_tag))

#    exclusion = " | grep -v WZ_Tune | grep -v WZTo3LNu_0Jets | grep -v WZTo3LNu_1Jets | grep -v WZTo3LNu_2Jets | grep -v WZTo3LNu_3Jets | grep -v WZTo3LNu_13TeV"
    exclusion = " | grep -v WpWpJJ | grep -v ttWJet"
    if not os.path.isfile("outputs/condor/{}/{}/signal.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/signal.root       /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*_t_www*/*.root"           .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/data.root"    .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/data.root         /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*Run201*t_ss*/*.root"      .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/ddfakes.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/ddfakes.root      /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*Run201*t_ddfakes*/*.root" .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/ewksubt.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/ewksubt.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_ewksubt*/*.root | grep -v WJetsToLNu_Tune)" .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))

    if not os.path.isfile("outputs/condor/{}/{}/lostlep.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/lostlep.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_lostlep*/*.root)"    .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/fakes.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/fakes.root   $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_fakes*/*.root)"      .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/photon.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/photon.root  $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_photon*/*.root)"     .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/prompt.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/prompt.root  $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_prompt*/*.root)"     .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/qflip.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/qflip.root   $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_qflip*/*.root)"      .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))

    if not os.path.isfile("outputs/condor/{}/{}/vbsww.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/vbsww.root   $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*WpWpJJ*t_ss*/*.root)"     .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/ttw.root"     .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/ttw.root     $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*TTWJet*t_ss*/*.root)"     .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag))

    if not os.path.isfile("outputs/condor/{}/{}/lostlep_fit.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/lostlep_fit.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_lostlep*/*.root {})"    .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/fakes_fit.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/fakes_fit.root   $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_fakes*/*.root {})"      .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/photon_fit.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/photon_fit.root  $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_photon*/*.root {})"     .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/prompt_fit.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/prompt_fit.root  $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_prompt*/*.root {})"     .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/qflip_fit.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/qflip_fit.root   $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/{}/*t_qflip*/*.root {})"      .format (input_ntup_tag, job_tag, input_ntup_tag, job_tag, exclusion))


    print ""
    print "=============================================="
    print ""
    print ""
    print "Finished processing {} with www baby {}!".format(job_tag, input_ntup_tag)
    print "Your output should be outputs/condor/{}/{}".format(input_ntup_tag, job_tag)
    print ""


if __name__ == "__main__":
    main()

#eof
