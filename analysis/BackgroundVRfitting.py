import ROOT
import math

# need to test how RooFit works for python, else just make histograms and do it in a C root macro
# implement fits for
# - ttZ vs. WZ vs. rest using ttZWZfitRegion__nb (for WZ need to remove ttz.root from lostlep.root)
#   * consider split by years
#
# - gamma fakes vs everything else using GammaCRLowMT__M3l, GammaCRLowPt3lMT__M3l, GammaCRLowPt3l__M3l, try also  GammaCRLowMT__DPhi3lMET, GammaCRLowPt3lMT__DPhi3lMET, GammaCRLowPt3l__DPhi3lMET
#   * split by years
#
# - WWjj vs. everything using WWVBSVRHighMJJ__DetajjL and WWVBSVRHighDEta__MjjLDetajjL
#
# - ttW vs. everything using ttWVRmNBgeq1__nb
#   * split by years
#
#
# get ratios
# - Mjj in/out using WZCRSSnoZmassKinSel__Mjj
#
# - Mll in/Mll including for SS using WZCRSSnoZmassKinSel__MllOnOff
#
# - Mll in/out for WZCR3LnoZmassKinSelInvertAll__MllOnOff, WZCR3LnoZmassKinSelInvertDPhi__MllOnOff, WZCR3LnoZmassKinSelInvertExOne__MllOnOff, WZCR3LnoZmassKinSelInvertMTmax__MllOnOff, WZCR3LnoZmassKinSelInvertPt3l__MllOnOff, WZCRSS1JnoZcand1JKin__MllOnOff
#
#   * compare iwht Mll in/out using WZCR1SFOSFull/WZCR2SFOSFull and SR1SFOSFull/SR2SFOSFull simulation
#
#
# do systematics variations for ratios of WZCR*Full and SR*Full of LepSF, TrigSF, Pileup, PDF, Qsq, JES for SS2j case

def getpath(short=True,year=-1):
    subpath = "master/"
    if not short:
        subpath = "mastersyst/"
    versionpath = "_v5.3.3/"
    typepath = "Loose"
    prepath = "hists/combineyears"+typepath+versionpath
    if year == 2016:
        prepath = "hists/"+typepath+"2016" + versionpath
    if year == 2017:
        prepath = "hists/"+typepath+"2017" + versionpath
    if year == 2018:
        prepath = "hists/"+typepath+"2018"+ versionpath
    return prepath + subpath


def loadfiles(mydir="",isshort=True,theyear=-1):
    pathdir = mydir
    if mydir == "":
        pathdir = getpath(isshort,theyear)
    fS    = ROOT.TFile.Open(pathdir+"signal.root")
    fwww  = ROOT.TFile.Open(pathdir+"www.root")
    fwh   = ROOT.TFile.Open(pathdir+"vh_private.root")
    fwwz  = ROOT.TFile.Open(pathdir+"wwz.root")
    fwzz  = ROOT.TFile.Open(pathdir+"wzz.root")
    fzzz  = ROOT.TFile.Open(pathdir+"zzz.root")
    fP    = ROOT.TFile.Open(pathdir+"prompt.root")
    fL    = ROOT.TFile.Open(pathdir+"lostlep.root")
    fF    = ROOT.TFile.Open(pathdir+"fakes.root")
    fFdd  = ROOT.TFile.Open(pathdir+"ddfakes.root")
    fQ    = ROOT.TFile.Open(pathdir+"qflip.root")
    fG    = ROOT.TFile.Open(pathdir+"photon.root")
    fD    = ROOT.TFile.Open(pathdir+"data.root")
    ffP   = ROOT.TFile.Open(pathdir+"fitprompt.root")
    ffL   = ROOT.TFile.Open(pathdir+"fitlostlep.root")
    ffF   = ROOT.TFile.Open(pathdir+"fitfakes.root")
    #ffFdd = ROOT.TFile.Open(pathdir+"fitddfakes.root")
    ffQ   = ROOT.TFile.Open(pathdir+"fitqflip.root")
    ffG   = ROOT.TFile.Open(pathdir+"fitphoton.root")
    fvbs  = ROOT.TFile.Open(pathdir+"vbs.root")
    fttw  = ROOT.TFile.Open(pathdir+"ttw.root")
    fttz  = ROOT.TFile.Open(pathdir+"ttz.root")
    filedict = dict()
    filedict["signal"]     = fS
    filedict["www"]        = fwww
    filedict["wh"]         = fwh
    filedict["wwz"]        = fwwz
    filedict["wzz"]        = fwzz
    filedict["zzz"]        = fzzz
    filedict["prompt"]     = fP
    filedict["lostlep"]    = fL
    filedict["fakes"]      = fF
    filedict["ddfakes"]    = fFdd
    filedict["qflip"]      = fQ
    filedict["photon"]     = fG
    filedict["data"]       = fD
    filedict["fitprompt"]  = ffP
    filedict["fitlostlep"] = ffL
    filedict["fitfakes"]   = ffF
    #filedict["fitddfakes"] = ffFdd
    filedict["fitqflip"]   = ffQ
    filedict["fitphoton"]  = ffG
    filedict["vbs"]        = fvbs
    filedict["ttw"]        = fttw
    filedict["ttz"]        = fttz
    return filedict


# - ttZ vs. WZ vs. rest using ttZWZfitRegion__nb (for WZ need to remove ttz.root from lostlep.root)
#   * consider split by years
def ttZWZfit(year=-1):
    histoname = "ttZWZfitRegion__nb"
    files = loadfiles(theyear=year)
    htemp = files["data"].Get(histoname)
    hdata = htemp.Clone(histoname+"Data")
    htemp = files["fitlostlep"].Get(histoname)
    hLL   = htemp.Clone(histoname+"LL")
    htemp = files["ttz"].Get(histoname)
    httz  = htemp.Clone(histoname+"ttz")
    hLL.Add(httz,-1.)
    htemp = files["fitprompt"].Get(histoname)
    hother= htemp.Clone(histoname+"Other")
    htemp = files["ddfakes"].Get(histoname)
    #htemp = files["fitfakes"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["fitqflip"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["fitphoton"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["vbs"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["ttw"].Get(histoname)
    hother.Add(htemp,1.)
    hLL.SetLineWidth(3)
    hLL.SetLineColor(ROOT.kMagenta)
    hLL.SetMarkerColor(ROOT.kMagenta)
    httz.SetLineWidth(3)
    httz.SetLineColor(ROOT.kRed)
    httz.SetMarkerColor(ROOT.kRed)
    hother.SetLineWidth(3)
    hother.SetLineColor(ROOT.kBlue)
    hother.SetMarkerColor(ROOT.kBlue)
    hdata.SetLineWidth(2)
    hdata.SetLineColor(ROOT.kBlack)
    hdata.SetMarkerColor(ROOT.kBlack)
    hdata.SetMarkerStyle(20)

    #w = ROOT.RooWorkspace()
    nb = ROOT.RooRealVar("nb","nb",0.,5.)
    Data  = ROOT.RooDataHist("data"  ,"data"  ,ROOT.RooArgList(nb),hdata ,1.)
    LL    = ROOT.RooDataHist("WZ"    ,"WZ"    ,ROOT.RooArgList(nb),hLL   ,1.)
    ttZ   = ROOT.RooDataHist("ttZ"   ,"ttZ"   ,ROOT.RooArgList(nb),httz  ,1.)
    Other = ROOT.RooDataHist("Other" ,"Other" ,ROOT.RooArgList(nb),hother,1.)
    LL_pdf    = ROOT.RooHistPdf("WZ_pdf"     ,"WZ_pdf"     ,ROOT.RooArgSet(nb),LL     ,0)
    ttZ_pdf   = ROOT.RooHistPdf("ttZ_pdf"    ,"ttZ_pdf"    ,ROOT.RooArgSet(nb),ttZ    ,0)
    Other_pdf = ROOT.RooHistPdf("Other_pdf"  ,"other_pdf"  ,ROOT.RooArgSet(nb),Other  ,0)
    nLL    = ROOT.RooRealVar("nwz"    ,"number of WZ events",         hLL.Integral()   ,  hLL.Integral()   *0.1, hLL.Integral()   *1.9)
    nttz   = ROOT.RooRealVar("nttz"   ,"number of ttZ events",        httz.Integral()  ,  httz.Integral()  *0.1, httz.Integral()  *1.9)
    nother = ROOT.RooRealVar("nother" ,"number of Other SM events",   hother.Integral(),  hother.Integral()*0.1, hother.Integral()*1.9) 
    model = ROOT.RooAddPdf("model","model", ROOT.RooArgList(LL_pdf,ttZ_pdf,Other_pdf), ROOT.RooArgList(nLL, nttz, nother));
    fitres = ROOT.RooFitResult()
    fitres.SetName("fitres")
    fitres = model.fitTo(Data)
    #fitres = model.fitTo(Data,ROOT.RooCmdArg.SumW2Error(ROOT.kFALSE),ROOT.RooCmdArg.Extended(), ROOT.RooCmdArg.Save(ROOT.kTRUE))

    err = ROOT.Double()
    prc = "%.3f"
    print("Data  value = "+str(prc % hdata.IntegralAndError(1,hdata.GetNbinsX(),err))+" +/- "+str(prc % err))
    print("WZ    value = "+str(prc %    nLL.getVal())+" +/- "+str(prc %    nLL.getError())+", WZ    SF ="+str(prc %  (   nLL.getVal()/    hLL.Integral()))+" +/- "+str(prc % (   nLL.getError()/      hLL.Integral())))
    print("ttZ   value = "+str(prc %   nttz.getVal())+" +/- "+str(prc %   nttz.getError())+", WZ    SF ="+str(prc %  (  nttz.getVal()/   httz.Integral()))+" +/- "+str(prc % (  nttz.getError()/     httz.Integral())))
    print("Other value = "+str(prc % nother.getVal())+" +/- "+str(prc % nother.getError())+", WZ    SF ="+str(prc %  (nother.getVal()/ hother.Integral()))+" +/- "+str(prc % (nother.getError()/   hother.Integral())))
    savestring = getpath(year=year)
    hLL.Scale(      nLL.getVal()/    hLL.Integral())
    httz.Scale(    nttz.getVal()/   httz.Integral())
    hother.Scale(nother.getVal()/ hother.Integral())
    hsum = hLL.Clone(histoname+"Sum")
    hsum.Add(httz,1.)
    hsum.Add(hother,1.)
    hsum.SetLineWidth(3)
    hsum.SetLineColor(ROOT.kGreen+1)
    hsum.SetMarkerColor(ROOT.kGreen+1)
    fout = ROOT.TFile(savestring+"ttZvsWZfit.root","recreate")
    model.Write()
    #fitres.Write()
    hdata.Write()
    hLL.Write()
    httz.Write()
    hother.Write()
    hsum.Write()
    fout.Close()
    print("Wrote results in "+savestring+"ttZvsWZfit.root")
    return True




# - gamma fakes vs everything else using GammaCRLowMT__M3l, GammaCRLowPt3lMT__M3l, GammaCRLowPt3l__M3l, try also  GammaCRLowMT__DPhi3lMET, GammaCRLowPt3lMT__DPhi3lMET, GammaCRLowPt3l__DPhi3lMET
#   * split by years
#
def gammafit(year=-1,histname=""):
    #histoname = "GammaCRLowPt3lMT__M3l"
    histoname = "GammaCRLowPt3lMT__M3l"
    if histname != "":
        histoname = histname
    files = loadfiles(theyear=year)
    htemp = files["data"].Get(histoname)
    hdata = htemp.Clone(histoname+"Data")
    htemp = files["lostlep"].Get(histoname)
    hother   = htemp.Clone(histoname+"Other")
    htemp = files["prompt"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["ddfakes"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["qflip"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["photon"].Get(histoname)
    hphoton= htemp.Clone(histoname+"Gamma")
    hother.SetLineWidth(3)
    hother.SetLineColor(ROOT.kRed)
    hother.SetMarkerColor(ROOT.kRed)
    hphoton.SetLineWidth(3)
    hphoton.SetLineColor(ROOT.kBlue)
    hphoton.SetMarkerColor(ROOT.kBlue)
    hdata.SetLineWidth(2)
    hdata.SetLineColor(ROOT.kBlack)
    hdata.SetMarkerColor(ROOT.kBlack)
    hdata.SetMarkerStyle(20)
    #hphoton.Rebin(6)
    #hother.Rebin(6)
    #hdata.Rebin(6)

    #w = ROOT.RooWorkspace()
    nb = ROOT.RooRealVar()
    if "DPhi3lMET" in histoname:
        nb = ROOT.RooRealVar("nb","nb",0.,3.2)
    else:
        nb = ROOT.RooRealVar("nb","nb",30.,150.)
    Data  = ROOT.RooDataHist("data"  ,"data"  ,ROOT.RooArgList(nb),hdata ,1.)
    Gamma = ROOT.RooDataHist("Gamma" ,"Gamma" ,ROOT.RooArgList(nb),hphoton,1.)
    Other = ROOT.RooDataHist("Other" ,"Other" ,ROOT.RooArgList(nb),hother,1.)
    Gamma_pdf = ROOT.RooHistPdf("Gamma_pdf"  ,"Gamma_pdf"  ,ROOT.RooArgSet(nb),Gamma  ,0)
    Other_pdf = ROOT.RooHistPdf("Other_pdf"  ,"other_pdf"  ,ROOT.RooArgSet(nb),Other  ,0)
    nGamma = ROOT.RooRealVar("ngamma" ,"number of photon events",    hphoton.Integral(), hphoton.Integral()*0.1,hphoton.Integral()*1.9)
    nother = ROOT.RooRealVar("nother" ,"number of Other SM events",   hother.Integral(),  hother.Integral()*0.7, hother.Integral()*1.3) 
    model = ROOT.RooAddPdf("model","model", ROOT.RooArgList(Gamma_pdf,Other_pdf), ROOT.RooArgList(nGamma, nother));
    fitres = ROOT.RooFitResult()
    fitres.SetName("fitres")
    fitres = model.fitTo(Data)
    #fitres = model.fitTo(Data,ROOT.RooCmdArg.SumW2Error(ROOT.kFALSE),ROOT.RooCmdArg.Extended(), ROOT.RooCmdArg.Save(ROOT.kTRUE))

    err = ROOT.Double()
    prc = "%.3f"
    print("Data  value = "+str(prc % hdata.IntegralAndError(1,hdata.GetNbinsX(),err))+" +/- "+str(prc % err))
    print("Gamma value = "+str(prc %nGamma.getVal())+" +/- "+str(prc %nGamma.getError())+", WZ    SF ="+str(prc %  (nGamma.getVal()/hphoton.Integral()))+" +/- "+str(prc % (nGamma.getError()/hphoton.Integral())))
    print("Other value = "+str(prc % nother.getVal())+" +/- "+str(prc % nother.getError())+", WZ    SF ="+str(prc %  (nother.getVal()/ hother.Integral()))+" +/- "+str(prc % (nother.getError()/   hother.Integral())))
    savestring = getpath(year=year)
    hphoton.Scale(  nGamma.getVal()/hphoton.Integral())
    hother.Scale(nother.getVal()/ hother.Integral())
    hsum = hphoton.Clone(histoname+"Sum")
    hsum.Add(hother,1.)
    hsum.SetLineWidth(3)
    hsum.SetLineColor(ROOT.kGreen+1)
    hsum.SetMarkerColor(ROOT.kGreen+1)
    fout = ROOT.TFile(savestring+"PhotonFakeFit.root","recreate")
    model.Write()
    #fitres.Write()
    hdata.Write()
    hphoton.Write()
    hother.Write()
    hsum.Write()
    fout.Close()
    print("Wrote results in "+savestring+"PhotonFakeFit.root with the histogram "+histoname)
    return True

# - WWjj vs. everything using WWVBSVRHighMJJ__DetajjL and WWVBSVRHighDEta__MjjL
def WWVBSfit(year=-1,histname=""):
    histoname = "WWVBSVRHighMJJ__DetajjL"
    if histname != "":
        histoname = histname
    files = loadfiles(theyear=year)
    htemp = files["data"].Get(histoname)
    hdata = htemp.Clone(histoname+"Data")
    htemp = files["fitlostlep"].Get(histoname)
    hother= htemp.Clone(histoname+"LL")
    htemp = files["fitprompt"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["ddfakes"].Get(histoname)
    #htemp = files["fitfakes"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["fitqflip"].Get(histoname)
    hother.Add(htemp,1.)
    #htemp = files["fitphoton"].Get(histoname)
    #hother.Add(htemp,1.)
    htemp = files["vbs"].Get(histoname)
    hvbs  = htemp.Clone(histoname+"vbs")
    htemp = files["ttw"].Get(histoname)
    hother.Add(htemp,1.)
    hother.SetLineWidth(3)
    hother.SetLineColor(ROOT.kRed)
    hother.SetMarkerColor(ROOT.kRed)
    hvbs.SetLineWidth(3)
    hvbs.SetLineColor(ROOT.kBlue)
    hvbs.SetMarkerColor(ROOT.kBlue)
    hdata.SetLineWidth(2)
    hdata.SetLineColor(ROOT.kBlack)
    hdata.SetMarkerColor(ROOT.kBlack)
    hdata.SetMarkerStyle(20)

    #w = ROOT.RooWorkspace()
    nb = ROOT.RooRealVar()
    if "DetajjL" in histoname:
        nb = ROOT.RooRealVar("nb","nb",0.,5.)
    else:
        nb = ROOT.RooRealVar("nb","nb",0.,750.)
    Data  = ROOT.RooDataHist("data"  ,"data"  ,ROOT.RooArgList(nb),hdata ,1.)
    VBS   = ROOT.RooDataHist("Gamma" ,"Gamma" ,ROOT.RooArgList(nb),  hvbs,1.)
    Other = ROOT.RooDataHist("Other" ,"Other" ,ROOT.RooArgList(nb),hother,1.)
    VBS_pdf   = ROOT.RooHistPdf(  "VBS_pdf"  ,  "VBS_pdf"  ,ROOT.RooArgSet(nb),VBS    ,0)
    Other_pdf = ROOT.RooHistPdf("Other_pdf"  ,"other_pdf"  ,ROOT.RooArgSet(nb),Other  ,0)
    nVBS   = ROOT.RooRealVar("nVBS"   ,"number of photon events",       hvbs.Integral(),    hvbs.Integral()*0.1,   hvbs.Integral()*1.9)
    nother = ROOT.RooRealVar("nother" ,"number of Other SM events",   hother.Integral(),  hother.Integral()*0.7, hother.Integral()*1.3) 
    model = ROOT.RooAddPdf("model","model", ROOT.RooArgList(VBS_pdf,Other_pdf), ROOT.RooArgList(nVBS, nother));
    fitres = ROOT.RooFitResult()
    fitres.SetName("fitres")
    fitres = model.fitTo(Data)
    #fitres = model.fitTo(Data,ROOT.RooCmdArg.SumW2Error(ROOT.kFALSE),ROOT.RooCmdArg.Extended(), ROOT.RooCmdArg.Save(ROOT.kTRUE))

    err = ROOT.Double()
    prc = "%.3f"
    print("Data  value = "+str(prc % hdata.IntegralAndError(1,hdata.GetNbinsX(),err))+" +/- "+str(prc % err))
    print("VBS   value = "+str(prc %nVBS.getVal())+" +/- "+str(prc %nVBS.getError())+  ", VBS   SF ="+str(prc %  (nVBS.getVal()/hvbs.Integral()))+" +/- "+str(prc % (nVBS.getError()/hvbs.Integral())))
    print("Other value = "+str(prc % nother.getVal())+" +/- "+str(prc % nother.getError())+", Other SF ="+str(prc %  (nother.getVal()/ hother.Integral()))+" +/- "+str(prc % (nother.getError()/   hother.Integral())))
    savestring = getpath(year=year)
    hvbs.Scale(  nVBS.getVal()/hvbs.Integral())
    hother.Scale(nother.getVal()/ hother.Integral())
    hsum = hvbs.Clone(histoname+"Sum")
    hsum.Add(hother,1.)
    hsum.SetLineWidth(3)
    hsum.SetLineColor(ROOT.kGreen+1)
    hsum.SetMarkerColor(ROOT.kGreen+1)
    fout = ROOT.TFile(savestring+"VBSFit.root","recreate")
    model.Write()
    #fitres.Write()
    hdata.Write()
    hvbs.Write()
    hother.Write()
    hsum.Write()
    fout.Close()
    print("Wrote results in "+savestring+"VBSFit.root with the histogram "+histoname)
    return True

# - ttW vs. everything using ttWVRmNBgeq1__nb
#   * split by years
def ttXfit(year=-1,histname=""):
    histoname = "ttWVRlNBgeq1__nb"
    #histoname = "ttWVRlNBgeq1BTagLFUp__nb"
    if histname != "":
        histoname = histname
    files = loadfiles(theyear=year,isshort=True)
    htemp = files["data"].Get(histoname)
    hdata = htemp.Clone(histoname+"Data")
    htemp = files["fitlostlep"].Get(histoname)
    hother= htemp.Clone(histoname+"Other")
    htemp = files["fitprompt"].Get(histoname)
    httX  = htemp.Clone(histoname+"ttX")
    htemp = files["ddfakes"].Get(histoname)
    #htemp = files["fitfakes"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["fitqflip"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["fitphoton"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["vbs"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["ttw"].Get(histoname)
    httX.Add(htemp,1.)
    hother.SetLineWidth(3)
    hother.SetLineColor(ROOT.kRed)
    hother.SetMarkerColor(ROOT.kRed)
    httX.SetLineWidth(3)
    httX.SetLineColor(ROOT.kBlue)
    httX.SetMarkerColor(ROOT.kBlue)
    hdata.SetLineWidth(2)
    hdata.SetLineColor(ROOT.kBlack)
    hdata.SetMarkerColor(ROOT.kBlack)
    hdata.SetMarkerStyle(20)

    #w = ROOT.RooWorkspace()
    nb = ROOT.RooRealVar("nb","nb",0.,5.)
    Data  = ROOT.RooDataHist("data"  ,"data"  ,ROOT.RooArgList(nb),hdata ,1.)
    ttX   = ROOT.RooDataHist("ttX"   ,"ttX"   ,ROOT.RooArgList(nb),  httX,1.)
    Other = ROOT.RooDataHist("Other" ,"Other" ,ROOT.RooArgList(nb),hother,1.)
    ttX_pdf   = ROOT.RooHistPdf(  "ttX_pdf"  ,  "ttX_pdf"  ,ROOT.RooArgSet(nb),ttX    ,0)
    Other_pdf = ROOT.RooHistPdf("Other_pdf"  ,"other_pdf"  ,ROOT.RooArgSet(nb),Other  ,0)
    nttX   = ROOT.RooRealVar("nttX"   ,"number of ttX events",       httX.Integral(),    httX.Integral()*0.1,   httX.Integral()*1.9)
    nother = ROOT.RooRealVar("nother" ,"number of Other SM events",   hother.Integral(),  hother.Integral()*0.7, hother.Integral()*1.3) 
    model = ROOT.RooAddPdf("model","model", ROOT.RooArgList(ttX_pdf,Other_pdf), ROOT.RooArgList(nttX, nother));
    fitres = ROOT.RooFitResult()
    fitres.SetName("fitres")
    fitres = model.fitTo(Data)
    #fitres = model.fitTo(Data,ROOT.RooCmdArg.SumW2Error(ROOT.kFALSE),ROOT.RooCmdArg.Extended(), ROOT.RooCmdArg.Save(ROOT.kTRUE))

    err = ROOT.Double()
    prc = "%.3f"
    print("Data  value = "+str(prc % hdata.IntegralAndError(1,hdata.GetNbinsX(),err))+" +/- "+str(prc % err))
    print("ttX   value = "+str(prc %nttX.getVal())+" +/- "+str(prc %nttX.getError())+  ", ttX   SF ="+str(prc %  (nttX.getVal()/httX.Integral()))+" +/- "+str(prc % (nttX.getError()/httX.Integral())))
    print("Other value = "+str(prc % nother.getVal())+" +/- "+str(prc % nother.getError())+", Other SF ="+str(prc %  (nother.getVal()/ hother.Integral()))+" +/- "+str(prc % (nother.getError()/   hother.Integral())))
    savestring = getpath(year=year)
    httX.Scale(  nttX.getVal()/httX.Integral())
    hother.Scale(nother.getVal()/ hother.Integral())
    hsum = httX.Clone(histoname+"Sum")
    hsum.Add(hother,1.)
    hsum.SetLineWidth(3)
    hsum.SetLineColor(ROOT.kGreen+1)
    hsum.SetMarkerColor(ROOT.kGreen+1)
    fout = ROOT.TFile(savestring+"ttWttHFit.root","recreate")
    model.Write()
    #fitres.Write()
    hdata.Write()
    httX.Write()
    hother.Write()
    hsum.Write()
    fout.Close()
    print("Wrote results in "+savestring+"ttWttHFit.root with the histogram "+histoname)
    return True

# - WWjj vs. everything using WWVBSVRHighMJJ__DetajjL and WWVBSVRHighDEta__MjjL
def QFlipfit(year=-1,histname=""):
    histoname = "SRSSee__MllZ"
    if histname != "":
        histoname = histname
    files = loadfiles(theyear=year)
    htemp = files["data"].Get(histoname)
    hdata = htemp.Clone(histoname+"Data")
    htemp = files["lostlep"].Get(histoname)
    hother   = htemp.Clone(histoname+"Other")
    htemp = files["prompt"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["ddfakes"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["photon"].Get(histoname)
    hother.Add(htemp,1.)
    htemp = files["qflip"].Get(histoname)
    hqflip= htemp.Clone(histoname+"Qlip")
  
    hother.SetLineWidth(3)
    hother.SetLineColor(ROOT.kRed)
    hother.SetMarkerColor(ROOT.kRed)
    hqflip.SetLineWidth(3)
    hqflip.SetLineColor(ROOT.kBlue)
    hqflip.SetMarkerColor(ROOT.kBlue)
    hdata.SetLineWidth(2)
    hdata.SetLineColor(ROOT.kBlack)
    hdata.SetMarkerColor(ROOT.kBlack)
    hdata.SetMarkerStyle(20)

    #w = ROOT.RooWorkspace()
    #nb = ROOT.RooRealVar()
    nb = ROOT.RooRealVar("nb","nb",60.,120.)
    Data  = ROOT.RooDataHist("data"  ,"data"  ,ROOT.RooArgList(nb),hdata ,1.)
    qflip = ROOT.RooDataHist("QFlip" ,"QFlip" ,ROOT.RooArgList(nb),hqflip,1.)
    Other = ROOT.RooDataHist("Other" ,"Other" ,ROOT.RooArgList(nb),hother,1.)
    qflip_pdf   = ROOT.RooHistPdf(  "qflip_pdf"  ,  "qflip_pdf"  ,ROOT.RooArgSet(nb),qflip   ,0)
    Other_pdf = ROOT.RooHistPdf("Other_pdf"  ,"other_pdf"  ,ROOT.RooArgSet(nb),Other  ,0)
    nqflip = ROOT.RooRealVar("nqflip"   ,"number of charge flip events",       hqflip.Integral(),    hqflip.Integral()*0.1,   hqflip.Integral()*1.9)
    nother = ROOT.RooRealVar("nother" ,"number of Other SM events",   hother.Integral(),  hother.Integral()*0.5, hother.Integral()*1.5) 
    model = ROOT.RooAddPdf("model","model", ROOT.RooArgList(qflip_pdf,Other_pdf), ROOT.RooArgList(nqflip, nother));
    fitres = ROOT.RooFitResult()
    fitres.SetName("fitres")
    fitres = model.fitTo(Data)
    #fitres = model.fitTo(Data,ROOT.RooCmdArg.SumW2Error(ROOT.kFALSE),ROOT.RooCmdArg.Extended(), ROOT.RooCmdArg.Save(ROOT.kTRUE))

    err = ROOT.Double()
    prc = "%.3f"
    print("Data  value = "+str(prc % hdata.IntegralAndError(1,hdata.GetNbinsX(),err))+" +/- "+str(prc % err))
    print("QFlip value = "+str(prc %nqflip.getVal())+" +/- "+str(prc %nqflip.getError())+  ", QFlip SF ="+str(prc %  (nqflip.getVal()/hqflip.Integral()))+" +/- "+str(prc % (nqflip.getError()/hqflip.Integral())))
    print("Other value = "+str(prc % nother.getVal())+" +/- "+str(prc % nother.getError())+", Other SF ="+str(prc %  (nother.getVal()/ hother.Integral()))+" +/- "+str(prc % (nother.getError()/   hother.Integral())))
    savestring = getpath(year=year)
    hqflip.Scale(  nqflip.getVal()/hqflip.Integral())
    hother.Scale(nother.getVal()/ hother.Integral())
    hsum = hqflip.Clone(histoname+"Sum")
    hsum.Add(hother,1.)
    hsum.SetLineWidth(3)
    hsum.SetLineColor(ROOT.kGreen+1)
    hsum.SetMarkerColor(ROOT.kGreen+1)
    fout = ROOT.TFile(savestring+"QFlipFit.root","recreate")
    model.Write()
    #fitres.Write()
    hdata.Write()
    hqflip.Write()
    hother.Write()
    hsum.Write()
    fout.Close()
    print("Wrote results in "+savestring+"QFlipFit.root with the histogram "+histoname)
    return True


#ttZWZfit() #do ttZ vs. WZ fit
#ttZWZfit(year=2016) #do ttZ vs. WZ fit
#ttZWZfit(year=2017) #do ttZ vs. WZ fit
#ttZWZfit(year=2018) #do ttZ vs. WZ fit

#gammafit(histname="GammaCRLowMT__M3l")
#gammafit(histname="GammaCRLowPt3lMT__M3l")
#gammafit(histname="GammaCRLowPt3l__M3l")
#gammafit(histname="GammaCRLowMT__DPhi3lMET")
#gammafit(histname="GammaCRLowPt3lMT__DPhi3lMET")
#gammafit(histname="GammaCRLowPt3l__DPhi3lMET")
#gammafit()
#gammafit(year=2016)
#gammafit(year=2017)
#gammafit(year=2018)

#WWVBSfit(histname="WWVBSVRHighDEta__MjjL")
#WWVBSfit(histname="WWVBSVRHighMJJ__DetajjL")
#WWVBSfit()
#WWVBSfit(year=2016)
#WWVBSfit(year=2017)
#WWVBSfit(year=2018)
#WWVBSfit(histname="WWVBSVR__MjjL")
#WWVBSfit(histname="WWVBSVR__DetajjL")

#ttXfit(year=2016)
#ttXfit(year=2017)
#ttXfit(year=2018)
#ttXfit()

QFlipfit()
