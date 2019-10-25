#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export SCRAM_ARCH=slc6_amd64_gcc530
export CMSSW_VERSION=CMSSW_8_1_0
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_8_1_0
cd $DIR/CMSSW_8_1_0/src 
cmsenv
cd -

if [ -z $1 ]; then echo "sh $0 COMBINECARD.txt"; exit; fi
combine -M ProfileLikelihood --significance $1 -t -1 --expectSignal=1 --rMin -50 --rMax 50
#combine -M ProfileLikelihood --significance $1 --rMin -50 --rMax 50
#combine -M Asymptotic $1
