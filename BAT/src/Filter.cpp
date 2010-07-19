/*
 * Filter.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Filter.h"

namespace BAT {

Filter::Filter() {

}

Filter::~Filter() {
}

Filter * Filter::makeStandardFilter() {
	Filter::resetSelectionValues();
	Filter * filter = new Filter();
	
	filter->setGoodJetMinimalEt(30.0);
	filter->setGoodJetMaximalAbsoluteEta(2.4);
	filter->setGoodJetMinimalElectromagneticFraction(0.01);

	filter->setGoodElectronMinimalEt(30.0);
	filter->setGoodElectronMaximalAbsoluteEta(2.5);
	filter->setGoodElectronMaximalDistanceFromInteractionPoint(200);//micro meter

	filter->setLooseElectronMinimalEt(20.0);
	filter->setLooseElectronMaximalAbsoluteEta(2.5);

	filter->setIsolatedElectronMaximalRelativeIsolation(0.1);
	filter->setLooseIsolatedElectronMaximalRelativeIsolation(1.);

	filter->setGoodMETMinimalEt(20);

	return filter;
}

void Filter::setGoodJetMinimalEt(float minimalEt) {
	Jet::goodJetMinimalEt = minimalEt;
}

void Filter::setGoodJetMaximalAbsoluteEta(float maximalAbsoluteEta) {
	Jet::goodJetMaximalAbsoluteEta = maximalAbsoluteEta;
}

void Filter::setGoodJetMinimalElectromagneticFraction(float minimalElectromagneticFraction) {
	Jet::goodJetMinimalElectromagneticFraction = minimalElectromagneticFraction;
}

void Filter::setGoodElectronMinimalEt(float minimalEt){
	Electron::goodElectronMinimalEt = minimalEt;
}

void Filter::setGoodElectronMaximalAbsoluteEta(float maximalAbsoluteEta){
	Electron::goodElectronMaximalAbsoluteEta = maximalAbsoluteEta;
}

void Filter::setGoodElectronMaximalDistanceFromInteractionPoint(float maximalDistance){
	Electron::goodElectronMaximalDistanceFromInteractionPoint = maximalDistance;
}

void Filter::setIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation){
	Electron::isolatedElectronMaximalRelativeIsolation = maximalRelativeIsolation;
}

void Filter::setGoodMETMinimalEt(float minimalEt){
	MET::goodMETMinimalEt = minimalEt;
}

void Filter::setLooseElectronMinimalEt(float minimalEt){
	Electron::looseElectronMinimalEt = minimalEt;
}

void Filter::setLooseElectronMaximalAbsoluteEta(float maximalAbsoluteEta){
	Electron::looseElectronMaximalAbsoluteEta = maximalAbsoluteEta;
}

void Filter::setLooseIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation){
	Electron::looseIsolatedElectronMaximalRelativeIsolation = maximalRelativeIsolation;
}

}
