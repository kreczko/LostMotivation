/*
 * Electron.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Electron.h"

namespace BAT {
float Electron::goodElectronMinimalEt = 0;
float Electron::goodElectronMaximalAbsoluteEta = 5;
float Electron::goodElectronMaximalDistanceFromInteractionPoint = 5000;

float Electron::isolatedElectronMaximalRelativeIsolation = 2;

Electron::Electron() :
	energy(0), transversalEnergy(0), px(0), py(0), pz(0), pt(0), eta(0), phi(0), robustLooseId(false), robustTightId(
			false), calorimeterIsolation(0), trackerIsolation(0), relativeIsolation(0), innerLayerMissingHits(0) {
	// TODO Auto-generated constructor stub

}

Electron::~Electron() {
	// TODO Auto-generated destructor stub
}

}
