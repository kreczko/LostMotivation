#include "cute_suite.h"
#include "Event.h"
#include "Filter.h"
#include <boost/scoped_ptr.hpp>

using namespace BAT;

struct TestEvent {
	Event ttbarEvent, goodZEvent, poorZEvent, DiJetEvent, DiJetEventWithConversion;
	Event emptyEvent;
	boost::scoped_ptr<Filter> eventFilter;
	Electron goodIsolatedElectron, goodIsolatedElectron2;
	Electron goodLooseElectron;
	Electron badElectron;
	Electron electronFromConversion;
	Jet goodJet;
	Jet goodBJet;
	Jet badJet;
	PrimaryVertex goodVertex;
	PrimaryVertex badVertex;
	TestEvent() :
		ttbarEvent(), goodZEvent(), poorZEvent(), DiJetEvent(), DiJetEventWithConversion(), emptyEvent(), eventFilter(
				Filter::makeStandardFilter()), goodIsolatedElectron(100., 99., 13., 5.), goodIsolatedElectron2(100.,
				79., -13., -5.), goodLooseElectron(100., 79., -13., -5.), badElectron(20, 14., 15., 0),
				electronFromConversion(goodIsolatedElectron), goodJet(100, 99, 13, 5), goodBJet(goodJet), badJet(20,
						19, 0, 0), goodVertex(), badVertex() {
		setUpGoodIsolatedElectron();
		setUpGoodIsolatedElectron2();
		setUpGoodLooseElectron();
		setUpGoodIsolatedElectronFromConversion();
		setUpGoodJet();
		setUpGoodBJet();
		setUpGoodVertex();
		setUpBadVertex();

		setUpTTbarEvent();
		setUpGoodZEvent();
		setUpDiJetEvent();
	}

private:
	void setUpGoodIsolatedElectron() {
		goodIsolatedElectron.setHcalIsolation(0.5);
		goodIsolatedElectron.setEcalIsolation(0.3);
		goodIsolatedElectron.setTrackerIsolation(0.4);
		goodIsolatedElectron.setVBTF_W70_ElectronID(true);
		electronFromConversion.setNumberOfMissingInnerLayerHits(0);
	}

	void setUpGoodIsolatedElectron2() {
		goodIsolatedElectron2.setHcalIsolation(0.5);
		goodIsolatedElectron2.setEcalIsolation(0.3);
		goodIsolatedElectron2.setTrackerIsolation(0.4);
		goodIsolatedElectron2.setVBTF_W70_ElectronID(true);
		electronFromConversion.setNumberOfMissingInnerLayerHits(0);
	}

	void setUpGoodLooseElectron() {
		goodLooseElectron.setHcalIsolation(5);
		goodLooseElectron.setEcalIsolation(3);
		goodLooseElectron.setTrackerIsolation(4);
		goodLooseElectron.setVBTF_W70_ElectronID(false);
		goodLooseElectron.setRobustLooseID(true);
		electronFromConversion.setNumberOfMissingInnerLayerHits(0);
	}

	void setUpGoodIsolatedElectronFromConversion() {
		electronFromConversion.setHcalIsolation(0.5);
		electronFromConversion.setEcalIsolation(0.3);
		electronFromConversion.setTrackerIsolation(0.4);
		electronFromConversion.setVBTF_W70_ElectronID(true);
		electronFromConversion.setNumberOfMissingInnerLayerHits(3);
	}
	void setUpGoodJet() {
		goodJet.setEMF(0.2);
		goodJet.setFHPD(0.5);
		goodJet.setN90Hits(2);
	}

	void setUpGoodBJet() {
		goodBJet.setEMF(0.2);
		goodBJet.setFHPD(0.5);
		goodBJet.setN90Hits(2);
		goodBJet.setDiscriminatorForBtagType(2.5, BJetTagger::SimpleSecondaryVertex);
	}

	void setUpTTbarEvent() {
		ElectronCollection electrons;
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(badElectron);
		ttbarEvent.setElectrons(electrons);
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		jets.push_back(goodBJet);
		jets.push_back(badJet);
		ttbarEvent.setJets(jets);
		ttbarEvent.setHLT_Photon15_L1R(true);
		ttbarEvent.setPrimaryVertex(goodVertex);
	}

	void setUpGoodZEvent() {
		ElectronCollection electrons;
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(goodIsolatedElectron2);
		electrons.push_back(badElectron);
		goodZEvent.setElectrons(electrons);

		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		goodZEvent.setJets(jets);
		goodZEvent.setHLT_Photon15_L1R(true);
		goodZEvent.setPrimaryVertex(goodVertex);
	}

	void setUpPoorZEvent() {
		ElectronCollection electrons;
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(goodLooseElectron);
		electrons.push_back(badElectron);
		poorZEvent.setElectrons(electrons);

		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		poorZEvent.setJets(jets);
		poorZEvent.setHLT_Photon15_L1R(true);
		poorZEvent.setPrimaryVertex(goodVertex);
	}

	void setUpDiJetEvent() {
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		DiJetEvent.setJets(jets);
		DiJetEvent.setHLT_Photon15_L1R(false);
		DiJetEvent.setPrimaryVertex(badVertex);
	}

	void setUpDiJetEventWithConversion() {
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		DiJetEventWithConversion.setJets(jets);
		DiJetEventWithConversion.setHLT_Photon15_L1R(false);
		DiJetEventWithConversion.setPrimaryVertex(goodVertex);
		ElectronCollection electrons;
		electrons.push_back(electronFromConversion);
		DiJetEventWithConversion.setElectrons(electrons);
	}

	void setUpGoodVertex() {
		goodVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
		goodVertex.setFake(false);
		goodVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteRho);
		goodVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
	}

	void setUpBadVertex() {
		badVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
		badVertex.setFake(true);
		badVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteRho);
		badVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
	}

public:
	void testNumberOfElectrons() {
		ASSERT_EQUAL(2, ttbarEvent.getElectrons().size());
	}

	void testNumberOfGoodElectrons() {
		ASSERT_EQUAL(1, ttbarEvent.getGoodElectrons().size());
	}

	void testNumberOfGoodIsolatedElectrons() {
		ASSERT_EQUAL(1, ttbarEvent.getGoodIsolatedElectrons().size());
	}

	void testNumberOfJets() {
		ASSERT_EQUAL(5, ttbarEvent.getJets().size());
	}

	void testNumberOfGoodJets() {
		ASSERT_EQUAL(4, ttbarEvent.getGoodJets().size());
	}

	void testPassesHLT() {
		ASSERT(ttbarEvent.passesHighLevelTrigger());
	}

	void testDoesNotPassHLT() {
		ASSERT(DiJetEvent.passesHighLevelTrigger() == false);
	}

	void testDoesHaveGoodPV() {
		ASSERT(ttbarEvent.hasOneGoodPrimaryVertex());
	}

	void testDoesntHaveGoodPV() {
		ASSERT(DiJetEvent.hasOneGoodPrimaryVertex() == false);
	}

	void testHasOnlyOneGoodIsolatedElectron() {
		ASSERT(ttbarEvent.hasOnlyOneGoodIsolatedElectron());
	}

	void testHasNotOnlyOneGoodIsolatedElectron() {
		ASSERT(goodZEvent.hasOnlyOneGoodIsolatedElectron() == false);
		ASSERT(DiJetEvent.hasOnlyOneGoodIsolatedElectron() == false);
	}

	void testIsolatedElectronNotFromConversion() {
		ASSERT(ttbarEvent.isolatedElectronDoesNotComeFromConversion());
	}

	void testIsolatedElectronFromConversion() {
		ASSERT(DiJetEventWithConversion.isolatedElectronDoesNotComeFromConversion() == false);
	}

	void testNoElectronInEventReturnsFalse() {
		ASSERT(DiJetEvent.isolatedElectronDoesNotComeFromConversion() == false);
	}

	void testHasAtLeastOneGoodJet() {
		ASSERT(ttbarEvent.hasAtLeastOneGoodJet());
	}

	void testHasNoGoodJets() {
		ASSERT(emptyEvent.hasAtLeastOneGoodJet() == false);
	}

	void testHasAtLeastTwoGoodjet() {
		ASSERT(ttbarEvent.hasAtLeastTwoGoodJets());
	}

	void testHasNoTwoGoodJets() {
		ASSERT(emptyEvent.hasAtLeastTwoGoodJets() == false);
	}

	void testHasAtLeastThreeGoodJets() {
		ASSERT(ttbarEvent.hasAtLeastThreeGoodJets());
	}

	void testHasNoThreeGoodJets() {
		ASSERT(DiJetEvent.hasAtLeastThreeGoodJets() == false);
	}

	void testHasAtFourThreeGoodJets() {
		ASSERT(ttbarEvent.hasAtLeastThreeGoodJets());
	}

	void testHasNoFourThreeGoodJets() {
		ASSERT(DiJetEvent.hasAtLeastThreeGoodJets() == false);
	}

};

extern cute::suite make_suite_TestEvent() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfElectrons));
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodElectrons));
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodJets));

	s.push_back(CUTE_SMEMFUN(TestEvent, testPassesHLT));
	s.push_back(CUTE_SMEMFUN(TestEvent, testDoesNotPassHLT));
	s.push_back(CUTE_SMEMFUN(TestEvent, testDoesHaveGoodPV));
	s.push_back(CUTE_SMEMFUN(TestEvent, testDoesntHaveGoodPV));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasOnlyOneGoodIsolatedElectron));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasNotOnlyOneGoodIsolatedElectron));
	s.push_back(CUTE_SMEMFUN(TestEvent, testIsolatedElectronNotFromConversion));
	s.push_back(CUTE_SMEMFUN(TestEvent, testIsolatedElectronFromConversion));
	s.push_back(CUTE_SMEMFUN(TestEvent, testNoElectronInEventReturnsFalse));

	s.push_back(CUTE_SMEMFUN(TestEvent, testHasAtLeastOneGoodJet));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasNoGoodJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasAtLeastTwoGoodjet));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasNoTwoGoodJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasAtLeastThreeGoodJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasNoThreeGoodJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasAtFourThreeGoodJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testHasNoFourThreeGoodJets));
	return s;
}
