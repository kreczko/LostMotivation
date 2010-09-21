#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>

#include "../interface/Event.h"
#include "../interface/Filter.h"
#include "../interface/Selection.h"
#include "../interface/VBTF_ElectronID.h"

using namespace BAT;

struct TestEvent {
    Event ttbarEvent, goodZEvent, poorZEvent, DiJetEvent, DiJetEventWithConversion, muonEvent;
    Event emptyEvent;
    boost::scoped_ptr<Filter> eventFilter;
    ElectronPointer goodIsolatedElectron, goodIsolatedElectron2;
    ElectronPointer goodLooseElectron;
    ElectronPointer badElectron;
    ElectronPointer electronFromConversion;
    JetPointer goodJet, goodBJet, badJet, goodJetCloseToElectron;
    PrimaryVertex goodVertex;
    PrimaryVertex badVertex;
    Muon goodIsolatedMuon;
    Muon badMuon;
    METPointer met;
    TestEvent() :
        ttbarEvent(), goodZEvent(), poorZEvent(), DiJetEvent(), DiJetEventWithConversion(), muonEvent(), emptyEvent(),
                eventFilter(Filter::makeTopPairEPlusJetsFilter()), goodIsolatedElectron(
                        new Electron(100., 99., 13., 5.)), goodIsolatedElectron2(new Electron(100., 79., -13., -5.)),
                goodLooseElectron(new Electron(100., 79., -13., -5.)), badElectron(new Electron(20, 14., 15., 0)),
                electronFromConversion(new Electron(*goodIsolatedElectron)), goodJet(new Jet(100, 13, 99, 5)),
                goodBJet(new Jet(*goodJet)), badJet(new Jet(20, 19, 0, 0)), goodJetCloseToElectron(new Jet(100., 98.,
                        13., 5.)), goodVertex(), badVertex(), goodIsolatedMuon(100., 99., 13., 5.), badMuon(100., 99.,
                        13., 5.), met(new MET(40, 30)) {
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
        goodIsolatedElectron->setHcalIsolation(0.5);
        goodIsolatedElectron->setEcalIsolation(0.3);
        goodIsolatedElectron->setTrackerIsolation(0.4);
        goodIsolatedElectron->setNumberOfMissingInnerLayerHits(0);
        goodIsolatedElectron->setD0(0);
        goodIsolatedElectron->setSuperClusterEta(1);
    }

    void setUpGoodIsolatedElectron2() {
        goodIsolatedElectron2->setHcalIsolation(0.4);
        goodIsolatedElectron2->setEcalIsolation(0.3);
        goodIsolatedElectron2->setTrackerIsolation(0.4);
        goodIsolatedElectron2->setNumberOfMissingInnerLayerHits(0);
        goodIsolatedElectron2->setD0(0);
        goodIsolatedElectron2->setSuperClusterEta(1);
    }

    void setUpBadElectron() {
        badElectron->setHcalIsolation(4);
        badElectron->setEcalIsolation(44);
        badElectron->setTrackerIsolation(1);
    }

    void setUpGoodLooseElectron() {
        goodLooseElectron->setHcalIsolation(5);
        goodLooseElectron->setEcalIsolation(3);
        goodLooseElectron->setTrackerIsolation(4);
        goodLooseElectron->setSigmaIEtaIEta(VBTF_W70::MaximalDEtaIn_BarrelRegion + 2);
        goodLooseElectron->setSigmaIEtaIEta(VBTF_W95::MaximalSigmaIEtaIEta_BarrelRegion - 0.1
                * VBTF_W95::MaximalSigmaIEtaIEta_BarrelRegion);
        goodLooseElectron->setDPhiIn(VBTF_W95::MaximalDPhiIn_BarrelRegion - 0.1 * VBTF_W95::MaximalDPhiIn_BarrelRegion);
        goodLooseElectron->setDEtaIn(VBTF_W95::MaximalDEtaIn_BarrelRegion - 0.1 * VBTF_W95::MaximalDEtaIn_BarrelRegion);
        goodLooseElectron->setHadOverEm(VBTF_W95::MaximalHadOverEm_BarrelRegion - 0.1
                * VBTF_W95::MaximalHadOverEm_BarrelRegion);
        goodLooseElectron->setRobustLooseID(true);
        goodLooseElectron->setNumberOfMissingInnerLayerHits(0);
        goodLooseElectron->setD0(0);
        goodLooseElectron->setSuperClusterEta(0);
        assert(goodLooseElectron->isGood() == false);
        assert(goodLooseElectron->isLoose());
    }

    void setUpGoodIsolatedElectronFromConversion() {
        electronFromConversion->setHcalIsolation(0.5);
        electronFromConversion->setEcalIsolation(0.3);
        electronFromConversion->setTrackerIsolation(0.4);
        electronFromConversion->setNumberOfMissingInnerLayerHits(3);
    }
    void setUpGoodJet() {
        goodJet->setEMF(0.2);
        goodJet->setFHPD(0.5);
        goodJet->setN90Hits(2);
    }

    void setUpGoodBJet() {
        goodBJet->setEMF(0.2);
        goodBJet->setFHPD(0.5);
        goodBJet->setN90Hits(2);
        goodBJet->setDiscriminatorForBtagType(2.5, BJetTagger::SimpleSecondaryVertex);
    }

    void setUpGoodJetCloseToElectron() {
        goodJetCloseToElectron->setEMF(0.2);
        goodJetCloseToElectron->setFHPD(0.5);
        goodJetCloseToElectron->setN90Hits(2);
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
        ttbarEvent.setHLT_Photon15_TO20(true);
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
        goodZEvent.setHLT_Photon15_TO20(true);
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
        poorZEvent.setHLT_Photon15_TO20(true);
        poorZEvent.setPrimaryVertex(goodVertex);
    }

    void setUpDiJetEvent() {
        JetCollection jets;
        jets.push_back(goodJet);
        jets.push_back(goodJet);
        DiJetEvent.setJets(jets);
        DiJetEvent.setHLT_Photon15_TO20(false);
        DiJetEvent.setPrimaryVertex(badVertex);
    }

    void setUpDiJetEventWithConversion() {
        JetCollection jets;
        jets.push_back(goodJet);
        jets.push_back(goodJet);
        DiJetEventWithConversion.setJets(jets);
        DiJetEventWithConversion.setHLT_Photon15_TO20(false);
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
        muonEvent.setHLT_Photon15_TO20(true);
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

    void testGetMostIsolatedElectron() {
        ASSERT_EQUAL_DELTA(goodIsolatedElectron2->relativeIsolation(),
                goodZEvent.getMostIsolatedElectron()->relativeIsolation(), 0.001);
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
        goodIsolatedElectron->setSigmaIEtaIEta(VBTF_W70::MaximalDEtaIn_BarrelRegion + 2);
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

    void testMET() {
        ASSERT_EQUAL(50, ttbarEvent.getMET()->et());
    }

};

extern cute::suite make_suite_TestEvent() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfElectrons));
    s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodElectrons));
    s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodIsolatedElectrons));
    s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfJets));
    s.push_back(CUTE_SMEMFUN(TestEvent, testNumberOfGoodJets));

    s.push_back(CUTE_SMEMFUN(TestEvent, testRunNumber));
    s.push_back(CUTE_SMEMFUN(TestEvent, testEventNumber));
    s.push_back(CUTE_SMEMFUN(TestEvent, testLocalEventNumber));
    s.push_back(CUTE_SMEMFUN(TestEvent, testLumiBlock));
    s.push_back(CUTE_SMEMFUN(TestEvent, testEventWeight));

    s.push_back(CUTE_SMEMFUN(TestEvent, testGetMostIsolatedElectron));

    s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaning));
    s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaningNoGoodElectrons));
    s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaningNoElectrons));
    s.push_back(CUTE_SMEMFUN(TestEvent, testGoodJetCleaningNoGoodJets));
    s.push_back(CUTE_SMEMFUN(TestEvent, testMET));

    return s;
}
