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
			false), ecalEtSumInDr03(0), hcalEtSumInDr03(0), trackPtSumInDr03(0), innerLayerMissingHits(0) {
}

Electron::Electron(float energy, float px, float py, float pz): Particle(energy, px, py, pz), robustLooseId(false), robustTightId(
		false), ecalEtSumInDr03(0), hcalEtSumInDr03(0), trackPtSumInDr03(0), innerLayerMissingHits(0){

}

Electron::~Electron() {
	// TODO Auto-generated destructor stub
}

float Electron::relativeIsolation() const{
	return (ecalEtSumInDr03 + hcalEtSumInDr03 + trackPtSumInDr03)/this->et();
}

bool Electron::isIsolated() const{
	return this->relativeIsolation() < Electron::isolatedElectronMaximalRelativeIsolation;
}

void Electron::setEcalEtSumInDr03(float etsum){
	ecalEtSumInDr03 = etsum;
}

void Electron::setHcalEtSumInDr03(float etsum){
	hcalEtSumInDr03 = etsum;
}

void Electron::setTrackPtSumInDr03(float ptsum){
	trackPtSumInDr03 = ptsum;
}
}
