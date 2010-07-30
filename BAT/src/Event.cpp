/*
 * Event.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Event.h"

namespace BAT {

Event::Event() :
	HLT_PHOTON15_L1R(false), primaryVertex(), allElectrons(), goodElectrons(), goodBarrelElectrons(),
			goodEndcapElectrons(), goodIsolatedElectrons(), goodIsolatedBarrelElectrons(),
			goodIsolatedEndcapElectrons(), dataType(DATA) {

}

Event::~Event() {
}

bool Event::isRealData() const {
	return dataType == DATA;
}

const Event::DataType Event::getDataType() const {
	return dataType;
}

void Event::setDataType(Event::DataType type) {
	dataType = type;
}

void Event::setPrimaryVertex(PrimaryVertex vertex) {
	primaryVertex = vertex;
}
void Event::setElectrons(ElectronCollection electrons) {
	allElectrons.clear();
	allElectrons = electrons;
	selectElectronsByQuality();
}

void Event::setJets(JetCollection jets) {
	allJets.clear();
	allJets = jets;
	selectGoodJets();
}

void Event::setHLT_Photon15_L1R(bool hltTrigger) {
	HLT_PHOTON15_L1R = hltTrigger;
}

const PrimaryVertex& Event::getPrimaryVertex() const {
	return primaryVertex;
}

const ElectronCollection& Event::getElectrons() const {
	return allElectrons;
}

const ElectronCollection& Event::getGoodElectrons() const {
	return goodElectrons;
}

const ElectronCollection& Event::getGoodIsolatedElectrons() const {
	return goodIsolatedElectrons;
}

const JetCollection& Event::getJets() const {
	return allJets;
}

const JetCollection& Event::getGoodJets() const {
	return goodJets;
}

void Event::selectElectronsByQuality() {
	goodElectrons.clear();
	goodIsolatedElectrons.clear();
	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		Electron electron = allElectrons.at(index);

		if (electron.isGood())
			goodElectrons.push_back(electron);

		if (electron.isGood() && electron.isIsolated())
			goodIsolatedElectrons.push_back(electron);
		if(electron.isGood() == false && electron.isLoose())
			looseElectrons.push_back(electron);
	}
}

void Event::selectGoodJets() {
	goodJets.clear();
	for (unsigned int index = 0; index < allJets.size(); ++index) {
		if (allJets.at(index).isGood())
			goodJets.push_back(allJets.at(index));
	}
}

bool Event::passesHighLevelTrigger() const {
	return HLT_PHOTON15_L1R;
}

bool Event::hasOneGoodPrimaryVertex() const {
	return primaryVertex.isGood();
}

bool Event::hasOnlyOneGoodIsolatedElectron() const {
	return goodIsolatedElectrons.size() == 1;
}

bool Event::isolatedElectronDoesNotComeFromConversion() const {
	if (goodIsolatedElectrons.size() > 0)
		return goodIsolatedElectrons.front().isFromConversion() == false;
	else
		return false;
}

bool Event::hasAtLeastOneGoodJet() const {
	return goodJets.size() >= 1;
}

bool Event::hasAtLeastTwoGoodJets() const {
	return goodJets.size() >= 2;
}

bool Event::hasAtLeastThreeGoodJets() const {
	return goodJets.size() >= 3;
}

bool Event::hasAtLeastFourGoodJets() const {
	return goodJets.size() >= 4;
}

bool Event::isNotAZBosonEvent() const {
	float invariantMass = 0;
	if (goodIsolatedElectrons.size() == 2)
		invariantMass = goodIsolatedElectrons.at(0).invariantMass(goodIsolatedElectrons.at(1));
	else if (goodIsolatedElectrons.size() == 1 && looseElectrons.size() > 0)
		invariantMass = goodIsolatedElectrons.front().invariantMass(looseElectrons.front());

	bool passesLowerLimit = invariantMass >= 76;
	bool passesUpperLimit = invariantMass <= 106;
	return (passesLowerLimit && passesUpperLimit) == false;
}

}
