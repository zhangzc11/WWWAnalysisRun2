#!/bin/env python

# Get WZ uncertainties
# Get VBS/Gamma VR uncertainties
# Get Fake uncertainties
# Create data card

from rooutil import rooutil as ru
from rooutil import plottery_wrapper as p
from rooutil import datacard_writer as dw
import glob
import ROOT as r

output_dirpath = "outputs/WWW2016_v4.0.5/test3"
output_dirpath = "outputs/condor/WWW2016_v4.0.5/test2"
output_dirpath = "outputs/WWW_v1.2.2/test1"
output_dirpath = "outputs/condor/WWW_v1.2.2/test1"
output_dirpath = "outputs/condor/WWW_v1.2.2/test8"
output_dirpath = "outputs/WWW2016_v4.0.6/test4"
output_dirpath = "outputs/condor/WWW2017_v4.0.5/test1"
output_dirpath = "outputs/condor/WWW2016_v4.0.6/test5"
output_dirpath = "outputs/condor/WWW2016_v4.0.6/test6"
output_dirpath = "outputs/condor/WWW2016_v4.0.6/test9"
output_dirpath = "outputs/condor/WWW2016_v4.0.6/test10"
is2017 = "WWW2017" in output_dirpath

# Bkg order
#bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
bkg_order = ["fakes", "photon", "lostlep", "qflip", "prompt", "ttw", "vbsww"]
colors_map = {"photon":920, "qflip":2007, "lostlep":2003, "prompt":2001, "fakes":2005, "sig":2, "vbsww":2002, "ttw":2004}
colors = [ colors_map[b] for b in bkg_order ]

def main():
    write_datacard()
#    plotSR()
#    plot()
#    get_wzsf()
#    study_wz()
#    oscr()

def write_datacard():

    # List of processes

    # Get the main yield
    wzsf = get_wzsf()
    hists = get_yield_hists("SR", True, wzsf) # Get the main yields
    systs = get_systs() # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in bkg_order ]

    # Write to the datacard
    #ru.write_shape_fit_datacard(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs)
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])
    d.set_bin(1)
    d.set_region_name("SRSSee")
    #print d.get_str()
    d.write("datacard_SRSSee.txt")
    d.set_bin(2)
    d.set_region_name("SRSSem")
    #print d.get_str()
    d.write("datacard_SRSSem.txt")
    d.set_bin(3)
    d.set_region_name("SRSSmm")
    #print d.get_str()
    d.write("datacard_SRSSmm.txt")
    d.set_bin(4)
    d.set_region_name("SRSSSideee")
    #print d.get_str()
    d.write("datacard_SRSSSideee.txt")
    d.set_bin(5)
    d.set_region_name("SRSSSideem")
    #print d.get_str()
    d.write("datacard_SRSSSideem.txt")
    d.set_bin(6)
    d.set_region_name("SRSSSidemm")
    #print d.get_str()
    d.write("datacard_SRSSSidemm.txt")
    d.set_bin(7)
    d.set_region_name("SR0SFOS")
    #print d.get_str()
    d.write("datacard_SR0SFOS.txt")
    d.set_bin(8)
    d.set_region_name("SR1SFOS")
    #print d.get_str()
    d.write("datacard_SR1SFOS.txt")
    d.set_bin(9)
    d.set_region_name("SR2SFOS")
    #print d.get_str()
    d.write("datacard_SR2SFOS.txt")
    d.write()

def get_wzalpha():
    hists = get_yield_hists("WZCR", False)
    bgs = [ hists[x] for x in bkg_order ]
    histsSR = get_yield_hists("SR", False)
    alpha = ru.get_alpha(histsSR["lostlep"], hists["lostlep"], hists["data"], [hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"], hists["ttw"], hists["vbsww"]])
    return alpha

def get_wzsf():
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

def get_systs():

    # Get the main yield
    wzsf = get_wzsf()
    hists = get_yield_hists("SR", True, wzsf)
    #hists["lostlep"].Print("all")

    systs = []

    # Usual systematic variations for both signal and backgrounds
    syst_names = ["JES", "LepSF", "TrigSF", "BTagLF", "BTagHF", "Pileup"]
    for sys in syst_names:
        sys_hists_up = get_yield_hists("SR", True, wzsf, sys+"Up")
        sys_hists_dn = get_yield_hists("SR", True, wzsf, sys+"Down")
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
        sys_hists_up = get_yield_hists("SR", True, wzsf, sys+"Up")
        sys_hists_dn = get_yield_hists("SR", True, wzsf, sys+"Down")
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
        sys_hists_up = get_yield_hists("SR", True, wzsf, sys+"Up")
        sys_hists_dn = get_yield_hists("SR", True, wzsf, sys+"Down")
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["www"]:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # WZ CR Stats
    wzalpha = get_wzalpha()
    data_yield = get_yield_hists("WZCR", False)
    systnames = ["WZCRSSeeFull_CRstat", "WZCRSSemFull_CRstat", "WZCRSSmmFull_CRstat", "WZCR1SFOSFull_CRstat", "WZCR2SFOSFull_CRstat"]
    for sys in systnames:
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["lostlep"]:
                systval[proc] = modify_wzalpha(wzalpha, sys)
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

def plotSR():

    # Regions to plot
    region = "SR"
    use_data_driven_fakes = True
    histnames = get_histnames(output_dirpath + "/signal.root", region)
    histnames.sort(key=region_index)
    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=(get_wzsf() if region == "SR" else {}))
    alloptions= {
                "ratio_range":[0.0,2.2],
                "nbins": 15,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/test.pdf",
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": True,
                "yield_prec": 1,
                "blind": True if "SR" in histnames[0] else False,
                #"blind": False,
                "lumi_value": "41.3" if is2017 else "35.9",
                #"yaxis_range": [0., 40.],
                }

    bgs = [ ru.remove_negative_or_zero(hists[x]) for x in bkg_order ]
    bgs_dict = {}
    for x in bkg_order:
        bgs_dict[x] = hists[x].Clone()
    p.plot_hist(
            sigs = [hists["www"]],
            bgs  = bgs,
            data = hists["data"],
            colors = colors,
            #syst = ru.get_total_error(bgs_dict, get_systs()),
            syst = None,
            options=alloptions)

def plot():

    # Regions to plot
    region = "WZCR"
    use_data_driven_fakes = False

    # Bkg stack order

    histnames = get_histnames(output_dirpath + "/signal.root", region)
    histnames.sort(key=region_index)

    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=(get_wzsf() if region == "SR" else {}))

    alloptions= {
                "ratio_range":[0.0,2.2],
                "nbins": 15,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/test.pdf",
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": True,
                "blind": True if "SR" in histnames[0] else False,
                #"blind": False,
                "lumi_value": "41.3",
                }

    bgs = [ hists[x] for x in bkg_order ]

    p.plot_hist(
            sigs = [hists["www"]],
            bgs  = bgs,
            data = hists["data"],
            colors = colors,
            syst = None,
            options=alloptions)

def study_wz():
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
    #for hist in hists:
        #hist.Divide(h_nom_tf)
    #h_nom_tf.Divide(h_nom_tf)
    alloptions= { "output_name": "plots/test.pdf", "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 5}
    p.plot_hist(sigs=hists, bgs=[h_nom_tf], options=alloptions)

def oscr():

    output_dirpath = "outputs/WWW2017_analysis_v0.44.1_byproc"
    sample_lists = {}
    sample_lists["Z"]    = [ x for x in glob.glob(output_dirpath+"/DY*.root") ]
    sample_lists["top"]  = [ x for x in glob.glob(output_dirpath+"/TT*.root") ]
    sample_lists["top"] += [ x for x in glob.glob(output_dirpath+"/ST_*.root") ]
    sample_lists["W"]    = [ x for x in glob.glob(output_dirpath+"/WJ*.root") ]
    sample_lists["MB"]   = [ x for x in glob.glob(output_dirpath+"/WW*.root") ]
    sample_lists["MB"]  += [ x for x in glob.glob(output_dirpath+"/WZTo1*.root") ]
    sample_lists["MB"]  += [ x for x in glob.glob(output_dirpath+"/WZTo2*.root") ]
    sample_lists["MB"]  += [ x for x in glob.glob(output_dirpath+"/WZTo3LNu_Tu*.root") ]
    sample_lists["MB"]  += [ x for x in glob.glob(output_dirpath+"/ZZ*.root") ]
    sample_lists["data"] = [ x for x in glob.glob(output_dirpath+"/*Run2017*.root") ]

    bkgs = [ "Z", "top", "W" , "MB"]

    #histnames = ["OSCRmm__MllSS"]
    #histnames = ["OSCRee__MllSS"]
    #histnames = ["OSCRem__nb"]
    #histnames = ["OSCRem__nj"]
    #histnames = ["OSCRem__nj30"]
    #histnames = ["OSCRem__nvtx"]
    #histnames = ["OSCRem__MET"]
    #histnames = ["OSCRem__MllSS"]

    histnames = [
            "WZCRSSeeFull",
            "WZCRSSemFull",
            "WZCRSSmmFull",
            "WZCR1SFOSFull",
            "WZCR2SFOSFull",
            ]

    hists = {}
    for bkg in bkgs:
        if "__" in histnames[0]:
            hists[bkg] = ru.get_summed_histogram(sample_lists[bkg], histnames).Clone(bkg)
        else:
            hists[bkg] = ru.get_yield_histogram(sample_lists[bkg], histnames).Clone(bkg)

    if "__" in histnames[0]:
        hists["data"] = ru.get_summed_histogram(sample_lists["data"] , histnames).Clone("data")
    else:
        hists["data"] = ru.get_yield_histogram(sample_lists["data"] , histnames).Clone("data")


    alloptions= {
                "ratio_range":[0.3,1.7],
                "nbins": 15,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/test.pdf",
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": True,
                #"blind": True if "SR" in histnames[0] else False,
                "blind": False,
                "lumi_value": "41.3",
                #"yaxis_log": True,
                #"yaxis_range": [1, 5e10],
                "legend_smart": False,
                }

    bgs = [ hists[x] for x in bkgs ]

    p.plot_hist(
            sigs = [],
            bgs  = bgs,
            data = hists["data"],
            colors = colors,
            syst = None,
            options=alloptions)


###########################################################################################################3

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


def get_hists(histnames, use_data_driven_fakes=False, docutflow=False, sfs={}):

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
        hists["lostlep"] = ru.get_yield_histogram(bkg_lists["lostlep"] , histnames , sfs=sfs)
        hists["photon"]  = ru.get_yield_histogram(bkg_lists["photon"]  , histnames , sfs=sfs)
        hists["qflip"]   = ru.get_yield_histogram(bkg_lists["qflip"]   , histnames , sfs=sfs)
        hists["ewksubt"] = ru.get_yield_histogram(bkg_lists["ewksubt"] , histnames , sfs=sfs)
        hists["prompt"]  = ru.get_yield_histogram(bkg_lists["prompt"]  , histnames , sfs=sfs)
        hists["vbsww"]   = ru.get_yield_histogram(bkg_lists["vbsww"]   , histnames , sfs=sfs)
        hists["ttw"]     = ru.get_yield_histogram(bkg_lists["ttw"]     , histnames , sfs=sfs)
        hists["www"]     = ru.get_yield_histogram(sig_list             , histnames , sfs=sfs)
        # Only access data root file when accessing nominal variation
        if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
            hists["fakes"]   = ru.get_yield_histogram(bkg_lists["fakes"]   , histnames , sfs=sfs)
        if do_retrieve_data_event_based_histograms:
            hists["data"]    = ru.get_yield_histogram(data_list            , histnames , sfs=sfs)

    if use_data_driven_fakes:
        if do_retrieve_data_event_based_histograms:
            for i in xrange(1, hists["ewksubt"].GetNbinsX()+1):
                if hists["ewksubt"].GetBinContent(i) > 0:
                    hists["ewksubt"].SetBinContent(i, 0)
            hists["fakes"].Add(hists["ewksubt"])

    hists["lostlep"] .SetName("Lost/three lep")
    hists["photon"]  .SetName("#gamma#rightarrowlepton")
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

def modify_wzalpha(wzalpha, regname):
    tmphist = wzalpha.Clone()
    if "SSee" in regname:
        tmphist.SetBinContent(2,0)
        tmphist.SetBinContent(3,0)
        tmphist.SetBinContent(5,0)
        tmphist.SetBinContent(6,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)
        tmphist.SetBinContent(9,0)
    elif "SSem" in regname:
        tmphist.SetBinContent(1,0)
        tmphist.SetBinContent(3,0)
        tmphist.SetBinContent(4,0)
        tmphist.SetBinContent(6,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)
        tmphist.SetBinContent(9,0)
    elif "SSmm" in regname:
        tmphist.SetBinContent(1,0)
        tmphist.SetBinContent(2,0)
        tmphist.SetBinContent(4,0)
        tmphist.SetBinContent(5,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)
        tmphist.SetBinContent(9,0)
    elif "SSSideee" in regname:
        tmphist.SetBinContent(2,0)
        tmphist.SetBinContent(3,0)
        tmphist.SetBinContent(5,0)
        tmphist.SetBinContent(6,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)
        tmphist.SetBinContent(9,0)
    elif "SSSideem" in regname:
        tmphist.SetBinContent(1,0)
        tmphist.SetBinContent(3,0)
        tmphist.SetBinContent(4,0)
        tmphist.SetBinContent(6,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)
        tmphist.SetBinContent(9,0)
    elif "SSSidemm" in regname:
        tmphist.SetBinContent(1,0)
        tmphist.SetBinContent(2,0)
        tmphist.SetBinContent(4,0)
        tmphist.SetBinContent(5,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)
        tmphist.SetBinContent(9,0)
    elif "1SFOS" in regname:
        tmphist.SetBinContent(1,0)
        tmphist.SetBinContent(2,0)
        tmphist.SetBinContent(3,0)
        tmphist.SetBinContent(4,0)
        tmphist.SetBinContent(5,0)
        tmphist.SetBinContent(6,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(9,0)
    elif "2SFOS" in regname:
        tmphist.SetBinContent(1,0)
        tmphist.SetBinContent(2,0)
        tmphist.SetBinContent(3,0)
        tmphist.SetBinContent(4,0)
        tmphist.SetBinContent(5,0)
        tmphist.SetBinContent(6,0)
        tmphist.SetBinContent(7,0)
        tmphist.SetBinContent(8,0)

    return tmphist


if __name__ == "__main__":
    main()

