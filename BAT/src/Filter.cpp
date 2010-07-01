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

namespace BAT {

Filter::Filter() {
	// TODO Auto-generated constructor stub

}

Filter::~Filter() {
	// TODO Auto-generated destructor stub
}

Filter * Filter::makeStandardFilter() {
	Filter * filter = new Filter();
	filter->setSimpleSecondaryVertexHighEfficiencyMediumCut(1.74);
	filter->setGoodJetMinimalEt(30.0);
	filter->setGoodJetMaximalAbsoluteEta(2.4);
	filter->setGoodJetMinimalElectromagneticFraction(0.01);
	filter->setGoodElectronMinimalEt(30.0);
	filter->setGoodElectronMaximalAbsoluteEta(2.5);
	return filter;
}

void Filter::setSimpleSecondaryVertexHighEfficiencyMediumCut(float cut) {
	BJetTagger::simpleSecondaryVertexHighEfficiencyMediumCut = cut;
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
}
