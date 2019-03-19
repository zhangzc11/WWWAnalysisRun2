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
    is2017 = "2017" in output_dirpath

def set_to_2016_v122():
    global input_ntuple
    global analysis_tag
    global iscondor
    global hassyst
    global hashist

    #---
    input_ntuple = "WWW_v1.2.2"
    analysis_tag = "test2"
    iscondor = False

    hassyst = True
    hashist = False
    process_output_dirpath()

# 2016 analysis re-processed
def set_to_2016():
    global input_ntuple
    global analysis_tag
    global iscondor
    global hassyst
    global hashist

    #---
    input_ntuple = "WWW2016_v4.0.5"
    analysis_tag = "test2"
    iscondor = True

    #---
    input_ntuple = "WWW2016_v5.0.2"
    analysis_tag = "jerstudy_v1"
    iscondor = False

    #---
    input_ntuple = "WWW2016_v5.0.3"
    analysis_tag = "jerstudy_v1"
    iscondor = False

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

    #---
    #input_ntuple = "WWW2017_v4.0.6"
    #analysis_tag = "test22"

    #---
    input_ntuple = "WWW2017_v4.0.6.2"
    analysis_tag = "test25"
    analysis_tag = "test26" # WZ jet binned
    iscondor = True

    #---
    input_ntuple = "Loose2017_v4.0.6.2"
    analysis_tag = "test28"
    analysis_tag = "test29"
    iscondor = True

    #---
    input_ntuple = "Loose2017_v4.0.6.2"
    analysis_tag = "test4"
    iscondor = False

    #---
    input_ntuple = "WWW2017_v4.0.6.2"
    analysis_tag = "test30"
    iscondor = True

    #---
    input_ntuple = "WWW2017_v5.0.0"
    analysis_tag = "test31"
    iscondor = True

    #---
    input_ntuple = "WWW2017_v5.0.0"
    analysis_tag = "test35"
    iscondor = True

    #---
    input_ntuple = "WWW2017_v5.0.0"
    analysis_tag = "test1"
    iscondor = False

    hassyst = True
    hashist = False
    process_output_dirpath()

#########################################################################################################################################
#########################################################################################################################################
#########################################################################################################################################
#########################################################################################################################################

# Bkg order
bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
bkg_order_5 = ["photon", "qflip", "fakes", "lostlep", "prompt"]
bkg_order_7 = ["fakes", "photon", "lostlep", "qflip", "prompt", "ttw", "vbsww"]
colors_map = {"photon":920, "qflip":2007, "lostlep":2003, "prompt":2001, "fakes":2005, "sig":2, "vbsww":2002, "ttw":2004}
colors = [ colors_map[b] for b in bkg_order ]

def set_bkg_to_7():
    global bkg_order
    global colors
    bkg_order = bkg_order_7
    colors = [ colors_map[b] for b in bkg_order ]

def set_bkg_to_5():
    global bkg_order
    global colors
    bkg_order = bkg_order_5
    colors = [ colors_map[b] for b in bkg_order ]

#________________________________________________________________________________________________________________________________________
def make_test_plots():

    set_to_2017()
    plot(["SRSSmmNb0__lep_pt1"], "SRSSmmNb0__lep_pt1", False, caption="", do_ewksubtraction=False)#, extraoptions={"yaxis_range":[0.,25.]})

    return

    set_to_2016_v122()
    # set_to_2016()

    study_lostlep()
    plot("SR", "sr_yield", True, caption="Signal region yields with each process set to its background estimation method's prediction.", do_ewksubtraction=False)#, extraoptions={"yaxis_range":[0.,25.]})

    write_datacard()
    write_datacard_w_control_regions()

    return

    set_to_2017()
    plot("SR", "sr_yield", True, caption="Signal region yields with each process set to its background estimation method's prediction.", do_ewksubtraction=False)#, extraoptions={"yaxis_range":[0.,25.]})

    write_datacard()
    return

    set_to_2016()

    # Money plot
    plot("SR", "sr_yield", True, caption="Signal region yields with each process set to its background estimation method's prediction.", do_ewksubtraction=False, extraoptions={"yaxis_range":[0.,25.]})
    # plot("SR", "sr_rawyield", True, caption="Signal region raw yields with each process set to its background estimation method's prediction.", do_ewksubtraction=False, dorawcutflow=True)
    # plot("AR", "ar_yield_mc", False, caption="Application region yields with WZ set to its bkg. est. method. fake is from MC", do_ewksubtraction=False, extraoptions={"yaxis_range":[0.,500.]})
    # plot("WZCR", "wzcr_yield", False, caption="Signal region yields with each process set to its background estimation method's prediction.", do_ewksubtraction=False)

    # study_jer_syst()

    #write_datacard()

    # MVA preselection
    #plot(["SRSSeeFull(10)", "SRSSemFull(9)", "SRSSmmFull(9)"], "pr_yield", False, caption="Preselection region yields with MC estimation on yields.", dorawcutflow=True)
    #plot(["SRSSemNb0__Mjj", "SRSSmmNb0__Mjj"], "pr_Mjj", False, caption="Preselection region (em+mm) only $m_{jj}$ distribution")
    #plot(["SRSSemNb0__MinMlj", "SRSSmmNb0__MinMlj"], "pr_MinMlj", False, caption="Preselection region (em+mm) only $m_{min,lj}$ distribution", nbin=30)
    #plot(["SRSSemNb0__MaxMlj", "SRSSmmNb0__MaxMlj"], "pr_MaxMlj", False, caption="Preselection region (em+mm) only $m_{max,lj}$ distribution", nbin=30)
    #plot(["SRSSemNb0__SumMlj", "SRSSmmNb0__SumMlj"], "pr_SumMlj", False, caption="Preselection region (em+mm) only $#Sigmam_{lj}$ distribution", nbin=30)
    #plot(["SRSSemNb0__MinMljj", "SRSSmmNb0__MinMljj"], "pr_MinMljj", False, caption="Preselection region (em+mm) only $m_{min,ljj}$ distribution", nbin=30)
    #plot(["SRSSemNb0__MaxMljj", "SRSSmmNb0__MaxMljj"], "pr_MaxMljj", False, caption="Preselection region (em+mm) only $m_{max,ljj}$ distribution", nbin=30)
    #plot(["SRSSemNb0__SumMljj", "SRSSmmNb0__SumMljj"], "pr_SumMljj", False, caption="Preselection region (em+mm) only $#Sigmam_{ljj}$ distribution", nbin=30)
    #plot(["SRSSmmNb0__MinMlj"], "pr_mm_MinMlj", False, caption="Preselection region (em+mm) only $m_{min,lj}$ distribution", nbin=30)
    #plot(["SRSSemNb0__MinMlj"], "pr_em_MinMlj", False, caption="Preselection region (em+mm) only $m_{min,lj}$ distribution", nbin=30)

    #plot(["WZCRSSeeFull__nj", "WZCRSSemFull__nj", "WZCRSSmmFull__nj", "WZCR1SFOSFull__nj", "WZCR2SFOSFull__nj"], "lostlep_cr_nj", False)
    #plot(["LRSSmmMjjW__lep_relIso03EAv2LepMaxSS", ], "ssmm_lr_lepisomaxss", False, nbin=40, blind=True, extraoptions={"yaxis_range":[0.,5]})

    #plot(["SRSSmmNj2__lep_pt1"], "pr_ssmm_lep_pt1", False, caption="preselection region sub-leading lepton Pt", nbin=30)
    #plot(["SRSSemNj2__lep_pt1"], "pr_ssem_lep_pt1", False, caption="preselection region sub-leading lepton Pt", nbin=30)
    #plot(["SRSSeeNj2__lep_pt1"], "pr_ssee_lep_pt1", False, caption="preselection region sub-leading lepton Pt", nbin=30)

    #plot(["WZVR1SFOSMllOnOff__MllOnOff", "WZVR2SFOSMllOnOff__MllOnOff"], "lostlep_cr_3l_msfos", False, extraoptions={"yaxis_log": True, "yaxis_range": [0.1, 1000000]}, nbin=60)
    #plot(["WZVR1SFOSMllOnOff__MllOnOff", "WZVR2SFOSMllOnOff__MllOnOff"], "lostlep_cr_3l_msfos", False, extraoptions={"yaxis_range": [0.5, 50]}, nbin=60)

    #optimize_leptons()

    #check_stats()

    return

#________________________________________________________________________________________________________________________________________
def make_2016_v122_plots():

    set_to_2016_v122()
    produce_main_plots()

#________________________________________________________________________________________________________________________________________
def make_2017_plots():

    set_to_2017()
    produce_main_plots()

#________________________________________________________________________________________________________________________________________
def produce_main_plots():

    # Money plot
    plot("SR", "sr_yield", True, caption="Signal region yields with each process set to its background estimation method's prediction.", do_ewksubtraction=True if "v1.2.2" not in input_ntuple else False)
    plot("SR", "sr_yield_mc", False, caption="Signal region yields with WZ set to its bkg. est. method. fake is from MC")

    # Plot lost lepton yields
    plot("WZCR", "lostlep_cr_yield", False, caption="Lost lepton control region yields.")
    plot(["WZCRSSeeMllSS__MllOnOff", "WZCRSSemMTmax__MllOnOff", "WZCRSSmmMllSS__MllOnOff"], "lostlep_cr_ss_msfos", False)
    plot(["WZVR1SFOSMllOnOff__MllOnOff", "WZVR2SFOSMllOnOff__MllOnOff"], "lostlep_cr_3l_msfos", False, nbin=20)
    plot(["WZVR1SFOSMllOnOff__MllOnOff"], "lostlep_cr_3l_msfos_1sfos", False, nbin=20)
    plot(["WZVR2SFOSMllOnOff__MllOnOff"], "lostlep_cr_3l_msfos_2sfos", False, nbin=20)
    plot(["WZVRSSee__MjjZoom", "WZVRSSem__MjjZoom", "WZVRSSmm__MjjZoom"], "lostlep_cr_ss_mjj", False, 8)

    set_bkg_to_7()
    plot(["VBSCRSSeeFull__MjjVBF", "VBSCRSSemFull__MjjVBF", "VBSCRSSmmFull__MjjVBF"], "vbsww_cr_ss_mjj", False, 8)
    plot(["VBSCRSSeeFull__DetajjL", "VBSCRSSemFull__DetajjL", "VBSCRSSmmFull__DetajjL"], "vbsww_cr_ss_detajj", False, 8)
    plot(["TTWCRSSeeFull__nb", "TTWCRSSemFull__nb", "TTWCRSSmmFull__nb"], "ttw_cr_ss_nb", False)
    plot(["TTWCRSSeeFull__MET", "TTWCRSSemFull__MET", "TTWCRSSmmFull__MET"], "ttw_cr_ss_MET", False, 6)
    set_bkg_to_5()

    # Print extrapolation factors
    study_lostlep()

    # Study msfos modeling
    study_msfos_modeling()

    # Study mjj modeling
    study_mjj_modeling()

    # Fake estimate plots
    fake_est_plots()

    # Writing datacards
    write_datacard()
    write_datacard_w_control_regions()

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
    # d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])

    # Region names
    reg_names = [ "SRSSee", "SRSSem", "SRSSmm", "SRSSSideee", "SRSSSideem", "SRSSSidemm", "SR0SFOS", "SR1SFOS", "SR2SFOS" ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("plots/{}/{}/datacard_{}.txt".format(input_ntuple, analysis_tag, reg_name))

#________________________________________________________________________________________________________________________________________
# Writing statistics datacards
def write_datacard_w_control_regions():

    #
    # Signal region
    #

    global bkg_order
    bkg_order = ["fakes", "photon", "lostlep", "qflip", "prompt", "ttw", "vbsww"]

    # Get the main yield
    lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors
    # hists = get_yield_hists("SR", True, lostlep_sf) # Get the main yields with lost lepton scale factors applied
    hists = get_yield_hists("SR", True) # Get the main yields with lost lepton scale factors applied
    systs = get_systs(apply_lostlep_sf=False) # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in bkg_order ]

    # Write to the datacard
    # d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs)
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs)

    # Region names
    reg_names = [ "v2_SRSSee", "v2_SRSSem", "v2_SRSSmm", "v2_SRSSSideee", "v2_SRSSSideem", "v2_SRSSSidemm", "v2_SR0SFOS", "v2_SR1SFOS", "v2_SR2SFOS" ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("plots/{}/{}/datacard_{}.txt".format(input_ntuple, analysis_tag, reg_name))

    #
    # Lost Lep Control region
    #

    # Get the main yield
    lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors
    hists = get_yield_hists("WZCR", True) # Get the main yields with lost lepton scale factors applied
    systs = get_systs("WZCR") # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in bkg_order ]

    # Write to the datacard
    # d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs)
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs)

    # Region names
    reg_names = [ "v2_WZCRSSee", "v2_WZCRSSem", "v2_WZCRSSmm", "v2_WZCR1SFOS", "v2_WZCR2SFOS" ]

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
def get_systs(region="SR", apply_lostlep_sf=True):

    # Get the main yield
    lostlep_sf = get_lostlep_sf() if region == "SR" and apply_lostlep_sf else {}
    hists = get_yield_hists(region, True, lostlep_sf)

    systs = []

    # Usual systematic variations for both signal and backgrounds
    syst_names = ["JES", "LepSF", "TrigSF", "BTagLF", "BTagHF", "Pileup"]
    if "v1.2.2" not in input_ntuple:
        syst_names += ["JER"]
    for sys in syst_names:
        sys_hists_up = get_yield_hists(region, True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists(region, True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + bkg_order + ["lostlep"]:
            if proc in ["www", "qflip", "prompt", "photon", "ttw", "vbsww"]:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            # elif proc == "lostlep":
            #     lostlep_yield_sysup = get_yield_hists(region, True, lostlep_sf)
            #     lostlep_yield_sysdn = get_yield_hists(region, True, lostlep_sf)
            #     lostlep_alpha_nom = get_lostlep_alpha()
            #     lostlep_alpha_sysup = get_lostlep_alpha(sys+"Up")
            #     lostlep_alpha_sysdn = get_lostlep_alpha(sys+"Down")
            #     lostlep_alpha_sysup.Divide(lostlep_alpha_nom)
            #     lostlep_alpha_sysdn.Divide(lostlep_alpha_nom)
            #     lostlep_alpha_sysup.SetBinContent(7, lostlep_alpha_sysup.GetBinContent(8))
            #     lostlep_alpha_sysdn.SetBinContent(7, lostlep_alpha_sysdn.GetBinContent(8))
            #     lostlep_yield_sysup[proc].Multiply(lostlep_alpha_sysup)
            #     lostlep_yield_sysdn[proc].Multiply(lostlep_alpha_sysdn)
            #     systval[proc] = [lostlep_yield_sysup[proc], lostlep_yield_sysdn[proc]] 
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # Fake systematics
    for sys in ["FakeRateEl", "FakeRateMu", "FakeClosureEl", "FakeClosureMu"]:
        sys_hists_up = get_yield_hists(region, True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists(region, True, lostlep_sf, sys+"Down")
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
        sys_hists_up = get_yield_hists(region, True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists(region, True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + bkg_order:
            if proc in ["www"]:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # LostLep alpha MC statistical error
    if apply_lostlep_sf:
        hists = get_yield_hists(region, True)
        h_mcstat_alpha = hists["lostlep"].Clone()
        hnom = get_yield_hists(region, True, lostlep_sf)["lostlep"].Clone()
        hnom_raw = hnom.Clone()
        h_mcstat_alpha.Divide(get_yield_hists("WZCR", True)["lostlep"])
        for i in xrange(len(h_mcstat_alpha)):
            h_mcstat_alpha.SetBinContent(i+1, 1 + (h_mcstat_alpha.GetBinError(i+1) / h_mcstat_alpha.GetBinContent(i+1) if h_mcstat_alpha.GetBinContent(i+1) != 0 else 0))
        h_mcstat_alpha.SetBinContent(7, h_mcstat_alpha.GetBinContent(8))
        hnom.Multiply(h_mcstat_alpha)
        systnames = ["llalpha_SRSSee_stat", "llalpha_SRSSem_stat", "llalpha_SRSSmm_stat", "llalpha_Sideee_stat", "llalpha_Sideem_stat", "llalpha_Sidemm_stat", "llalpha_SR0SFOS_stat", "llalpha_SR1SFOS_stat", "llalpha_SR2SFOS_stat"]
        syst_relevant_bins = {
                "llalpha_SRSSee_stat"  : [1],
                "llalpha_SRSSem_stat"  : [2],
                "llalpha_SRSSmm_stat"  : [3],
                "llalpha_Sideee_stat"  : [4],
                "llalpha_Sideem_stat"  : [5],
                "llalpha_Sidemm_stat"  : [6],
                "llalpha_SR0SFOS_stat" : [7],
                "llalpha_SR1SFOS_stat" : [8],
                "llalpha_SR2SFOS_stat" : [9],
                }
        for sys in systnames:
            systval = {}
            for proc in ["www"] + bkg_order:
                if proc == "lostlep":
                    systval[proc] = [ "{:.4f}".format((hnom.GetBinContent(i)/hnom_raw.GetBinContent(i) if hnom_raw.GetBinContent(i) > 0 else 1)) if i in syst_relevant_bins[sys] else "-" for i in xrange(1, hnom.GetNbinsX()+1) ]
                else:
                    systval[proc] = 0
            syst_datacard_data = (sys, 'lnN', [], systval)
            systs.append(syst_datacard_data)

    # LostLep CR Stats (only for SR)
    if region == "SR" and apply_lostlep_sf:
        lostlep_alpha_nominal = get_lostlep_alpha()
        lostlep_alpha = lostlep_alpha_nominal
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
def get_lostlep_alpha(syst=""):
    hists_nosyst = get_yield_hists("WZCR", False)
    hists = get_yield_hists("WZCR", False, syst=syst)
    bgs = [ hists[x] for x in bkg_order ]
    histsSR = get_yield_hists("SR", False, syst=syst)
    alpha = ru.get_alpha(histsSR["lostlep"], hists["lostlep"], hists_nosyst["data"], [hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"], hists["ttw"], hists["vbsww"]])
    return alpha

#________________________________________________________________________________________________________________________________________
# Main plotting script
def plot(histnames, outputfilename, use_data_driven_fakes=False, nbin=12, caption="", dorawcutflow=False, blind=False, extraoptions={}, docutscan=False, blowupfakes=1, lepscansystsmap={}, doroc=False, do_ewksubtraction=True):

    sfs = get_lostlep_sf() if histnames == "SR" else {}

    # If provided histnames are just a string indicating a region, then get the list of cutflow table histograms, and plot the yields.
    if isinstance(histnames, str):
        # Regions to plot
        histnames = get_histnames(output_dirpath + "/signal.root", histnames)
        histnames.sort(key=region_index) # Sort pretty

    # Now obtain the list of histograms
    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=sfs, dorawcutflow=dorawcutflow, do_ewksubtraction=do_ewksubtraction)

    if blowupfakes != 1:
        hists["fakes"].Scale(blowupfakes)

    # Set the option for plotting
    alloptions= {
                "ratio_range":[0.0,2.2],
                "nbins": nbin,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, outputfilename),
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": True,
                "yield_prec": 3,
                "yield_table_caption": caption,
                #"blind": True if ("SR" in histnames[0] and "Full" in histnames[0]) else blind,
                "blind": False,
                "lumi_value": "41.3" if is2017 else "35.9",
                #"yaxis_range": [0., 30],
                #"yaxis_log": True,
                }
    alloptions.update(extraoptions)

    # aggregate a list of backgrounds from the "hists"
    bgs = [ hists[x] for x in bkg_order ]

    plot_func = p.plot_hist
    if docutscan:
        plot_func = p.plot_cut_scan
        systs_map = lepscansystsmap
        syst = [ systs_map[x] for x in bkg_order ]
    if doroc:
        plot_func = p.plot_roc
        #systs_map = lepscansystsmap
        #syst = [ systs_map[x] for x in bkg_order ]
        alloptions["output_name"] = alloptions["output_name"].replace(".pdf", "_roc.pdf")
        plot_func(
                tps = [hists["www"]],
                fps = [hists["fakes"]],
                legend_labels = ["RelIso"],
                scanreverse = [True],
                colors = colors,
                cutvals = [0.03],
                options=alloptions,
                )
    else:
        # Now actually plot the histogram
        plot_func(
                sigs = [hists["www"]],
                bgs  = bgs,
                data = hists["data"],
                colors = colors,
                syst = syst if docutscan else None,
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
    alloptions= { "output_name": "plots/{}/{}/lostlep_exp_tf.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 3, "yield_table_caption": "Lost lepton transfer factor systematic variations."}
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
    alloptions= { "output_name": "plots/{}/{}/lostlep_exp_syst.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 3, "yield_table_caption": "Lost lepton transfer factor systematic variations."}
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
            #"WZVR2SFOSMllOnOffFull(-2)",
            #"WZVR2SFOSMllOnOffFull(-2)",
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
    hists_ss_after_raw = get_hists(histnames, False, "_cutflow" in histnames[0], sfs=(get_lostlep_sf() if histnames == "SR" else {}), dorawcutflow=True)

    # Mjj-in efficiency

    # Do the math
    import math
    eff_data = hists_ss_after["data"].Integral() / hists_ss_before["data"].Integral()
    eff_mc = hists_ss_after["lostlep"].Integral() / hists_ss_before["lostlep"].Integral()
    eff_err_data = math.sqrt(eff_data * (1 - eff_data) / hists_ss_before["data"].Integral())
    eff_err_mc = math.sqrt(eff_mc * (1 - eff_mc) / hists_ss_before_raw["lostlep"].Integral())

    # Create histograms with the calculation results so that it can be plotted/made into a table
    h_eff_data = r.TH1F("lostlep eff mjj ss data", "lostlep eff mjj ss data", 5, 0, 5)
    h_eff_mc = r.TH1F("lostlep eff mjj ss mc", "lostlep eff mjj ss mc", 5, 0, 5)

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

    h_eff_data.GetXaxis().SetBinLabel(5, "raw pass ($n$)")
    h_eff_data.SetBinContent(5, hists_ss_after["data"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_eff_mc.SetBinContent(2, hists_ss_after["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_eff_mc.SetBinContent(3, hists_ss_before["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_eff_mc.SetBinContent(4, hists_ss_before_raw["lostlep"].Integral())

    h_eff_mc.GetXaxis().SetBinLabel(5, "raw pass ($n$)")
    h_eff_mc.SetBinContent(5, hists_ss_after_raw["lostlep"].Integral())

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

    out_raw_lostlep = hists_ss_before_raw["lostlep"][1] - hists_ss_after_raw["lostlep"][1]

    ineff_data = out_data / total_data;
    ineff_err_data = math.sqrt(ineff_data * (1 - ineff_data) / hists_ss_before["data"].Integral())
    ineff_mc = out_lostlep / total_lostlep;
    ineff_err_mc = math.sqrt(ineff_mc * (1 - ineff_mc) / hists_ss_before_raw["lostlep"].Integral())

    # Create histograms with the calculation results so that it can be plotted/made into a table
    h_ineff_data = r.TH1F("lostlep ineff mjj ss data", "lostlep ineff mjj ss data", 5, 0, 5)
    h_ineff_mc = r.TH1F("lostlep ineff mjj ss mc", "lostlep ineff mjj ss mc", 5, 0, 5)

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

    h_ineff_data.GetXaxis().SetBinLabel(5, "raw ($n$)")
    h_ineff_data.SetBinContent(5, out_data)

    h_ineff_mc.GetXaxis().SetBinLabel(2, "after ($a$)")
    h_ineff_mc.SetBinContent(2, out_lostlep)

    h_ineff_mc.GetXaxis().SetBinLabel(3, "before ($b$)")
    h_ineff_mc.SetBinContent(3, total_lostlep)

    h_ineff_mc.GetXaxis().SetBinLabel(4, "raw ($n$)")
    h_ineff_mc.SetBinContent(4, hists_ss_before_raw["lostlep"].GetBinContent(1))

    h_ineff_mc.GetXaxis().SetBinLabel(5, "raw ($n$)")
    h_ineff_mc.SetBinContent(5, out_raw_lostlep)

    # Write them out to a table/plot
    alloptions= { "output_name": "plots/{}/{}/lostlep_ineff_mjj_ss.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3" if is2017 else "35.9", "yield_prec": 3}
    alloptions["yield_table_caption"] = "Some numbers for same-sign channel $m_{jj}$ inefficiency measurement. Equation is that $\\textrm{ineff} = b / a$ and $\\textrm{ineff}_\\textrm{err} = \\sqrt(\\textrm{ineff} (1 - \\textrm{ineff}) / n)$"
    p.plot_hist(bgs=[h_ineff_mc], data=h_ineff_data, colors=colors, options=alloptions)

#________________________________________________________________________________________________________________________________________
def check_stats():

    histnames = "SR"

    # If provided histnames are just a string indicating a region, then get the list of cutflow table histograms, and plot the yields.
    if isinstance(histnames, str):
        # Regions to plot
        histnames = get_histnames(output_dirpath + "/signal.root", histnames)
        histnames.sort(key=region_index) # Sort pretty

    # Now obtain the list of histograms
    hists = get_hists(histnames)

    # Set the option for plotting
    alloptions= {
                "output_name": "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, "mc_smwww_check"),
                "print_yield": True,
                "yield_prec": 3,
                "legend_datalabel": "Official SM WWW",
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                }

    # Now actually plot the histogram
    p.plot_hist(
            bgs  = [hists["smwww"].Clone("SM WWW")],
            data = hists["smwwwofficial"],
            colors = colors,
            options=alloptions)

    # Set the option for plotting
    alloptions= {
                "output_name": "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, "mc_whwww_check"),
                "print_yield": True,
                "yield_prec": 3,
                "legend_datalabel": "Official WH#rightarrowWWW",
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                }

    # Now actually plot the histogram
    p.plot_hist(
            bgs  = [hists["whwww"].Clone("WH#rightarrowWWW")],
            data = hists["whwwwofficial"],
            colors = colors,
            options=alloptions)

    # Set the option for plotting
    alloptions= {
                "output_name": "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, "mc_www_check"),
                "print_yield": True,
                "yield_prec": 3,
                "legend_datalabel": "Official Signal",
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                }

    total = hists["whwwwofficial"].Clone("total")
    total.Add(hists["smwwwofficial"])

    # Now actually plot the histogram
    p.plot_hist(
            bgs  = [hists["whwww"].Clone("WH#rightarrowWWW") + hists["smwww"].Clone("SM WWW")],
            data = total,
            colors = colors,
            options=alloptions)

#________________________________________________________________________________________________________________________________________
def optimize_leptons():

    # Apply some mockup simpls systematics to all processes
    systs_map = {"photon":0.5, "qflip":0.5, "lostlep":0.2, "prompt":0.2, "fakes":0.5, "sig":0, "vbsww":0.2, "ttw":0.2}

    plot(["LRSSmmNb0__lep_relIso03EAv2LepMaxSS", ], "ssmm_lr_lepisomaxss_allsyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)
    plot(["LRSSemNb0__el_relIso03EAv2Lep", ], "ssem_lr_eliso_allsyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)

    plot(["LRSSmmFull__lep_relIso03EAv2LepMaxSS", ], "ssmm_lrfull_lepisomaxss_allsyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)
    plot(["LRSSemFull__el_relIso03EAv2Lep", ], "ssem_lrfull_eliso_allsyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)

    # Apply mockup systematics to fake only
    systs_map = {"photon":0., "qflip":0., "lostlep":0., "prompt":0., "fakes":0.5, "sig":0, "vbsww":0., "ttw":0.}

    plot(["LRSSmmNb0__lep_relIso03EAv2LepMaxSS", ], "ssmm_lr_lepisomaxss_fakeonlysyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)
    plot(["LRSSemNb0__el_relIso03EAv2Lep", ], "ssem_lr_eliso_fakeonlysyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)

    plot(["LRSSmmFull__lep_relIso03EAv2LepMaxSS", ], "ssmm_lrfull_lepisomaxss_fakeonlysyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)
    plot(["LRSSemFull__el_relIso03EAv2Lep", ], "ssem_lrfull_eliso_fakeonlysyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)

    # Apply no systematics
    systs_map = {"photon":0., "qflip":0., "lostlep":0., "prompt":0., "fakes":0., "sig":0, "vbsww":0., "ttw":0.}

    plot(["LRSSmmNb0__lep_relIso03EAv2LepMaxSS", ], "ssmm_lr_lepisomaxss_nosyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)
    plot(["LRSSemNb0__el_relIso03EAv2Lep", ], "ssem_lr_eliso_nosyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)

    plot(["LRSSmmFull__lep_relIso03EAv2LepMaxSS", ], "ssmm_lrfull_lepisomaxss_nosyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)
    plot(["LRSSemFull__el_relIso03EAv2Lep", ], "ssem_lrfull_eliso_nosyst", False, nbin=180, blind=True, docutscan=True, extraoptions={"yaxis_range":[-1,2]}, blowupfakes=2, lepscansystsmap=systs_map)

    # ROC
    plot(["LRSSmmNb0__lep_relIso03EAv2LepMaxSS", ], "ssmm_lr_lepisomaxss", False, nbin=180, doroc=True, extraoptions={"yaxis_range":[0,1]})
    plot(["LRSSemNb0__el_relIso03EAv2Lep", ], "ssem_lr_eliso", False, nbin=180, doroc=True, extraoptions={"yaxis_range":[0,1]})

    plot(["LRSSmmFull__lep_relIso03EAv2LepMaxSS", ], "ssmm_lrfull_lepisomaxss", False, nbin=180, doroc=True, extraoptions={"yaxis_range":[0,1]})
    plot(["LRSSemFull__el_relIso03EAv2Lep", ], "ssem_lrfull_eliso", False, nbin=180, doroc=True, extraoptions={"yaxis_range":[0,1]})

    plot(["LRSSmmNb0__lep_relIso03EAv2LepMaxSS", ], "ssmm_lr_lepisomaxss", False, nbin=40, blind=True, extraoptions={"no_overflow":True}, blowupfakes=2)
    plot(["LRSSemNb0__el_relIso03EAv2Lep", ], "ssem_lr_eliso", False, nbin=40, blind=True, extraoptions={"no_overflow":True}, blowupfakes=2)

    plot(["LRSSmmFull__lep_relIso03EAv2LepMaxSS", ], "ssmm_lrfull_lepisomaxss", False, nbin=40, blind=True, extraoptions={"no_overflow":True}, blowupfakes=2)
    plot(["LRSSemFull__el_relIso03EAv2Lep", ], "ssem_lrfull_eliso", False, nbin=40, blind=True, extraoptions={"no_overflow":True}, blowupfakes=2)

    plot("SR", "sr_mc_yield_fake2x", False, caption="Signal region yields with each process-except fakes-set to its background estimation method's prediction.", blowupfakes=2)

#________________________________________________________________________________________________________________________________________
def fake_est_plots():

    plot(["SRSSmmNj2__lep_pt1", "SRSSemNj2__lep_pt1", "SRSSeeNj2__lep_pt1"], "pr_ss_lep_pt1", False, caption="preselection region sub-leading lepton Pt", nbin=20)
    plot(["SRSSmmNj2__lep_pt1", "SRSSemNj2__lep_pt1", "SRSSeeNj2__lep_pt1"], "pr_ss_lep_pt1_ddfakes", True, caption="preselection region sub-leading lepton Pt", nbin=20)

    plot(["SRSSmmNb0__lep_pt1", "SRSSemNb0__lep_pt1", "SRSSeeNb0__lep_pt1"], "prnb0_ss_lep_pt1", False, caption="preselection region sub-leading lepton Pt", nbin=20)
    plot(["SRSSmmNb0__lep_pt1", "SRSSemNb0__lep_pt1", "SRSSeeNb0__lep_pt1"], "prnb0_ss_lep_pt1_ddfakes", True, caption="preselection region sub-leading lepton Pt", nbin=20)

    plot([
        "ARSSeeFull", 
        "ARSSemFull",
        "ARSSmmFull",
        "ARSSSideeeFull",
        "ARSSSideemFull",
        "ARSSSidemmFull",
        "AR0SFOSFull",
        "AR1SFOSFull",
        "AR2SFOSFull",
        ], "ar_yields", False, caption="application region yields")

    plot([
        "BTCRSSeeFull", 
        "BTCRSSemFull",
        "BTCRSSmmFull",
        "BTCRSSSideeeFull",
        "BTCRSSSideemFull",
        "BTCRSSSidemmFull",
        "BTCR0SFOSFull",
        "BTCR1SFOSFull",
        "BTCR2SFOSFull",
        ], "btcr_yields", False, caption="b-tagged control region yields")

    plot([
        "BTCRSSeeFull", 
        "BTCRSSemFull",
        "BTCRSSmmFull",
        "BTCRSSSideeeFull",
        "BTCRSSSideemFull",
        "BTCRSSSidemmFull",
        "BTCR0SFOSFull",
        "BTCR1SFOSFull",
        "BTCR2SFOSFull",
        ], "btcr_yields_ddfakes", True, caption="b-tagged control region yields")

    plot([
        "LXECRSSeeFull", 
        "LXECRSSemFull",
        "LXECRSSmmFull",
        ], "lxecr_yields", False, caption="b-tagged control region yields")

    plot([
        "LXECRSSeeFull", 
        "LXECRSSemFull",
        "LXECRSSmmFull",
        ], "lxecr_yields_ddfakes", True, caption="b-tagged control region yields")

    plot([
        "LXEARCRSSeeFull", 
        "LXEARCRSSemFull",
        "LXEARCRSSmmFull",
        ], "lxear_yields", False, caption="b-tagged control region yields")

#________________________________________________________________________________________________________________________________________
def study_jer_syst():

    global bkg_order
    bkg_order = ["www", "photon", "qflip", "prompt", "ttw", "vbsww", "lostlep"]

    # Get the main yield
    lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors
    hists = get_yield_hists("WZCR", True, lostlep_sf, "JER")
    hists_jerup = get_yield_hists("WZCR", True, lostlep_sf, "JERUp")
    hists_jerdn = get_yield_hists("WZCR", True, lostlep_sf, "JERDown")
    hists_nom = get_yield_hists("WZCR", True, lostlep_sf) # JES nominal
    hists_jesup = get_yield_hists("WZCR", True, lostlep_sf, "JESUp") # JES up
    hists_jesdn = get_yield_hists("WZCR", True, lostlep_sf, "JESDown") # JES down

    # aggregate a list of backgrounds from the "hists"
    bgs = [ hists[x] for x in bkg_order ]

    for x in bkg_order:

        # Set the option for plotting
        alloptions= {
                    "ratio_range":[0.0,2.2],
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "lumi_value": "41.3" if is2017 else "35.9",
                    "yaxis_range": [0., 2.7],
                    #"yaxis_log": True,
                    }

        alloptions["output_name"] = "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, x + "_jer_study")
        print alloptions["output_name"]

        varup = hists_jerup[x].Clone()
        vardn = hists_jerdn[x].Clone()
        varup.Divide(hists[x])
        vardn.Divide(hists[x])
        nom = hists[x].Clone()
        nom.Divide(nom)

        # p.plot_hist(
        #         sigs = [hists_jerup[x], hists_jerdn[x]],
        #         bgs  = [hists[x]],
        #         data = None,
        #         colors = [2001],
        #         options=alloptions)

        p.plot_hist(
                sigs = [varup, vardn],
                bgs  = [nom],
                data = None,
                colors = [2001],
                options=alloptions)

        # Set the option for plotting
        alloptions= {
                    "ratio_range":[0.0,2.2],
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "lumi_value": "41.3" if is2017 else "35.9",
                    "yaxis_range": [0., 2.7],
                    #"yaxis_log": True,
                    }

        alloptions["output_name"] = "plots/{}/{}/{}.pdf".format(input_ntuple, analysis_tag, x + "_jes_study")
        print alloptions["output_name"]

        varup = hists_jesup[x].Clone()
        vardn = hists_jesdn[x].Clone()
        varup.Divide(hists_nom[x])
        vardn.Divide(hists_nom[x])
        nom = hists_nom[x].Clone()
        nom.Divide(nom)

        # p.plot_hist(
        #         sigs = [hists_jerup[x], hists_jerdn[x]],
        #         bgs  = [hists[x]],
        #         data = None,
        #         colors = [2001],
        #         options=alloptions)

        p.plot_hist(
                sigs = [varup, vardn],
                bgs  = [nom],
                data = None,
                colors = [2001],
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
    alloptions= { "output_name": "plots/{}/{}/lostlep_exp_tf.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 3, "yield_table_caption": "Lost lepton transfer factor systematic variations."}
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
    alloptions= { "output_name": "plots/{}/{}/lostlep_exp_syst.pdf".format(input_ntuple, analysis_tag), "bkg_sort_method" : "unsorted", "print_yield": True, "lumi_value": "41.3", "yield_prec": 3, "yield_table_caption": "Lost lepton transfer factor systematic variations."}
    #p.plot_hist(sigs=hists, bgs=[h_nom_tf], options=alloptions)
    p.plot_hist(sigs=systs_symmetrized, bgs=[h_nom_tf], options=alloptions)


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
def get_hists(histnames, use_data_driven_fakes=False, docutflow=False, sfs={}, dorawcutflow=False, do_ewksubtraction=True):

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

    smwww_list = glob.glob(output_dirpath+"/smwww.root")
    whwww_list = glob.glob(output_dirpath+"/whwww.root")
    smwwwofficial_list = glob.glob(output_dirpath+"/smwwwofficial.root")
    whwwwofficial_list = glob.glob(output_dirpath+"/whwwwofficial.root")
    if len(smwwwofficial_list) == 0:
        smwwwofficial_list = glob.glob(output_dirpath+"/smwww.root")
    if len(whwwwofficial_list) == 0:
        whwwwofficial_list = glob.glob(output_dirpath+"/whwww.root")

    do_retrieve_data_event_based_histograms = ("Up" not in histnames[0] and "Down" not in histnames[0]) or ("Fake" in histnames[0])

    hists = {}
    if "__" in histnames[0] or docutflow:
        hists["lostlep"] = ru.get_summed_histogram(bkg_lists["lostlep"] , histnames , sfs=sfs)
        hists["photon"]  = ru.get_summed_histogram(bkg_lists["photon"]  , histnames , sfs=sfs)
        hists["qflip"]   = ru.get_summed_histogram(bkg_lists["qflip"]   , histnames , sfs=sfs)
        # hists["ewksubt"] = ru.get_summed_histogram(bkg_lists["ewksubt"] , histnames , sfs=sfs)
        hists["prompt"]  = ru.get_summed_histogram(bkg_lists["prompt"]  , histnames , sfs=sfs)
        hists["vbsww"]   = ru.get_summed_histogram(bkg_lists["vbsww"]   , histnames , sfs=sfs)
        hists["ttw"]     = ru.get_summed_histogram(bkg_lists["ttw"]     , histnames , sfs=sfs)
        hists["www"]     = ru.get_summed_histogram(sig_list             , histnames , sfs=sfs)
        # Only access data root file when accessing nominal variation
        if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
            hists["fakes"]   = ru.get_summed_histogram(bkg_lists["fakes"]   , histnames , sfs=sfs)
        if do_retrieve_data_event_based_histograms:
            hists["data"]    = ru.get_summed_histogram(data_list            , histnames , sfs=sfs)
        hists["smwww"]   = ru.get_summed_histogram(smwww_list           , histnames , sfs=sfs)
        hists["whwww"]   = ru.get_summed_histogram(whwww_list           , histnames , sfs=sfs)
        hists["smwwwofficial"]   = ru.get_summed_histogram(smwwwofficial_list           , histnames , sfs=sfs)
        hists["whwwwofficial"]   = ru.get_summed_histogram(whwwwofficial_list           , histnames , sfs=sfs)
    else:
        labels = ru.remove_all_common_longest_common_substring(histnames)
        labels = [ l.replace("FO","SFOS") for l in labels ]
        labels = [ l.replace("ide","side-") for l in labels ]
        hists["lostlep"] = ru.get_yield_histogram(bkg_lists["lostlep"] , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["photon"]  = ru.get_yield_histogram(bkg_lists["photon"]  , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["qflip"]   = ru.get_yield_histogram(bkg_lists["qflip"]   , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        # hists["ewksubt"] = ru.get_yield_histogram(bkg_lists["ewksubt"] , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["prompt"]  = ru.get_yield_histogram(bkg_lists["prompt"]  , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["vbsww"]   = ru.get_yield_histogram(bkg_lists["vbsww"]   , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["ttw"]     = ru.get_yield_histogram(bkg_lists["ttw"]     , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["www"]     = ru.get_yield_histogram(sig_list             , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        # Only access data root file when accessing nominal variation
        if do_retrieve_data_event_based_histograms or not use_data_driven_fakes:
            hists["fakes"]   = ru.get_yield_histogram(bkg_lists["fakes"]   , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        if do_retrieve_data_event_based_histograms:
            hists["data"]    = ru.get_yield_histogram(data_list            , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["smwww"]   = ru.get_yield_histogram(smwww_list           , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["whwww"]   = ru.get_yield_histogram(whwww_list           , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["smwwwofficial"]   = ru.get_yield_histogram(smwwwofficial_list           , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))
        hists["whwwwofficial"]   = ru.get_yield_histogram(whwwwofficial_list           , histnames , labels=labels, sfs=sfs, hsuffix=("_cutflow" if not dorawcutflow else "_rawcutflow"))

    if use_data_driven_fakes:
        if do_retrieve_data_event_based_histograms:
            for i in xrange(1, hists["ewksubt"].GetNbinsX()+1):
                if hists["ewksubt"].GetBinContent(i) > 0:
                    hists["ewksubt"].SetBinContent(i, 0)
            if do_ewksubtraction:
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
    hists["smwww"]   .SetName("smwww")
    hists["whwww"]   .SetName("whwww")
    hists["smwwwofficial"]   .SetName("smwwwofficial")
    hists["whwwwofficial"]   .SetName("whwwwofficial")

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
    #    p.remove_overflow(hists[h])

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

    make_test_plots()
    #make_2016_v122_plots()
    # make_2017_plots()

