/*
 * Event.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Event.h"

namespace BAT {

Event::Event() :
	allElectrons(),goodElectrons(), goodBarrelElectrons(), goodEndcapElectrons(), goodIsolatedElectrons(),
			goodIsolatedBarrelElectrons(), goodIsolatedEndcapElectrons(),  dataType(DATA) {

}

Event::~Event() {
}

bool Event::isRealData() const{
	return dataType == DATA;
}

const Event::DataType Event::getDataType() const{
	return dataType;
}

void Event::setDataType(Event::DataType type){
	dataType = type;
}

void Event::setElectrons(ElectronCollection electrons){
	allElectrons.clear();
	allElectrons = electrons;
	selectGoodElectrons();
}

void Event::setJets(JetCollection jets){
	allJets.clear();
	allJets = jets;
	selectGoodJets();
}

const ElectronCollection& Event::getElectrons() const{
	return allElectrons;
}

const ElectronCollection& Event::getGoodElectrons() const{
	return goodElectrons;
}

const JetCollection& Event::getJets() const{
	return allJets;
}

const JetCollection& Event::getGoodJets() const{
	return goodJets;
}

void Event::selectGoodElectrons(){
	goodElectrons.clear();
	for(unsigned int index = 0; index < allElectrons.size(); ++ index){
		if(allElectrons.at(index).isGood())
			goodElectrons.push_back(allElectrons.at(index));
	}
}

void Event::selectGoodJets(){
	goodJets.clear();
	for(unsigned int index = 0; index < allJets.size(); ++ index){
		if(allJets.at(index).isGood())
			goodJets.push_back(allJets.at(index));
	}
}

}
