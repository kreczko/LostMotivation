#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestVariableReader.h"
#include "Readers/VariableReader.h"
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"

using namespace ROOT;
using namespace BAT;
using namespace std;

static VariableReader<unsigned int>* singleVariableReader;
static VariableReader<vector<float>*>* multipleVariableReader;
static const TString invalidEmptyVariableName("");
static const TString invalidNotAvailableVariableName("thisIsNotInTheFile");
static boost::shared_ptr<TChain> input;
static VariableReader<int>* invalidEmptyVariableVariableReader;
static VariableReader<int>* invalidnNotAvailableVariableReader;
//select two related variables
static const TString numberOfElectrons("Nels");
static const TString energyForEachElectron("els_energy");

void setUpOnce() {
	gROOT->ProcessLine("#include <vector>");
}

void setUpVariableReaders() {
	input = boost::shared_ptr<TChain>(new TChain("configurableAnalysis/eventB"));
	input->Add("/storage/top/mc/summer09_7TeV/MG/HLTskim_ttjet_7TeV_v5/*_1.root");
	input->GetEntries();
	input->SetBranchStatus("*", 0);
	singleVariableReader = new VariableReader<unsigned int>::VariableReader(input, numberOfElectrons);
	multipleVariableReader = new VariableReader<std::vector<float>*>::VariableReader(input, energyForEachElectron);
	invalidEmptyVariableVariableReader = new VariableReader<int>::VariableReader(input, invalidEmptyVariableName);
	invalidnNotAvailableVariableReader
			= new VariableReader<int>::VariableReader(input, invalidNotAvailableVariableName);
	singleVariableReader->initialise();
	multipleVariableReader->initialise();
	input->GetEntry(1);
}

void testReadSingleVariable() {
	setUpVariableReaders();
	ASSERT_EQUAL(3, singleVariableReader->getVariable());
}

void testReadMultipleVariable() {
	setUpVariableReaders();
	ASSERT_EQUAL_DELTA(193.008, multipleVariableReader->getVariable()->at(0), 0.001);
	ASSERT_EQUAL(singleVariableReader->getVariable(), multipleVariableReader->getVariable()->size());
}

void testInvalidVariableThrowsException() {
	setUpVariableReaders();
	ASSERT_THROWS(invalidnNotAvailableVariableReader->initialise(), VariableNotFoundException);
}

void testInvalidEmptyVariableThrowsException() {
	setUpVariableReaders();
	ASSERT_THROWS(invalidEmptyVariableVariableReader->initialise(), VariableNotFoundException);
}

cute::suite make_suite_TestVariableReader() {
	setUpOnce();
	cute::suite s;
	s.push_back(CUTE(testReadSingleVariable));
	s.push_back(CUTE(testReadMultipleVariable));
	s.push_back(CUTE(testInvalidVariableThrowsException));
	s.push_back(CUTE(testInvalidEmptyVariableThrowsException));
	return s;
}

