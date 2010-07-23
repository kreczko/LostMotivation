#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestJet.h"
#include "RecoObjects/Jet.h"
#include "Taggers/BJetTagger.h"
using namespace BAT;

static Jet goodJet;
static Jet badEtaJet;
static Jet badEtJet;
static Jet badEMFJet;
static Jet badn90HitsJet;
static Jet badfHPDJet;

void setJetConditions() {
	Jet::goodJetMaximalAbsoluteEta = 2.4;
	Jet::goodJetMinimalEt = 30.0;
	Jet::goodJetMinimalElectromagneticFraction = 0.01;
	Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy = 1;
	Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout = 0.98;
}

void setUpGoodJet() {
	goodJet = Jet(290., 200., 200., 0.);
	goodJet.setEMF(0.1);
	goodJet.setN90Hits(2.);
	goodJet.setFHPD(0.5);
}

void setUpBadEtaJet() {
	badEtaJet = Jet(2900., 200., 2000., 0.);
	badEtaJet.setEMF(0.1);
	badEtaJet.setN90Hits(2.);
	badEtaJet.setFHPD(0.5);
	assert(badEtaJet.et() > Jet::goodJetMinimalEt);
}

void setUpBadEtJet() {
	badEtaJet = Jet(20., 20., 20., 0.);
	badEtaJet.setEMF(0.1);
	badEtaJet.setN90Hits(2.);
	badEtaJet.setFHPD(0.5);
	assert(fabs(badEtaJet.eta()) < Jet::goodJetMaximalAbsoluteEta);
}

void setUpBadEMFJet() {
	badEMFJet = Jet(290., 200., 200., 0.);
	badEMFJet.setEMF(0.);
	badEMFJet.setN90Hits(2.);
	badEMFJet.setFHPD(0.5);
}

void setUpBadn90HitsJet() {
	badn90HitsJet = Jet(290., 200., 200., 0.);
	badn90HitsJet.setEMF(0.2);
	badn90HitsJet.setN90Hits(1.);
	badn90HitsJet.setFHPD(0.5);
}

void setUpBadfHPDJet() {
	badfHPDJet = Jet(290., 200., 200., 0.);
	badfHPDJet.setEMF(0.2);
	badfHPDJet.setN90Hits(3.);
	badfHPDJet.setFHPD(0.99);
}

void setUpJets() {
	setJetConditions();
	setUpGoodJet();
	setUpBadEtaJet();
	setUpBadEtJet();
	setUpBadEMFJet();
	setUpBadn90HitsJet();
	setUpBadfHPDJet();
}

void testGoodJet() {
	setUpJets();
	ASSERT(goodJet.isGoodJet());
}

void testBadEtaJet() {
	setUpJets();
	ASSERT(badEtaJet.isGoodJet() == false);
}

void testBadEtJet() {
	setUpJets();
	ASSERT(badEtJet.isGoodJet() == false);
}

void testBadEMFJet() {
	setUpJets();
	ASSERT(badEMFJet.isGoodJet() == false);
}

void testBadN90HitsJet() {
	setUpJets();
	ASSERT(badn90HitsJet.isGoodJet() == false);
}

void testBadfHPDJet() {
	setUpJets();
	ASSERT(badfHPDJet.isGoodJet() == false);
}

void testUsedJetAlgorithm() {
	setUpJets();
	ASSERT_EQUAL(Jet::DEFAULT, goodJet.getUsedAlgorithm());
	goodJet.setUsedAlgorithm(Jet::ParticleFlow);
	ASSERT_EQUAL(Jet::ParticleFlow, goodJet.getUsedAlgorithm());
}

void testJetEMF() {
	setUpJets();
	goodJet.setEMF(2304.23);
	ASSERT_EQUAL_DELTA(2304.23, goodJet.emf(), 0.01);
}

void testJetN90Hits() {
	setUpJets();
	goodJet.setN90Hits(234.);
	ASSERT_EQUAL_DELTA(234., goodJet.n90Hits(), 0.1);
}

void testJetFHPD() {
	setUpJets();
	goodJet.setFHPD(0.444);
	ASSERT_EQUAL_DELTA(0.444, goodJet.fHPD(), 0.001);
}

void testPositiveBtag() {
	setUpJets();
	goodJet.setDiscriminatorForBtagType(BJetTagger::simpleSecondaryVertexHighEfficiencyMediumCut + 0.1,
			BJetTagger::SimpleSecondaryVertex);
	ASSERT(goodJet.isBJetAccordingToBtagAlgorithm(BJetTagger::SimpleSecondaryVertex));
}

void testNegativeBtag() {
	setUpJets();
	goodJet.setDiscriminatorForBtagType(BJetTagger::simpleSecondaryVertexHighEfficiencyMediumCut - 0.1,
			BJetTagger::SimpleSecondaryVertex);
	ASSERT(goodJet.isBJetAccordingToBtagAlgorithm(BJetTagger::SimpleSecondaryVertex) == false);
}
cute::suite make_suite_TestJet() {
	cute::suite s;
	s.push_back(CUTE(testGoodJet));
	s.push_back(CUTE(testBadEtaJet));
	s.push_back(CUTE(testBadEtJet));
	s.push_back(CUTE(testBadEMFJet));
	s.push_back(CUTE(testBadN90HitsJet));
	s.push_back(CUTE(testBadfHPDJet));

	s.push_back(CUTE(testUsedJetAlgorithm));
	s.push_back(CUTE(testJetEMF));
	s.push_back(CUTE(testJetN90Hits));
	s.push_back(CUTE(testJetFHPD));

	s.push_back(CUTE(testPositiveBtag));
	s.push_back(CUTE(testNegativeBtag));
	return s;
}

