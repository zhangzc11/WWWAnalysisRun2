#!/usr/bin/env python
# coding: utf-8
import matplotlib.pyplot as plt
import xgboost as xgb
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, roc_curve, roc_auc_score
import numpy as np
import pandas as pd
import math
import pickle as pickle
import ROOT as root
import os
import shlex
import uproot

root.gROOT.SetBatch(True)
root.gStyle.SetOptStat(0)
root.gStyle.SetOptFit(111)
root.gStyle.SetPaintTextFormat("2.1f")

plt.rcParams["font.family"] = "Arial"
plt.rcParams["axes.unicode_minus"] = False
plt.rcParams["text.usetex"] = False
plt.rcParams["mathtext.fontset"] = "cm"


test_name = 'xgb_www_vs_lostlep_prompt_SFOS'

lumi_sf_sig = 1.0 # scale lumi from 2018 sample to full run2
lumi_sf_bkg = 1.0

plotDir = "/home/users/zhicaiz/public_html/WWW/BDT/"
pwd = os.getcwd()
dataDir = pwd.replace("python", "data/All/")

os.system("mkdir -p "+plotDir)
os.system("mkdir -p "+plotDir+"training")
os.system("mkdir -p "+plotDir+"results")
os.system("mkdir -p "+plotDir+"scores")
os.system("mkdir -p "+plotDir+"variables")

#signal
signalFileName =  dataDir + 'signal_SFOS_cutMll3L.root' 
signalFile = root.TFile(signalFileName)
signalTree = signalFile.Get('t')
signalTree.Draw('met_pt>>tmp1')
signalHisto = root.gDirectory.Get('tmp1')
signalEvents = lumi_sf_sig*signalHisto.Integral()

#bkg
bkgFileName    = dataDir + 'lostlep_prompt_SFOS_cutMll3L.root'
bkgFile = root.TFile(bkgFileName)
bkgTree = bkgFile.Get('t')
bkgTree.Draw('met_pt>>tmp2')
bkgHisto = root.gDirectory.Get('tmp2')
bkgEvents = lumi_sf_bkg*bkgHisto.Integral()


print('[INFO]: S =' + str(signalEvents) + '; B =' + str(bkgEvents) +"; S/sqrt(B) = " + str(signalEvents/math.sqrt(bkgEvents)))

##Define variables to be used
#variables = ['met_pt_corr','lep3Pt','lep4Pt','ZPt','lep3dZ', 'lep4dZ','lep3MT','lep4MT','lep34MT','phi0','theta0','phi','theta1','theta2','MllN', 'pt_zeta', 'pt_zeta_vis', 'M4l', 'Pt4l'] #full

variables =   [	['met_pt', 'met_pt', '$p_{T}^{miss}$ (GeV)', 100, 0, 500],
	     	['lep1Pt', 'lep1Pt', '$p_T^{l1}$ (GeV)', 100, 0, 500],
	     	['lep2Pt', 'lep2Pt', '$p_T^{l2}$ (GeV)', 100, 0, 500],
		['lep3Pt', 'lep3Pt', '$p_T^{l3}$ (GeV)', 100, 0, 500],
	     	['lep1pdgId', 'lep1_pdgId', 'l1 pdg Id', 40, -20, 20],
	     	['lep2pdgId', 'lep2_pdgId', 'l2 pdg Id', 40, -20, 20],
		['lep3pdgId', 'lep3_pdgId', 'l3 pdg Id', 40, -20, 20],
	     	['jet1Pt', 'jet1Pt', '$p_T^{j1}$ (GeV)', 100, 0, 500],
	     	['jet2Pt', 'jet2Pt', '$p_T^{j2}$ (GeV)', 100, 0, 500],
	     	['jet3Pt', 'jet3Pt', '$p_T^{j3}$ (GeV)', 100, 0, 500],
	     	['nj30', 'nj30', '$N_{j}$', 8, -0.5, 7.5],
	     	['nSFOS', 'nSFOS', 'nSFOS', 3, -0.5, 2.5],
#	     	['nb', 'nb', '$N_{b}$', 8, -0.5, 7.5],
		['Mll3L', 'Mll3L', '$m_{ll}^{SF, leading} (GeV)$', 100, 0, 500],
                ['Mll3L1', 'Mll3L1', '$m_{ll}^{SF, sub-leading} (GeV)$', 100, 0, 500],
                ['M3l', 'M3l', '$m_{3l} (GeV)$', 100, 0, 500],
                ['Pt3l', 'Pt3l', '$p_{T}^{3l} (GeV)$', 100, 0, 500],
		['Pt2l', 'Pt2l', '$p_T^{ll}$ (GeV)', 100, 0, 500],
                ['MllSS', 'MllSS', '$m_{ll}^{SS}$ (GeV)', 100, 0, 500],
                ['MTmax3L', 'MTmax3L', '$m_{T}^{max,3L}$ (GeV)', 100, 0, 500],
                ['MTmax', 'MTmax', '$m_{T}^{max}$ (GeV)', 100, 0, 500],
                ['MTmin', 'MTmin', '$m_{T}^{min}$ (GeV)', 100, 0, 500],
                ['DPhi3lMET', 'DPhi3lMET', '$\Delta \phi({p}_T(lll), {p}_{T}^{miss})$', 100, 0, 3.5],
#	     	['DRjj', 'DRjj', '$\Delta R_{jj}$', 100, 0, 6.0],
#	     	['DRjjDR1', 'DRjjDR1', '$\Delta R_{jj}^{DR1}$', 100, 0, 6.0],
#	     	['Mjj', 'Mjj', '$m_{jj}^{min \Delta R}$ (GeV)', 100, 0, 500],
#	     	['MjjL', 'MjjL', '$m_{jj}^{leading}$ (GeV)', 100, 0, 500],
#	     	['MjjDR1', 'MjjDR1', '$m_{jj}^{DR1}$ (GeV)', 100, 0, 500],
#	     	['DetajjL', 'DetajjL', '$\Delta \eta_{jj}^{leading}$ (GeV)', 100, 0, 10.0],
		['event_weight','event_weight', 'event weight', 100, -1.0, 1.0]
	      ] 

print(len(variables))

##Getting ROOT files into pandas
df_signal = uproot.open(signalFileName)['t'].pandas.df([row[0] for row in variables], flatten=False)
df_bkg = uproot.open(bkgFileName)['t'].pandas.df([row[0] for row in variables], flatten=False)

##Getting a numpy array out of two pandas data frame

#getting a numpy array from two pandas data frames
x = np.concatenate([df_bkg.values,df_signal.values])
#creating numpy array for target variables
y = np.concatenate([np.zeros(len(df_bkg)), np.ones(len(df_signal))])

print("signal sample size: "+str(len(df_signal.values)))
print("bkg sample size: "+str(len(df_bkg.values)))
###plot correlation
file_sig = root.TFile(signalFileName)
tree_sig = file_sig.Get("t")
file_bkg = root.TFile(bkgFileName)
tree_bkg = file_sig.Get("t")
h2_corr_sig = root.TH2F("h2_corr_sig", "h2_corr_sig", len(variables)-1, 0, len(variables)-1, len(variables)-1, 0, len(variables)-1)
h2_corr_bkg = root.TH2F("h2_corr_bkg", "h2_corr_bkg", len(variables)-1, 0, len(variables)-1, len(variables)-1, 0, len(variables)-1)

for idx1 in range(len(variables)-1):
        for idx2 in range(len(variables)-1):
                tree_sig.Draw(variables[idx1][0]+":"+variables[idx2][0]+">>temp_sig")
                tree_bkg.Draw(variables[idx1][0]+":"+variables[idx2][0]+">>temp_bkg")
                sig_hist = root.gDirectory.Get('temp_sig')
                h2_corr_sig.SetBinContent(idx1+1, idx2+1, sig_hist.GetCorrelationFactor())
                bkg_hist = root.gDirectory.Get('temp_bkg')
                h2_corr_bkg.SetBinContent(idx1+1, idx2+1, bkg_hist.GetCorrelationFactor())
                root.gDirectory.Delete('temp_sig')
                root.gDirectory.Delete('temp_bkg')
h2_corr_sig.GetZaxis().SetRangeUser(-1.0, 1.0)
h2_corr_bkg.GetZaxis().SetRangeUser(-1.0, 1.0)
for idx in range(len(variables)-1):
        h2_corr_sig.GetXaxis().SetBinLabel(idx+1, variables[idx][1])
        h2_corr_sig.GetYaxis().SetBinLabel(idx+1, variables[idx][1])
        h2_corr_bkg.GetXaxis().SetBinLabel(idx+1, variables[idx][1])
        h2_corr_bkg.GetYaxis().SetBinLabel(idx+1, variables[idx][1])

myC = root.TCanvas( "myC", "myC", 200, 10, 900, 800 )
myC.SetHighLightColor(2)
myC.SetFillColor(0)
myC.SetBorderMode(0)
myC.SetBorderSize(2)
myC.SetLeftMargin( 0.12 )
myC.SetRightMargin( 0.12 )
myC.SetBottomMargin( 0.12 )
myC.SetTopMargin( 0.12 )
myC.SetFrameBorderMode(0)
myC.SetFrameBorderMode(0)

stops = np.array([0.00, 0.34, 0.61, 0.84, 1.00])
red= np.array([0.50, 0.50, 1.00, 1.00, 1.00])
green = np.array([ 0.50, 1.00, 1.00, 0.60, 0.50])
blue = np.array([1.00, 1.00, 0.50, 0.40, 0.50])
root.TColor.CreateGradientColorTable(len(stops), stops, red, green, blue, 255)
root.gStyle.SetNumberContours(255)

h2_corr_sig.Draw("COLZTEXT")
h2_corr_sig.SetTitle("")
myC.SaveAs(plotDir+'variables/'+test_name + '_correlation_matrix_sig.pdf')
myC.SaveAs(plotDir+'variables/'+test_name + '_correlation_matrix_sig.png')
myC.SaveAs(plotDir+'variables/'+test_name + '_correlation_matrix_sig.C')
h2_corr_bkg.Draw("COLZTEXT")
h2_corr_bkg.SetTitle("")
myC.SaveAs(plotDir+'variables/'+test_name + '_correlation_matrix_bkg.pdf')
myC.SaveAs(plotDir+'variables/'+test_name + '_correlation_matrix_bkg.png')
myC.SaveAs(plotDir+'variables/'+test_name + '_correlation_matrix_bkg.C')
os.system("chmod 755 "+plotDir+"variables/*")
####Plot input variables######

for idx in range(len(variables)-1):
        f = plt.figure()
        ax = f.add_subplot(111)
        plt.subplots_adjust(top=0.9, bottom=0.15, left=0.15, right=0.95)
        plt.hist(df_signal[df_signal[variables[idx][0]] > -999][variables[idx][0]], density=True, alpha=1.0, histtype="step", lw=3, label="signal", bins=variables[idx][3], range=(variables[idx][4], variables[idx][5]))
        plt.hist(df_bkg[df_bkg[variables[idx][0]] > -999][variables[idx][0]], density=True, alpha=1.0, histtype="step", lw=3, label="lostlep/prompt", bins=variables[idx][3], range=(variables[idx][4], variables[idx][5]))
        plt.legend(loc="upper right", fontsize = 50)
        plt.xlabel(variables[idx][2], fontsize=50,horizontalalignment='right', x=1.0)
        plt.ylabel('Events', fontsize=30,horizontalalignment='right', y=1.0)
        plt.xticks(fontsize=35)
        plt.yticks(fontsize=30)
        fig = plt.gcf()
        fig.set_size_inches(16, 12)
        plt.text(0.0, 1.01, "CMS", ha='left', va='bottom', transform=ax.transAxes, weight='bold', fontsize=45)
        plt.text(0.12, 1.01, "Simulation Preliminary", ha='left', va='bottom', transform=ax.transAxes, style='italic', fontsize=40)
        plt.text(1.0, 1.01, "13 TeV", ha='right', va='bottom', transform=ax.transAxes, fontsize=40)
        plt.draw()
        plt.savefig(plotDir+'variables/'+test_name + '_' + variables[idx][0]+'.pdf')#, bbox_inches='tight')
        plt.savefig(plotDir+'variables/'+test_name + '_' + variables[idx][0]+'.png')#, bbox_inches='tight')
        plt.savefig(plotDir+'variables/'+test_name + '_' + variables[idx][0]+'.eps')#, bbox_inches='tight')


os.system("chmod 755 "+plotDir+"variables/*")

# split data into train and test sets
seed = 7
test_size = 0.4
sample_size = 1.0
x_train_p, x_test_p, y_train, y_test = train_test_split(x, y, train_size = sample_size*(1-test_size), test_size=sample_size*test_size, random_state=seed)

x_train = x_train_p[:,:-1]
x_test = x_test_p[:,:-1]
sample_weights_train = x_train_p[:,:-1]
sample_weights_test = x_test_p[:,:-1]

# fit model no training data
model = xgb.XGBClassifier(max_depth=3, learning_rate=0.1, n_estimators=400, verbosity=2, n_jobs=4, reg_lambda=1.0)
model.fit(x_train, y_train, sample_weights_train)

#print( dir(model) )
#print(model)
# make predictions for test data
y_pred = model.predict_proba(x_test)[:, 1]
y_pred_train = model.predict_proba(x_train)[:, 1]
predictions = [round(value) for value in y_pred]
# evaluate predictions
accuracy = accuracy_score(y_test, predictions)
print("Accuracy: %.2f%%" % (accuracy * 100.0))

AUC = roc_auc_score(y_test, y_pred)
print("AUC: "+str(AUC))
#get roc curve
#roc = roc_curve(y_test, y_pred)
fpr, tpr, thr = roc_curve(y_test, y_pred)


significance = []
effSignal = []
effBkg = []
thresholds = []

ctr = 0
for i in range(len(fpr)):
    if fpr[i] > 1e-5 and tpr[i] > 1e-5:
        print("thr = "+str(thr[i])+", fpr = "+str(fpr[i]) + ", tpr = "+str(tpr[i]))
        #print fpr[i], tpr[i] 
        #significance.append(math.sqrt(lumi)*4.8742592356*0.006431528796*tpr[i]/math.sqrt(fpr[i]*0.9935684712))
        significance.append(signalEvents*tpr[i]/math.sqrt(fpr[i]*bkgEvents))
        effSignal.append(tpr[i])
        effBkg.append(fpr[i])
        thresholds.append(thr[i])
        #print significance[ctr], ' ' , fpr[ctr], ' ', tpr[ctr]
        ctr = ctr + 1


max_significance = max(significance)
idx_max_significance = np.argmax(np.array(significance))
best_threshold = thresholds[idx_max_significance]
best_effSignal = effSignal[idx_max_significance]
best_effBkg = effBkg[idx_max_significance]

print("max_significance: "+str(max_significance))
print("best_threshold: "+str(best_threshold))
print("best_effSignal: "+str(best_effSignal))
print("best_effBkg: "+str(best_effBkg))

idx_WP90 = 0
minD0p9 = 999.0
for idx in range(len(effSignal)):
	if abs(effSignal[idx] - 0.90) < minD0p9:
		idx_WP90 = idx
		minD0p9 = abs(effSignal[idx] - 0.90)

WP90_significance = significance[idx_WP90]
WP90_threshold = thresholds[idx_WP90]
WP90_effSignal = effSignal[idx_WP90]
WP90_effBkg = effBkg[idx_WP90]

print("WP90_significance: "+str(WP90_significance))
print("WP90_threshold: "+str(WP90_threshold))
print("WP90_effSignal: "+str(WP90_effSignal))
print("WP90_effBkg: "+str(WP90_effBkg))

idx_WP80 = 0
minD0p8 = 999.0
for idx in range(len(effSignal)):
        if abs(effSignal[idx] - 0.80) < minD0p8:
                idx_WP80 = idx
                minD0p8 = abs(effSignal[idx] - 0.80)

WP80_significance = significance[idx_WP80]
WP80_threshold = thresholds[idx_WP80]
WP80_effSignal = effSignal[idx_WP80]
WP80_effBkg = effBkg[idx_WP80]

print("WP80_significance: "+str(WP80_significance))
print("WP80_threshold: "+str(WP80_threshold))
print("WP80_effSignal: "+str(WP80_effSignal))
print("WP80_effBkg: "+str(WP80_effBkg))


##########################################################
# make histogram of discriminator value for signal and bkg
##########################################################
#pd.DataFrame({'truth':y_test, 'disc':y_pred}).hist(column='disc', by='truth', bins=50)
y_frame = pd.DataFrame({'truth':y_test, 'disc':y_pred})
y_frame_train = pd.DataFrame({'truth':y_train, 'disc':y_pred_train})
disc_bkg    = y_frame[y_frame['truth'] == 0]['disc'].values
disc_bkg_train    = y_frame_train[y_frame_train['truth'] == 0]['disc'].values
disc_signal = y_frame[y_frame['truth'] == 1]['disc'].values
disc_signal_train = y_frame_train[y_frame_train['truth'] == 1]['disc'].values
f = plt.figure()
ax = f.add_subplot(111)
plt.subplots_adjust(top=0.9, bottom=0.15, left=0.15, right=0.95)
plt.hist(disc_signal, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="signal - test")
plt.hist(disc_signal_train, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="signal  - train")
plt.hist(disc_bkg, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="lostlep/prompt - test")
plt.hist(disc_bkg_train, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="lostlep/prompt - train")
plt.yscale("log")
plt.xlim([0.0, 1.0])
plt.ylim([0.001, 1000.0])
plt.legend(loc="upper center")
plt.xlabel('BDT response',horizontalalignment='right', x=1.0, fontsize=15)
plt.ylabel('Events',horizontalalignment='right', y=1.0, fontsize=14)
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.axvline(x=WP90_threshold, color="black", linestyle='--')
plt.axvline(x=WP80_threshold, color="black")
plt.text(0.5,0.7,'WP90: disc > %.4f'%WP90_threshold, fontsize=12, horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)
plt.text(0.5,0.6,'WP80: disc > %.4f'%WP80_threshold, fontsize=12, horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)
plt.text(0.0, 1.01, "CMS", ha='left', va='bottom', transform=ax.transAxes, weight='bold', fontsize=17)
plt.text(0.12, 1.01, "Simulation Preliminary", ha='left', va='bottom', transform=ax.transAxes, style='italic', fontsize=16)
plt.text(1.0, 1.01, "13 TeV", ha='right', va='bottom', transform=ax.transAxes, fontsize=16)
plt.savefig(plotDir+'training/mydiscriminator_' + test_name +'_logY.pdf')
plt.savefig(plotDir+'training/mydiscriminator_' + test_name +'_logY.png')
plt.savefig(plotDir+'training/mydiscriminator_' + test_name +'_logY.eps')


f = plt.figure()
ax = f.add_subplot(111)
plt.subplots_adjust(top=0.9, bottom=0.15, left=0.15, right=0.95)
plt.hist(disc_signal, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="signal - test")
plt.hist(disc_signal_train, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="signal  - train")
plt.hist(disc_bkg, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="lostlep/prompt - test")
plt.hist(disc_bkg_train, density=True, bins=100, alpha=1.0, histtype="step", lw=2, label="lostlep/prompt - train")
plt.yscale("linear")
plt.xlim([0.0, 1.0])
#plt.ylim([0.001, 100.0])
plt.legend(loc="upper center")
plt.xlabel('BDT response',horizontalalignment='right', x=1.0, fontsize=15)
plt.ylabel('Events',horizontalalignment='right', y=1.0, fontsize=14)
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.axvline(x=WP90_threshold, color="black", linestyle='--')
plt.axvline(x=WP80_threshold, color="black")
plt.text(0.5,0.7,'WP90: disc > %.4f'%WP90_threshold, fontsize=12, horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)
plt.text(0.5,0.6,'WP80: disc > %.4f'%WP80_threshold, fontsize=12, horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)
plt.text(0.0, 1.01, "CMS", ha='left', va='bottom', transform=ax.transAxes, weight='bold', fontsize=17)
plt.text(0.12, 1.01, "Simulation Preliminary", ha='left', va='bottom', transform=ax.transAxes, style='italic', fontsize=16)
plt.text(1.0, 1.01, "13 TeV", ha='right', va='bottom', transform=ax.transAxes, fontsize=16)
plt.savefig(plotDir+'training/mydiscriminator_' + test_name +'_linY.pdf')
plt.savefig(plotDir+'training/mydiscriminator_' + test_name +'_linY.png')
plt.savefig(plotDir+'training/mydiscriminator_' + test_name +'_linY.eps')


os.system("chmod 755 "+plotDir+"training/*")


#plot roc curve
f = plt.figure()
ax = f.add_subplot(111)
plt.subplots_adjust(top=0.9, bottom=0.15, left=0.15, right=0.95)
lw = 2
plt.plot(fpr, tpr, color='darkorange',
         lw=lw, label='ROC curve')
plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.ylabel('Signal Efficiency',horizontalalignment='right', y=1.0, fontsize=15)
plt.xlabel('Background Efficiency',horizontalalignment='right', x=1.0, fontsize=15)
plt.xticks(fontsize=13)
plt.yticks(fontsize=13)
plt.axhline(y=0.9, color="black", linestyle='--')
plt.axhline(y=0.8, color="black")
plt.text(0.5,0.1,'WP80: bkg eff = %.4f'%WP80_effBkg, fontsize=12)
plt.text(0.5,0.2,'WP90: bkg eff = %.4f'%WP90_effBkg, fontsize=12)
#plt.text(0.5,0.3,'WP90: S/sqrt(B) = %.2f'%WP90_significance, fontsize=12)
plt.text(0.5,0.3,'AUC = %.4f'%AUC, fontsize=12)
#plt.title('Receiver operating characteristic example')
#plt.legend(loc="lower right")
#plt.show()
plt.text(0.0, 1.01, "CMS", ha='left', va='bottom', transform=ax.transAxes, weight='bold', fontsize=17)
plt.text(0.12, 1.01, "Simulation Preliminary", ha='left', va='bottom', transform=ax.transAxes, style='italic', fontsize=16)
plt.text(1.0, 1.01, "13 TeV", ha='right', va='bottom', transform=ax.transAxes, fontsize=16)
plt.savefig(plotDir+'training/myroc_' + test_name + '.pdf')
plt.savefig(plotDir+'training/myroc_' + test_name + '.png')
plt.savefig(plotDir+'training/myroc_' + test_name + '.eps')
os.system("chmod 755 "+plotDir+"training/*")

# Pickle dictionary using protocol 0.
output = open('../models/model_'+test_name+'.pkl', 'wb')
pickle.dump(model, output)
output.close()
model.get_booster().dump_model('../models/model_'+test_name+'.txt')
model.get_booster().save_model('../models/model_'+test_name+'.xgb')

#plot feature importances

model.get_booster().feature_names = [row[1] for row in variables[:-1]]

xgb.plot_importance(model, max_num_features=len(variables)-1, xlabel="F score (weight)")
plt.savefig(plotDir+'training/myImportances_Fscore_' + test_name + '.pdf', bbox_inches='tight')
plt.savefig(plotDir+'training/myImportances_Fscore_' + test_name + '.png', bbox_inches='tight')
plt.savefig(plotDir+'training/myImportances_Fscore_' + test_name + '.eps', bbox_inches='tight')
os.system("chmod 755 "+plotDir+"training/*")

#xgb.plot_tree( model.get_booster() )
xgb.plot_tree( model )
fig = plt.gcf()
#fig.set_size_inches(500, 50)
plt.draw()
plt.savefig(plotDir+'training/myTree_' + test_name + '.pdf')
plt.savefig(plotDir+'training/myTree_' + test_name + '.png')
plt.savefig(plotDir+'training/myTree_' + test_name + '.eps')
os.system("chmod 755 "+plotDir+"training/*")
