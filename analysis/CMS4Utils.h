#ifndef CMS4Utils_h
#define CMS4Utils_h

#include "CMS3.h"
#include "ElectronSelections.h"
#include "IsolationTools.h"
#include "Tools/JetCorrector.h"
#include "MuonSelections.h"
#include "SSSelections.h"
#include "Config.h"
#include "Base.h"

//// CORE
//#include "../CORE/CMS3.h"
//#include "../CORE/Base.h"
//#include "../CORE/OSSelections.h"
//#include "../CORE/SSSelections.h"
//#include "../CORE/VVVSelections.h"
//#include "../CORE/ElectronSelections.h"
//#include "../CORE/IsolationTools.h"
//#include "../CORE/JetSelections.h"
//#include "../CORE/IsoTrackVeto.h"
//#include "../CORE/PhotonSelections.h"
//#include "../CORE/TriggerSelections.h"
//#include "../CORE/VertexSelections.h"
//#include "../CORE/MCSelections.h"
//#include "../CORE/MetSelections.h"
//#include "../CORE/SimPa.h"
//#include "../CORE/Config.h"
////#include "../CORE/Tools/JetCorrector.h"
////#include "../CORE/Tools/jetcorr/FactorizedJetCorrector.h"
////#include "../CORE/Tools/jetcorr/JetCorrectionUncertainty.h"
//#include "../CORE/Tools/MT2/MT2.h"
//#include "../CORE/Tools/hemJet.h"
//#include "../CORE/Tools/utils.h"
//#include "../CORE/Tools/goodrun.h"
//#include "../CORE/Tools/btagsf/BTagCalibrationStandalone.h"
//#include "../CORE/Tools/btagsf/BTagCalibrationStandalone.h"
//#include "../CORE/Tools/datasetinfo/getDatasetInfo.h"

#include "rooutil.h"
#include "wwwtree.h"

class CMS4Reader
{
public:
    TChain* cms4_tree;

    void printParticle(int i);
    void printPartonsWithCondition(TString message, std::function<bool(int)> pass=nullptr);
    void open();
    void printLeptons();
};

extern CMS4Reader cms4reader;



#endif
