#include "cute_suite.h"
#include "TString.h"
#include "TChain.h"
#include <boost/scoped_ptr.hpp>
#include <iostream>

struct TestROOT {
private:
	TString invalidBranch;
	//select two related variables
	TString numberOfElectrons;
	TString energyForEachElectron;

	boost::scoped_ptr<TChain> input;
public:
	TestROOT() :
		invalidBranch("this is not in the chain"), numberOfElectrons("Nels"), energyForEachElectron("els_energy"),
				input(new TChain("configurableAnalysis/eventB")) {
		input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");

		input->GetEntries();
		input->SetBranchStatus("*", 0);
		input->SetBranchStatus(numberOfElectrons, 1);
		input->SetBranchStatus(energyForEachElectron, 1);
	}
	void testInvalidTBranch() {
		try {
			TBranch* br = input->GetBranch(invalidBranch);
			if (br) {
				input->SetBranchStatus(invalidBranch, 1);
			}
		} catch (...) {
			std::cout << "exception occurred" << std::endl;
		}
		ASSERT(input->GetBranch(invalidBranch) == NULL);
	}

	void testValidBranch(){
		ASSERT(input->GetBranch(numberOfElectrons) != NULL);
	}


};

extern cute::suite make_suite_ROOTLearnTests() {
		cute::suite s;
		s.push_back(CUTE_SMEMFUN(TestROOT,testInvalidTBranch));
		s.push_back(CUTE_SMEMFUN(TestROOT,testValidBranch));
		return s;
	}
