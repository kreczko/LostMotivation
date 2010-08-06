#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "RecoObjects/Electron.h"
#include "Readers/ElectronReader.h"

using namespace BAT;

struct TestElectronReader {
private:
	boost::shared_ptr<TChain> input;
	boost::scoped_ptr<ElectronReader> electronReader;
public:
	TestElectronReader() :
		input(new TChain("configurableAnalysis/eventB")), electronReader(new ElectronReader(input)) {
		input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
		input->LoadTree(1);
		input->SetBranchStatus("*", 0);
		electronReader->initialise();
		input->GetEntry(1);
	}

	void testReadElectronsSize() {
		ElectronCollection electrons = electronReader->getElectrons();
		ASSERT_EQUAL(6, electrons.size());
	}

	void testReadFirstElectronEnergy() {
		ElectronCollection electrons = electronReader->getElectrons();
		Electron firstElectron = electrons.front();
		ASSERT_EQUAL_DELTA(38.7786, firstElectron.energy(), 0.0001);
	}

	void testReadFirstElectronIsIsolated() {
		ElectronCollection electrons = electronReader->getElectrons();
		Electron firstElectron = electrons.front();
		ASSERT(firstElectron.isIsolated());
	}

	void testReadFirstElectronIsIsolatedAfterChangingCut() {
		Electron::isolatedElectronMaximalRelativeIsolation = 0.00001;
		ElectronCollection electrons = electronReader->getElectrons();
		Electron firstElectron = electrons.front();
		ASSERT(firstElectron.isIsolated() == false);
	}
};
extern cute::suite make_suite_TestElectronReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadElectronsSize));
	s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadFirstElectronEnergy));
	s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadFirstElectronIsIsolated));
	s.push_back(CUTE_SMEMFUN(TestElectronReader, testReadFirstElectronIsIsolatedAfterChangingCut));
	return s;
}
