#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/cute_runner.h"

#include "TestElectron.h"
#include "TestElectronReader.h"
#include "TestEvent.h"
#include "TestEventCounter.h"
#include "TestFilter.h"
#include "TestJet.h"
#include "TestJetReader.h"
#include "TestMET.h"
#include "TestMETReader.h"
#include "TestMuon.h"
#include "TestMuonReader.h"
#include "TestNTupleEventReader.h"
#include "TestParticle.h"
#include "TestPrimaryVertex.h"
#include "TestPrimaryVertexReader.h"
#include "TestROOT.h"
#include "TestStringOperations.h"
#include "TestTHCollection.h"
#include "TestTopPairEventCandidate.h"
#include "TestVariableReader.h"

#include "TROOT.h"

void setUpOnce() {
    //needed to proper link vector<float> etc.
	gROOT->ProcessLine("#include <vector>");
	//prevent automatic ownership of ROOT objects
	TH1F::AddDirectory(false);
}

void runSuite(){
	setUpOnce();
	cute::suite s = make_suite_TestElectron();
	s+= make_suite_TestElectronReader();
	s+= make_suite_TestEvent();
	s+= make_suite_TestEventCounter();
	s+= make_suite_TestFilter();
	s+= make_suite_TestJet();
	s+= make_suite_TestJetReader();
	s+= make_suite_TestMET();
	s+= make_suite_TestMETReader();
	s+= make_suite_TestMuon();
	s+= make_suite_TestMuonReader();
	s+= make_suite_TestNTupleEventReader();
	s+= make_suite_TestParticle();
	s+= make_suite_TestPrimaryVertex();
	s+= make_suite_TestPrimaryVertexReader();
	s+= make_suite_ROOTLearnTests();
	s+= make_suite_TestStringOperations();
	s+= make_suite_TestTHCollection();
	s+= make_suite_TestTopPairEventCandidate();
	s+= make_suite_TestVariableReader();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Testing BristolAnalysis Tools");
}

int main(){
    runSuite();
    return 0;
}


