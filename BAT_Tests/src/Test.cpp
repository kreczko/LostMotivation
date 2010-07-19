#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include "ROOTLearnTests.h"
#include "TestElectron.h"
#include "TestElectronReader.h"
#include "TestEvent.h"
#include "TestEventCounter.h"
#include "TestFilter.h"
#include "TestJet.h"
#include "TestJetReader.h"
#include "TestNTupleReader.h"
#include "TestParticle.h"
#include "TestVariableReader.h"

void runSuite(){
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
	s+= make_suite_TestVariableReader();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Testing BAT");
}

int main(){
    runSuite();
}


