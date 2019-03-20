#!/bin/env python

# option parser
import argparse

parser = argparse.ArgumentParser(description="Plot dumper from Run 2 Boosted Higgs Analysis")
parser.add_argument('-i' , '--input_dir'              , dest='input_dir'  , help='input dir path (where hists are)'                               , required=True      ) 
parser.add_argument('-o' , '--output_dir'             , dest='output_dir' , help='output dir path'                        , default='plots'                            ) 
parser.add_argument('-n' , '--nbins'                  , dest='nbins'      , help='number of bins for the histograms'      , default=30                                 ) 
parser.add_argument('-y' , '--yaxis_range'            , dest='yaxis_range', help='Y-axis range set by user'               , default=None                               ) 
parser.add_argument('-l' , '--yaxis_log'              , dest='yaxis_log'  , help='Y-axis set to log'                      , default=False         , action='store_true') 
parser.add_argument('-s' , '--sig_scale'              , dest='sig_scale'  , help='Signal scale'                           , default=1                                  ) 
parser.add_argument('-u' , '--rm_udflow'              , dest='rm_udflow'  , help='Remove underflow'                       , default=False         , action='store_true') 
parser.add_argument('-S' , '--do_scan'                , dest='do_scan'    , help='Do cut scan'                            , default=False         , action='store_true') 
parser.add_argument('-P' , '--use_private_sig_sample' , dest='use_private', help='Use private signal sample'              , default=False         , action='store_true') 

parser.add_argument('filter_patterns', metavar='FILTER_PATTERN', type=str, nargs='*', help='patterns to use to filter histograms to dump')

args = parser.parse_args()

from rooutil import plottery_wrapper as p

# sig scale determines how much to scale your signal up by
# default is set to 1
if args.sig_scale < 0:
    sig_scale = "auto"
else:
    sig_scale = float(args.sig_scale)

# filter_pattern is used to filter out specific histograms you want to plot
# otherwise it will dump EVERY histograms which could reach O(1000) of histograms
# if no filter pattern is provided, it assumes that I want to draw the money plot (9 bin SR plot)
if len(args.filter_patterns) == 0:
    print ""
    print "---------------------------------------------------------------"
    print "No filter pattern provided, I will plot the 9 bin SR money plot."
    print "If you want to plot something else, please provide a histogram filter pattern."
    print " e.g. SRSSmmNb0__lep_pt1"
    print "---------------------------------------------------------------"
    print ""
    filter_pattern = None
else:
    filter_pattern = ','.join(args.filter_patterns)

# path to where the histogram files are sitting at
input_dir = args.input_dir + "/" # trailing is added to ensure the logic in the  next step doesn't fail

# parsing input job tag based on the structure that it is outputs/BABYTAG/JOBTAG/
babytag = input_dir.rsplit("outputs/")[1].split("/")[0]
jobtag  = input_dir.rsplit("outputs/")[1].split("/")[1].split("/")[0]

# then create plot output with a directory structure like plots/BABYTAG/JOBTAG/
output_dir = args.output_dir + "/" + babytag + "/" + jobtag

# Figuring out lumi and year
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

# background file names
bkg_fnames = [
    "{}/photon.root".format(input_dir),
    "{}/qflip.root".format(input_dir),
    "{}/ddfakes.root".format(input_dir),
    "{}/lostlep.root".format(input_dir),
    "{}/prompt.root".format(input_dir),
    ]

# Signal file names
if args.use_private:
    sig_fnames = ["{}/signal_private.root".format(input_dir)]
else:
    sig_fnames = ["{}/signal.root".format(input_dir)]

# legend_labels
legend_labels = ["Non-prompt", "Irredu.", "Lost/three lep", "Charge mis-id", "#gamma#rightarrowl"]

# If a histogram filter pattern was provided then plot the requested plots
if filter_pattern:
    p.dump_plot(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            legend_labels=legend_labels,
            donorm=False,
            filter_pattern=filter_pattern,
            signal_scale=sig_scale,
            extraoptions={
                "nbins":int(args.nbins),
                "print_yield":True,
                "yaxis_log":args.yaxis_log,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "legend_smart":False if args.yaxis_log else True,
                "yaxis_range":args.yaxis_range.split(',') if args.yaxis_range else [],
                "remove_underflow":args.rm_udflow,
                "bkg_sort_method": "unsorted",
                "lumi_value": lumi,
                "no_ratio": True,
                },
            usercolors=[920, 2007, 2005, 2003, 2001],
            )
    
    # scan optimization
    if args.do_scan:
        p.dump_plot(
                dirname=output_dir + "/scan",
                fnames=bkg_fnames,
                sig_fnames=sig_fnames,
                filter_pattern=filter_pattern,
                signal_scale=sig_scale,
                extraoptions={
                    "nbins":180,
                    },
                _plotter=p.plot_cut_scan,
                )

else:
    #__________________________________________________________________________________
    # Draw the money plot (the 9 bin plot)
    p.plot_yields(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            regions=[ "SRSSeeFull", "SRSSemFull", "SRSSmmFull", "SRSSSideeeFull", "SRSSSideemFull", "SRSSSidemmFull", "SR0SFOSFull", "SR1SFOSFull", "SR2SFOSFull", ],
            binlabels=[ "ee", "em", "mm", "side-ee", "side-em", "side-mm", "0SFOS", "1SFOS", "2SFOS", ],
            dirname=output_dir,
            output_name="yield",
            legend_labels=legend_labels,
            donorm=False,
            filter_pattern=filter_pattern,
            signal_scale=sig_scale,
            extraoptions={
                "bkg_sort_method": "unsorted",
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "lumi_value": lumi,
                "print_yield": True,
                "blind": True, # BE CAREFUL!!!!!!!!!!!!!!!!!!
                },
            usercolors=[920, 2007, 2005, 2003, 2001],
            )


