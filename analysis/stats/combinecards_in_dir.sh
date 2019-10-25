#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export SCRAM_ARCH=slc6_amd64_gcc530
export CMSSW_VERSION=CMSSW_8_1_0
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_8_1_0
cd $DIR/CMSSW_8_1_0/src 
cmsenv
cd -

usage() {
    echo "Usage:"
    echo ""
    echo "  sh $0 DIR_CONTAINING_INDIVIDUAL_DATACARDS/ OUTPUT_TXT_PATH"
    echo ""
    exit
}

if [ -z $1 ]; then usage; fi
if [ -z $2 ]; then usage; fi

OPTSTRING=""
INDEX=1
for i in $(ls $1/*.txt); do
    OPTSTRING="${OPTSTRING} b$INDEX=$i"
    INDEX=$((INDEX+1))
done

combineCards.py ${OPTSTRING} > $2
