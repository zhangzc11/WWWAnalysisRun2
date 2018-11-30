##!/bin/env python

from rooutil import rooutil as ru
import glob
import os

def main():

    data_year = "2017"
    job_tag = "test1"
    input_ntup_tag = "OS2017_v4.0.5"
    input_ntup_tag = "WWW2017_v4.0.5"
    base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/".format(input_ntup_tag)
    tar_files = ["doAnalysis", "setup.sh", "scalefactors/*.root", "scalefactors/*/*/*/*/sf.root"]
    hadoop_dirname = "wwwanalysis"
    trees = ["t"] if "OS" in input_ntup_tag else ["t_lostlep", "t_fakes", "t_prompt", "t_qflip", "t_photon"]

    regions="SRSSee,SRSSem,SRSSmm,SRSSSideee,SRSSSideem,SRSSSidemm,SR0SFOS,SR1SFOS,SR2SFOS,WZCRSSee,WZCRSSem,WZCRSSmm,WZCR1SFOS,WZCR2SFOS,OSCRee,OSCRem,OSCRmm"
    regions="all"

    all_samples = glob.glob("{}/*".format(base_dir_path))

    samples_map = {}
    arguments_map = {}

    # Bkg sample
    for sample_dir_path in [ x for x in all_samples if "WWW_" not in x and "_Run2017" not in x and "tZq" not in x]:
        for tree in trees:
            sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
            samples_map[sample_name] = sample_dir_path
            arguments_map[sample_name] = "{} {} {}".format(tree, tree, regions)

    # Signal sample
    for sample_dir_path in [ x for x in all_samples if "WWW_" in x or "VHToNonbb" in x ]:
        tree = "t" if "OS" in input_ntup_tag else "t_www"
        sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
        samples_map[sample_name] = sample_dir_path
        arguments_map[sample_name] = "{} {} {}".format(tree, tree, regions)

    # Data sample
    for sample_dir_path in [ x for x in all_samples if "_Run2017" in x ]:
        tree = "t" if "OS" in input_ntup_tag else "t_ss"
        sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
        samples_map[sample_name] = sample_dir_path
        arguments_map[sample_name] = "{} {} {}".format(tree, tree, regions)

    # Data-driven fake estimate and ewksubtraction only for SS analysis and not for opposite sign (OS)
    if "OS" not in input_ntup_tag:
        # Data-driven fake sample
        for sample_dir_path in [ x for x in all_samples if "_Run2017" in x ]:
            tree = "t_ddfakes"
            sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
            samples_map[sample_name] = sample_dir_path
            arguments_map[sample_name] = "{} {} {}".format("t_ss", tree, regions)

        # Electroweak subtraction in data-drivek fake estimate
        for sample_dir_path in [ x for x in all_samples if "_Run2017" not in x and "tZq" not in x]:
            tree = "t_ewksubt"
            sample_name = sample_dir_path.split("MAKER_")[1].split("_"+input_ntup_tag)[0] + "_" + tree
            samples_map[sample_name] = sample_dir_path
            arguments_map[sample_name] = "{} {} {}".format("t_ss", tree, regions)

    #ru.submit_metis(job_tag, samples_map, arguments_map=arguments_map, tar_files=tar_files, hadoop_dirname=hadoop_dirname, files_per_output=1, globber="merged/*.root" if "OS" not in input_ntup_tag else "*.root", sites="T2_US_UCSD,UAF,LOCAL")

    os.system("mkdir -p outputs/condor/{}/{}/".format(input_ntup_tag, job_tag))

    exclusion = " | grep -v WZ_Tune | grep -v WZTo3LNu_0Jets | grep -v WZTo3LNu_1Jets | grep -v WZTo3LNu_2Jets | grep -v WZTo3LNu_3Jets | grep -v WZTo3LNu_13TeV"
    if not os.path.isfile("outputs/condor/{}/{}/signal.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/signal.root  /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*_t_www*/*.root"             .format (input_ntup_tag, job_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/data.root"    .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/data.root    /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*Run2017*t_ss*/*.root"       .format (input_ntup_tag, job_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/ddfakes.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/ddfakes.root /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*Run2017*t_ddfakes*/*.root"  .format (input_ntup_tag, job_tag, job_tag))
    if not os.path.isfile("outputs/condor/{}/{}/lostlep.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/lostlep.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*t_lostlep*/*.root {})" .format (input_ntup_tag, job_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/fakes.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/fakes.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*t_fakes*/*.root {})"     .format (input_ntup_tag, job_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/photon.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/photon.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*t_photon*/*.root {})"   .format (input_ntup_tag, job_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/prompt.root"  .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/prompt.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*t_prompt*/*.root {})"   .format (input_ntup_tag, job_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/qflip.root"   .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/qflip.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*t_qflip*/*.root {})"     .format (input_ntup_tag, job_tag, job_tag, exclusion))
    if not os.path.isfile("outputs/condor/{}/{}/ewksubt.root" .format (input_ntup_tag, job_tag)): os.system("hadd outputs/condor/{}/{}/ewksubt.root $(ls /hadoop/cms/store/user/phchang/metis/wwwanalysis/{}/*t_ewksubt*/*.root {} | grep -v WJetsToLNu_Tune)" .format (input_ntup_tag, job_tag, job_tag, exclusion))

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
