#ifndef histograms_h

#include "rooutil/rooutil.h"
#include "wwwtree.h"
#include "scalefactors.h"

RooUtil::Histograms createHistograms();

#ifndef __CINT__
extern const std::vector<float> eta_bounds = {0.0, 1.6, 2.4};
extern const std::vector<float> ptcorrcoarse_bounds = {0., 20., 25., 30., 35., 150.};
#endif

#endif
