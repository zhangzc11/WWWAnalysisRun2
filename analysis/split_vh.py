#!/bin/env python

import ROOT as r
import sys
import os

# root [27] t->Scan("abs(genPart_pdgId[4]):MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))")

def split(dirpath, filename):

    f = r.TFile(os.path.join(dirpath, filename))

    t = f.Get("t")
    h = f.Get("h_neventsinfile")

    # create a suffix based on the input filename
    suffix = filename
    suffix.replace("vh_nonbb", "")

    output_file_path = os.path.join(dirpath, "wh_ww_{}".format(suffix))
    f_www = r.TFile(output_file_path, "recreate")
    t_www = t.CopyTree("abs(genPart_pdgId[4])==24&&MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))==24")
    t_www.Write()
    h.Write()

    output_file_path = os.path.join(dirpath, "zh_ww_{}".format(suffix))
    f_zww = r.TFile(output_file_path, "recreate")
    t_zww = t.CopyTree("abs(genPart_pdgId[4])==23&&MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))==24")
    t_zww.Write()
    h.Write()

    output_file_path = os.path.join(dirpath, "wh_zz_{}".format(suffix))
    f_wzz = r.TFile(output_file_path, "recreate")
    t_wzz = t.CopyTree("abs(genPart_pdgId[4])==24&&MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))==23")
    t_wzz.Write()
    h.Write()

    output_file_path = os.path.join(dirpath, "zh_zz_{}".format(suffix))
    f_zzz = r.TFile(output_file_path, "recreate")
    t_zzz = t.CopyTree("abs(genPart_pdgId[4])==23&&MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))==23")
    t_zzz.Write()
    h.Write()

    output_file_path = os.path.join(dirpath, "zh_zz_{}".format(suffix))
    f_zzz = r.TFile(output_file_path, "recreate")
    t_zzz = t.CopyTree("abs(genPart_pdgId[4])==23&&MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))==23")
    t_zzz.Write()
    h.Write()

    output_file_path = os.path.join(dirpath, "vh_nonbbwwzz_{}".format(suffix))
    f_rest = r.TFile(output_file_path, "recreate")
    t_rest = t.CopyTree("MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))!=23&&MaxIf$(genPart_pdgId,(genPart_motherId==25)*(genPart_status==22||genPart_status==23||genPart_status==2||genPart_status==1))!=24")
    t_rest.Write()
    h.Write()

if __name__ == "__main__":

    split("/nfs-7/userdata/phchang/WWW_babies/Loose2016_v5.3.2/skim/","vh_nonbb_amcnlo_1.root")
    split("/nfs-7/userdata/phchang/WWW_babies/Loose2017_v5.3.2/skim/","vh_nonbb_2l_amcatnlo_1.root")
    split("/nfs-7/userdata/phchang/WWW_babies/Loose2017_v5.3.2/skim/","vh_nonbb_2l_amcatnlo_2.root")
    split("/nfs-7/userdata/phchang/WWW_babies/Loose2017_v5.3.2/skim/","vh_nonbb_amcatnlo_1.root")
    split("/nfs-7/userdata/phchang/WWW_babies/Loose2018_v5.3.2/skim/","vh_nonbb_amcatnlo_1.root")
    split("/nfs-7/userdata/phchang/WWW_babies/Loose2018_v5.3.2/skim/","vh_nonbb_amcatnlo_dilepfilter_1.root")
    split("/nfs-7/userdata/phchang/WWW_babies/Loose2018_v5.3.2/skim/","vh_nonbb_amcatnlo_dilepfilter_2.root")
