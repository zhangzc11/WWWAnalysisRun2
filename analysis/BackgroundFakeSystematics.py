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

def LoadSRvars(hist,cSRY,cSRYerr,syst="",sample="ddfakes",issr=True): #load nominal
    if issr:
        cSRY["eein" +syst+"_"+sample],cSRYerr["eein" +syst+"_"+sample] = hist["SRSSeeMjjInFull" +syst+"__yield_"+sample].GetBinContent(1),hist["SRSSeeMjjInFull" +syst+"__yield_"+sample].GetBinError(1)
        cSRY["emin" +syst+"_"+sample],cSRYerr["emin" +syst+"_"+sample] = hist["SRSSemMjjInFull" +syst+"__yield_"+sample].GetBinContent(1),hist["SRSSemMjjInFull" +syst+"__yield_"+sample].GetBinError(1)
        cSRY["mmin" +syst+"_"+sample],cSRYerr["mmin" +syst+"_"+sample] = hist["SRSSmmMjjInFull" +syst+"__yield_"+sample].GetBinContent(1),hist["SRSSmmMjjInFull" +syst+"__yield_"+sample].GetBinError(1)
        cSRY["eeout"+syst+"_"+sample],cSRYerr["eeout"+syst+"_"+sample] = hist["SRSSeeMjjOutFull"+syst+"__yield_"+sample].GetBinContent(1),hist["SRSSeeMjjOutFull"+syst+"__yield_"+sample].GetBinError(1)
        cSRY["emout"+syst+"_"+sample],cSRYerr["emout"+syst+"_"+sample] = hist["SRSSemMjjOutFull"+syst+"__yield_"+sample].GetBinContent(1),hist["SRSSemMjjOutFull"+syst+"__yield_"+sample].GetBinError(1)
        cSRY["mmout"+syst+"_"+sample],cSRYerr["mmout"+syst+"_"+sample] = hist["SRSSmmMjjOutFull"+syst+"__yield_"+sample].GetBinContent(1),hist["SRSSmmMjjOutFull"+syst+"__yield_"+sample].GetBinError(1)
        cSRY["ee1j" +syst+"_"+sample],cSRYerr["ee1j" +syst+"_"+sample] = hist["SRSS1JeeFull"    +syst+"__yield_"+sample].GetBinContent(1),hist["SRSS1JeeFull"    +syst+"__yield_"+sample].GetBinError(1)
        cSRY["em1j" +syst+"_"+sample],cSRYerr["em1j" +syst+"_"+sample] = hist["SRSS1JemFull"    +syst+"__yield_"+sample].GetBinContent(1),hist["SRSS1JemFull"    +syst+"__yield_"+sample].GetBinError(1)
        cSRY["mm1j" +syst+"_"+sample],cSRYerr["mm1j" +syst+"_"+sample] = hist["SRSS1JmmFull"    +syst+"__yield_"+sample].GetBinContent(1),hist["SRSS1JmmFull"    +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl0"  +syst+"_"+sample],cSRYerr["tl0"  +syst+"_"+sample] = hist["SR0SFOSFull"     +syst+"__yield_"+sample].GetBinContent(1),hist["SR0SFOSFull"     +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl1"  +syst+"_"+sample],cSRYerr["tl1"  +syst+"_"+sample] = hist["SR1SFOSFull"     +syst+"__yield_"+sample].GetBinContent(1),hist["SR1SFOSFull"     +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl2"  +syst+"_"+sample],cSRYerr["tl2"  +syst+"_"+sample] = hist["SR2SFOSFull"     +syst+"__yield_"+sample].GetBinContent(1),hist["SR1SFOSFull"     +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl0m" +syst+"_"+sample],cSRYerr["tl0m" +syst+"_"+sample] = hist["SR0SFOSeemFull"  +syst+"__yield_"+sample].GetBinContent(1),hist["SR0SFOSeemFull"  +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl0e" +syst+"_"+sample],cSRYerr["tl0e" +syst+"_"+sample] = hist["SR0SFOSemmFull"  +syst+"__yield_"+sample].GetBinContent(1),hist["SR0SFOSemmFull"  +syst+"__yield_"+sample].GetBinError(1)
    else:
        cSRY["eein" +syst+"_"+sample],cSRYerr["eein" +syst+"_"+sample] = hist["ARSSeeMjjInFull" +syst+"__yield_"+sample].GetBinContent(1),hist["ARSSeeMjjInFull" +syst+"__yield_"+sample].GetBinError(1)
        cSRY["emin" +syst+"_"+sample],cSRYerr["emin" +syst+"_"+sample] = hist["ARSSemMjjInFull" +syst+"__yield_"+sample].GetBinContent(1),hist["ARSSemMjjInFull" +syst+"__yield_"+sample].GetBinError(1)
        cSRY["mmin" +syst+"_"+sample],cSRYerr["mmin" +syst+"_"+sample] = hist["ARSSmmMjjInFull" +syst+"__yield_"+sample].GetBinContent(1),hist["ARSSmmMjjInFull" +syst+"__yield_"+sample].GetBinError(1)
        cSRY["eeout"+syst+"_"+sample],cSRYerr["eeout"+syst+"_"+sample] = hist["ARSSeeMjjOutFull"+syst+"__yield_"+sample].GetBinContent(1),hist["ARSSeeMjjOutFull"+syst+"__yield_"+sample].GetBinError(1)
        cSRY["emout"+syst+"_"+sample],cSRYerr["emout"+syst+"_"+sample] = hist["ARSSemMjjOutFull"+syst+"__yield_"+sample].GetBinContent(1),hist["ARSSemMjjOutFull"+syst+"__yield_"+sample].GetBinError(1)
        cSRY["mmout"+syst+"_"+sample],cSRYerr["mmout"+syst+"_"+sample] = hist["ARSSmmMjjOutFull"+syst+"__yield_"+sample].GetBinContent(1),hist["ARSSmmMjjOutFull"+syst+"__yield_"+sample].GetBinError(1)
        cSRY["ee1j" +syst+"_"+sample],cSRYerr["ee1j" +syst+"_"+sample] = hist["ARSS1JeeFull"    +syst+"__yield_"+sample].GetBinContent(1),hist["ARSS1JeeFull"    +syst+"__yield_"+sample].GetBinError(1)
        cSRY["em1j" +syst+"_"+sample],cSRYerr["em1j" +syst+"_"+sample] = hist["ARSS1JemFull"    +syst+"__yield_"+sample].GetBinContent(1),hist["ARSS1JemFull"    +syst+"__yield_"+sample].GetBinError(1)
        cSRY["mm1j" +syst+"_"+sample],cSRYerr["mm1j" +syst+"_"+sample] = hist["ARSS1JmmFull"    +syst+"__yield_"+sample].GetBinContent(1),hist["ARSS1JmmFull"    +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl0"  +syst+"_"+sample],cSRYerr["tl0"  +syst+"_"+sample] = hist["AR0SFOSFull"     +syst+"__yield_"+sample].GetBinContent(1),hist["AR0SFOSFull"     +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl1"  +syst+"_"+sample],cSRYerr["tl1"  +syst+"_"+sample] = hist["AR1SFOSFull"     +syst+"__yield_"+sample].GetBinContent(1),hist["AR1SFOSFull"     +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl2"  +syst+"_"+sample],cSRYerr["tl2"  +syst+"_"+sample] = hist["AR2SFOSFull"     +syst+"__yield_"+sample].GetBinContent(1),hist["AR1SFOSFull"     +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl0m" +syst+"_"+sample],cSRYerr["tl0m" +syst+"_"+sample] = hist["AR0SFOSeemFull"  +syst+"__yield_"+sample].GetBinContent(1),hist["AR0SFOSeemFull"  +syst+"__yield_"+sample].GetBinError(1)
        cSRY["tl0e" +syst+"_"+sample],cSRYerr["tl0e" +syst+"_"+sample] = hist["AR0SFOSemmFull"  +syst+"__yield_"+sample].GetBinContent(1),hist["AR0SFOSemmFull"  +syst+"__yield_"+sample].GetBinError(1)
    return True

    # purity uncertainty - 25% on impurity - scale ddfakes up/down by impurity - Call it PurityUp/Down
def GetPurityUpDownOneRegion(cCRY,cSRY,region):
    if (cCRY[region+"_fakes"]+cCRY[region+"_other"])<=0:
        return False
    purity   = cCRY[region+"_fakes"]/(cCRY[region+"_fakes"]+1.0*cCRY[region+"_other"])
    purityup = cCRY[region+"_fakes"]/(cCRY[region+"_fakes"]+0.7*cCRY[region+"_other"])
    puritydn = cCRY[region+"_fakes"]/(cCRY[region+"_fakes"]+1.3*cCRY[region+"_other"])
    cSRY[region+"PurityUp_ddfakes"  ] = cSRY[region+"_ddfakes"]*purityup/purity
    cSRY[region+"PurityDown_ddfakes"] = cSRY[region+"_ddfakes"]*puritydn/purity
    #print("Region "+region+" - Purity = "+st(purity)+ " + " + st((purityup-purity)/purity) + " - " + st((purity-puritydn)/purity))
    print("Region "+region+" - Purity = "+st(purity)+ " + " + st((purityup-purity)) + " - " + st((purity-puritydn)))
    return True
    
def GetPurityUpDown(cCRY,cSRY):
    GetPurityUpDownOneRegion(cCRY,cSRY,"eein")
    GetPurityUpDownOneRegion(cCRY,cSRY,"emin")
    GetPurityUpDownOneRegion(cCRY,cSRY,"mmin")
    GetPurityUpDownOneRegion(cCRY,cSRY,"eeout")
    GetPurityUpDownOneRegion(cCRY,cSRY,"emout")
    GetPurityUpDownOneRegion(cCRY,cSRY,"mmout")
    GetPurityUpDownOneRegion(cCRY,cSRY,"ee1j")
    GetPurityUpDownOneRegion(cCRY,cSRY,"em1j")
    GetPurityUpDownOneRegion(cCRY,cSRY,"mm1j")
    GetPurityUpDownOneRegion(cCRY,cSRY,"tl0")
    GetPurityUpDownOneRegion(cCRY,cSRY,"tl1")
    GetPurityUpDownOneRegion(cCRY,cSRY,"tl2")
    GetPurityUpDownOneRegion(cCRY,cSRY,"tl0e")
    GetPurityUpDownOneRegion(cCRY,cSRY,"tl0m")
    return True
    # data stats uncertainty - 1:1 - scale ddfakes up/down by datastats - Call it StatsUp/Down
def GetDataUpDownOneRegion(cCRY,cSRY,region):
    data = cCRY[region+"_data"]
    if data <=0:
        return False
    #dataup = statErrorP(cCRY[region+"_data"])
    #datadn = statErrorN(cCRY[region+"_data"])
    #cSRY[region+"StatsUp_ddfakes"  ] = cSRY[region+"_ddfakes"]+cSRY[region+"_ddfakes"]/data*dataup
    #cSRY[region+"StatsDown_ddfakes"] = cSRY[region+"_ddfakes"]-cSRY[region+"_ddfakes"]/data*datadn
    cSRY[region+"StatsUp_ddfakes"  ] = cSRY[region+"_ddfakes"]/data*statErrorP(cCRY[region+"_data"])
    cSRY[region+"StatsDown_ddfakes"] = cSRY[region+"_ddfakes"]/data*statErrorN(cCRY[region+"_data"])
    return True

def GetDataUpDown(cCRY,cSRY):
    GetDataUpDownOneRegion(cCRY,cSRY,"eein")
    GetDataUpDownOneRegion(cCRY,cSRY,"emin")
    GetDataUpDownOneRegion(cCRY,cSRY,"mmin")
    GetDataUpDownOneRegion(cCRY,cSRY,"eeout")
    GetDataUpDownOneRegion(cCRY,cSRY,"emout")
    GetDataUpDownOneRegion(cCRY,cSRY,"mmout")
    GetDataUpDownOneRegion(cCRY,cSRY,"ee1j")
    GetDataUpDownOneRegion(cCRY,cSRY,"em1j")
    GetDataUpDownOneRegion(cCRY,cSRY,"mm1j")
    GetDataUpDownOneRegion(cCRY,cSRY,"tl0")
    GetDataUpDownOneRegion(cCRY,cSRY,"tl1")
    GetDataUpDownOneRegion(cCRY,cSRY,"tl2")
    GetDataUpDownOneRegion(cCRY,cSRY,"tl0e")
    GetDataUpDownOneRegion(cCRY,cSRY,"tl0m")
    return True

def GetHistoUncOneRegion(cSRY,cSRYerr,name):
    cSRY["eeinUnc_" +name] = cSRYerr["eein_" +name]
    cSRY["eminUnc_" +name] = cSRYerr["emin_" +name]
    cSRY["mminUnc_" +name] = cSRYerr["mmin_" +name]
    cSRY["eeoutUnc_"+name] = cSRYerr["eeout_"+name]
    cSRY["emoutUnc_"+name] = cSRYerr["emout_"+name]
    cSRY["mmoutUnc_"+name] = cSRYerr["mmout_"+name]
    cSRY["ee1jUnc_" +name] = cSRYerr["ee1j_" +name]
    cSRY["em1jUnc_" +name] = cSRYerr["em1j_" +name]
    cSRY["mm1jUnc_" +name] = cSRYerr["mm1j_" +name]
    cSRY["tl0Unc_"  +name] = cSRYerr["tl0_"  +name]
    cSRY["tl1Unc_"  +name] = cSRYerr["tl1_"  +name]
    cSRY["tl2Unc_"  +name] = cSRYerr["tl2_"  +name]
    cSRY["tl0eUnc_" +name] = cSRYerr["tl0e_" +name]
    cSRY["tl0mUnc_" +name] = cSRYerr["tl0m_" +name]

def st(myfloat=-.1,prc="%.3f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))

def loadhist(histdict,name,filelist): 
    htemp = filelist["ddfakes"].Get(name)
    histdict[name+"_ddfakes"] = htemp.Clone(name+"_ddfakes")
    if (not (("Up__" in name) or ("Down__" in name))):
        htemp = filelist["fakes"].Get(name)
        histdict[name+"_fakes"] = htemp.Clone(name+"_fakes")
        htemp = filelist["lostlep"].Get(name)
        histdict[name+"_other"] = htemp.Clone(name+"_other")
        htemp = filelist["qflip"].Get(name)
        histdict[name+"_other"].Add(htemp,1.)
        htemp = filelist["photon"].Get(name)
        histdict[name+"_other"].Add(htemp,1.)
        htemp = filelist["prompt"].Get(name)
        histdict[name+"_other"].Add(htemp,1.)
        histdict[name+"_sim"] = histdict[name+"_other"].Clone(name+"_sim")
        histdict[name+"_sim"].Add(histdict[name+"_fakes"],1.)
        htemp = filelist["data"].Get(name)
        histdict[name+"_data"] = htemp.Clone(name+"_data")
    return True

def doPredictionPerRegion(name,prediction,cSRY):
    prediction[name] = cSRY[name+"_ddfakes"]
    prediction[name+"Unc"] = cSRY[name+"Unc_ddfakes"]
    prediction[name+ "Simtruth"   ] = cSRY[name+"_fakes"]
    prediction[name+ "SimtruthErr"] = cSRY[name+"Unc_fakes"]
    prediction[name+ "DataErrUp"  ] = cSRY[name+   "StatsUp_ddfakes"]
    prediction[name+ "DataErrDown"] = cSRY[name+ "StatsDown_ddfakes"]
    prediction[name+  "PurityErrUp"  ]    = cSRY[name+  "PurityUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+  "PurityErrDown"]    = cSRY[name+"_ddfakes"]-cSRY[name+"PurityDown_ddfakes"]
    prediction[name+    "FakeRateElErrUp"  ] = cSRY[name+     "FakeRateElUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+    "FakeRateElErrDown"] = cSRY[name+"_ddfakes"]-cSRY[name+   "FakeRateElDown_ddfakes"]
    prediction[name+    "FakeRateMuErrUp"  ] = cSRY[name+     "FakeRateMuUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+    "FakeRateMuErrDown"] = cSRY[name+"_ddfakes"]-cSRY[name+   "FakeRateMuDown_ddfakes"]
    prediction[name+    "FakeRateErrUp"  ]   = cSRY[name+     "FakeRateUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+    "FakeRateErrDown"]   = cSRY[name+"_ddfakes"]-cSRY[name+   "FakeRateDown_ddfakes"]
    prediction[name+ "FakeClosureElErrUp"  ] = cSRY[name+  "FakeClosureElUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+ "FakeClosureElErrDown"] = cSRY[name+"_ddfakes"]-cSRY[name+"FakeClosureElDown_ddfakes"]
    prediction[name+ "FakeClosureMuErrUp"  ] = cSRY[name+  "FakeClosureMuUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+ "FakeClosureMuErrDown"] = cSRY[name+"_ddfakes"]-cSRY[name+"FakeClosureMuDown_ddfakes"]
    prediction[name+ "FakeClosureErrUp"  ]   = cSRY[name+  "FakeClosureUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+ "FakeClosureErrDown"]   = cSRY[name+"_ddfakes"]-cSRY[name+"FakeClosureDown_ddfakes"]
    prediction[name+    "FakeErrUp"  ]       = cSRY[name+     "FakeUp_ddfakes"]-cSRY[name+"_ddfakes"]
    prediction[name+    "FakeErrDown"]       = cSRY[name+"_ddfakes"]-cSRY[name+   "FakeDown_ddfakes"]
    prediction[name+"SystErrUp"  ]  = math.sqrt(pow(prediction[name+"FakeErrUp"  ],2)+pow(prediction[name+"PurityErrUp"  ],2))
    prediction[name+"SystErrDown"]  = math.sqrt(pow(prediction[name+"FakeErrDown"],2)+pow(prediction[name+"PurityErrDown"],2))
    prediction[name+"TotalErrUp"  ] = math.sqrt(pow(prediction[name+"SystErrUp"  ],2)+pow(prediction[name+"DataErrUp"  ],2))
    prediction[name+"TotalErrDown"] = math.sqrt(pow(prediction[name+"SystErrDown"],2)+pow(prediction[name+"DataErrDown"],2))
    return True

def doPrediction(prediction,cSRY):
    doPredictionPerRegion("eein" ,prediction,cSRY)
    doPredictionPerRegion("emin" ,prediction,cSRY)
    doPredictionPerRegion("mmin" ,prediction,cSRY)
    doPredictionPerRegion("eeout",prediction,cSRY)
    doPredictionPerRegion("emout",prediction,cSRY)
    doPredictionPerRegion("mmout",prediction,cSRY)
    doPredictionPerRegion("ee1j" ,prediction,cSRY)
    doPredictionPerRegion("em1j" ,prediction,cSRY)
    doPredictionPerRegion("mm1j" ,prediction,cSRY)
    doPredictionPerRegion("tl0"  ,prediction,cSRY)
    doPredictionPerRegion("tl1"  ,prediction,cSRY)
    doPredictionPerRegion("tl2"  ,prediction,cSRY)
    return True

    #PrintPredictions(prediction, 3)#full details
    #PrintPredictions(prediction, 2)#don't split e/mu
    #PrintPredictions(prediction, 1)#fake rate
    #PrintPredictions(prediction, 0)#just have syst / stat
    #PrintPredictions(prediction,-1)#total
    #PrintPredictions(prediction,-2)#total Unc

def SavePredictionsIntoRoot(prediction,year):
    directory = getpath(year=year,short=False)
    savehists = dict()
    FillOneHist(savehists,prediction,"")
    FillOneHist(savehists,prediction,"Simtruth")
    FillOneHist(savehists,prediction,"SimtruthErr")
    FillOneHist(savehists,prediction,"DataErrUp")
    FillOneHist(savehists,prediction,"DataErrDown")
    FillOneHist(savehists,prediction,"PurityErrUp")
    FillOneHist(savehists,prediction,"PurityErrDown")
    FillOneHist(savehists,prediction,"FakeRateElErrUp")
    FillOneHist(savehists,prediction,"FakeRateElErrDown")
    FillOneHist(savehists,prediction,"FakeRateMuErrUp")
    FillOneHist(savehists,prediction,"FakeRateMuErrDown")
    FillOneHist(savehists,prediction,"FakeRateErrUp")
    FillOneHist(savehists,prediction,"FakeRateErrDown")
    FillOneHist(savehists,prediction,"FakeClosureElErrUp")
    FillOneHist(savehists,prediction,"FakeClosureElErrDown")
    FillOneHist(savehists,prediction,"FakeClosureMuErrUp")
    FillOneHist(savehists,prediction,"FakeClosureMuErrDown")
    FillOneHist(savehists,prediction,"FakeClosureErrUp")
    FillOneHist(savehists,prediction,"FakeClosureErrDown")
    FillOneHist(savehists,prediction,"FakeErrUp")
    FillOneHist(savehists,prediction,"FakeErrDown")
    FillOneHist(savehists,prediction,"SystErrUp")
    FillOneHist(savehists,prediction,"SystErrDown")
    FillOneHist(savehists,prediction,"TotalErrUp")
    FillOneHist(savehists,prediction,"TotalErrDown")
    fout = ROOT.TFile(directory+"PredictionHistogramsForFakebkg.root","recreate")
    fout.cd()
    for h in savehists.itervalues():
        h.Write()
    fout.Close()
    print ("Wrote prediction into file "+directory+"PredictionHistogramsForFakebkg.root")
    return True

def  FillOneHist(savehists,prediction,whatvariation):
    histoname = whatvariation
    if (whatvariation == ""): histoname = "Yield"
    htemp = ROOT.TH1F(histoname,"",12,0.5,12.5)
    FillOneBin( 1,"eein" ,htemp,prediction,whatvariation)
    FillOneBin( 2,"emin" ,htemp,prediction,whatvariation)
    FillOneBin( 3,"mmin" ,htemp,prediction,whatvariation)
    FillOneBin( 4,"eeout",htemp,prediction,whatvariation)
    FillOneBin( 5,"emout",htemp,prediction,whatvariation)
    FillOneBin( 6,"mmout",htemp,prediction,whatvariation)
    FillOneBin( 7,"ee1j" ,htemp,prediction,whatvariation)
    FillOneBin( 8,"em1j" ,htemp,prediction,whatvariation)
    FillOneBin( 9,"mm1j" ,htemp,prediction,whatvariation)
    FillOneBin(10,"tl0"  ,htemp,prediction,whatvariation)
    FillOneBin(11,"tl1"  ,htemp,prediction,whatvariation)
    FillOneBin(12,"tl2"  ,htemp,prediction,whatvariation)
    savehists[histoname] = htemp
    return True

def FillOneBin(bin,predname,histo,prediction,whatvariation):
    histo.SetBinContent(bin,prediction[predname+whatvariation])
    return True


def StringPredictionOneLine(prediction,name,title,total=0):
    if total ==3:
        return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st( prediction[name+ "DataErrUp"  ]) + "/-" + st(prediction[name+ "DataErrDown"]) + " (stat) +" + st(prediction[name+  "PurityErrUp"  ]) + "/-" + st(prediction[name+  "PurityErrDown"]) + " (purity) +" + st(prediction[name+    "FakeRateElErrUp"  ]) + "/-"+st(prediction[name+    "FakeRateElErrUp"  ]) + " (fr el) +" + st(prediction[name+    "FakeRateMuErrUp"  ]) + "/-"+st(prediction[name+    "FakeRateMuErrUp"  ]) + " (fr Mu) +" + st(prediction[name+    "FakeClosureElErrUp"  ]) + "/-"+st(prediction[name+    "FakeClosureElErrUp"  ]) + " (cl el) +" + st(prediction[name+    "FakeClosureMuErrUp"  ]) + "/-"+st(prediction[name+    "FakeClosureMuErrUp"  ]) + " (cl mu)"
        #return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st( prediction[name+ "DataErrUp"  ]/prediction[name]) + "/-" + st(prediction[name+ "DataErrDown"]/prediction[name]) + " (stat) +" + st(prediction[name+  "PurityErrUp"  ]/prediction[name]) + "/-" + st(prediction[name+  "PurityErrDown"]/prediction[name]) + " (purity) +" + st(prediction[name+    "FakeRateElErrUp"  ]/prediction[name]) + "/-"+st(prediction[name+    "FakeRateElErrUp"  ]/prediction[name]) + " (fr el) +" + st(prediction[name+    "FakeRateMuErrUp"  ]/prediction[name]) + "/-"+st(prediction[name+    "FakeRateMuErrUp"  ]/prediction[name]) + " (fr Mu) +" + st(prediction[name+    "FakeClosureElErrUp"  ]/prediction[name]) + "/-"+st(prediction[name+    "FakeClosureElErrUp"  ]/prediction[name]) + " (cl el) +" + st(prediction[name+    "FakeClosureMuErrUp"  ]/prediction[name]) + "/-"+st(prediction[name+    "FakeClosureMuErrUp"  ]/prediction[name]) + " (cl mu)"
    if total ==2:
        return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st( prediction[name+ "DataErrUp"  ]) + "/-" + st(prediction[name+ "DataErrDown"]) + " (stat) +" + st(prediction[name+  "PurityErrUp"  ]) + "/-" + st(prediction[name+  "PurityErrDown"]) + " (purity) +" + st(prediction[name+    "FakeRateErrUp"  ]) + "/-"+st(prediction[name+    "FakeRateErrUp"  ]) + " (fr) +" + st(prediction[name+    "FakeClosureErrUp"  ]) + "/-"+st(prediction[name+    "FakeClosureErrUp"  ]) + " (cl)"
    if total ==1:
        return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st( prediction[name+ "DataErrUp"  ]) + "/-" + st(prediction[name+ "DataErrDown"]) + " (stat) +" + st(prediction[name+  "PurityErrUp"  ]) + "/-" + st(prediction[name+  "PurityErrDown"]) + " (purity) +" + st(prediction[name+    "FakeErrUp"  ]) + "/-"+st(prediction[name+    "FakeErrUp"  ]) + " (fake syst)"
    if total == 0:
        return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st( prediction[name+ "DataErrUp"  ]) + "/-" + st(prediction[name+ "DataErrDown"]) + " (stat) +" + st(prediction[name+  "SystErrUp"  ]) + "/-" + st(prediction[name+  "SystErrDown"]) + " (syst)"    
    if total == -1:
        return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +" + st( prediction[name+ "TotalErrUp"  ]) + "/-" + st(prediction[name+ "TotalErrDown"])
    if total == -2:
        return title + ": truth = " + st(prediction[name+ "Simtruth"   ]) + "+/-" + st( prediction[name+ "SimtruthErr"]) + ", Prediction = " + st(prediction[name]) + " +/- " + st( prediction[name+ "Unc"  ])
    return ""


def PrintPredictions(prediction,total=0):
    print("\n\n")
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



def getFakeUncertainties(year=-1):
    mydir = getpath(year=year,short=False)
    fileslong = loadfiles(theyear=year,isshort=False)
    hist = dict()
    signalselection  = ["SRSSeeMjjInFull","SRSSemMjjInFull","SRSSmmMjjInFull","SRSSeeMjjOutFull","SRSSemMjjOutFull","SRSSmmMjjOutFull","SRSS1JeeFull","SRSS1JemFull","SRSS1JmmFull","SR0SFOSFull","SR0SFOSeemFull","SR0SFOSemmFull","SR1SFOSFull","SR2SFOSFull"]
    controlselection = ["ARSSeeMjjInFull","ARSSemMjjInFull","ARSSmmMjjInFull","ARSSeeMjjOutFull","ARSSemMjjOutFull","ARSSmmMjjOutFull","ARSS1JeeFull","ARSS1JemFull","ARSS1JmmFull","AR0SFOSFull","AR0SFOSeemFull","AR0SFOSemmFull","AR1SFOSFull","AR2SFOSFull"]
    # ************
    # need extra work for SSxxFull to be made from SSxxMjjInFull and SSxxMjjOutFull
    # ************
    histos = ["yield"]
    #this is MC variations, not ttZ/WZ, Mll validation, or Mjj uncertainties
    #systematics = ["FakeRateEl","FakeRateMu","FakeClosureEl","FakeClosureMu"]
    systematics = ["Fake","FakeRate","FakeRateEl","FakeRateMu","FakeClosure","FakeClosureEl","FakeClosureMu"]
    #systematics = ["Fake","FakeRate","FakeRateEl","FakeRateMu","FakeClosure","FakeClosureEl","FakeClosureMu","FakeRateSSEl","FakeRateSSMu","FakeRate3LEl","FakeRate3LMu","FakeClosureSSEl","FakeClosureSSMu","FakeClosure3LEl","FakeClosure3LMu"]
    finalsyst = systematics + ["Purity","Stats"]

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
    #for name in validationhistos:
    #    #print(name)
    #    #print(filesshort["data"])
    #    loadhist(hist,name,filesshort)
    for name in allhistnames:
        #print(name)
        #print(fileslong["data"])
        loadhist(hist,name,fileslong)
    print("Loaded "+str(len(hist))+" histograms")

    #simply get
    cCRY = dict()
    cCRYerr = dict()
    cSRY = dict()
    cSRYerr = dict()
    ddict = dict()#likely unused
    dummy = -1.
    #cTF["eein" ],cTFerr["eein" ] = getTF(hist[ "SRSSeeMjjInFull__yield_LL"],hist[  "WZCRSSeeFull__yield_LL"])
    #TFlist["eein" +syst+addname],TFlist["eein" +syst+addname] = getTF(histlist[ "SRSSeeMjjInFull"+syst+"__yield_"+process],histlist[  "WZCRSSeeFull"+syst+"__yield_"+process])
    #simply get yields for ddfakes
    LoadSRvars(hist,cSRY,cSRYerr,"","ddfakes",True) #load nominal
    LoadSRvars(hist,cSRY,cSRYerr,"","fakes",  True) #load nominal
    GetHistoUncOneRegion(cSRY,cSRYerr,"ddfakes")
    GetHistoUncOneRegion(cSRY,cSRYerr,"fakes")
    LoadSRvars(hist,cCRY,cCRYerr,"","fakes",  False) #load CR yield - fakes
    LoadSRvars(hist,cCRY,cCRYerr,"","data",   False) #load CR yield - data - get stats from here
    LoadSRvars(hist,cCRY,cCRYerr,"","other",  False) #load CR yield - other
    for s in systematics:
        LoadSRvars(hist,cSRY,cSRYerr,s+"Up",  "ddfakes",True) #load var up
        LoadSRvars(hist,cSRY,cSRYerr,s+"Down","ddfakes",True) #load var down

    # purity uncertainty - 25% on impurity - scale ddfakes up/down by impurity - Call it PurityUp/Down
    GetPurityUpDown(cCRY,cSRY)
    # data stats uncertainty - 1:1 - scale ddfakes up/down by datastats - Call it StatsUp/Down
    GetDataUpDown(cCRY,cSRY)
    # variations
    prediction = dict()
    doPrediction(prediction,cSRY)#do actual up/down in here
    SavePredictionsIntoRoot(prediction,year)

    PrintPredictions(prediction, 3)#full details
    PrintPredictions(prediction, 2)#don't split e/mu
    PrintPredictions(prediction, 1)#fake rate
    PrintPredictions(prediction, 0)#just have syst / stat
    PrintPredictions(prediction,-1)#total
    PrintPredictions(prediction,-2)#total Unc

getFakeUncertainties()
                             

