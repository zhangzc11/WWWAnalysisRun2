#!/bin/bash

if [ -z $1 ]; then
    echo "Usage:"
    echo ""
    echo "  sh $0 YEAR"
    echo ""
    echo ""
    exit
fi

YEAR=$1
INPUT_TAG=FR${YEAR}_v5.1.9
TAG=test_2019_08_21_0742

mkdir -p outputs/${INPUT_TAG}/${TAG}/ss/
mkdir -p outputs/${INPUT_TAG}/${TAG}/3l/

HADOOPDIR=/hadoop/cms/store/user/phchang/metis/franalysis/${TAG}/${INPUT_TAG}_ss_${TAG}/
hadd outputs/${INPUT_TAG}/${TAG}/ss/dy.root      ${HADOOPDIR}/dy_m50_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/data_mu.root ${HADOOPDIR}/data_Run${YEAR}*_mm_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/data_el.root ${HADOOPDIR}/data_Run${YEAR}*_*e*_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/tt_incl.root ${HADOOPDIR}/ttbar_incl_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/tt_1l.root   ${HADOOPDIR}/ttbar_1l*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/wj_incl.root ${HADOOPDIR}/wjets_incl_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/wj_ht.root   ${HADOOPDIR}/wjets_ht*_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/ww.root      ${HADOOPDIR}/ww_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/wz.root      ${HADOOPDIR}/wz_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/qcd_mu.root  ${HADOOPDIR}/qcd_pt*_muenriched_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/qcd_em.root  ${HADOOPDIR}/qcd_pt*_emenriched_*.root
hadd outputs/${INPUT_TAG}/${TAG}/ss/qcd_bc.root  ${HADOOPDIR}/qcd_pt*_bctoe_*.root

HADOOPDIR=/hadoop/cms/store/user/phchang/metis/franalysis/${TAG}/${INPUT_TAG}_3l_${TAG}/
hadd outputs/${INPUT_TAG}/${TAG}/3l/dy.root      ${HADOOPDIR}/dy_m50_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/data_mu.root ${HADOOPDIR}/data_Run${YEAR}*_mm_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/data_el.root ${HADOOPDIR}/data_Run${YEAR}*_*e*_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/tt_incl.root ${HADOOPDIR}/ttbar_incl_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/tt_1l.root   ${HADOOPDIR}/ttbar_1l*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/wj_incl.root ${HADOOPDIR}/wjets_incl_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/wj_ht.root   ${HADOOPDIR}/wjets_ht*_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/ww.root      ${HADOOPDIR}/ww_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/wz.root      ${HADOOPDIR}/wz_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/qcd_mu.root  ${HADOOPDIR}/qcd_pt*_muenriched_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/qcd_em.root  ${HADOOPDIR}/qcd_pt*_emenriched_*.root
hadd outputs/${INPUT_TAG}/${TAG}/3l/qcd_bc.root  ${HADOOPDIR}/qcd_pt*_bctoe_*.root
