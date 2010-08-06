#include "cute/cute.h"
#include "cute/cute_suite.h"

#include "RecoObjects/MET.h"

using namespace BAT;

struct TestMET {
private:
	MET goodMET, badMET;
public:
	TestMET() :
		goodMET(40, 30), badMET(4, 3) {
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

	void testSetAlgorithm(){
		goodMET.setUsedAlgorithm(MET::ParticleFlowMET);
		ASSERT_EQUAL(MET::ParticleFlowMET, goodMET.getUsedAlgorithm());
	}

	void testStandardAlgorithm(){
		ASSERT_EQUAL(MET::DEFAULT, goodMET.getUsedAlgorithm());
	}
};

extern cute::suite make_suite_TestMET() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardConstructorEt));
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardConstructorEz));
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardConstructorMass));
	s.push_back(CUTE_SMEMFUN(TestMET,testGoodMETIsGood));
	s.push_back(CUTE_SMEMFUN(TestMET,testBadMETNoGood));
	s.push_back(CUTE_SMEMFUN(TestMET,testSetAlgorithm));
	s.push_back(CUTE_SMEMFUN(TestMET,testStandardAlgorithm));
	return s;
}
