# WWW Analysis

WWW analysis code for both 2016/2017.
This area started for 2017 analysis with eventual integration of 2016 into a single event looper in mind.

The analysis ran over the ntuple babies created from cmstas/VVVBabyMaker.
As of Mar. 2019, latest 2017 ntuple baby is:

    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/sig
    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/sigofficial
    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg
    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/data

## Quick start

    git clone --recurse-submodules git@github.com:sgnoohc/WWWAnalysisRun2.git
    cd WWWAnalysis/analysis/
    source setup.sh
    make clean
    make -j
    time sh process.sh # should take about ~2 mins

If it complains about missing ```.root``` files for some scalefactors, then try deleting ```scalefactors/``` and trying again

## Understanding the code

I recommend reading ```main.cc```. I really tried putting a lot of comments to help user understand what is going on.
If you have any questions, ask <philip@ucsd.edu>.
After reading main.cc, If there is a specific non-trivial task that isn't clear how to do from existing examples, let me know as well.
