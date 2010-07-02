#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestParticle.h"
#include "RecoObjects/Particle.h"

using namespace BAT;

static Particle particle1;
static Particle particle2;
static Particle particle3;
static FourVector combinedVector;

void setUpTestParticle() {
	particle1 = Particle(20., 10., 0., 0.);
	particle2 = Particle(20., -10., 0., 0.);
	combinedVector = FourVector(particle1.getFourVector() + particle2.getFourVector());
	particle3 = particle1 + particle2;
}

void testAsignOperator() {
	setUpTestParticle();
	particle3 = particle1;
	ASSERT_EQUAL(particle1.mass(), particle3.mass());
	ASSERT_EQUAL(particle1.getFourVector(), particle3.getFourVector());
}

void testPlusOperatorCorrectFourvector() {
	setUpTestParticle();
	ASSERT_EQUAL(particle3.getFourVector(), combinedVector);
}

void testPlusOperatorCorrectMass() {
	setUpTestParticle();
	ASSERT_EQUAL(combinedVector.M(), particle3.mass());
}

void testStandardConstructor() {
	Particle particle;
	ASSERT_EQUAL(0., particle.energy());
	ASSERT_EQUAL(0., particle.px());
	ASSERT_EQUAL(0., particle.py());
	ASSERT_EQUAL(0., particle.pz());
	ASSERT_EQUAL(0., particle.mass());
	ASSERT_EQUAL(0., particle.massFromEnergyAndMomentum());
}

void testFourvectorConstructor() {
	Particle particle(5., 4., 0., 0.);
	ASSERT_EQUAL(5., particle.energy());
	ASSERT_EQUAL(4., particle.px());
	ASSERT_EQUAL(0., particle.py());
	ASSERT_EQUAL(0., particle.pz());
	ASSERT_EQUAL(0., particle.mass());
	ASSERT_EQUAL(3., particle.massFromEnergyAndMomentum());
}

void testSetMass() {
	setUpTestParticle();
	ASSERT_EQUAL(0.,particle1.mass());
	particle1.setMass(200.);
	ASSERT_EQUAL(200., particle1.mass());
}

cute::suite make_suite_TestParticle() {
	cute::suite s;
	s.push_back(CUTE(testPlusOperatorCorrectFourvector));
	s.push_back(CUTE(testAsignOperator));
	s.push_back(CUTE(testPlusOperatorCorrectMass));
	s.push_back(CUTE(testStandardConstructor));
	s.push_back(CUTE(testFourvectorConstructor));
	s.push_back(CUTE(testSetMass));
	return s;
}

