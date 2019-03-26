export SCRAM_ARCH=slc6_amd64_gcc530
export CMSSW_VERSION=CMSSW_8_1_0
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_8_1_0
cd CMSSW_8_1_0/src 
cmsenv
git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
git clone https://github.com/cms-analysis/CombineHarvester.git CombineHarvester
cd HiggsAnalysis/CombinedLimit
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
git fetch origin
git checkout v7.0.12
scramv1 b clean; scramv1 b # always make a clean build
cd $CMSSW_BASE/../
