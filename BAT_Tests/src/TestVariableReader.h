#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Readers/VariableReader.h"
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"


using namespace ROOT;
using namespace BAT;
using namespace std;

static const TString invalidEmptyVariableName("");
static const TString invalidNotAvailableVariableName("thisIsNotInTheFile");
//select two related variables
static const TString numberOfElectrons("Nels");
static const TString energyForEachElectron("els_energy");

static boost::shared_ptr<TChain> input;

static VariableReader<unsigned int>* singleVariableReader;
static VariableReader<vector<float>*>* multipleVariableReader;
static VariableReader<int>* invalidEmptyVariableVariableReader;
static VariableReader<int>* invalidnNotAvailableVariableReader;


void setUpVariableReaders() {
	input = boost::shared_ptr<TChain>(new TChain("configurableAnalysis/eventB"));
	input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/*_1.root");
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

void tearDownVariableReaders(){
	delete singleVariableReader;
	delete multipleVariableReader;
	delete invalidEmptyVariableVariableReader;
	delete invalidnNotAvailableVariableReader;
}

void testReadSingleVariable() {
	setUpVariableReaders();
	ASSERT_EQUAL(6, singleVariableReader->getVariable());
	tearDownVariableReaders();
}

void testReadMultipleVariable() {
	setUpVariableReaders();
	ASSERT_EQUAL_DELTA(38.7786, multipleVariableReader->getVariableAt(0), 0.0001);
	ASSERT_EQUAL(singleVariableReader->getVariable(), multipleVariableReader->size());
	tearDownVariableReaders();
}

void testInvalidVariableThrowsException() {
	setUpVariableReaders();
	ASSERT_THROWS(invalidnNotAvailableVariableReader->initialise(), VariableNotFoundException);
	tearDownVariableReaders();
}

void testInvalidEmptyVariableThrowsException() {
	setUpVariableReaders();
	ASSERT_THROWS(invalidEmptyVariableVariableReader->initialise(), VariableNotFoundException);
	tearDownVariableReaders();
}

cute::suite make_suite_TestVariableReader() {
//	setUpOnce();
	cute::suite s;
	s.push_back(CUTE(testReadSingleVariable));
	s.push_back(CUTE(testReadMultipleVariable));
	s.push_back(CUTE(testInvalidVariableThrowsException));
	s.push_back(CUTE(testInvalidEmptyVariableThrowsException));
	return s;
}

