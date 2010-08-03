/*
 * Electron.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Electron.h"
#include <assert.h>
#include "../../interface/DetectorGeometry.h"

namespace BAT {
const boost::array<std::string, Electron::NUMBER_OF_ELECTRONIDS> Electron::ElectronIDNames = { { "loose ID",
		"tight ID", "robust loose ID", "robust tight ID", "VBTF working point 70%", "High Energy" } };
float Electron::goodElectronMinimalEt = 0;
float Electron::goodElectronMaximalAbsoluteEta = 5;
float Electron::goodElectronMaximalDistanceFromInteractionPoint = 5000;

float Electron::looseElectronMinimalEt = 0;
float Electron::looseElectronMaximalAbsoluteEta = 5;
float Electron::looseIsolatedElectronMaximalRelativeIsolation = 5000;

float Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion = 500;

float Electron::isolatedElectronMaximalRelativeIsolation = 2;

Electron::Electron() :
	Particle(), usedAlgorithm(Electron::Calo), robustLooseId(false), robustTightId(false), VBTF_W70_ElectronID(false),
			superCluser_Eta(0.), ecal_Isolation(0.), hcal_Isolation(0.), tracker_Isolation(0.), innerLayerMissingHits(
					0.) {
}

Electron::Electron(float energy, float px, float py, float pz) :
	Particle(energy, px, py, pz), usedAlgorithm(Electron::Calo), robustLooseId(false), robustTightId(false),
			VBTF_W70_ElectronID(false), superCluser_Eta(0.), ecal_Isolation(0.), hcal_Isolation(0.), tracker_Isolation(
					0.), innerLayerMissingHits(0.) {
}

Electron::~Electron() {
}

float Electron::superClusterEta() const {
	return superCluser_Eta;
}
float Electron::ecalIsolation() const {
	return ecal_Isolation;
}

float Electron::hcalIsolation() const {
	return hcal_Isolation;
}

float Electron::trackerIsolation() const {
	return tracker_Isolation;
}

float Electron::relativeIsolation() const {
	return (ecal_Isolation + hcal_Isolation + tracker_Isolation) / this->et();
}

bool Electron::isIsolated() const {
	return this->relativeIsolation() < Electron::isolatedElectronMaximalRelativeIsolation;
}

void Electron::setEcalIsolation(float isolation) {
	ecal_Isolation = isolation;
}

void Electron::setHcalIsolation(float isolation) {
	hcal_Isolation = isolation;
}

void Electron::setTrackerIsolation(float isolation) {
	tracker_Isolation = isolation;
}

void Electron::setSuperClusterEta(float eta) {
	superCluser_Eta = eta;
}

void Electron::setRobustLooseID(bool id) {
	robustLooseId = id;
}

void Electron::setRobustTightID(bool id) {
	robustTightId = id;
}

void Electron::setVBTF_W70_ElectronID(bool id) {
	VBTF_W70_ElectronID = id;
}
bool Electron::isLoose() const {
	bool passesEt = et() > Electron::looseElectronMinimalEt;
	bool passesEta = fabs(eta()) < Electron::looseElectronMaximalAbsoluteEta;
	bool passesIsolation = relativeIsolation() < Electron::looseIsolatedElectronMaximalRelativeIsolation;
	return passesEt && passesEta && passesIsolation && robustLooseId;
}

bool Electron::isGood() const {
	bool passesEt = et() > Electron::goodElectronMinimalEt;
	bool passesEta = fabs(superClusterEta()) < goodElectronMaximalAbsoluteEta && !isInCrack();
	bool passesD0 = fabs(d0()) < goodElectronMaximalDistanceFromInteractionPoint;
	bool passesID = VBTF_W70_ElectronID;
	return passesEt && passesEta && passesD0 && passesID;
}

bool Electron::isInBarrelRegion() const {
	return fabs(superClusterEta()) < Detector::Barrel::MaximalAbsoluteEta;
}

bool Electron::isInCrack() const {
	bool passesMinimalEta = fabs(superClusterEta()) > Detector::Crack::MinimalAbsoluteEta;
	bool passesMaximalEta = fabs(superClusterEta()) < Detector::Crack::MaximalAbsoluteEta;
	return passesMinimalEta && passesMaximalEta;
}

bool Electron::isInEndCapRegion() const {
	return fabs(superClusterEta()) > Detector::EndCap::MinimalAbsoluteEta;
}

bool Electron::isFromConversion() const {
	return innerLayerMissingHits > Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion;
}

void Electron::setNumberOfMissingInnerLayerHits(float missingHits) {
	innerLayerMissingHits = missingHits;
}

unsigned short Electron::getClosestJetID(const JetCollection& jets) const {//#TODO fix definition in Particles!!!
	unsigned short idOfClosest = 999;
	float closestDR = 999.;
	for (unsigned short index = 0; index < jets.size(); ++index) {
		float DR = deltaR(jets.at(index));
		if (DR < closestDR) {
			closestDR = DR;
			idOfClosest = index;
		}
	}
	return idOfClosest;
}

void Electron::setUsedAlgorithm(Electron::Algorithm algo) {
	usedAlgorithm = algo;
}

}
