#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestVariableReader.h"

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s+= make_suite_TestVariableReader();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
}



