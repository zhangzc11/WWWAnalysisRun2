#ifndef ElectronScaleFactors_h
#define ElectronScaleFactors_h

//
// Class to apply the electron ID scale factors presented and approved in the EGamma meeting:
// https://indico.cern.ch/event/879917/
// Watch out, there are two links in the agenda: be sure to took at the updated presentation
// from 19 February 2020
//
// Here the link to the website with all the plots and the histogram ROOT files:
// https://rembserj.web.cern.ch/rembserj/plots/egamma/20200218_electron_scale_factors/Ele_MVA_V2
//
// Author: Jonas Rembser 2020
//

#include "rooutil.h"

#include <vector>

// ID names in enum so we don't have to use strings in the event loop
enum class LeptonID {
  CommonVeto,
  ZCandidate,
  WCandidate,
  ThreeLepton,
  SameSign,
};

enum class SystematicVariation {
  Nominal = 0,
  Up = 1,
  Down = -1,
};

class ElectronScaleFactors {
public:
  // make sure this doesn't get descycronized with the ID enum class and string names
  static constexpr int yearMin = 2016;
  static constexpr int yearMax = 2018;
  static constexpr int nYears = yearMax - yearMin + 1;
  static constexpr int nIDs = 5;

  ElectronScaleFactors(std::string const& electronScaleFactorsPath);

  float operator()(int year, LeptonID id, float eta, float pt, SystematicVariation = SystematicVariation::Nominal);

  // get the index in the histMap array corresponding to the ID and the year
  // static_casting the enum class to int undermines a bit the idea of type safety,
  // therefore we'll check in ElectronScaleFactors.cc with some static_casts that everything goes well
  static constexpr int getIDHistMapIndex(int year, LeptonID id) {
    return (year - yearMin) * nIDs + static_cast<int>(id);
  }

private:
  std::vector<RooUtil::HistMap> histMapsReconstruction_;
  std::vector<RooUtil::HistMap> histMapsReconstructionLowPt_;
  std::vector<RooUtil::HistMap> histMapsIdentification_;
};

#endif
