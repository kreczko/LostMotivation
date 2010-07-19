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

Jet::Jet() :
	Particle(), electroMagneticFraction(0.), btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}

Jet::Jet(float energy, float px, float py, float pz) :
	Particle(energy, px, py, pz), electroMagneticFraction(0.),
			btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS) {

}

Jet::~Jet() {
}
float Jet::emf(){
	return electroMagneticFraction;
}

void Jet::setEMF(float emf){
	electroMagneticFraction = emf;
}

void Jet::setDiscriminatorForBtagType(float discriminator, BJetTagger::Algorithm type){
	btag_discriminators[type] = discriminator;
}
}
