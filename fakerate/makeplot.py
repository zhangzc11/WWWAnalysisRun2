#!/bin/env python

# Plotting script for the fake rate analysis

import sys


def grand_main(input_ntup_tag, analysis_tag, isSS):

    output_dirpath = "outputs/{}/{}/{}".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l")

    import ROOT as r
    import pyrootutil as ru
    import plottery_wrapper as p
    from plottery import utils as u
    import glob
    import math
    from array import array
    from pytable import Table
    import tabletex

    is2017 = "FR2017" in output_dirpath

    def main():

        p.makedir("./plots/{}/{}/{}/".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l"))
        p.copy_nice_plot("./plots/{}/{}/{}/".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l"))

        mu_isos()
        el_isos()
        mu_fakerate()
        el_fakerate()
        
        ofile = r.TFile("histmap/fakerate_ss.root" if isSS else "histmap/fakerate_3l.root", "recreate")

        prescale_muHLT17 = get_prescale("TwoMuHLT17__Mll")
        prescale_elHLT23 = get_prescale("TwoElHLT23__Mll")
        print prescale_muHLT17 , prescale_elHLT23
        #prescale_muHLT17 = 1
        #prescale_elHLT23 = 1

        plot("OneEl__nj"                  , prescale_muHLT17)
        plot("OneEl__pt"                  , prescale_muHLT17)
        plot("OneEl__MET"                 , prescale_muHLT17)
        plot("OneElHighMET__MT"           , prescale_elHLT23)
        plot("OneElEWKCR__MT"             , prescale_elHLT23)
        plot("OneElEWKCR__MET"            , prescale_elHLT23)
        plot("OneElEWKCR__Nvtx"           , prescale_elHLT23)
        plot("OneElMR__MT"                , prescale_elHLT23)
        plot("OneElMR__ptcorr"            , prescale_elHLT23)
        plot("OneElTightMR__ptcorr"       , prescale_elHLT23)

        el_sf, el_sferr = ewksf("OneElEWKCR__MT", prescale_elHLT23)
        plot("OneElMR__ptcorrvarbin"      , prescale_elHLT23, el_sf)
        plot("OneElTightMR__ptcorrvarbin" , prescale_elHLT23, el_sf)
        fakerate("OneElTightMR__pt"                    , "OneElMR__pt"                    , prescale_elHLT23 , el_sf , el_sferr, ofile)
        fakerate("OneElTightMR__ptcorrvarbin"          , "OneElMR__ptcorrvarbin"          , prescale_elHLT23 , el_sf , el_sferr, ofile)
        fakerate("OneElTightMR__etavarbin"             , "OneElMR__etavarbin"             , prescale_elHLT23 , el_sf , el_sferr, ofile)
        fakerate("OneElTightMR__ptcorretarolled"       , "OneElMR__ptcorretarolled"       , prescale_elHLT23 , el_sf , el_sferr, ofile)
        fakerate("OneElTightMR__ptcorretarolledcoarse" , "OneElMR__ptcorretarolledcoarse" , prescale_elHLT23 , el_sf , el_sferr, ofile)

        plot("OneMu__nj"                  , prescale_muHLT17)
        plot("OneMu__pt"                  , prescale_muHLT17)
        plot("OneMu__MET"                 , prescale_muHLT17)
        plot("OneMuHighMET__MT"           , prescale_muHLT17)
        plot("OneMuEWKCR__MT"             , prescale_muHLT17)
        plot("OneMuEWKCR__MET"            , prescale_muHLT17)
        plot("OneMuEWKCR__Nvtx"           , prescale_muHLT17)
        plot("OneMuMR__MT"                , prescale_muHLT17)
        plot("OneMuMR__ptcorr"            , prescale_muHLT17)
        plot("OneMuTightMR__ptcorr"       , prescale_muHLT17)
    #    plot("OneMuMR__lepmotherid"       , prescale_muHLT17)
    #    plot("MuClosureTight__mumotherid" , prescale_muHLT17)
    #    plot("OneMuMR__lepmotherid"       , prescale_muHLT17)
    #    plot("MuClosureLoose__mumotherid" , prescale_muHLT17)
    #    plot("MuClosureLooseEta0Pt1__mumotherid" , prescale_muHLT17)
    #    plot("MuClosureLooseEta1Pt1__mumotherid" , prescale_muHLT17)

        plot("OneMuEWKCREta0Pt3__MT"      , prescale_muHLT17)
        plot("OneMuEWKCREta1Pt3__MT"      , prescale_muHLT17)

        mu_sf, mu_sferr = ewksf("OneMuEWKCR__MT", prescale_muHLT17)
        plot("OneMuMR__ptcorrvarbin"      , prescale_muHLT17)
        plot("OneMuTightMR__ptcorrvarbin" , prescale_muHLT17)
        fakerate("OneMuTightMR__pt"                    , "OneMuMR__pt"                    , prescale_muHLT17 , mu_sf , mu_sferr, ofile)
        fakerate("OneMuTightMR__ptcorrvarbin"          , "OneMuMR__ptcorrvarbin"          , prescale_muHLT17 , mu_sf , mu_sferr, ofile)
        fakerate("OneMuTightMR__etavarbin"             , "OneMuMR__etavarbin"             , prescale_muHLT17 , mu_sf , mu_sferr, ofile)
        fakerate("OneMuTightMR__ptcorretarolled"       , "OneMuMR__ptcorretarolled"       , prescale_muHLT17 , mu_sf , mu_sferr, ofile)
        fakerate("OneMuTightMR__ptcorretarolledcoarse" , "OneMuMR__ptcorretarolledcoarse" , prescale_muHLT17 , mu_sf , mu_sferr, ofile)
        x = Table()
        x.add_column("type of scale factors", [ "Prescale $e$", "Prescale $\mu$", "$e$ prompt SF", "$\mu$ prompt SF", ])
        x.add_column("scale factor values", ["{:.2f}".format(prescale_elHLT23), "{:.2f}".format(prescale_muHLT17), "{:.2f} $\\pm$ {:.2f}".format(el_sf, el_sferr), "{:.2f} $\\pm$ {:.2f}".format(mu_sf, mu_sferr)])
        ru.write_tex_table(x, "./plots/{}/{}/{}/scalefactors.tex".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l"), caption="Scale factors used for {} channel".format("same-sign" if isSS else "three-lepton"))
        print "PRINTHERE", "prescale_muHLT17 , prescale_elHLT23,", prescale_muHLT17 , prescale_elHLT23
        print "PRINTHERE", "el_sf", el_sf, el_sferr
        print "PRINTHERE", "mu_sf", mu_sf, mu_sferr
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

    def get_bounds_from_source_file(keyword):
        line = [ y.strip() for y in open("process.cc").readlines() if keyword in y and "const std::vector<float>" in y ][0]
        bounds = [ float(x) for x in line.split("{")[1].split("}")[0].split(",") ]
        return bounds

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

    def get_prescale(histname):
        _, h_d, h_b, _, _, _ = plot(histname)
        h_b.Rebin(h_b.GetNbinsX())
        h_d.Rebin(h_d.GetNbinsX())
        h_d.Print("all")
        h_b.Print("all")
        h_b.Divide(h_d)
        return h_b.GetBinContent(1)

    def select_mt_window(h):
        h.Rebin(10)
        for i in [1, 2, 3, 4, 5, 6, 7, 8]:
            h.SetBinContent(i, 0)
            h.SetBinError(i, 0)
        for i in [13, 14, 15, 16, 17, 18]:
            h.SetBinContent(i, 0)
            h.SetBinError(i, 0)
        h.Rebin(18)
        return h

    def ewksf(histname, ps=0):
        _, h_d, h_b, _, _, _ = plot(histname, ps)
        h_d = select_mt_window(h_d)
        h_b = select_mt_window(h_b)
        h_d.Print("all")
        h_b.Print("all")
        h_d.Divide(h_b)
        h_d.Print("all")
        return h_d.GetBinContent(1), h_d.GetBinError(1)

    def get_fakerate_histograms(num, den, ps=0, sf=0):

        h_num, _, _, h_num_qcd_mu, h_num_qcd_el, h_num_qcd_bc = plot(num, ps, sf)
        h_den, _, _, h_den_qcd_mu, h_den_qcd_el, h_den_qcd_bc = plot(den, ps, sf)

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

        return h_num, h_num_qcd_mu, h_num_qcd_esum, h_num_qcd_el, h_num_qcd_bc

    def add_systematics(h_num, herr_num):
        h_num.Print("all")
        herr_num.Print("all")
        for i in xrange(1, h_num.GetNbinsX()+1):
            derr = abs(herr_num.GetBinContent(i) - h_num.GetBinContent(i))
            h_num.SetBinError(i, math.sqrt(h_num.GetBinError(i)**2 + derr**2))

    def fakerate(num, den, ps=0, sf=0, sferr=0, tfile=None):

        # Obtain histograms
        h_num    , h_num_qcd_mu    , h_num_qcd_esum    , h_num_qcd_el    , h_num_qcd_bc    = get_fakerate_histograms(num , den , ps , sf)
        herr_num , herr_num_qcd_mu , herr_num_qcd_esum , herr_num_qcd_el , herr_num_qcd_bc = get_fakerate_histograms(num , den , ps , sf+sferr)

        # Set data-driven QCD estimate systematics stemming from EWK SF uncertainty
        add_systematics(h_num, herr_num)

        # Options
        alloptions= {
                    "ratio_range":[0.0,2.0],
                    "nbins": 180,
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "output_name": "plots/{}/{}/{}/fakerate/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", num+"__"+den),
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "draw_points": True,
                    "lumi_value" : 41.3,
                    }

        bgs_list = [h_num_qcd_mu] if "Mu" in num else [h_num_qcd_esum]
        #bgs_list = [h_num_qcd_mu] if "Mu" in num else [h_num_qcd_esum, h_num_qcd_el, h_num_qcd_bc]
        sigs_list = [] if "Mu" in num else [h_num_qcd_el, h_num_qcd_bc]

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
        alloptions["canvas_main_rightmargin"] = 1./6.
        alloptions["canvas_ratio_rightmargin"] = 1./6.
        alloptions["canvas_ratio_bottommargin"] = 0.5

        p.plot_hist(
                sigs = sigs_list,
                bgs = bgs_list,
                data = h_num,
                #data = None,
                syst = None,
                options=alloptions)

        if tfile:
            tfile.cd()
            channel = "Mu" if "Mu" in num else "El"
            histname = num.split("__")[1]
            data_fakerate = h_num.Clone(channel+"_"+histname+"_data_fakerate")
            qcd_fakerate  = bgs_list[0].Clone(channel+"_"+histname+"_qcd_fakerate")
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

    def plot(histnames, ps=0, sf=0):

        # Glob the file lists
    #    bkg_list_wjets  = glob.glob(output_dirpath+"/WJetsToLNu_Tune*.root")
    #    bkg_list_dy     = glob.glob(output_dirpath+"/DY*.root")
    #    bkg_list_ttbar  = glob.glob(output_dirpath+"/TTJets_Tune*.root")
    #    bkg_list_vv     = glob.glob(output_dirpath+"/WW*.root") + glob.glob(output_dirpath+"/WW*.root")
    #    bkg_list_qcd_mu = glob.glob(output_dirpath+"/QCD*MuEn*.root")
    #    bkg_list_qcd_el = glob.glob(output_dirpath+"/QCD*EMEn*.root")
    #    bkg_list_qcd_bc = glob.glob(output_dirpath+"/QCD*bcToE*.root")
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

        # Scale the histograms appropriately from SF from the EWKCR
        if sf > 0:
            h_wjets  .Scale(sf)
            h_dy     .Scale(sf)
            h_ttbar  .Scale(sf)
            h_vv     .Scale(sf)

        # If the data needs some additional correction for the prescale
        if ps > 0:
            h_data.Scale(ps)

        # Color settings
        colors = [ 2007, 2005, 2003, 2001, 920, 2 ]

        # Options
        alloptions= {
                    "ratio_range":[0.0,2.0],
                    "nbins": 30,
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "output_name": "plots/{}/{}/{}/plot/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", histnames),
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": False,
                    "yaxis_log": True if "ptcorr" in histnames else False,
                    #"yaxis_log": False,
                    "divide_by_bin_width": True,
                    "legend_smart": False if "ptcorr" in histnames else True,
                    "lumi_value" : 41.3,
                    }

        # The bkg histogram list
        bgs_list = [h_vv , h_ttbar , h_dy , h_wjets, h_qcd_mu ],
        bgs_list = [h_vv , h_ttbar , h_dy , h_wjets, h_qcd_mu ] if "Mu" in histnames else [h_vv , h_ttbar , h_dy , h_wjets, h_qcd_el ]

        legend_labels = ["VV", "t#bar{t}", "DY", "W", "QCD" ]

        # Plot them
        p.plot_hist(
                bgs = bgs_list,
                data = h_data.Clone("Data"),
                colors = colors,
                syst = None,
                legend_labels=legend_labels,
                options=alloptions)

        # Obtain the histogram again to return the object for further calculations

        # Data-driven QCD = data - bkg
        h_ddqcd  = ru.get_summed_histogram(data_list      , histnames)
        h_bkg    = ru.get_summed_histogram(bkg_list_all   , histnames)
        if ps > 0:
            h_ddqcd.Scale(ps)
        if sf > 0:
            h_bkg.Scale(sf)
        h_ddqcd.Add(h_bkg, -1)

        # MC QCD
        h_qcd_mu = ru.get_summed_histogram(bkg_list_qcd_mu, histnames).Clone("QCD(#mu)")
        h_qcd_el = ru.get_summed_histogram(bkg_list_qcd_el, histnames).Clone("QCD(EM)")
        h_qcd_bc = ru.get_summed_histogram(bkg_list_qcd_bc, histnames).Clone("QCD(HF)")

        return h_ddqcd, h_data, h_bkg, h_qcd_mu, h_qcd_el, h_qcd_bc

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
                    "lumi_value" : 41.3,
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

    def mu_fakerate():

        # Glob the file lists
        mcs  = [
            output_dirpath + "/wj_ht.root",
            output_dirpath + "/tt_1l.root",
            ]
        varname = "muptcorretarolledcoarse"
        num = "MuClosureTight__{}".format(varname)
        den = "MuClosureLoose__{}".format(varname)
        h_num = ru.get_summed_histogram(mcs , num)
        h_den = ru.get_summed_histogram(mcs , den)
        u.move_in_overflows(h_num)
        u.move_in_overflows(h_den)
        h_num.Divide(h_den)

        qcds  = [
            output_dirpath + "/qcd_mu.root",
            ]
        qcd_num = "OneMuTightMR__{}".format(varname)
        qcd_den = "OneMuMR__{}".format(varname)
        h_qcd_num = ru.get_summed_histogram(qcds , qcd_num)
        h_qcd_den = ru.get_summed_histogram(qcds , qcd_den)
        u.move_in_overflows(h_qcd_num)
        u.move_in_overflows(h_qcd_den)
        h_qcd_num.Divide(h_qcd_den)
        h_qcd_num.SetName("QCD(#mu)")

        # Color settings
        colors = [ 2005, 2001, ]

        # Options
        alloptions= {
                    "ratio_range":[0.0,2.0],
                    "nbins": 180,
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "output_name": "plots/{}/{}/{}/fakeratemc/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", num+"__"+den),
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "draw_points": True,
                    "lumi_value" : 41.3,
                    "legend_datalabel" : "W+t#bar{t}"
                    }

        # Plot them
        p.plot_hist(
                bgs = [h_qcd_num],
                data = h_num,
                colors = colors,
                syst = None,
                options=alloptions)

    def el_fakerate():

        # Glob the file lists
        mcs  = [
            output_dirpath + "/wj_ht.root",
            output_dirpath + "/tt_1l.root",
            ]
        num = "ElClosureTight__elptcorretarolledcoarse"
        den = "ElClosureLoose__elptcorretarolledcoarse"
        h_num = ru.get_summed_histogram(mcs , num)
        h_den = ru.get_summed_histogram(mcs , den)
        u.move_in_overflows(h_num)
        u.move_in_overflows(h_den)
        h_num.Divide(h_den)

        qcds  = [
            output_dirpath + "/qcd_em.root",
            output_dirpath + "/qcd_bc.root",
            ]
        qcd_num = "OneElTightMR__elptcorretarolledcoarse"
        qcd_den = "OneElMR__elptcorretarolledcoarse"
        h_qcd_num = ru.get_summed_histogram(qcds , qcd_num)
        h_qcd_den = ru.get_summed_histogram(qcds , qcd_den)
        u.move_in_overflows(h_qcd_num)
        u.move_in_overflows(h_qcd_den)
        h_qcd_num.Divide(h_qcd_den)
        h_qcd_num.SetName("QCD(e)")

        # Color settings
        colors = [ 2005, 2001, ]

        # Options
        alloptions= {
                    "ratio_range":[0.0,2.0],
                    "nbins": 180,
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "output_name": "plots/{}/{}/{}/fakeratemc/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", num+"__"+den),
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "draw_points": True,
                    "lumi_value" : 41.3,
                    "legend_datalabel" : "W+t#bar{t}"
                    }

        # Plot them
        p.plot_hist(
                bgs = [h_qcd_num],
                data = h_num,
                colors = colors,
                syst = None,
                options=alloptions)

    def mu_isos():
        mu_iso()
        mu_iso("Eta0Pt1")
        mu_iso("Eta0Pt2")
        mu_iso("Eta0Pt3")
        mu_iso("Eta1Pt1")
        mu_iso("Eta1Pt2")
        mu_iso("Eta1Pt3")

    def el_isos():
        el_iso()
        el_iso("Eta0Pt1")
        el_iso("Eta0Pt2")
        el_iso("Eta0Pt3")
        el_iso("Eta1Pt1")
        el_iso("Eta1Pt2")
        el_iso("Eta1Pt3")


    def mu_iso(binname=""):

        # Glob the file lists
        mcs  = [
            #output_dirpath + "/wj_incl.root",
            output_dirpath + "/wj_ht.root",
            output_dirpath + "/tt_1l.root",
            ]
        qcds  = [
            output_dirpath + "/qcd_mu.root",
            ]

        bkg_hist = "MuClosureLoose{}__muiso".format(binname)
        qcd_hist = "OneMuMR{}__iso".format(binname)

        h_bkg = ru.get_summed_histogram(mcs , bkg_hist)
        h_qcd = ru.get_summed_histogram(qcds, qcd_hist)

        h_bkg.Scale(1. / h_bkg.Integral())
        h_qcd.Scale(1. / h_qcd.Integral())

        h_qcd.SetName("QCD(#mu)")
        h_bkg.SetName("")

        # Color settings
        colors = [ 2001, ]

        # Options
        alloptions= {
                    "ratio_range":[0.0,2.0],
                    "nbins": 10,
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "output_name": "plots/{}/{}/{}/muiso/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", bkg_hist + "__" + qcd_hist),
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "draw_points": True,
                    "lumi_value" : 41.3,
                    "legend_datalabel": "W+t#bar{t}",
                    }

        # Plot them
        p.plot_hist(
                bgs = [h_qcd],
                data = h_bkg,
                colors = colors,
                syst = None,
                options=alloptions)

    def el_iso(binname=""):

        # Glob the file lists
        mcs  = [
            output_dirpath + "/wj_ht.root",
            output_dirpath + "/tt_1l.root",
            ]
        qcds  = [
            output_dirpath + "/qcd_em.root",
            output_dirpath + "/qcd_bc.root",
            ]

        bkg_hist = "ElClosureLoose{}__eliso".format(binname)
        qcd_hist = "OneElMR{}__iso".format(binname)

        h_bkg = ru.get_summed_histogram(mcs , bkg_hist)
        h_qcd = ru.get_summed_histogram(qcds, qcd_hist)
        h_qcd_em = ru.get_summed_histogram([output_dirpath + "/qcd_em.root"], qcd_hist)
        h_qcd_bc = ru.get_summed_histogram([output_dirpath + "/qcd_bc.root"], qcd_hist)

        h_bkg.Scale(1. / h_bkg.Integral())
        h_qcd.Scale(1. / h_qcd.Integral())
        h_qcd_em.Scale(1. / h_qcd_em.Integral())
        h_qcd_bc.Scale(1. / h_qcd_bc.Integral())

        h_qcd.SetName("QCD(e)")
        h_qcd_em.SetName("QCD(LF)")
        h_qcd_bc.SetName("QCD(HF)")

        # Color settings
        colors = [ 2001, ]

        # Options
        alloptions= {
                    "ratio_range":[0.0,2.0],
                    "nbins": 10,
                    "autobin": False,
                    "legend_scalex": 1.8,
                    "legend_scaley": 1.1,
                    "output_name": "plots/{}/{}/{}/eliso/{}.pdf".format(input_ntup_tag, analysis_tag, "ss" if isSS else "3l", bkg_hist + "__" + qcd_hist),
                    "bkg_sort_method": "unsorted",
                    "no_ratio": False,
                    "print_yield": True,
                    "yield_prec": 3,
                    "draw_points": True,
                    "lumi_value" : 41.3,
                    "legend_datalabel": "W+t#bar{t}",
                    }

        # Plot them
        p.plot_hist(
                sigs = [h_qcd_em, h_qcd_bc],
                bgs = [h_qcd],
                data = h_bkg,
                colors = colors,
                syst = None,
                options=alloptions)

    main()

if __name__ == "__main__":

    def help():
        print "Error - Usage:"
        print ""
        print "  $ python {} INPUT_NTUP_TAG ANALYSIS_TAG".format(sys.argv[0])
        print ""
        print "    INPUT_NTUP_TAG     input ntuple tag       (e.g. FR2017_v3.0.17)"
        print "    ANALYSIS_TAG       fake rate analysis tag (e.g. FR2017_analysis_v0.11.4)"
        print ""
        sys.exit()

    if len(sys.argv) == 1:
        input_ntup_tag = "FR2017_v3.0.17"
        analysis_tag = "FR2017_analysis_v1.0.0"
        print "Using default input and analysis tag"
        print "input_ntup_tag", input_ntup_tag
        print "analysis_tag", analysis_tag
    else:
        try:
            input_ntup_tag = sys.argv[1]
            analysis_tag = sys.argv[2]
        except:
            help()

    # Run the same-sign fake rate studies first
    grand_main(input_ntup_tag, analysis_tag, isSS=True)

    # Then run the three-lepton fake rate studies
    grand_main(input_ntup_tag, analysis_tag, isSS=False)

    print ""
    print ""
    print "=============================================="
    print "Wrote fake rate histograms to histmap/fakerate_ss.root"
    print "Also Wrote fake rate histograms to histmap/fakerate_3l.root"
    print "Same-sign fake rate study plots should be outputted at outputs/{}/{}/ss".format(input_ntup_tag, analysis_tag)
    print "Three-lepton fake rate studyplots should be outputted at outputs/{}/{}/3l".format(input_ntup_tag, analysis_tag)
    print "=============================================="
    print ""
    print ""

