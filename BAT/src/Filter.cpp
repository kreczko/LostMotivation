/*
 * Filter.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Filter.h"
#include "../interface/Taggers/BJetTagger.h"
#include "../interface/RecoObjects/Jet.h"
#include "../interface/RecoObjects/Electron.h"
#include "../interface/RecoObjects/MET.h"

namespace BAT {

Filter::Filter() {

}

Filter::~Filter() {
}

Filter * Filter::makeStandardFilter() {
	Filter * filter = new Filter();
	
	filter->setGoodJetMinimalEt(30.0);
	filter->setGoodJetMaximalAbsoluteEta(2.4);
	filter->setGoodJetMinimalElectromagneticFraction(0.01);

	filter->setGoodElectronMinimalEt(30.0);
	filter->setGoodElectronMaximalAbsoluteEta(2.5);
	filter->setGoodElectronMaximalDistanceFromInteractionPoint(200);//micro meter
	filter->setIsolatedElectronMaximalRelativeIsolation(0.1);

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

}
