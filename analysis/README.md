# WWW Analysis

WWW analysis code for both 2016/2017.

This area started for 2017 analysis with eventual integration of 2016 into a single event looper in mind.

The analysis ran over the ntuple babies created from cmstas/VVVBabyMaker.

As of Mar. 2019, latest 2017 ntuple baby is:

    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/sig
    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/sigofficial
    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg
    /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/data

## Understanding the code

I recommend reading ```main.cc```. I really tried putting a lot of comments to help user understand what is going on.

If you have any questions, ask <philip@ucsd.edu>.

After reading main.cc, If there is a specific non-trivial task that isn't clear how to do from existing examples, let me know as well.

## Quick start

    git clone --recurse-submodules https://github.com/cmstas/WWWAnalysisRun2.git
    cd WWWAnalysisRun2/analysis/
    source setup.sh
    make clean
    make -j
    time sh process.sh -i WWW2017_v5.0.0 -t test1 # should take about ~2 mins
    python plot.py --use_private_sig_sample -i outputs/WWW2017_v5.0.0/test1 "SRSSmmNb0__lep_pt1"             # To plot sub-leading lepton pt in mm channel at b-veto cut stage
    # Make sure to run the following command with -b,--blind option because it gets awfully close to signal region and we do not want to see data
    python plot.py --use_private_sig_sample -i outputs/WWW2017_v5.0.0/test1 "SR0SFOSNb0__minDRllOS"  --blind # To plot Yifan's new variable she's studying for separating WH v. WWW
    python plot.py --use_private_sig_sample -i outputs/WWW2017_v5.0.0/test1 "SR0SFOSFull__minDRllOS" --blind # To plot Yifan's new variable she's studying for separating WH v. WWW
    python plot.py --use_private_sig_sample -i outputs/WWW2017_v5.0.0/test1                                  # To plot 9 bin SR yield plot and 5 bin lost lep CR plot

The yield plot produced from the last command should more or less match the result presented at CMS Week Feb. (https://indico.cern.ch/event/795443/)

If it complains about missing ```.root``` files for some scalefactors, then try deleting ```scalefactors/``` and trying again

If the process.sh ran successfully, use ```plot.py``` for plotting

For more histogram names and information read through ```main.cc```.

In short, the histogram names are formatted as, "<CutName>__<HistName>".

And cut names are defined in ```main.cc``` with various "addCut" functions, 

And histogram names are defined in ```main.cc``` with various "addHistogram" functions.

However, __I really recommend reading through ```main.cc```__ as I mentioned in previous section.

## Plotting options

If you have any questions let me know

    $ python plot.py -h
    usage: plot.py [-h] -i INPUT_DIR [-o OUTPUT_DIR] [-n NBINS] [-y YAXIS_RANGE]
                   [-l] [-s SIG_SCALE] [-u] [-S] [-P]
                   [FILTER_PATTERN [FILTER_PATTERN ...]]
    
    Plot dumper from Run 2 WWW Analysis
    
    positional arguments:
      FILTER_PATTERN        patterns to use to filter histograms to dump
    
    optional arguments:
      -h, --help            show this help message and exit
      -i INPUT_DIR, --input_dir INPUT_DIR
                            input dir path (where hists are)
      -o OUTPUT_DIR, --output_dir OUTPUT_DIR
                            output dir path
      -n NBINS, --nbins NBINS
                            number of bins for the histograms
      -y YAXIS_RANGE, --yaxis_range YAXIS_RANGE
                            Y-axis range set by user
      -l, --yaxis_log       Y-axis set to log
      -s SIG_SCALE, --sig_scale SIG_SCALE
                            Signal scale
      -u, --rm_udflow       Remove underflow
      -S, --do_scan         Do cut scan
      -P, --use_private_sig_sample
                            Use private signal sample

