#!/bin/bash

#
# Script to download the electron ID scale factors presented and approved in the EGamma meeting:
# https://indico.cern.ch/event/879917/
# Watch out, there are two links in the agenda: be sure to took at the updated presentation
# from 19 February 2020
#
# Here the link to the website with all the plots and the histogram ROOT files:
# https://rembserj.web.cern.ch/rembserj/plots/egamma/20200218_electron_scale_factors/Ele_MVA_V2
#
# Author: Jonas Rembser 2020
#

WEBSITE_BASE=https://rembserj.web.cern.ch/rembserj/plots/egamma/20200226_electron_scale_factors/Ele_MVA_V2

# The scale factors are in the EGamma_SF2D histogram directly in the ROOT file
# eta is on X axis, pt is on Y axis

for YEAR in 2016 2017 2018
do
    for FLAG in passingWVZCandidateZID passingWVZCandidateWID passingWWWSameSignID passingWWW3LID passingVVVCommonVetoID
    do
        wget $WEBSITE_BASE/$YEAR/$FLAG/egammaEffi.txt_EGM2D.root -O ${YEAR}_${FLAG}.root
    done
done
