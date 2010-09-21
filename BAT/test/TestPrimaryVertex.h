#include "cute/cute.h"
#include "cute/cute_suite.h"

#include "../interface/RecoObjects/PrimaryVertex.h"

using namespace BAT;

struct TestPrimaryVertex {
private:
	PrimaryVertex goodVertex;
	PrimaryVertex badNDOFVertex;
	PrimaryVertex badZPositionVertex;
	PrimaryVertex badRhoVertex;
	PrimaryVertex fakeVertex;
public:
	TestPrimaryVertex() :
		goodVertex(), badNDOFVertex(), badZPositionVertex(), badRhoVertex(), fakeVertex() {
		setGoodVertexCuts();
		setGoodVertex();
		setBadNDOFVertex();
		setBadZPositionVertex();
		setBadRhoVertex();
		setFakeVertex();
	}
private:
	void setGoodVertexCuts() {
		PrimaryVertex::goodVertexMaximalAbsoluteRho = 2.0;
		PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom = 4;
		PrimaryVertex::goodVertexMaximalAbsoluteZPosition = 15.;
	}

	void setGoodVertex() {
		goodVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
		goodVertex.setFake(false);
		goodVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteRho);
		goodVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
	}

	void setBadNDOFVertex() {
		badNDOFVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom - 1);
		badNDOFVertex.setFake(false);
		badNDOFVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
		badNDOFVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
	}

	void setBadZPositionVertex() {
		badZPositionVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
		badZPositionVertex.setFake(false);
		badZPositionVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
		badZPositionVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition + 1);
	}

	void setBadRhoVertex() {
		badRhoVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
		badRhoVertex.setFake(false);
		badRhoVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition + 2);
		badRhoVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
	}

	void setFakeVertex() {
		fakeVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
		fakeVertex.setFake(true);
		fakeVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
		fakeVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
	}
public:
	void testSetDegreesOfFreedom() {
		goodVertex.setDegreesOfFreedom(111);
		ASSERT_EQUAL(111, goodVertex.ndof());
	}

	void testSetFake() {
		ASSERT(goodVertex.isFake() == false);
		goodVertex.setFake(true);
		ASSERT(goodVertex.isFake());
	}

	void testSetPositiveRho() {
		goodVertex.setRho(222.);
		ASSERT_EQUAL(222., goodVertex.absoluteRho());
	}

	void testSetNegativeRho() {
		goodVertex.setRho(-222.);
		ASSERT_EQUAL(222., goodVertex.absoluteRho());
	}

	void testSetPositiveZ() {
		goodVertex.setZPosition(333.);
		ASSERT_EQUAL(333., goodVertex.absoluteZPosition());
	}

	void testSetNegativeZ() {
		goodVertex.setZPosition(-333.);
		ASSERT_EQUAL(333., goodVertex.absoluteZPosition());
	}

	void testGoodVertex() {
		ASSERT(goodVertex.isGood());
	}

	void testGoodVertexInRealData() {
	        ASSERT(goodVertex.isGoodInRealData());
	    }

	void testBadNDOFVertex() {
		ASSERT(badNDOFVertex.isGood() == false);
	}

	void testBadZpositionVertex() {
		ASSERT(badZPositionVertex.isGood() == false);
	}

	void testBadRhoVertex() {
		ASSERT(badRhoVertex.isGood() == false);
	}

	void testFakeVertex() {
		ASSERT(fakeVertex.isGood() == false);
	}
};

cute::suite make_suite_TestPrimaryVertex() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testSetDegreesOfFreedom));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testSetFake));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testSetPositiveRho));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testSetNegativeRho));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testSetPositiveZ));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testSetNegativeZ));

	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testGoodVertex));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testGoodVertexInRealData));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testBadNDOFVertex));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testBadZpositionVertex));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testBadRhoVertex));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertex, testFakeVertex));
	return s;
}
