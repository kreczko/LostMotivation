//#include "cute.h"
//#include "ide_listener.h"
//#include "cute_runner.h"
//#include "TestFilter.h"
//#include "Filter.h"
//#include "Taggers/BJetTagger.h"
//#include "RecoObjects/Jet.h"
//#include "RecoObjects/Electron.h"
//#include "RecoObjects/MET.h"
//#include "RecoObjects/PrimaryVertex.h"
//
//using namespace BAT;
//static Filter* filter;
//
//void setUpTestFilter() {
//	filter = Filter::makeStandardFilter();
//}
//
//void tearDownFilter() {
//	delete filter;
//}
//
//void testSetGoodVertexMinimalNumberOfDegreesOfFreedom() {
//	setUpTestFilter();
//	ASSERT_EQUAL(4, PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
//	filter->setGoodVertexMinimalNumberOfDegreesOfFreedom(5);
//	ASSERT_EQUAL(5, PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
//	tearDownFilter();
//}
//
//void testSetGoodVertexMaximalAbsoluteZPosition() {
//	setUpTestFilter();
//	ASSERT_EQUAL(15, PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
//	filter->setGoodVertexMaximalAbsoluteZPosition(20);
//	ASSERT_EQUAL(20, PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
//	tearDownFilter();
//}
//
//void testSetGoodVertexMaximalRho() {
//	setUpTestFilter();
//	ASSERT_EQUAL(2.0, PrimaryVertex::goodVertexMaximalAbsoluteRho);
//	filter->setGoodVertexMaximalRho(2.5);
//	ASSERT_EQUAL(2.5, PrimaryVertex::goodVertexMaximalAbsoluteRho);
//	tearDownFilter();
//}
//
//void testSetGoodJetMinimalPt() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(30.0, Jet::goodJetMinimalEt, 0.01);
//	filter->setGoodJetMinimalEt(50.5);
//	ASSERT_EQUAL_DELTA(50.5, Jet::goodJetMinimalEt, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodJetMaximalAbsoluteEta() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(2.4, Jet::goodJetMaximalAbsoluteEta, 0.01);
//	filter->setGoodJetMaximalAbsoluteEta(1.4);
//	ASSERT_EQUAL_DELTA(1.4, Jet::goodJetMaximalAbsoluteEta, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodJetMinimalElectromagneticFraction() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(0.01, Jet::goodJetMinimalElectromagneticFraction, 0.001);
//	filter->setGoodJetMinimalElectromagneticFraction(0.9);
//	ASSERT_EQUAL_DELTA(0.9, Jet::goodJetMinimalElectromagneticFraction, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(1., Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy, 0.001);
//	filter->setGoodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy(0.9);
//	ASSERT_EQUAL_DELTA(0.9, Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodJetMaximalFractionOfEnergyIntheHottestHPDReadout() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(0.98, Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout, 0.001);
//	filter->setGoodJetMaximalFractionOfEnergyIntheHottestHPDReadout(1.9);
//	ASSERT_EQUAL_DELTA(1.9, Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodElectronMinimalEt() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(30.0, Electron::goodElectronMinimalEt, 0.01);
//	filter->setGoodElectronMinimalEt(50.5);
//	ASSERT_EQUAL_DELTA(50.5, Electron::goodElectronMinimalEt, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodElectronMaximalAbsoluteEta() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(2.5, Electron::goodElectronMaximalAbsoluteEta, 0.01);
//	filter->setGoodElectronMaximalAbsoluteEta(1.442);
//	ASSERT_EQUAL_DELTA(1.442, Electron::goodElectronMaximalAbsoluteEta, 0.01);
//	tearDownFilter();
//}
//
//void testSetGoodElectronMaximalRelativeIsolation() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(0.1, Electron::isolatedElectronMaximalRelativeIsolation, 0.01);
//	filter->setIsolatedElectronMaximalRelativeIsolation(0.05);
//	ASSERT_EQUAL_DELTA(0.05, Electron::isolatedElectronMaximalRelativeIsolation, 0.005);
//	tearDownFilter();
//}
//
//void testSetLooseElectronMinimalEt() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(20, Electron::looseElectronMinimalEt, 0.1);
//	filter->setLooseElectronMinimalEt(55);
//	ASSERT_EQUAL_DELTA(55, Electron::looseElectronMinimalEt, 0.1);
//	tearDownFilter();
//}
//
//void testSetLooseElectronMaximalRelativeIsolation() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(1., Electron::looseIsolatedElectronMaximalRelativeIsolation, 0.01);
//	filter->setLooseIsolatedElectronMaximalRelativeIsolation(1.442);
//	ASSERT_EQUAL_DELTA(1.442, Electron::looseIsolatedElectronMaximalRelativeIsolation, 0.01);
//	tearDownFilter();
//}
//
//void testSetLooseElectronMaximalAbsoluteEta() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(2.5, Electron::looseElectronMaximalAbsoluteEta, 0.01);
//	filter->setLooseElectronMaximalAbsoluteEta(1.442);
//	ASSERT_EQUAL_DELTA(1.442, Electron::looseElectronMaximalAbsoluteEta, 0.01);
//	tearDownFilter();
//}
//void testSetGoodElectronMaximalDistanceFromInteractionPoint() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(200, Electron::goodElectronMaximalDistanceFromInteractionPoint, 0.1);
//	filter->setGoodElectronMaximalDistanceFromInteractionPoint(100);
//	ASSERT_EQUAL_DELTA(100, Electron::goodElectronMaximalDistanceFromInteractionPoint, 0.1);
//	tearDownFilter();
//}
//
//void testSetGoodMETMinimalEt() {
//	setUpTestFilter();
//	ASSERT_EQUAL_DELTA(20, MET::goodMETMinimalEt, 0.1);
//	filter->setGoodMETMinimalEt(30);
//	ASSERT_EQUAL_DELTA(30, MET::goodMETMinimalEt, 0.1);
//	tearDownFilter();
//}
//
//cute::suite make_suite_TestFilter() {
//	cute::suite s;
//	s.push_back(CUTE(testSetGoodVertexMinimalNumberOfDegreesOfFreedom));
//	s.push_back(CUTE(testSetGoodVertexMaximalAbsoluteZPosition));
//	s.push_back(CUTE(testSetGoodVertexMaximalRho));
//
//	s.push_back(CUTE(testSetGoodJetMinimalPt));
//	s.push_back(CUTE(testSetGoodJetMaximalAbsoluteEta));
//	s.push_back(CUTE(testSetGoodJetMinimalElectromagneticFraction));
//	s.push_back(CUTE(testSetGoodElectronMinimalEt));
//	s.push_back(CUTE(testSetGoodElectronMaximalAbsoluteEta));
//	s.push_back(CUTE(testSetGoodElectronMaximalRelativeIsolation));
//	s.push_back(CUTE(testSetGoodElectronMaximalDistanceFromInteractionPoint));
//	s.push_back(CUTE(testSetGoodMETMinimalEt));
//	s.push_back(CUTE(testSetLooseElectronMinimalEt));
//	s.push_back(CUTE(testSetLooseElectronMaximalRelativeIsolation));
//	s.push_back(CUTE(testSetLooseElectronMaximalAbsoluteEta));
//	s.push_back(CUTE(testSetGoodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy));
//	s.push_back(CUTE(testSetGoodJetMaximalFractionOfEnergyIntheHottestHPDReadout));
//
//	return s;
//}

