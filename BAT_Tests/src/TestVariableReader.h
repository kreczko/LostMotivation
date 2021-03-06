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

struct TestVariableReader {
private:
	TString invalidEmptyVariableName, invalidNotAvailableVariableName, numberOfElectrons, energyForEachElectron;
	TChainPointer input;
	boost::scoped_ptr<VariableReader<unsigned int> > singleVariableReader;
	boost::scoped_ptr<VariableReader<MultiFloatPointer> > multipleVariableReader;
	boost::scoped_ptr<VariableReader<int> > invalidEmptyVariableVariableReader, invalidnNotAvailableVariableReader;
public:
	TestVariableReader() :
		invalidEmptyVariableName(""), invalidNotAvailableVariableName("thisIsNotInTheFile"), numberOfElectrons("Nels"),
				energyForEachElectron("els_energy"), input(new TChain("configurableAnalysis/eventB")),
				singleVariableReader(new VariableReader<unsigned int>::VariableReader(input, numberOfElectrons)),
				multipleVariableReader(new VariableReader<MultiFloatPointer>::VariableReader(input,
						energyForEachElectron)), invalidEmptyVariableVariableReader(
						new VariableReader<int>::VariableReader(input, invalidEmptyVariableName)),
				invalidnNotAvailableVariableReader(new VariableReader<int>::VariableReader(input,
						invalidNotAvailableVariableName)) {
		input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/*_1.root");
		input->SetBranchStatus("*", 0);
		singleVariableReader->initialise();
		multipleVariableReader->initialise();
		input->LoadTree(1);
		input->GetEntry(1);
	}
	void testReadSingleVariable() {
		ASSERT_EQUAL(6, singleVariableReader->getVariable());
	}

	void testReadMultipleVariable() {
		ASSERT_EQUAL_DELTA(38.7786, multipleVariableReader->getVariableAt(0), 0.0001);
		ASSERT_EQUAL(singleVariableReader->getVariable(), multipleVariableReader->size());
	}

	void testInvalidVariableThrowsException() {
		ASSERT_THROWS(invalidnNotAvailableVariableReader->initialise(), VariableNotFoundException);
	}

	void testInvalidEmptyVariableThrowsException() {
		ASSERT_THROWS(invalidEmptyVariableVariableReader->initialise(), VariableNotFoundException);
	}

};

cute::suite make_suite_TestVariableReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestVariableReader,testReadSingleVariable));
	s.push_back(CUTE_SMEMFUN(TestVariableReader,testReadMultipleVariable));
	s.push_back(CUTE_SMEMFUN(TestVariableReader,testInvalidVariableThrowsException));
	s.push_back(CUTE_SMEMFUN(TestVariableReader,testInvalidEmptyVariableThrowsException));
	return s;
}

