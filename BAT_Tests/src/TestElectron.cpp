#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestElectron.h"
#include "RecoObjects/Electron.h"

using namespace BAT;
static Electron isolatedElectron;

void setUpTestElectron() {
	Electron::isolatedElectronMaximalRelativeIsolation = 0.1;
	isolatedElectron = Electron(30., 10., 0., 0.);
	isolatedElectron.setEcalEtSumInDr03(1.);
	isolatedElectron.setHcalEtSumInDr03(1.);
	isolatedElectron.setTrackPtSumInDr03(0.9);
}

void testConstructorEnergy() {
	setUpTestElectron();
	ASSERT_EQUAL_DELTA(30., isolatedElectron.energy(), 0.01);
}

void testConstructorPx() {
	setUpTestElectron();
	ASSERT_EQUAL_DELTA(10., isolatedElectron.px(), 0.01);
}

void testConstructorPy() {
	setUpTestElectron();
	ASSERT_EQUAL_DELTA(0., isolatedElectron.py(), 0.01);
}

void testConstructorPz() {
	setUpTestElectron();
	ASSERT_EQUAL_DELTA(0., isolatedElectron.pz(), 0.01);
}

void testRelativeIsolation(){
	setUpTestElectron();
	ASSERT_EQUAL_DELTA(2.9/30., isolatedElectron.relativeIsolation(), 0.01);
	ASSERT(isolatedElectron.isIsolated());
}


cute::suite make_suite_TestElectron() {
	cute::suite s;
	s.push_back(CUTE(testConstructorEnergy));
	s.push_back(CUTE(testConstructorPx));
	s.push_back(CUTE(testConstructorPy));
	s.push_back(CUTE(testConstructorPz));
	s.push_back(CUTE(testRelativeIsolation));
	return s;
}

