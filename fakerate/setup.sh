export SCRAM_ARCH=slc6_amd64_gcc530   # or whatever scram_arch you need for your desired CMSSW release
export CMSSW_VERSION=CMSSW_9_2_0
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/cmssw/$CMSSW_VERSION/src
eval `scramv1 runtime -sh`
cd - > /dev/null

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export LD_LIBRARY_PATH=$DIR:$LD_LIBRARY_PATH

# Copy Philip's histograms for preliminary fakerate.root for closure test.
# If you are running it for the first time this histmap/fakerate.root is meaningless and closure test histograms from your first output will be meaningless
cp -r /home/users/phchang/public_html/analysis/www/code/WWWAnalysisRun2/fakerate/histmap .
