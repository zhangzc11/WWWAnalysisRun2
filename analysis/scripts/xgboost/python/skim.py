#!/usr/bin/env python

from ROOT import TFile, gROOT, gDirectory
import os, sys

gROOT.SetBatch(True)
def GetKeyNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetName() for key in gDirectory.GetListOfKeys()]
def GetClassNames( self, dir = "" ):
        self.cd(dir)
        return [key.GetClassName() for key in gDirectory.GetListOfKeys()]

TFile.GetKeyNames = GetKeyNames
TFile.GetClassNames = GetClassNames

if __name__ == "__main__":
	fileInName = sys.argv[1]
	fileOutName = sys.argv[2]
	cut_skim = sys.argv[3]
	print("input file: "+fileInName)
	print("output file: "+fileOutName)
	print("cut_skim: "+cut_skim)
	fileIn = TFile(fileInName, "READ")
	keyList = fileIn.GetKeyNames()
	classList = fileIn.GetClassNames()
	fileOut = TFile(fileOutName, "RECREATE")
	
	fileOut.cd()
	
	for j in range(0, len(keyList)):
		print(classList[j] + "   ===   " + keyList[j])
		if classList[j] == "TTree":
			fileIn.cd()
			inputTree = fileIn.Get(keyList[j])
			fileOut.cd()
			outputTree = inputTree.CopyTree(cut_skim)
			outputTree.Write()
		if classList[j] == "TH1F":
			fileIn.cd()
			histThis = fileIn.Get(keyList[j])
			fileOut.cd()
			histThis_out = histThis.Clone()
			histThis_out.Write()
