#!/bin/env python

import ROOT as r
from rooutil import plottery_wrapper as p

input_dir = "outputs/WWW2017_v5.0.0/test1/"
filter_pattern = "RSSmmNb0__lep_pt1"
signal_scale = 1
plot_output_dir = "plots"
nbins = 12

year = -1
lumi = -1
if "2016" in input_dir:
    year = 2016
    lumi = 35.9
if "2017" in input_dir:
    year = 2017
    lumi = 41.3
if "2018" in input_dir:
    year = 2018
    lumi = 59.74

p.dump_plot(
        fnames=[
            "{}/ddfakes.root".format(input_dir),
            "{}/prompt.root".format(input_dir),
            "{}/lostlep.root".format(input_dir),
            "{}/qflip.root".format(input_dir),
            "{}/photon.root".format(input_dir),
            ],
        sig_fnames=["{}/signal.root".format(input_dir)],
        data_fname="{}/data.root".format(input_dir),
        dirname=plot_output_dir,
        legend_labels=["Fakes", "Irred.", "Lost-lep", "Q-flip", "#gamma#rightarrowl"],
        donorm=False,
        filter_pattern=filter_pattern,
        signal_scale=signal_scale,
        extraoptions={
            "legend_scalex": 1.8,
            "legend_scaley": 1.1,
            "nbins": nbins,
            "lumi_value": lumi,
            },
        )

p.plot_yields(
        fnames=[
            "{}/ddfakes.root".format(input_dir),
            "{}/prompt.root".format(input_dir),
            "{}/lostlep.root".format(input_dir),
            "{}/qflip.root".format(input_dir),
            "{}/photon.root".format(input_dir),
            ],
        sig_fnames=["{}/signal.root".format(input_dir)],
        regions=[ "SRSSeeFull", "SRSSemFull", "SRSSmmFull", "SRSSSideeeFull", "SRSSSideemFull", "SRSSSidemmFull", "SR0SFOSFull", "SR1SFOSFull", "SR2SFOSFull", ],
        binlabels=[ "ee-in", "em-in", "mm-in", "ee-out", "em-out", "mm-out", "0", "1", "2", ],
        dirname=plot_output_dir,
        output_name="yield",
        legend_labels=["Fakes", "Irred.", "Lost-lep", "Q-flip", "#gamma#rightarrowl"],
        donorm=False,
        filter_pattern=filter_pattern,
        signal_scale=signal_scale,
        extraoptions={
            "legend_scalex": 1.8,
            "legend_scaley": 1.1,
            "lumi_value": lumi,
            },
        )

