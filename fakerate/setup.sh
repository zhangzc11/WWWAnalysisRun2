DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export LD_LIBRARY_PATH=$DIR:$LD_LIBRARY_PATH

# Copy Philip's histograms for preliminary fakerate.root for closure test.
# If you are running it for the first time this histmap/fakerate.root is meaningless and closure test histograms from your first output will be meaningless
if [ ! -d histmap/ ]; then
    cp -r /home/users/phchang/public_html/analysis/www/code/WWWAnalysisRun2/fakerate/histmap .
fi

source rooutil/thisrooutil.sh
source rooutil/root.sh
