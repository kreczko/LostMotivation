#include "cute_suite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestPrimaryVertex.h"
#include "RecoObjects/PrimaryVertex.h"
#include <iostream>

using namespace BAT;
static PrimaryVertex goodVertex;
static PrimaryVertex badNDOFVertex;
static PrimaryVertex badZPositionVertex;
static PrimaryVertex badRhoVertex;
static PrimaryVertex fakeVertex;

void setGoodVertexCuts() {
	PrimaryVertex::goodVertexMaximalAbsoluteRho = 2.0;
	PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom = 4;
	PrimaryVertex::goodVertexMaximalAbsoluteZPosition = 15.;
}

void setGoodVertex() {
	goodVertex = PrimaryVertex();
	goodVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
	goodVertex.setFake(false);
	goodVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteRho);
	goodVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
}

void setBadNDOFVertex() {
	badNDOFVertex = PrimaryVertex();
	badNDOFVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom - 1);
	badNDOFVertex.setFake(false);
	badNDOFVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition );
	badNDOFVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
}

void setBadZPositionVertex() {
	badZPositionVertex = PrimaryVertex();
	badZPositionVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
	badZPositionVertex.setFake(false);
	badZPositionVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition );
	badZPositionVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition + 1);
}

void setBadRhoVertex() {
	badRhoVertex = PrimaryVertex();
	badRhoVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
	badRhoVertex.setFake(false);
	badRhoVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition + 2);
	badRhoVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
}

void setFakeVertex() {
	fakeVertex = PrimaryVertex();
	fakeVertex.setDegreesOfFreedom(PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom);
	fakeVertex.setFake(true);
	fakeVertex.setRho(PrimaryVertex::goodVertexMaximalAbsoluteZPosition );
	fakeVertex.setZPosition(PrimaryVertex::goodVertexMaximalAbsoluteZPosition);
}

void setUpPrimaryVertex() {
	setGoodVertexCuts();
	setGoodVertex();
	setBadNDOFVertex();
	setBadZPositionVertex();
	setBadRhoVertex();
	setFakeVertex();
}

void testSetDegreesOfFreedom() {
	setUpPrimaryVertex();
	goodVertex.setDegreesOfFreedom(111);
	ASSERT_EQUAL(111, goodVertex.ndof());
}

void testSetFake() {
	setUpPrimaryVertex();
	goodVertex.setFake(true);
	ASSERT(goodVertex.isFake());
}

void testSetPositiveRho() {
	setUpPrimaryVertex();
	goodVertex.setRho(222.);
	ASSERT_EQUAL(222., goodVertex.absoluteRho());
}

void testSetNegativeRho() {
	setUpPrimaryVertex();
	goodVertex.setRho(-222.);
	ASSERT_EQUAL(222., goodVertex.absoluteRho());
}

void testSetPositiveZ() {
	setUpPrimaryVertex();
	goodVertex.setZPosition(333.);
	ASSERT_EQUAL(333., goodVertex.absoluteZPosition());
}

void testSetNegativeZ() {
	setUpPrimaryVertex();
	goodVertex.setZPosition(-333.);
	ASSERT_EQUAL(333., goodVertex.absoluteZPosition());
}

void testGoodVertex() {
	setUpPrimaryVertex();
	ASSERT(goodVertex.isGood());
}

void testBadNDOFVertex() {
	setUpPrimaryVertex();
	ASSERT(badNDOFVertex.isGood() == false);
}

void testBadZpositionVertex() {
	setUpPrimaryVertex();
	ASSERT(badZPositionVertex.isGood() == false);
}

void testBadRhoVertex() {
	setUpPrimaryVertex();
	ASSERT(badRhoVertex.isGood() == false);
}

void testFakeVertex() {
	setUpPrimaryVertex();
	ASSERT(fakeVertex.isGood() == false);
}

cute::suite make_suite_TestPrimaryVertex() {
	cute::suite s;
	s.push_back(CUTE(testSetDegreesOfFreedom));
	s.push_back(CUTE(testSetFake));
	s.push_back(CUTE(testSetPositiveRho));
	s.push_back(CUTE(testSetNegativeRho));
	s.push_back(CUTE(testSetPositiveZ));
	s.push_back(CUTE(testSetNegativeZ));

	s.push_back(CUTE(testGoodVertex));
	s.push_back(CUTE(testBadNDOFVertex));
	s.push_back(CUTE(testBadZpositionVertex));
	s.push_back(CUTE(testBadRhoVertex));
	s.push_back(CUTE(testFakeVertex));
	return s;
}

