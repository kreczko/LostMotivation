#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ROOTLearnTests.h"
#include "TChain.h"
#include "TBranch.h"
#include <signal.h>
#include <execinfo.h>
using namespace std;

static TChain* input;
//select two related variables
static string numberOfElectrons = "Nels";
static string energyForEachElectron = "els_energy";

static TString invalidBranch("this is not in the chain");

void setUpROOTTests() {
	input = new TChain("configurableAnalysis/eventB");
	input->Add("/storage/top/mc/summer09_7TeV/MG/HLTskim_ttjet_7TeV_v5/HLTskim_S9nTuple_ttjet_7TeV_v5_1.root");

	input->GetEntries();
	input->SetBranchStatus("*", 0);
	input->SetBranchStatus(numberOfElectrons.c_str(), 1);
	input->SetBranchStatus(energyForEachElectron.c_str(), 1);
	//	input->GetEntry(1);
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

}

cute::suite make_suite_ROOTLearnTests() {
	cute::suite s;
	s.push_back(CUTE(testInvalidTBranch));
	return s;
}

