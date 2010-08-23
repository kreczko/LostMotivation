#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>

#include "../interface/Event.h"
#include "../interface/Filter.h"
#include "../interface/TopPairEventCandidate.h"
#include "../interface/Selection.h"

using namespace BAT;

struct TestTopPairEventCandidate {
    TopPairEventCandidate ttbarEvent, goodZEvent, poorZEvent, DiJetEvent, DiJetEventWithConversion, muonEvent;
    TopPairEventCandidate emptyEvent;
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

    TestTopPairEventCandidate() :
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
        goodIsolatedElectron->setSuperClusterEta(0);
    }

    void setUpGoodIsolatedElectron2() {
        goodIsolatedElectron2->setHcalIsolation(0.4);
        goodIsolatedElectron2->setEcalIsolation(0.3);
        goodIsolatedElectron2->setTrackerIsolation(0.4);
        goodIsolatedElectron2->setNumberOfMissingInnerLayerHits(0);
        goodIsolatedElectron2->setD0(0);
        goodIsolatedElectron2->setSuperClusterEta(0);
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
        goodLooseElectron->setSigmaIEtaIEta(VBTF_W95::MaximalSigmaIEtaIEta_BarrelRegion - 0.1
                * VBTF_W95::MaximalSigmaIEtaIEta_BarrelRegion);
        goodLooseElectron->setDPhiIn(VBTF_W95::MaximalDPhiIn_BarrelRegion - 0.1 * VBTF_W95::MaximalDPhiIn_BarrelRegion);
        goodLooseElectron->setDEtaIn(VBTF_W95::MaximalDEtaIn_BarrelRegion - 0.1 * VBTF_W95::MaximalDEtaIn_BarrelRegion);
        goodLooseElectron->setHadOverEm(VBTF_W95::MaximalHadOverEm_BarrelRegion - 0.1
                * VBTF_W95::MaximalHadOverEm_BarrelRegion);
        goodLooseElectron->setRobustLooseID(true);
        goodLooseElectron->setNumberOfMissingInnerLayerHits(0);
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
        ttbarEvent.setHLT_Emulated_Photon15(true);
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
        goodZEvent.setHLT_Emulated_Photon15(true);
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
        poorZEvent.setHLT_Emulated_Photon15(true);
        poorZEvent.setPrimaryVertex(goodVertex);
    }

    void setUpDiJetEvent() {
        JetCollection jets;
        jets.push_back(goodJet);
        jets.push_back(goodJet);
        DiJetEvent.setJets(jets);
        DiJetEvent.setHLT_Emulated_Photon15(false);
        DiJetEvent.setPrimaryVertex(badVertex);
    }

    void setUpDiJetEventWithConversion() {
        JetCollection jets;
        jets.push_back(goodJet);
        jets.push_back(goodJet);
        DiJetEventWithConversion.setJets(jets);
        DiJetEventWithConversion.setHLT_Emulated_Photon15(false);
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
        muonEvent.setHLT_Emulated_Photon15(true);
        muonEvent.setPrimaryVertex(goodVertex);
        MuonCollection muons;
        muons.push_back(goodIsolatedMuon);
        muonEvent.setMuons(muons);
    }

public:
    void testEventConstructor() {
        TopPairEventCandidate candidate = TopPairEventCandidate(ttbarEvent);
        ASSERT_EQUAL(2, candidate.getElectrons().size());
        ASSERT_EQUAL(1, candidate.getGoodIsolatedElectrons().size());
        ASSERT_EQUAL(5, candidate.getJets().size());
        ASSERT_EQUAL(4, candidate.getGoodJets().size());
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

    void testComputeNeutrinoPzsWithoutMETThrowsExpeption() {
        TopPairEventCandidate cand = TopPairEventCandidate();
        ElectronPointer electron(new Electron(40, -40, 0, 0));
        electron->setHcalIsolation(0);
        electron->setEcalIsolation(0);
        electron->setTrackerIsolation(0);
        electron->setNumberOfMissingInnerLayerHits(0);
        ElectronCollection eCollection;
        eCollection.push_back(electron);
        cand.setElectrons(eCollection);
        ASSERT_THROWS(cand.computeNeutrinoPz(),ReconstructionException);
    }

    void testComputeNeutrinoPzsIsolatedElectronThrowsExpeption() {
        TopPairEventCandidate cand = TopPairEventCandidate();
        ElectronPointer electron(new Electron(40, -40, 0, 0));
        electron->setHcalIsolation(50);
        electron->setEcalIsolation(50);
        electron->setTrackerIsolation(50);
        electron->setNumberOfMissingInnerLayerHits(0);
        ElectronCollection eCollection;
        eCollection.push_back(electron);
        cand.setElectrons(eCollection);
        ASSERT_THROWS(cand.computeNeutrinoPz(),ReconstructionException);
    }

    void testComputeNeutrinoPzs() {
        METPointer met(new MET(40, 0));
        ElectronPointer electron(new Electron(40, -40, 0, 0));
        electron->setHcalIsolation(0);
        electron->setEcalIsolation(0);
        electron->setTrackerIsolation(0);
        electron->setNumberOfMissingInnerLayerHits(0);
        electron->setD0(0);
        electron->setSuperClusterEta(0);
        ElectronCollection eCollection;
        eCollection.push_back(electron);
        TopPairEventCandidate cand = TopPairEventCandidate();
        cand.setMET(met);
        cand.setElectrons(eCollection);
        ASSERT_EQUAL(sqrt(80*80-80.389*80.389), cand.computeNeutrinoPz().at(0));
        ASSERT_EQUAL(sqrt(80*80-80.389*80.389), cand.computeNeutrinoPz().at(1));
    }

    void testReconstructTopEventUsingChiWithNotEnoughJetsThrowsException() {
        METPointer met(new MET(40, 0));
        ElectronPointer electron(new Electron(40, -40, 0, 0));
        electron->setHcalIsolation(0);
        electron->setEcalIsolation(0);
        electron->setTrackerIsolation(0);
        electron->setNumberOfMissingInnerLayerHits(0);
        ElectronCollection eCollection;
        eCollection.push_back(electron);
        TopPairEventCandidate cand = TopPairEventCandidate();
        cand.setMET(met);
        cand.setElectrons(eCollection);
        ASSERT_THROWS(cand.reconstructUsingChi2(),ReconstructionException);
    }

};

extern cute::suite make_suite_TestTopPairEventCandidate() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventConstructor));

    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testPassesHLT));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testDoesNotPassHLT));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testDoesHaveGoodPV));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testDoesntHaveGoodPV));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasOnlyOneGoodIsolatedElectron));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasNotOnlyOneGoodIsolatedElectron));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testIsolatedElectronNotFromConversion));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testIsolatedElectronFromConversion));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testNoElectronInEventReturnsFalse));

    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasAtLeastOneGoodJet));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasNoGoodJets));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasAtLeastTwoGoodjet));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasNoTwoGoodJets));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasAtLeastThreeGoodJets));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasNoThreeGoodJets));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasAtFourThreeGoodJets));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testHasNoFourThreeGoodJets));

    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testTTbarIsNotAZBosonEvent));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testGoodZIsAZBosonEvent));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testPoorZIsAZBosonEvent));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testDiJetIsNotAZBosonEvent));

    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testTTbarEventPassesMuonVeto));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testMuonEventDoesnPassMuonVeto));

    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses1stStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses2ndStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses3ndStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses4thStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses5thStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses6thStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testEventPasses7thStep));

    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testTTbarEventPassesNStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testPoorZEventPassesUpToStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testPoorZEventDoesntPassUpToStep));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testPassesFullTTbarSelection));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testFailsFullTTbarSelection));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testComputeNeutrinoPzsWithoutMETThrowsExpeption));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testComputeNeutrinoPzsIsolatedElectronThrowsExpeption));
    s.push_back(CUTE_SMEMFUN(TestTopPairEventCandidate, testComputeNeutrinoPzs));
    s.push_back(
            CUTE_SMEMFUN(TestTopPairEventCandidate, testReconstructTopEventUsingChiWithNotEnoughJetsThrowsException));

    return s;
}
