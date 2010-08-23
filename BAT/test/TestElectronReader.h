#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "../interface/RecoObjects/Electron.h"
#include "../interface/Readers/ElectronReader.h"
#include "../interface/Readers/NTupleEventReader.h"
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
        input(new TChain(NTupleEventReader::EVENT_CHAIN)), input2(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
                input3(new TChain(NTupleEventReader::ECAL_SPIKE_CLEANING_CHAIN)), electronReader(new ElectronReader(
                        input)), swissCrossReader(new VariableReader<MultiFloatPointer> (input, "e_swissCross")),
                numberOfElectronsReader(new VariableReader<unsigned int> (input, "e_num")), electrons(),
                firstElectron() {
        input->AddFriend(input2.get());
        input->AddFriend(input3.get());

        input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
        input2->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
        input3->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");

        input->LoadTree(1);
        input->SetBranchStatus("*", 0);
        input2->SetBranchStatus("*", 0);
        input3->SetBranchStatus("*", 0);
        swissCrossReader->initialise();
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
        ASSERT(firstElectron->isIsolated());
    }

    void testReadFirstElectronIsIsolatedAfterChangingCut() {
        Electron::isolatedElectronMaximalRelativeIsolation = 0.00001;
        ASSERT(firstElectron->isIsolated() == false);
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
        ASSERT_EQUAL_DELTA(0., firstElectron->HadOverEm(), 0.0000001);
    }

    void testFirstElectronIsEcalDriven() {
        ASSERT_EQUAL(true, firstElectron->isEcalDriven());
    }

    void testFirstElectronIsTrackerDriven() {
        ASSERT_EQUAL(true, firstElectron->isTrackerDriven());
    }

    void testFirstElectronCharge() {
        ASSERT_EQUAL(1, fabs(firstElectron->charge()));
    }

    void testFirstElectronD0() {
        ASSERT_EQUAL_DELTA(-0.000193891, firstElectron->d0(), 0.000000001);
    }

    void testFirstElectronSwissCross() {
        ASSERT_EQUAL_DELTA(0.706935, firstElectron->swissCross(), 0.000001);
    }

    void testEcalSpikeBranchNumberOfElectrons() {
        ASSERT_EQUAL(numberOfElectronsReader->getVariable(), electrons.size());
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
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronIsEcalDriven));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronIsTrackerDriven));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronCharge));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronD0));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testFirstElectronSwissCross));
    s.push_back(CUTE_SMEMFUN(TestElectronReader, testEcalSpikeBranchNumberOfElectrons));
    return s;
}
