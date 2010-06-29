#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestVariableReader.h"
#include "Readers/VariableReader.h"
#include <vector>
#include <string>
#include <iostream>

#include "TChain.h"

using namespace BAT;
using namespace std;

static VariableReader<unsigned int>* singleVariableReader;
static VariableReader<vector<float>*>* multipleVariableReader;
static string validVariableName = "aValidVariableName";
static string invalidEmptyVariableName = "";
static TChain* input;

//select two related variables
static string numberOfElectrons = "Nels";
static string energyForEachElectron = "els_energy";

void setUpVariableReaders() {
	input = new TChain("configurableAnalysis/eventB");
	input->Add("/storage/top/mc/summer09_7TeV/MG/HLTskim_ttjet_7TeV_v5/*_1*.root");

	singleVariableReader = new VariableReader<unsigned int>::VariableReader(input, numberOfElectrons);
	multipleVariableReader = new VariableReader<std::vector<float>*>::VariableReader(input, energyForEachElectron);
	input->GetEntries();
	input->SetBranchStatus("*", 0);
	input->SetBranchStatus(numberOfElectrons.c_str(), 1);
	input->SetBranchStatus(energyForEachElectron.c_str(), 1);
	input->GetEntry(1);
}

void testIsValidVariableName() {
	ASSERT(VariableReader<>::isValidVariableName(validVariableName));
}
void testInvalidEmptyVariableName() {
	ASSERT(!VariableReader<>::isValidVariableName(invalidEmptyVariableName));
}
void testReadSingleVariable(){
	setUpVariableReaders();
	ASSERT_EQUAL(3, singleVariableReader->getVariable());
}

void testReadMultipleVariable(){
	setUpVariableReaders();
	ASSERT_EQUAL_DELTA(193.008, multipleVariableReader->getVariable()->at(0), 0.001);
	ASSERT_EQUAL(singleVariableReader->getVariable(), multipleVariableReader->getVariable()->size());
}



cute::suite make_suite_TestVariableReader() {
	cute::suite s;
	s.push_back(CUTE(testIsValidVariableName));
	s.push_back(CUTE(testInvalidEmptyVariableName));
	s.push_back(CUTE(testReadSingleVariable));
	s.push_back(CUTE(testReadMultipleVariable));
	return s;
}

