/*
 * Particle.h
 *
 *  Created on: 2 Jul 2010
 *      Author: kreczko
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "TLorentzVector.h"
//#include "BeamSpot.h"
#include <vector>
#include <string>

typedef TLorentzVector FourVector;

namespace BAT {

class Particle {
public:
	Particle();
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
	FourVector getFourVector() const;
	void setFourVector(FourVector fourvector);
//	float computeD0WRTBeamSpot(const BeamSpot & spot);
	unsigned int getClosest(const std::vector<Particle>& particles) const;

	bool isInBarrelRegion() const;
	bool isInCrack() const;
	bool isInEndCapRegion() const;
	std::string getEtaRegion() const;

protected:
	float particleMass;
	float distanceFromInteractionPointInMicron;
	FourVector fourvector;
};

}

#endif /* PARTICLE_H_ */
