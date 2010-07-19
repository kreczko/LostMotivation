#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestElectron.h"
#include "RecoObjects/Electron.h"
#include <iostream>

using namespace BAT;
static Electron isolatedElectron;
static Electron goodElectron;
static Electron badEtElectron;
static Electron badEtaElectron;
static Electron badInCrackElectron;
static Electron badD0Electron;
static Electron badElectronFromConversion;
static Electron looseElectron;
static Electron badLooseElectronNoID;
static Electron badElectronNoID;

void setElectronConditions() {
	Electron::isolatedElectronMaximalRelativeIsolation = 0.1;
	Electron::goodElectronMaximalAbsoluteEta = 2.1;
	Electron::goodElectronMinimalEt = 20.;
	Electron::goodElectronMaximalDistanceFromInteractionPoint = 200.;
	Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion = 0;
	Electron::looseElectronMaximalAbsoluteEta = 2.5;
	Electron::looseElectronMinimalEt = 25;
	Electron::looseIsolatedElectronMaximalRelativeIsolation = 1.0;
}

void setIsolatedElectron() {
	isolatedElectron = Electron(30., 10., 0., 0.);
	isolatedElectron.setEcalIsolation(1.);
	isolatedElectron.setHcalIsolation(1.);
	isolatedElectron.setTrackerIsolation(0.9);
}

void setGoodElectron() {
	goodElectron = Electron(30., 20., 5., 2.);
	goodElectron.setHcalIsolation(0.5);
	goodElectron.setEcalIsolation(0.3);
	goodElectron.setTrackerIsolation(0.4);
	goodElectron.setVBTF_W70_ElectronID(true);

	ASSERT(fabs(goodElectron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
	ASSERT(fabs(goodElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
	ASSERT(goodElectron.et() > Electron::goodElectronMinimalEt);
}

void setBadEtElectron() {
	badEtElectron = Electron(20., 10., 0., 5.);
	badEtElectron.setD0(100.);
	badEtElectron.setVBTF_W70_ElectronID(true);
	ASSERT(fabs(badEtElectron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
	ASSERT(fabs(badEtElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
	//and fails the selected
	ASSERT(badEtElectron.et() < Electron::goodElectronMinimalEt);
}

void setBadEtaElectron() {
	badEtaElectron = Electron(400., 50., 50., 380);
	badEtaElectron.setSuperClusterEta(2.6);
	badEtaElectron.setVBTF_W70_ElectronID(true);
	//make sure it passes all other requirements
	ASSERT(badEtaElectron.et() > Electron::goodElectronMinimalEt);
	ASSERT(fabs(badEtaElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
	//and fails the selected
	ASSERT(fabs(badEtaElectron.superClusterEta()) > Electron::goodElectronMaximalAbsoluteEta);
}

void setBadD0Electron() {
	badD0Electron = Electron(40., 5., 5., 0.);
	badD0Electron.setD0(300.);
	badD0Electron.setVBTF_W70_ElectronID(true);
	//make sure it passes all other requirements
	ASSERT(badD0Electron.et() > Electron::goodElectronMinimalEt);
	ASSERT(fabs(badD0Electron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
	//and fails the selected
	ASSERT(fabs(badD0Electron.d0()) > Electron::goodElectronMaximalDistanceFromInteractionPoint);
}

void setBadInCrackElectron() {
	badInCrackElectron = Electron(400., 50., 50., 380);
	badInCrackElectron.setVBTF_W70_ElectronID(true);
	badInCrackElectron.setSuperClusterEta(1.5);
	//make sure it passes all other requirements
	ASSERT(badInCrackElectron.et() > Electron::goodElectronMinimalEt);
	ASSERT(fabs(badInCrackElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
	//and fails the selected
	ASSERT(fabs(badInCrackElectron.superClusterEta()) < Electron::goodElectronMaximalAbsoluteEta);
	ASSERT(badInCrackElectron.isInCrack());
}

void setElectronFromConversion() {
	badElectronFromConversion = Electron(400., 50., 50., 380);
	badElectronFromConversion.setNumberOfMissingInnerLayerHits(1);
	badElectronFromConversion.setVBTF_W70_ElectronID(true);
}

void setLooseElectron() {
	looseElectron = Electron(40., 20., 20., 0.);
	looseElectron.setRobustLooseID(true);
}

void setBadLooseElectronNoID() {
	badLooseElectronNoID = Electron(30., 20., 5., 2.);
	badLooseElectronNoID.setHcalIsolation(0.5);
	badLooseElectronNoID.setEcalIsolation(0.3);
	badLooseElectronNoID.setTrackerIsolation(0.4);
}

void setBadElectronNoID() {
	badElectronNoID = Electron(30., 20., 5., 2.);
	badElectronNoID.setHcalIsolation(0.5);
	badElectronNoID.setEcalIsolation(0.3);
	badElectronNoID.setTrackerIsolation(0.4);
}

void setUpElectrons() {
	setElectronConditions();
	setIsolatedElectron();
	setGoodElectron();
	setBadEtElectron();
	setBadEtaElectron();
	setBadD0Electron();
	setBadInCrackElectron();
	setElectronFromConversion();
	setLooseElectron();
	setBadLooseElectronNoID();
	setBadElectronNoID();
}

void testEcalIsolation() {
	setUpElectrons();
	ASSERT_EQUAL_DELTA(0.3, goodElectron.ecalIsolation(), 0.01);
}

void testHcalIsolation() {
	setUpElectrons();
	ASSERT_EQUAL_DELTA(0.5, goodElectron.hcalIsolation(), 0.01);
}

void testTrackerIsolation() {
	setUpElectrons();
	ASSERT_EQUAL_DELTA(0.4, goodElectron.trackerIsolation(), 0.01);
}

void testBadEtElectron() {
	setUpElectrons();
	ASSERT(badEtElectron.isGood() == false);
}

void testBadEtaElectron() {
	setUpElectrons();
	ASSERT(badEtaElectron.isGood() == false);
}

void testBadInCrackElectron() {
	setUpElectrons();
	ASSERT(badInCrackElectron.isGood() == false);
}

void testElectronFromConversion() {
	setUpElectrons();
	ASSERT(badElectronFromConversion.isFromConversion());
}
void testBadD0Electron() {
	setUpElectrons();
	ASSERT(badD0Electron.isGood() == false);
}

void testLooseElectron() {
	setUpElectrons();
	ASSERT(badD0Electron.isLoose() == false);
	ASSERT(looseElectron.isLoose());
}

void testRelativeIsolation() {
	setUpElectrons();
	ASSERT_EQUAL_DELTA(2.9/30., isolatedElectron.relativeIsolation(), 0.01);
	ASSERT(isolatedElectron.isIsolated());
}

void testGoodElectron() {
	setUpElectrons();
	ASSERT(goodElectron.isGood());
}

void testBadLooseElectronNoID() {
	setUpElectrons();
	ASSERT(badLooseElectronNoID.isLoose() == false);
}

void testBadElectronNoID() {
	setUpElectrons();
	ASSERT(badElectronNoID.isGood() == false);
}

cute::suite make_suite_TestElectron() {
	cute::suite s;
	s.push_back(CUTE(testRelativeIsolation));
	s.push_back(CUTE(testGoodElectron));
	s.push_back(CUTE(testBadEtElectron));
	s.push_back(CUTE(testBadEtaElectron));
	s.push_back(CUTE(testBadD0Electron));
	s.push_back(CUTE(testBadInCrackElectron));
	s.push_back(CUTE(testElectronFromConversion));
	s.push_back(CUTE(testEcalIsolation));
	s.push_back(CUTE(testHcalIsolation));
	s.push_back(CUTE(testTrackerIsolation));
	s.push_back(CUTE(testLooseElectron));
	s.push_back(CUTE(testBadLooseElectronNoID));
	s.push_back(CUTE(testBadElectronNoID));
	return s;
}

