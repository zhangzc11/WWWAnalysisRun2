#!/bin/env python

from rooutil import rooutil as ru
from rooutil import plottery_wrapper as p
from rooutil import datacard_writer as dw
import glob
import ROOT as r

#
# SET ME APPROPRIATELY
# SET ME APPROPRIATELY
# SET ME APPROPRIATELY
#

# Global variables
input_ntuple = "WWW2016_v4.0.5"
analysis_tag = "test10"
iscondor = True
hassyst = True
hashist = False
output_dirpath = ""
is2017 = ""

def process_output_dirpath():
    global output_dirpath
    global is2017
    output_dirpath = "outputs/{}/{}/{}".format("condor" if iscondor else "", input_ntuple, analysis_tag)
    is2017 = "WWW2017" in output_dirpath

# 2016 analysis re-processed
def set_to_2016():
    global input_ntuple
    global analysis_tag
    global iscondor
    global hassyst
    global hashist
    input_ntuple = "WWW2016_v4.0.5"
    analysis_tag = "test10"
    iscondor = True
    hassyst = True
    hashist = False
    process_output_dirpath()

# 2017 analysis with yields + systematics only (no histograms)
def set_to_2017():
    global input_ntuple
    global analysis_tag
    global iscondor
    global hassyst
    global hashist
    input_ntuple = "WWW2017_v4.0.5"
    analysis_tag = "test21"
    iscondor = True
    hassyst = True
    hashist = False
    process_output_dirpath()

#########################################################################################################################################
#########################################################################################################################################
#########################################################################################################################################
#########################################################################################################################################

# Bkg order
bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
#bkg_order = ["fakes", "photon", "lostlep", "qflip", "prompt", "ttw", "vbsww"]
colors_map = {"photon":920, "qflip":2007, "lostlep":2003, "prompt":2001, "fakes":2005, "sig":2, "vbsww":2002, "ttw":2004}
colors = [ colors_map[b] for b in bkg_order ]

#________________________________________________________________________________________________________________________________________
def main():

    set_to_2017()

    # Plot lost lepton yields
    plot("WZCR", "lostlep_cr_yield", False)
    plot(["WZCRSSeeMllSS__MllOnOff", "WZCRSSemMTmax__MllOnOff", "WZCRSSmmMllSS__MllOnOff"], "lostlep_cr_ss_msfos", False)
    plot(["WZVR1SFOSMllOnOff__MllOnOff", "WZVR2SFOSMllOnOff__MllOnOff"], "lostlep_cr_3l_msfos", False)
    plot(["WZVRSSee__MjjZoom", "WZVRSSem__MjjZoom", "WZVRSSmm__MjjZoom"], "lostlep_cr_ss_mjj", False)

    # Print extrapolation factors
    study_lostlep()

    # Study msfos modeling
    study_msfos_modeling()

    # Study mjj modeling
    study_mjj_modeling()

    # Writing datacards
    write_datacard()

#________________________________________________________________________________________________________________________________________
# Writing statistics datacards
def write_datacard():

    global bkg_order
    bkg_order = ["fakes", "photon", "lostlep", "qflip", "prompt", "ttw", "vbsww"]

    # Get the main yield
    lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors
    hists = get_yield_hists("SR", True, lostlep_sf) # Get the main yields with lost lepton scale factors applied
    systs = get_systs() # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in bkg_order ]

    # Write to the datacard
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])

    # Region names
    reg_names = [ "SRSSee", "SRSSem", "SRSSmm", "SRSSSideee", "SRSSSideem", "SRSSSidemm", "SR0SFOS", "SR1SFOS", "SR2SFOS" ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("plots/{}/{}/datacard_{}.txt".format(input_ntuple, analysis_tag, reg_name))

#________________________________________________________________________________________________________________________________________
# Get the lost lepton scale factors to be applied
# The calculation is SF = data - (non-lost-lep) / lost-lep-MC. And this is done in CR.
# Then this SF will be applied to the lost-lep-MC in SR
# The final output will be a dict of {"(region-name)" : [ SF, SFerr], ... }
def get_lostlep_sf():
    hists = get_yield_hists("WZCR", False)
    bgs = [ hists[x] for x in bkg_order ]
    sf = ru.get_sf(hists["lostlep"], hists["data"], [hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"], hists["ttw"], hists["vbsww"]])
    sfs = {"lostlep": {
            "SSee"    : [sf.GetBinContent(1),sf.GetBinError(1)],
            "SSem"    : [sf.GetBinContent(2),sf.GetBinError(2)],
            "SSmm"    : [sf.GetBinContent(3),sf.GetBinError(3)],
            "SSSideee": [sf.GetBinContent(4),sf.GetBinError(4)],
            "SSSideem": [sf.GetBinContent(5),sf.GetBinError(5)],
            "SSSidemm": [sf.GetBinContent(6),sf.GetBinError(6)],
            "1SFOS"   : [sf.GetBinContent(8),sf.GetBinError(8)],
            "2SFOS"   : [sf.GetBinContent(9),sf.GetBinError(9)],
            }
            }
    return sfs

#________________________________________________________________________________________________________________________________________
# This returns a list of systematics to be provided to the DataCardWriter class (located under rooutil/datacard_writer.py)
# The format is explained in detail in github.com:sgnoohc/rooutil/datacard_writer.py
# TL;DR
# systs = [
#           ('syst', 'lnN', [], {'qqWW': [TH1, TH1], 'ggWW': None, 'ggH': [TH1, TH1], 'others': None}),
#             name
#
#                     lnN
#                     gmN
#                     or
#                     etc
#                           yield for gmN
#                               dictionary of process -> [TH1, TH1]
#                                                         up   down variation
#                                                         It could also not be a list and have a one TH1 to indicate symmetric
#                                                         If it set to None then it's not applied
#                                                         A float can work too (e.g. below)
#           ('syst', 'lnN', [], {'qqWW': float, 'ggWW': None, 'ggH': float, 'others': None}),
#           ...
#           ...
#           ...
#           ...
#           ...
#           # If provided is a gmN then the 3rd option has the data yield for gmN and each process has the extrapolation factors
#           ('WW_norm', 'gmN', [TH1], {'qqWW': TH1, 'ggWW': TH1, 'ggH': TH1, 'others': TH1}),
#           ('WW_norm', 'gmN', [TH1], {'qqWW': [float,..], 'ggWW': [float,..], 'ggH': [float,..], 'others': [float,..]}),
# ]
def get_systs():

    # Get the main yield
    lostlep_sf = get_lostlep_sf()
    hists = get_yield_hists("SR", True, lostlep_sf)

    systs = []

    # Usual systematic variations for both signal and backgrounds
    syst_names = ["JES", "LepSF", "TrigSF", "BTagLF", "BTagHF", "Pileup"]
    for sys in syst_names:
        sys_hists_up = get_yield_hists("SR", True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists("SR", True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["www", "qflip", "prompt", "photon", "ttw", "vbsww"]:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # Fake systematics
    for sys in ["FakeRateEl", "FakeRateMu", "FakeClosureEl", "FakeClosureMu"]:
        sys_hists_up = get_yield_hists("SR", True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists("SR", True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["fakes"]:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # Signal systematics
    for sys in ["PDF", "Qsq", "AlphaS"]:
        sys_hists_up = get_yield_hists("SR", True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists("SR", True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["www"]:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # WZ CR Stats
    lostlep_alpha = get_lostlep_alpha()
    data_yield = get_yield_hists("WZCR", False)
    systnames = ["WZCRSSeeFull_CRstat", "WZCRSSemFull_CRstat", "WZCRSSmmFull_CRstat", "WZCR1SFOSFull_CRstat", "WZCR2SFOSFull_CRstat"]
    syst_relevant_bins = {
            "WZCRSSeeFull_CRstat": [1, 4],
            "WZCRSSemFull_CRstat": [2, 5],
            "WZCRSSmmFull_CRstat": [3, 6],
            "WZCR1SFOSFull_CRstat":[8],
            "WZCR2SFOSFull_CRstat":[9]
            }
    for sys in systnames:
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["lostlep"]:
                systval[proc] = [ "{:.4f}".format(lostlep_alpha.GetBinContent(i)) if i in syst_relevant_bins[sys] else "-" for i in xrange(1, lostlep_alpha.GetNbinsX()+1) ]
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'gmN', [data_yield["data"]], systval)
        systs.append(syst_datacard_data)

    # Lost-Lep extrapolation factor (alpha) error
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["lostlep"]:
            systval[proc] = ["1.049"] * 6 + ["-"] * 3
        else:
            systval[proc] = 0
    systs.append(("MjjSyst", 'lnN', [], systval))

    # Lost-Lep extrapolation factor (alpha) error
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["lostlep"]:
            systval[proc] = ["1.053"] * 6 + ["-"] * 3
        else:
            systval[proc] = 0
    systs.append(("MllSSSyst", 'lnN', [], systval))

    # Lost-Lep extrapolation factor (alpha) error
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["lostlep"]:
            systval[proc] = ["-"] * 6 + ["1.082"] * 3
        else:
            systval[proc] = 0
    systs.append(("Mll3LSyst", 'lnN', [], systval))

    # Flat systematics

    # VBSWWVR
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["vbsww"]:
            systval[proc] = "1.22"
        else:
            systval[proc] = 0
    systs.append(("VBSWWVR", 'lnN', [], systval))

    # VBSWWXsec
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["vbsww"]:
            systval[proc] = "1.20"
        else:
            systval[proc] = 0
    systs.append(("VBSWWXsec", 'lnN', [], systval))

    # ttWXVR
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["ttw"]:
            systval[proc] = "1.18"
        else:
            systval[proc] = 0
    systs.append(("TTWVR", 'lnN', [], systval))

    # ttWXsec
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["ttw"]:
            systval[proc] = "1.20"
        else:
            systval[proc] = 0
    systs.append(("TTWXsec", 'lnN', [], systval))

    # photon validation region
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["photon"]:
            systval[proc] = "1.50"
        else:
            systval[proc] = 0
    systs.append(("GammaVR", 'lnN', [], systval))

    # qflip MC syst
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["qflip"]:
            systval[proc] = "1.50"
        else:
            systval[proc] = 0
    systs.append(("QFlipSyst", 'lnN', [], systval))

    # LumiSyst
    systval = {}
    for proc in ["www"] + bkg_order:
        if proc in ["www", "qflip", "photon", "ttw", "vbsww", "prompt"]:
            systval[proc] = "1.025"
        else:
            systval[proc] = 0
    systs.append(("LumSyst", 'lnN', [], systval))

    return systs

#________________________________________________________________________________________________________________________________________
# Compute the extrapolation factor
# This will be the value that will be put into the datacards.
# Alpha = (data - non-lost-lep) * (lost-lep-SR / lost-lep-CR) / data
def get_lostlep_alpha():
    hists = get_yield_hists("WZCR", False)
    bgs = [ hists[x] for x in bkg_order ]
    histsSR = get_yield_hists("SR", False)
    alpha = ru.get_alpha(histsSR["lostlep"], hists["lostlep"], hists["data"], [hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"], hists["ttw"], hists["vbsww"]])
    return alpha

#________________________________________________________________________________________________________________________________________
# Main plotting script
def plot(histnames, outputfilename, use_data_driven_fakes=False):

    # If provided histnames are just a string indicating a region, then get the list of cutflow table histograms, and plot the yields.
    if isinstance(histnames, str):
        # Regions to plot
        histnames = get_histnames(output_dirpath + "/signal.root", histnames)
        histnames.sort(key=region_index) # Sort pretty

    # Now obtain the list of histograms
    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}))

    # Set the option for plotting
    alloptions= {
                "ratio_range":[0.0,2.2],
                "nbins": 12,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, outputfilename),
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": True,
                "yield_prec": 3,
                "blind": True if "SR" in histnames[0] else False,
                "lumi_value": "41.3" if is2017 else "35.9",
                #"yaxis_range": [0.001,150],
                #"yaxis_log": True,
                }

    # aggregate a list of backgrounds from the "hists"
    bgs = [ hists[x] for x in bkg_order ]

    # Now actually plot the histogram
    p.plot_hist(
            sigs = [hists["www"]],
            bgs  = bgs,
            data = hists["data"],
            colors = colors,
            syst = None,
            options=alloptions)

#________________________________________________________________________________________________________________________________________
# This function plots the variations of lost lepton SR / CR yields extrapolation (N.B. slightly different math from alpha)
def study_lostlep():
    key = "lostlep"
    systs = ["JES", "LepSF", "TrigSF", "BTagLF", "BTagHF", "Pileup"]
    histnames_cr = [ "WZCRSSeeFull", "WZCRSSemFull", "WZCRSSmmFull", "WZCRSSeeFull", "WZCRSSemFull", "WZCRSSmmFull", "WZCR1SFOSFull", "WZCR2SFOSFull" ]
    histnames_sr = [ "SRSSeeFull", "SRSSemFull", "SRSSmmFull", "SRSSSideeeFull", "SRSSSideemFull", "SRSSSidemmFull", "SR1SFOSFull", "SR2SFOSFull" ]
    hists_cr = get_hists(histnames_cr)
    hists_sr = get_hists(histnames_sr)
    hists_sr[key].Divide(hists_cr[key])
    h_nom_tf = hists_sr[key].Clone("Nominal")
    h_sys_tf = {}
    for syst in systs:
        for var in ["Up", "Down"]:
            histnames_cr_syst = [ x + syst + var for x in histnames_cr ]
            histnames_sr_syst = [ x + syst + var for x in histnames_sr ]
            hists_cr = get_hists(histnames_cr_syst)
            hists_sr = get_hists(histnames_sr_syst)
            hists_sr[key].Divide(hists_cr[key])
            h_sys_tf[syst+var] = hists_sr[key].Clone(syst+var)
    hists = [ h_sys_tf[syst+var] for syst in systs for var in ["Up", "Down"] ]
    alloptions= { "output_name": "plots/{}/{}/lostlep_exp_tf.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 3}
    p.plot_hist(bgs=[h_nom_tf], options=alloptions)
    for hist in hists:
        hist.Divide(h_nom_tf)
    h_nom_tf.Divide(h_nom_tf)
    # Symmetrization
    import math
    systs_symmetrized = []
    for syst in systs:
        systs_symmetrized.append(h_sys_tf[syst+"Up"].Clone(syst))
        systs_symmetrized[-1].Reset()
        for i in xrange(1, h_sys_tf[syst+"Up"].GetNbinsX()+1):
            symerr = math.sqrt(abs(1 - h_sys_tf[syst+"Up"][i])**2 + abs(1 - h_sys_tf[syst+"Down"][i])**2)
            systs_symmetrized[-1].SetBinContent(i, symerr)
    alloptions= { "output_name": "plots/{}/{}/lostlep_exp_syst.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 3}
    #p.plot_hist(sigs=hists, bgs=[h_nom_tf], options=alloptions)
    p.plot_hist(sigs=systs_symmetrized, bgs=[h_nom_tf], options=alloptions)


#________________________________________________________________________________________________________________________________________
def study_msfos_modeling():

    #
    # Same-sign regions
    #

    # before msfos cut
    histnames = [
            "WZCRSSeeFull(-2)",
            "WZCRSSemFull(-2)",
            "WZCRSSmmFull(-2)",
            ]

    # Now obtain the list of histograms
    hists_ss_before = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)
    hists_ss_before_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=True)

    # after msfos cut
    histnames = [
            "WZCRSSeeFull(-1)",
            "WZCRSSemFull(-1)",
            "WZCRSSmmFull(-1)",
            ]

    # Now obtain the list of histograms
    hists_ss_after = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)
    hists_ss_after_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)

    # Do the math
    import math
    eff_data = hists_ss_after["data"].Integral() / hists_ss_before["data"].Integral()
    eff_mc = hists_ss_after["lostlep"].Integral() / hists_ss_before["lostlep"].Integral()
    eff_err_data = math.sqrt(eff_data * (1 - eff_data) / hists_ss_before["data"].Integral())
    eff_err_mc = math.sqrt(eff_mc * (1 - eff_mc) / hists_ss_before_raw["lostlep"].Integral())

    # Create histograms with the calculation results so that it can be plotted/made into a table
    h_eff_data = r.TH1F("lostlep eff msfos ss data", "lostlep eff msfos ss data", 4, 0, 4)
    h_eff_mc = r.TH1F("lostlep eff msfos ss mc", "lostlep eff msfos ss mc", 4, 0, 4)

    h_eff_data.GetXaxis().SetBinLabel(1, "eff ($e$)")
    h_eff_data.SetBinContent(1, eff_data)
    h_eff_data.SetBinError(1, eff_err_data)

    h_eff_mc.GetXaxis().SetBinLabel(1, "eff ($e$)")
    h_eff_mc.SetBinContent(1, eff_mc)
    h_eff_mc.SetBinError(1, eff_err_mc)

    h_eff_data.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_eff_data.SetBinContent(2, hists_ss_after["data"].Integral())

    h_eff_data.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_eff_data.SetBinContent(3, hists_ss_before["data"].Integral())

    h_eff_data.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_eff_data.SetBinContent(4, hists_ss_before["data"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_eff_mc.SetBinContent(2, hists_ss_after["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_eff_mc.SetBinContent(3, hists_ss_before["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_eff_mc.SetBinContent(4, hists_ss_before_raw["lostlep"].Integral())

    # Write them out to a table/plot
    alloptions= { "output_name": "plots/{}/{}/lostlep_eff_msfos_ss.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3" if is2017 else "35.9", "yield_prec": 3}
    alloptions["yield_table_caption"] = "Some numbers for same-sign channel $m_{SFOS}$ efficiency measurement. Equation is that $\\textrm{eff} = b / a$ and $\\textrm{eff}_\\textrm{err} = \\sqrt(\\textrm{eff} (1 - \\textrm{eff}) / n)$"
    p.plot_hist(bgs=[h_eff_mc], data=h_eff_data, colors=colors, options=alloptions)

    #
    # Three-lepton regions
    #

    # before msfos cut
    histnames = [
            "WZVR1SFOSMllOnOffFull(-2)",
            "WZVR2SFOSMllOnOffFull(-2)",
            ]

    # Now obtain the list of histograms
    hists_3l_before = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)
    hists_3l_before_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=True)

    # after msfos cut
    histnames = [
            "WZVR1SFOSMllOnOffFull(-1)",
            "WZVR2SFOSMllOnOffFull(-1)",
            ]

    # Now obtain the list of histograms
    hists_3l_after = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)
    hists_3l_after_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)

    # Do the math (for three lepton the math is on / off ratio)
    import math

    # Compute the non lost lepton MC parts
    non_lostlep_before = hists_3l_before["prompt"].Clone()
    non_lostlep_before.Reset()
    #for proc in ["prompt", "fakes", "qflip", "photon"]:
    #    non_lostlep_before.Add(hists_3l_before[proc])

    non_lostlep_after = hists_3l_after["prompt"].Clone()
    non_lostlep_after.Reset()
    #for proc in ["prompt", "fakes", "qflip", "photon"]:
    #    non_lostlep_after.Add(hists_3l_after[proc])

    hists_3l_after["data"].Rebin(2)
    hists_3l_before["data"].Rebin(2)
    hists_3l_after["lostlep"].Rebin(2)
    hists_3l_before["lostlep"].Rebin(2)
    hists_3l_after_raw["data"].Rebin(2)
    hists_3l_before_raw["data"].Rebin(2)
    hists_3l_after_raw["lostlep"].Rebin(2)
    hists_3l_before_raw["lostlep"].Rebin(2)
    non_lostlep_before.Rebin(2)
    non_lostlep_after.Rebin(2)

    on_data = hists_3l_after["data"][1] - non_lostlep_after[1]
    on_mc = hists_3l_after["lostlep"][1]
    on_err_data = math.sqrt(hists_3l_after["data"].GetBinError(1)**2 - non_lostlep_after.GetBinError(1)**2)
    on_err_mc = hists_3l_after["lostlep"].GetBinError(1)

    off_data = hists_3l_before["data"][1] - on_data - non_lostlep_before[1]
    off_mc = hists_3l_before["lostlep"][1] - on_mc
    off_err_data = math.sqrt(hists_3l_before["data"].GetBinError(1)**2 - non_lostlep_before.GetBinError(1)**2 - on_err_data**2)
    off_err_mc = math.sqrt(hists_3l_before["lostlep"].GetBinError(1)**2 - on_err_mc**2)

    ratio_data = on_data / off_data
    ratio_mc = on_mc / off_mc

    ratio_err_data = math.sqrt((on_err_data / on_data)**2 + (off_err_data / off_data)**2)
    ratio_err_mc = math.sqrt((on_err_mc / on_mc)**2 + (off_err_mc / off_mc)**2)

    # Create histograms with the calculation results so that it can be plotted/made into a table
    h_ratio_data = r.TH1F("lostlep ratio msfos 3l data", "lostlep ratio msfos 3l data", 3, 0, 3)
    h_ratio_mc = r.TH1F("lostlep ratio msfos 3l mc", "lostlep ratio msfos 3l mc", 3, 0, 3)

    h_ratio_data.GetXaxis().SetBinLabel(1, "ratio ($r$)")
    h_ratio_data.SetBinContent(1, ratio_data)
    h_ratio_data.SetBinError(1, ratio_err_data)

    h_ratio_mc.GetXaxis().SetBinLabel(1, "ratio ($r$)")
    h_ratio_mc.SetBinContent(1, ratio_mc)
    h_ratio_mc.SetBinError(1, ratio_err_mc)

    h_ratio_data.GetXaxis().SetBinLabel(2, "on ($p$)")
    h_ratio_data.SetBinContent(2, on_data)
    h_ratio_data.SetBinError(2, on_err_data)

    h_ratio_data.GetXaxis().SetBinLabel(3, "off ($f$)")
    h_ratio_data.SetBinContent(3, off_data)
    h_ratio_data.SetBinError(3, off_err_data)

    h_ratio_mc.GetXaxis().SetBinLabel(2, "on ($p$)")
    h_ratio_mc.SetBinContent(2, on_mc)
    h_ratio_mc.SetBinError(2, on_err_mc)

    h_ratio_mc.GetXaxis().SetBinLabel(3, "off ($f$)")
    h_ratio_mc.SetBinContent(3, off_mc)
    h_ratio_mc.SetBinError(3, off_err_mc)

    # Write them out to a table/plot
    alloptions= { "output_name": "plots/{}/{}/lostlep_ratio_msfos_3l.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3" if is2017 else "35.9", "yield_prec": 3}
    alloptions["yield_table_caption"] = "Some numbers for three-lepton channel $m_{SFOS}$ on//off ratio measurement. Equation is that $\\textrm{r} = p / f$"
    p.plot_hist(bgs=[h_ratio_mc], data=h_ratio_data, colors=colors, options=alloptions)

#________________________________________________________________________________________________________________________________________
def study_mjj_modeling():

    #
    # Same-sign regions
    #

    # before msfos cut
    histnames = [
            "WZVRSSeeFull(-2)",
            "WZVRSSemFull(-2)",
            "WZVRSSmmFull(-2)",
            ]

    # Now obtain the list of histograms
    hists_ss_before = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)
    hists_ss_before_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=True)

    # after msfos cut
    histnames = [
            "WZVRSSeeFull(-1)",
            "WZVRSSemFull(-1)",
            "WZVRSSmmFull(-1)",
            ]

    # Now obtain the list of histograms
    hists_ss_after = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)
    hists_ss_after_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=False)

    # Mjj-in efficiency

    # Do the math
    import math
    eff_data = hists_ss_after["data"].Integral() / hists_ss_before["data"].Integral()
    eff_mc = hists_ss_after["lostlep"].Integral() / hists_ss_before["lostlep"].Integral()
    eff_err_data = math.sqrt(eff_data * (1 - eff_data) / hists_ss_before["data"].Integral())
    eff_err_mc = math.sqrt(eff_mc * (1 - eff_mc) / hists_ss_before_raw["lostlep"].Integral())

    # Create histograms with the calculation results so that it can be plotted/made into a table
    h_eff_data = r.TH1F("lostlep eff mjj ss data", "lostlep eff mjj ss data", 4, 0, 4)
    h_eff_mc = r.TH1F("lostlep eff mjj ss mc", "lostlep eff mjj ss mc", 4, 0, 4)

    h_eff_data.GetXaxis().SetBinLabel(1, "eff ($e$)")
    h_eff_data.SetBinContent(1, eff_data)
    h_eff_data.SetBinError(1, eff_err_data)

    h_eff_mc.GetXaxis().SetBinLabel(1, "eff ($e$)")
    h_eff_mc.SetBinContent(1, eff_mc)
    h_eff_mc.SetBinError(1, eff_err_mc)

    h_eff_data.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_eff_data.SetBinContent(2, hists_ss_after["data"].Integral())

    h_eff_data.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_eff_data.SetBinContent(3, hists_ss_before["data"].Integral())

    h_eff_data.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_eff_data.SetBinContent(4, hists_ss_before["data"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_eff_mc.SetBinContent(2, hists_ss_after["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_eff_mc.SetBinContent(3, hists_ss_before["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_eff_mc.SetBinContent(4, hists_ss_before_raw["lostlep"].Integral())

    # Write them out to a table/plot
    alloptions= { "output_name": "plots/{}/{}/lostlep_eff_mjj_ss.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3" if is2017 else "35.9", "yield_prec": 3}
    alloptions["yield_table_caption"] = "Some numbers for same-sign channel $m_{jj}$ efficiency measurement. Equation is that $\\textrm{eff} = b / a$ and $\\textrm{eff}_\\textrm{err} = \\sqrt(\\textrm{eff} (1 - \\textrm{eff}) / n)$"
    p.plot_hist(bgs=[h_eff_mc], data=h_eff_data, colors=colors, options=alloptions)

    # Mjj-in inefficiency

    # Do the math
    hists_ss_after["data"].Rebin(3)
    hists_ss_before["data"].Rebin(3)
    hists_ss_after["lostlep"].Rebin(3)
    hists_ss_before["lostlep"].Rebin(3)
    hists_ss_after_raw["lostlep"].Rebin(3)
    hists_ss_before_raw["lostlep"].Rebin(3)

    in_data = hists_ss_after["data"][1]
    out_data = hists_ss_before["data"][1] - in_data
    total_data = hists_ss_before["data"][1]
    in_err_data = hists_ss_after["data"].GetBinError(1)
    out_err_data = math.sqrt(hists_ss_after["data"].GetBinError(1)**2 - in_err_data**2)
    total_err_data = hists_ss_before["data"].GetBinError(1)

    in_lostlep = hists_ss_after["lostlep"][1]
    out_lostlep = hists_ss_before["lostlep"][1] - in_lostlep
    total_lostlep = hists_ss_before["lostlep"][1]
    in_err_lostlep = hists_ss_after["lostlep"].GetBinError(1)
    out_err_lostlep = math.sqrt(hists_ss_after["lostlep"].GetBinError(1)**2 - in_err_lostlep**2)
    total_err_lostlep = hists_ss_before["lostlep"].GetBinError(1)

    ineff_data = out_data / total_data;
    ineff_err_data = math.sqrt((out_err_data / out_data)**2 + (total_err_data / total_data)**2)
    ineff_mc = out_lostlep / total_lostlep;
    ineff_err_mc = math.sqrt((out_err_lostlep / out_lostlep)**2 + (total_err_lostlep / total_lostlep)**2)

    # Create histograms with the calculation results so that it can be plotted/made into a table
    h_ineff_data = r.TH1F("lostlep ineff mjj ss data", "lostlep ineff mjj ss data", 4, 0, 4)
    h_ineff_mc = r.TH1F("lostlep ineff mjj ss mc", "lostlep ineff mjj ss mc", 4, 0, 4)

    h_ineff_data.GetXaxis().SetBinLabel(1, "ineff ($e$)")
    h_ineff_data.SetBinContent(1, ineff_data)
    h_ineff_data.SetBinError(1, ineff_err_data)

    h_ineff_mc.GetXaxis().SetBinLabel(1, "ineff ($e$)")
    h_ineff_mc.SetBinContent(1, ineff_mc)
    h_ineff_mc.SetBinError(1, ineff_err_mc)

    h_ineff_data.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_ineff_data.SetBinContent(2, out_data)

    h_ineff_data.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_ineff_data.SetBinContent(3, total_data)

    h_ineff_data.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_ineff_data.SetBinContent(4, total_data)

    h_ineff_mc.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_ineff_mc.SetBinContent(2, out_lostlep)

    h_ineff_mc.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_ineff_mc.SetBinContent(3, total_lostlep)

    h_ineff_mc.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_ineff_mc.SetBinContent(4, hists_ss_before_raw["lostlep"].GetBinError(1))

    # Write them out to a table/plot
    alloptions= { "output_name": "plots/{}/{}/lostlep_ineff_mjj_ss.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3" if is2017 else "35.9", "yield_prec": 3}
    alloptions["yield_table_caption"] = "Some numbers for same-sign channel $m_{jj}$ inefficiency measurement. Equation is that $\\textrm{ineff} = b / a$ and $\\textrm{ineff}_\\textrm{err} = \\sqrt(\\textrm{ineff} (1 - \\textrm{ineff}) / n)$"
    p.plot_hist(bgs=[h_ineff_mc], data=h_ineff_data, colors=colors, options=alloptions)

#----------------===============--------------------------------===============--------------------------------===============----------------
#----------------===============--------------------------------===============--------------------------------===============----------------
#----------------===============--------------------------------===============--------------------------------===============----------------

#________________________________________________________________________________________________________________________________________
# Things that happen under the hood
def get_histnames(fpath, region, syst=""):

    f = r.TFile(fpath)

    rtn = []

    for key in f.GetListOfKeys():
        if region in str(key.GetName()) and "Full{}_cutflow".format(syst) in str(key.GetName()):
            name = str(key.GetName())
            name = name.replace("_cutflow", "")
            rtn.append(name)

    return rtn;

def region_index(s):
    if "ee" in s and "Side" not in s: return 0
    if "em" in s and "Side" not in s: return 1
    if "mm" in s and "Side" not in s: return 2
    if "ee" in s and "Side" in s: return 3
    if "em" in s and "Side" in s: return 4
    if "mm" in s and "Side" in s: return 5
    if "0SFOS" in s: return 6
    if "1SFOS" in s: return 7
    if "2SFOS" in s: return 8
    else: return 999


#________________________________________________________________________________________________________________________________________
# One of the most important function in ths script
# This script dictates how the histograms are read from the root files.
# i.e. This does most of the leg work and the user will retrieve a nice dictionary of "samples":TH1s.
def get_hists(histnames, use_data_driven_fakes=False, docutflow=False, sfs={}, dorawcutflow=False):

    bkg_lists = {}
    bkg_lists["ddfakes"] = [ x for x in glob.glob(output_dirpath+"/ddfakes.root") ]
    bkg_lists["ewksubt"] = [ x for x in glob.glob(output_dirpath+"/ewksubt.root") ]

    if len(bkg_order) == 7:
        bkg_lists["lostlep"] = [ x for x in glob.glob(output_dirpath+"/lostlep_fit.root") ]
        bkg_lists["photon"]  = [ x for x in glob.glob(output_dirpath+"/photon_fit.root")  ]
        bkg_lists["qflip"]   = [ x for x in glob.glob(output_dirpath+"/qflip_fit.root")   ]
        bkg_lists["mcfakes"] = [ x for x in glob.glob(output_dirpath+"/fakes_fit.root")   ]
        bkg_lists["prompt"]  = [ x for x in glob.glob(output_dirpath+"/prompt_fit.root")  ]
    else:
        bkg_lists["lostlep"] = [ x for x in glob.glob(output_dirpath+"/lostlep.root") ]
        bkg_lists["photon"]  = [ x for x in glob.glob(output_dirpath+"/photon.root")  ]
        bkg_lists["qflip"]   = [ x for x in glob.glob(output_dirpath+"/qflip.root")   ]
        bkg_lists["mcfakes"] = [ x for x in glob.glob(output_dirpath+"/fakes.root")   ]
        bkg_lists["prompt"]  = [ x for x in glob.glob(output_dirpath+"/prompt.root")  ]

    bkg_lists["vbsww"]   = [ x for x in glob.glob(output_dirpath+"/vbsww.root")   ]
    bkg_lists["ttw"]     = [ x for x in glob.glob(output_dirpath+"/ttw.root")     ]

    bkg_lists["fakes"] = bkg_lists["ddfakes"] if use_data_driven_fakes else bkg_lists["mcfakes"]

    sig_list  = glob.glob(output_dirpath+"/*t_www_*/*.root")
    vh_list   = glob.glob(output_dirpath+"/*VH*t_www_*/*.root")
    www_list  = glob.glob(output_dirpath+"/*WWW*t_www_*/*.root")
    data_list = glob.glob(output_dirpath+"/*Run2017*_t_ss*/*.root")
    sig_list  = glob.glob(output_dirpath+"/signal.root")
    data_list = glob.glob(output_dirpath+"/data.root")

    do_retrieve_data_event_based_histograms = ("Up" not in histnames[0] and "Down" not in histnames[0]) or ("Fake" in histnames[0])

    hists = {}
    if "__" in histnames[0] or docutflow:
        hists["lostlep"] = ru.get_summed_histogram(bkg_lists["lostlep"] , histnames , sfs=sfs)
        hists["photon"]  = ru.get_summed_histogram(bkg_lists["photon"]  , histnames , sfs=sfs)
        hists["qflip"]   = ru.get_summed_histogram(bkg_lists["qflip"]   , histnames , sfs=sfs)
        hists["ewksubt"] = ru.get_summed_histogram(bkg_lists["ewksubt"] , histnames , sfs=sfs)
        hists["prompt"]  = ru.get_summed_histogram(bkg_lists["prompt"]  , histnames , sfs=sfs)
        hists["vbsww"]   = ru.get_summed_histogram(bkg_lists["vbsww"]   , histnames , sfs=sfs)
        hists["ttw"]     = ru.get_summed_histogram(bkg_lists["ttw"]     , histnames , sfs=sfs)
        hists["www"]     = ru.get_summed_histogram(sig_list             , histnames , sfs=sfs)
        # Only access data root file when accessing nominal variation
        if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
            hists["fakes"]   = ru.get_summed_histogram(bkg_lists["fakes"]   , histnames , sfs=sfs)
        if do_retrieve_data_event_based_histograms:
            hists["data"]    = ru.get_summed_histogram(data_list            , histnames , sfs=sfs)
    else:
        labels = ru.remove_all_common_longest_common_substring(histnames)
        labels = [ l.replace("FO","SFOS") for l in labels ]
        labels = [ l.replace("ide","side-") for l in labels ]
        hists["lostlep"] = ru.get_yield_histogram(bkg_lists["lostlep"] , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["photon"]  = ru.get_yield_histogram(bkg_lists["photon"]  , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["qflip"]   = ru.get_yield_histogram(bkg_lists["qflip"]   , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["ewksubt"] = ru.get_yield_histogram(bkg_lists["ewksubt"] , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["prompt"]  = ru.get_yield_histogram(bkg_lists["prompt"]  , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["vbsww"]   = ru.get_yield_histogram(bkg_lists["vbsww"]   , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["ttw"]     = ru.get_yield_histogram(bkg_lists["ttw"]     , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["www"]     = ru.get_yield_histogram(sig_list             , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        # Only access data root file when accessing nominal variation
        if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
            hists["fakes"]   = ru.get_yield_histogram(bkg_lists["fakes"]   , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        if do_retrieve_data_event_based_histograms:
            hists["data"]    = ru.get_yield_histogram(data_list            , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))

    if use_data_driven_fakes:
        if do_retrieve_data_event_based_histograms:
            for i in xrange(1, hists["ewksubt"].GetNbinsX()+1):
                if hists["ewksubt"].GetBinContent(i) > 0:
                    hists["ewksubt"].SetBinContent(i, 0)
            hists["fakes"].Add(hists["ewksubt"])

    hists["lostlep"] .SetName("Lost/three lep")
    hists["photon"]  .SetName("#gamma#rightarrow lepton")
    hists["qflip"]   .SetName("Charge mis-id")
    if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
        hists["fakes"].SetName("Non-prompt")
    hists["prompt"]  .SetName("Irredu.")
    hists["www"]     .SetName("WWW")
    if do_retrieve_data_event_based_histograms:
        hists["data"].SetName("Data")
    hists["vbsww"]   .SetName("VBS W^{#pm}W^{#pm}")
    hists["ttw"]     .SetName("ttW")

    hists["lostlep"] .SetTitle("lostlep")
    hists["photon"]  .SetTitle("photon")
    hists["qflip"]   .SetTitle("qflip")
    if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
        hists["fakes"].SetTitle("fakes")
    hists["prompt"]  .SetTitle("prompt")
    hists["www"]     .SetTitle("www")
    if do_retrieve_data_event_based_histograms:
        hists["data"].SetTitle("data")
    hists["vbsww"]   .SetTitle("vbsww")
    hists["ttw"]     .SetTitle("ttw")

    from plottery import utils as u
    for h in hists:
        u.move_in_overflows(hists[h])

    return hists

def get_yield_hists(region, use_data_driven_fakes, sfs={}, syst=""):
    histnames = get_histnames(output_dirpath + "/signal.root", region, syst)
    if len(histnames) == 0:
        histnames = get_histnames(output_dirpath + "/ddfakes.root", region, syst)
    histnames.sort(key=region_index)
    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=sfs)
    for h in hists:
        hists[h] = ru.remove_negative_or_zero(hists[h])
    if region == "WZCR": # Special treatment for WZCR
        for h in hists:
            tmphist = r.TH1F(hists[h].GetName(), hists[h].GetTitle(), 9, 0, 9)
            tmphist.Sumw2()
            tmphist.SetBinContent(1, hists[h].GetBinContent(1))
            tmphist.SetBinContent(2, hists[h].GetBinContent(2))
            tmphist.SetBinContent(3, hists[h].GetBinContent(3))
            tmphist.SetBinContent(4, hists[h].GetBinContent(1))
            tmphist.SetBinContent(5, hists[h].GetBinContent(2))
            tmphist.SetBinContent(6, hists[h].GetBinContent(3))
            tmphist.SetBinContent(8, hists[h].GetBinContent(4))
            tmphist.SetBinContent(9, hists[h].GetBinContent(5))
            hists[h] = tmphist
    #hists["lostlep"].Print("all")
    return hists

if __name__ == "__main__":
    main()

