#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
if [ -r CMSSW_9_3_6_patch1/src ] ; then 
 echo release CMSSW_9_3_6_patch1 already exists
else
scram p CMSSW CMSSW_9_3_6_patch1
fi
cd CMSSW_9_3_6_patch1/src
eval `scram runtime -sh`

#curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIIFall17wmLHEGS-00008 --retry 2 --create-dirs -o Configuration/GenProduction/python/SUS-RunIIFall17wmLHEGS-00008-fragment.py 
#[ -s Configuration/GenProduction/python/SUS-RunIIFall17wmLHEGS-00008-fragment.py ] || exit $?;

cat << EOF > vhww_fragment.py
import FWCore.ParameterSet.Config as cms

# link to cards:
# https://github.com/cms-sw/genproductions/tree/d46da5ba339adab8f4c923c792a5e4aa79826860/bin/MadGraph5_aMCatNLO/cards/production/13TeV/higgs/vh012j_5f_NLO_FXFX_M125_VToAll #TO BE UPDATED

externalLHEProducer = cms.EDProducer("ExternalLHEProducer",
    #args = cms.vstring('/afs/cern.ch/user/w/wverbeke/workspace/genproductions/bin/MadGraph5_aMCatNLO/vh012j_5f_NLO_FXFX_M125_VToAll_slc6_amd64_gcc481_CMSSW_7_1_30_tarball.tar.xz'),
    args = cms.vstring('/cvmfs/cms.cern.ch/phys_generator/gridpacks/2017/13TeV/madgraph/V5_2.4.2/vh012j_5f_NLO_FXFX_M125_VToAll/v2/vh012j_5f_NLO_FXFX_M125_VToAll_slc6_amd64_gcc481_CMSSW_7_1_30_tarball.tar.xz'),
    nEvents = cms.untracked.uint32(5000),
    numberOfParameters = cms.uint32(1),
    outputFile = cms.string('cmsgrid_final.lhe'),
    scriptName = cms.FileInPath('GeneratorInterface/LHEInterface/data/run_generic_tarball_cvmfs.sh')
)


from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.MCTunes2017.PythiaCP5Settings_cfi import *
from Configuration.Generator.Pythia8aMCatNLOSettings_cfi import *
generator = cms.EDFilter("Pythia8HadronizerFilter",
maxEventsToPrint = cms.untracked.int32(1),
pythiaPylistVerbosity = cms.untracked.int32(1),
filterEfficiency = cms.untracked.double(1.0),
pythiaHepMCVerbosity = cms.untracked.bool(False),
comEnergy = cms.double(13000.),
PythiaParameters = cms.PSet(
pythia8CommonSettingsBlock,
pythia8CP5SettingsBlock ,
pythia8aMCatNLOSettingsBlock,
  processParameters = cms.vstring(
  'JetMatching:setMad = off',
  'JetMatching:scheme = 1',
  'JetMatching:merge = on',
  'JetMatching:jetAlgorithm = 2',
  'JetMatching:etaJetMax = 999.',
  'JetMatching:coneRadius = 1.',
  'JetMatching:slowJetPower = 1',
  'JetMatching:qCut = 18.', #this is the actual merging scale
  'JetMatching:doFxFx = on',
  'JetMatching:qCutME = 10.',#this must match the ptj cut in the lhe generation step
  'JetMatching:nQmatch = 5', #4 corresponds to 4-flavour scheme (no matching of b-quarks), 5 for 5-flavour scheme
  'JetMatching:nJetMax = 2', #number of partons in born matrix element for highest multiplicity
  'SLHA:useDecayTable = off',  # Use pythia8s own decay mode instead of decays defined in LH accord
  '25:m0 = 125.0',
  '25:onMode = off', 	# Allow all higgs decays 
  '25:onIfAny = 24',    # Switch decays of b quarks off
  ),
parameterSets = cms.vstring('pythia8CommonSettings',
'pythia8CP5Settings',
'pythia8aMCatNLOSettings',
'processParameters',
)
)
)

EOF

mkdir -p Configuration/GenProduction/python/
cp vhww_fragment.py Configuration/GenProduction/python/

scram b
cd ../../
#cmsDriver.py Configuration/GenProduction/python/SUS-RunIIFall17wmLHEGS-00008-fragment.py \
cmsDriver.py Configuration/GenProduction/python/vhww_fragment.py \
    --fileout file:file_GEN-SIM__LHE.root \
    --mc \
    --eventcontent RAWSIM,LHE \
    --datatier GEN-SIM,LHE \
    --conditions 93X_mc2017_realistic_v3 \
    --beamspot Realistic25ns13TeVEarly2017Collision \
    --step LHE,GEN,SIM \
    --nThreads 8 \
    --geometry DB:Extended \
    --era Run2_2017 \
    --python_filename SUS-RunIIFall17wmLHEGS-00008_1_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 100 || exit $? ;
cmsRun -e -j GEN-SIM,LHE.xml SUS-RunIIFall17wmLHEGS-00008_1_cfg.py

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
    --python_filename SUS-RunIIFall17DRPremix-00074_1_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 100 || exit $? ;
cmsRun -e -j GEN-SIM-RAW.xml SUS-RunIIFall17DRPremix-00074_1_cfg.py

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
    --python_filename SUS-RunIIFall17DRPremix-00074_2_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 100 || exit $? ;
cmsRun -e -j AODSIM.xml SUS-RunIIFall17DRPremix-00074_2_cfg.py

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
    --python_filename SUS-RunIIFall17MiniAODv2-00008_1_cfg.py \
    --no_exec \
    --customise Configuration/DataProcessing/Utils.addMonitoring \
    -n 100 || exit $? ;
cmsRun -e -j MINIAODSIM.xml SUS-RunIIFall17MiniAODv2-00008_1_cfg.py

