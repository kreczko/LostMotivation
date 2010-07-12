#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestElectronReader.h"
#include "Readers/ElectronReader.h"
#include <vector>
#include "RecoObjects/Electron.h"

using namespace BAT;

static TChain* input;
static ElectronReader* electronReader;

void setUpElectronReader() {
	input = new TChain("configurableAnalysis/eventB");
	input->Add("/storage/top/mc/summer09_7TeV/MG/HLTskim_ttjet_7TeV_v5/*_1.root");
	input->GetEntries();
	input->SetBranchStatus("*", 0);
	electronReader = new ElectronReader(input);

	//	singleVariableReader = new VariableReader<unsigned int>::VariableReader(input, numberOfElectrons);
	//	multipleVariableReader = new VariableReader<std::vector<float>*>::VariableReader(input, energyForEachElectron);
	input->GetEntry(1);
}


void testReadElectronsSize() {
	setUpElectronReader();
	std::vector<Electron> electrons = electronReader->getElectrons();
	ASSERT_EQUAL(3, electrons.size());
}

void testReadFirstElectronEnergy(){
	std::vector<Electron> electrons = electronReader->getElectrons();
	Electron firstElectron = electrons.front();
	ASSERT_EQUAL_DELTA(193.008, firstElectron.energy(), 0.001);
}



cute::suite make_suite_TestElectronReader() {
	cute::suite s;
	s.push_back(CUTE(testReadElectronsSize));
	s.push_back(CUTE(testReadFirstElectronEnergy));
	return s;
}

