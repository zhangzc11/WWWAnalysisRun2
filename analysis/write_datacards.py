#!/bin/env python

from rooutil import pyrootutil as ru
from rooutil import datacard_writer as dw
import glob
import ROOT as r
import os

# option parser
import argparse

parser = argparse.ArgumentParser(description="Higgs Combine Datacard dumper for Run 2 WWW Analysis")
parser.add_argument('-i' , '--input_dir' , dest='input_dir' , help='input dir path (where hists are) NOTE: pattern MUST be hists/${BABY_VERSION}/${TAG}/', required=True ) 
args = parser.parse_args()

# Global variables
config = {

        # Order of backgrounds to be written out to the data cards
        "bkg_order": ["fakes", "photon", "lostlep", "qflip", "prompt", "ttw", "vbsww"],

        # The input dirpath which is the output of the looper
        "input_dirpath": args.input_dir,

        # Signal sample root name
        "signal_filename" : "signal_private.root"

    }

#________________________________________________________________________________________________________________________________________
# Parse baby version, job tag...
def parse_output_dir():

    # path to where the histogram files are sitting at
    input_dir = config["input_dirpath"]

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

    # Parse the input_dirpath to get the baby version and job tag
    # then create plot output with a directory structure like plots/BABYTAG/JOBTAG/
    output_dir = "datacards/" + babytag + "/" + jobtag

    config["output_dir"] = output_dir

#________________________________________________________________________________________________________________________________________
# Writing statistics datacards
def write_datacard():

    lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors

    hists = get_yield_hists("SR", True, lostlep_sf) # Get the main yields with lost lepton scale factors applied

    systs = get_systs() # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in config["bkg_order"] ]

    # Write to the datacard
    # d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])

    # Create output directory
    os.system("mkdir -p {}".format(config["output_dir"]))

    # Region names
    reg_names = [ "b{}".format(index) for index in xrange(1, 10) ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("{}/datacard_{}.txt".format(config["output_dir"], reg_name))

    print "Wrote datacards to {}".format(config["output_dir"])

#________________________________________________________________________________________________________________________________________
# Writing statistics datacards
def write_datacard_nj1():

    hists = get_yield_hists("EXSS", True) # Get the main yields with lost lepton scale factors applied

    # lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors

    # hists = get_yield_hists("SR", True, lostlep_sf) # Get the main yields with lost lepton scale factors applied

    systs = get_systs("EXSS", apply_lostlep_sf=False, include_lostlep=True, isnj1=True) # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in config["bkg_order"] ]

    # Write to the datacard
    # d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs)#, no_stat_procs=["lostlep"])

    # Create output directory
    os.system("mkdir -p {}".format(config["output_dir"]))

    # Region names
    reg_names = [ "n{}".format(index) for index in xrange(1, 5) ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("{}/datacard_{}.txt".format(config["output_dir"], reg_name))

    print "Wrote datacards to {}".format(config["output_dir"])

#________________________________________________________________________________________________________________________________________
# Writing statistics datacards
def write_datacard_btag():

    hists = get_yield_hists("CRBTag", True) # Get the main yields with lost lepton scale factors applied

    # lostlep_sf = get_lostlep_sf() # Get the lost lepton scale factors

    # hists = get_yield_hists("SR", True, lostlep_sf) # Get the main yields with lost lepton scale factors applied

    systs = get_systs("CRBTag", apply_lostlep_sf=False, include_lostlep=True, isnj1=True) # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in config["bkg_order"] ]

    # Write to the datacard
    # d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs, no_stat_procs=["lostlep"])
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs)#, no_stat_procs=["lostlep"])

    # Create output directory
    os.system("mkdir -p {}".format(config["output_dir"]))

    # Region names
    reg_names = [ "t{}".format(index) for index in xrange(1, 7) ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("{}/datacard_{}.txt".format(config["output_dir"], reg_name))

    print "Wrote datacards to {}".format(config["output_dir"])

#________________________________________________________________________________________________________________________________________
# Writing statistics datacards
def write_datacard_w_control_regions():

    #
    # Signal region
    #

    hists = get_yield_hists("SR", True) # Get the main yields without lost lepton scale factors applied
    systs = get_systs(apply_lostlep_sf=False, include_lostlep=True) # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in config["bkg_order"] ]

    # Write to the datacard
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs)

    # Region names
    reg_names = [ "s{}".format(index) for index in xrange(1, 10) ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("{}/datacard_{}.txt".format(config["output_dir"], reg_name))

    #
    # Lost Lep Control region
    #

    hists = get_yield_hists("WZCR", True) # Get the main yields without lost lepton scale factors applied in control region
    systs = get_systs("WZCR", apply_lostlep_sf=False, include_lostlep=True) # Get all systematic histograms

    # putting together the background histograms
    bgs = [ hists[x] for x in config["bkg_order"] ]

    # Write to the datacard
    d = dw.DataCardWriter(sig=hists["www"], bgs=bgs, data=hists["data"], datacard_filename="datacard.txt", systs=systs)

    # Region names
    reg_names = [ "c{}".format(index) for index in xrange(1, 10) ]

    # Write the datacards for each regions
    for i, reg_name in enumerate(reg_names):
        d.set_bin(i+1) # TH1 bin indices start with 1
        d.set_region_name(reg_name)
        d.write("{}/datacard_{}.txt".format(config["output_dir"], reg_name))

    print "Wrote datacards to {}".format(config["output_dir"])

#________________________________________________________________________________________________________________________________________
# Get the lost lepton scale factors to be applied
# The calculation is SF = data - (non-lost-lep) / lost-lep-MC. And this is done in CR.
# Then this SF will be applied to the lost-lep-MC in SR
# The final output will be a dict of {"(region-name)" : [ SF, SFerr], ... }
def get_lostlep_sf():

    # Retrieve the yield histograms (i.e. yields per SR/CR bins)
    hists = get_yield_hists("WZCR", False)
    
    bgs = [ hists[x] for x in config["bkg_order"] ]

    sf = ru.get_sf(
            h_proc=hists["lostlep"], # The process to measure scale factors of
            h_data=hists["data"], # The data yields
            h_sub=[hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"], hists["ttw"], hists["vbsww"]] # rest of the process that needs to be subtracted
            )

    # This kind of map format is used to later apply scalefactors to the histograms under the hood via rooutil/rooutil.py utility script
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
# Interface to read the histograms from output path
def get_yield_hists(region, use_data_driven_fakes, sfs={}, syst=""):

    # get all the histogram names in the file matching the region string and syst string
    histnames = get_histnames(config["input_dirpath"] + "/" + config["signal_filename"], region, syst)

    print histnames

    # Sort the histogram names that were retrieved
    histnames.sort(key=region_index)

    # actually obtain the histograms from the histogram files
    hists = get_hists(histnames, use_data_driven_fakes, sfs=sfs)

    # Do some modifications to clean up negative or zero bins in as RooStats goes haywire when dealing with negative probability
    for h in hists:
        hists[h] = ru.remove_negative_or_zero(hists[h])

    # Now when obtaing yield histograms for WZCR, make the 5 bin output into a 9 bin out
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
            tmphist.SetBinError(1, hists[h].GetBinError(1))
            tmphist.SetBinError(2, hists[h].GetBinError(2))
            tmphist.SetBinError(3, hists[h].GetBinError(3))
            tmphist.SetBinError(4, hists[h].GetBinError(1))
            tmphist.SetBinError(5, hists[h].GetBinError(2))
            tmphist.SetBinError(6, hists[h].GetBinError(3))
            tmphist.SetBinError(8, hists[h].GetBinError(4))
            tmphist.SetBinError(9, hists[h].GetBinError(5))
            hists[h] = tmphist

    return hists

#________________________________________________________________________________________________________________________________________
# Get the histogram names that matches the region of interest
# For example, I want the 9 bin SR then, I use "SR" as region and the function will go through all the histogram list in one file and gather all that matches "<pattern>*Full{SYST}__yield".
# As an example, for signal regions (with syst string = "LepSFUp")there will be exactly 9 that are matching:
# SRSSeeFullLepSFUp__yield
# SRSSemFullLepSFUp__yield
# SRSSmmFullLepSFUp__yield
# SRSSSideeeFullLepSFUp__yield
# SRSSSideemFullLepSFUp__yield
# SRSSSidemmFullLepSFUp__yield
# SR0SFOSFullLepSFUp__yield
# SR1SFOSFullLepSFUp__yield
# SR2SFOSFullLepSFUp__yield
def get_histnames(fpath, region, syst=""):
    f = r.TFile(fpath)
    rtn = []
    for key in f.GetListOfKeys():
        if region in str(key.GetName()) and "Full{}__yield".format(syst) in str(key.GetName()):
            name = str(key.GetName())
            name = name.replace("__yield", "")
            rtn.append(name)
    return rtn;

#________________________________________________________________________________________________________________________________________
# i.e. This does most of the leg work and the user will retrieve a nice dictionary of "samples":TH1s.
def get_hists(histnames, use_data_driven_fakes=False, sfs={}, dorawcutflow=False):

    config["input_dirpath"]

    # Form all the strings for the backgrounds, signal, and data
    bkg_lists = {}
    bkg_lists["ddfakes"] = [ x for x in glob.glob(config["input_dirpath"]+"/ddfakes.root") ]
    bkg_lists["mcfakes"] = [ x for x in glob.glob(config["input_dirpath"]+"/fakes.root") ]
    bkg_lists["lostlep"] = [ x for x in glob.glob(config["input_dirpath"]+"/fitlostlep.root") ]
    bkg_lists["photon"]  = [ x for x in glob.glob(config["input_dirpath"]+"/fitphoton.root")  ]
    bkg_lists["qflip"]   = [ x for x in glob.glob(config["input_dirpath"]+"/fitqflip.root")   ]
    bkg_lists["mcfakes"] = [ x for x in glob.glob(config["input_dirpath"]+"/fitfakes.root")   ]
    bkg_lists["prompt"]  = [ x for x in glob.glob(config["input_dirpath"]+"/fitprompt.root")  ]
    bkg_lists["vbsww"]   = [ x for x in glob.glob(config["input_dirpath"]+"/vbs.root")   ]
    bkg_lists["ttw"]     = [ x for x in glob.glob(config["input_dirpath"]+"/ttw.root")     ]
    bkg_lists["fakes"]   = bkg_lists["ddfakes"] if use_data_driven_fakes else bkg_lists["mcfakes"]
    sig_list = [ x for x in glob.glob(config["input_dirpath"]+"/"+config["signal_filename"]) ]
    data_list = [ x for x in glob.glob(config["input_dirpath"]+"/data.root") ]

    # Form the labeling of the histograms
    labels = ru.remove_all_common_longest_common_substring(histnames)
    labels = [ l.replace("FO","SFOS") for l in labels ]
    labels = [ l.replace("ide","side-") for l in labels ]

    # Retrieve all the histograms with the scale factors applied appropriately (sfs is the special format that ru.get_yield_histogram expects)
    hists = {}
    hists["lostlep"] = ru.get_yield_histogram(bkg_lists["lostlep"] , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["photon"]  = ru.get_yield_histogram(bkg_lists["photon"]  , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["qflip"]   = ru.get_yield_histogram(bkg_lists["qflip"]   , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["prompt"]  = ru.get_yield_histogram(bkg_lists["prompt"]  , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["vbsww"]   = ru.get_yield_histogram(bkg_lists["vbsww"]   , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["ttw"]     = ru.get_yield_histogram(bkg_lists["ttw"]     , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["fakes"]   = ru.get_yield_histogram(bkg_lists["fakes"]   , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["www"]     = ru.get_yield_histogram(sig_list             , histnames , labels=labels, sfs=sfs, hsuffix="__yield")
    hists["data"]    = ru.get_yield_histogram(data_list            , histnames , labels=labels, sfs=sfs, hsuffix="__yield")

    # The title of histograms are used as the name of the process for datacards
    hists["lostlep"] .SetTitle("lostlep")
    hists["photon"]  .SetTitle("photon")
    hists["qflip"]   .SetTitle("qflip")
    hists["fakes"]   .SetTitle("fakes")
    hists["prompt"]  .SetTitle("prompt")
    hists["www"]     .SetTitle("www")
    hists["data"]    .SetTitle("data")
    hists["vbsww"]   .SetTitle("vbsww")
    hists["ttw"]     .SetTitle("ttw")

    return hists

#________________________________________________________________________________________________________________________________________
# To sort histograms based on the region. This will be provided to "sort" function later on
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
# Compute the extrapolation factor
# This will be the value that will be put into the datacards.
# Alpha = (data - non-lost-lep) * (lost-lep-SR / lost-lep-CR) / data
def get_lostlep_alpha(syst=""):
    hists_nosyst = get_yield_hists("WZCR", False)
    hists = get_yield_hists("WZCR", False, syst=syst)
    bgs = [ hists[x] for x in config["bkg_order"] ]
    histsSR = get_yield_hists("SR", False, syst=syst)
    alpha = ru.get_alpha(histsSR["lostlep"], hists["lostlep"], hists_nosyst["data"], [hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"], hists["ttw"], hists["vbsww"]])
    return alpha

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
def get_systs(region="SR", apply_lostlep_sf=True, include_lostlep=False, isnj1=False):

    # Get the main yield
    lostlep_sf = get_lostlep_sf() if region == "SR" and apply_lostlep_sf else {}
    hists = get_yield_hists(region, True, lostlep_sf)

    systs = []

    # Usual systematic variations for both signal and backgrounds
    syst_names = ["JES", "LepSF", "TrigSF", "BTagLF", "BTagHF", "Pileup"]
    # if "v1.2.2" not in input_ntuple:
    #     syst_names += ["JER"]
    for sys in syst_names:
        sys_hists_up = get_yield_hists(region, True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists(region, True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + config["bkg_order"]:
            bkglist = ["www", "qflip", "prompt", "photon", "ttw", "vbsww"]
            if include_lostlep:
                bkglist.append("lostlep")
            if proc in bkglist:
                systval[proc] = [sys_hists_up[proc], sys_hists_dn[proc]]
            elif proc == "lostlep":
                lostlep_yield_sysup = get_yield_hists(region, True, lostlep_sf)
                lostlep_yield_sysdn = get_yield_hists(region, True, lostlep_sf)
                lostlep_alpha_nom = get_lostlep_alpha()
                lostlep_alpha_sysup = get_lostlep_alpha(sys+"Up")
                lostlep_alpha_sysdn = get_lostlep_alpha(sys+"Down")
                lostlep_alpha_sysup.Divide(lostlep_alpha_nom)
                lostlep_alpha_sysdn.Divide(lostlep_alpha_nom)
                lostlep_alpha_sysup.SetBinContent(7, lostlep_alpha_sysup.GetBinContent(8))
                lostlep_alpha_sysdn.SetBinContent(7, lostlep_alpha_sysdn.GetBinContent(8))
                lostlep_yield_sysup[proc].Multiply(lostlep_alpha_sysup)
                lostlep_yield_sysdn[proc].Multiply(lostlep_alpha_sysdn)
                systval[proc] = [lostlep_yield_sysup[proc], lostlep_yield_sysdn[proc]] 
            else:
                systval[proc] = 0
        syst_datacard_data = (sys, 'lnN', [], systval)
        systs.append(syst_datacard_data)

    # Fake systematics
    # for sys in ["FakeRateEl", "FakeRateMu", "FakeClosureEl", "FakeClosureMu"]:
    for sys in ["FakeRateSSEl", "FakeRateSSMu", "FakeClosureSSEl", "FakeClosureSSMu", "FakeRate3LEl", "FakeRate3LMu", "FakeClosure3LEl", "FakeClosure3LMu"]:
        sys_hists_up = get_yield_hists(region, True, lostlep_sf, sys+"Up")
        sys_hists_dn = get_yield_hists(region, True, lostlep_sf, sys+"Down")
        systval = {}
        for proc in ["www"] + config["bkg_order"]:
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
        for proc in ["www"] + config["bkg_order"]:
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
            for proc in ["www"] + config["bkg_order"]:
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
            for proc in ["www"] + config["bkg_order"]:
                if proc in ["lostlep"]:
                    systval[proc] = [ "{:.4f}".format(lostlep_alpha.GetBinContent(i)) if i in syst_relevant_bins[sys] else "-" for i in xrange(1, lostlep_alpha.GetNbinsX()+1) ]
                else:
                    systval[proc] = 0
            syst_datacard_data = (sys, 'gmN', [data_yield["data"]], systval)
            systs.append(syst_datacard_data)

    if not isnj1:
        # Lost-Lep extrapolation factor (alpha) error
        systval = {}
        for proc in ["www"] + config["bkg_order"]:
            if proc in ["lostlep"]:
                systval[proc] = ["1.049"] * 6 + ["-"] * 3
            else:
                systval[proc] = 0
        systs.append(("MjjSyst", 'lnN', [], systval))

        # Lost-Lep extrapolation factor (alpha) error
        systval = {}
        for proc in ["www"] + config["bkg_order"]:
            if proc in ["lostlep"]:
                systval[proc] = ["1.053"] * 6 + ["-"] * 3
            else:
                systval[proc] = 0
        systs.append(("MllSSSyst", 'lnN', [], systval))

        # Lost-Lep extrapolation factor (alpha) error
        systval = {}
        for proc in ["www"] + config["bkg_order"]:
            if proc in ["lostlep"]:
                systval[proc] = ["-"] * 6 + ["1.082"] * 3
            else:
                systval[proc] = 0
        systs.append(("Mll3LSyst", 'lnN', [], systval))

    # Flat systematics

    # VBSWWVR
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        if proc in ["vbsww"]:
            systval[proc] = "1.22"
        else:
            systval[proc] = 0
    systs.append(("VBSWWVR", 'lnN', [], systval))

    # VBSWWXsec
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        if proc in ["vbsww"]:
            systval[proc] = "1.20"
        else:
            systval[proc] = 0
    systs.append(("VBSWWXsec", 'lnN', [], systval))

    # ttWXVR
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        if proc in ["ttw"]:
            systval[proc] = "1.18"
        else:
            systval[proc] = 0
    systs.append(("TTWVR", 'lnN', [], systval))

    # ttWXsec
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        if proc in ["ttw"]:
            systval[proc] = "1.20"
        else:
            systval[proc] = 0
    systs.append(("TTWXsec", 'lnN', [], systval))

    # photon validation region
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        if proc in ["photon"]:
            systval[proc] = "1.50"
        else:
            systval[proc] = 0
    systs.append(("GammaVR", 'lnN', [], systval))

    # qflip MC syst
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        if proc in ["qflip"]:
            systval[proc] = "1.50"
        else:
            systval[proc] = 0
    systs.append(("QFlipSyst", 'lnN', [], systval))

    # LumiSyst
    systval = {}
    for proc in ["www"] + config["bkg_order"]:
        bkglist = ["www", "qflip", "prompt", "photon", "ttw", "vbsww"]
        if include_lostlep:
            bkglist.append("lostlep")
        if proc in bkglist:
            systval[proc] = "1.025"
        else:
            systval[proc] = 0
    systs.append(("LumSyst", 'lnN', [], systval))

    return systs

if __name__ == "__main__":

    parse_output_dir()

    write_datacard()
    # write_datacard_nj1()
    write_datacard_btag()
    # write_datacard_w_control_regions()

