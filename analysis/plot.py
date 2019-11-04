#!/bin/env python

import sys

# option parser
import argparse

parser = argparse.ArgumentParser(description="Plot dumper from Run 2 WWW Analysis")
parser.add_argument('-i' , '--input_dir'              , dest='input_dir'       , help='input dir path (where hists are) NOTE: pattern MUST be hists/${BABY_VERSION}/${TAG}/', required=True      ) 
parser.add_argument('-o' , '--output_dir'             , dest='output_dir'      , help='output dir path'                        , default='plots'                                                 ) 
parser.add_argument('-n' , '--nbins'                  , dest='nbins'           , help='number of bins for the histograms'      , default=30                                                      ) 
parser.add_argument('-xt', '--xaxis_title'            , dest='xaxis_title'     , help='X-axis title'                           , default=None                                                    ) 
parser.add_argument('-y' , '--yaxis_range'            , dest='yaxis_range'     , help='Y-axis range set by user'               , default=None                                                    ) 
parser.add_argument('-l' , '--yaxis_log'              , dest='yaxis_log'       , help='Y-axis set to log'                      , default=False                              , action='store_true') 
parser.add_argument('-s' , '--sig_scale'              , dest='sig_scale'       , help='Signal scale'                           , default=1                                                       ) 
parser.add_argument('-u' , '--rm_udflow'              , dest='rm_udflow'       , help='Remove underflow'                       , default=False                              , action='store_true') 
parser.add_argument('-S' , '--do_scan'                , dest='do_scan'         , help='Do cut scan'                            , default=False                              , action='store_true') 
parser.add_argument('-d' , '--draw_data'              , dest='draw_data'       , help='Draw data'                              , default=False                              , action='store_true') 
parser.add_argument('-1' , '--stack_signal'           , dest='stack_signal'    , help='stack signal'                           , default=False                              , action='store_true') 
parser.add_argument('-v' , '--split_signal'           , dest='split_signal'    , help='Split signal'                           , default=False                              , action='store_true') 
parser.add_argument('-7' , '--split_vbsttw'           , dest='split_vbsttw'    , help='Split VBS and ttW background'           , default=False                              , action='store_true') 
parser.add_argument('-m' , '--use_mc_fake'            , dest='use_mc_fake'     , help='use_mc_fake'                            , default=False                              , action='store_true') 
parser.add_argument('-P' , '--use_private_sig_sample' , dest='use_private'     , help='Use private signal sample'              , default=False                              , action='store_true') 
parser.add_argument('-a' , '--sum_hists'              , dest='sum_hists'       , help='Sum all hists that passes filter'       , default=False                              , action='store_true') 
parser.add_argument('-O' , '--output_name'            , dest='output_name'     , help='output file name when using sum_hists'  , default=None                                                    ) 
parser.add_argument('-t' , '--syst'                   , dest='syst'            , help='Specific syst variation'                , default=""                                                      ) 
parser.add_argument('-8' , '--do_grep'                , dest='do_grep'         , help='Use filter as pattern matching'         , default=False                              , action='store_true') 
parser.add_argument('-p' , '--order_by_purity'        , dest='order_by_purity' , help='Rearrange 9 bin SR plot by S/B purity'  , default=False                              , action='store_true') 
parser.add_argument('-uw', '--usewhatSR'              , dest='usewhatSR'       , help='what selecton for the nine bins'        , default=False, action='store_true') 
parser.add_argument('-w' , '--whatSR'                 , dest='whatSR'          , help='what selecton for the nine bins'        , default=["SRSSeeMjjInFull", "SRSSemMjjInFull", "SRSSmmMjjInFull", "SRSSeeMjjOutFull", "SRSSemMjjOutFull", "SRSSemMjjOutFull", "SRSS1JeeFull", "SRSS1JemFull", "SRSS1JmmFull", "SR0SFOSFull", "SR1SFOSFull", "SR2SFOSFull",], nargs='+') 

parser.add_argument('hist_filters', metavar='<histogram_names>=(e.g. SRSSmmPre__lep_pt1,SRSSmmNj2__lep_pt1)', type=str, nargs='*', help='patterns to use to filter histograms to dump')

args = parser.parse_args()

import plottery_wrapper as p

# sig scale determines how much to scale your signal up by
# default is set to 1
if float(args.sig_scale) < 0:
    sig_scale = "auto"
else:
    sig_scale = float(args.sig_scale)

# hist_filters is used to filter out specific histograms you want to plot
# otherwise it will dump EVERY histograms which could reach O(1000) of histograms
# if no filter pattern is provided, it assumes that I want to draw the money plot (9 bin SR plot)
if len(args.hist_filters) == 0:
    print ""
    print "---------------------------------------------------------------"
    print "No hist names provided, I will plot the 9 bin SR money plot."
    print "If you want to plot something else, please provide a histogram names."
    print " e.g. SRSSmmPre__lep_pt1"
    print "---------------------------------------------------------------"
    print ""
    hist_filters = None
else:
    hist_filters = ','.join(args.hist_filters)


#*******************************************************************************************
#
#
# Figuring out various plot configuration by parsing options
#
#
#*******************************************************************************************

# path to where the histogram files are sitting at
input_dir = args.input_dir

# if last character is not "/" then add
if input_dir[-1] != "/":
    input_dir += "/" # trailing is added to ensure the logic in the  next step doesn't fail (kind of dumb...)

# The following error message will be thrown if the parsing fails
def badformat():
    print "ERROR: -i,--input_dir option pattern MUST be of format 'hists/BABYTAG/JOBTAG/'"
    sys.exit(1)

# Check that we have a pattern of exactly "hists/BABYTAG/JOBTAG/"
if len(input_dir.split("/")) != 4:
    badformat()

# If the first token is not "hists" then badformat
if input_dir.split("/")[0] != "hists":
    badformat()

# parsing input job tag based on the structure that it is hists/BABYTAG/JOBTAG/
babytag = input_dir.rsplit("hists/")[1].split("/")[0]
jobtag  = input_dir.rsplit("hists/")[1].split("/")[1].split("/")[0]

# then create plot output with a directory structure like plots/BABYTAG/JOBTAG/
output_dir = args.output_dir + "/" + babytag + "/" + jobtag

# Figuring out lumi and year
year = -1
lumi = -1
if "2016" in input_dir:
    year = 2016
    lumi = 35.9
elif "2017" in input_dir:
    year = 2017
    lumi = 41.3
elif "2018" in input_dir:
    year = 2018
    lumi = 59.74
elif "comb" in input_dir:
    year = 6051
    lumi = 136.9
else:
    print "ERROR: from -i,--input_dir {}, I can't figure out which year it is. I don't see 2016, 2017 nor 2018 anywhere"
    sys.exit(1)

# background file names
bkg_fnames = [
    "{}/photon.root".format(input_dir),
    "{}/qflip.root".format(input_dir),
    "{}/fakes.root".format(input_dir) if args.use_mc_fake else "{}/ddfakes.root".format(input_dir),
    "{}/lostlep.root".format(input_dir),
    "{}/prompt.root".format(input_dir),
    ]
histcolors = [920, 2007, 2005, 2003, 2001, 2011]

# background file names w/ mc_fakes
bkg_fnames_mc_fakes = [
    "{}/photon.root".format(input_dir),
    "{}/qflip.root".format(input_dir),
    "{}/fakes.root".format(input_dir),
    "{}/lostlep.root".format(input_dir),
    "{}/prompt.root".format(input_dir),
    ]
histcolors = [920, 2007, 2005, 2003, 2001, 2011]

# Background file names if split_vbsttw is true
if args.split_vbsttw:
    bkg_fnames = [
            "{}/fitphoton.root".format(input_dir),
            "{}/fitqflip.root".format(input_dir),
            "{}/fitfakes.root".format(input_dir) if args.use_mc_fake else "{}/ddfakes.root".format(input_dir),
            "{}/fitlostlep.root".format(input_dir),
            "{}/fitprompt.root".format(input_dir),
            "{}/vbs.root".format(input_dir),
            "{}/ttw.root".format(input_dir),
            ]
    histcolors = [920, 2007, 2005, 2003, 2001, 7005, 7001, 2011]

# Signal file names
if args.use_private:
    if args.split_signal:
        sig_fnames = [
            "{}/www_private.root".format(input_dir),
            "{}/vh_private.root".format(input_dir),
            # "{}/vh_www_private.root".format(input_dir),
            ]
    else:
        sig_fnames = [
            "{}/signal_private.root".format(input_dir),
            # "{}/vh_private.root".format(input_dir),
            ]
else:
    sig_fnames = ["{}/signal.root".format(input_dir)]

if args.stack_signal:
    if args.use_private:
        bkg_fnames.append("{}/signal_private.root".format(input_dir))
    else:
        bkg_fnames.append("{}/signal.root".format(input_dir))

# legend_labels
legend_labels = [
        "#gamma#rightarrowl",
        "Charge mis-id",
        "Non-prompt (MC)" if args.use_mc_fake else "Non-prompt",
        "Lost/three lep",
        "Irredu.",
        "All WWW (stacked)"
        ]

# legend_labels
legend_labels_mc_fakes = [
        "#gamma#rightarrowl",
        "Charge mis-id",
        "Non-prompt (MC)",
        "Lost/three lep",
        "Irredu.",
        "All WWW (stacked)"
        ]

if args.split_vbsttw:
    legend_labels = [
            "#gamma#rightarrowl",
            "Charge mis-id",
            "Non-prompt (MC)" if args.use_mc_fake else "Non-prompt",
            "Lost/three lep",
            "Other Irredu.",
            "W^{#pm}W^{#pm}",
            "t#bar{t}W",
            "All WWW (stacked)"
            ]

    legend_labels_mc_fakes = [
            "#gamma#rightarrowl",
            "Charge mis-id",
            "Non-prompt (MC)",
            "Lost/three lep",
            "Other Irredu.",
            "W^{#pm}W^{#pm}",
            "t#bar{t}W",
            "All WWW (stacked)"
            ]

# If plotting 9 bin SR the following defines the order
#try adding here also 1j
binorder9binSR=[
    "SRSSeeMjjInFull",
    "SRSSemMjjInFull",
    "SRSSmmMjjInFull",
    "SRSSeeMjjOutFull",
    "SRSSemMjjOutFull",
    "SRSSmmMjjOutFull",
    "SRSS1JeeFull",
    "SRSS1JemFull",
    "SRSS1JmmFull",    
    "SR0SFOSFull",
    "SR1SFOSFull",
    "SR2SFOSFull",
    ]
binorder9binPreSel=[
    'SRSSeeNsoftbVeto',
    'SRSSemNsoftbVeto',
    'SRSSmmNsoftbVeto',
    'SRSS1JeeNsoftbVeto',
    'SRSS1JemNsoftbVeto',
    'SRSS1JmmNsoftbVeto',
    'SR0SFOSNsoftbVeto',
    'SR1SFOSNsoftbVeto',
    'SR2SFOSNsoftbVeto',
    ]

if args.usewhatSR:
    binorder9binSR = args.whatSR[0].split(',')
binlabels9binSR=[
    "ee,Mjj-in",
    "em,Mjj-in",
    "mm,Mjj-in",
    "ee,Mjj-out",
    "em,Mjj-out",
    "mm,Mjj-out",
    "ee,1j",
    "em,1j",
    "mm,1j",
    "0SFOS",
    "1SFOS",
    "2SFOS",
    ]

# If the option --order_by_purity is true then rearrange 9 bin SR by purity
# Rough order of purity... not exact
if args.order_by_purity:
    binorder9binSR=[
        "SR0SFOSFull",
        "SRSSmmMjjInFull",
        "SRSSemMjjInFull",
        "SR1SFOSFull",
        "SRSSmmMjjOutFull",
        "SRSSemMjjOutFull",
        "SR2SFOSFull",
        "SRSSeeMjjOutFull",
        "SRSSeeMjjInFull",
        ]
    binlabels9binSR=[
        "0SFOS",
        "mm,Mjj-in",
        "em,Mjj-in",
        "1SFOS",
        "mm,Mjj-out",
        "em,Mjj-out",
        "2SFOS",
        "ee,Mjj-out",
        "ee,Mjj-in",
        ]



#*******************************************************************************************
#
#
# Below are main plotting
#
#
#*******************************************************************************************

#
# 1. Plotting a 1D distribution of a specific variable
#

# If hist_filters = histogram name is provided plot those histograms that were indicated
if hist_filters:
    p.dump_plot(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            legend_labels=legend_labels,
            signal_labels=["WWW", "VH"],
            donorm=False,
            filter_pattern=hist_filters,
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
                "blind": not args.draw_data,
                "ratio_range": [0., 2.],
                "xaxis_label": args.xaxis_title if args.xaxis_title and not args.draw_data else "",
                "xaxis_title_size": 0.05 if args.xaxis_title and not args.draw_data else None,
                "xaxis_title_offset": 1.5 if args.xaxis_title and not args.draw_data else None,
                "ratio_xaxis_title": args.xaxis_title if args.xaxis_title and args.draw_data else "",
                "ratio_xaxis_title_size": 0.135 if args.xaxis_title and args.draw_data else None,
                "ratio_xaxis_title_offset": 1.25 if args.xaxis_title and args.draw_data else None,
                },
            do_sum=args.sum_hists,
            dogrep=args.do_grep,
            output_name=args.output_name if args.sum_hists else None,
            usercolors=histcolors,
            )
    
    # scan optimization
    if args.do_scan:
        p.dump_plot(
                dirname=output_dir + "/scan",
                fnames=bkg_fnames,
                sig_fnames=sig_fnames,
                filter_pattern=hist_filters,
                signal_scale=sig_scale,
                extraoptions={
                    "nbins":180,
                    },
                _plotter=p.plot_cut_scan,
                )

#
# 2. Plotting a 9 bin money plot and the 5 bin lost lepton CR plot
#

else:
    #__________________________________________________________________________________
    # Draw the lost lepton control region plot (the 5 bin plot)
    p.plot_yields(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            regions=[
                "WZCRSSeeFull{}(1)".format(args.syst),
                "WZCRSSemFull{}(1)".format(args.syst),
                "WZCRSSmmFull{}(1)".format(args.syst),
                "WZCRSS1JeeFull{}(1)".format(args.syst),
                "WZCRSS1JemFull{}(1)".format(args.syst),
                "WZCRSS1JmmFull{}(1)".format(args.syst),
                "WZCR1SFOSFull{}(1)".format(args.syst),
                "WZCR2SFOSFull{}(1)".format(args.syst)
                ],
            binlabels=[ "ee", "em", "mm", "ee1j", "em1j", "mm1j", "1SFOS", "2SFOS", ],
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            output_name="yield_wzcr",
            legend_labels=legend_labels,
            signal_labels=["WWW", "VH"],
            donorm=False,
            signal_scale=sig_scale,
            hsuffix="__yield",
            extraoptions={
                "bkg_sort_method": "unsorted",
                "legend_scalex": 2.8,
                "legend_scaley": 0.8,
                "lumi_value": lumi,
                "print_yield": True,
                "blind": False,
                "legend_ncolumns": 3,
                "ymax_scale": 1.3,
                "ratio_range": [0., 2.],
                },
            usercolors=histcolors,
            )

    #__________________________________________________________________________________
    # Draw the money plot (the 9 bin plot)
    binorder=[ "{}{}(1)".format(x, args.syst) for x in binorder9binSR ]
    if args.order_by_purity:
        binorder.reverse()
        binlabels9binSR.reverse()
    p.plot_yields(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            regions=binorder,
            binlabels=binlabels9binSR,
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            output_name="yield_ordered" if args.order_by_purity else "yield",
            legend_labels=legend_labels,
            signal_labels=["WWW", "VH"],
            donorm=False,
            signal_scale=sig_scale,
            hsuffix="__yield",
            extraoptions={
                "bkg_sort_method": "unsorted",
                "legend_scalex": 2.8,
                "legend_scaley": 0.8,
                "lumi_value": lumi,
                "print_yield": True,
                "legend_ncolumns": 3,
                "ratio_range": [0., 2.],
                "ymax_scale": 1.3,
                #"yaxis_range": [0., 46.],
                "blind": not args.draw_data, # BE CAREFUL!!!!!!!!!!!!!!!!!!
                },
            usercolors=histcolors,
            )

    #__________________________________________________________________________________
    # Draw the money plot (the preselection plots)
    p.plot_yields(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            regions=binorder9binPreSel,
            binlabels=binorder9binPreSel,
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            output_name="yield_presel",
            legend_labels=legend_labels,
            signal_labels=["WWW", "VH"],
            donorm=False,
            signal_scale=sig_scale,
            hsuffix="__yield",
            extraoptions={
                "bkg_sort_method": "unsorted",
                "legend_scalex": 2.8,
                "legend_scaley": 0.8,
                "lumi_value": lumi,
                "print_yield": True,
                "legend_ncolumns": 3,
                "ratio_range": [0., 2.],
                "ymax_scale": 1.3,
                #"yaxis_range": [0., 46.],
                "blind": not args.draw_data, # BE CAREFUL!!!!!!!!!!!!!!!!!!
                },
            usercolors=histcolors,
            )

    #__________________________________________________________________________________
    # Draw the money plot (b-tagged CR)
    p.plot_yields(
            fnames=bkg_fnames,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            regions=[
                "CRBTageeFull{}(1)".format(args.syst),
                "CRBTagemFull{}(1)".format(args.syst),
                "CRBTagmmFull{}(1)".format(args.syst),
                "CRBTag1JeeFull{}(1)".format(args.syst),
                "CRBTag1JemFull{}(1)".format(args.syst),
                "CRBTag1JmmFull{}(1)".format(args.syst),
                "CRBTag0SFOSFull{}(1)".format(args.syst),
                "CRBTag1SFOSFull{}(1)".format(args.syst),
                "CRBTag2SFOSFull{}(1)".format(args.syst)
                ],
            binlabels=[ "ee", "em", "mm", "ee1j", "em1j", "mm1j", "0SFOS", "1SFOS", "2SFOS" ],
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            output_name="yield_bcr",
            legend_labels=legend_labels,
            signal_labels=["WWW", "VH"],
            donorm=False,
            signal_scale=sig_scale,
            hsuffix="__yield",
            extraoptions={
                "bkg_sort_method": "unsorted",
                "legend_scalex": 2.8,
                "legend_scaley": 0.8,
                "lumi_value": lumi,
                "print_yield": True,
                "legend_ncolumns": 3,
                "ratio_range": [0., 2.],
                "ymax_scale": 1.3,
                "blind": False,
                },
            usercolors=histcolors,
            )

    #__________________________________________________________________________________
    # Draw the money plot (Application Region)
    p.plot_yields(
            fnames=bkg_fnames_mc_fakes,
            sig_fnames=sig_fnames,
            data_fname="{}/data.root".format(input_dir),
            regions=[
                "ARSSeeMjjInFull{}(1)".format(args.syst),
                "ARSSemMjjInFull{}(1)".format(args.syst),
                "ARSSmmMjjInFull{}(1)".format(args.syst),
                "ARSSeeMjjOutFull{}(1)".format(args.syst),
                "ARSSemMjjOutFull{}(1)".format(args.syst),
                "ARSSmmMjjOutFull{}(1)".format(args.syst),
                "ARSS1JeeFull{}(1)".format(args.syst),
                "ARSS1JemFull{}(1)".format(args.syst),
                "ARSS1JmmFull{}(1)".format(args.syst),
                "AR0SFOSFull{}(1)".format(args.syst),
                "AR1SFOSFull{}(1)".format(args.syst),
                "AR2SFOSFull{}(1)".format(args.syst)
                ],
            binlabels=[ "ee", "em", "mm", "ee-out", "em-out", "mm-out", "ee1j", "em1j", "mm1j", "0SFOS", "1SFOS", "2SFOS" ],
            dirname=output_dir+"/log" if args.yaxis_log else output_dir+"/lin",
            output_name="yield_ar",
            legend_labels=legend_labels_mc_fakes,
            signal_labels=["WWW", "VH"],
            donorm=False,
            signal_scale=sig_scale,
            hsuffix="__yield",
            extraoptions={
                "bkg_sort_method": "unsorted",
                "legend_scalex": 2.8,
                "legend_scaley": 0.8,
                "lumi_value": lumi,
                "print_yield": True,
                "legend_ncolumns": 3,
                "ratio_range": [0., 2.],
                "ymax_scale": 1.3,
                "blind": False,
                },
            usercolors=histcolors,
            )


