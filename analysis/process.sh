#!/bin/bash

mkdir -p outputs/WWW2017_v5.0.0/test1/

./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg/          -o outputs/WWW2017_v5.0.0/test1/lostlep.root        -T t_lostlep > outputs/WWW2017_v5.0.0/test1/lostlep.log        2>&1 &
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg/          -o outputs/WWW2017_v5.0.0/test1/qflip.root          -T t_qflip   > outputs/WWW2017_v5.0.0/test1/qflip.log          2>&1 &
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg/          -o outputs/WWW2017_v5.0.0/test1/prompt.root         -T t_prompt  > outputs/WWW2017_v5.0.0/test1/prompt.log         2>&1 &
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg/          -o outputs/WWW2017_v5.0.0/test1/fakes.root          -T t_fakes   > outputs/WWW2017_v5.0.0/test1/fakes.log          2>&1 &
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg/          -o outputs/WWW2017_v5.0.0/test1/photon.root         -T t_photon  > outputs/WWW2017_v5.0.0/test1/photon.log         2>&1 &
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/data/         -o outputs/WWW2017_v5.0.0/test1/data.root           -T t_ss      > outputs/WWW2017_v5.0.0/test1/data.log           2>&1 &
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/data/         -o outputs/WWW2017_v5.0.0/test1/ddfakes.root        -T t_ss -F   > outputs/WWW2017_v5.0.0/test1/ddfakes.log        2>&1 & # fake estimation
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/bkg/          -o outputs/WWW2017_v5.0.0/test1/ewksubt.root        -T t_ss -F   > outputs/WWW2017_v5.0.0/test1/ewksubt.log        2>&1 & # ewk subtraction (prompt contamination subtraction)
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/sig/          -o outputs/WWW2017_v5.0.0/test1/signal_private.root -T t_www     > outputs/WWW2017_v5.0.0/test1/signal_private.log 2>&1 & # Private sample generated over winter break by P.Chang
./doAnalysis -i /nfs-7/userdata/phchang/WWW_babies/WWW2017_v5.0.0/grouped/sigofficial/  -o outputs/WWW2017_v5.0.0/test1/signal.root         -T t_www     > outputs/WWW2017_v5.0.0/test1/signal.log         2>&1 & # Official CMS sample

wait
