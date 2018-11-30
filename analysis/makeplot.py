#!/bin/env python

# Get WZ uncertainties
# Get VBS/Gamma VR uncertainties
# Get Fake uncertainties
# Create data card

from rooutil import rooutil as ru
from rooutil import plottery_wrapper as p
import glob
import ROOT as r

output_dirpath = "outputs/condor/WWW2017_v4.0.5/test1"
is2017 = "WWW2017" in output_dirpath

def main():
    write_datacard()
#    get_wzsf()
#    plot()
#    study_wz()
#    oscr()

def write_datacard():

    # Get the main yield
    wzsf = get_wzsf()
    hists = get_yield_hists("SR", True, wzsf)

    # Get the WZ CR statistical uncertainties
    systs={
            "lostlep": {
                "CRstat_ee"    : ru.frac_syst_hists(hists["lostlep"],[wzsf["lostlep"]["SSee"][1]/wzsf["lostlep"]["SSee"][0],0,0,wzsf["lostlep"]["SSee"][1]/wzsf["lostlep"]["SSee"][0],0,0,0,0,0]),
                "CRstat_em"    : ru.frac_syst_hists(hists["lostlep"],[0,wzsf["lostlep"]["SSem"][1]/wzsf["lostlep"]["SSem"][0],0,0,wzsf["lostlep"]["SSem"][1]/wzsf["lostlep"]["SSem"][0],0,0,0,0]),
                "CRstat_mm"    : ru.frac_syst_hists(hists["lostlep"],[0,0,wzsf["lostlep"]["SSmm"][1]/wzsf["lostlep"]["SSmm"][0],0,0,wzsf["lostlep"]["SSmm"][1]/wzsf["lostlep"]["SSmm"][0],0,0,0]),
                "CRstat_1sfos" : ru.frac_syst_hists(hists["lostlep"],[0,0,0,0,0,0,0,wzsf["lostlep"]["1SFOS"][1]/wzsf["lostlep"]["1SFOS"][0],0]),
                "CRstat_2sfos" : ru.frac_syst_hists(hists["lostlep"],[0,0,0,0,0,0,0,0,wzsf["lostlep"]["2SFOS"][1]/wzsf["lostlep"]["2SFOS"][0]]),
                }
            }

    # putting together the background histograms
    bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
    bgs = [ hists[x] for x in bkg_order ]

    # Write to the datacard
    ru.write_shape_fit_datacard(sig=hists["sig"], bgs=bgs, data=None, datacard_filename="datacard.txt", systs=systs)

def get_wzsf():
    hists = get_yield_hists("WZCR", False)
    bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
    bgs = [ hists[x] for x in bkg_order ]
    sf = ru.get_sf(hists["lostlep"], hists["data"], [hists["photon"], hists["qflip"], hists["fakes"], hists["prompt"]])
    sfs = {"lostlep": {
            "SSee"    : [sf.GetBinContent(1),sf.GetBinError(1)],
            "SSem"    : [sf.GetBinContent(2),sf.GetBinError(2)],
            "SSmm"    : [sf.GetBinContent(3),sf.GetBinError(3)],
            "SSSideee": [sf.GetBinContent(1),sf.GetBinError(1)],
            "SSSideem": [sf.GetBinContent(2),sf.GetBinError(2)],
            "SSSidemm": [sf.GetBinContent(3),sf.GetBinError(3)],
            "1SFOS"   : [sf.GetBinContent(4),sf.GetBinError(4)],
            "2SFOS"   : [sf.GetBinContent(5),sf.GetBinError(5)],
            }
            }
    return sfs

def plot():

    # Regions to plot
    region = "WZCR"
    use_data_driven_fakes = False

    # Bkg stack order
    bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
    color_map = { "photon":920, "qflip":2007, "fakes":2005, "lostlep":2003, "prompt":2001, "www":2 }

    histnames = get_histnames(output_dirpath + "/signal.root", region)
    histnames.sort(key=region_index)

    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=get_wzsf())
    #hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0])

    colors = [ 920, 2007, 2005, 2003, 2001, 2 ]

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
            sigs = [hists["sig"]],
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
    #histnames = ["WZCRSSmm__MllSS"]

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

    colors = [ 920, 2007, 2005, 2003, 2001, 2 ]

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

def get_histnames(fpath, region):

    f = r.TFile(fpath)

    rtn = []

    for key in f.GetListOfKeys():
        if region in str(key.GetName()) and "Full_cutflow" in str(key.GetName()):
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
    bkg_lists["lostlep"] = [ x for x in glob.glob(output_dirpath+"/lostlep.root") ]
    bkg_lists["photon"]  = [ x for x in glob.glob(output_dirpath+"/photon.root")  ]
    bkg_lists["qflip"]   = [ x for x in glob.glob(output_dirpath+"/qflip.root")   ]
    bkg_lists["ddfakes"] = [ x for x in glob.glob(output_dirpath+"/ddfakes.root") ]
    bkg_lists["ewksubt"] = [ x for x in glob.glob(output_dirpath+"/ewksubt.root") ]
    bkg_lists["mcfakes"] = [ x for x in glob.glob(output_dirpath+"/fakes.root")   ]
    bkg_lists["prompt"]  = [ x for x in glob.glob(output_dirpath+"/prompt.root")  ]
    bkg_lists["fakes"] = bkg_lists["ddfakes"] if use_data_driven_fakes else bkg_lists["mcfakes"]

    sig_list  = glob.glob(output_dirpath+"/*t_www_*/*.root")
    vh_list   = glob.glob(output_dirpath+"/*VH*t_www_*/*.root")
    www_list  = glob.glob(output_dirpath+"/*WWW*t_www_*/*.root")
    data_list = glob.glob(output_dirpath+"/*Run2017*_t_ss*/*.root")
    sig_list  = glob.glob(output_dirpath+"/signal.root")
    data_list = glob.glob(output_dirpath+"/data.root")

    hists = {}
    if "__" in histnames[0] or docutflow:
        hists["lostlep"] = ru.get_summed_histogram(bkg_lists["lostlep"] , histnames , sfs=sfs)
        hists["photon"]  = ru.get_summed_histogram(bkg_lists["photon"]  , histnames , sfs=sfs)
        hists["qflip"]   = ru.get_summed_histogram(bkg_lists["qflip"]   , histnames , sfs=sfs)
        hists["fakes"]   = ru.get_summed_histogram(bkg_lists["fakes"]   , histnames , sfs=sfs)
        hists["ewksubt"] = ru.get_summed_histogram(bkg_lists["ewksubt"] , histnames , sfs=sfs)
        hists["prompt"]  = ru.get_summed_histogram(bkg_lists["prompt"]  , histnames , sfs=sfs)
        hists["sig"]     = ru.get_summed_histogram(sig_list             , histnames , sfs=sfs)
        hists["data"]    = ru.get_summed_histogram(data_list            , histnames , sfs=sfs)
    else:
        hists["lostlep"] = ru.get_yield_histogram(bkg_lists["lostlep"] , histnames , sfs=sfs)
        hists["photon"]  = ru.get_yield_histogram(bkg_lists["photon"]  , histnames , sfs=sfs)
        hists["qflip"]   = ru.get_yield_histogram(bkg_lists["qflip"]   , histnames , sfs=sfs)
        hists["fakes"]   = ru.get_yield_histogram(bkg_lists["fakes"]   , histnames , sfs=sfs)
        hists["ewksubt"] = ru.get_yield_histogram(bkg_lists["ewksubt"] , histnames , sfs=sfs)
        hists["prompt"]  = ru.get_yield_histogram(bkg_lists["prompt"]  , histnames , sfs=sfs)
        hists["sig"]     = ru.get_yield_histogram(sig_list             , histnames , sfs=sfs)
        hists["data"]    = ru.get_yield_histogram(data_list            , histnames , sfs=sfs)

    if bkg_lists["fakes"] == bkg_lists["ddfakes"]:
        for i in xrange(1, hists["ewksubt"].GetNbinsX()+1):
            if hists["ewksubt"].GetBinContent(i) > 0:
                hists["ewksubt"].SetBinContent(i, 0)
        hists["fakes"].Add(hists["ewksubt"])

    hists["lostlep"] .SetName("Lost/three lep")
    hists["photon"]  .SetName("#gamma#rightarrowlepton")
    hists["qflip"]   .SetName("Charge mis-id")
    hists["fakes"]   .SetName("Non-prompt")
    hists["prompt"]  .SetName("Irredu.")
    hists["sig"]     .SetName("WWW")
    hists["data"]    .SetName("Data")

    hists["lostlep"] .SetTitle("lostlep")
    hists["photon"]  .SetTitle("photon")
    hists["qflip"]   .SetTitle("qflip")
    hists["fakes"]   .SetTitle("fakes")
    hists["prompt"]  .SetTitle("prompt")
    hists["sig"]     .SetTitle("www")
    hists["data"]    .SetTitle("data")

    return hists

def get_yield_hists(region, use_data_driven_fakes, sfs={}):
    bkg_order = ["photon", "qflip", "fakes", "lostlep", "prompt"]
    histnames = get_histnames(output_dirpath + "/signal.root", region)
    histnames.sort(key=region_index)
    hists = get_hists(histnames, use_data_driven_fakes, "_cutflow" in histnames[0], sfs=sfs)
    return hists

if __name__ == "__main__":
    main()

