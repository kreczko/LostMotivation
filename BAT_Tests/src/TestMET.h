#include "cute_suite.h"
#include "RecoObjects/MET.h"
using namespace BAT;

struct TestMET {
private:
	MET goodMET, badMET;
public:
	TestMET() :
		goodMET(50, 40, 30), badMET(5, 4, 3) {
		MET::goodMETMinimalEt = 20;
	}

	void testStandardConstructorEt() {
		ASSERT_EQUAL(50, goodMET.et());
	}

	void testStandardConstructorEz() {
		ASSERT_EQUAL(0, goodMET.pz());
	}

	void testStandardConstructorMass() {
		ASSERT_EQUAL(0, goodMET.mass());
	}

	void testGoodMETIsGood(){
		ASSERT_EQUAL(true, goodMET.isGood());
	}

	void testBadMETNoGood(){
		ASSERT_EQUAL(false, badMET.isGood());
	}
};

extern cute::suite make_suite_TestMET() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardConstructorEt));
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardConstructorEz));
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardConstructorMass));
	s.push_back(CUTE_SMEMFUN(TestMET,testGoodMETIsGood));
	s.push_back(CUTE_SMEMFUN(TestMET,testBadMETNoGood));
	return s;
}
