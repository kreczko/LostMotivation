/*
 * Jet.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Jet.h"

namespace BAT {
float Jet::goodJetMaximalAbsoluteEta = 2.4;
float Jet::goodJetMinimalPt = 30.;
float Jet::goodJetMinimalElectromagneticFraction = 0.01;
float Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy = 1;
float Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout = 0.98;

Jet::Jet() :
    Particle(), usedAlgorithm(Jet::Calo_AntiKT_Cone05), electromagneticFraction(0.),
            numberOfRecHitsContaining90PercentOfTheJetEnergy(0.), fractionOfEnergyIntheHottestHPDReadout(0.),
            btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS), btagInData(-1000), numberOfDaughters(0),
            chargedEmEnergyFraction(1), neutralHadronEnergyFraction(1), neutralEmEnergyFraction(1),
            chargedHadronEnergyFraction(1), chargedMultiplicity(0) {

}

Jet::Jet(const Particle& particle) :
    Particle(particle), usedAlgorithm(Jet::Calo_AntiKT_Cone05), electromagneticFraction(0.),
            numberOfRecHitsContaining90PercentOfTheJetEnergy(0.), fractionOfEnergyIntheHottestHPDReadout(0.),
            btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS), btagInData(-1000), numberOfDaughters(0),
            chargedEmEnergyFraction(1), neutralHadronEnergyFraction(1), neutralEmEnergyFraction(1),
            chargedHadronEnergyFraction(1), chargedMultiplicity(0) {

}
Jet::Jet(float energy, float px, float py, float pz) :
    Particle(energy, px, py, pz), usedAlgorithm(Jet::Calo_AntiKT_Cone05), electromagneticFraction(0.),
            btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS), btagInData(-1000), numberOfDaughters(0),
            chargedEmEnergyFraction(1), neutralHadronEnergyFraction(1), neutralEmEnergyFraction(1),
            chargedHadronEnergyFraction(1), chargedMultiplicity(0) {

}

Jet::~Jet() {
}

Jet::Algorithm Jet::getUsedAlgorithm() const {
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

float Jet::NOD() const {
    return numberOfDaughters;
}

float Jet::CEF() const {
    return chargedEmEnergyFraction;
}

float Jet::NHF() const {
    return neutralHadronEnergyFraction;
}

float Jet::NEF() const {
    return neutralEmEnergyFraction;
}

float Jet::CHF() const {
    return chargedHadronEnergyFraction;
}

float Jet::NCH() const {
    return chargedMultiplicity;
}

void Jet::setUsedAlgorithm(Jet::Algorithm algo) {
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

void Jet::setBtagForData(float btag) {
    btagInData = btag;
}

void Jet::setNOD(float nod) {
    numberOfDaughters = nod;
}
void Jet::setCEF(float cef) {
    chargedEmEnergyFraction = cef;
}
void Jet::setNHF(float nhf) {
    neutralHadronEnergyFraction = nhf;
}
void Jet::setNEF(float nef) {
    neutralEmEnergyFraction = nef;
}
void Jet::setCHF(float chf) {
    chargedHadronEnergyFraction = chf;
}
void Jet::setNCH(float nch) {
    chargedMultiplicity = nch;
}

bool Jet::isGood() const {
    bool passesPt = pt() > Jet::goodJetMinimalPt;
    bool passesEta = fabs(eta()) < Jet::goodJetMaximalAbsoluteEta;
    if (usedAlgorithm == ParticleFlow){
        bool passNOD = NOD() > 1;
        bool passCEF = CEF() < 0.99;
        bool passNHF = NHF() < 0.99;
        bool passNEF = NEF() < 0.99;
        bool passCHF = true;
        bool passNCH = true;
        if(fabs(eta()) < 2.4){
            passCHF = CHF() > 0;
            passNCH = NCH() > 0;
        }
        return passesPt && passesEta && passNOD && passCEF && passNHF && passNEF && passCHF && passNCH;
    }

    bool passesEMF = emf() > Jet::goodJetMinimalElectromagneticFraction;
    bool passesN90Hits = n90Hits() > Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy;
    bool passesFHPD = fHPD() < Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout;
    return passesPt && passesEta && passesEMF && passesN90Hits && passesFHPD;
}

bool Jet::isBJetAccordingToBtagAlgorithm(BJetTagger::Algorithm btag) const {
    return BJetTagger::doesDiscriminatorPassBtagOfType(btag_discriminators.at(btag), btag);
}

bool Jet::isBJetInData() const {
    return BJetTagger::doesDiscriminatorPassBtagOfType(btagInData, BJetTagger::SimpleSecondaryVertex);
}
}
