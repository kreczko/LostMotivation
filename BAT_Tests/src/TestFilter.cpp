#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestFilter.h"
#include "Filter.h"
#include "Taggers/BJetTagger.h"
#include "RecoObjects/Jet.h"
#include "RecoObjects/Electron.h"
#include "RecoObjects/MET.h"

using namespace BAT;
static Filter* filter;

void setUpTestFilter() {
	filter = Filter::makeStandardFilter();
}


void testSetGoodJetMinimalPt() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(30.0, Jet::goodJetMinimalEt, 0.01);
	filter->setGoodJetMinimalEt(50.5);
	ASSERT_EQUAL_DELTA(50.5, Jet::goodJetMinimalEt, 0.01);
}

void testSetGoodJetMaximalAbsoluteEta() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(2.4, Jet::goodJetMaximalAbsoluteEta, 0.01);
	filter->setGoodJetMaximalAbsoluteEta(1.4);
	ASSERT_EQUAL_DELTA(1.4, Jet::goodJetMaximalAbsoluteEta, 0.01);
}

void testSetGoodJetMinimalElectromagneticFraction() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(0.01, Jet::goodJetMinimalElectromagneticFraction, 0.001);
	filter->setGoodJetMinimalElectromagneticFraction(0.9);
	ASSERT_EQUAL_DELTA(0.9, Jet::goodJetMinimalElectromagneticFraction, 0.01);
}
void testSetGoodElectronMinimalEt() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(30.0, Electron::goodElectronMinimalEt, 0.01);
	filter->setGoodElectronMinimalEt(50.5);
	ASSERT_EQUAL_DELTA(50.5, Electron::goodElectronMinimalEt, 0.01);
}

void testSetGoodElectronMaximalAbsoluteEta() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(2.5, Electron::goodElectronMaximalAbsoluteEta, 0.01);
	filter->setGoodElectronMaximalAbsoluteEta(1.442);
	ASSERT_EQUAL_DELTA(1.442, Electron::goodElectronMaximalAbsoluteEta, 0.01);
}

void testSetGoodElectronMaximalRelativeIsolation() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(0.1, Electron::isolatedElectronMaximalRelativeIsolation, 0.01);
	filter->setIsolatedElectronMaximalRelativeIsolation(0.05);
	ASSERT_EQUAL_DELTA(0.05, Electron::isolatedElectronMaximalRelativeIsolation, 0.005);
}

void testSetGoodElectronMaximalDistanceFromInteractionPoint() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(200, Electron::goodElectronMaximalDistanceFromInteractionPoint, 0.1);
	filter->setGoodElectronMaximalDistanceFromInteractionPoint(100);
	ASSERT_EQUAL_DELTA(100, Electron::goodElectronMaximalDistanceFromInteractionPoint, 0.1);
}

void testSetGoodMETMinimalEt() {
	setUpTestFilter();
	ASSERT_EQUAL_DELTA(20, MET::goodMETMinimalEt, 0.1);
	filter->setGoodMETMinimalEt(30);
	ASSERT_EQUAL_DELTA(30, MET::goodMETMinimalEt, 0.1);
}

cute::suite make_suite_TestFilter() {
	cute::suite s;
	s.push_back(CUTE(testSetGoodJetMinimalPt));
	s.push_back(CUTE(testSetGoodJetMaximalAbsoluteEta));
	s.push_back(CUTE(testSetGoodJetMinimalElectromagneticFraction));
	s.push_back(CUTE(testSetGoodElectronMinimalEt));
	s.push_back(CUTE(testSetGoodElectronMaximalAbsoluteEta));
	s.push_back(CUTE(testSetGoodElectronMaximalRelativeIsolation));
	s.push_back(CUTE(testSetGoodElectronMaximalDistanceFromInteractionPoint));
	s.push_back(CUTE(testSetGoodMETMinimalEt));
	return s;
}

