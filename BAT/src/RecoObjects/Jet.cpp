/*
 * Jet.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Jet.h"

namespace BAT {
float Jet::goodJetMaximalAbsoluteEta = 5;
float Jet::goodJetMinimalEt = 0;
float Jet::goodJetMinimalElectromagneticFraction = 0;
float Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy = 0;
float Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout = 5000.;

Jet::Jet() :
	Particle(), electroMagneticFraction(0.), numberOfRecHitsContaining90PercentOfTheJetEnergy(0.),
			fractionOfEnergyIntheHottestHPDReadout(0.), btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}

Jet::Jet(const Particle& particle) :
	Particle(particle), electroMagneticFraction(0.), numberOfRecHitsContaining90PercentOfTheJetEnergy(0.),
			fractionOfEnergyIntheHottestHPDReadout(0.), btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}
Jet::Jet(float energy, float px, float py, float pz) :
	Particle(energy, px, py, pz), electroMagneticFraction(0.),
			btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}

Jet::~Jet() {
}
float Jet::emf() const {
	return electroMagneticFraction;
}

float Jet::n90Hits() const {
	return numberOfRecHitsContaining90PercentOfTheJetEnergy;
}

float Jet::fHPD() const {
	return fractionOfEnergyIntheHottestHPDReadout;
}

void Jet::setEMF(float emf) {
	electroMagneticFraction = emf;
}

void Jet::setN90Hits(float n90Hits) {
	numberOfRecHitsContaining90PercentOfTheJetEnergy = n90Hits;
}

void Jet::setFHPD(float fHPD) {
	fractionOfEnergyIntheHottestHPDReadout = fHPD;
}

void Jet::setDiscriminatorForBtagType(float discriminator, BJetTagger::Algorithm type) {
	btag_discriminators[type] = discriminator;
}

bool Jet::isGoodJet() const{
	bool passesEt = et() > Jet::goodJetMinimalEt;
	bool passesEta = fabs(eta()) < Jet::goodJetMaximalAbsoluteEta;
	bool passesEMF = emf() > Jet::goodJetMinimalElectromagneticFraction;
	bool passesN90Hits = n90Hits() > Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy;
	bool passesFHPD = fHPD() < Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout;
	return passesEt && passesEta && passesEMF && passesN90Hits && passesFHPD;
}
}
