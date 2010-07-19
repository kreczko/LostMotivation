/*
 * Electron.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Electron.h"
#include <assert.h>

namespace BAT {
float Electron::goodElectronMinimalEt = 0;
float Electron::goodElectronMaximalAbsoluteEta = 5;
float Electron::goodElectronMaximalDistanceFromInteractionPoint = 5000;

float Electron::isolatedElectronMaximalRelativeIsolation = 2;

Electron::Electron() :
	Particle(), robustLooseId(false), robustTightId(false), ecalIsolation(0), hcalIsolation(0), trackerIsolation(0),
			innerLayerMissingHits(0) {
}

Electron::Electron(float energy, float px, float py, float pz) :
	Particle(energy, px, py, pz), robustLooseId(false), robustTightId(false), ecalIsolation(0), hcalIsolation(0),
			trackerIsolation(0), innerLayerMissingHits(0) {
}

Electron::~Electron() {
	// TODO Auto-generated destructor stub
}

float Electron::relativeIsolation() const {
	return (ecalIsolation + hcalIsolation + trackerIsolation) / this->et();
}

bool Electron::isIsolated() const {
	return this->relativeIsolation() < Electron::isolatedElectronMaximalRelativeIsolation;
}

void Electron::setEcalIsolation(float isolation) {
	ecalIsolation = isolation;
}

void Electron::setHcalIsolation(float isolation) {
	hcalIsolation = isolation;
}

void Electron::setTrackerIsolation(float isolation) {
	trackerIsolation = isolation;
}

bool Electron::isGood() const {
	bool passesEt = et() > Electron::goodElectronMinimalEt;
	bool passesEta = fabs(eta()) < goodElectronMaximalAbsoluteEta;
	bool passesD0 = fabs(d0()) < goodElectronMaximalDistanceFromInteractionPoint;
	return passesEt && passesEta && passesD0;
}
}
