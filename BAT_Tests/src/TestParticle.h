#include "cute_suite.h"
#include "RecoObjects/Particle.h"
#include "DetectorGeometry.h"

using namespace BAT;

struct TestParticle {
private:
	Particle particle1;
	Particle particle2;
	Particle particle3;
	Particle particleInBarrelRegion;
	Particle particleInCrack;
	Particle particleInEndcap;
	Particle zParticle1;
	Particle zParticle2;
	FourVector combinedVector;
public:
	TestParticle() :
		particle1(20., 10., 0., 0.), particle2(20., -10., 0., 0.), particle3(particle1 + particle2),
				particleInBarrelRegion(30., 20., -20., 0.), particleInCrack(25., 0., 10., -20.), particleInEndcap(20.,
						5., 5., -20.), zParticle1(100., 79., -13., -5.), zParticle2(100., 99., 13., 5.),
				combinedVector(FourVector(particle1.getFourVector() + particle2.getFourVector())) {
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

		zParticle1 = Particle(100., 79., -13., -5.);
		zParticle2 = Particle(100., 99., 13., 5.);
	}

	void testAsignOperator() {
		particle3 = particle1;
		ASSERT_EQUAL(particle1.mass(), particle3.mass());
		ASSERT_EQUAL(particle1.getFourVector(), particle3.getFourVector());
	}

	void testPlusOperatorCorrectFourvector() {
		ASSERT_EQUAL(particle3.getFourVector(), combinedVector);
	}

	void testPlusOperatorCorrectMass() {
		ASSERT_EQUAL(combinedVector.M(), particle3.mass());
	}

	void testDeltaEta() {
		float deltaEta = fabs(particle1.eta() - particle2.eta());
		ASSERT_EQUAL(deltaEta, particle1.deltaEta(particle2));
	}

	void testDeltaPhi() {
		float deltaPhi = particle1.getFourVector().DeltaPhi(particle2.getFourVector());
		ASSERT_EQUAL(deltaPhi, particle1.deltaPhi(particle2));
	}

	void testDeltaR() {
		float deltaR = particle1.getFourVector().DeltaR(particle2.getFourVector());
		ASSERT_EQUAL(deltaR, particle1.deltaR(particle2));
	}

	void testIsWithinDR() {
		Particle particle(20., 9.99, 0., 0.);
		ASSERT(particle1.isWithinDeltaR(0.3, particle));
	}

	void testIsNotWithinDR() {
		Particle particle(20., -9.99, 0., 0.);
		ASSERT(particle1.isWithinDeltaR(0.3, particle) == false);
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
		Particle particle(particle1);
		ASSERT_EQUAL(particle1.energy(), particle.energy());
		ASSERT_EQUAL(particle1.px(), particle.px());
		ASSERT_EQUAL(particle1.py(), particle.py());
		ASSERT_EQUAL(particle1.pz(), particle.pz());
	}

	void testSetMass() {
		particle1.setMass(200.);
		ASSERT_EQUAL(200., particle1.mass());
	}

	void testDistanceFromInteractionPointAliasD0() {
		ASSERT_EQUAL(180., particle1.d0());
	}

	void testGetMassFromEnergyAndMomentumIfEquals0() {
		ASSERT(particle1.mass() != 0);
	}

	void testParticleIsInBarrelRegion() {
		ASSERT(particleInBarrelRegion.isInBarrelRegion());
		ASSERT(particleInBarrelRegion.isInEndCapRegion() == false);
		ASSERT(particleInBarrelRegion.isInCrack() == false);

	}

	void testParticleInEndcap() {
		ASSERT(particleInEndcap.isInEndCapRegion());
		ASSERT(particleInEndcap.isInCrack() == false);
		ASSERT(particleInEndcap.isInBarrelRegion() == false);
	}

	void testParticleInCrack() {
		ASSERT(particleInCrack.isInCrack());
		ASSERT(particleInCrack.isInEndCapRegion() == false);
		ASSERT(particleInCrack.isInBarrelRegion() == false);
	}

	void testGetEtaRegionCrack() {
		ASSERT(strcmp("crack", particleInCrack.getEtaRegion()) == 0);
	}

	void testGetEtaRegionBarrel() {
		ASSERT(strcmp("barrel", particleInBarrelRegion.getEtaRegion()) == 0);
	}

	void testGetEtaRegionEndcap() {
		ASSERT(strcmp("endcap", particleInEndcap.getEtaRegion()) == 0);
	}

	void testInvarianMassOfTwoParticles(){
		TLorentzVector combinedParticle(zParticle1.getFourVector() + zParticle2.getFourVector());
		ASSERT_EQUAL_DELTA(combinedParticle.M(), zParticle1.invariantMass(zParticle2), 0.0001);
	}

	void testInvarianMassOfOneParticles(){
		ASSERT_EQUAL_DELTA(2*zParticle1.mass(), zParticle1.invariantMass(zParticle1), 0.0001);
	}
};

extern cute::suite make_suite_TestParticle() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestParticle,testPlusOperatorCorrectFourvector));
	s.push_back(CUTE_SMEMFUN(TestParticle,testAsignOperator));
	s.push_back(CUTE_SMEMFUN(TestParticle,testPlusOperatorCorrectMass));
	s.push_back(CUTE_SMEMFUN(TestParticle,testStandardConstructor));
	s.push_back(CUTE_SMEMFUN(TestParticle,testFourvectorConstructor));
	s.push_back(CUTE_SMEMFUN(TestParticle,testSetMass));
	s.push_back(CUTE_SMEMFUN(TestParticle,testDistanceFromInteractionPointAliasD0));
	s.push_back(CUTE_SMEMFUN(TestParticle,testGetMassFromEnergyAndMomentumIfEquals0));
	s.push_back(CUTE_SMEMFUN(TestParticle,testParticleIsInBarrelRegion));
	s.push_back(CUTE_SMEMFUN(TestParticle,testParticleInEndcap));
	s.push_back(CUTE_SMEMFUN(TestParticle,testParticleInCrack));
	s.push_back(CUTE_SMEMFUN(TestParticle,testParticleConstructor));

	s.push_back(CUTE_SMEMFUN(TestParticle,testGetEtaRegionCrack));
	s.push_back(CUTE_SMEMFUN(TestParticle,testGetEtaRegionBarrel));
	s.push_back(CUTE_SMEMFUN(TestParticle,testGetEtaRegionEndcap));

	s.push_back(CUTE_SMEMFUN(TestParticle,testDeltaEta));
	s.push_back(CUTE_SMEMFUN(TestParticle,testDeltaPhi));
	s.push_back(CUTE_SMEMFUN(TestParticle,testDeltaR));

	s.push_back(CUTE_SMEMFUN(TestParticle,testIsWithinDR));
	s.push_back(CUTE_SMEMFUN(TestParticle,testIsNotWithinDR));

	s.push_back(CUTE_SMEMFUN(TestParticle,testInvarianMassOfTwoParticles));
	s.push_back(CUTE_SMEMFUN(TestParticle,testInvarianMassOfOneParticles));
	return s;
}
