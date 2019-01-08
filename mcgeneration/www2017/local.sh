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

#curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SMP-RunIIFall17wmLHEGS-00059 --retry 2 --create-dirs -o Configuration/GenProduction/python/SMP-RunIIFall17wmLHEGS-00059-fragment.py 
#[ -s Configuration/GenProduction/python/SMP-RunIIFall17wmLHEGS-00059-fragment.py ] || exit $?;

cat << EOF > www_2l_fragment.py
import FWCore.ParameterSet.Config as cms

externalLHEProducer = cms.EDProducer("ExternalLHEProducer",
    args = cms.vstring('/cvmfs/cms.cern.ch/phys_generator/gridpacks/2017/13TeV/madgraph/V5_2.4.2/VVV/WWWJets_4f_NLO_slc6_amd64_gcc481_CMSSW_7_1_30_tarball.tar.xz'),
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
                            pythia8CP5SettingsBlock,
                            pythia8aMCatNLOSettingsBlock,
                            processParameters = cms.vstring(
                                '23:mMin = 0.05',      
                                '24:mMin = 0.05',      
                                'TimeShower:nPartonsInBorn = 0', #number of coloured particles (before resonance decays) in born matrix element
                                'ResonanceDecayFilter:filter = on', 
                                'ResonanceDecayFilter:exclusive = off', #off: require at least the specified number of daughters, on: require exactly the specified number of daughters
                                'ResonanceDecayFilter:eMuAsEquivalent = off', #on: treat electrons and muons as equivalent
                                'ResonanceDecayFilter:eMuTauAsEquivalent = on', #on: treat electrons, muons , and taus as equivalent
                                'ResonanceDecayFilter:allNuAsEquivalent = on', #on: treat all three neutrino flavours as equivalent
            #'ResonanceDecayFilter:mothers =', #list of mothers not specified -> count all particles in hard process+resonance decays (better to avoid specifying mothers when including leptons from the lhe in counting, since intermediate resonances are not gauranteed to appear in general
                                'ResonanceDecayFilter:daughters = 11,11'
                                ),
                            parameterSets = cms.vstring('pythia8CommonSettings',
                                    'pythia8CP5Settings',
                                    'pythia8aMCatNLOSettings',
                                    'processParameters',
                                    )
                            )
                         )
ProductionFilterSequence = cms.Sequence(generator)

EOF

mkdir -p Configuration/GenProduction/python/
cp www_2l_fragment.py Configuration/GenProduction/python/

scram b
cd ../../
#cmsDriver.py Configuration/GenProduction/python/SMP-RunIIFall17wmLHEGS-00059-fragment.py \
cmsDriver.py Configuration/GenProduction/python/www_2l_fragment.py \
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
    -n 30 || exit $? ;
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
    -n 30 || exit $? ;
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
    -n 30 || exit $? ;
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
    -n 30 || exit $? ;
cmsRun -e -j MINIAODSIM.xml SMP-RunIIFall17MiniAODv2-00024_1_cfg.py
