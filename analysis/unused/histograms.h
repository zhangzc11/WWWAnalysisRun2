#ifndef histograms_h
#define histograms_h

#include "rooutil/rooutil.h"
#include "wwwtree.h"
#include "scalefactors.h"

RooUtil::Histograms createHistograms();

#ifndef __CINT__
extern const std::vector<float> eta_bounds;
extern const std::vector<float> ptcorrcoarse_bounds;
#endif

#endif
