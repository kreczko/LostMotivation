#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include "TestROOT.h"
#include "TChain.h"
#include "TBranch.h"
#include <boost/shared_ptr.hpp>

using namespace std;


static const TString invalidBranch("this is not in the chain");
//select two related variables
static const TString numberOfElectrons = "Nels";
static const TString energyForEachElectron = "els_energy";

static boost::shared_ptr<TChain> input;

void setUpROOTTests() {
	input = boost::shared_ptr<TChain>(new TChain("configurableAnalysis/eventB"));
	input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");

	input->GetEntries();
	input->SetBranchStatus("*", 0);
	input->SetBranchStatus(numberOfElectrons, 1);
	input->SetBranchStatus(energyForEachElectron, 1);
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
}

void testValidBranch(){
	setUpROOTTests();
	ASSERT(input->GetBranch(numberOfElectrons) != NULL);
}

extern cute::suite make_suite_ROOTLearnTests() {
	cute::suite s;
	s.push_back(CUTE(testInvalidTBranch));
	s.push_back(CUTE(testValidBranch));
	return s;
}

