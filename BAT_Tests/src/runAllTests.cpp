#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include "TestElectron.h"
#include "TestElectronReader.h"
#include "TestEvent.h"
#include "TestEventCounter.h"
#include "TestFilter.h"
#include "TestJet.h"
#include "TestJetReader.h"
#include "TestNTupleReader.h"
#include "TestParticle.h"
#include "TestPrimaryVertex.h"
#include "TestPrimaryVertexReader.h"
#include "TestROOT.h"
#include "TestVariableReader.h"

#include "TROOT.h"

void setUpOnce() {
	gROOT->ProcessLine("#include <vector>");
}

void runSuite(){
	setUpOnce();
	cute::suite s = make_suite_ROOTLearnTests();
	s+= make_suite_TestElectron();
	s+= make_suite_TestElectronReader();
	s+= make_suite_TestEvent();
	s+= make_suite_TestEventCounter();
	s+= make_suite_TestFilter();
	s+= make_suite_TestJet();
	s+= make_suite_TestJetReader();
	s+= make_suite_TestNTupleReader();
	s+= make_suite_TestParticle();
	s+= make_suite_TestPrimaryVertex();
	s+= make_suite_TestPrimaryVertexReader();
	s+= make_suite_TestVariableReader();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Testing BristolAnalysis Tools");
}

int main(){
    runSuite();
    return 0;
}


