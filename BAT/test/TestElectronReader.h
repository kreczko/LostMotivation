#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "../interface/RecoObjects/Electron.h"
#include "../interface/Readers/ElectronReader.h"
#include "../interface/Readers/NTupleEventReader.h"
#include "InputFiles.h"
#include <iostream>

using namespace BAT;

struct TestElectronReader {
private:
    boost::shared_ptr<TChain> input, input2, input3;
    boost::scoped_ptr<ElectronReader> electronReader;
    boost::scoped_ptr<VariableReader<MultiFloatPointer> > swissCrossReader;
    boost::scoped_ptr<VariableReader<unsigned int> > numberOfElectronsReader;
    ElectronCollection electrons;
    ElectronPointer firstElectron;
public:
    TestElectronReader() :
        input(new TChain(NTupleEventReader::EVENT_CHAIN)),
        input2(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
        input3(new TChain(NTupleEventReader::ADDITIONAL_CHAIN)),
        electronReader(new ElectronReader(input, input3)),
        numberOfElectronsReader(new VariableReader<unsigned int> (input, "e_num")),
        electrons(),
        firstElectron()
    {
        input->AddFriend(input2.get());
        input->AddFriend(input3.get());

        input->Add(InputFile::ttbar);
        input2->Add(InputFile::ttbar);
        input3->Add(InputFile::ttbar);

        input->LoadTree(1);
        input->SetBranchStatus("*", 0);
        input2->SetBranchStatus("*", 0);
        input3->SetBranchStatus("*", 0);
        numberOfElectronsReader->initialise();
        electronReader->initialise();
        input->GetEntry(1);
        electrons = electronReader->getElectrons();
        firstElectron = electrons.front();
    }

    void testReadElectronsSize() {
        ASSERT_EQUAL(6, electrons.size());
    }

    void testReadFirstElectronEnergy() {
        ASSERT_EQUAL_DELTA(38.7786, firstElectron->energy(), 0.0001);
    }

    void testReadFirstElectronIsIsolated() {
        ASSERT_EQUAL(true, firstElectron->isIsolated());
    }

    void testReadFirstElectronIsIsolatedAfterChangingCut() {
        Electron::isolatedElectronMaximalRelativeIsolation = 10.2;
        ASSERT_EQUAL(true, firstElectron->isIsolated());
    }

    void testFirstElectronSigmaEtaEta() {
        ASSERT_EQUAL_DELTA(0.00902937, firstElectron->sigmaIEtaIEta(), 0.0000001);
    }

    void testFirstElectronDPhiIn() {
        ASSERT_EQUAL_DELTA(0.00104798, firstElectron->dPhiIn(), 0.0000001);
    }

    void testFirstElectronDEtaIn() {
        ASSERT_EQUAL_DELTA(0.000115712, firstElectron->dEtaIn(), 0.0000001);
    }

    void testFirstElectronHadOverEm() {
        ASSERT_EQUAL_DELTA(0, firstElectron->HadOverEm(), 0.0000001);
    }

    void testFirstElectronCharge() {
        ASSERT_EQUAL(1, fabs(firstElectron->charge()));
    }

    void testFirstElectronD0() {
        ASSERT_EQUAL_DELTA(0.00159562, firstElectron->d0(), 0.00000001);
    }

    void testEcalSpikeBranchNumberOfElectrons() {
        ASSERT_EQUAL(numberOfElectronsReader->getVariable(), electrons.size());
    }

    void testShFracInnerHits() {
        ASSERT_EQUAL(1, firstElectron->shFracInnerLayer());
    }

    void testGSFTrack() {
        const TrackPointer track = firstElectron->GSFTrack();
        ASSERT_EQUAL(track->charge(), firstElectron->charge());
    }

    void testGSFTrackPhi() {
        const TrackPointer track = firstElectron->GSFTrack();
        ASSERT_EQUAL_DELTA(-2.03531, track->phi(), 0.00001);
    }

    void testGSFTrackEta() {
        const TrackPointer track = firstElectron->GSFTrack();
        ASSERT_EQUAL_DELTA(-0.0565041, track->eta(), 0.00001);
    }

    void testGSFTrackPt() {
        const TrackPointer track = firstElectron->GSFTrack();
        ASSERT_EQUAL_DELTA(40.9702, track->pt(), 0.0001);
    }

    void testGSFTrackTheta() {
        const TrackPointer track = firstElectron->GSFTrack();
        ASSERT_EQUAL_DELTA(1.62727, track->theta(), 0.00001);
    }

    void testClosestCTFTrackID() {
        ASSERT_EQUAL(9, firstElectron->closestCTFTrackID());
    }

    void testTRackd0(){
        const TrackPointer track = firstElectron->GSFTrack();
        ASSERT_EQUAL(firstElectron->d0(), track->d0());
    }
};
extern cute::suite make_suite_TestElectronReader() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadElectronsSize));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadFirstElectronEnergy));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadFirstElectronIsIsolated));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadFirstElectronIsIsolatedAfterChangingCut));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronSigmaEtaEta));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronDPhiIn));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronDEtaIn));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronHadOverEm));
//    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronIsEcalDriven));
//    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronIsTrackerDriven));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronCharge));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronD0));
//    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronSwissCross));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testEcalSpikeBranchNumberOfElectrons));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testShFracInnerHits));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testGSFTrack));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testGSFTrackPhi));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testGSFTrackEta));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testGSFTrackPt));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testGSFTrackTheta));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testClosestCTFTrackID));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testTRackd0));
    return s;
}
