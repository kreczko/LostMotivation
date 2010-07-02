/*
 * Particle.cpp
 *
 *  Created on: 2 Jul 2010
 *      Author: kreczko
 */

#include "../../interface/RecoObjects/Particle.h"

namespace BAT {

Particle::Particle() :
	particleMass(0), fourvector(0., 0., 0., 0.) {

}

Particle::Particle(float energy, float px, float py, float pz) :
	particleMass(0), fourvector(px, py, pz, energy) {
}

Particle::~Particle() {
}

float Particle::mass() const{
	return particleMass;
}

float Particle::energy() const{
	return fourvector.Energy();
}

float Particle::et() const{
	return fourvector.Et();
}

float Particle::px() const{
	return fourvector.Px();
}

float Particle::py() const{
	return fourvector.Py();
}

float Particle::pz() const{
	return fourvector.Pz();
}

float Particle::pt() const{
	return fourvector.Pt();
}

float Particle::eta() const{
	return fourvector.Eta();
}

float Particle::massFromEnergyAndMomentum() const{
	return fourvector.M();
}

void Particle::setMass(float mass){
	particleMass = mass;
}

FourVector Particle::getFourVector() const{
	return fourvector;
}

void Particle::setFourVector(FourVector vector){
	fourvector = vector;
}

Particle & Particle::operator =(const Particle &rightHandSide) {
	if (this == &rightHandSide)
		return *this;
	fourvector = rightHandSide.getFourVector();
	particleMass = rightHandSide.mass();
	return *this;
}

const Particle Particle::operator +(const Particle &other) const{
	Particle result = *this;
	FourVector vector = result.getFourVector() + other.getFourVector();
	result.setFourVector(vector);
	result.setMass(result.massFromEnergyAndMomentum());
	return result;
}

}