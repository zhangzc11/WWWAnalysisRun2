#!/bin/env python

# Plotting script for the fake rate analysis

import sys
import ROOT as r
import pyrootutil as ru
import plottery_wrapper as p
from plottery import utils as u
import glob
import math
from array import array
from pytable import Table
import tabletex
from errors import E

def usage():
    print "Usage:"
    print ""
    print "  python {} input_ntup_tag analysis_tag isSS(=0 or 1) (e.g. FR2018_v5.1.9 test_2019_08_21_0633)"
    print ""
    print ""
    sys.exit()

if len(sys.argv) <= 2:
    usage()

# input_ntup_tag = "FR2018_v5.1.9"
# analysis_tag = "test_2019_08_21_0633"
input_ntup_tag = sys.argv[1]
analysis_tag = sys.argv[2]
isSS = int(sys.argv[3])

output_dirpath = "outputs/{}/{}/{}".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l")
is2016 = "FR2016" in output_dirpath
is2017 = "FR2017" in output_dirpath
is2018 = "FR2018" in output_dirpath
if is2016: lumi = 35.9
if is2017: lumi = 41.3
if is2018: lumi = 59.74

def plot(histnames, ps=0, sf=None, sfqcd=None, output_suffix="", dd_qcd=None):

    # Glob the file lists
    bkg_list_wjets  = [ output_dirpath+"/wj_incl.root" ]
    bkg_list_dy     = [ output_dirpath+"/dy.root" ]
    bkg_list_ttbar  = [ output_dirpath+"/tt_incl.root" ]
    bkg_list_vv     = [ output_dirpath+"/ww.root", output_dirpath+"/wz.root" ]
    bkg_list_qcd_mu = [ output_dirpath+"/qcd_mu.root" ]
    bkg_list_qcd_el = [ output_dirpath+"/qcd_em.root" ]
    bkg_list_qcd_bc = [ output_dirpath+"/qcd_bc.root" ]
    bkg_list_all = bkg_list_wjets + bkg_list_dy + bkg_list_ttbar + bkg_list_vv

    # Glob the data file list depending on the region
    if "Mu" in histnames:
        data_list       = [ output_dirpath+"/data_mu.root" ]
    elif "El" in histnames:
        data_list       = [ output_dirpath+"/data_el.root" ]
    else:
        data_list       = [ output_dirpath+"/data_mu.root", output_dirpath+"/data_el.root" ]

    # Get all the histogram objects
    h_wjets  = ru.get_summed_histogram(bkg_list_wjets , histnames)
    h_dy     = ru.get_summed_histogram(bkg_list_dy    , histnames)
    h_ttbar  = ru.get_summed_histogram(bkg_list_ttbar , histnames)
    h_vv     = ru.get_summed_histogram(bkg_list_vv    , histnames)
    h_qcd_mu = ru.get_summed_histogram(bkg_list_qcd_mu, histnames)
    h_qcd_el = ru.get_summed_histogram(bkg_list_qcd_el, histnames)
    h_qcd_bc = ru.get_summed_histogram(bkg_list_qcd_bc, histnames)
    h_data   = ru.get_summed_histogram(data_list      , histnames)

    # Set the names of the histograms
    h_wjets  .SetName("W")
    h_dy     .SetName("Z")
    h_ttbar  .SetName("Top")
    h_vv     .SetName("VV")
    h_qcd_mu .SetName("QCD(#mu)")
    h_qcd_el .SetName("QCD(e)")
    h_qcd_bc .SetName("QCD(bc)")
    h_data   .SetName("Data")

    # print h_wjets.Integral() + h_dy.Integral() + h_ttbar.Integral() + h_vv.Integral()
    # print h_qcd_el.Integral() + h_qcd_bc.Integral()

    # Scale the histograms appropriately from SF from the EWKCR
    if sf:
        if isinstance(sf, list):
            hists = [h_wjets, h_dy, h_ttbar, h_vv]
            for h in hists:
                for ii, s in enumerate(sf):
                    bc = h.GetBinContent(ii + 1)
                    be = h.GetBinError(ii + 1)
                    h.SetBinContent(ii + 1, bc * s)
                    h.SetBinError(ii + 1, be * s)
        else:
            if sf > 0:
                h_wjets  .Scale(sf)
                h_dy     .Scale(sf)
                h_ttbar  .Scale(sf)
                h_vv     .Scale(sf)
    if sfqcd:
        if isinstance(sfqcd, list):
            hists = [h_qcd_mu, h_qcd_el, h_qcd_bc]
            for h in hists:
                for ii, s in enumerate(sfqcd):
                    bc = h.GetBinContent(ii + 1)
                    be = h.GetBinError(ii + 1)
                    h.SetBinContent(ii + 1, bc * s)
                    h.SetBinError(ii + 1, be * s)
        else:
            if sfqcd > 0:
                h_qcd_mu.Scale(sfqcd)
                h_qcd_el.Scale(sfqcd)
                h_qcd_bc.Scale(sfqcd)


    # If the data needs some additional correction for the prescale
    if ps > 0:
        h_data.Scale(ps)

    # print h_wjets.Integral() + h_dy.Integral() + h_ttbar.Integral() + h_vv.Integral()
    # print h_qcd_el.Integral() + h_qcd_bc.Integral()
    # print h_data.Integral()

    # Color settings
    colors = [ 2007, 2005, 2003, 2001, 920, 921 ]

    # Options
    alloptions= {
                "ratio_range":[0.0,2.0],
                "nbins": 30,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/{}/{}/{}/plot/{}{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", histnames, output_suffix),
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": True,
                "yaxis_log": False if "ptcorr" in histnames else False,
                #"yaxis_log": False,
                #"yaxis_log": False,
                "divide_by_bin_width": True,
                "legend_smart": False if "ptcorr" in histnames else True,
                "lumi_value" : lumi,
                }

    # The bkg histogram list
    h_qcd = h_qcd_mu if "Mu" in histnames else h_qcd_el
    if dd_qcd:
        h_qcd = dd_qcd
    bgs_list = [h_vv , h_ttbar , h_dy , h_wjets, h_qcd ]

    legend_labels = ["VV", "t#bar{t}", "DY", "W", "QCD(#mu)"] if "Mu" in histnames else ["VV", "t#bar{t}", "DY", "W", "QCD(e)", "QCD(HF)"]
    if "Mu" not in histnames:
        bgs_list.append(h_qcd_bc)

    # # For 2018 merge the last two bins in the central
    # if "ptcorretarolledcoarse" in histnames:
    #     def merge_4_5(h):
    #         bc4 = h.GetBinContent(4)
    #         bc5 = h.GetBinContent(5)
    #         be4 = h.GetBinError(4)
    #         be5 = h.GetBinError(5)
    #         nb = E(bc4, be4) + E(bc5, be5)
    #         nbc = nb.val
    #         nbe = nb.err
    #         h.SetBinContent(4, nbc)
    #         h.SetBinError(4, nbe)
    #         h.SetBinContent(5, nbc)
    #         h.SetBinError(5, nbe)
    #     merge_4_5(h_vv)
    #     merge_4_5(h_ttbar)
    #     merge_4_5(h_dy)
    #     merge_4_5(h_wjets)
    #     merge_4_5(h_qcd_mu)
    #     merge_4_5(h_qcd_el)
    #     merge_4_5(h_qcd_bc)
    #     merge_4_5(h_data)

    # Plot them
    p.plot_hist(
            bgs = bgs_list,
            data = h_data.Clone("Data"),
            colors = colors,
            syst = None,
            legend_labels=legend_labels,
            options=alloptions)

    # print h_wjets.Integral() + h_dy.Integral() + h_ttbar.Integral() + h_vv.Integral()
    # print h_qcd_el.Integral() + h_qcd_bc.Integral()
    # print h_data.Integral()

    # Obtain the histogram again to return the object for further calculations

    # Data-driven QCD = data - bkg
    h_ddqcd  = ru.get_summed_histogram(data_list      , histnames)
    h_bkg    = ru.get_summed_histogram(bkg_list_all   , histnames)
    h_wjets  = ru.get_summed_histogram(bkg_list_wjets , histnames)
    h_dy     = ru.get_summed_histogram(bkg_list_dy    , histnames)
    h_ttbar  = ru.get_summed_histogram(bkg_list_ttbar , histnames)
    h_vv     = ru.get_summed_histogram(bkg_list_vv    , histnames)
    if ps > 0:
        h_ddqcd.Scale(ps)
    # Scale the histograms appropriately from SF from the EWKCR
    if sf:
        if isinstance(sf, list):
            hists = [h_bkg, h_wjets, h_dy, h_ttbar, h_vv]
            for h in hists:
                for ii, s in enumerate(sf):
                    bc = h.GetBinContent(ii + 1)
                    be = h.GetBinError(ii + 1)
                    h.SetBinContent(ii + 1, bc * s)
                    h.SetBinError(ii + 1, be * s)
        else:
            if sf > 0:
                h_bkg    .Scale(sf)
                h_wjets  .Scale(sf)
                h_dy     .Scale(sf)
                h_ttbar  .Scale(sf)
                h_vv     .Scale(sf)

    if "ptcorretarolled" in histnames:

        # print h_ddqcd.GetBinContent(6), h_ddqcd.GetBinContent(7)
        # d6 = E(h_ddqcd.GetBinContent(6), h_ddqcd.GetBinError(6)) + E(h_ddqcd.GetBinContent(7), h_ddqcd.GetBinError(7))
        # d13 = E(h_ddqcd.GetBinContent(13), h_ddqcd.GetBinError(13)) + E(h_ddqcd.GetBinContent(14), h_ddqcd.GetBinError(14))
        # b6 = E(h_bkg.GetBinContent(6), h_bkg.GetBinError(6)) + E(h_bkg.GetBinContent(7), h_bkg.GetBinError(7))
        # b13 = E(h_bkg.GetBinContent(13), h_bkg.GetBinError(13)) + E(h_bkg.GetBinContent(14), h_bkg.GetBinError(14))
        # h_ddqcd.SetBinContent(6, d6.val)
        # h_ddqcd.SetBinContent(7, d6.val)
        # h_ddqcd.SetBinError(6, d6.err)
        # h_ddqcd.SetBinError(7, d6.err)
        # h_ddqcd.SetBinContent(13, d13.val)
        # h_ddqcd.SetBinContent(14, d13.val)
        # h_ddqcd.SetBinError(13, d13.err)
        # h_ddqcd.SetBinError(14, d13.err)
        # h_bkg.SetBinContent(6, b6.val)
        # h_bkg.SetBinContent(7, b6.val)
        # h_bkg.SetBinError(6, b6.err)
        # h_bkg.SetBinError(7, b6.err)
        # h_bkg.SetBinContent(13, b13.val)
        # h_bkg.SetBinContent(14, b13.val)
        # h_bkg.SetBinError(13, b13.err)
        # h_bkg.SetBinError(14, b13.err)

        for ii in xrange(1, h_ddqcd.GetNbinsX() + 1):
            data_bc = h_ddqcd.GetBinContent(ii)
            data_be = h_ddqcd.GetBinError(ii)
            bkg_bc = h_bkg.GetBinContent(ii)
            bkg_be = h_bkg.GetBinError(ii)
            d = E(data_bc, data_be)
            b = E(bkg_bc, bkg_be)
            n = d - b
            if isSS:
                if d.err > n.val:
                    n.val = d.err

            h_ddqcd.SetBinContent(ii, n.val)
            h_ddqcd.SetBinError(ii, n.err)

    else:
        h_ddqcd.Add(h_bkg, -1)

    # MC QCD
    h_qcd_mu = ru.get_summed_histogram(bkg_list_qcd_mu, histnames).Clone("QCD(#mu)")
    h_qcd_el = ru.get_summed_histogram(bkg_list_qcd_el, histnames).Clone("QCD(EM)")
    h_qcd_bc = ru.get_summed_histogram(bkg_list_qcd_bc, histnames).Clone("QCD(HF)")

    return h_ddqcd, h_data, h_bkg, h_qcd_mu, h_qcd_el, h_qcd_bc, h_wjets, h_dy, h_ttbar, h_vv

def ewksf_v2(histname, ps=0, dd_qcd=None):

    _, h_d, h_b, h_qcd_mu, h_qcd_el, h_qcd_bc, h_w, h_dy, h_top, h_vv = plot(histname, ps, output_suffix="_prefit")

    if "__MET" in histname:
       mt = r.RooRealVar("mt", "mt", 0., 250.)
    else:
       mt = r.RooRealVar("mt", "mt", 0., 180.)

    h_qcd = h_qcd_mu.Clone() if "Mu" in histname else h_qcd_el.Clone()
    if dd_qcd:
        h_qcd = dd_qcd
    if "El" in histname:
        h_qcd.Add(h_qcd_bc)

    h_d = h_d.Clone()
    h_qcd = h_qcd.Clone()
    h_b = h_b.Clone()

    h_d.Rebin(6)
    h_qcd.Rebin(6)
    h_b.Rebin(6)

    hdata = r.RooDataHist("data", "data", r.RooArgList(mt), h_d)
    hqcd = r.RooDataHist("qcd", "qcd", r.RooArgList(mt), h_qcd)
    hewk = r.RooDataHist("ewk", "ewk", r.RooArgList(mt), h_b)
    hw = r.RooDataHist("w", "w", r.RooArgList(mt), h_w)
    hdy = r.RooDataHist("dy", "dy", r.RooArgList(mt), h_dy)
    htop = r.RooDataHist("top", "top", r.RooArgList(mt), h_top)
    hvv = r.RooDataHist("vv", "vv", r.RooArgList(mt), h_vv)
    hqcd_pdf = r.RooHistPdf("qcd_pdf", "qcd_pdf", r.RooArgSet(mt), hqcd)
    hewk_pdf = r.RooHistPdf("ewk_pdf", "ewk_pdf", r.RooArgSet(mt), hewk)
    hw_pdf = r.RooHistPdf("w_pdf", "w_pdf", r.RooArgSet(mt), hw)
    hdy_pdf = r.RooHistPdf("dy_pdf", "dy_pdf", r.RooArgSet(mt), hdy)
    htop_pdf = r.RooHistPdf("top_pdf", "top_pdf", r.RooArgSet(mt), htop)
    hvv_pdf = r.RooHistPdf("vv_pdf", "vv_pdf", r.RooArgSet(mt), hvv)

    nqcd = r.RooRealVar("nqcd", "number of QCD events", h_qcd.Integral(), h_qcd.Integral() * 0.5, h_qcd.Integral() * 1.5) # Allowed to float +/- 50% 
    newk = r.RooRealVar("newk", "number of EWK events", h_b.Integral(), h_b.Integral() * 0.5, h_b.Integral() * 1.5) # Allowed to float +/- 50% 

    nw = r.RooRealVar("nw", "number of EWK events", h_w.Integral(), h_w.Integral() * 0.5, h_w.Integral() * 1.5) # Allowed to float +/- 50% 
    ndy = r.RooRealVar("ndy", "number of EWK events", h_dy.Integral(), h_dy.Integral() * 0.5, h_dy.Integral() * 1.5) # Allowed to float +/- 50% 
    ntop = r.RooRealVar("ntop", "number of EWK events", h_top.Integral(), h_top.Integral() * 0.5, h_top.Integral() * 1.5) # Allowed to float +/- 50% 
    nvv = r.RooRealVar("nvv", "number of EWK events", h_vv.Integral(), h_vv.Integral() * 0.5, h_vv.Integral() * 1.5) # Allowed to float +/- 50% 
    model = r.RooAddPdf("model","model", r.RooArgList(hewk_pdf, hqcd_pdf), r.RooArgList(newk, nqcd))

    # model = r.RooAddPdf("model","model", r.RooArgList(hqcd_pdf, hw_pdf, hdy_pdf, htop_pdf, hvv_pdf), r.RooArgList(nqcd, nw, ndy, ntop, nvv))
    if "__MET" in histname:
        roofit_range = r.RooFit.Range(0, 250)
    elif "Mu" in histname:
        roofit_range = r.RooFit.Range(0, 100)
    elif "Loose" in histname:
        roofit_range = r.RooFit.Range(0, 180)
    else:
        roofit_range = r.RooFit.Range(0, 180)
    fitres = model.fitTo(hdata, r.RooFit.SumW2Error(r.kFALSE), r.RooFit.Extended(), r.RooFit.Save(r.kTRUE), roofit_range)

    c1 = r.TCanvas()

    mesframe = mt.frame()
    hdata.plotOn(mesframe)
    model.plotOn(mesframe)
    model.plotOn(mesframe, r.RooFit.Components("ewk_pdf"), r.RooFit.LineStyle(r.kDashed))
    mesframe.Draw()

    c1.SaveAs("test.pdf")

    print "qcd", nqcd.getValV() / h_qcd.Integral(), nqcd.getError() / h_qcd.Integral()
    print "ewk", newk.getValV() / h_b.Integral(), newk.getError() / h_b.Integral()
    print "w", nw.getValV() / h_w.Integral(), nw.getError() / h_w.Integral()
    print "dy", ndy.getValV() / h_dy.Integral(), ndy.getError() / h_dy.Integral()
    print "top", ntop.getValV() / h_top.Integral(), ntop.getError() / h_top.Integral()
    print "vv", nvv.getValV() / h_vv.Integral(), nvv.getError() / h_vv.Integral()

    sf = newk.getValV() / h_b.Integral()
    sfqcd = nqcd.getValV() / h_qcd.Integral()

    # print h_d.Integral()
    # print nqcd.getValV(), h_qcd.Integral()
    # print newk.getValV(), h_b.Integral()

    # print sf
    # print sfqcd

    plot(histname, ps, sf, sfqcd, output_suffix="_postfit", dd_qcd=dd_qcd)

    # plot(histname, ps, sf=0.9, sfqcd=10, output_suffix="_postfit", dd_qcd=dd_qcd)
    sf = newk.getValV() / h_b.Integral()

    dd_qcd = h_d.Clone("ddqcd")
    ewkclone = h_b.Clone("ewk")
    ewkclone.Scale(sf)
    dd_qcd.Add(ewkclone, -1)

    return newk.getValV() / h_b.Integral(), newk.getError() / h_b.Integral(), dd_qcd

def get_bounds_from_source_file(keyword):
    line = [ y.strip() for y in open("process.cc").readlines() if keyword in y and "const std::vector<float>" in y ][0]
    bounds = [ float(x) for x in line.split("{")[1].split("}")[0].split(",") ]
    return bounds

def get_fakerate_histograms(num, den, ps=0, sf=0, sfden=0):

    h_num, _, _, h_num_qcd_mu, h_num_qcd_el, h_num_qcd_bc, _, _, _, _ = plot(num, ps, sf)
    if sfden == 0:
        h_den, _, _, h_den_qcd_mu, h_den_qcd_el, h_den_qcd_bc, _, _, _, _ = plot(den, ps, sf)
    else:
        h_den, _, _, h_den_qcd_mu, h_den_qcd_el, h_den_qcd_bc, _, _, _, _ = plot(den, ps, sfden)

    # Creating a summed histogram (EM + HF sourced e-fake) where the ratio will be only of importance as we will divide the histograms to get fake rate
    h_num_qcd_esum = h_num_qcd_el.Clone("QCD(e)")
    h_den_qcd_esum = h_den_qcd_el.Clone("QCD(e)")
    h_num_qcd_esum.Add(h_num_qcd_bc)
    h_den_qcd_esum.Add(h_den_qcd_bc)

    # Data
    u.move_in_overflows(h_num)
    u.move_in_overflows(h_den)
    h_num.Divide(h_den)

    # Mu fake rate
    u.move_in_overflows(h_num_qcd_mu)
    u.move_in_overflows(h_den_qcd_mu)
    h_num_qcd_mu.Divide(h_den_qcd_mu)

    # EM fake rate
    u.move_in_overflows(h_num_qcd_el)
    u.move_in_overflows(h_den_qcd_el)
    h_num_qcd_el.Divide(h_den_qcd_el)

    # HF fake rate
    u.move_in_overflows(h_num_qcd_bc)
    u.move_in_overflows(h_den_qcd_bc)
    h_num_qcd_bc.Divide(h_den_qcd_bc)

    # Total summed electron fake rate
    u.move_in_overflows(h_num_qcd_esum)
    u.move_in_overflows(h_den_qcd_esum)
    h_num_qcd_esum.Divide(h_den_qcd_esum)

    # Set any negative fake rate to 0 or some tiny number
    def set_nonzero(h):
       for i in xrange(1, h.GetNbinsX()+1):
           bc = h.GetBinContent(i)
           if bc < 0:
               h.SetBinContent(i, 1e-6)
    set_nonzero(h_num)
    set_nonzero(h_num_qcd_mu)
    set_nonzero(h_num_qcd_esum)
    set_nonzero(h_num_qcd_el)
    set_nonzero(h_num_qcd_bc)

    return h_num, h_num_qcd_mu, h_num_qcd_esum, h_num_qcd_el, h_num_qcd_bc

def add_systematics(h_num, herr_num):
    h_num.Print("all")
    herr_num.Print("all")
    for i in xrange(1, h_num.GetNbinsX()+1):
        derr = abs(herr_num.GetBinContent(i) - h_num.GetBinContent(i))
        h_num.SetBinError(i, math.sqrt(h_num.GetBinError(i)**2 + derr**2))


def fakerate(num, den, ps=0, sf=0, sferr=0, tfile=None, sfden=0, sfdenerr=0):

    # Obtain histograms
    h_num    , h_num_qcd_mu    , h_num_qcd_esum    , h_num_qcd_el    , h_num_qcd_bc    = get_fakerate_histograms(num , den , ps , sf, sfden)
    if isinstance(sf, list):
        herr_num , herr_num_qcd_mu , herr_num_qcd_esum , herr_num_qcd_el , herr_num_qcd_bc = get_fakerate_histograms(num , den , ps , sferr, sfdenerr)
    else:
        herr_num , herr_num_qcd_mu , herr_num_qcd_esum , herr_num_qcd_el , herr_num_qcd_bc = get_fakerate_histograms(num , den , ps , sf-sferr)

    # Set data-driven QCD estimate systematics stemming from EWK SF uncertainty
    add_systematics(h_num, herr_num)

    # Options
    alloptions= {
               "ratio_range":[0.0,2.0],
               "nbins": 180,
               "autobin": False,
               "legend_scalex": 0.8,
               "legend_scaley": 0.8,
               "output_name": "plots/{}/{}/{}/fakerate/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", num+"__"+den),
               "bkg_sort_method": "unsorted",
               "no_ratio": False,
               "print_yield": True,
               "yield_prec": 3,
               "draw_points": True,
               "hist_line_none": True,
               "show_bkg_errors": True,
               "lumi_value" : lumi,
               "yaxis_range": [0., 0.4] if "Mu" in num else ([0., 1.2] if isSS else [0., 1.8]),
               }

    bgs_list = [h_num_qcd_mu] if "Mu" in num else [h_num_qcd_esum]
    #bgs_list = [h_num_qcd_mu] if "Mu" in num else [h_num_qcd_esum, h_num_qcd_el, h_num_qcd_bc]
    #sigs_list = [] if "Mu" in num else [h_num_qcd_el, h_num_qcd_bc]
    bgs_list_copy = [h_num_qcd_mu.Clone()] if "Mu" in num else [h_num_qcd_esum.Clone()]
    sigs_list = []

    h_num_qcd_esum.Print("all")

    # Special label handling instance for pt-eta rolled out case
    histname = num.split("__")[1]
    if histname == "ptcorretarolledcoarse":
       xbounds = get_bounds_from_source_file("ptcorrcoarse_bounds")
       ybounds = get_bounds_from_source_file("eta_bounds")
       for jndex in xrange(len(ybounds)-1):
           for index in xrange(len(xbounds)-1):
               #label = "Ptcorr #in ({}, {}) and |#eta| #in ({:.1f}, {:.1f})".format(int(xbounds[index]), int(xbounds[index+1]), ybounds[jndex], ybounds[jndex+1])
               label = "({}, {}), ({:.1f}, {:.1f})".format(int(xbounds[index]), int(xbounds[index+1]), ybounds[jndex], ybounds[jndex+1])
               for h in sigs_list + bgs_list + [h_num]:
                   h.GetXaxis().SetBinLabel((jndex)*(len(xbounds)-1) + (index+1), label)
    if histname == "ptcorretarolled":
       xbounds = get_bounds_from_source_file("ptcorr_bounds")
       ybounds = get_bounds_from_source_file("eta_bounds")
       for jndex in xrange(len(ybounds)-1):
           for index in xrange(len(xbounds)-1):
               #label = "Ptcorr #in ({}, {}) and |#eta| #in ({:.1f}, {:.1f})".format(int(xbounds[index]), int(xbounds[index+1]), ybounds[jndex], ybounds[jndex+1])
               label = "({}, {}), ({:.1f}, {:.1f})".format(int(xbounds[index]), int(xbounds[index+1]), ybounds[jndex], ybounds[jndex+1])
               for h in sigs_list + bgs_list + [h_num]:
                   h.GetXaxis().SetBinLabel((jndex)*(len(xbounds)-1) + (index+1), label)
    alloptions["canvas_main_rightmargin"] = 1./6.
    alloptions["canvas_ratio_rightmargin"] = 1./6.
    alloptions["canvas_ratio_bottommargin"] = 0.5

    p.plot_hist(
           sigs = sigs_list,
           bgs = bgs_list,
           data = h_num,
           #data = None,
           syst = None,
           colors=[2001],
           legend_labels=["QCD(#mu)"] if "Mu" in num else ["QCD(e)"],
           options=alloptions)

    if tfile:
        tfile.cd()
        channel = "Mu" if "Mu" in num else "El"
        histname = num.split("__")[1]
        data_fakerate = h_num.Clone(channel+"_"+histname+"_data_fakerate")
        qcd_fakerate  = bgs_list_copy[0].Clone(channel+"_"+histname+"_qcd_fakerate")

        # Special treatment for 2018 3l mu fakerate
        # if highest bin in pt set it to QCD one
        if channel == "Mu" and isSS == False:
            data_fakerate.SetBinContent(6, qcd_fakerate.GetBinContent(6))
            data_fakerate.SetBinError(6, qcd_fakerate.GetBinError(6))
            data_fakerate.SetBinContent(12, qcd_fakerate.GetBinContent(12))
            data_fakerate.SetBinError(12, qcd_fakerate.GetBinError(12))

        if histname == "etacorrvarbin":
            create_varbin(data_fakerate, "eta_bounds").Write()
            create_varbin(qcd_fakerate, "eta_bounds").Write()
        elif histname == "ptcorrvarbin":
            create_varbin(data_fakerate, "ptcorr_bounds").Write()
            create_varbin(qcd_fakerate, "ptcorr_bounds").Write()
        elif histname == "ptcorrvarbincoarse":
            create_varbin(data_fakerate, "ptcorrcoarse_bounds").Write()
            create_varbin(qcd_fakerate, "ptcorrcoarse_bounds").Write()
        elif histname == "ptcorretarolled":
            create_varbin(data_fakerate, "ptcorr_bounds", "eta_bounds").Write()
            create_varbin(qcd_fakerate, "ptcorr_bounds", "eta_bounds").Write()
            # Closure 3l mu 51% 3l el 1% ss mu 33% ss el 3% (1.51, 0.994, 1.329, 0.978)
            if channel == "Mu":
                if isSS:
                    create_varbin(data_fakerate, "ptcorr_bounds", "eta_bounds", 0.14, "closure").Write()
                else:
                    create_varbin(data_fakerate, "ptcorr_bounds", "eta_bounds", 0.56, "closure").Write()
            elif channel == "El":
                if isSS:
                    create_varbin(data_fakerate, "ptcorr_bounds", "eta_bounds", 0.29, "closure").Write()
                else:
                    create_varbin(data_fakerate, "ptcorr_bounds", "eta_bounds", 0.11, "closure").Write()
        elif histname == "ptcorretarolledcoarse":
            create_varbin(data_fakerate, "ptcorrcoarse_bounds", "eta_bounds").Write()
            create_varbin(qcd_fakerate, "ptcorrcoarse_bounds", "eta_bounds").Write()
            # Closure 3l mu 51% 3l el 1% ss mu 33% ss el 3% (1.51, 0.994, 1.329, 0.978)
            if channel == "Mu":
                if isSS:
                    create_varbin(data_fakerate, "ptcorrcoarse_bounds", "eta_bounds", 0.33, "closure").Write()
                else:
                    create_varbin(data_fakerate, "ptcorrcoarse_bounds", "eta_bounds", 0.51, "closure").Write()
            elif channel == "El":
                if isSS:
                    create_varbin(data_fakerate, "ptcorrcoarse_bounds", "eta_bounds", 0.03, "closure").Write()
                else:
                    create_varbin(data_fakerate, "ptcorrcoarse_bounds", "eta_bounds", 0.01, "closure").Write()

def create_varbin(h, xboundskeyword, yboundskeyword=None, closureerr=0, suffix=""):
    # Read the initialization line from process.cc
    xbounds = get_bounds_from_source_file(xboundskeyword)
    if yboundskeyword:
        ybounds = get_bounds_from_source_file(yboundskeyword)
    if not yboundskeyword:
        hrtn = r.TH1F(h.GetName()+suffix, h.GetTitle(), len(xbounds)-1, array('d', xbounds)) 
        for i in xrange(1, len(xbounds)+1):
            hrtn.SetBinContent(i, h.GetBinContent(i))
            if closureerr == 0:
                hrtn.SetBinError(i, h.GetBinError(i))
            else:
                hrtn.SetBinError(i, h.GetBinContent(i) * closureerr)
    else:
        hrtn = r.TH2F(h.GetName()+suffix, h.GetTitle(), len(xbounds)-1, array('d', xbounds), len(ybounds)-1, array('d', ybounds)) 
        for i in xrange(1, len(xbounds)+1):
            for j in xrange(1, len(ybounds)+1):
                hrtn.SetBinContent(i, j, h.GetBinContent(i + (j-1)*(len(xbounds)-1)))
                hrtn.SetBinError(i, j, h.GetBinError(i + (j-1)*(len(xbounds)-1)))
                if closureerr == 0:
                    hrtn.SetBinError(i, j, h.GetBinError(i + (j-1)*(len(xbounds)-1)))
                else:
                    hrtn.SetBinError(i, j, h.GetBinContent(i + (j-1)*(len(xbounds)-1)) * closureerr)
    hrtn = set_overflow_bins_to_last_bins(hrtn)
    return hrtn

def set_overflow_bins_to_last_bins(h):
    if h.GetDimension() == 1:
        h.SetBinContent(h.GetNbinsX()+1, h.GetBinContent(h.GetNbinsX()))
        h.SetBinError(h.GetNbinsX()+1, h.GetBinError(h.GetNbinsX()))
    if h.GetDimension() == 2:
        for y in xrange(1, h.GetNbinsY()+1):
            h.SetBinContent(h.GetNbinsX()+1, y, h.GetBinContent(h.GetNbinsX(), y))
            h.SetBinError(h.GetNbinsX()+1, y, h.GetBinError(h.GetNbinsX(), y))
        for x in xrange(1, h.GetNbinsX()+1):
            h.SetBinContent(x, h.GetNbinsY()+1, h.GetBinContent(x, h.GetNbinsY()))
            h.SetBinError(x, h.GetNbinsY()+1, h.GetBinError(x, h.GetNbinsY()))
        h.SetBinContent(h.GetNbinsX()+1, h.GetNbinsY()+1, h.GetBinContent(h.GetNbinsX(), h.GetNbinsY()))
        h.SetBinError(h.GetNbinsX()+1, h.GetNbinsY()+1, h.GetBinError(h.GetNbinsX(), h.GetNbinsY()))
    return h

def closure_plot(predict, estimate, nbins=1):

    # Glob the file lists
    bkg_list_wjets  = [ output_dirpath+"/wj_ht.root" ]
    bkg_list_ttbar  = [ output_dirpath+"/tt_1l.root" ]

    # Get all the histogram objects
    h_wjets_predict = ru.get_summed_histogram(bkg_list_wjets , predict)
    h_ttbar_predict = ru.get_summed_histogram(bkg_list_ttbar , predict)
    h_wjets_estimate = ru.get_summed_histogram(bkg_list_wjets , estimate)
    h_ttbar_estimate = ru.get_summed_histogram(bkg_list_ttbar , estimate)

    # Set the names of the histograms
    h_wjets_predict.SetTitle("W predict")
    h_ttbar_predict.SetTitle("Top predict")
    h_wjets_estimate.SetTitle("W estimate")
    h_ttbar_estimate.SetTitle("Top estimate")

    # Color settings
    colors = [ 2005, 2001, ]

    # Options
    alloptions= {
                "ratio_range":[0.0,2.0],
                "nbins": nbins,
                "autobin": False,
                "legend_scalex": 1.8,
                "legend_scaley": 1.1,
                "output_name": "plots/{}/{}/{}/closure/{}_nbins{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", predict + "__" + estimate, nbins),
                "bkg_sort_method": "unsorted",
                "no_ratio": False,
                "print_yield": False,
                "yaxis_log": False,
                "legend_smart": True,
                "lumi_value" : lumi,
                "legend_datalabel": "Estimate",
                "yield_prec": 3,
                "print_yield": True,
                }

    # The bkg histogram list
    bgs_list = [ h_ttbar_predict.Clone() , h_wjets_predict.Clone() ]
    #bgs_list = [ h_ttbar_predict  ]

    h_estimate = h_wjets_estimate.Clone("Estimate")
    h_estimate.Add(h_ttbar_estimate)

    ll = [ "Top Predict", "W Predict" ]

    # Plot them
    p.plot_hist(
            bgs = bgs_list,
            data = h_estimate,
            colors = colors,
            syst = None,
            legend_labels=ll,
            options=alloptions)

def main():


    ofile = r.TFile("histmap/fakerate_ss.root" if isSS else "histmap/fakerate_3l.root", "recreate")

    ewksf_v2("OneMuLoose__nVlep")
    ewksf_v2("OneMu__nVlep")
    ewksf_v2("OneMuLoose__pt")
    ewksf_v2("OneMu__pt")
    ewksf_v2("OneMuLoose__ptcorr")
    ewksf_v2("OneMu__ptcorr")
    ewksf_v2("OneMuMR2__pt")
    ewksf_v2("OneMuTightMR2__pt")
    ewksf_v2("OneMuMR2__ptcorr")
    ewksf_v2("OneMuTightMR2__ptcorr")
    if isSS:
        sf01, sf01err, _ = ewksf_v2("OneMuLooseEta0Pt1__MT")
        sf02, sf02err, _ = ewksf_v2("OneMuLooseEta0Pt2__MT")
        sf03, sf03err, _ = ewksf_v2("OneMuLooseEta0Pt3__MT")
        sf04, sf04err, _ = ewksf_v2("OneMuLooseEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneMuLooseEta1Pt1__MT")
        sf12, sf12err, _ = ewksf_v2("OneMuLooseEta1Pt2__MT")
        sf13, sf13err, _ = ewksf_v2("OneMuLooseEta1Pt3__MT")
        sf14, sf14err, _ = ewksf_v2("OneMuLooseEta1Pt4__MT")
        sfden = [0., 0., sf01, sf02, sf03, sf04, 0., 0., sf11, sf12, sf13, sf14]
        sfdenerr = [0., 0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, 0., 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err]
        sf01, sf01err, _ = ewksf_v2("OneMuEta0Pt1__MT")
        sf02, sf02err, _ = ewksf_v2("OneMuEta0Pt2__MT")
        sf03, sf03err, _ = ewksf_v2("OneMuEta0Pt3__MT")
        sf04, sf04err, _ = ewksf_v2("OneMuEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneMuEta1Pt1__MT")
        sf12, sf12err, _ = ewksf_v2("OneMuEta1Pt2__MT")
        sf13, sf13err, _ = ewksf_v2("OneMuEta1Pt3__MT")
        sf14, sf14err, _ = ewksf_v2("OneMuEta1Pt4__MT")
        sf = [0., 0., sf01, sf02, sf03, sf04, 0., 0., sf11, sf12, sf13, sf14]
        sferr = [0., 0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, 0., 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err]
    else:
        sf01, sf01err, _ = ewksf_v2("OneMuLooseEta0Pt0__MT")
        sf02, sf02err, _ = ewksf_v2("OneMuLooseEta0Pt1__MT")
        sf03, sf03err, _ = ewksf_v2("OneMuLooseEta0Pt2__MT")
        sf04, sf04err, _ = ewksf_v2("OneMuLooseEta0Pt3__MT")
        sf05, sf05err, _ = ewksf_v2("OneMuLooseEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneMuLooseEta1Pt0__MT")
        sf12, sf12err, _ = ewksf_v2("OneMuLooseEta1Pt1__MT")
        sf13, sf13err, _ = ewksf_v2("OneMuLooseEta1Pt2__MT")
        sf14, sf14err, _ = ewksf_v2("OneMuLooseEta1Pt3__MT")
        sf15, sf15err, _ = ewksf_v2("OneMuLooseEta1Pt4__MT")
        sfden = [0., sf01, sf02, sf03, sf04, sf05, 0., sf11, sf12, sf13, sf14, sf15]
        sfdenerr = [0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, sf05-sf05err, 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err, sf15-sf15err]
        sf01, sf01err, _ = ewksf_v2("OneMuEta0Pt0__MT")
        sf02, sf02err, _ = ewksf_v2("OneMuEta0Pt1__MT")
        sf03, sf03err, _ = ewksf_v2("OneMuEta0Pt2__MT")
        sf04, sf04err, _ = ewksf_v2("OneMuEta0Pt3__MT")
        sf05, sf05err, _ = ewksf_v2("OneMuEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneMuEta1Pt0__MT")
        sf12, sf12err, _ = ewksf_v2("OneMuEta1Pt1__MT")
        sf13, sf13err, _ = ewksf_v2("OneMuEta1Pt2__MT")
        sf14, sf14err, _ = ewksf_v2("OneMuEta1Pt3__MT")
        sf15, sf15err, _ = ewksf_v2("OneMuEta1Pt4__MT")
        sf = [0., sf01, sf02, sf03, sf04, sf05, 0., sf11, sf12, sf13, sf14, sf15]
        sferr = [0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, sf05-sf05err, 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err, sf15-sf15err]
    fakerate("OneMuTightMR2__ptcorretarolled" , "OneMuMR2__ptcorretarolled", sf=sf, sferr=sferr, sfden=sfden, sfdenerr=sfdenerr, tfile=ofile)

    ewksf_v2("OneElLoose__nVlep")
    ewksf_v2("OneEl__nVlep")
    ewksf_v2("OneElLoose__pt")
    ewksf_v2("OneEl__pt")
    ewksf_v2("OneElLoose__ptcorr")
    ewksf_v2("OneEl__ptcorr")
    ewksf_v2("OneElMR2__pt")
    ewksf_v2("OneElTightMR2__pt")
    ewksf_v2("OneElMR2__ptcorr")
    ewksf_v2("OneElTightMR2__ptcorr")
    if isSS:
        sf01, sf01err, _ = ewksf_v2("OneElLooseEta0Pt1__MT")
        sf02, sf02err, _ = ewksf_v2("OneElLooseEta0Pt2__MT")
        sf03, sf03err, _ = ewksf_v2("OneElLooseEta0Pt3__MT")
        sf04, sf04err, _ = ewksf_v2("OneElLooseEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneElLooseEta1Pt1__MT")
        sf12, sf12err, _ = ewksf_v2("OneElLooseEta1Pt2__MT")
        sf13, sf13err, _ = ewksf_v2("OneElLooseEta1Pt3__MT")
        sf14, sf14err, _ = ewksf_v2("OneElLooseEta1Pt4__MT")
        sfden = [0., 0., sf01, sf02, sf03, sf04, 0., 0., sf11, sf12, sf13, sf14]
        sfdenerr = [0., 0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, 0., 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err]
        sf01, sf01err, _ = ewksf_v2("OneElEta0Pt1__MT")
        sf02, sf02err, _ = ewksf_v2("OneElEta0Pt2__MT")
        sf03, sf03err, _ = ewksf_v2("OneElEta0Pt3__MT")
        sf04, sf04err, _ = ewksf_v2("OneElEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneElEta1Pt1__MT")
        sf12, sf12err, _ = ewksf_v2("OneElEta1Pt2__MT")
        sf13, sf13err, _ = ewksf_v2("OneElEta1Pt3__MT")
        sf14, sf14err, _ = ewksf_v2("OneElEta1Pt4__MT")
        sf = [0., 0., sf01, sf02, sf03, sf04, 0., 0., sf11, sf12, sf13, sf14]
        sferr = [0., 0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, 0., 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err]
    else:
        sf01, sf01err, _ = ewksf_v2("OneElLooseEta0Pt0__MT")
        sf02, sf02err, _ = ewksf_v2("OneElLooseEta0Pt1__MT")
        sf03, sf03err, _ = ewksf_v2("OneElLooseEta0Pt2__MT")
        sf04, sf04err, _ = ewksf_v2("OneElLooseEta0Pt3__MT")
        sf05, sf05err, _ = ewksf_v2("OneElLooseEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneElLooseEta1Pt0__MT")
        sf12, sf12err, _ = ewksf_v2("OneElLooseEta1Pt1__MT")
        sf13, sf13err, _ = ewksf_v2("OneElLooseEta1Pt2__MT")
        sf14, sf14err, _ = ewksf_v2("OneElLooseEta1Pt3__MT")
        sf15, sf15err, _ = ewksf_v2("OneElLooseEta1Pt4__MT")
        sfden = [0., sf01, sf02, sf03, sf04, sf05, 0., sf11, sf12, sf13, sf14, sf15]
        sfdenerr = [0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, sf05-sf05err, 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err, sf15-sf15err]
        sf01, sf01err, _ = ewksf_v2("OneElEta0Pt0__MT")
        sf02, sf02err, _ = ewksf_v2("OneElEta0Pt1__MT")
        sf03, sf03err, _ = ewksf_v2("OneElEta0Pt2__MT")
        sf04, sf04err, _ = ewksf_v2("OneElEta0Pt3__MT")
        sf05, sf05err, _ = ewksf_v2("OneElEta0Pt4__MT")
        sf11, sf11err, _ = ewksf_v2("OneElEta1Pt0__MT")
        sf12, sf12err, _ = ewksf_v2("OneElEta1Pt1__MT")
        sf13, sf13err, _ = ewksf_v2("OneElEta1Pt2__MT")
        sf14, sf14err, _ = ewksf_v2("OneElEta1Pt3__MT")
        sf15, sf15err, _ = ewksf_v2("OneElEta1Pt4__MT")
        sf = [0., sf01, sf02, sf03, sf04, sf05, 0., sf11, sf12, sf13, sf14, sf15]
        sferr = [0., sf01-sf01err, sf02-sf02err, sf03-sf03err, sf04-sf04err, sf05-sf05err, 0., sf11-sf11err, sf12-sf12err, sf13-sf13err, sf14-sf14err, sf15-sf15err]
    fakerate("OneElTightMR2__ptcorretarolled" , "OneElMR2__ptcorretarolled", sf=sf, sferr=sferr, sfden=sfden, sfdenerr=sfdenerr, tfile=ofile)

    closure_plot("MuClosureTight__MT", "MuClosureTightPredict__MT")
    closure_plot("ElClosureTight__MT", "ElClosureTightPredict__MT")
    closure_plot("MuClosureTightBVeto__MT", "MuClosureTightBVetoPredict__MT")
    closure_plot("ElClosureTightBVeto__MT", "ElClosureTightBVetoPredict__MT")
    closure_plot("MuClosureTightNbgeq2__MT", "MuClosureTightNbgeq2Predict__MT")
    closure_plot("ElClosureTightNbgeq2__MT", "ElClosureTightNbgeq2Predict__MT")
    closure_plot("MuClosureTightNbgeq1__MT", "MuClosureTightNbgeq1Predict__MT")
    closure_plot("ElClosureTightNbgeq1__MT", "ElClosureTightNbgeq1Predict__MT")
    closure_plot("ElClosureTightBVeto__Mll", "ElClosureTightBVetoPredict__Mll", 6)
    closure_plot("ElClosureTightBVeto__MET", "ElClosureTightBVetoPredict__MET", 6)
    closure_plot("ElClosureTightBVeto__MT", "ElClosureTightBVetoPredict__MT", 6)
    closure_plot("ElClosureTightBVeto__ptcorr", "ElClosureTightBVetoPredict__ptcorr", 6)
    closure_plot("MuClosureTightBVeto__Mll", "MuClosureTightBVetoPredict__Mll", 6)
    closure_plot("MuClosureTightBVeto__MET", "MuClosureTightBVetoPredict__MET", 6)
    closure_plot("MuClosureTightBVeto__MT", "MuClosureTightBVetoPredict__MT", 6)
    closure_plot("MuClosureTightBVeto__ptcorr", "MuClosureTightBVetoPredict__ptcorr", 6)


if __name__ == "__main__":

    main()


