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

Electron::Electron() : Particle(),
	robustLooseId(false), robustTightId(
			false), calorimeterIsolation(0), trackerIsolation(0), relativeIsolation(0), innerLayerMissingHits(0) {
}

Electron::Electron(float energy, float px, float py, float pz): Particle(energy, px, py, pz), robustLooseId(false), robustTightId(
		false), calorimeterIsolation(0), trackerIsolation(0), relativeIsolation(0), innerLayerMissingHits(0){

}

Electron::~Electron() {
	// TODO Auto-generated destructor stub
}

}
