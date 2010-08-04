#include "cute_suite.h"
#include "Event.h"
#include "Filter.h"
#include <boost/scoped_ptr.hpp>
#include "Selection.h"

using namespace BAT;

struct TestEvent {
	Event ttbarEvent, goodZEvent, poorZEvent, DiJetEvent, DiJetEventWithConversion, muonEvent;
	Event emptyEvent;
	boost::scoped_ptr<Filter> eventFilter;
	Electron goodIsolatedElectron, goodIsolatedElectron2;
	Electron goodLooseElectron;
	Electron badElectron;
	Electron electronFromConversion;
	Jet goodJet;
	Jet goodBJet;
	Jet badJet;
	Jet goodJetCloseToElectron;
	PrimaryVertex goodVertex;
	PrimaryVertex badVertex;
	Muon goodIsolatedMuon;
	Muon badMuon;
	MET met;
	TestEvent() :
		ttbarEvent(), goodZEvent(), poorZEvent(), DiJetEvent(), DiJetEventWithConversion(), muonEvent(), emptyEvent(),
				eventFilter(Filter::makeStandardFilter()), goodIsolatedElectron(100., 99., 13., 5.),
				goodIsolatedElectron2(100., 79., -13., -5.), goodLooseElectron(100., 79., -13., -5.), badElectron(20,
						14., 15., 0), electronFromConversion(goodIsolatedElectron), goodJet(100, 13, 99, 5), goodBJet(
						goodJet), badJet(20, 19, 0, 0), goodJetCloseToElectron(100., 98., 13., 5.), goodVertex(),
				badVertex(), goodIsolatedMuon(100., 99., 13., 5.), badMuon(100., 99., 13., 5.), met(40, 30) {
		setUpGoodIsolatedElectron();
		setUpGoodIsolatedElectron2();
		setUpGoodLooseElectron();
		setUpBadElectron();
		setUpGoodIsolatedElectronFromConversion();
		setUpGoodJet();
		setUpGoodBJet();
		setUpGoodJetCloseToElectron();
		setUpGoodVertex();
		setUpBadVertex();
		setUpIsolatedGoodMuon();
		setUpBadMuon();

		setUpTTbarEvent();
		setUpGoodZEvent();
		setUpPoorZEvent();
		setUpDiJetEvent();
		setUpMuonEvent();
	}

private:
	void setUpGoodIsolatedElectron() {
		goodIsolatedElectron.setHcalIsolation(0.5);
		goodIsolatedElectron.setEcalIsolation(0.3);
		goodIsolatedElectron.setTrackerIsolation(0.4);
		goodIsolatedElectron.setVBTF_W70_ElectronID(true);
		goodIsolatedElectron.setNumberOfMissingInnerLayerHits(0);
	}

	void setUpGoodIsolatedElectron2() {
		goodIsolatedElectron2.setHcalIsolation(0.4);
		goodIsolatedElectron2.setEcalIsolation(0.3);
		goodIsolatedElectron2.setTrackerIsolation(0.4);
		goodIsolatedElectron2.setVBTF_W70_ElectronID(true);
		goodIsolatedElectron2.setNumberOfMissingInnerLayerHits(0);
	}

	void setUpBadElectron() {
		badElectron.setHcalIsolation(4);
		badElectron.setEcalIsolation(44);
		badElectron.setTrackerIsolation(1);
	}

	void setUpGoodLooseElectron() {
		goodLooseElectron.setHcalIsolation(5);
		goodLooseElectron.setEcalIsolation(3);
		goodLooseElectron.setTrackerIsolation(4);
		goodLooseElectron.setVBTF_W70_ElectronID(false);
		goodLooseElectron.setRobustLooseID(true);
		goodLooseElectron.setNumberOfMissingInnerLayerHits(0);
		assert(goodLooseElectron.isGood() == false);
		assert(goodLooseElectron.isLoose());
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

	void setUpGoodJetCloseToElectron() {
		goodJetCloseToElectron.setEMF(0.2);
		goodJetCloseToElectron.setFHPD(0.5);
		goodJetCloseToElectron.setN90Hits(2);
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

	void setUpIsolatedGoodMuon() {
		goodIsolatedMuon.makeGlobal(true);
		goodIsolatedMuon.setEcalIsolation(1);
		goodIsolatedMuon.setHcalIsolation(1);
		goodIsolatedMuon.setTrackerIsolation(1);
	}

	void setUpBadMuon() {
		badMuon.makeGlobal(false);
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
		MuonCollection muons;
		muons.push_back(badMuon);
		ttbarEvent.setMuons(muons);
		ttbarEvent.setMET(met);
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

	void setUpMuonEvent() {
		ElectronCollection electrons;
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(badElectron);
		muonEvent.setElectrons(electrons);
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		jets.push_back(goodBJet);
		jets.push_back(badJet);
		muonEvent.setJets(jets);
		muonEvent.setHLT_Photon15_L1R(true);
		muonEvent.setPrimaryVertex(goodVertex);
		MuonCollection muons;
		muons.push_back(goodIsolatedMuon);
		muonEvent.setMuons(muons);
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

	void testTTbarIsNotAZBosonEvent() {
		ASSERT(ttbarEvent.isNotAZBosonEvent());
	}

	void testGoodZIsAZBosonEvent() {
		ASSERT(goodZEvent.isNotAZBosonEvent() == false);
	}

	void testPoorZIsAZBosonEvent() {
		ASSERT(poorZEvent.isNotAZBosonEvent() == false);
	}

	void testDiJetIsNotAZBosonEvent() {
		ASSERT(DiJetEvent.isNotAZBosonEvent());
	}

	void testTTbarEventPassesMuonVeto() {
		ASSERT_EQUAL(true, ttbarEvent.hasNoIsolatedMuon());
	}

	void testMuonEventDoesnPassMuonVeto() {
		ASSERT_EQUAL(false, muonEvent.hasNoIsolatedMuon());
	}

	void testRunNumber() {
		ttbarEvent.setRunNumber(42);
		ASSERT_EQUAL(42, ttbarEvent.runnumber());
	}

	void testEventNumber() {
		ttbarEvent.setEventNumber(42);
		ASSERT_EQUAL(42, ttbarEvent.eventnumber());
	}

	void testLocalEventNumber() {
		ttbarEvent.setLocalEventNumber(42);
		ASSERT_EQUAL(42, ttbarEvent.localnumber());
	}

	void testLumiBlock() {
		ttbarEvent.setLumiBlock(42);
		ASSERT_EQUAL(42, ttbarEvent.lumiblock());
	}

	void testEventWeight() {
		ttbarEvent.setEventWeight(1.152);
		ASSERT_EQUAL_DELTA(1.152, ttbarEvent.weight(), 0.001);
	}

	void testEventPasses1stStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::HighLevelTrigger));
	}

	void testEventPasses2ndStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::GoodPrimaryvertex));
	}

	void testEventPasses3ndStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::OneIsolatedElectron));
	}

	void testEventPasses4thStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::ConversionRejection));
	}

	void testEventPasses5thStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::LooseMuonVeto));
	}

	void testEventPasses6thStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::AtLeastFourGoodJets));
	}

	void testEventPasses7thStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStep(TTbarEPlusJetsSelection::Zveto));
	}

	void testTTbarEventPassesNStep() {
		ASSERT_EQUAL(true, ttbarEvent.passesSelectionStepUpTo(TTbarEPlusJetsSelection::Zveto));
	}

	void testPoorZEventPassesUpToStep() {
		ASSERT_EQUAL(true, poorZEvent.passesSelectionStepUpTo(TTbarEPlusJetsSelection::AtLeastFourGoodJets));
	}

	void testPoorZEventDoesntPassUpToStep() {
		ASSERT_EQUAL(false, poorZEvent.passesSelectionStepUpTo(TTbarEPlusJetsSelection::Zveto));
	}

	void testPassesFullTTbarSelection() {
		ASSERT_EQUAL(true, ttbarEvent.passesFullTTbarEPlusJetSelection());
	}

	void testFailsFullTTbarSelection() {
		ASSERT_EQUAL(false, DiJetEvent.passesFullTTbarEPlusJetSelection());
	}

	void testGetMostIsolatedElectron() {
		ASSERT_EQUAL_DELTA(goodIsolatedElectron2.relativeIsolation(),
				goodZEvent.getMostIsolatedElectron().relativeIsolation(), 0.001);
	}

	void testGoodJetCleaning() {
		Event event = Event();
		ElectronCollection electrons;
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(badElectron);
		event.setElectrons(electrons);
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		jets.push_back(goodBJet);
		jets.push_back(goodJetCloseToElectron);
		event.setJets(jets);
		ASSERT_EQUAL(5, event.getJets().size());
		ASSERT_EQUAL(4, event.getGoodJets().size());
	}

	void testGoodJetCleaningNoGoodElectrons() {
		Event event = Event();
		ElectronCollection electrons;
		goodIsolatedElectron.setVBTF_W70_ElectronID(false);
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(badElectron);
		event.setElectrons(electrons);
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		jets.push_back(goodBJet);
		jets.push_back(goodJetCloseToElectron);
		event.setJets(jets);
		ASSERT_EQUAL(0, event.getGoodElectrons().size());
		ASSERT_EQUAL(0, event.getGoodIsolatedElectrons().size());
		ASSERT_EQUAL(jets.size(), event.getJets().size());
		ASSERT_EQUAL(jets.size() - 1, event.getGoodJets().size());
	}

	void testGoodJetCleaningNoElectrons() {
		Event event = Event();
		JetCollection jets;
		jets.push_back(goodJet);
		jets.push_back(goodJet);
		jets.push_back(goodBJet);
		jets.push_back(goodBJet);
		jets.push_back(goodJetCloseToElectron);
		event.setJets(jets);
		ASSERT_EQUAL(jets.size(), event.getJets().size());
		ASSERT_EQUAL(jets.size(), event.getGoodJets().size());
	}

	void testGoodJetCleaningNoGoodJets() {
		Event event = Event();
		ElectronCollection electrons;
		electrons.push_back(goodIsolatedElectron);
		electrons.push_back(badElectron);
		event.setElectrons(electrons);
		JetCollection jets;
		jets.push_back(badJet);
		event.setJets(jets);
		ASSERT_EQUAL(jets.size(), event.getJets().size());
		ASSERT_EQUAL(0, event.getGoodJets().size());
	}

	void testMET(){
	    ASSERT_EQUAL(50, ttbarEvent.getMET().et());
	}

};

extern cute::suite make_suite_TestEvent() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfElectrons));
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodElectrons));
	s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodIsolatedElectrons));
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

	s.push_back(CUTE_SMEMFUN(TestEvent, testTTbarIsNotAZBosonEvent));
	s.push_back(CUTE_SMEMFUN(TestEvent, testGoodZIsAZBosonEvent));
	s.push_back(CUTE_SMEMFUN(TestEvent, testPoorZIsAZBosonEvent));
	s.push_back(CUTE_SMEMFUN(TestEvent, testDiJetIsNotAZBosonEvent));

	s.push_back(CUTE_SMEMFUN(TestEvent, testTTbarEventPassesMuonVeto));
	s.push_back(CUTE_SMEMFUN(TestEvent, testMuonEventDoesnPassMuonVeto));

	s.push_back(CUTE_SMEMFUN(TestEvent, testRunNumber));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventNumber));
	s.push_back(CUTE_SMEMFUN(TestEvent, testLocalEventNumber));
	s.push_back(CUTE_SMEMFUN(TestEvent, testLumiBlock));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventWeight));

	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses1stStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses2ndStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses3ndStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses4thStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses5thStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses6thStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testEventPasses7thStep));

	s.push_back(CUTE_SMEMFUN(TestEvent, testTTbarEventPassesNStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testPoorZEventPassesUpToStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testPoorZEventDoesntPassUpToStep));
	s.push_back(CUTE_SMEMFUN(TestEvent, testPassesFullTTbarSelection));
	s.push_back(CUTE_SMEMFUN(TestEvent, testFailsFullTTbarSelection));

	s.push_back(CUTE_SMEMFUN(TestEvent, testGetMostIsolatedElectron));

	s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaning));
	s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaningNoGoodElectrons));
	s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaningNoElectrons));
	s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaningNoGoodJets));
	s.push_back(CUTE_SMEMFUN(TestEvent, testMET));

	return s;
}
