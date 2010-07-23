/*
 * Event.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Event.h"

namespace BAT {

Event::Event() :
	goodElectrons(), goodBarrelElectrons(), goodEndcapElectrons(), goodIsolatedElectrons(),
			goodIsolatedBarrelElectrons(), goodIsolatedEndcapElectrons(), allElectrons(), dataType(DATA) {

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

void Event::addElectrons(ElectronCollection electrons){
	allElectrons.clear();
	allElectrons = electrons;

}

const ElectronCollection& Event::getElectrons() const{
	return allElectrons;
}

const ElectronCollection& Event::getGoodElectrons() const{
	return goodElectrons;
}

}
