# Fake rate analysis

This will loop over the fake rate babies produced by the VVVBabyMaker and write fake rate measurement related histograms

## Quick start

    git clone --recurse-submodules git@github.com:sgnoohc/WWWAnalysisRun2.git
    cd WWWAnalysis/fakerate/
    source setup.sh # will copy over some histograms so that the code can run
    make clean
    make -j2
    # Test a job to make sure things don't crash
    # ./doAnalysis /nfs-7/userdata/phchang/WWW_babies/FR2017_v3.0.17/link/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM_output_1.root test.root -1
    python runMetis.py # submits jobs to condor (change the job_tag in the script the next time you submit the job)
