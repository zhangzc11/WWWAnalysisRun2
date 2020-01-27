import ROOT
import math

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
#
# also change WZ by 0.9 and ttZ by 1.2 and see impact on SF

def statErrorN(x):
    return x - 0.5*ROOT.TMath.ChisquareQuantile(  0.3173/2,2* x   )
def statErrorP(x):
    return     0.5*ROOT.TMath.ChisquareQuantile(1-0.3173/2,2*(x+1))-x



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

def getTF(h1=ROOT.TH1F(),h2=ROOT.TH1F()):
    if "MllOnOff" in h1.GetName():
        lowborder = 91.1876 - 20.
        hghborder = 91.1876 + 20.
        errl = ROOT.Double()
        onerr = ROOT.Double()
        errh = ROOT.Double()
        binl = h1.FindBin(lowborder)
        binh = h1.FindBin(hghborder)
        lowyield = h1.IntegralAndError(0,binl,errl)#add underflow
        onyield = h1.IntegralAndError(binl+1,binh-1,onerr)
        hghyield = h1.IntegralAndError(binh,h1.GetNbinsX()+1,errh)#add overflow
        offyield = lowyield+hghyield
        offerr = math.sqrt(errl*errl + errh*errh)
        #print(h1.GetName(),lowyield,onyield,hghyield,offyield)
        if offyield < 0 or onyield <= 0:
            return -1.,-1.
        if ("3L" in h1.GetName()) or ("SFOS" in h1.GetName()):
            TF = offyield/onyield
            TFerr = math.sqrt(pow(offerr/onyield,2)+pow((offyield*onerr)/(onyield*onyield),2))
            return TF,TFerr
        elif "SS" in h1.GetName():
            TF = onyield/(onyield+offyield)
            TFerr = math.sqrt(pow((onerr*offyield)/pow(onyield+offyield,2),2)+pow((onyield*offerr)/pow(onyield+offyield,2),2))
            return TF,TFerr
    elif h1.GetName() != '' and h2.GetName() != '':  #assume this is SRyield in h1 and CR yield in h2
        err1 = ROOT.Double()
        err2 = ROOT.Double()
        yield1 = h1.IntegralAndError(0,h1.GetNbinsX()+1,err1)#add under/overflow
        yield2 = h2.IntegralAndError(0,h2.GetNbinsX()+1,err2)#add under/overflow
        if yield1 < 0 or yield2<=0:
            return -1.,-1.     
        TF = yield1/yield2
        TFerr = math.sqrt(pow(err1/yield2,2)+pow((yield1*err2)/(yield2*yield2),2))
        return TF, TFerr
    else:
        return -1.,-1.

def getdoubleTF(h1=ROOT.TH1F()):
        if ( not ( "__Mjj_" in h1.GetName() ) ):
            return -1.,-1.,-1.,-1.
        lowborder = 65.
        hghborder = 105.
        errl = ROOT.Double()
        onerr = ROOT.Double()
        errh = ROOT.Double()
        binl = h1.FindBin(lowborder)
        binh = h1.FindBin(hghborder)
        lowyield = h1.IntegralAndError(0,binl-1,errl)#add underflow
        onyield = h1.IntegralAndError(binl,binh-1,onerr)
        hghyield = h1.IntegralAndError(binh,h1.GetNbinsX()+1,errh)#add overflow
        offyield = lowyield+hghyield
        offerr = math.sqrt(errl*errl + errh*errh)
        TFon = onyield/(onyield+offyield)
        TFonerr = math.sqrt(pow((onerr*offyield)/pow(onyield+offyield,2),2)+pow((onyield*offerr)/pow(onyield+offyield,2),2))
        TFoff = offyield/(onyield+offyield)
        TFofferr = math.sqrt(pow((offerr*onyield)/pow(offyield+onyield,2),2)+pow((offyield*onerr)/pow(offyield+onyield,2),2))
        return TFon,TFonerr,TFoff,TFofferr


def LoadTFvars(histlist,TFlist,TFerrlist,syst="",process="LL",addname=""):
    TFlist["eein" +syst+addname],TFerrlist["eein" +syst+addname] = getTF(histlist[ "SRSSeeMjjInFull"+syst+"__yield_"+process],histlist[  "WZCRSSeeFull"+syst+"__yield_"+process])
    TFlist["emin" +syst+addname],TFerrlist["emin" +syst+addname] = getTF(histlist[ "SRSSemMjjInFull"+syst+"__yield_"+process],histlist[  "WZCRSSemFull"+syst+"__yield_"+process])
    TFlist["mmin" +syst+addname],TFerrlist["mmin" +syst+addname] = getTF(histlist[ "SRSSmmMjjInFull"+syst+"__yield_"+process],histlist[  "WZCRSSmmFull"+syst+"__yield_"+process])
    TFlist["eeout"+syst+addname],TFerrlist["eeout"+syst+addname] = getTF(histlist["SRSSeeMjjOutFull"+syst+"__yield_"+process],histlist[  "WZCRSSeeFull"+syst+"__yield_"+process])
    TFlist["emout"+syst+addname],TFerrlist["emout"+syst+addname] = getTF(histlist["SRSSemMjjOutFull"+syst+"__yield_"+process],histlist[  "WZCRSSemFull"+syst+"__yield_"+process])
    TFlist["mmout"+syst+addname],TFerrlist["mmout"+syst+addname] = getTF(histlist["SRSSmmMjjOutFull"+syst+"__yield_"+process],histlist[  "WZCRSSmmFull"+syst+"__yield_"+process])
    TFlist["ee1j" +syst+addname],TFerrlist["ee1j" +syst+addname] = getTF(histlist[    "SRSS1JeeFull"+syst+"__yield_"+process],histlist["WZCRSS1JeeFull"+syst+"__yield_"+process])
    TFlist["em1j" +syst+addname],TFerrlist["em1j" +syst+addname] = getTF(histlist[    "SRSS1JemFull"+syst+"__yield_"+process],histlist["WZCRSS1JemFull"+syst+"__yield_"+process])
    TFlist["mm1j" +syst+addname],TFerrlist["mm1j" +syst+addname] = getTF(histlist[    "SRSS1JmmFull"+syst+"__yield_"+process],histlist["WZCRSS1JmmFull"+syst+"__yield_"+process])
    TFlist["tl0"  +syst+addname],TFerrlist["tl0"  +syst+addname] = getTF(histlist[     "SR0SFOSFull"+syst+"__yield_"+process],histlist[ "WZCR0SFOSFull"+syst+"__yield_"+process])
    TFlist["tl1"  +syst+addname],TFerrlist["tl1"  +syst+addname] = getTF(histlist[     "SR1SFOSFull"+syst+"__yield_"+process],histlist[ "WZCR1SFOSFull"+syst+"__yield_"+process])
    TFlist["tl2"  +syst+addname],TFerrlist["tl2"  +syst+addname] = getTF(histlist[     "SR2SFOSFull"+syst+"__yield_"+process],histlist[ "WZCR2SFOSFull"+syst+"__yield_"+process])
    return True

def GetTFerrSyst(TFlist,TFerrlist,syst="",addname=""):
    TFerrlist["eein" +syst+addname] = TFlist["eein" +syst+addname]-TFlist["eein" +addname]
    TFerrlist["emin" +syst+addname] = TFlist["emin" +syst+addname]-TFlist["emin" +addname]
    TFerrlist["mmin" +syst+addname] = TFlist["mmin" +syst+addname]-TFlist["mmin" +addname]
    TFerrlist["eeout"+syst+addname] = TFlist["eeout"+syst+addname]-TFlist["eeout"+addname]
    TFerrlist["emout"+syst+addname] = TFlist["emout"+syst+addname]-TFlist["emout"+addname]
    TFerrlist["mmout"+syst+addname] = TFlist["mmout"+syst+addname]-TFlist["mmout"+addname]
    TFerrlist["ee1j" +syst+addname] = TFlist["ee1j" +syst+addname]-TFlist["ee1j" +addname]
    TFerrlist["em1j" +syst+addname] = TFlist["em1j" +syst+addname]-TFlist["em1j" +addname]
    TFerrlist["mm1j" +syst+addname] = TFlist["mm1j" +syst+addname]-TFlist["mm1j" +addname]
    TFerrlist["tl0"  +syst+addname] = TFlist["tl0"  +syst+addname]-TFlist["tl0"  +addname]
    TFerrlist["tl1"  +syst+addname] = TFlist["tl1"  +syst+addname]-TFlist["tl1"  +addname]
    TFerrlist["tl2"  +syst+addname] = TFlist["tl2"  +syst+addname]-TFlist["tl2"  +addname]
    return True

def LoadTFWZttZVar(histlist,TFlist,TFerrlist):
    temphist = dict()
    CloneHistogramsForScaling(temphist,histlist,"", "WZ",0.874)
    CloneHistogramsForScaling(temphist,histlist,"","ttZ",1.128)
    TFlist["eein" + "WZscaled"],TFerrlist["eein" + "WZscaled"] = getTF(histlist[ "SRSSeeMjjInFull__yield_ttZ"]+temphist[ "SRSSeeMjjInFull__yield_WZ"],histlist[  "WZCRSSeeFull__yield_ttZ"]+temphist[  "WZCRSSeeFull__yield_WZ"])
    TFlist["emin" + "WZscaled"],TFerrlist["emin" + "WZscaled"] = getTF(histlist[ "SRSSemMjjInFull__yield_ttZ"]+temphist[ "SRSSemMjjInFull__yield_WZ"],histlist[  "WZCRSSemFull__yield_ttZ"]+temphist[  "WZCRSSemFull__yield_WZ"])
    TFlist["mmin" + "WZscaled"],TFerrlist["mmin" + "WZscaled"] = getTF(histlist[ "SRSSmmMjjInFull__yield_ttZ"]+temphist[ "SRSSmmMjjInFull__yield_WZ"],histlist[  "WZCRSSmmFull__yield_ttZ"]+temphist[  "WZCRSSmmFull__yield_WZ"])
    TFlist["eeout"+ "WZscaled"],TFerrlist["eeout"+ "WZscaled"] = getTF(histlist["SRSSeeMjjOutFull__yield_ttZ"]+temphist["SRSSeeMjjOutFull__yield_WZ"],histlist[  "WZCRSSeeFull__yield_ttZ"]+temphist[  "WZCRSSeeFull__yield_WZ"])
    TFlist["emout"+ "WZscaled"],TFerrlist["emout"+ "WZscaled"] = getTF(histlist["SRSSemMjjOutFull__yield_ttZ"]+temphist["SRSSemMjjOutFull__yield_WZ"],histlist[  "WZCRSSemFull__yield_ttZ"]+temphist[  "WZCRSSemFull__yield_WZ"])
    TFlist["mmout"+ "WZscaled"],TFerrlist["mmout"+ "WZscaled"] = getTF(histlist["SRSSmmMjjOutFull__yield_ttZ"]+temphist["SRSSmmMjjOutFull__yield_WZ"],histlist[  "WZCRSSmmFull__yield_ttZ"]+temphist[  "WZCRSSmmFull__yield_WZ"])
    TFlist["ee1j" + "WZscaled"],TFerrlist["ee1j" + "WZscaled"] = getTF(histlist[    "SRSS1JeeFull__yield_ttZ"]+temphist[    "SRSS1JeeFull__yield_WZ"],histlist["WZCRSS1JeeFull__yield_ttZ"]+temphist["WZCRSS1JeeFull__yield_WZ"])
    TFlist["em1j" + "WZscaled"],TFerrlist["em1j" + "WZscaled"] = getTF(histlist[    "SRSS1JemFull__yield_ttZ"]+temphist[    "SRSS1JemFull__yield_WZ"],histlist["WZCRSS1JemFull__yield_ttZ"]+temphist["WZCRSS1JemFull__yield_WZ"])
    TFlist["mm1j" + "WZscaled"],TFerrlist["mm1j" + "WZscaled"] = getTF(histlist[    "SRSS1JmmFull__yield_ttZ"]+temphist[    "SRSS1JmmFull__yield_WZ"],histlist["WZCRSS1JmmFull__yield_ttZ"]+temphist["WZCRSS1JmmFull__yield_WZ"])
    TFlist["tl0"  + "WZscaled"],TFerrlist["tl0"  + "WZscaled"] = getTF(histlist[     "SR0SFOSFull__yield_ttZ"]+temphist[     "SR0SFOSFull__yield_WZ"],histlist[ "WZCR0SFOSFull__yield_ttZ"]+temphist[ "WZCR0SFOSFull__yield_WZ"])
    TFlist["tl1"  + "WZscaled"],TFerrlist["tl1"  + "WZscaled"] = getTF(histlist[     "SR1SFOSFull__yield_ttZ"]+temphist[     "SR1SFOSFull__yield_WZ"],histlist[ "WZCR1SFOSFull__yield_ttZ"]+temphist[ "WZCR1SFOSFull__yield_WZ"])
    TFlist["tl2"  + "WZscaled"],TFerrlist["tl2"  + "WZscaled"] = getTF(histlist[     "SR2SFOSFull__yield_ttZ"]+temphist[     "SR2SFOSFull__yield_WZ"],histlist[ "WZCR2SFOSFull__yield_ttZ"]+temphist[ "WZCR2SFOSFull__yield_WZ"])
    TFlist["eein" +"ttZscaled"],TFerrlist["eein" +"ttZscaled"] = getTF(temphist[ "SRSSeeMjjInFull__yield_ttZ"]+histlist[ "SRSSeeMjjInFull__yield_WZ"],temphist[  "WZCRSSeeFull__yield_ttZ"]+histlist[  "WZCRSSeeFull__yield_WZ"])
    TFlist["emin" +"ttZscaled"],TFerrlist["emin" +"ttZscaled"] = getTF(temphist[ "SRSSemMjjInFull__yield_ttZ"]+histlist[ "SRSSemMjjInFull__yield_WZ"],temphist[  "WZCRSSemFull__yield_ttZ"]+histlist[  "WZCRSSemFull__yield_WZ"])
    TFlist["mmin" +"ttZscaled"],TFerrlist["mmin" +"ttZscaled"] = getTF(temphist[ "SRSSmmMjjInFull__yield_ttZ"]+histlist[ "SRSSmmMjjInFull__yield_WZ"],temphist[  "WZCRSSmmFull__yield_ttZ"]+histlist[  "WZCRSSmmFull__yield_WZ"])
    TFlist["eeout"+"ttZscaled"],TFerrlist["eeout"+"ttZscaled"] = getTF(temphist["SRSSeeMjjOutFull__yield_ttZ"]+histlist["SRSSeeMjjOutFull__yield_WZ"],temphist[  "WZCRSSeeFull__yield_ttZ"]+histlist[  "WZCRSSeeFull__yield_WZ"])
    TFlist["emout"+"ttZscaled"],TFerrlist["emout"+"ttZscaled"] = getTF(temphist["SRSSemMjjOutFull__yield_ttZ"]+histlist["SRSSemMjjOutFull__yield_WZ"],temphist[  "WZCRSSemFull__yield_ttZ"]+histlist[  "WZCRSSemFull__yield_WZ"])
    TFlist["mmout"+"ttZscaled"],TFerrlist["mmout"+"ttZscaled"] = getTF(temphist["SRSSmmMjjOutFull__yield_ttZ"]+histlist["SRSSmmMjjOutFull__yield_WZ"],temphist[  "WZCRSSmmFull__yield_ttZ"]+histlist[  "WZCRSSmmFull__yield_WZ"])
    TFlist["ee1j" +"ttZscaled"],TFerrlist["ee1j" +"ttZscaled"] = getTF(temphist[    "SRSS1JeeFull__yield_ttZ"]+histlist[    "SRSS1JeeFull__yield_WZ"],temphist["WZCRSS1JeeFull__yield_ttZ"]+histlist["WZCRSS1JeeFull__yield_WZ"])
    TFlist["em1j" +"ttZscaled"],TFerrlist["em1j" +"ttZscaled"] = getTF(temphist[    "SRSS1JemFull__yield_ttZ"]+histlist[    "SRSS1JemFull__yield_WZ"],temphist["WZCRSS1JemFull__yield_ttZ"]+histlist["WZCRSS1JemFull__yield_WZ"])
    TFlist["mm1j" +"ttZscaled"],TFerrlist["mm1j" +"ttZscaled"] = getTF(temphist[    "SRSS1JmmFull__yield_ttZ"]+histlist[    "SRSS1JmmFull__yield_WZ"],temphist["WZCRSS1JmmFull__yield_ttZ"]+histlist["WZCRSS1JmmFull__yield_WZ"])
    TFlist["tl0"  +"ttZscaled"],TFerrlist["tl0"  +"ttZscaled"] = getTF(temphist[     "SR0SFOSFull__yield_ttZ"]+histlist[     "SR0SFOSFull__yield_WZ"],temphist[ "WZCR0SFOSFull__yield_ttZ"]+histlist[ "WZCR0SFOSFull__yield_WZ"])
    TFlist["tl1"  +"ttZscaled"],TFerrlist["tl1"  +"ttZscaled"] = getTF(temphist[     "SR1SFOSFull__yield_ttZ"]+histlist[     "SR1SFOSFull__yield_WZ"],temphist[ "WZCR1SFOSFull__yield_ttZ"]+histlist[ "WZCR1SFOSFull__yield_WZ"])
    TFlist["tl2"  +"ttZscaled"],TFerrlist["tl2"  +"ttZscaled"] = getTF(temphist[     "SR2SFOSFull__yield_ttZ"]+histlist[     "SR2SFOSFull__yield_WZ"],temphist[ "WZCR2SFOSFull__yield_ttZ"]+histlist[ "WZCR2SFOSFull__yield_WZ"])
    return True

def st(myfloat=-.1,prc="%.3f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))

def PrintvariationSystOneLine(TF,TFerr,name,title,total=False):
    addedsyststr = ""
    addedsyst = 0.
    #print (name)
    #print(TF[name])
    #print(0.01*TF[name],type(0.01*TF[name]))
    #print(0.10*TF[name],type(0.10*TF[name]))
    if "tl" in name:
        addedsyststr = " +/- " + st(0.10*TF[name]) + "(val)"
        addedsyst = 0.10*TF[name]
    elif "1j" in name:
        addedsyststr = " +/- " + st(0.01*TF[name]) + "(val)"
        addedsyst = 0.01*TF[name]
    elif "out" in name:
        addedsyststr = " +/- " + st(0.03*TF[name]) + "(Mjj) +/- " + st(0.01*TF[name]) + "(val)"
        addedsyst = math.sqrt(0.03*0.04+0.01*0.01)*TF[name]
    elif "in" in name:
        addedsyststr = " +/- " + st(0.10*TF[name]) + "(Mjj) +/- " + st(0.02*TF[name]) + "(val)"
        addedsyst = math.sqrt(0.10*0.10+0.02*0.02)*TF[name]
    #TFerr[name+"TotalUp"] = math.sqrt(pow(TFerr[name],2)+pow(TFerr[name+"LepSFUp"],2)+pow(TFerr[name+"TrigSFUp"],2)+pow(TFerr[name+"PileupUp"],2)+pow(TFerr[name+"QsqUp"],2)+pow(TFerr[name+"PDFUp"],2)+pow(TFerr[name+"JESUp"],2)+pow(TFerr[name+"WZscaled"],2)+pow(TFerr[name+"ttZscaled"],2)+pow(addedsyst,2) )
    TFerr[name+"TotalUp"] = math.sqrt(pow(TFerr[name],2)+pow(TFerr[name+"EleSFUp"],2)+pow(TFerr[name+"MuoSFUp"],2)+pow(TFerr[name+"TrigSFUp"],2)+pow(TFerr[name+"PileupUp"],2)+pow(TFerr[name+"QsqUp"],2)+pow(TFerr[name+"PDFUp"],2)+pow(TFerr[name+"JESUp"],2)+pow(TFerr[name+"WZscaled"],2)+pow(TFerr[name+"ttZscaled"],2)+pow(addedsyst,2) )
    TFerr[name+"TotalDown"] = math.sqrt(pow(TFerr[name],2)+pow(TFerr[name+"EleSFDown"],2)+pow(TFerr[name+"MuoSFDown"],2)+pow(TFerr[name+"TrigSFDown"],2)+pow(TFerr[name+"PileupDown"],2)+pow(TFerr[name+"QsqDown"],2)+pow(TFerr[name+"PDFDown"],2)+pow(TFerr[name+"JESDown"],2)+pow(TFerr[name+"WZscaled"],2)+pow(TFerr[name+"ttZscaled"],2)+pow(addedsyst,2) )
    #TFerr[name+"TotalDown"] = math.sqrt(pow(TFerr[name],2)+pow(TFerr[name+"LepSFDown"],2)+pow(TFerr[name+"TrigSFDown"],2)+pow(TFerr[name+"PileupDown"],2)+pow(TFerr[name+"QsqDown"],2)+pow(TFerr[name+"PDFDown"],2)+pow(TFerr[name+"JESDown"],2)+pow(TFerr[name+"WZscaled"],2)+pow(TFerr[name+"ttZscaled"],2)+pow(addedsyst,2) )
    if total:
        return title+" TF = "+st(TF[name])+" +" + st(TFerr[name+"TotalUp"]) + "/-" + st(TFerr[name+"TotalDown"])
    #return title+" TF = "+st(TF[name])+" +/- "+st(TFerr[name])+" (stat) +" + st(TFerr[name+"LepSFUp"])+"/-"+ st(TFerr[name+"LepSFDown"])+ "(lep) +" + st(TFerr[name+"TrigSFUp"])+"/-"+ st(TFerr[name+"TrigSFDown"])+ "(trig) +" + st(TFerr[name+"PileupUp"])+"/-"+ st(TFerr[name+"PileupDown"])+ "(PU) +" + st(TFerr[name+"QsqUp"])+"/-"+ st(TFerr[name+"QsqDown"])+ "(Q^2) +" + st(TFerr[name+"PDFUp"])+"/-"+ st(TFerr[name+"PDFDown"])+ "(PDF) +" + st(TFerr[name+"JESUp"])+"/-"+ st(TFerr[name+"JESDown"])+ "(JES) +/- "+st(TFerr[name+"WZscaled"])+ "(WZ) +/- "+st(TFerr[name+"ttZscaled"])+ "(ttZ)" + addedsyststr
    return title+" TF = "+st(TF[name])+" +/- "+st(TFerr[name])+" (stat) +" + st(TFerr[name+"EleSFUp"])+"/-"+ st(TFerr[name+"EleSFDown"])+ "(ele) +" + st(TFerr[name+"MuoSFUp"])+"/-"+ st(TFerr[name+"MuoSFDown"])+ "(muo) +" + st(TFerr[name+"TrigSFUp"])+"/-"+ st(TFerr[name+"TrigSFDown"])+ "(trig) +" + st(TFerr[name+"PileupUp"])+"/-"+ st(TFerr[name+"PileupDown"])+ "(PU) +" + st(TFerr[name+"QsqUp"])+"/-"+ st(TFerr[name+"QsqDown"])+ "(Q^2) +" + st(TFerr[name+"PDFUp"])+"/-"+ st(TFerr[name+"PDFDown"])+ "(PDF) +" + st(TFerr[name+"JESUp"])+"/-"+ st(TFerr[name+"JESDown"])+ "(JES) +/- "+st(TFerr[name+"WZscaled"])+ "(WZ) +/- "+st(TFerr[name+"ttZscaled"])+ "(ttZ)" + addedsyststr
    #return title+" TF = "+st(TF[name])+" +/- "+st(TFerr[name]/TF[name])+" (stat) +" + st(TFerr[name+"LepSFUp"]/TF[name])+"/-"+ st(TFerr[name+"LepSFDown"]/TF[name])+ "(lep) +" + st(TFerr[name+"TrigSFUp"]/TF[name])+"/-"+ st(TFerr[name+"TrigSFDown"]/TF[name])+ "(trig) +" + st(TFerr[name+"PileupUp"]/TF[name])+"/-"+ st(TFerr[name+"PileupDown"]/TF[name])+ "(PU) +" + st(TFerr[name+"QsqUp"]/TF[name])+"/-"+ st(TFerr[name+"QsqDown"]/TF[name])+ "(Q^2) +" + st(TFerr[name+"PDFUp"]/TF[name])+"/-"+ st(TFerr[name+"PDFDown"]/TF[name])+ "(PDF) +" + st(TFerr[name+"JESUp"]/TF[name])+"/-"+ st(TFerr[name+"JESDown"]/TF[name])+ "(JES) +/- "+st(TFerr[name+"WZscaled"]/TF[name])+ "(WZ) +/- "+st(TFerr[name+"ttZscaled"]/TF[name])+ "(ttZ)" + addedsyststr


def PrintvariationSyst(TF,TFerr,total=False):
    print("\n")
    print(PrintvariationSystOneLine(TF,TFerr,"eein" ,"ee Mjj-in ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"emin" ,"em Mjj-in ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"mmin" ,"mm Mjj-in ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"eeout","ee Mjj-out",total))
    print(PrintvariationSystOneLine(TF,TFerr,"emout","em Mjj-out",total))
    print(PrintvariationSystOneLine(TF,TFerr,"mmout","mm Mjj-out",total))
    print(PrintvariationSystOneLine(TF,TFerr,"ee1j" ,"ee 1j     ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"em1j" ,"em 1j     ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"mm1j" ,"mm 1j     ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"tl0"  ,"0 SFOS    ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"tl1"  ,"1 SFOS    ",total))
    print(PrintvariationSystOneLine(TF,TFerr,"tl2"  ,"2 SFOS    ",total))


def CloneHistogramsForScaling(newhistlist,oldhistlist,syst="",process="WZ",scale=1.):
        newhistlist[ "SRSSeeMjjInFull"+syst+"__yield_"+process] = oldhistlist[ "SRSSeeMjjInFull"+syst+"__yield_"+process]
        newhistlist[ "SRSSemMjjInFull"+syst+"__yield_"+process] = oldhistlist[ "SRSSemMjjInFull"+syst+"__yield_"+process]
        newhistlist[ "SRSSmmMjjInFull"+syst+"__yield_"+process] = oldhistlist[ "SRSSmmMjjInFull"+syst+"__yield_"+process]
        newhistlist["SRSSeeMjjOutFull"+syst+"__yield_"+process] = oldhistlist["SRSSeeMjjOutFull"+syst+"__yield_"+process]
        newhistlist["SRSSemMjjOutFull"+syst+"__yield_"+process] = oldhistlist["SRSSemMjjOutFull"+syst+"__yield_"+process]
        newhistlist["SRSSmmMjjOutFull"+syst+"__yield_"+process] = oldhistlist["SRSSmmMjjOutFull"+syst+"__yield_"+process]
        newhistlist[    "SRSS1JeeFull"+syst+"__yield_"+process] = oldhistlist[    "SRSS1JeeFull"+syst+"__yield_"+process]
        newhistlist[    "SRSS1JemFull"+syst+"__yield_"+process] = oldhistlist[    "SRSS1JemFull"+syst+"__yield_"+process]
        newhistlist[    "SRSS1JmmFull"+syst+"__yield_"+process] = oldhistlist[    "SRSS1JmmFull"+syst+"__yield_"+process]
        newhistlist[     "SR0SFOSFull"+syst+"__yield_"+process] = oldhistlist[     "SR0SFOSFull"+syst+"__yield_"+process]
        newhistlist[     "SR1SFOSFull"+syst+"__yield_"+process] = oldhistlist[     "SR1SFOSFull"+syst+"__yield_"+process]
        newhistlist[     "SR2SFOSFull"+syst+"__yield_"+process] = oldhistlist[     "SR2SFOSFull"+syst+"__yield_"+process]
        newhistlist[  "WZCRSSeeFull"+syst+"__yield_"+process] = oldhistlist[  "WZCRSSeeFull"+syst+"__yield_"+process]
        newhistlist[  "WZCRSSemFull"+syst+"__yield_"+process] = oldhistlist[  "WZCRSSemFull"+syst+"__yield_"+process]
        newhistlist[  "WZCRSSmmFull"+syst+"__yield_"+process] = oldhistlist[  "WZCRSSmmFull"+syst+"__yield_"+process]
        newhistlist["WZCRSS1JeeFull"+syst+"__yield_"+process] = oldhistlist["WZCRSS1JeeFull"+syst+"__yield_"+process]
        newhistlist["WZCRSS1JemFull"+syst+"__yield_"+process] = oldhistlist["WZCRSS1JemFull"+syst+"__yield_"+process]
        newhistlist["WZCRSS1JmmFull"+syst+"__yield_"+process] = oldhistlist["WZCRSS1JmmFull"+syst+"__yield_"+process]
        newhistlist[ "WZCR0SFOSFull"+syst+"__yield_"+process] = oldhistlist[ "WZCR0SFOSFull"+syst+"__yield_"+process]
        newhistlist[ "WZCR1SFOSFull"+syst+"__yield_"+process] = oldhistlist[ "WZCR1SFOSFull"+syst+"__yield_"+process]
        newhistlist[ "WZCR2SFOSFull"+syst+"__yield_"+process] = oldhistlist[ "WZCR2SFOSFull"+syst+"__yield_"+process]
        newhistlist[ "SRSSeeMjjInFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[ "SRSSemMjjInFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[ "SRSSmmMjjInFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist["SRSSeeMjjOutFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist["SRSSemMjjOutFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist["SRSSmmMjjOutFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[    "SRSS1JeeFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[    "SRSS1JemFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[    "SRSS1JmmFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[     "SR0SFOSFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[     "SR1SFOSFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[     "SR2SFOSFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[  "WZCRSSeeFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[  "WZCRSSemFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[  "WZCRSSmmFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist["WZCRSS1JeeFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist["WZCRSS1JemFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist["WZCRSS1JmmFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[ "WZCR0SFOSFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[ "WZCR1SFOSFull"+syst+"__yield_"+process].Scale(scale)
        newhistlist[ "WZCR2SFOSFull"+syst+"__yield_"+process].Scale(scale)
        return True
    
def createMergedHisto(name,myfile):
    mjjinstring = ""
    mjjoutstring = ""
    sumstring = name
    if ("WZCRSSee" in name):
        mjjinstring  = name.replace("WZCRSSee","WZCRSSeeMjjIn")
        mjjoutstring = name.replace("WZCRSSee","WZCRSSeeMjjOut")
    if ("WZCRSSem" in name):
        mjjinstring  = name.replace("WZCRSSem","WZCRSSemMjjIn")
        mjjoutstring = name.replace("WZCRSSem","WZCRSSemMjjOut")
    if ("WZCRSSmm" in name):
        mjjinstring  = name.replace("WZCRSSmm","WZCRSSmmMjjIn")
        mjjoutstring = name.replace("WZCRSSmm","WZCRSSmmMjjOut")
        
    htemp1 = myfile.Get(mjjinstring)
    htemp2 = myfile.Get(mjjoutstring)
    hist = htemp1.Clone(name+"_temp")
    hist.Add(htemp2,1.)
    return hist
        
def loadhist(histdict,name,filelist):
    if ( (("WZCRSSee" in name) or ("WZCRSSem" in name) or ("WZCRSSmm" in name)) and "yield" in name):
        htemp = createMergedHisto(name,filelist["fitlostlep"])
        histdict[name+"_LL"] = htemp.Clone(name+"_LL")
        histdict[name+"_WZ"] = htemp.Clone(name+"_WZ")
        htemp = createMergedHisto(name,filelist["ttz"])
        histdict[name+"_ttZ"] = htemp.Clone(name+"_ttZ")
        histdict[name+"_WZ"].Add(histdict[name+"_ttZ"],-1.)
        if (not (("Up__" in name) or ("Down__" in name))):
            htemp = createMergedHisto(name,filelist["fitprompt"])
            histdict[name+"_Other"] = htemp.Clone(name+"_Other")
            htemp = createMergedHisto(name,filelist["fitfakes"])
            histdict[name+"_Other"].Add(htemp,1.)
            htemp = createMergedHisto(name,filelist["fitqflip"])
            histdict[name+"_Other"].Add(htemp,1.)
            htemp = createMergedHisto(name,filelist["fitphoton"])
            histdict[name+"_Other"].Add(htemp,1.)
            htemp = createMergedHisto(name,filelist["vbs"])
            histdict[name+"_Other"].Add(htemp,1.)
            htemp = createMergedHisto(name,filelist["ttw"])
            histdict[name+"_Other"].Add(htemp,1.)
            histdict[name+"_Sim"] = histdict[name+"_Other"].Clone(name+"_Sim")
            histdict[name+"_Sim"].Add(histdict[name+"_LL"],1.)
            htemp = createMergedHisto(name,filelist["data"])
            histdict[name+"_Data"] = htemp.Clone(name+"_Data")
        return True
    htemp = filelist["fitlostlep"].Get(name)
    histdict[name+"_LL"] = htemp.Clone(name+"_LL")
    histdict[name+"_WZ"] = htemp.Clone(name+"_WZ")
    htemp = filelist["ttz"].Get(name)
    histdict[name+"_ttZ"] = htemp.Clone(name+"_ttZ")
    histdict[name+"_WZ"].Add(histdict[name+"_ttZ"],-1.)
    if (not (("Up__" in name) or ("Down__" in name))):
        htemp = filelist["fitprompt"].Get(name)
        histdict[name+"_Other"] = htemp.Clone(name+"_Other")
        htemp = filelist["fitfakes"].Get(name)
        histdict[name+"_Other"].Add(htemp,1.)
        htemp = filelist["fitqflip"].Get(name)
        histdict[name+"_Other"].Add(htemp,1.)
        htemp = filelist["fitphoton"].Get(name)
        histdict[name+"_Other"].Add(htemp,1.)
        htemp = filelist["vbs"].Get(name)
        histdict[name+"_Other"].Add(htemp,1.)
        htemp = filelist["ttw"].Get(name)
        histdict[name+"_Other"].Add(htemp,1.)
        histdict[name+"_Sim"] = histdict[name+"_Other"].Clone(name+"_Sim")
        histdict[name+"_Sim"].Add(histdict[name+"_LL"],1.)
        htemp = filelist["data"].Get(name)
        histdict[name+"_Data"] = htemp.Clone(name+"_Data")
    return True

def doPredictionPerRegion(name,prediction,hist,cTF,cTFerr):
    truthhistname,histname = "",""
    if (name == "eein"):
        truthhistname,histname = "SRSSeeMjjInFull","WZCRSSeeFull"
    if (name == "emin"):
        truthhistname,histname = "SRSSemMjjInFull","WZCRSSemFull"
    if (name == "mmin"):
        truthhistname,histname = "SRSSmmMjjInFull","WZCRSSmmFull"
    if (name == "eeout"):
        truthhistname,histname = "SRSSeeMjjOutFull","WZCRSSeeFull"
    if (name == "emout"):
        truthhistname,histname = "SRSSemMjjOutFull","WZCRSSemFull"
    if (name == "mmout"):
        truthhistname,histname = "SRSSmmMjjOutFull","WZCRSSmmFull"
    if (name == "ee1j"):
        truthhistname,histname = "SRSS1JeeFull","WZCRSS1JeeFull"
    if (name == "em1j"):
        truthhistname,histname = "SRSS1JemFull","WZCRSS1JemFull"
    if (name == "mm1j"):
        truthhistname,histname = "SRSS1JmmFull","WZCRSS1JmmFull"
    if (name == "tl0"):
        truthhistname,histname = "SR0SFOSFull","WZCR0SFOSFull"
    if (name == "tl1"):
        truthhistname,histname = "SR1SFOSFull","WZCR1SFOSFull"
    if (name == "tl2"):
        truthhistname,histname = "SR2SFOSFull","WZCR2SFOSFull"

    if (name == "tl0"):
        prediction[name] = hist[truthhistname+"__yield_LL"].Integral()
        prediction[name+ "Simtruth"   ] = hist[truthhistname+"__yield_LL"].GetBinContent(1)
        prediction[name+ "SimtruthErr"] = hist[truthhistname+"__yield_LL"].GetBinError(1)
        prediction[name+ "DataErrUp"  ] = 0.
        prediction[name+"OtherErrUp"  ] = 0.
        prediction[name+   "TFErrUp"  ] = 0.
        prediction[name+   "TotalUp"  ] = hist[truthhistname+"__yield_LL"].Integral()
        prediction[name+ "DataErrDown"] = 0.
        prediction[name+"OtherErrDown"] = 0.
        prediction[name+   "TFErrDown"] = 0.
        prediction[name+   "TotalDown"] = hist[truthhistname+"__yield_LL"].Integral()
        return True

    prediction[name] = (hist[histname+"__yield_Data"].Integral()-hist[histname+"__yield_Other"].Integral())*cTF[name]
    prediction[name+ "Simtruth"   ] = hist[truthhistname+"__yield_LL"].GetBinContent(1)
    prediction[name+ "SimtruthErr"] = hist[truthhistname+"__yield_LL"].GetBinError(1)
    prediction[name+ "DataErrUp"  ] = statErrorP(hist[histname+"__yield_Data"].Integral())*cTF[name]
    prediction[name+"OtherErrUp"  ] = 0.3*hist[histname+"__yield_Other"].Integral()*cTF[name]
    prediction[name+   "TFErrUp"  ] = (hist[histname+"__yield_Data"].Integral()-hist[histname+"__yield_Other"].Integral())*cTFerr[name+"TotalUp"]
    prediction[name+   "TotalUp"  ] = math.sqrt(pow(prediction[name+ "DataErrUp"  ],2)+pow(prediction[name+"OtherErrUp"  ],2)+pow(prediction[name+   "TFErrUp"  ],2))
    prediction[name+ "DataErrDown"] = statErrorN(hist[histname+"__yield_Data"].Integral())*cTF[name]
    prediction[name+"OtherErrDown"] = 0.3*hist[histname+"__yield_Other"].Integral()*cTF[name]
    prediction[name+   "TFErrDown"] = (hist[histname+"__yield_Data"].Integral()-hist[histname+"__yield_Other"].Integral())*cTFerr[name+"TotalDown"]
    prediction[name+   "TotalDown"] = math.sqrt(pow(prediction[name+ "DataErrDown"],2)+pow(prediction[name+"OtherErrDown"],2)+pow(prediction[name+   "TFErrDown"],2))
    return True

def doPrediction(prediction,hist,cTF,cTFerr):
    doPredictionPerRegion("eein" ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("emin" ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("mmin" ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("eeout",prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("emout",prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("mmout",prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("ee1j" ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("em1j" ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("mm1j" ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("tl0"  ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("tl1"  ,prediction,hist,cTF,cTFerr)
    doPredictionPerRegion("tl2"  ,prediction,hist,cTF,cTFerr)
    return True

def SavePredictionsIntoRoot(prediction,cTF,cTFerr,year):
    directory = getpath(year=year,short=False)
    savehists = dict()
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"Simtruth")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"SimtruthErr")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"DataErrUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"DataErrDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"OtherErrUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"OtherErrDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"TFErrUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"TFErrDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"TotalUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,False,"TotalDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"LepSFUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"LepSFDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"EleSFUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"EleSFDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"MuoSFUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"MuoSFDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"TrigSFUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"TrigSFDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"PileupUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"PileupDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"QsqUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"QsqDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"PDFUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"PDFDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"JESUp")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"JESDown")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"WZscaled")
    FillOneHist(savehists,prediction,cTF,cTFerr,True ,"ttZscaled")
    fout = ROOT.TFile(directory+"PredictionHistogramsForWZbkg.root","recreate")
    fout.cd()
    for h in savehists.itervalues():
        h.Write()
    fout.Close()
    print ("Wrote prediction into file "+directory+"PredictionHistogramsForWZbkg.root")
    return True

def  FillOneHist(savehists,prediction,cTF,cTFerr,TFvariation,whatvariation):
    histoname = whatvariation
    if (TFvariation == True ) and (whatvariation == ""): histoname = "TFstat"
    if (TFvariation == False) and (whatvariation == ""): histoname = "Yield"
    htemp = ROOT.TH1F(histoname,"",12,0.5,12.5)
    FillOneBin( 1,"eein" ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 2,"emin" ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 3,"mmin" ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 4,"eeout",htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 5,"emout",htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 6,"mmout",htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 7,"ee1j" ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 8,"em1j" ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin( 9,"mm1j" ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin(10,"tl0"  ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin(11,"tl1"  ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    FillOneBin(12,"tl2"  ,htemp,prediction,cTF,cTFerr,TFvariation,whatvariation)
    savehists[histoname] = htemp
    return True

def FillOneBin(bin,predname,histo,prediction,cTF,cTFerr,TFvariation,whatvariation):
    if (not TFvariation):
        histo.SetBinContent(bin,prediction[predname+whatvariation])
    elif (cTF[predname] != 0) and (bin !=10):
        histo.SetBinContent(bin,prediction[predname]*cTFerr[predname+whatvariation]/cTF[predname])
    if bin == 10 and whatvariation == "TotalUp":
        histo.SetBinContent(bin,0.87) #HARDCODED
    if bin == 10 and whatvariation == "TotalDown":
        histo.SetBinContent(bin,0.92) #HARDCODED
    return True


def StringOtherYieldOneLine(hist,name):
    truthhistname,histname = "",""
    if (name == "eein"):
        truthhistname,histname = "SRSSeeMjjInFull","WZCRSSeeFull"
    if (name == "emin"):
        truthhistname,histname = "SRSSemMjjInFull","WZCRSSemFull"
    if (name == "mmin"):
        truthhistname,histname = "SRSSmmMjjInFull","WZCRSSmmFull"
    if (name == "eeout"):
        truthhistname,histname = "SRSSeeMjjOutFull","WZCRSSeeFull"
    if (name == "emout"):
        truthhistname,histname = "SRSSemMjjOutFull","WZCRSSemFull"
    if (name == "mmout"):
        truthhistname,histname = "SRSSmmMjjOutFull","WZCRSSmmFull"
    if (name == "ee1j"):
        truthhistname,histname = "SRSS1JeeFull","WZCRSS1JeeFull"
    if (name == "em1j"):
        truthhistname,histname = "SRSS1JemFull","WZCRSS1JemFull"
    if (name == "mm1j"):
        truthhistname,histname = "SRSS1JmmFull","WZCRSS1JmmFull"
    if (name == "tl0"):
        truthhistname,histname = "SR0SFOSFull","WZCR0SFOSFull"
    if (name == "tl1"):
        truthhistname,histname = "SR1SFOSFull","WZCR1SFOSFull"
    if (name == "tl2"):
        truthhistname,histname = "SR2SFOSFull","WZCR2SFOSFull"
    return name + ": Other = " + st(hist[histname+"__yield_Other"].GetBinContent(1)) + "+/-" + st(hist[histname+"__yield_Other"].GetBinError(1))

def StringPredictionOneLine(prediction,name,title,total=False):
    if name == "tl0":
        return title + ": LLtruth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction ----"
    if total:
        return title + ": LLtruth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st(prediction[name+   "TotalUp"  ]) + "/-" + st(prediction[name+   "TotalDown"])
    return title + ": LLtruth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st(prediction[name+ "DataErrUp"  ]) + "/-" + st(prediction[name+ "DataErrDown"]) + " (stat) +" + st(prediction[name+"OtherErrUp"  ]) + "/-" + st(prediction[name+"OtherErrDown"]) + " (bkg) +" + st(prediction[name+   "TFErrUp"  ]) + "/-" + st(prediction[name+   "TFErrDown"]) + " (syst)"

def StringPredictionOneLineText(prediction,name,title,total=False):
    if name == "tl0":
        return title + ": LLtruth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction ----"
    if total:
        return title + ": LLtruth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st(prediction[name+   "TotalUp"  ]) + "/-" + st(prediction[name+   "TotalDown"])
    return title + ": LLtruth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st(prediction[name+ "DataErrUp"  ]) + "/-" + st(prediction[name+ "DataErrDown"]) + " (stat) +" + st(prediction[name+"OtherErrUp"  ]) + "/-" + st(prediction[name+"OtherErrDown"]) + " (bkg) +" + st(prediction[name+   "TFErrUp"  ]) + "/-" + st(prediction[name+   "TFErrDown"]) + " (syst)"


def PrintPredictions(prediction,total=False):
    print(StringPredictionOneLine(prediction,"eein" ,"ee Mjj-in", total))
    print(StringPredictionOneLine(prediction,"emin" ,"em Mjj-in", total))
    print(StringPredictionOneLine(prediction,"mmin" ,"mm Mjj-in", total))
    print(StringPredictionOneLine(prediction,"eeout","ee Mjj-out",total))
    print(StringPredictionOneLine(prediction,"emout","em Mjj-out",total))
    print(StringPredictionOneLine(prediction,"mmout","mm Mjj-out",total))
    print(StringPredictionOneLine(prediction,"ee1j" ,"ee 1j",     total))
    print(StringPredictionOneLine(prediction,"em1j" ,"em 1j",     total))
    print(StringPredictionOneLine(prediction,"mm1j" ,"mm 1j",     total))
    print(StringPredictionOneLine(prediction,"tl0"  ,"0 SFOS",    total))
    print(StringPredictionOneLine(prediction,"tl1"  ,"1 SFOS",    total))
    print(StringPredictionOneLine(prediction,"tl2"  ,"2 SFOS",    total))



def getWZuncertainties(year=1):
    mydir = getpath(year=year,short=False)
    fileslong = loadfiles(theyear=year,isshort=False)
    filesshort = loadfiles(theyear=year,isshort=True)
    hist = dict()
    signalselection  = ["SRSSeeMjjInFull","SRSSemMjjInFull","SRSSmmMjjInFull","SRSSeeMjjOutFull","SRSSemMjjOutFull","SRSSmmMjjOutFull","SRSS1JeeFull","SRSS1JemFull","SRSS1JmmFull","SR0SFOSFull","SR1SFOSFull","SR2SFOSFull"]
    controlselection = ["WZCRSSeeFull","WZCRSSemFull","WZCRSSmmFull","WZCRSSeeFull","WZCRSSemFull","WZCRSSmmFull","WZCRSS1JeeFull","WZCRSS1JemFull","WZCRSS1JmmFull","WZCR0SFOSFull","WZCR1SFOSFull","WZCR2SFOSFull"]
    # ************
    # need extra work for SSxxFull to be made from SSxxMjjInFull and SSxxMjjOutFull
    # ************
    validationhistos = ["WZCRSSnoZmassLowDetaMjj__Mjj","WZCRSSnoZmassLowDetaMjj__MllOnOff","WZCRSSnoZmassKinSel__Mjj","WZCRSSnoZmassKinSel__MllOnOff","WZCR3LnoZmassKinSelInvertAll__MllOnOff","WZCR3LnoZmassKinSelInvertDPhi__MllOnOff","WZCR3LnoZmassKinSelInvertExOne__MllOnOff","WZCR3LnoZmassKinSelInvertMTmax__MllOnOff","WZCR3LnoZmassKinSelInvertOne__MllOnOff","WZCR3LnoZmassKinSelInvertPt3l__MllOnOff","WZCRSS1JnoZcand1JKin__MllOnOff","WZCRSS1JnoZcandNsoftbVeto__MllOnOff"]
    #histos = ["yield","MllOnOff"]
    histos = ["yield"]
    #this is MC variations, not ttZ/WZ, Mll validation, or Mjj uncertainties
    #systematics = ["LepSF","TrigSF","Pileup","Qsq","PDF","JES"]
    systematics = ["EleSF","MuoSF","TrigSF","Pileup","Qsq","PDF","JES"]
    systematics = ["LepSF","EleSF","MuoSF","TrigSF","Pileup","Qsq","PDF","JES"]
    #processes define as LL, WZ, ttZ, Data, Other
    allhistnames = [] #validationhistos
    templist = signalselection+controlselection
    for n1 in templist:
        for n2 in histos:
            allhistnames.append(n1+"__"+n2)
            for n3 in systematics:
                allhistnames.append(n1+n3+"Up__"+n2)
                allhistnames.append(n1+n3+"Down__"+n2)

    print("Start loading histograms")
    for name in validationhistos:
        #print(name)
        #print(filesshort["data"])
        loadhist(hist,name,filesshort)
    for name in allhistnames:
        #print(name)
        #print(fileslong["data"])
        loadhist(hist,name,fileslong)
    print("Loaded "+str(len(hist))+" histograms")

    # now it is time to calculate SF
    #def getTF(h1=ROOT.TH1F(),h2=ROOT.TH1F()):
    cTF = dict()
    cTFerr = dict()
    ddict = dict()#likely unused
    dummy = -1.
    #cTF["eein" ],cTFerr["eein" ] = getTF(hist[ "SRSSeeMjjInFull__yield_LL"],hist[  "WZCRSSeeFull__yield_LL"])
    #TFlist["eein" +syst+addname],TFlist["eein" +syst+addname] = getTF(histlist[ "SRSSeeMjjInFull"+syst+"__yield_"+process],histlist[  "WZCRSSeeFull"+syst+"__yield_"+process])
    LoadTFvars(hist,cTF,cTFerr,"","LL","") #load nominal
    print("Nominal",cTF)
    print("Nominalerr",cTFerr)
    LoadTFvars(hist,cTF,ddict,"LepSFUp"   ,"LL","") #load LepSFUp
    LoadTFvars(hist,cTF,ddict,"LepSFDown" ,"LL","") #load LepSFDown
    LoadTFvars(hist,cTF,ddict,"EleSFUp"   ,"LL","") #load LepSFUp
    LoadTFvars(hist,cTF,ddict,"EleSFDown" ,"LL","") #load LepSFDown
    LoadTFvars(hist,cTF,ddict,"MuoSFUp"   ,"LL","") #load LepSFUp
    LoadTFvars(hist,cTF,ddict,"MuoSFDown" ,"LL","") #load LepSFDown
    LoadTFvars(hist,cTF,ddict,"TrigSFUp"  ,"LL","") #load TrigSFUp
    LoadTFvars(hist,cTF,ddict,"TrigSFDown","LL","") #load TrigSFDown
    LoadTFvars(hist,cTF,ddict,"PileupUp"  ,"LL","") #load PileupUp
    LoadTFvars(hist,cTF,ddict,"PileupDown","LL","") #load PileupDown
    LoadTFvars(hist,cTF,ddict,"QsqUp"     ,"LL","") #load QsqUp
    LoadTFvars(hist,cTF,ddict,"QsqDown"   ,"LL","") #load QsqDown
    LoadTFvars(hist,cTF,ddict,"PDFUp"     ,"LL","") #load PDFUp
    LoadTFvars(hist,cTF,ddict,"PDFDown"   ,"LL","") #load PDFDown
    LoadTFvars(hist,cTF,ddict,"JESUp"     ,"LL","") #load JESUp
    LoadTFvars(hist,cTF,ddict,"JESDown"   ,"LL","") #load JESDown
    LoadTFWZttZVar(hist,cTF,cTFerr)
    GetTFerrSyst(cTF,cTFerr,"LepSFUp"   ,"")
    GetTFerrSyst(cTF,cTFerr,"LepSFDown" ,"")
    GetTFerrSyst(cTF,cTFerr,"EleSFUp"   ,"")
    GetTFerrSyst(cTF,cTFerr,"EleSFDown" ,"")
    GetTFerrSyst(cTF,cTFerr,"MuoSFUp"   ,"")
    GetTFerrSyst(cTF,cTFerr,"MuoSFDown" ,"")
    GetTFerrSyst(cTF,cTFerr,"TrigSFUp"  ,"")
    GetTFerrSyst(cTF,cTFerr,"TrigSFDown","")
    GetTFerrSyst(cTF,cTFerr,"PileupUp"  ,"")
    GetTFerrSyst(cTF,cTFerr,"PileupDown","")
    GetTFerrSyst(cTF,cTFerr,"QsqUp"     ,"")
    GetTFerrSyst(cTF,cTFerr,"QsqDown"   ,"")
    GetTFerrSyst(cTF,cTFerr,"PDFUp"     ,"")
    GetTFerrSyst(cTF,cTFerr,"PDFDown"   ,"")
    GetTFerrSyst(cTF,cTFerr,"JESUp"     ,"")
    GetTFerrSyst(cTF,cTFerr,"JESDown"   ,"")
    GetTFerrSyst(cTF,cTFerr,"WZscaled"  ,"")
    GetTFerrSyst(cTF,cTFerr,"ttZscaled" ,"")

    print(StringOtherYieldOneLine(hist,"eein"))
    print(StringOtherYieldOneLine(hist,"emin"))
    print(StringOtherYieldOneLine(hist,"mmin"))
    print(StringOtherYieldOneLine(hist,"eeout"))
    print(StringOtherYieldOneLine(hist,"emout"))
    print(StringOtherYieldOneLine(hist,"mmout"))
    print(StringOtherYieldOneLine(hist,"ee1j"))
    print(StringOtherYieldOneLine(hist,"em1j"))
    print(StringOtherYieldOneLine(hist,"mm1j"))
    print(StringOtherYieldOneLine(hist,"tl0"))
    print(StringOtherYieldOneLine(hist,"tl1"))
    print(StringOtherYieldOneLine(hist,"tl2"))


    PrintvariationSyst(cTF,cTFerr)#do stuff by hands here
    PrintvariationSyst(cTF,cTFerr,True)#do stuff by hands here
    #print(cTF["eein"],cTFerr["eeinTotalUp"],cTFerr["eeinTotalDown"])
    #print(cTF["emin"],cTFerr["eminTotalUp"],cTFerr["eminTotalDown"])
    #print(cTF["mmin"],cTFerr["mminTotalUp"],cTFerr["mminTotalDown"])
    #print(cTF["eeout"],cTFerr["eeoutTotalUp"],cTFerr["eeoutTotalDown"])
    #print(cTF["emout"],cTFerr["emoutTotalUp"],cTFerr["emoutTotalDown"])
    #print(cTF["mmout"],cTFerr["mmoutTotalUp"],cTFerr["mmoutTotalDown"])
    #print(cTF["ee1j"],cTFerr["ee1jTotalUp"],cTFerr["ee1jTotalDown"])
    #print(cTF["em1j"],cTFerr["em1jTotalUp"],cTFerr["em1jTotalDown"])
    #print(cTF["mm1j"],cTFerr["mm1jTotalUp"],cTFerr["mm1jTotalDown"])
    #print(cTF["tl0"],cTFerr["tl0TotalUp"],cTFerr["tl0TotalDown"])
    #print(cTF["tl1"],cTFerr["tl1TotalUp"],cTFerr["tl1TotalDown"])
    #print(cTF["tl2"],cTFerr["tl2TotalUp"],cTFerr["tl2TotalDown"])

    
    
    #REFERENCES: ADD 15% on 3l WZ CR, ADD 10% (+) 1% on SS WZ CR (only 1% for 1j region)
    #validation regions Mll in/out testing
    TFtestM0,TFtestM0e = getTF(hist[ "WZCR3LnoZmassKinSelInvertAll__MllOnOff_LL"])
    TFtestM1,TFtestM1e = getTF(hist[ "WZCR3LnoZmassKinSelInvertPt3l__MllOnOff_LL"])
    TFtestM2,TFtestM2e = getTF(hist[ "WZCR3LnoZmassKinSelInvertOne__MllOnOff_LL"])
    TFtestM3,TFtestM3e = getTF(hist[ "WZCR3LnoZmassKinSelInvertExOne__MllOnOff_LL"])
    TFtestM8,TFtestM8e = getTF(hist[ "WZCRSSnoZmassKinSel__MllOnOff_LL"])
    TFtestM9,TFtestM9e = getTF(hist[ "WZCRSS1JnoZcand1JKin__MllOnOff_LL"])
    TFtestS0,TFtestS0e = getTF(hist[ "WZCR3LnoZmassKinSelInvertAll__MllOnOff_Sim"])
    TFtestS1,TFtestS1e = getTF(hist[ "WZCR3LnoZmassKinSelInvertPt3l__MllOnOff_Sim"])
    TFtestS2,TFtestS2e = getTF(hist[ "WZCR3LnoZmassKinSelInvertOne__MllOnOff_Sim"])
    TFtestS3,TFtestS3e = getTF(hist[ "WZCR3LnoZmassKinSelInvertExOne__MllOnOff_Sim"])
    TFtestS8,TFtestS8e = getTF(hist[ "WZCRSSnoZmassKinSel__MllOnOff_Sim"])
    TFtestS9,TFtestS9e = getTF(hist[ "WZCRSS1JnoZcand1JKin__MllOnOff_Sim"])
    TFtestD0,TFtestD0e = getTF(hist[ "WZCR3LnoZmassKinSelInvertAll__MllOnOff_Data"])
    TFtestD1,TFtestD1e = getTF(hist[ "WZCR3LnoZmassKinSelInvertPt3l__MllOnOff_Data"])
    TFtestD2,TFtestD2e = getTF(hist[ "WZCR3LnoZmassKinSelInvertOne__MllOnOff_Data"])
    TFtestD3,TFtestD3e = getTF(hist[ "WZCR3LnoZmassKinSelInvertExOne__MllOnOff_Data"])
    TFtestD8,TFtestD8e = getTF(hist[ "WZCRSSnoZmassKinSel__MllOnOff_Data"])
    TFtestD9,TFtestD9e = getTF(hist[ "WZCRSS1JnoZcand1JKin__MllOnOff_Data"])
    print("\n My studies showed this is the best one - one of three options where contamination is reasonable, plus this has biggest statisticts: Result: 15\% uncertainty.")
    print("WZCR3LnoZmassKinSelInvertExOne LL="+str("%.3f" % TFtestM3)+"+/-"+str("%.3f" % TFtestM3e)+", Sim="+str("%.3f" % TFtestS3)+"+/-"+str("%.3f" % TFtestS3e)+", Data="+str("%.3f" % TFtestD3)+"+/-"+str("%.3f" % TFtestD3e))
    print("xx WZCR3LnoZmassKinSelInvertOne LL=" +str("%.3f" % TFtestM2)+"+/-"+str("%.3f" % TFtestM2e)+", Sim="+str("%.3f" % TFtestS2)+"+/-"+str("%.3f" % TFtestS2e)+", Data="+str("%.3f" % TFtestD2)+"+/-"+str("%.3f" % TFtestD2e))
    print("xx WZCR3LnoZmassKinSelInvertPt3l LL="+str("%.3f" % TFtestM1)+"+/-"+str("%.3f" % TFtestM1e)+", Sim="+str("%.3f" % TFtestS1)+"+/-"+str("%.3f" % TFtestS1e)+", Data="+str("%.3f" % TFtestD1)+"+/-"+str("%.3f" % TFtestD1e))
    print("xx WZCR3LnoZmassKinSelInvertAll LL=" +str("%.3f" % TFtestM0)+"+/-"+str("%.3f" % TFtestM0e)+", Sim="+str("%.3f" % TFtestS0)+"+/-"+str("%.3f" % TFtestS0e)+", Data="+str("%.3f" % TFtestD0)+"+/-"+str("%.3f" % TFtestD0e))
    print("\n My studies showed these: Result: 1\% uncertainty.")
    print("WZCRSSnoZmassKinSel  LL="+str("%.3f" % TFtestM8)+"+/-"+str("%.3f" % TFtestM8e)+", Sim="+str("%.3f" % TFtestS8)+"+/-"+str("%.3f" % TFtestS8e)+", Data="+str("%.3f" % TFtestD8)+"+/-"+str("%.3f" % TFtestD8e))
    print("WZCRSS1JnoZcand1JKin LL="+str("%.3f" % TFtestM9)+"+/-"+str("%.3f" % TFtestM9e)+", Sim="+str("%.3f" % TFtestS9)+"+/-"+str("%.3f" % TFtestS9e)+", Data="+str("%.3f" % TFtestD9)+"+/-"+str("%.3f" % TFtestD9e))

    #Mjj in testing
    onTFtestMb,onTFtestMbe,offTFtestMb,offTFtestMbe = getdoubleTF(hist[ "WZCRSSnoZmassKinSel__Mjj_LL"])
    onTFtestSb,onTFtestSbe,offTFtestSb,offTFtestSbe = getdoubleTF(hist[ "WZCRSSnoZmassKinSel__Mjj_Sim"])
    onTFtestDb,onTFtestDbe,offTFtestDb,offTFtestDbe = getdoubleTF(hist[ "WZCRSSnoZmassKinSel__Mjj_Data"])
    print("\n My studies showed these: Result: 10\% uncertainty from statistical precision of the test.")
    print("WZCRSSnoZmassKinSel     On  LL="+str("%.3f" % onTFtestMb)+"+/-"+str("%.3f" % onTFtestMbe)+", Sim="+str("%.3f" % onTFtestSb)+"+/-"+str("%.3f" % onTFtestSbe)+", Data="+str("%.3f" % onTFtestDb)+"+/-"+str("%.3f" % onTFtestDbe))
    print("WZCRSSnoZmassKinSel     Off LL="+str("%.3f" % offTFtestMb)+"+/-"+str("%.3f" % offTFtestMbe)+", Sim="+str("%.3f" % offTFtestSb)+"+/-"+str("%.3f" % offTFtestSbe)+", Data="+str("%.3f" % offTFtestDb)+"+/-"+str("%.3f" % offTFtestDbe))

    print("\n\n\n FINAL PREDICTION \n")
    #now do estimate
    #yield = (data - other) * TF
    #yielderr = sqrt(data) * TF (+) othersyst * TF (+) (data-other) * TFerr
    prediction = dict()
    doPrediction(prediction,hist,cTF,cTFerr)
    SavePredictionsIntoRoot(prediction,cTF,cTFerr,year)

    PrintPredictions(prediction)
    PrintPredictions(prediction,True)


getWZuncertainties()
                             

