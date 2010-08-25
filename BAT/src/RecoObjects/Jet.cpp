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
	Particle(), usedAlgorithm(Jet::Calo_AntiKT_Cone05), electromagneticFraction(0.),
			numberOfRecHitsContaining90PercentOfTheJetEnergy(0.), fractionOfEnergyIntheHottestHPDReadout(0.),
			btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}

Jet::Jet(const Particle& particle) :
	Particle(particle), usedAlgorithm(Jet::Calo_AntiKT_Cone05), electromagneticFraction(0.),
			numberOfRecHitsContaining90PercentOfTheJetEnergy(0.), fractionOfEnergyIntheHottestHPDReadout(0.),
			btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}
Jet::Jet(float energy, float px, float py, float pz) :
	Particle(energy, px, py, pz), usedAlgorithm(Jet::Calo_AntiKT_Cone05), electromagneticFraction(0.), btag_discriminators(
			BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}

Jet::~Jet() {
}

Jet::Algorithm Jet::getUsedAlgorithm() const{
	return usedAlgorithm;
}

float Jet::emf() const {
	return electromagneticFraction;
}

float Jet::n90Hits() const {
	return numberOfRecHitsContaining90PercentOfTheJetEnergy;
}

float Jet::fHPD() const {
	return fractionOfEnergyIntheHottestHPDReadout;
}

void Jet::setUsedAlgorithm(Jet::Algorithm algo){
	usedAlgorithm = algo;
}
void Jet::setEMF(float emf) {
	electromagneticFraction = emf;
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

bool Jet::isGood() const {
	bool passesEt = et() > Jet::goodJetMinimalEt;
	bool passesEta = fabs(eta()) < Jet::goodJetMaximalAbsoluteEta;
	if(usedAlgorithm == ParticleFlow)
	    return passesEt && passesEta;
	bool passesEMF = emf() > Jet::goodJetMinimalElectromagneticFraction;
	bool passesN90Hits = n90Hits() > Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy;
	bool passesFHPD = fHPD() < Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout;
	return passesEt && passesEta && passesEMF && passesN90Hits && passesFHPD;
}

bool Jet::isBJetAccordingToBtagAlgorithm(BJetTagger::Algorithm btag) const {
	return BJetTagger::doesDiscriminatorPassBtagOfType(btag_discriminators.at(btag), btag);
}
}
