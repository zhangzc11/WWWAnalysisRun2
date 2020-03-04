#include "ElectronScaleFactors.h"

#include <stdexcept>
#include <experimental/filesystem>

namespace {
  struct IdentificationScaleFactorInfo {
    LeptonID id;       // the enum value in this class
    std::string flag;  // the flag in the TnP tool which appears in the filename of the histogram file
  };
}  // namespace

ElectronScaleFactors::ElectronScaleFactors(std::string const& electronScaleFactorsPath) {
  const std::vector<IdentificationScaleFactorInfo> idInfos{
      {LeptonID::CommonVeto, "passingVVVCommonVetoID"},
      {LeptonID::ZCandidate, "passingWVZCandidateZID"},
      {LeptonID::WCandidate, "passingWVZCandidateWID"},
      {LeptonID::ThreeLepton, "passingWWW3LID"},
      {LeptonID::SameSign, "passingWWWSameSignID"},
  };

  // Load ID scale factors
  std::string idPath = electronScaleFactorsPath + "/identification/";

  for (int year : {2016, 2017, 2018}) {
    for (auto const& idInfo : idInfos) {
      std::string rootFileName = idPath + std::to_string(year) + "_" + idInfo.flag + ".root";

      if (!std::experimental::filesystem::exists(rootFileName)) {
        throw std::runtime_error(std::string("Error in ElectronScaleFactors: ") + rootFileName + " not found!");
      }

      histMapsIdentification_.emplace_back(rootFileName + ":EGamma_SF2D");
    }

    // Load RECO scale factors
    std::string recoPath = electronScaleFactorsPath + "/reconstruction/";
    histMapsReconstruction_ = {
        {recoPath + "EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root:EGamma_SF2D"},       // 2016
        {recoPath + "egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D"},  // 2017
        {recoPath + "egammaEffi.txt_EGM2D_updatedAll.root:EGamma_SF2D"},            // 2018
    };
    histMapsReconstructionLowPt_ = {
        {recoPath + "EGM2D_BtoH_low_RecoSF_Legacy2016.root:EGamma_SF2D"},                 // 2016
        {recoPath + "egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root:EGamma_SF2D"},  // 2017
        // no 2018 version since there is only one histogram file in this year for all pT
    };
  }
}

float ElectronScaleFactors::operator()(int year, LeptonID id, float eta, float pt, SystematicVariation variation) {
  // make sure we get a supported year
  if (year < 2016 || year > 2018) {
    throw std::runtime_error("Year " + std::to_string(year) + " not supported!");
  }
  // basic eta and pt checks to make sure they are not accidentally swapped
  if (pt < 0) {
    throw std::runtime_error("The pt passed to ElectronScaleFactors is negative. Did you swap pt and eta?");
  }
  if (pt < 5.) {
    throw std::runtime_error(
        "The pt passed to ElectronScaleFactors is smaller than 5 GeV. This is ridiculous. Did you swap pt and eta?");
  }

  // choose RECO hist map
  auto recoYearIdx = year - 2016;
  auto& recoHistMap =
      (pt > 20 || year == 2018) ? histMapsReconstruction_[recoYearIdx] : histMapsReconstructionLowPt_[recoYearIdx];

  // choose ID HistMap
  auto& idHistMap = histMapsIdentification_[getIDHistMapIndex(year, id)];

  float scaleFactor = 1.0;

  // apply them
  if (variation == SystematicVariation::Nominal) {
    scaleFactor *= recoHistMap.eval(eta, pt);
    scaleFactor *= idHistMap.eval(eta, pt);
  }
  if (variation == SystematicVariation::Up) {
    scaleFactor *= recoHistMap.eval_up(eta, pt);
    scaleFactor *= idHistMap.eval_up(eta, pt);
  }
  if (variation == SystematicVariation::Down) {
    scaleFactor *= recoHistMap.eval_down(eta, pt);
    scaleFactor *= idHistMap.eval_down(eta, pt);
  }

  return scaleFactor;
}

// Let's check at compile time that the indices in the histMap array turn out fine, just in case
static_assert(ElectronScaleFactors::getIDHistMapIndex(2016, LeptonID::CommonVeto) == 0);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2016, LeptonID::ZCandidate) == 1);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2016, LeptonID::WCandidate) == 2);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2016, LeptonID::ThreeLepton) == 3);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2016, LeptonID::SameSign) == 4);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2017, LeptonID::CommonVeto) == 5);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2017, LeptonID::ZCandidate) == 6);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2017, LeptonID::WCandidate) == 7);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2017, LeptonID::ThreeLepton) == 8);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2017, LeptonID::SameSign) == 9);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2018, LeptonID::CommonVeto) == 10);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2018, LeptonID::ZCandidate) == 11);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2018, LeptonID::WCandidate) == 12);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2018, LeptonID::ThreeLepton) == 13);
static_assert(ElectronScaleFactors::getIDHistMapIndex(2018, LeptonID::SameSign) == 14);
