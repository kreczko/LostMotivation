#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ROOTLearnTests.h"
#include "TChain.h"
#include "TBranch.h"
using namespace std;

static TChain* input;
//select two related variables
static TString numberOfElectrons = "Nels";
static TString energyForEachElectron = "els_energy";

static TString invalidBranch("this is not in the chain");

void setUpROOTTests() {
	input = new TChain("configurableAnalysis/eventB");
	input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");

	input->GetEntries();
	input->SetBranchStatus("*", 0);
	input->SetBranchStatus(numberOfElectrons, 1);
	input->SetBranchStatus(energyForEachElectron, 1);
}

void tearDownROOTTests(){
	delete input;
}

void testInvalidTBranch() {
	setUpROOTTests();
	try {
		TBranch* br = input->GetBranch(invalidBranch);
		if (br) {
			input->SetBranchStatus(invalidBranch, 1);
		}
	} catch (...) {
		cout << "exception occurred" << endl;
	}
	ASSERT(input->GetBranch(invalidBranch) == NULL);
	tearDownROOTTests();
}

void testValidBranch(){
	setUpROOTTests();
	ASSERT(input->GetBranch(numberOfElectrons) != NULL);
	tearDownROOTTests();
}

cute::suite make_suite_ROOTLearnTests() {
	cute::suite s;
	s.push_back(CUTE(testInvalidTBranch));
	s.push_back(CUTE(testValidBranch));
	return s;
}

