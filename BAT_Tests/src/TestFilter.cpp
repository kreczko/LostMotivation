#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestFilter.h"
#include "Filter.h"
#include "Taggers/BJetTagger.h"
#include "RecoObjects/Jet.h"
#include "RecoObjects/Electron.h"

using namespace BAT;
static Filter* filter;

void setUpTestFilter() {
	filter = Filter::makeStandardFilter();
}

void testSetBTagSimpleSecondaryVertexHighEfficiencyMediumCut() {
	setUpTestFilter();
	//standard value
	ASSERT_EQUAL_DELTA(1.74, BJetTagger::simpleSecondaryVertexHighEfficiencyMediumCut, 0.01);
	filter->setSimpleSecondaryVertexHighEfficiencyMediumCut(2.0);
	ASSERT_EQUAL_DELTA(2.0, BJetTagger::simpleSecondaryVertexHighEfficiencyMediumCut, 0.01);
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
	ASSERT_EQUAL_DELTA(50.5, Electron::goodElectronMinimalEt, 0.01);
}

cute::suite make_suite_TestFilter() {
	cute::suite s;
	s.push_back(CUTE(testSetBTagSimpleSecondaryVertexHighEfficiencyMediumCut));
	s.push_back(CUTE(testSetGoodJetMinimalPt));
	s.push_back(CUTE(testSetGoodJetMaximalAbsoluteEta));
	s.push_back(CUTE(testSetGoodJetMinimalElectromagneticFraction));
	s.push_back(CUTE(testSetGoodElectronMinimalEt));
	return s;
}

