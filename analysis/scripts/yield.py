
import numpy as np
import math
import ROOT as r
from colors import *
import shlex

leftMargin   = 0.12
rightMargin  = 0.05
topMargin    = 0.07
bottomMargin = 0.12
r.gStyle.SetOptStat(0)
r.gStyle.SetOptFit(111)

signalcolors = [632, 600, 418, 800, 1]
####WWW part#####
#12 channels
nCh_23L = 12
nS_23L = 5
nB_23L = 5
sigs_23L = np.zeros((nCh_23L, nS_23L+1))
esigs_23L = np.zeros((nCh_23L, nS_23L+1))
sigs_names_23L = ["WWW", "WWZ", "WZZ", "ZZZ", "VH", "S"]
bkgs_23L = np.zeros((nCh_23L, nB_23L+1))
ebkgs_23L = np.zeros((nCh_23L, nB_23L+1))
bkgs_names = ["#gamma#rightarrow l", "Charge mis-id", "Non-prompt (MC)", "Lost/three lep", "Irredu.", "B"]
L_23L = [] #L=s/sqrt(B)

idx_channel = 0
with open("www.txt", "r") as yield_file:
	for this_line in yield_file:
		line_array = shlex.split(this_line)
		if len(line_array) == 1 or line_array[1] == "Bin#":
			continue
		sigs_23L[idx_channel][nS_23L] = float(line_array[nB_23L*4+3])				
		esigs_23L[idx_channel][nS_23L] = float(line_array[nB_23L*4+5])				
		for ib in range(0,nB_23L):
			bkgs_23L[idx_channel][ib] = float(line_array[ib*4+3])
			ebkgs_23L[idx_channel][ib] = float(line_array[ib*4+5])
		idx_channel = idx_channel+1

#read sig channels
idx_channel = 0
with open("wwwvh.txt", "r") as yield_file:
	for this_line in yield_file:
		line_array = shlex.split(this_line)
		if len(line_array) == 1 or line_array[1] == "Bin#":
			continue
		sigs_23L[idx_channel][0] = float(line_array[0*4+3])				
		esigs_23L[idx_channel][0] = float(line_array[0*4+5])				
		sigs_23L[idx_channel][4] = float(line_array[1*4+3])				
		esigs_23L[idx_channel][4] = float(line_array[1*4+5])				
		sigs_23L[idx_channel][1] = float(line_array[2*4+3])				
		esigs_23L[idx_channel][1] = float(line_array[2*4+5])				
		sigs_23L[idx_channel][2] = float(line_array[3*4+3])				
		esigs_23L[idx_channel][2] = float(line_array[3*4+5])				
		sigs_23L[idx_channel][3] = float(line_array[4*4+3])				
		esigs_23L[idx_channel][3] = float(line_array[4*4+5])				

		idx_channel = idx_channel+1


#add up bkgs
for ich in range(0, nCh_23L):
	b = 0.0
	eb2 = 0.0
	for idx in range(0, nB_23L):
		b = b + bkgs_23L[ich][idx]
		eb2 = eb2 + ebkgs_23L[ich][idx] * ebkgs_23L[ich][idx]
	bkgs_23L[ich][nB_23L] = b
	ebkgs_23L[ich][nB_23L] = math.sqrt(eb2)

#print(sigs_23L)
#print(esigs_23L)
#print(bkgs_23L)
#print(ebkgs_23L)

###plot####

myC = r.TCanvas("myC","myC", 1000, 600)

pad1 = r.TPad("pad1","pad1", 0.05, 0.3,0.95, 0.97)
pad1.SetBottomMargin(0)
pad1.SetRightMargin( rightMargin )
pad1.SetLeftMargin( leftMargin )
pad1.Draw()

pad2 = r.TPad("pad2","pad2", 0.05, 0.02, 0.95, 0.29)
pad2.SetTopMargin(0.04)
pad2.SetTopMargin(0.008)
pad2.SetBottomMargin(0.4)
pad2.SetRightMargin( rightMargin )
pad2.SetLeftMargin( leftMargin )
#pad2.SetGridy()
pad2.Draw()

pad1.cd()

stack_b_23L = r.THStack("s_b_23L","s_b_23L")
histcolors_23L = [920, 2007, 2005, 2003, 2001, 2011]
for ib in range(0, nB_23L):
	h1_b = r.TH1F("h1_23L_b"+str(ib), "h1_23L_b"+str(ib), nCh_23L, 0, nCh_23L)
	for idx in range(1,nCh_23L+1):
		h1_b.SetBinContent(idx, bkgs_23L[idx-1][ib])
		h1_b.SetBinError(idx, ebkgs_23L[idx-1][ib])
	h1_b.SetLineColor(histcolors_23L[ib])
	h1_b.SetFillColorAlpha(histcolors_23L[ib], 1)
	h1_b.SetLineWidth(1)
	h1_b.SetMarkerColor(histcolors_23L[ib])
	h1_b.SetMarkerSize(0)
	stack_b_23L.Add(h1_b)
stack_b_23L.SetMaximum(200.0)

stack_b_23L.SetTitle("")
stack_b_23L.Draw("hist")
stack_b_23L.GetXaxis().SetLimits(0,21)
stack_b_23L.GetYaxis().SetTitleOffset(0.52)
stack_b_23L.GetYaxis().SetTitleSize(0.08)
stack_b_23L.GetYaxis().SetLabelSize(0.05)
stack_b_23L.GetYaxis().SetTitle("Events")

hists_sig_23L = []
for isig in range(0, nS_23L):
	h1_s = r.TH1F("h1_23L_s"+str(isig), "h1_23L_s"+str(isig), nCh_23L, 0, nCh_23L)
	for idx in range(1,nCh_23L+1):
		h1_s.SetBinContent(idx, 10*sigs_23L[idx-1][isig])
		h1_s.SetBinError(idx, 10*esigs_23L[idx-1][isig])
	h1_s.SetLineColor(signalcolors[isig])
	h1_s.SetLineWidth(2)
	h1_s.SetMarkerColor(signalcolors[isig])
	hists_sig_23L.append(h1_s)
for isig in range(0, nS_23L):
	hists_sig_23L[isig].Draw("samehist")

legend_23L = r.TLegend(0.2,0.6,0.55,0.9)
legend_23L.SetFillStyle(0)
legend_23L.SetBorderSize(0)
legend_23L.SetTextFont(42)
legend_23L.SetNColumns(3)
for ib in range(0, nB_23L):
	legend_23L.AddEntry("h1_23L_b"+str(ib), bkgs_names[ib], "F")
for isig in range(0, nS_23L):
	legend_23L.AddEntry("h1_23L_s"+str(isig), sigs_names_23L[isig]+" x 10", "L")

legend_23L.Draw()

pad2.cd()
ratio_23L = r.TH1F("h_ratio_23L","h_ratio_23L", 21, 0, 21)
for idx in range(1,nCh_23L+1):
	s = sigs_23L[idx-1][nS_23L]
	b = bkgs_23L[idx-1][nB_23L]
	L = math.sqrt(2.0*((s+b)*math.log(1+s/b) - s))
	ratio_23L.SetBinContent(idx, L)
ratio_23L.SetLineColor(r.kBlack)
ratio_23L.SetLineWidth(1)
ratio_23L.SetTitle("")
ratio_23L.GetYaxis().SetTitle("L (#sigma)")
ratio_23L.GetXaxis().SetTitle("Bin #")
ratio_23L.GetYaxis().SetRangeUser(0.0,4.0)
ratio_23L.GetXaxis().SetTitleOffset(0.94)
ratio_23L.GetXaxis().SetTitleSize(0.18)
ratio_23L.GetXaxis().SetLabelSize(0.12)
ratio_23L.GetYaxis().SetTitleOffset(0.22)
ratio_23L.GetYaxis().SetTitleSize(0.17)
ratio_23L.GetYaxis().SetLabelSize(0.11)
ratio_23L.Draw("hist")


######WWZ part
#7 channels
nCh_4L = 7
nS_4L = 5
nB_4L = 6
sigs_4L = np.zeros((nCh_4L, nS_4L+1))
esigs_4L = np.zeros((nCh_4L, nS_4L+1))
sigs_names_4L = ["WWW", "WWZ", "WZZ", "ZZZ", "VH", "S"]
bkgs_4L = np.zeros((nCh_4L, nB_4L+1))
ebkgs_4L = np.zeros((nCh_4L, nB_4L+1))
bkgs_names = ["ZZ", "t#bar{t}Z", "tWZ", "WZ", "Higgs", "Other", "B"]
L_4L = [] #L=s/sqrt(B)

idx_channel = 0
with open("wwz.txt", "r") as yield_file:
	for this_line in yield_file:
		line_array = shlex.split(this_line)
		if len(line_array) == 1 or line_array[1] == "Bin#":
			continue
		sigs_4L[idx_channel][1] = float(line_array[6*4+3])				
		esigs_4L[idx_channel][1] = float(line_array[6*4+5])				
		sigs_4L[idx_channel][2] = float(line_array[7*4+3])				
		esigs_4L[idx_channel][2] = float(line_array[7*4+5])				
		sigs_4L[idx_channel][3] = float(line_array[8*4+3])				
		esigs_4L[idx_channel][3] = float(line_array[8*4+5])				
		sigs_4L[idx_channel][4] = float(line_array[9*4+3])				
		esigs_4L[idx_channel][4] = float(line_array[9*4+5])				
		for ib in range(0,nB_4L):
			bkgs_4L[idx_channel][ib] = float(line_array[ib*4+3])
			ebkgs_4L[idx_channel][ib] = float(line_array[ib*4+5])
		idx_channel = idx_channel+1

#add up bkgs/sigs
for ich in range(0, nCh_4L):
	b = 0.0
	eb2 = 0.0
	for idx in range(0, nB_4L):
		b = b + bkgs_4L[ich][idx]
		eb2 = eb2 + ebkgs_4L[ich][idx] * ebkgs_4L[ich][idx]
	bkgs_4L[ich][nB_4L] = b
	ebkgs_4L[ich][nB_4L] = math.sqrt(eb2)
	
	s = 0.0
	es2 = 0.0
	for idx in range(0, nS_4L):
		s = s + sigs_4L[ich][idx]
		es2 = es2 + esigs_4L[ich][idx] * esigs_4L[ich][idx]
	sigs_4L[ich][nS_4L] = s
	esigs_4L[ich][nS_4L] = math.sqrt(es2)

#print(sigs_4L)
#print(sigs_4L)
#print(esigs_4L)
#print(bkgs_4L)
#print(ebkgs_4L)

###plot####

pad1.cd()
stack_b_4L = r.THStack("s_b_4L","s_b_4L")
histcolors_4L = [2001, 2005, 2007, 2003, 2011, 920, 2012, 2011, 2002]
hists_b_4L = []
for ib in range(0, nB_4L):
	h1_b = r.TH1F("h1_4L_b"+str(ib), "h1_4L_b"+str(ib), nCh_4L, nCh_23L, nCh_23L+nCh_4L)
	for idx in range(1,nCh_4L+1):
		h1_b.SetBinContent(idx, 10*bkgs_4L[idx-1][ib])
		h1_b.SetBinError(idx, 10*ebkgs_4L[idx-1][ib])
	h1_b.SetLineColor(histcolors_4L[ib])
	h1_b.SetFillColorAlpha(histcolors_4L[ib], 1)
	h1_b.SetLineWidth(1)
	h1_b.SetMarkerColor(histcolors_4L[ib])
	h1_b.SetMarkerSize(0)
	hists_b_4L.append(h1_b)

#bkgs_names = ["ZZ", "t#bar{t}Z", "tWZ", "WZ", "Higgs", "Other", "B"]
stack_b_4L.Add(hists_b_4L[3])
stack_b_4L.Add(hists_b_4L[2])
stack_b_4L.Add(hists_b_4L[5])
stack_b_4L.Add(hists_b_4L[4])
stack_b_4L.Add(hists_b_4L[1])
stack_b_4L.Add(hists_b_4L[0])
stack_b_4L.SetMaximum(200.0)

stack_b_4L.SetTitle("")
stack_b_4L.Draw("histsame")
stack_b_4L.GetYaxis().SetTitleOffset(0.52)
stack_b_4L.GetYaxis().SetTitleSize(0.08)
stack_b_4L.GetYaxis().SetLabelSize(0.05)
stack_b_4L.GetYaxis().SetTitle("Events")

hists_sig_4L = []
for isig in range(0, nS_4L):
	h1_s = r.TH1F("h1_4L_s"+str(isig), "h1_4L_s"+str(isig), nCh_4L, nCh_23L, nCh_23L+nCh_4L)
	for idx in range(1,nCh_4L+1):
		h1_s.SetBinContent(idx, 10*sigs_4L[idx-1][isig])
		h1_s.SetBinError(idx, 10*esigs_4L[idx-1][isig])
	h1_s.SetLineColor(signalcolors[isig])
	h1_s.SetLineWidth(2)
	h1_s.SetMarkerColor(signalcolors[isig])
	hists_sig_4L.append(h1_s)
for isig in range(0, nS_4L):
	hists_sig_4L[isig].Draw("samehist")

legend_4L = r.TLegend(0.60,0.4,0.85,0.9)
legend_4L.SetFillStyle(0)
legend_4L.SetBorderSize(0)
legend_4L.SetTextFont(42)
legend_4L.SetNColumns(2)
for ib in range(0, nB_4L):
	legend_4L.AddEntry("h1_4L_b"+str(ib), bkgs_names[ib]+" x 10", "F")
for isig in range(0, nS_4L):
	legend_4L.AddEntry("h1_4L_s"+str(isig), sigs_names_4L[isig]+" x 10", "L")

legend_4L.Draw()

pad2.cd()
ratio_4L = r.TH1F("h_ratio_4L","h_ratio_4L", 21, 0, 21)
for idx in range(1,nCh_4L+1):
	s = sigs_4L[idx-1][nS_4L]
	b = bkgs_4L[idx-1][nB_4L]
	L = math.sqrt(2.0*((s+b)*math.log(1+s/b) - s))
	ratio_4L.SetBinContent(idx+nCh_23L, L)
ratio_4L.SetLineColor(r.kBlack)
ratio_4L.SetLineWidth(1)
ratio_4L.Draw("histsame")


####5/6L part
#2 channels
nCh_56L = 2
nS_56L = 5
nB_56L = 2
sigs_56L = np.zeros((nCh_56L, nS_56L+1))
esigs_56L = np.zeros((nCh_56L, nS_56L+1))
sigs_names_56L = ["WWW", "WWZ", "WZZ", "ZZZ", "VH", "S"]
bkgs_56L = np.zeros((nCh_56L, nB_56L+1))
ebkgs_56L = np.zeros((nCh_56L, nB_56L+1))
bkgs_names = ["ZZ","Other", "B"]
L_56L = [] #L=s/sqrt(B)

idx_channel = 0
with open("56L.txt", "r") as yield_file:
	for this_line in yield_file:
		line_array = shlex.split(this_line)
		if len(line_array) == 1 or line_array[1] == "Bin#":
			continue
		sigs_56L[idx_channel][2] = float(line_array[2*4+3])				
		esigs_56L[idx_channel][2] = float(line_array[2*4+5])				
		sigs_56L[idx_channel][3] = float(line_array[3*4+3])				
		esigs_56L[idx_channel][3] = float(line_array[3*4+5])				
		sigs_56L[idx_channel][4] = float(line_array[4*4+3])				
		esigs_56L[idx_channel][4] = float(line_array[4*4+5])				
		bkgs_56L[idx_channel][0] = float(line_array[0*4+3])
		ebkgs_56L[idx_channel][0] = float(line_array[0*4+5])
		bkgs_56L[idx_channel][1] = float(line_array[1*4+3])
		ebkgs_56L[idx_channel][1] = float(line_array[1*4+5])
		idx_channel = idx_channel+1

#add up bkgs/sigs
for ich in range(0, nCh_56L):
	b = 0.0
	eb2 = 0.0
	for idx in range(0, nB_56L):
		b = b + bkgs_56L[ich][idx]
		eb2 = eb2 + ebkgs_56L[ich][idx] * ebkgs_56L[ich][idx]
	bkgs_56L[ich][nB_56L] = b
	ebkgs_56L[ich][nB_56L] = math.sqrt(eb2)
	
	s = 0.0
	es2 = 0.0
	for idx in range(0, nS_56L):
		s = s + sigs_56L[ich][idx]
		es2 = es2 + esigs_56L[ich][idx] * esigs_56L[ich][idx]
	sigs_56L[ich][nS_56L] = s
	esigs_56L[ich][nS_56L] = math.sqrt(es2)

#print(sigs_56L)
#print(sigs_56L)
#print(esigs_56L)
#print(bkgs_56L)
#print(ebkgs_56L)

###plot####

pad1.cd()
stack_b_56L = r.THStack("s_b_56L","s_b_56L")
histcolors_56L = [2001, 920, 2005, 2007, 2003, 2011, 920, 2012, 2011, 2002]
hists_b_56L = []
for ib in range(0, nB_56L):
	h1_b = r.TH1F("h1_56L_b"+str(ib), "h1_56L_b"+str(ib), nCh_56L, nCh_23L+nCh_4L, nCh_23L+nCh_4L+nCh_56L)
	for idx in range(1,nCh_56L+1):
		h1_b.SetBinContent(idx, 50*bkgs_56L[idx-1][ib])
		h1_b.SetBinError(idx, 50*ebkgs_56L[idx-1][ib])
	h1_b.SetLineColor(histcolors_56L[ib])
	h1_b.SetFillColorAlpha(histcolors_56L[ib], 1)
	h1_b.SetLineWidth(1)
	h1_b.SetMarkerColor(histcolors_56L[ib])
	h1_b.SetMarkerSize(0)
	hists_b_56L.append(h1_b)
stack_b_56L.Add(hists_b_56L[1])
stack_b_56L.Add(hists_b_56L[0])
stack_b_56L.SetMaximum(200.0)

stack_b_56L.SetTitle("")
stack_b_56L.Draw("histsame")
stack_b_56L.GetYaxis().SetTitleOffset(0.52)
stack_b_56L.GetYaxis().SetTitleSize(0.08)
stack_b_56L.GetYaxis().SetLabelSize(0.05)
stack_b_56L.GetYaxis().SetTitle("Events")

hists_sig_56L = []
for isig in range(0, nS_56L):
	h1_s = r.TH1F("h1_56L_s"+str(isig), "h1_56L_s"+str(isig), nCh_56L, nCh_23L+nCh_4L, nCh_23L+nCh_4L+nCh_56L)
	for idx in range(1,nCh_56L+1):
		h1_s.SetBinContent(idx, 50*sigs_56L[idx-1][isig])
		h1_s.SetBinError(idx, 50*esigs_56L[idx-1][isig])
	h1_s.SetLineColor(signalcolors[isig])
	h1_s.SetLineWidth(2)
	h1_s.SetMarkerColor(signalcolors[isig])
	hists_sig_56L.append(h1_s)
for isig in range(0, nS_56L):
	hists_sig_56L[isig].Draw("samehist")

legend_56L = r.TLegend(0.875,0.3,0.966,0.9)
legend_56L.SetFillStyle(0)
legend_56L.SetBorderSize(0)
legend_56L.SetTextFont(42)
legend_56L.SetNColumns(1)
for ib in range(0, nB_56L):
	legend_56L.AddEntry("h1_56L_b"+str(ib), bkgs_names[ib] + " x 50", "F")
for isig in range(0, nS_56L):
	legend_56L.AddEntry("h1_56L_s"+str(isig), sigs_names_56L[isig]+" x 50", "L")

legend_56L.Draw()

pad2.cd()
ratio_56L = r.TH1F("h_ratio_56L","h_ratio_56L", 21, 0, 21)
for idx in range(1,nCh_56L+1):
	s = sigs_56L[idx-1][nS_56L]
	b = bkgs_56L[idx-1][nB_56L]
	L = math.sqrt(2.0*((s+b)*math.log(1+s/b) - s))
	ratio_56L.SetBinContent(idx+nCh_23L+nCh_4L, L)
ratio_56L.SetLineColor(r.kBlack)
ratio_56L.SetLineWidth(1)
ratio_56L.Draw("histsame")

###draw vertical lines between SS/3L, 4L, 5/6L
pad1.cd()
line1 = r.TLine(12,0,12,210)
line1.SetLineStyle(7)
line1.Draw("same")
line2 = r.TLine(19,0,19,210)
line2.SetLineStyle(7)
line2.Draw("same")

pad2.cd()
line3 = r.TLine(12,-2,12,5)
line3.SetLineStyle(7)
line3.Draw("same")
line4 = r.TLine(19,-2,19,5)
line4.SetLineStyle(7)
line4.Draw("same")
##draw CMS preliminary
pad1.cd()
tex1 = r.TLatex(0.12, 0.91, "CMS")
tex1.SetNDC()
tex1.SetTextFont(61)
tex1.SetTextSize(0.070)
tex1.SetLineWidth(2)
tex1.Draw()
tex2 = r.TLatex(0.19,0.912,"Preliminary")
tex2.SetNDC()
tex2.SetTextFont(52)
tex2.SetTextSize(0.055)
tex2.SetLineWidth(2)
tex2.Draw()

tex3 = r.TLatex(0.77,0.912,"136.9 fb^{-1} (13 TeV)")
tex3.SetNDC()
tex3.SetTextFont(42)
tex3.SetTextSize(0.055)
tex3.SetLineWidth(2)
tex3.Draw()


myC.SaveAs("yield.png")
myC.SaveAs("yield.pdf")
myC.SaveAs("yield.C")
