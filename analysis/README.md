# WWW Analysis

WWW analysis code for both 2016/2017.
This area started for 2017 analysis with eventual integration of 2016 into a single event looper in mind.

The analysis ran over the ntuple babies created from cmstas/VVVBabyMaker.
As of Nov. 2018, latest 2017 ntuple baby is:

    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v4.0.5/skim/

## Quick start

    git clone --recurse-submodules git@github.com:sgnoohc/WWWAnalysisRun2.git
    cd WWWAnalysis/analysis/
    source setup.sh
    make clean
    make -j2
    sh run.sh WWW2017_v4.0.5 test1
    # Or to submit in batch to condor
    python runMetis.py
    # Once the job has finished plot using
    python makeplot.py
