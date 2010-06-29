#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include "TestEvent.h"
#include "TestVariableReader.h"


//void testStringConstructorThrowsAtIllegalName(){
//	ASSERT_THROWS(new BAT::Reader(""), std::);
//}




void runSuite(){
	cute::suite s = make_suite_TestEvent();
	s+= make_suite_TestVariableReader();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Testing BAT");
}

int main(){
    runSuite();
}



