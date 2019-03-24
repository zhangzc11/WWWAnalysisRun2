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
    git fetch && git fetch --tags
    git checkout looper_instruction_v2
    git submodule update --init --recursive
    source ./setup.sh
    make clean
    make -j
    time sh ./process.sh -i WWW2017_v5.0.0 -t test1 # should take about a minute
    ## To Print plotting options
    python ./plot.py -h
    ## Read the options for more information
    ## Brlow are some examples for plotting
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SRSSmmNj2__lep_pt0" -n 30 -S -v                                                 # To plot leading lepton pt in mm channel at preselection
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SRSSmmNj2__lep_pt1" -n 30 -S -v -m                                              # To plot sub-leading lepton pt in mm channel at preselection (Where fake is from MC directly, toggle option -m to see data-driven v. MC estimate)
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SRSSmmNj2__Mjj" -n 30 -S -v                                                     # To plot Mjj in mm channel at preselection
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SRSSmmNj2__Mjj,SRSSemNj2__Mjj,SRSSeeNj2__Mjj" -n 30 -S -v -a -O SRSSNj2__Mjj    # To plot Mjj in ee,em,mm channel combined at preselection and rename it "SRSSNj2__Mjj"
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SRSSmmNj2__Mjj" -n 30 -S -v                                                     # To plot Mjj in mm channel at preselection
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SR0SFOSDYVeto__minDRllOS" -n 6 -S -v                                            # To plot Yifan's new variable she's studying for separating WH v. WWW
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1 "SR0SFOSFull__minDRllOS"  -n 3 -S -v                                             # To plot Yifan's new variable she's studying for separating WH v. WWW
    python ./plot.py --use_private_sig_sample -i hists/WWW2017_v5.0.0/test1                                                                                  # To plot 9 bin SR and and 5 bin lost-lepton CR plots

The yield plot produced from the last command should more or less match the result presented at CMS Week Feb. (https://indico.cern.ch/event/795443/)

If it complains about missing ```.root``` files for some scalefactors, then try deleting ```scalefactors/``` and trying again

If the process.sh ran successfully, use ```plot.py``` for plotting

For more histogram names and information read through ```main.cc```.

In short, the histogram names are formatted as, "<CutName>__<HistName>".

And cut names are defined in ```main.cc``` with various "addCut" functions, 

And histogram names are defined in ```main.cc``` with various "addHistogram" functions.

However, __I really recommend reading through ```main.cc```__ as I mentioned in previous section.


## Quick start to reproduce 2016 results

The following script will run the 2016 looper and produce the 9 bin SR plot and 5 bin WZCR plots.

The 9 bin SR plots' lost-lepton components are not scaled by the data * Transfer-Factor from WZCR.

However, since for 2016 we had an almost perfect aggreement in data v. MC yields the final 9 bin SR plots should be very close to what is in public result.

    git clone --recurse-submodules https://github.com/cmstas/WWWAnalysisRun2.git
    cd WWWAnalysisRun2/analysis/
    git fetch && git fetch --tags
    git checkout looper_instruction_v3
    git submodule update --init --recursive
    source ./setup.sh
    cp template_user_study.h my_user_study.h
    ln -s my_user_study.h user_study.h
    make clean
    make -j
    time sh ./process.sh -i WWW2016_v1.2.2 -t test -u # should take about ~30 seconds
    ## To Print plotting options
    python ./plot.py -h
    ## Read the options for more information
    ## Brlow are some examples for plotting
    python ./plot.py -i hists/WWW2016_v1.2.2/test/ --use_private_sig_sample --draw_data # To plot 9 bin SR and and 5 bin lost-lepton CR plots (--draw_data option unblinds it)
    python ./plot.py -i hists/WWW2016_v1.2.2/test/ --use_private_sig_sample --draw_data SRSSmmMjjInPP__Mlljj -n 5 # To plot Mlljj in mu+mu+ region Mjj-in

When running again, it will complain that the ```hists/WWW2016_v1.2.2/test/*.root``` already exists.

Either delete the previous output histograms or run with a new tag ```-t newtest``` for ```./process.sh```

## Statistical interpretation

The ```write_datacards.py``` scripts will write the datacards and in ```stats/``` directory there are few scripts to compute significances.

### Writing 9 individual data cards

Assuming histograms are created by running the looper.

    python ./write_datacards.py -i hists/WWW2016_v1.2.2/test/

Then, datacards will be written out to

    ls datacards/WWW2016_v1.2.2/test/
        datacard_b1.txt
        datacard_b2.txt
        datacard_b3.txt
        datacard_b4.txt
        datacard_b5.txt
        datacard_b6.txt
        datacard_b7.txt
        datacard_b8.txt
        datacard_b9.txt

Notice, that all 9 bins are written separately. (the order is in-ee, in-em, in-mm, out-ee, out-em, out-mm, 0, 1, 2)

We will combine this later with Higgs Combine Tool

### Higgs Combine Tool

#### Setting up the first time
In a separate terminal run the following to install the Higgs Combined Limit Tool. (Because the ROOT version is different one needs a new terminal environment.)

    cd stats/
    source ./setup_higgs_combine.sh

This only has to be done one time, and it takes about the time for you get a cup of coffee.

#### Setup up script after re-logging in

Next time logging into the terminal, run to setup the appropriate environment

    cd stats/
    source setup.sh    

#### Combining individual datacards

Then, to combine all 9 SR bins into a one giant datacards, we run

    sh combinecards.sh /path/to/where/your/datacards/WWW2016_v1.2.2/test/

Now you should have

    ls datacards/WWW2016_v1.2.2/test/
        datacard_b1.txt
        datacard_b2.txt
        datacard_b3.txt
        datacard_b4.txt
        datacard_b5.txt
        datacard_b6.txt
        datacard_b7.txt
        datacard_b8.txt
        datacard_b9.txt
        datacard_combined.txt     # new file
        datacard_combined_ss.txt  # new file
        datacard_combined_3l.txt  # new file

#### Expected sensitivity

To compute expected sensitivity

    sh doSensitivity.sh /path/to/your/datacard.txt

e.g.

    $ cd stats/
    $ sh doSensitivity.sh ../datacards/WWW2016_v1.2.2/test/datacard_combined.txt
     <<< Combine >>>
     WARNING --  From combine v7, method ProfileLikelihood has been renamed to Significance
    >>> including systematics
    >>> method used is ProfileLikelihood
    >>> random number generator seed is 123456
    Computing results starting from expected outcome (a-priori)
    
     -- Significance --
    Significance: 1.85503
    Done in 0.01 min (cpu), 0.01 min (real)


NOTE: The lost lepton numbers for the public result came directly from Hannsjorg (same as what is in AN)
While, the numbers I get with my looper seems slightly different.
But to zero-th order things pretty much the same ¯\_(ツ)_


