#!/bin/env python

from rooutil import datacard_writer as dw
from rooutil import pyrootutil as pr
import ROOT as r
import sys

histpath = sys.argv[1]

# Systematics
# Supported types of input are
#    1. [TH1, TH1] # up and down variation
#    2. TH1
#    3. [float, float] # up and down variation
#    4. float
#    5. str         # direct input
#    6. [str, ... ] # direct input per bin
#    7. None
# All of the yields on these are expected to be the YIELDS AFTER SYST IS APPLIED. (i.e. NOT FRACTIONS)
# You can mix and match
systs = []

# 20% symmetric error on prompt
systs.append( ("promptSyst"  , "lnN" , [] , {"signal":0 , "prompt":"1.2" , "photon":0     , "qflip":0     , "ddfakes":0     , "lostlep":0    }) )
systs.append( ("ddfakesSyst" , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0     , "qflip":0     , "ddfakes":"1.5" , "lostlep":0    }) )
systs.append( ("lostlepSyst" , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0     , "qflip":0     , "ddfakes":0     , "lostlep":"1.2"}) )
systs.append( ("qflipSyst"   , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0     , "qflip":"1.5" , "ddfakes":0     , "lostlep":0    }) )
systs.append( ("photonSyst"  , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":"1.5" , "qflip":0     , "ddfakes":0     , "lostlep":0    }) )

fnames = [
        "{}/photon.root".format(histpath),
        "{}/qflip.root".format(histpath),
        "{}/ddfakes.root".format(histpath),
        "{}/lostlep.root".format(histpath),
        "{}/prompt.root".format(histpath),
        "{}/signal.root".format(histpath),
        ]

hists = []

for fname in fnames:

    hists.append(
            pr.get_yield_histogram(
                list_of_file_names = [fname],
                regions = [
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
                    ],
                labels = [
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
                    ],
                hsuffix = "__yield"
                )
        )

print hists

bkg_hists = hists[:-1]
sig_hists = [hists[-1]]

bkg_hists[0].SetTitle("photon")
bkg_hists[1].SetTitle("qflip")
bkg_hists[2].SetTitle("ddfakes")
bkg_hists[3].SetTitle("lostlep")
bkg_hists[4].SetTitle("prompt")
sig_hists[0].SetTitle("signal")

# Now create data card writer
# bkg2 does not need stat error as it is taken care of by CR stats
d = dw.DataCardWriter(sig=sig_hists[0], bgs=bkg_hists, data=None, systs=systs, no_stat_procs=["ddfakes", "lostlep"])

for i in xrange(1, sig_hists[0].GetNbinsX()+1):
    d.set_bin(i)
    d.set_region_name("bin{}".format(i))
    d.write("datacards_simple/www_{}.txt".format(i))
