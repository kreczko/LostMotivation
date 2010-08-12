/*
 * Particle.h
 *
 *  Created on: 2 Jul 2010
 *      Author: kreczko
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "TLorentzVector.h"
#include <vector>
#include <string>
#include <math.h>

typedef TLorentzVector FourVector;

namespace BAT {
class Particle;
typedef std::vector<Particle> ParticleCollection;

class Particle {
public:
	Particle();
	Particle(const Particle& particle);
	Particle(float energy, float px, float py, float pz);
	virtual ~Particle();
	const Particle operator+(const Particle &other) const;
	Particle & operator=(const Particle &rightHandSide);
	float mass() const;
	float d0() const;
	float energy() const;
	float et() const;
	float px() const;
	float py() const;
	float pz() const;
	float pt() const;
	float eta() const;
	float phi() const;
	float massFromEnergyAndMomentum() const;
	void setMass(float mass);
	void setD0(float d0);
	const FourVector& getFourVector() const;
	void setFourVector(FourVector fourvector);
	unsigned short getClosest(const ParticleCollection& particles) const;

	bool isInBarrelRegion() const;
	bool isInCrack() const;
	bool isInEndCapRegion() const;
	const char* getEtaRegion() const;
	float relativePtTo(const Particle& otherParticle) const;
	float deltaR(const Particle& otherParticle) const;
	float deltaPhi(const Particle& otherParticle) const;
	float deltaEta(const Particle& otherParticle) const;
	bool isWithinDeltaR(float deltaR, const Particle& particle) const;
	float invariantMass(const Particle& otherParticle) const;

protected:
	float particleMass;
	float distanceFromInteractionPointInMicron;
	FourVector fourvector;
};
}

#endif /* PARTICLE_H_ */
