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

frandom = ROOT.TFile("random.root","recreate")

def getpath(short=True,year=-1,signal=False):
    subpath = "master/"
    if not short:
        subpath = "mastersyst/"
    if signal:
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

def st(myfloat=-.1,prc="%.3f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))

def sst(myfloat=-.1,prc="%.2f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))
def dst(myfloat=-.1,prc="%.5f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))

def loadahistogram(histos,myfile,histoname,processname):
    #print(histoname,myfile.GetName())
    htemp = myfile.Get(histoname)
    frandom.cd()
    histos[processname+histoname] = htemp.Clone(processname+histoname)

def LoadWZprediction(histos):
    fWZ = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/mastersyst/PredictionHistogramsForWZbkg.root")
    loadahistogram(histos,fWZ,"Yield"       ,"WZ")
    loadahistogram(histos,fWZ,"Simtruth"    ,"WZ")
    loadahistogram(histos,fWZ,"SimtruthErr" ,"WZ")
    loadahistogram(histos,fWZ,"DataErrUp"   ,"WZ")
    loadahistogram(histos,fWZ,"DataErrDown" ,"WZ")
    loadahistogram(histos,fWZ,"OtherErrUp"  ,"WZ")
    loadahistogram(histos,fWZ,"OtherErrDown","WZ")
    loadahistogram(histos,fWZ,"TFErrUp"     ,"WZ")
    loadahistogram(histos,fWZ,"TFErrDown"   ,"WZ")
    loadahistogram(histos,fWZ,"TotalUp"     ,"WZ")
    loadahistogram(histos,fWZ,"TotalDown"   ,"WZ")
    loadahistogram(histos,fWZ,"TFstat"      ,"WZ")
    loadahistogram(histos,fWZ,"LepSFUp"     ,"WZ")
    loadahistogram(histos,fWZ,"LepSFDown"   ,"WZ")
    loadahistogram(histos,fWZ,"TrigSFUp"    ,"WZ")
    loadahistogram(histos,fWZ,"TrigSFDown"  ,"WZ")
    loadahistogram(histos,fWZ,"PileupUp"    ,"WZ")
    loadahistogram(histos,fWZ,"PileupDown"  ,"WZ")
    loadahistogram(histos,fWZ,"QsqUp"       ,"WZ")
    loadahistogram(histos,fWZ,"QsqDown"     ,"WZ")
    loadahistogram(histos,fWZ,"PDFUp"       ,"WZ")
    loadahistogram(histos,fWZ,"PDFDown"     ,"WZ")
    loadahistogram(histos,fWZ,"JESUp"       ,"WZ")
    loadahistogram(histos,fWZ,"JESDown"     ,"WZ")
    loadahistogram(histos,fWZ,"WZscaled"    ,"WZ")
    loadahistogram(histos,fWZ,"ttZscaled"   ,"WZ")
    fWZ.Close()
    return True

def LoadFakeprediction(histos):
    fFake = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/mastersyst/PredictionHistogramsForFakebkg.root")
    loadahistogram(histos,fFake,"Yield"               ,"Fake")
    loadahistogram(histos,fFake,"Simtruth"            ,"Fake")
    loadahistogram(histos,fFake,"SimtruthErr"         ,"Fake")
    loadahistogram(histos,fFake,"DataErrUp"           ,"Fake")
    loadahistogram(histos,fFake,"DataErrDown"         ,"Fake")
    loadahistogram(histos,fFake,"PurityErrUp"         ,"Fake")
    loadahistogram(histos,fFake,"PurityErrDown"       ,"Fake")
    loadahistogram(histos,fFake,"FakeRateElErrUp"     ,"Fake")
    loadahistogram(histos,fFake,"FakeRateElErrDown"   ,"Fake")
    loadahistogram(histos,fFake,"FakeRateMuErrUp"     ,"Fake")
    loadahistogram(histos,fFake,"FakeRateMuErrDown"   ,"Fake")
    loadahistogram(histos,fFake,"FakeRateErrUp"       ,"Fake")
    loadahistogram(histos,fFake,"FakeRateErrDown"     ,"Fake")
    loadahistogram(histos,fFake,"FakeClosureElErrUp"  ,"Fake")
    loadahistogram(histos,fFake,"FakeClosureElErrDown","Fake")
    loadahistogram(histos,fFake,"FakeClosureMuErrUp"  ,"Fake")
    loadahistogram(histos,fFake,"FakeClosureMuErrDown","Fake")
    loadahistogram(histos,fFake,"FakeClosureErrUp"    ,"Fake")
    loadahistogram(histos,fFake,"FakeClosureErrDown"  ,"Fake")
    loadahistogram(histos,fFake,"FakeErrUp"           ,"Fake")
    loadahistogram(histos,fFake,"FakeErrDown"         ,"Fake")
    loadahistogram(histos,fFake,"SystErrUp"           ,"Fake")
    loadahistogram(histos,fFake,"SystErrDown"         ,"Fake")
    loadahistogram(histos,fFake,"TotalErrUp"          ,"Fake")
    loadahistogram(histos,fFake,"TotalErrDown"        ,"Fake")
    fFake.Close()
    return True

def LoadQFlipprediction(histos):
    fQ = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/master/PredictionHistogramsForQFlipbkg.root")
    loadahistogram(histos,fQ,"Yield"               ,"QFlip")
    loadahistogram(histos,fQ,"SimStatErr"          ,"QFlip")
    loadahistogram(histos,fQ,"SystErr"             ,"QFlip")
    loadahistogram(histos,fQ,"TotalErr"            ,"QFlip")
    fQ.Close()
    return True

def LoadPromptttWprediction(histos):
    fttW = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/master/PredictionHistogramsForttWbkg.root")
    loadahistogram(histos,fttW,"Yield"               ,"ttW")
    loadahistogram(histos,fttW,"SimStatErr"          ,"ttW")
    loadahistogram(histos,fttW,"SystErr"             ,"ttW")
    loadahistogram(histos,fttW,"TotalErr"            ,"ttW")
    fttW.Close()
    return True

def LoadPromptVBSprediction(histos):
    fvbs = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/master/PredictionHistogramsForVBSbkg.root")
    loadahistogram(histos,fvbs,"Yield"               ,"VBS")
    loadahistogram(histos,fvbs,"SimStatErr"          ,"VBS")
    loadahistogram(histos,fvbs,"SystErr"             ,"VBS")
    loadahistogram(histos,fvbs,"TotalErr"            ,"VBS")
    fvbs.Close()
    return True

def LoadPhotonFakesprediction(histos):
    fG = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/master/PredictionHistogramsForPhotonFakebkg.root")
    loadahistogram(histos,fG,"Yield"               ,"PhotonFake")
    loadahistogram(histos,fG,"SimStatErr"          ,"PhotonFake")
    loadahistogram(histos,fG,"Syst2016Err"         ,"PhotonFake")
    loadahistogram(histos,fG,"Syst2017Err"         ,"PhotonFake")
    loadahistogram(histos,fG,"Syst2018Err"         ,"PhotonFake")
    loadahistogram(histos,fG,"SystErr"             ,"PhotonFake")
    loadahistogram(histos,fG,"TotalErr"            ,"PhotonFake")
    fG.Close()
    return True

def LoadSignalPredictions(histos,signalid="WWW"):
    fsig = ROOT.TFile.Open("hists/combineyearsLoose_v5.3.3/mastersigsyst/PredictionHistogramsFor"+signalid+".root")
    loadahistogram(histos,fsig,"Yield"               ,signalid)
    loadahistogram(histos,fsig,"Yield"               ,signalid)
    loadahistogram(histos,fsig,"PDFErrUp"            ,signalid)
    loadahistogram(histos,fsig,"PDFErrDown"          ,signalid)
    loadahistogram(histos,fsig,"PDFErr"              ,signalid)
    loadahistogram(histos,fsig,"TrigSFErrUp"         ,signalid)
    loadahistogram(histos,fsig,"TrigSFErrDown"       ,signalid)
    loadahistogram(histos,fsig,"TrigSFErr"           ,signalid)
    loadahistogram(histos,fsig,"JESErrUp"            ,signalid)
    loadahistogram(histos,fsig,"JESErrDown"          ,signalid)
    loadahistogram(histos,fsig,"JESErr"              ,signalid)
    loadahistogram(histos,fsig,"PileupErrUp"         ,signalid)
    loadahistogram(histos,fsig,"PileupErrDown"       ,signalid)
    loadahistogram(histos,fsig,"PileupErr"           ,signalid)
    loadahistogram(histos,fsig,"AlphaSErrUp"         ,signalid)
    loadahistogram(histos,fsig,"AlphaSErrDown"       ,signalid)
    loadahistogram(histos,fsig,"AlphaSErr"           ,signalid)
    #loadahistogram(histos,fsig,"LepSFErrUp"          ,signalid)
    #loadahistogram(histos,fsig,"LepSFErrDown"        ,signalid)
    #loadahistogram(histos,fsig,"LepSFErr"            ,signalid)
    loadahistogram(histos,fsig,"MuoSFErrUp"          ,signalid)
    loadahistogram(histos,fsig,"MuoSFErrDown"        ,signalid)
    loadahistogram(histos,fsig,"MuoSFErr"            ,signalid)
    loadahistogram(histos,fsig,"EleSFErrUp"          ,signalid)
    loadahistogram(histos,fsig,"EleSFErrDown"        ,signalid)
    loadahistogram(histos,fsig,"EleSFErr"            ,signalid)
    loadahistogram(histos,fsig,"BTagHFErrUp"         ,signalid)
    loadahistogram(histos,fsig,"BTagHFErrDown"       ,signalid)
    loadahistogram(histos,fsig,"BTagHFErr"           ,signalid)
    loadahistogram(histos,fsig,"BTagLFErrUp"         ,signalid)
    loadahistogram(histos,fsig,"BTagLFErrDown"       ,signalid)
    loadahistogram(histos,fsig,"BTagLFErr"           ,signalid)
    loadahistogram(histos,fsig,"QsqErrUp"            ,signalid)
    loadahistogram(histos,fsig,"QsqErrDown"          ,signalid)
    loadahistogram(histos,fsig,"QsqErr"              ,signalid)
    loadahistogram(histos,fsig,"SimStatErr"          ,signalid)
    loadahistogram(histos,fsig,"SystErr"             ,signalid)
    loadahistogram(histos,fsig,"TotalErr"            ,signalid)
    fsig.Close()
    return True

def LoadAllPredictions(histos, signal=True):
    print("Loading QFlip.")
    LoadQFlipprediction(histos)
    print("Loading ttw.")
    LoadPromptttWprediction(histos)
    print("Loading VBS.")
    LoadPromptVBSprediction(histos)
    print("Loading Photon.")
    LoadPhotonFakesprediction(histos)
    print("Loading Fake.")
    LoadFakeprediction(histos)
    print("Loading WZ.")
    LoadWZprediction(histos)
    #print("b",histos["WZYield"])
    if signal:
        print("Loading signals.")
        LoadSignalPredictions(histos,"WWW")
        LoadSignalPredictions(histos,"WWWonshell")
        LoadSignalPredictions(histos,"WWWhiggs")
        LoadSignalPredictions(histos,"WWZ")
        LoadSignalPredictions(histos,"WWZonshell")
        LoadSignalPredictions(histos,"WWZhiggs")
        LoadSignalPredictions(histos,"WZZ")
        LoadSignalPredictions(histos,"WZZonshell")
        LoadSignalPredictions(histos,"WZZhiggs")
        LoadSignalPredictions(histos,"ZZZ")
        LoadSignalPredictions(histos,"ZZZonshell")
        LoadSignalPredictions(histos,"ZZZhiggs")
        LoadSignalPredictions(histos,"VVV")
        LoadSignalPredictions(histos,"VVVonshell")
        LoadSignalPredictions(histos,"VVVhiggs")
    return True


def MakePromptPrediction():
    MakePromptttWPrediction()
    MakePromptVBSPrediction()
    return True


def MakettWPrediction():
    mydir = getpath(short=True,year=-1)
    TF,TFerr=1.58,0.21
    fttwin = ROOT.TFile.Open(mydir+"prompt.root")
    httwtempX = LoadCentralPredictionAndPutThemIntoAHistogram(fttwin,"ttWTempX")
    fvbsin = ROOT.TFile.Open(mydir+"vbs.root")
    hvbstemp = LoadCentralPredictionAndPutThemIntoAHistogram(fvbsin,"VBSTemp")
    httwtemp = httwtempX.Clone("ttwTemp")
    httwtemp.Add(hvbstemp,-1)
    fttwout = ROOT.TFile(mydir+"PredictionHistogramsForttWbkg.root","recreate")
    fttwout.cd()
    hcentral = ROOT.TH1F("Yield","",     12,0.5,12.5)
    hstat    = ROOT.TH1F("SimStatErr","",12,0.5,12.5)
    hsyst    = ROOT.TH1F("SystErr","",   12,0.5,12.5)
    htotal   = ROOT.TH1F("TotalErr","",  12,0.5,12.5)
    #do something here
    for i in range(1,13):
        hcentral.SetBinContent(i,TF*httwtemp.GetBinContent(i))
        hstat.SetBinContent(i,TF*httwtemp.GetBinError(i))
        hsyst.SetBinContent(i,TF*httwtemp.GetBinContent(i)*TFerr)
        htotal.SetBinContent(i,math.sqrt(pow(TF*httwtemp.GetBinContent(i)*TFerr,2)+pow(TF*httwtemp.GetBinError(i),2)))
    hcentral.Write()
    hstat.Write()
    hsyst.Write()
    htotal.Write()
    fttwout.Close()
    print("Wrote ttW(nonVBS) prediction into "+mydir+"PredictionHistogramsForttWbkg.root")
    return True

def MakeVBSPrediction():
    mydir = getpath(short=True,year=-1)
    TF,TFerr=1.,0.1
    fvbsin = ROOT.TFile.Open(mydir+"vbs.root")
    hvbstemp = LoadCentralPredictionAndPutThemIntoAHistogram(fvbsin,"VBSTemp")
    fvbsout = ROOT.TFile(mydir+"PredictionHistogramsForVBSbkg.root","recreate")
    fvbsout.cd()
    hcentral = ROOT.TH1F("Yield","",     12,0.5,12.5)
    hstat    = ROOT.TH1F("SimStatErr","",12,0.5,12.5)
    hsyst    = ROOT.TH1F("SystErr","",   12,0.5,12.5)
    htotal   = ROOT.TH1F("TotalErr","",  12,0.5,12.5)
    #do something here
    for i in range(1,13):
        hcentral.SetBinContent(i,hvbstemp.GetBinContent(i))
        hstat.SetBinContent(i,hvbstemp.GetBinError(i))
        hsyst.SetBinContent(i,hvbstemp.GetBinContent(i)*TFerr)
        htotal.SetBinContent(i,math.sqrt(pow(hvbstemp.GetBinContent(i)*TFerr,2)+pow(hvbstemp.GetBinError(i),2)))
    hcentral.Write()
    hstat.Write()
    hsyst.Write()
    htotal.Write()
    fvbsout.Close()
    print("Wrote VBS prediction into "+mydir+"PredictionHistogramsForVBSbkg.root")
    return True

def MakePhotonFakePrediction():
    mydir = getpath(short=True,year=-1)
    TF2016,TF2016err, TF2017,TF2017err, TF2018,TF2018err = 0.895,0.079, 0.445,0.047, 0.506,0.031
    fgamma2016 = ROOT.TFile.Open(getpath(short=True,year=2016)+"photon.root")
    hGtemp2016 = LoadCentralPredictionAndPutThemIntoAHistogram(fgamma2016,"PhotonTemp2016")
    fgamma2017 = ROOT.TFile.Open(getpath(short=True,year=2017)+"photon.root")
    hGtemp2017 = LoadCentralPredictionAndPutThemIntoAHistogram(fgamma2017,"PhotonTemp2016")
    fgamma2018 = ROOT.TFile.Open(getpath(short=True,year=2018)+"photon.root")
    hGtemp2018 = LoadCentralPredictionAndPutThemIntoAHistogram(fgamma2018,"PhotonTemp2016")
    fPhotonout = ROOT.TFile(mydir+"PredictionHistogramsForPhotonFakebkg.root","recreate")
    fPhotonout.cd()
    hcentral  = ROOT.TH1F("Yield","",      12,0.5,12.5)
    hstat     = ROOT.TH1F("SimStatErr","", 12,0.5,12.5)
    hsyst2016 = ROOT.TH1F("Syst2016Err","",12,0.5,12.5)
    hsyst2017 = ROOT.TH1F("Syst2017Err","",12,0.5,12.5)
    hsyst2018 = ROOT.TH1F("Syst2018Err","",12,0.5,12.5)
    hsyst     = ROOT.TH1F("SystErr","",    12,0.5,12.5)
    htotal    = ROOT.TH1F("TotalErr","",   12,0.5,12.5)
    #do something here
    for i in range(1,13):
        hcentral.SetBinContent(i,TF2016*hGtemp2016.GetBinContent(i)+TF2017*hGtemp2017.GetBinContent(i)+TF2018*hGtemp2018.GetBinContent(i))
        hstat.SetBinContent(i,math.sqrt(pow(TF2016*hGtemp2016.GetBinError(i),2)+pow(TF2017*hGtemp2017.GetBinError(i),2)+pow(TF2018*hGtemp2018.GetBinError(i),2)))
        hsyst.SetBinContent(i,TF2016err*hGtemp2016.GetBinContent(i)+TF2017err*hGtemp2017.GetBinContent(i)+TF2018err*hGtemp2018.GetBinContent(i)) #I add them linearly, assume full correlation
        hsyst2016.SetBinContent(i,TF2016err*hGtemp2016.GetBinContent(i))
        hsyst2017.SetBinContent(i,TF2017err*hGtemp2017.GetBinContent(i))
        hsyst2018.SetBinContent(i,TF2018err*hGtemp2018.GetBinContent(i))
        htotal.SetBinContent(i,math.sqrt(pow(TF2016*hGtemp2016.GetBinError(i),2)+pow(TF2017*hGtemp2017.GetBinError(i),2)+pow(TF2018*hGtemp2018.GetBinError(i),2) +   pow(TF2016err*hGtemp2016.GetBinContent(i)+TF2017err*hGtemp2017.GetBinContent(i)+TF2018err*hGtemp2018.GetBinContent(i),2)) )
    hcentral.Write()
    hstat.Write()
    hsyst2016.Write()
    hsyst2017.Write()
    hsyst2018.Write()
    hsyst.Write()
    htotal.Write()
    fPhotonout.Close()
    print("Wrote PhotonFake prediction into "+mydir+"PredictionHistogramsForPhotonFakebkg.root")
    return True


def MakeQFlipPrediction():
    mydir = getpath(short=True,year=-1)
    TF,TFerr=1.,0.2
    fQlipin = ROOT.TFile.Open(mydir+"qflip.root")
    hQtemp = LoadCentralPredictionAndPutThemIntoAHistogram(fQlipin,"QFlipTemp")
    fQflipout = ROOT.TFile(mydir+"PredictionHistogramsForQFlipbkg.root","recreate")
    fQflipout.cd()
    hcentral = ROOT.TH1F("Yield","",     12,0.5,12.5)
    hstat    = ROOT.TH1F("SimStatErr","",12,0.5,12.5)
    hsyst    = ROOT.TH1F("SystErr","",   12,0.5,12.5)
    htotal   = ROOT.TH1F("TotalErr","",  12,0.5,12.5)
    #do something here
    for i in range(1,13):
        hcentral.SetBinContent(i,hQtemp.GetBinContent(i))
        hstat.SetBinContent(i,hQtemp.GetBinError(i))
        hsyst.SetBinContent(i,hQtemp.GetBinContent(i)*TFerr)
        htotal.SetBinContent(i,math.sqrt(pow(hQtemp.GetBinContent(i)*TFerr,2)+pow(hQtemp.GetBinError(i),2)))
    hcentral.Write()
    hstat.Write()
    hsyst.Write()
    htotal.Write()
    fQflipout.Close()
    print("Wrote ChargeFlip prediction into "+mydir+"PredictionHistogramsForQFlipbkg.root")
    return True

def MakeSignalPrediction(signal=0):
    # 0: www+wh,  1: www,  2: wh
    #10: wwz+zh, 11: wwz, 12: zh
    #20: wzz+wh, 21: wzz, 22: wh
    #30: zzz+zh, 31: zzz, 32: zh
    #40: vvv+vh, 41: vvv, 42: vh
    if signal == 1:
        MakeSignalPredictionOne("www_onshell","WWWonshell")
    if signal == 2:
        MakeSignalPredictionOne("wh_www","WWWhiggs")
    if signal == 0:
        MakeSignalPredictionOne("www_all","WWW")
    if signal == 11:
        MakeSignalPredictionOne("wwz_onshell","WWZonshell")
    if signal == 12:
        MakeSignalPredictionOne("zh_wwz","WWZhiggs")
    if signal == 10:
        MakeSignalPredictionOne("wwz_all","WWZ")
    if signal == 21:
        MakeSignalPredictionOne("wzz_onshell","WZZonshell")
    if signal == 22:
        MakeSignalPredictionOne("wh_wzz","WZZhiggs")
    if signal == 20:
        MakeSignalPredictionOne("wzz_all","WZZ")
    if signal == 31:
        MakeSignalPredictionOne("zzz_onshell","ZZZonshell")
    if signal == 32:
        MakeSignalPredictionOne("zh_zzz","ZZZhiggs")
    if signal == 30:
        MakeSignalPredictionOne("zzz_all","ZZZ")
    if signal == 41:
        MakeSignalPredictionOne("vvv_onshell","VVVonshell")
    if signal == 42:
        MakeSignalPredictionOne("vvv_higgs","VVVhiggs")
    if signal == 40:
        MakeSignalPredictionOne("vvv_all","VVV")
    return True

def MakeSignalPredictionAll():
    MakeSignalPrediction(0)
    MakeSignalPrediction(1)
    MakeSignalPrediction(2)
    MakeSignalPrediction(10)
    MakeSignalPrediction(11)
    MakeSignalPrediction(12)
    MakeSignalPrediction(20)
    MakeSignalPrediction(21)
    MakeSignalPrediction(22)
    MakeSignalPrediction(30)
    MakeSignalPrediction(31)
    MakeSignalPrediction(32)
    MakeSignalPrediction(40)
    MakeSignalPrediction(41)
    MakeSignalPrediction(42)
    return True
def MakeSignalPredictionOne(signalin,signalout): #0: www+wh, 1: www, 2: wh
    mydir = getpath(short=False,year=-1,signal=True)
    #systematics = ["LepSF","TrigSF","Pileup","Qsq","PDF","JES","AlphaS","BTagLF","BTagHF"]
    systematics = ["EleSF","MuoSF","TrigSF","Pileup","Qsq","PDF","JES","AlphaS","BTagLF","BTagHF"]
    fsigin = ROOT.TFile.Open(mydir+signalin+".root")
    temphistos = dict()
    temphistos["Yield"] = LoadCentralPredictionAndPutThemIntoAHistogram(fsigin,signalout+"Temp")
    for s in systematics:
        temphistos[s+"Up"] = LoadCentralPredictionAndPutThemIntoAHistogram(fsigin,signalout+"Temp",s+"Up")
        temphistos[s+"Down"] = LoadCentralPredictionAndPutThemIntoAHistogram(fsigin,signalout+"Temp",s+"Down")
    savehistos = dict()
    savehistos["Yield"]    = ROOT.TH1F("Yield"     ,"",12,0.5,12.5)
    savehistos["StatErr"]  = ROOT.TH1F("SimStatErr","",12,0.5,12.5)
    savehistos["SystErr"]  = ROOT.TH1F("SystErr"   ,"",12,0.5,12.5)
    savehistos["TotalErr"] = ROOT.TH1F("TotalErr"  ,"",12,0.5,12.5)
    for s in systematics:
        savehistos[s+"Up"]   = ROOT.TH1F(s+"ErrUp"  ,"",12,0.5,12.5)
        savehistos[s+"Down"] = ROOT.TH1F(s+"ErrDown","",12,0.5,12.5)
        savehistos[s+"Err"]  = ROOT.TH1F(s+"Err"    ,"",12,0.5,12.5)
    for i in range(1,13):
        savehistos["Yield"].SetBinContent(i,temphistos["Yield"].GetBinContent(i))
        savehistos["StatErr"].SetBinContent(i,temphistos["Yield"].GetBinError(i))
        for s in systematics:
            savehistos[s+"Up"  ].SetBinContent(i,temphistos[s+"Up"  ].GetBinContent(i)-temphistos["Yield"].GetBinContent(i))
            savehistos[s+"Down"].SetBinContent(i,temphistos["Yield"].GetBinContent(i)-temphistos[s+"Down"].GetBinContent(i))
            savehistos[s+"Err" ].SetBinContent(i,math.sqrt(abs(temphistos[s+"Down"].GetBinContent(i)-temphistos["Yield"].GetBinContent(i))*abs(temphistos[s+"Up"  ].GetBinContent(i)-temphistos["Yield"].GetBinContent(i))))
            savehistos["SystErr"].SetBinContent(i,math.sqrt(pow(savehistos["SystErr"].GetBinContent(i),2)+pow(savehistos[s+"Err"].GetBinContent(i),2) ) )
            #print(i,s,"Central",savehistos["Yield"].GetBinContent(i),"stat",savehistos["StatErr"].GetBinContent(i),"systS",savehistos[s+"Err" ].GetBinContent(i),"systTot",savehistos["SystErr" ].GetBinContent(i))
        savehistos["TotalErr"].SetBinContent(i,math.sqrt(pow(savehistos["SystErr"].GetBinContent(i),2)+pow(savehistos["StatErr"].GetBinContent(i),2) ) )
    #for i in range(1,13):
    #    print(signalout + " " + st(i) + " statistics " + st(savehistos["StatErr"].GetBinContent(i)/savehistos["Yield"].GetBinContent(i)))
    #for s in systematics:
    #    for i in range(1,13):
    #        print(signalout + " " + st(i) + " systematic " + s + "  " + st(savehistos[s+"Err" ].GetBinContent(i)/savehistos["Yield"].GetBinContent(i)))
    fsigout = ROOT.TFile(mydir+"PredictionHistogramsFor"+signalout+".root","recreate")
    fsigout.cd()
    for h in savehistos.itervalues():
        h.Write()
    fsigout.Close()
    print("Wrote signal prediction into "+mydir+"PredictionHistogramsFor"+signalout+".root")
    return True
    
def MakeBkgSum(histos):
    histos["BkgYield"]    = ROOT.TH1F("BkgYield"   ,"",12,0.5,12.5)
    histos["BkgTotalErr"] = ROOT.TH1F("BkgTotalErr","",12,0.5,12.5)
    histos["TotYield"]    = ROOT.TH1F("TotYield"   ,"",12,0.5,12.5)
    histos["TotTotalErr"] = ROOT.TH1F("TotTotalErr","",12,0.5,12.5)
    #print(histos["WZYield"],histos["FakeYield"],histos["ttWYield"],histos["VBSYield"],histos["PhotonFakeYield"],histos["QFlipYield"],histos["WWWYield"])
    for i in range(1,13):
        histos["TotYield"].SetBinContent(i,histos["WZYield"].GetBinContent(i)+histos["FakeYield"].GetBinContent(i)+histos["ttWYield"].GetBinContent(i)+histos["VBSYield"].GetBinContent(i)+histos["PhotonFakeYield"].GetBinContent(i)+histos["QFlipYield"].GetBinContent(i)+histos["WWWYield"].GetBinContent(i))
        histos["TotTotalErr"].SetBinContent(i,math.sqrt(pow(math.sqrt(histos["WZTotalUp"].GetBinContent(i)*histos["WZTotalDown"].GetBinContent(i)),2)+pow(math.sqrt(histos["FakeTotalErrUp"].GetBinContent(i)*histos["FakeTotalErrDown"].GetBinContent(i)),2)+pow(histos["ttWTotalErr"].GetBinContent(i),2)+pow(histos["VBSTotalErr"].GetBinContent(i),2)+pow(histos["PhotonFakeTotalErr"].GetBinContent(i),2)+pow(histos["QFlipTotalErr"].GetBinContent(i),2)+pow(histos["WWWTotalErr"].GetBinContent(i),2)))
        histos["BkgYield"].SetBinContent(i,histos["WZYield"].GetBinContent(i)+histos["FakeYield"].GetBinContent(i)+histos["ttWYield"].GetBinContent(i)+histos["VBSYield"].GetBinContent(i)+histos["PhotonFakeYield"].GetBinContent(i)+histos["QFlipYield"].GetBinContent(i))
        histos["BkgTotalErr"].SetBinContent(i,math.sqrt(pow(math.sqrt(histos["WZTotalUp"].GetBinContent(i)*histos["WZTotalDown"].GetBinContent(i)),2)+pow(math.sqrt(histos["FakeTotalErrUp"].GetBinContent(i)*histos["FakeTotalErrDown"].GetBinContent(i)),2)+pow(histos["ttWTotalErr"].GetBinContent(i),2)+pow(histos["VBSTotalErr"].GetBinContent(i),2)+pow(histos["PhotonFakeTotalErr"].GetBinContent(i),2)+pow(histos["QFlipTotalErr"].GetBinContent(i),2)))
    return True

def MakeDataFile():
    mydir = getpath(short=True,year=-1,signal=False)
    h    = ROOT.TH1F("Yield"   ,"",12,0.5,12.5)
    filein = ROOT.TFile.Open(mydir+"data.root")
    htemp = filein.Get("SRSSeeMjjInFull__yield")
    h.SetBinContent( 1,htemp.GetBinContent(1))
    htemp = filein.Get("SRSSemMjjInFull__yield")
    h.SetBinContent( 2,htemp.GetBinContent(1))
    htemp = filein.Get("SRSSmmMjjInFull__yield")
    h.SetBinContent( 3,htemp.GetBinContent(1))
    htemp = filein.Get("SRSSeeMjjOutFull__yield")
    h.SetBinContent( 4,htemp.GetBinContent(1))
    htemp = filein.Get("SRSSemMjjOutFull__yield")
    h.SetBinContent( 5,htemp.GetBinContent(1))
    htemp = filein.Get("SRSSmmMjjOutFull__yield")
    h.SetBinContent( 6,htemp.GetBinContent(1))
    htemp = filein.Get("SRSS1JeeFull__yield")
    h.SetBinContent( 7,htemp.GetBinContent(1))
    htemp = filein.Get("SRSS1JemFull__yield")
    h.SetBinContent( 8,htemp.GetBinContent(1))
    htemp = filein.Get("SRSS1JmmFull__yield")
    h.SetBinContent( 9,htemp.GetBinContent(1))
    htemp = filein.Get("SR0SFOSFull__yield")
    h.SetBinContent(10,htemp.GetBinContent(1))
    htemp = filein.Get("SR1SFOSFull__yield")
    h.SetBinContent(11,htemp.GetBinContent(1))
    htemp = filein.Get("SR2SFOSFull__yield")
    h.SetBinContent(12,htemp.GetBinContent(1))
    fdata = ROOT.TFile(mydir+"DataYieldHistogram.root","RECREATE")
    fdata.cd()
    h.Write()
    fdata.Close()
    print("Wrote data yields into "+mydir+"DataYieldHistogram.root")

def LoadDataHistogram(histos):
    mydir = getpath(short=True,year=-1,signal=False)
    fdata = ROOT.TFile.Open(mydir+"DataYieldHistogram.root")
    loadahistogram(histos,fdata,"Yield"               ,"Data")


def LoadCentralPredictionAndPutThemIntoAHistogram(myfile,histoname,variation=""):
    h = ROOT.TH1F(histoname+variation,"",12,0.5,12.5)
    htemp = myfile.Get("SRSSeeMjjInFull"+variation+"__yield")
    h.SetBinContent(1,htemp.GetBinContent(1))
    h.SetBinError(  1,htemp.GetBinError(1))
    htemp = myfile.Get("SRSSemMjjInFull"+variation+"__yield")
    h.SetBinContent(2,htemp.GetBinContent(1))
    h.SetBinError(  2,htemp.GetBinError(1))
    htemp = myfile.Get("SRSSmmMjjInFull"+variation+"__yield")
    h.SetBinContent(3,htemp.GetBinContent(1))
    h.SetBinError(  3,htemp.GetBinError(1))
    htemp = myfile.Get("SRSSeeMjjOutFull"+variation+"__yield")
    h.SetBinContent(4,htemp.GetBinContent(1))
    h.SetBinError(  4,htemp.GetBinError(1))
    htemp = myfile.Get("SRSSemMjjOutFull"+variation+"__yield")
    h.SetBinContent(5,htemp.GetBinContent(1))
    h.SetBinError(  5,htemp.GetBinError(1))
    htemp = myfile.Get("SRSSmmMjjOutFull"+variation+"__yield")
    h.SetBinContent(6,htemp.GetBinContent(1))
    h.SetBinError(  6,htemp.GetBinError(1))
    htemp = myfile.Get("SRSS1JeeFull"+variation+"__yield")
    h.SetBinContent(7,htemp.GetBinContent(1))
    h.SetBinError(  7,htemp.GetBinError(1))
    htemp = myfile.Get("SRSS1JemFull"+variation+"__yield")
    h.SetBinContent(8,htemp.GetBinContent(1))
    h.SetBinError(  8,htemp.GetBinError(1))
    htemp = myfile.Get("SRSS1JmmFull"+variation+"__yield")
    h.SetBinContent(9,htemp.GetBinContent(1))
    h.SetBinError(  9,htemp.GetBinError(1))
    htemp = myfile.Get("SR0SFOSFull"+variation+"__yield")
    h.SetBinContent(10,htemp.GetBinContent(1))
    h.SetBinError(  10,htemp.GetBinError(1))
    htemp = myfile.Get("SR1SFOSFull"+variation+"__yield")
    h.SetBinContent(11,htemp.GetBinContent(1))
    h.SetBinError(  11,htemp.GetBinError(1))
    htemp = myfile.Get("SR2SFOSFull"+variation+"__yield")
    h.SetBinContent(12,htemp.GetBinContent(1))
    h.SetBinError(  12,htemp.GetBinError(1))
    return h

"""
def GetSystematics(histos):
    PrintWZSystematics(histos)
    PrintFakeSystematics(histos)
    PrintOtherSystematics(histos)
    PrintSignalSystematics(histos)
"""

def MakeFinalTable(histos,wide=False,usedata=False):
    tablestring = \
    "\\begin{table}[htb]\n" + \
    "\\centering\n" + \
    "\\resizebox*{1.0\\textwidth}{!} {\\renewcommand{\\arraystretch}{1.2}\n" + \
    "\\begin{tabular}{l|cccccccccccc}\n" + \
    "\\hline \n" + \
    "Signal &  \multicolumn{3}{c}{SS \Mjjin} & \multicolumn{3}{c}{SS \Mjjout} & \multicolumn{3}{c}{SS 1j} & \multicolumn{3}{c}{$3\\ell$} \\\\\n" + \
    "region & \\SSee & \\SSem & \\SSmm & \\SSee & \\SSem & \\SSmm & \\SSee & \\SSem & \\SSmm & 0\\,SFOS & 1\\,SFOS & 2\,SFOS \\\\\n" + \
    "\\hline \n"
    r = "%.1f"
    if wide:
        r = "%.4f"
    tablestring = tablestring + "Lost/three $\\ell$"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WZYield"].GetBinContent(i),r) + "$\\pm$" + st(min(math.sqrt(histos["WZTotalUp"].GetBinContent(i)*histos["WZTotalDown"].GetBinContent(i)),histos["WZYield"].GetBinContent(i)),r)
    tablestring = tablestring + "\\\\\n" + "Irreducible"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["ttWYield"].GetBinContent(i)+histos["VBSYield"].GetBinContent(i),r) + "$\\pm$" + st(min(math.sqrt(pow(histos["ttWTotalErr"].GetBinContent(i),2)+pow(histos["VBSTotalErr"].GetBinContent(i),2) ),histos["ttWYield"].GetBinContent(i)+histos["VBSYield"].GetBinContent(i)),r)
    tablestring = tablestring + "\\\\\n" + "Nonprompt $\\ell$"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["FakeYield"].GetBinContent(i),r) + "$\\pm$" + st(min(math.sqrt(histos["FakeTotalErrUp"].GetBinContent(i)*histos["FakeTotalErrDown"].GetBinContent(i)),histos["FakeYield"].GetBinContent(i)),r)
    tablestring = tablestring + "\\\\\n" + "Charge flips"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["QFlipYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["QFlipTotalErr"].GetBinContent(i),histos["QFlipYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "$\\gamma\\to\\text{ nonprompt }\\ell$"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["PhotonFakeYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["PhotonFakeTotalErr"].GetBinContent(i),histos["PhotonFakeYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "Background sum"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["BkgYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["BkgTotalErr"].GetBinContent(i),histos["BkgYield"].GetBinContent(i)),r)
    #WWW
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "\\WWW onshell"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WWWonshellYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WWWonshellTotalErr"].GetBinContent(i),histos["WWWonshellYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\WHtoWWW"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WWWhiggsYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WWWhiggsTotalErr"].GetBinContent(i),histos["WWWhiggsYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\WWW total"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WWWYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WWWTotalErr"].GetBinContent(i),histos["WWWYield"].GetBinContent(i)),r)
    ######################3
    #WWZ
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "\\WWZ onshell"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WWZonshellYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WWZonshellTotalErr"].GetBinContent(i),histos["WWZonshellYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\VHWWZ"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WWZhiggsYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WWZhiggsTotalErr"].GetBinContent(i),histos["WWZhiggsYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\WWZ total"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WWZYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WWZTotalErr"].GetBinContent(i),histos["WWZYield"].GetBinContent(i)),r) 
    #WZZ
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "\\WZZ onshell"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WZZonshellYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WZZonshellTotalErr"].GetBinContent(i),histos["WZZonshellYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\VHWZZ"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WZZhiggsYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WZZhiggsTotalErr"].GetBinContent(i),histos["WZZhiggsYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\WZZ total"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["WZZYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["WZZTotalErr"].GetBinContent(i),histos["WZZYield"].GetBinContent(i)),r) 
    #ZZZ
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "\\ZZZ onshell"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["ZZZonshellYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["ZZZonshellTotalErr"].GetBinContent(i),histos["ZZZonshellYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\VHZZZ"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["ZZZhiggsYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["ZZZhiggsTotalErr"].GetBinContent(i),histos["ZZZhiggsYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\ZZZ total"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["ZZZYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["ZZZTotalErr"].GetBinContent(i),histos["ZZZYield"].GetBinContent(i)),r) 
    #VVV
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "\\VVV onshell"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["VVVonshellYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["VVVonshellTotalErr"].GetBinContent(i),histos["VVVonshellYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\VHVVV"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["VVVhiggsYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["VVVhiggsTotalErr"].GetBinContent(i),histos["VVVhiggsYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\VVV total"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["VVVYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["VVVTotalErr"].GetBinContent(i),histos["VVVYield"].GetBinContent(i)),r) 
    ######################
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "Total (w/ WWW only)"
    for i in range(1,13):
        tablestring = tablestring + " & " + st(histos["TotYield"].GetBinContent(i),r) + "$\\pm$" + st(min(histos["TotTotalErr"].GetBinContent(i),histos["TotYield"].GetBinContent(i)),r) 
    tablestring = tablestring + "\\\\\n" + "\\hline \n" + "Observed"
    if usedata:
        for i in range(1,13):
            tablestring = tablestring + " & " + st(histos["DataYield"].GetBinContent(i),"%.0f")
    else:
        for i in range(1,13):
            tablestring = tablestring + " & " + "\\NA"
    tablestring = tablestring + \
    "\\\\\n" + "\\hline\n" + \
    "\\end{tabular}\n" + \
    "}\n" + \
    "\\end{table}\n"

    print(tablestring)
    
#def MakeSystematicsTable(histos):

def PrintPredictions(usedata=False):
    histos = dict()
    LoadAllPredictions(histos)
    LoadDataHistogram(histos)
    #for h in histos:
    #    print(h)
    MakeBkgSum(histos)
    #GetSystematics(histos)
    MakeFinalTable(histos,False,usedata)
    MakeFinalTable(histos,True,usedata)
    

#MakeQFlipPrediction()
#MakePhotonFakePrediction()
#MakeVBSPrediction()
#MakettWPrediction()
"""
MakeSignalPrediction(0)
MakeSignalPrediction(1)
MakeSignalPrediction(2)
MakeSignalPrediction(10)
MakeSignalPrediction(11)
MakeSignalPrediction(12)
MakeSignalPrediction(20)
MakeSignalPrediction(21)
MakeSignalPrediction(22)
MakeSignalPrediction(30)
MakeSignalPrediction(31)
MakeSignalPrediction(32)
MakeSignalPrediction(40)
MakeSignalPrediction(41)
MakeSignalPrediction(42)
"""
#MakeSignalPredictionAll()
#MakeDataFile()
    
PrintPredictions()#blinded
#PrintPredictions(True)#unblind
