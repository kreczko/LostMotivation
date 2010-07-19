#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestElectronReader.h"
#include "Readers/ElectronReader.h"
#include <vector>
#include "RecoObjects/Electron.h"
#include <boost/shared_ptr.hpp>
using namespace BAT;

static boost::shared_ptr<TChain> input;
static ElectronReader* electronReader;

void setUpElectronReader() {
	input = boost::shared_ptr<TChain>(new TChain("configurableAnalysis/eventB"));
	input->Add("/storage/top/mc/spring10_7TeV_v4/MG/e20skim_ttjet/*_1.root");
	input->GetEntries();
	input->SetBranchStatus("*", 0);
	electronReader = new ElectronReader(input);
	electronReader->initialise();
	input->GetEntry(1);
}


void testReadElectronsSize() {
	setUpElectronReader();
	std::vector<Electron> electrons = electronReader->getElectrons();
	ASSERT_EQUAL(6, electrons.size());
}

void testReadFirstElectronEnergy(){
	std::vector<Electron> electrons = electronReader->getElectrons();
	Electron firstElectron = electrons.front();
	ASSERT_EQUAL_DELTA(38.7786, firstElectron.energy(), 0.0001);
}



cute::suite make_suite_TestElectronReader() {
	cute::suite s;
	s.push_back(CUTE(testReadElectronsSize));
	s.push_back(CUTE(testReadFirstElectronEnergy));
	return s;
}

