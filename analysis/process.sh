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
    echo
    exit
}

# Default value
CUTFLOW="-C"

# Command-line opts
while getopts ":i:t:uxh" OPTION; do
  case $OPTION in
    i) INPUT_BABY_VERSION=${OPTARG};;
    t) JOB_TAG=${OPTARG};;
    u) DO_USER_STUDY=" --user_study ";;
    u) CUTFLOW=" ";;
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

DDFAKEDIR=bkgdata/
if [[ ${INPUT_BABY_VERSION} == *"2016"* ]]; then
    DDFAKEDIR=data/
fi

mkdir -p outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/

echo "Submitting parallel jobs ... ==>"
echo "(below are individual bash commands)"
# Split a couple of big jobs by a few sub jobs
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_0.root      -T t_lostlep -j 3 -I 0 > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_0.log      2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_1.root      -T t_lostlep -j 3 -I 1 > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_1.log      2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_2.root      -T t_lostlep -j 3 -I 2 > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_2.log      2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/${DDFAKEDIR}  -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_0.root      -T t_ss -F   -j 3 -I 0 > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_0.log      2>&1) & # fake estimation
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/${DDFAKEDIR}  -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_1.root      -T t_ss -F   -j 3 -I 1 > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_1.log      2>&1) & # fake estimation
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/${DDFAKEDIR}  -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_2.root      -T t_ss -F   -j 3 -I 2 > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_2.log      2>&1) & # fake estimation
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/qflip.root          -T t_qflip             > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/qflip.log          2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/prompt.root         -T t_prompt            > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/prompt.log         2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/fakes.root          -T t_fakes             > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/fakes.log          2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/bkg/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/photon.root         -T t_photon            > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/photon.log         2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/data/         -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/data.root           -T t_ss                > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/data.log           2>&1) &
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sig/          -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/signal_private.root -T t_www               > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/signal_private.log 2>&1) & # Private sample generated over winter break by P.Chang
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sigofficial/  -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/signal.root         -T t_www               > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/signal.log         2>&1) & # Official CMS sample
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sigvh/        -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/vh_private.root     -T t_www               > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/vh_private.log     2>&1) & # Private sample generated over winter break by P.Chang
(set -x ;./doAnalysis ${CUTFLOW} -H ${DO_USER_STUDY} -i /nfs-7/userdata/phchang/WWW_babies/${INPUT_BABY_VERSION}/grouped/sigwww/       -o outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/www_private.root    -T t_www               > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/www_private.log    2>&1) & # Private sample generated over winter break by P.Chang
sleep 1;
echo "<== Submitted parallel jobs ..."
wait

echo ""
echo "Jobs finished ..."
echo ""
echo "Printing how long it took for each job."

tail -n 3 outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/*.log

# Hadd the split jobs result
hadd -f outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep.root outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep_*.root > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/lostlep.log
hadd -f outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes.root outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes_*.root > outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/ddfakes.log

echo "Done! outputs at outputs/${INPUT_BABY_VERSION}/${JOB_TAG}/*.root"
echo "Above is a report of how long each subjobs took"
