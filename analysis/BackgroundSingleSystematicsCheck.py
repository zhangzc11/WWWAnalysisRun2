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

def getpathsig(short=True,year=-1):
    subpath = "mastersig/"
    if not short:
        subpath = "mastersigsyst/"
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


def getScaledNumbers(hists,systematic=""):
    addname = ""
    SRyield = []
    SRerr   = []
    SRyield.append(hists["SRSSeeMjjInFull" +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSSemMjjInFull" +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSSmmMjjInFull" +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSSeeMjjOutFull"+systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSSemMjjOutFull"+systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSSmmMjjOutFull"+systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSS1JeeFull"    +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSS1JemFull"    +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SRSS1JmmFull"    +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SR0SFOSFull"     +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SR1SFOSFull"     +systematic+"__yield"].GetBinContent(1))
    SRyield.append(hists["SR2SFOSFull"     +systematic+"__yield"].GetBinContent(1))
    SRerr.append(hists["SRSSeeMjjInFull" +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSSemMjjInFull" +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSSmmMjjInFull" +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSSeeMjjOutFull"+systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSSemMjjOutFull"+systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSSmmMjjOutFull"+systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSS1JeeFull"    +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSS1JemFull"    +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SRSS1JmmFull"    +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SR0SFOSFull"     +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SR1SFOSFull"     +systematic+"__yield"].GetBinError(1))
    SRerr.append(hists["SR2SFOSFull"     +systematic+"__yield"].GetBinError(1))
    return SRyield, SRerr

def printYieldsPlusUncertaintiesOneLine(SRid,centralYield,centralError,centralUp, centralDown,rel):
    name = ""
    if SRid ==  0: name = "ee, Mjj-in:  "
    if SRid ==  1: name = "em, Mjj-in:  "
    if SRid ==  2: name = "mm, Mjj-in:  "
    if SRid ==  3: name = "ee, Mjj-out: "
    if SRid ==  4: name = "em, Mjj-out: "
    if SRid ==  5: name = "mm, Mjj-out: "
    if SRid ==  6: name = "ee, 1j:      "
    if SRid ==  7: name = "em, 1j:      "
    if SRid ==  8: name = "mm, 1j:      "
    if SRid ==  9: name = "0 SFOS:      "
    if SRid == 10: name = "1 SFOS:      "
    if SRid == 11: name = "2 SFOS:      "

    if rel == True:
        return (name + st(centralYield[SRid]) + " +/- " + st(centralError[SRid]/centralYield[SRid]) + "(MCstat) + " + st((centralUp[SRid]-centralYield[SRid])/centralYield[SRid],"%.4f") + " - " + st((centralYield[SRid]-centralDown[SRid])/centralYield[SRid],"%.4f") + " (syst)")

    return (name + st(centralYield[SRid]) + " +/- " + st(centralError[SRid]) + "(MCstat) + " + st(centralUp[SRid]-centralYield[SRid]) + " - " + st(centralYield[SRid]-centralDown[SRid]) + " (syst)")
                

def printYieldsPlusUncertainties(centralYield,centralError,centralUp, centralDown,systematics,rel,sample):
    print("Tested systematics: " + systematics + " for sample " + sample)
    print(printYieldsPlusUncertaintiesOneLine( 0,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 1,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 2,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 3,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 4,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 5,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 6,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 7,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 8,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine( 9,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine(10,centralYield,centralError,centralUp, centralDown,rel))
    print(printYieldsPlusUncertaintiesOneLine(11,centralYield,centralError,centralUp, centralDown,rel))

def loadHistos(hists,fF,systematic):
    #print (fF.GetName())
    htemp = fF.Get("SRSSeeMjjInFull" +systematic+"__yield")
    hists["SRSSeeMjjInFull" +systematic+"__yield"] = htemp.Clone("SRSSeeMjjInFull" +systematic)
    htemp = fF.Get("SRSSemMjjInFull" +systematic+"__yield")
    hists["SRSSemMjjInFull" +systematic+"__yield"] = htemp.Clone("SRSSemMjjInFull" +systematic)
    htemp = fF.Get("SRSSmmMjjInFull" +systematic+"__yield")
    hists["SRSSmmMjjInFull" +systematic+"__yield"] = htemp.Clone("SRSSmmMjjInFull" +systematic)
    htemp = fF.Get("SRSSeeMjjOutFull" +systematic+"__yield")
    hists["SRSSeeMjjOutFull" +systematic+"__yield"] = htemp.Clone("SRSSeeMjjOutFull" +systematic)
    htemp = fF.Get("SRSSemMjjOutFull" +systematic+"__yield")
    hists["SRSSemMjjOutFull" +systematic+"__yield"] = htemp.Clone("SRSSemMjjOutFull" +systematic)
    htemp = fF.Get("SRSSmmMjjOutFull" +systematic+"__yield")
    hists["SRSSmmMjjOutFull" +systematic+"__yield"] = htemp.Clone("SRSSmmMjjOutFull" +systematic)
    htemp = fF.Get("SRSS1JeeFull" +systematic+"__yield")
    hists["SRSS1JeeFull" +systematic+"__yield"] = htemp.Clone("SRSS1JeeFull" +systematic)
    htemp = fF.Get("SRSS1JemFull" +systematic+"__yield")
    hists["SRSS1JemFull" +systematic+"__yield"] = htemp.Clone("SRSS1JemFull" +systematic)
    htemp = fF.Get("SRSS1JmmFull" +systematic+"__yield")
    hists["SRSS1JmmFull" +systematic+"__yield"] = htemp.Clone("SRSS1JmmFull" +systematic)
    htemp = fF.Get("SR0SFOSFull" +systematic+"__yield")
    hists["SR0SFOSFull" +systematic+"__yield"] = htemp.Clone("SR0SFOSFull" +systematic)
    htemp = fF.Get("SR1SFOSFull" +systematic+"__yield")
    hists["SR1SFOSFull" +systematic+"__yield"] = htemp.Clone("SR1SFOSFull" +systematic)
    htemp = fF.Get("SR2SFOSFull" +systematic+"__yield")
    hists["SR2SFOSFull" +systematic+"__yield"] = htemp.Clone("SR2SFOSFull" +systematic)

    return True


def st(myfloat=-.1,prc="%.3f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))


def getSystUncertainty(sample,systematics,rel=False,theyear=-1):
    pathdir = getpath(short=False,year=theyear)
    #print (pathdir+sample+".root")
    fF = ROOT.TFile.Open(pathdir+sample+".root")
    hists = dict()
    loadHistos(hists,fF,"")
    loadHistos(hists,fF,systematics+"Up")
    loadHistos(hists,fF,systematics+"Down")
    centralYield, centralError = getScaledNumbers(hists,"")
    centralUp, dummyup = getScaledNumbers(hists,systematics+"Up")
    centralDown, dummydown = getScaledNumbers(hists,systematics+"Down")
    printYieldsPlusUncertainties(centralYield,centralError,centralUp, centralDown,systematics,rel,sample)
    return True

def getSystSigUncertainty(sample,systematics,rel=False,theyear=-1):
    pathdir = getpathsig(short=False,year=theyear)
    #print (pathdir+sample+".root")
    fF = ROOT.TFile.Open(pathdir+sample+".root")
    hists = dict()
    loadHistos(hists,fF,"")
    loadHistos(hists,fF,systematics+"Up")
    loadHistos(hists,fF,systematics+"Down")
    centralYield, centralError = getScaledNumbers(hists,"")
    centralUp, dummyup = getScaledNumbers(hists,systematics+"Up")
    centralDown, dummydown = getScaledNumbers(hists,systematics+"Down")
    printYieldsPlusUncertainties(centralYield,centralError,centralUp, centralDown,systematics,rel,sample)
    return True


getSystUncertainty("ttw","BTagHF")
getSystUncertainty("ttw","BTagLF")

#getSystSigUncertainty("www_all","LepSF")
#getSystSigUncertainty("www_all","EleSF")
#getSystSigUncertainty("www_all","MuoSF")
#getSystSigUncertainty("www_all","LepSF",True)
#getSystSigUncertainty("www_all","EleSF",True)
#getSystSigUncertainty("www_all","MuoSF",True)

