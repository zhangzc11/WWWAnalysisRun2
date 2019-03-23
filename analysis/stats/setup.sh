export SCRAM_ARCH=slc6_amd64_gcc530
export CMSSW_VERSION=CMSSW_8_1_0
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_8_1_0
pushd CMSSW_8_1_0/src 
cmsenv
cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
popd
