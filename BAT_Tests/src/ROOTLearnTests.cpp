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

void handler(int sig) throw(string){
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, 2);
  throw "A segmentation fault occured";
}

void setUpROOTTests() {
	input = new TChain("configurableAnalysis/eventB");
	input->Add("/storage/top/mc/summer09_7TeV/MG/HLTskim_ttjet_7TeV_v5/*_1*.root");

	input->GetEntries();
	input->SetBranchStatus("*", 0);
	input->SetBranchStatus(numberOfElectrons.c_str(), 1);
	input->SetBranchStatus(energyForEachElectron.c_str(), 1);
//	input->GetEntry(1);
}

void testInvalidTBranch() {
	signal(SIGSEGV, handler);
	try{
		TBranch* br = (TBranch*)input->GetListOfBranches()->FindObject(invalidBranch);
//		input->SetBranchStatus(invalidBranch.c_str(), 1);
	}
	catch(...){
		cout << "exception occured" << endl;
	}

}

cute::suite make_suite_ROOTLearnTests(){
	cute::suite s;
	s.push_back(CUTE(testInvalidTBranch));
	return s;
}



