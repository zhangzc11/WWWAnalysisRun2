#ifndef misccontrolregioncuts_h
#define misccontrolregioncuts_h

#include "wwwtree.h"
#include "globalvariables.h"
#include "rooutil/rooutil.h"

void addGammaControlRegionCuts(RooUtil::Cutflow& cutflow);
void addOppositeSignControlRegionCuts(RooUtil::Cutflow& cutflow);
void addLooseLeptonControlRegionCuts(RooUtil::Cutflow& cutflow);

#endif
