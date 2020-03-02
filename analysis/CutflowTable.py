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

def getpath(year=-1,signal=False):
    subpath = "cutflow/"
    if signal:
        subpath = "cutflowsig/"
    versionpath = "_v5.3.2/"
    typepath = "Loose"
    prepath = "hists/combineyears"+typepath+versionpath
    if year == 2016:
        prepath = "hists/"+typepath+"2016" + versionpath
    if year == 2017:
        prepath = "hists/"+typepath+"2017" + versionpath
    if year == 2018:
        prepath = "hists/"+typepath+"2018"+ versionpath
    return prepath + subpath

def stringSingleLineCutflowTable(hists, hist, cut, name):
    LLy , LLe   = getYieldAndErrorX(hists[hist+    "_LL"],cut)
    Irry, Irre  = getYieldAndErrorX(hists[hist+   "_Irr"],cut)
    Fakey,Fakee = getYieldAndErrorX(hists[hist+ "_Fakes"],cut)
    Qy,   Qe    = getYieldAndErrorX(hists[hist+"_Qflips"],cut)
    Photy,Phote = getYieldAndErrorX(hists[hist+ "_Gamma"],cut)
    WWWy, WWWe  = getYieldAndErrorX(hists[hist+   "_WWW"],cut)
    WHy,  WHe   = getYieldAndErrorX(hists[hist+    "_WH"],cut)
    VVVy, VVVe  = getYieldAndErrorX(hists[hist+   "_VVV"],cut)
    VHy,  VHe   = getYieldAndErrorX(hists[hist+    "_VH"],cut)
    Bkgy  = LLy+Irry+Fakey+Qy+Photy
    Bkge  = math.sqrt(pow(LLe,2)+pow(Irre,2)+pow(Fakee,2)+pow(Qe,2)+pow(Phote,2))
    WVZy  = max(0.,VVVy-WWWy)
    WVZe  = math.sqrt(max(0.,pow(VVVe,2)-pow(WWWe,2)))
    WVZHy = max(0.,VHy-WHy)
    WVZHe = math.sqrt(max(0.,pow(VHe,2)-pow(WHe,2)))
    return name + " & " + stye(LLy,LLe) + " & " + stye(Irry,Irre) + " & " + stye(Fakey,Fakee) + " & " + stye(Qy,Qe) + " & " + stye(Photy,Phote) + " & " + stye(Bkgy,Bkge) + " & " + stye(WWWy,WWWe) + " & " + stye(WHy,WHe) + " & " + stye(WVZy,WVZe) + " & " + stye(WVZHy,WVZHe) + " \\\\"

def stye(myyield,myerror):
    return "$"+ st(myyield) + "\\pm" + st(myerror) + "$"

def CreateCutflowTable(hists,histlist,cutslist,namelist):
    print("")
    print("\\begin{table}")
    print("\\centering")
    print("\\topcaption{\\label{tab::cutflow} Cutflow table for .}")
    print("\\resizebox*{1.0\\textwidth}{!} {\\renewcommand{\\arraystretch}{1.2}")
    print("\\begin{tabular}{lcccccccccc}")
    print("\\hline\\hline")
    print(" & Lost/         & Irre-   & Nonprompt & Charge & $\\gamma\\to$     & Bkg & \\WWW   & \\WH\\to  & \\PW{}\\PV{}\PZ{} & \\PW{}\\PV{}\PZ{} \\\\")
    print(" & three $\\ell$ & ducible & $\\ell$   & flips  & nonprompt $\\ell$ & sum & onshell & \\WWW^{*} & onshell           & through \\PH      \\\\")
    print("\\hline")
    for h,c,n in zip(histlist,cutslist,namelist):
        print(stringSingleLineCutflowTable(hists,h,c,n))
    print("\\hline\\hline")
    print("\\end{tabular}")
    print("}")
    print("\\end{table}")
    print("")
    
def loadHisto(hists,myfile,histname,sample):
    #print (fF.GetName())
    htemp = myfile.Get(histname)
    hists[histname+"_"+sample] = htemp.Clone(histname+"_"+sample)
    return True

def loadHistos(hists,myfile,histlist,sample):
    #print (fF.GetName())
    for h in histlist:
        loadHisto(hists,myfile,h,sample)
    return True

def getYieldAndErrorX(hist,cut):
    myyield, myerror = ROOT.Double(),ROOT.Double()
    if cut == 0 or cut ==1:
        return getYieldAndErrorNJ(hist,cut)
    return getYieldAndError(hist,cut)
def getYieldAndErrorXOthSig(hist,cut):
    myyield, myerror = ROOT.Double(),ROOT.Double()
    if cut == 0 or cut ==1:
        return getYieldAndErrorNJOthSig(hist,cut)
    return getYieldAndErrorOthSig(hist,cut)

def getYieldAndError(hist,cut):
    nbinlow = int(1)
    nbinhigh = int(hist.GetNbinsX()+1)
    if cut>0:
        nbinlow = int(hist.FindBin(cut+0.001))
    myerror = ROOT.Double()
    myyield = hist.IntegralAndError(nbinlow,nbinhigh,myerror)
    return myyield, myerror

def getYieldAndErrorNJ(hist,cut):
    nbinlow = int(cut+1) #cut + bin number starts at 1 not 0
    nbinhigh = int(cut+1)
    myerror = ROOT.Double()
    myyield = hist.IntegralAndError(nbinlow,nbinhigh,myerror)
    return myyield, myerror

def getYieldAndErrorOthSig(hist1,hist2,cut):
    yieldvvv,errorvvv = getYieldAndError(hist2,cut)
    yieldwww,errorwww = getYieldAndError(hist1,cut)
    return (yieldvvv-yieldwww),math.sqrt(pow(errorvvv,2)-pow(errorwww,2))
def getYieldAndErrorNJOthSig(hist1,hist2,cut):
    yieldvvv,errorvvv = getYieldAndErrorNJ(hist2,cut)
    yieldwww,errorwww = getYieldAndErrorNJ(hist1,cut)
    return (yieldvvv-yieldwww),math.sqrt(pow(errorvvv,2)-pow(errorwww,2))


def st(myfloat=-.1,prc="%.1f"):
    #print(myfloat,type(myfloat))
    return str(prc % (myfloat))




fP = ROOT.TFile.Open(getpath()+"prompt.root")
fL = ROOT.TFile.Open(getpath()+"lostlep.root")
fF = ROOT.TFile.Open(getpath()+"fakes.root")
fQ = ROOT.TFile.Open(getpath()+"qflip.root")
fG = ROOT.TFile.Open(getpath()+"photon.root")
fWWW = ROOT.TFile.Open(getpath(-1,True)+"www_onshell.root")
fWH  = ROOT.TFile.Open(getpath(-1,True)+"wh_www.root")
fVVV = ROOT.TFile.Open(getpath(-1,True)+"vvv_onshell.root")
fVH  = ROOT.TFile.Open(getpath(-1,True)+"vvv_higgs.root")

histlistSSee2j = ["CutSRDilep__yield","SRSSee__yield","SRSSee__nj30","SRSSee__nb__nj2","SRSSeePreSel__yield","SRSSeeNsoftbVeto__yield","SRSSeeLowDetaMjj__yield","SRSSeeLowDetaMjj__METExtra","SRSSeeKinSel__yield","SRSSeeMjjIn__yield","SRSSeeMjjOut__yield"]
namelistSSee2j = ["2 SS leptons", "\\SSee", "$\\Nj\\geq2$","$\\Nb=0$", "$\\abs{m_{\\Pe\\Pe}-\\MZ}>20\\GeV$", "$\\Nb^{soft}=0$","$\\MjjL > 500\\GeV$, $\\DetaJJ<2.5$", "$\\ptmiss>45\\GeV$", "$\\MTmax>90\\GeV$","\\Mjjin","\\Mjjout"]
cutslistSSee2j = [-1, -1, 2.,0., -1, -1,-1, 45., -1,-1,-1]
histlistSSem2j = ["CutSRDilep__yield","SRSSem__yield","SRSSem__nj30","SRSSemPreSel__yield","SRSSemNsoftbVeto__yield","SRSSemLowDetaMjj__yield","SRSSemLowDetaMjj__METExtra","SRSSemKinSel__yield","SRSSemMjjIn__yield","SRSSemMjjOut__yield"]
namelistSSem2j = ["2 SS leptons", "\\SSem", "$\\Nj\\geq2$","$\\Nb=0$", "$\\Nb^{soft}=0$","$\\MjjL > 500\\GeV$, $\\DetaJJ<2.5$", "$\\ptmiss>45\\GeV$", "$\\MTmax>90\\GeV$","\\Mjjin","\\Mjjout"]
cutslistSSem2j = [-1, -1, 2.,-1, -1,-1, 45., -1,-1,-1]
histlistSSmm2j = ["CutSRDilep__yield","SRSSmm__yield","SRSSmm__nj30","SRSSmmPreSel__yield","SRSSmmNsoftbVeto__yield","SRSSmmLowDetaMjj__yield","SRSSmmLowDetaMjj__METExtra","SRSSmmMjjIn__yield","SRSSmmMjjOut__yield"]
namelistSSmm2j = ["2 SS leptons", "\\SSmm", "$\\Nj\\geq2$","$\\Nb=0$", "$\\Nb^{soft}=0$","$\\MjjL > 500\\GeV$, $\\DetaJJ<2.5$", "$\\ptmiss>45\\GeV$","\\Mjjin","\\Mjjout"]
cutslistSSmm2j = [-1, -1, 2.,-1, -1,-1, 45., -1,-1]

histlistSSee1j = ["CutSRDilep__yield","SRSSee__yield","SRSSee__nj30","SRSSee__nb__nj2","SRSS1Jee1JPre__yield","SRSS1JeeNsoftbVeto__yield","SRSS1JeeNsoftbVeto__METExtra","SRSS1JeeNsoftbVeto__MTmax_afterMET","SRSS1Jee1JKin__yield"]
namelistSSee1j = ["2 SS leptons", "\\SSee", "$\\Nj=1$","$\\Nb=0$", "$\\abs{m_{\\Pe\\Pe}-\\MZ}>20\\GeV$", "$\\Nb^{soft}=0$", "$\\ptmiss>45\\GeV$", "$\\MTmax>90\\GeV$","$\\minDRlj<1.5$"]
cutslistSSee1j = [-1, -1, 1.,0., -1, -1, 45., 90.,-1]
histlistSSem1j = ["CutSRDilep__yield","SRSSem__yield","SRSSem__nj30","SRSS1Jem1JPre__yield","SRSS1JemNsoftbVeto__yield","SRSS1JemNsoftbVeto__METExtra","SRSS1JemNsoftbVeto__MTmax_afterMET","SRSS1Jem1JKin__yield"]
namelistSSem1j = ["2 SS leptons", "\\SSem", "$\\Nj=1$","$\\Nb=0$", "$\\Nb^{soft}=0$", "$\\ptmiss>45\\GeV$", "$\\MTmax>90\\GeV$","$\\minDRlj<1.5$"]
cutslistSSem1j = [-1, -1, 1., -1, -1, 45., 90.,-1]
histlistSSmm1j = ["CutSRDilep__yield","SRSSmm__yield","SRSSmm__nj30","SRSS1Jmm1JPre__yield","SRSS1JmmNsoftbVeto__yield","SRSS1JmmNsoftbVeto__METExtra","SRSS1JmmNsoftbVeto__MTmax_afterMET","SRSS1Jmm1JKin__yield"]
namelistSSmm1j = ["2 SS leptons", "\\SSmm", "$\\Nj=1$","$\\Nb=0$", "$\\Nb^{soft}=0$", "$\\ptmiss>45\\GeV$", "$\\MTmax>90\\GeV$","$\\minDRlj<1.5$"]
cutslistSSmm1j = [-1, -1, 1., -1, -1, 45., 90.,-1]

histlist0SFOS  = ["CutSRTrilep__yield","SR0SFOS__lep_pt2","SR0SFOS__lep_pt2_afterNJ","SR0SFOSPreSel__yield","SR0SFOSDYVeto__yield","SR0SFOSNsoftbVeto__yield"]
namelist0SFOS  = ["3 leptons", "\\1SFOS", "$\\Nj\\leq1$", "$\\Nb=0$", "$\\abs{m_{\\Pe\\Pe}-\\MZ}>20\\GeV$, $\\abs{\\Mlll-\\MZ}>10\\GeV$", "$\\Nb^{soft}=0$"]
cutslist0SFOS  = [-1,25.,25.,-1,-1,-1]

histlist1SFOS  = ["CutSRTrilep__yield","SR1SFOS__yield","SR1SFOS__nj30","SR1SFOSPreSel__yield","SR1SFOSPreSel__nSFOSinZ","SR1SFOSDYVeto__yield","SR1SFOSNsoftbVeto__yield", "SR1SFOSNsoftbVeto__MT3rd","SR1SFOSNsoftbVeto__Pt3l_afterMT3rd", "SR1SFOSKinSel__yield"]
namelist1SFOS  = ["3 leptons", "\\oSFOS", "$\\Nj=0$", "$\\Nb=0$", "$\\abs{\\MSFOS-\\MZ}>20\\GeV$", "$\\abs{\\Mlll-\\MZ}>10\\GeV$", "$\\Nb^{soft}=0$", "$\\MTthird>90\\GeV$", "$\\ptlll>50\\GeV","$\\DPhilllMET>2.5$"]
cutslist1SFOS  = [-1,-1,0.,-1,0.,-1,-1,90.,50.,-1]

histlist2SFOS  = ["CutSRTrilep__yield","SR2SFOS__yield","SR2SFOS__nj30","SR2SFOSPreSel__yield","SR2SFOSPreSel__nSFOSinZ","SR2SFOSDYVeto__yield","SR2SFOSNsoftbVeto__yield", "SR2SFOSNsoftbVeto__MTmax","SR2SFOSNsoftbVeto__Pt3l_afterMTmax", "SR2SFOSKinSel__yield"]
namelist2SFOS  = ["3 leptons", "\\oSFOS", "$\\Nj=0$", "$\\Nb=0$", "$\\abs{\\MSFOS-\\MZ}>20\\GeV$", "$\\abs{\\Mlll-\\MZ}>10\\GeV$", "$\\Nb^{soft}=0$", "$\\MTmax>90\\GeV$", "$\\ptlll>50\\GeV","$\\DPhilllMET>2.5$"]
cutslist2SFOS  = [-1,-1,0.,-1,0.,-1,-1,90.,50.,-1]

allhistlist = histlistSSee2j + histlistSSem2j + histlistSSmm2j + histlistSSee1j + histlistSSem1j + histlistSSmm1j + histlist0SFOS + histlist1SFOS + histlist2SFOS

hists = dict()

loadHistos(hists,fP,allhistlist,"Irr")
loadHistos(hists,fL,allhistlist,"LL")
loadHistos(hists,fF,allhistlist,"Fakes")
loadHistos(hists,fQ,allhistlist,"Qflips")
loadHistos(hists,fG,allhistlist,"Gamma")
loadHistos(hists,fWWW,allhistlist,"WWW")
loadHistos(hists,fWH ,allhistlist,"WH")
loadHistos(hists,fVVV,allhistlist,"VVV")
loadHistos(hists,fVH ,allhistlist,"VH")

CreateCutflowTable(hists,histlistSSee2j, cutslistSSee2j, namelistSSee2j)
CreateCutflowTable(hists,histlistSSem2j, cutslistSSem2j, namelistSSem2j)
CreateCutflowTable(hists,histlistSSmm2j, cutslistSSmm2j, namelistSSmm2j)
CreateCutflowTable(hists,histlistSSee1j, cutslistSSee1j, namelistSSee1j)
CreateCutflowTable(hists,histlistSSem1j, cutslistSSem1j, namelistSSem1j)
CreateCutflowTable(hists,histlistSSmm1j, cutslistSSmm1j, namelistSSmm1j)
CreateCutflowTable(hists,histlist0SFOS,  cutslist0SFOS,  namelist0SFOS )
CreateCutflowTable(hists,histlist1SFOS,  cutslist1SFOS,  namelist1SFOS )
CreateCutflowTable(hists,histlist2SFOS,  cutslist2SFOS,  namelist2SFOS )

