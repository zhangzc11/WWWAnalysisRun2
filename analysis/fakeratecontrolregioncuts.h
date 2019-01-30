#ifndef fakeratecontrolregioncuts_h
#define fakeratecontrolregioncuts_h

#include "wwwtree.h"
#include "globalvariables.h"
#include "rooutil/rooutil.h"

void addBtaggedControlRegionCuts(RooUtil::Cutflow& cutflow);
void addLowMETControlRegionCuts(RooUtil::Cutflow& cutflow);
void addBtaggedApplicationRegionCuts(RooUtil::Cutflow& cutflow);
void addLowMETApplicationRegionCuts(RooUtil::Cutflow& cutflow);

#endif
