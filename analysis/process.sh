#!/bin/bash

trap "kill 0" EXIT

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Help
usage()
{
    echo "ERROR - Usage:"
    echo
    echo "      sh $(basename $0) OPTIONSTRINGS ..."
    echo
    echo "Options with arguments:"
    echo "  -h    Help                   (Display this message)"
    echo "  -i    Input baby version     (e.g. -i WWW2017_v5.0.0)"
    echo "  -t    Job tag                (e.g. -t test1)"
    echo "  -u    Enable user study"
    echo "  -x    Skip cutflow histograms"
    echo "  -s    Do systematics"             
    echo
    exit
}

# Default value
CUTFLOW="-C"

# Command-line opts
while getopts ":i:t:uxsh" OPTION; do
  case $OPTION in
    i) INPUT_BABY_VERSION=${OPTARG};;
    t) JOB_TAG=${OPTARG};;
    u) DO_USER_STUDY=" --user_study ";;
    x) CUTFLOW=" ";;
    s) SYSTEMATICS=" -S";;
    h) usage;;
    :) usage;;
  esac
done

if [ -z ${INPUT_BABY_VERSION} ]; then usage; fi
if [ -z ${JOB_TAG}  ]; then usage; fi

# to shift away the parsed options
shift $(($OPTIND - 1))

# Verbose
date
echo "================================================"
echo "$(basename $0) $*"
echo "$(basename $0) $*" >> $DIR/.$(basename $0).history
echo "------------------------------------------------"
echo "INPUT_BABY_VERSION  : ${INPUT_BABY_VERSION}"
echo "JOB_TAG             : ${JOB_TAG}"
echo "================================================"

# DDFAKEDIR=data/
DDFAKEDIR=bkgdata/
if [[ ${INPUT_BABY_VERSION} == *"2016"* ]]; then
    DDFAKEDIR=data/
fi

mkdir -p hists/${INPUT_BABY_VERSION}/${JOB_TAG}/

echo "Submitting parallel jobs ... ==>"
echo "(below are individual bash commands)"
# Split a couple of big jobs by a few sub jobs
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/${DDFAKEDIR}  -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_0.root      -T t_ss -F   -j 3 -I 0 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_0.log      2>&1) & # fake estimation
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/${DDFAKEDIR}  -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_1.root      -T t_ss -F   -j 3 -I 1 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_1.log      2>&1) & # fake estimation
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/${DDFAKEDIR}  -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_2.root      -T t_ss -F   -j 3 -I 2 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_2.log      2>&1) & # fake estimation
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_0.root      -T t_lostlep -j 3 -I 0 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_0.log      2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_1.root      -T t_lostlep -j 3 -I 1 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_1.log      2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_2.root      -T t_lostlep -j 3 -I 2 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_2.log      2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/qflip.root          -T t_qflip             > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/qflip.log          2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/prompt.root         -T t_prompt            > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/prompt.log         2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fakes.root          -T t_fakes             > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fakes.log          2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/photon.root         -T t_photon            > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/photon.log         2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/data/         -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/data.root           -T t_ss                > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/data.log           2>&1) &
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sig/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/signal_private.root -T t_www               > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/signal_private.log 2>&1) & # Private sample generated over winter break by P.Chang
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sigofficial/  -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/signal.root         -T t_www               > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/signal.log         2>&1) & # Official CMS sample
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sigvh/        -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/vh_private.root     -T t_www               > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/vh_private.log     2>&1) & # Private sample generated over winter break by P.Chang
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sigwww/       -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/www_private.root    -T t_www               > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/www_private.log    2>&1) & # Private sample generated over winter break by P.Chang
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_0.root   -T t_lostlep -j 3 -I 0 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_0.log   2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_1.root   -T t_lostlep -j 3 -I 1 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_1.log   2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_2.root   -T t_lostlep -j 3 -I 2 > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_2.log   2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitqflip.root       -T t_qflip             > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitqflip.log       2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitprompt.root      -T t_prompt            > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitprompt.log      2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitfakes.root       -T t_fakes             > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitfakes.log       2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkgnonvbsttw/ -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitphoton.root      -T t_photon            > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitphoton.log      2>&1) & # These are for fits where vbs and ttw are not included
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/vbs/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/vbs.root            -T t_ss                > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/vbs.log            2>&1) & # All of VBS samples
(set -x ;./doAnalysis ${SYSTEMATICS} ${CUTFLOW} -L -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/ttw/          -o hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ttw.root            -T t_ss                > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ttw.log            2>&1) & # All of TTW samples
sleep 1;
echo "<== Submitted parallel jobs ..."
wait

echo ""
echo "Jobs finished ..."
echo ""
echo "Printing how long it took for each job."

tail -n 3 hists/${INPUT_BABY_VERSION}/${JOB_TAG}/*.log

# Hadd the split jobs result
echo "Hadding some histogram outputs ... ==>"
(set -x ; hadd hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep.root hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_*.root > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep.log) &
(set -x ; hadd hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes.root hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_*.root > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes.log) &
(set -x ; hadd hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep.root hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep_*.root > hists/${INPUT_BABY_VERSION}/${JOB_TAG}/fitlostlep.log) &
wait
echo "<== Done hadding histogram outputs!"

echo "histograms are at hists/${INPUT_BABY_VERSION}/${JOB_TAG}/*.root"
echo "You can find a print out of how long each subjobs took above for reference"
