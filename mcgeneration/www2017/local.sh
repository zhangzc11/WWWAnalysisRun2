#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
if [ -r CMSSW_9_3_4/src ] ; then 
 echo release CMSSW_9_3_4 already exists
else
scram p CMSSW CMSSW_9_3_4
fi
cd CMSSW_9_3_4/src
eval `scram runtime -sh`

curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SMP-RunIIFall17wmLHEGS-00059 --retry 2 --create-dirs -o Configuration/GenProduction/python/SMP-RunIIFall17wmLHEGS-00059-fragment.py 
[ -s Configuration/GenProduction/python/SMP-RunIIFall17wmLHEGS-00059-fragment.py ] || exit $?;

scram b
cd ../../
cmsDriver.py Configuration/GenProduction/python/SMP-RunIIFall17wmLHEGS-00059-fragment.py \
    --fileout file:file_GEN-SIM__LHE.root \
    --mc \
    --eventcontent RAWSIM,LHE \
    --datatier GEN-SIM,LHE \
    --conditions 93X_mc2017_realistic_v3 \
    --beamspot Realistic25ns13TeVEarly2017Collision \
    --step LHE,GEN,SIM \
    --geometry DB:Extended \
    --era Run2_2017 \
    --python_filename SMP-RunIIFall17wmLHEGS-00059_1_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 10 || exit $? ;
cmsRun -e -j GEN-SIM,LHE.xml SMP-RunIIFall17wmLHEGS-00059_1_cfg.py
#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
if [ -r CMSSW_9_4_0_patch1/src ] ; then
 echo release CMSSW_9_4_0_patch1 already exists
else
scram p CMSSW CMSSW_9_4_0_patch1
fi
cd CMSSW_9_4_0_patch1/src
eval `scram runtime -sh`


scram b
cd ../../
cmsDriver.py step1 \
    --filein file:file_GEN-SIM__LHE.root \
    --fileout file:file_GEN-SIM-RAW.root \
    --pileup_input "file:/hadoop/cms/store/user/phchang/pileupfiles/F4CEFFB5-FC0E-E811-A015-0025905B857E.root" \
    --mc \
    --eventcontent PREMIXRAW \
    --datatier GEN-SIM-RAW \
    --conditions 94X_mc2017_realistic_v11 \
    --step DIGIPREMIX_S2,DATAMIX,L1,DIGI2RAW,HLT:2e34v40 \
    --nThreads 8 \
    --datamix PreMix \
    --era Run2_2017 \
    --python_filename SMP-RunIIFall17DRPremix-00015_1_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 10 || exit $? ;
cmsRun -e -j GEN-SIM-RAW.xml SMP-RunIIFall17DRPremix-00015_1_cfg.py

cmsDriver.py step2 \
    --filein file:file_GEN-SIM-RAW.root \
    --fileout file:file_AODSIM.root \
    --mc \
    --eventcontent AODSIM \
    --runUnscheduled \
    --datatier AODSIM \
    --conditions 94X_mc2017_realistic_v11 \
    --step RAW2DIGI,RECO,RECOSIM,EI \
    --nThreads 8 \
    --era Run2_2017 \
    --python_filename SMP-RunIIFall17DRPremix-00015_2_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 10 || exit $? ;
cmsRun -e -j AODSIM.xml SMP-RunIIFall17DRPremix-00015_2_cfg.py
#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
if [ -r CMSSW_9_4_6_patch1/src ] ; then
 echo release CMSSW_9_4_6_patch1 already exists
else
scram p CMSSW CMSSW_9_4_6_patch1
fi
cd CMSSW_9_4_6_patch1/src
eval `scram runtime -sh`


scram b
cd ../../
cmsDriver.py step1 \
    --filein file:file_AODSIM.root \
    --fileout file:file_MINIAODSIM.root \
    --mc \
    --eventcontent MINIAODSIM \
    --runUnscheduled \
    --datatier MINIAODSIM \
    --conditions 94X_mc2017_realistic_v14 \
    --step PAT \
    --nThreads 4 \
    --scenario pp \
    --era Run2_2017,run2_miniAOD_94XFall17 \
    --python_filename SMP-RunIIFall17MiniAODv2-00024_1_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 10 || exit $? ;
cmsRun -e -j MINIAODSIM.xml SMP-RunIIFall17MiniAODv2-00024_1_cfg.py
