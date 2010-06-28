#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestVariableReader.h"
static BAT::VariableReader<unsigned int> *singleObjectReader;
static BAT::VariableReader<std::vector<float>* >* multipleObjectReader;

void setUp() {
//	singleObjectReader = new BAT::VariableReader<unsigned int>();
//	multipleObjectReader = new BAT::VariableReader<std::vector<float>*>;
}

void thisIsATest() {
	setUp();
	ASSERTM("start writing tests", false);
}

cute::suite make_suite_TestVariableReader() {
	cute::suite s;
	s.push_back(CUTE(thisIsATest));
	return s;
}

