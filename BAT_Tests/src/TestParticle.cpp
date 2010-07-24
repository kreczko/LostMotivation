#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestParticle.h"
#include "RecoObjects/Particle.h"
#include <assert.h>
#include "DetectorGeometry.h"
#include <iostream>
using namespace BAT;

static Particle particle1;
static Particle particle2;
static Particle particle3;
static Particle particleInBarrelRegion;
static Particle particleInCrack;
static Particle particleInEndcap;
static FourVector combinedVector;

void setUpParticles() {
	particle1 = Particle(20., 10., 0., 0.);
	particle1.setD0(180.);
	particle2 = Particle(20., -10., 0., 0.);

	combinedVector = FourVector(particle1.getFourVector() + particle2.getFourVector());
	particle3 = particle1 + particle2;

	particleInBarrelRegion = Particle(30., 20., -20., 0.);
	assert(fabs(particleInBarrelRegion.eta()) < Detector::Barrel::MaximalAbsoluteEta);

	particleInEndcap = Particle(20., 5., 5., -20.);
	assert(fabs(particleInEndcap.eta()) > Detector::EndCap::MinimalAbsoluteEta);

	particleInCrack = Particle(25., 0., 10., -20.);
	assert(fabs(particleInCrack.eta()) > Detector::Crack::MinimalAbsoluteEta);
	assert(fabs(particleInCrack.eta()) < Detector::Crack::MaximalAbsoluteEta);
}

void testAsignOperator() {
	setUpParticles();
	particle3 = particle1;
	ASSERT_EQUAL(particle1.mass(), particle3.mass());
	ASSERT_EQUAL(particle1.getFourVector(), particle3.getFourVector());
}

void testPlusOperatorCorrectFourvector() {
	setUpParticles();
	ASSERT_EQUAL(particle3.getFourVector(), combinedVector);
}

void testPlusOperatorCorrectMass() {
	setUpParticles();
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
	ASSERT_EQUAL(3., particle.massFromEnergyAndMomentum());
}

void testParticleConstructor() {
	setUpParticles();
	Particle particle(particle1);
	ASSERT_EQUAL(particle1.energy(), particle.energy());
	ASSERT_EQUAL(particle1.px(), particle.px());
	ASSERT_EQUAL(particle1.py(), particle.py());
	ASSERT_EQUAL(particle1.pz(), particle.pz());
}

void testSetMass() {
	setUpParticles();
	particle1.setMass(200.);
	ASSERT_EQUAL(200., particle1.mass());
}

void testDistanceFromInteractionPointAliasD0() {
	setUpParticles();
	ASSERT_EQUAL(180., particle1.d0());
}

void testGetMassFromEnergyAndMomentumIfEquals0() {
	setUpParticles();
	ASSERT(particle1.mass() != 0);
}

void testParticleIsInBarrelRegion() {
	setUpParticles();
	ASSERT(particleInBarrelRegion.isInBarrelRegion());
	ASSERT(particleInBarrelRegion.isInEndCapRegion() == false);
	ASSERT(particleInBarrelRegion.isInCrack() == false);

}

void testParticleInEndcap() {
	setUpParticles();
	ASSERT(particleInEndcap.isInEndCapRegion());
	ASSERT(particleInEndcap.isInCrack() == false);
	ASSERT(particleInEndcap.isInBarrelRegion() == false);
}

void testParticleInCrack() {
	setUpParticles();
	ASSERT(particleInCrack.isInCrack());
	ASSERT(particleInCrack.isInEndCapRegion() == false);
	ASSERT(particleInCrack.isInBarrelRegion() == false);
}

void testGetEtaRegionCrack(){
	setUpParticles();
	ASSERT(strcmp("crack", particleInCrack.getEtaRegion()) == 0);
}

void testGetEtaRegionBarrel(){
	setUpParticles();
	ASSERT(strcmp("barrel", particleInBarrelRegion.getEtaRegion()) == 0);
}

void testGetEtaRegionEndcap(){
	setUpParticles();
	ASSERT(strcmp("endcap", particleInEndcap.getEtaRegion()) == 0);
}

cute::suite make_suite_TestParticle() {
	cute::suite s;
	s.push_back(CUTE(testPlusOperatorCorrectFourvector));
	s.push_back(CUTE(testAsignOperator));
	s.push_back(CUTE(testPlusOperatorCorrectMass));
	s.push_back(CUTE(testStandardConstructor));
	s.push_back(CUTE(testFourvectorConstructor));
	s.push_back(CUTE(testSetMass));
	s.push_back(CUTE(testDistanceFromInteractionPointAliasD0));
	s.push_back(CUTE(testGetMassFromEnergyAndMomentumIfEquals0));
	s.push_back(CUTE(testParticleIsInBarrelRegion));
	s.push_back(CUTE(testParticleInEndcap));
	s.push_back(CUTE(testParticleInCrack));
	s.push_back(CUTE(testParticleConstructor));

	s.push_back(CUTE(testGetEtaRegionCrack));
	s.push_back(CUTE(testGetEtaRegionBarrel));
	s.push_back(CUTE(testGetEtaRegionEndcap));
	return s;
}

