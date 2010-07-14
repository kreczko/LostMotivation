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
			goodIsolatedBarrelElectrons(), goodIsolatedEndcapElectrons(), otherElectrons(), dataType(DATA) {

}

Event::~Event() {
}

bool Event::isRealData() {
	return dataType == DATA;
}

void Event::addElectrons(ElectronCollection electrons){
	otherElectrons.clear();
	otherElectrons = electrons;

}

ElectronCollection* Event::getOtherElectrons(){
	return &otherElectrons;
}

}
