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

Batch jobs can be submitted using aminnj/ProjectMetis.git

    # Setup Metis
    cd ProjectMetis/
    source setup.sh
    python runMetis_v2.py # submits jobs to condor (change the job_tag in the script the next time you submit the job)

Plotting is done via ```makeplot.py```

    # > python makeplot.py INPUT_NTUP_TAG ANALYSIS_TAG
    python makeplot_v2.py FR2017_v3.0.17 FR2017_analysis_v1.0.0 # This is an example

Once the plotting script runs, it also writes out ```fakerate_ss.root``` and ```fakerate_3l.root``` which is also used for closure test.
In order to perform the closure test, one needs to submit the batch job again.
