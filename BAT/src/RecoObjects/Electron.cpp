/*
 * Electron.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Electron.h"
#include <assert.h>
#include "../../interface/DetectorGeometry.h"
#include "../../interface/VBTF_ElectronID.h"

namespace BAT {
const boost::array<std::string, Electron::NUMBER_OF_ELECTRONIDS> Electron::ElectronIDNames = { {
        "loose ID",
        "tight ID",
        "robust loose ID",
        "robust tight ID",
        "VBTF working point 70%",
        "High Energy" } };
float Electron::goodElectronMinimalEt = 9999;
float Electron::goodElectronMaximalAbsoluteEta = 0;
float Electron::goodElectronMaximalDistanceFromInteractionPoint = 0;
float Electron::goodElectronMaximalSwissCross = 0;

float Electron::looseElectronMinimalEt = 9999;
float Electron::looseElectronMaximalAbsoluteEta = 0;
float Electron::looseIsolatedElectronMaximalRelativeIsolation = -1;

float Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion = -1;

float Electron::isolatedElectronMaximalRelativeIsolation = -1;

Electron::Electron() :
    Particle(), usedAlgorithm(Electron::Calo), robustLooseId(false), robustTightId(false), superCluser_Eta(123456789),
            ecal_Isolation(123456789), hcal_Isolation(123456789), tracker_Isolation(123456789), innerLayerMissingHits(
                    123456789), sigma_IEtaIEta(0), dPhi_In(0), dEta_In(0), hadOverEm(0), ecalDriven(false),
            trackerDriven(false), swissCross(1) {
}

Electron::Electron(const Electron& other) :
    Particle((Particle) other), usedAlgorithm(other.getUsedAlgorithm()), robustLooseId(other.RobustLooseID()),
            robustTightId(other.RobustLooseID()), superCluser_Eta(other.superClusterEta()), ecal_Isolation(
                    other.ecalIsolation()), hcal_Isolation(other.hcalIsolation()), tracker_Isolation(
                    other.trackerIsolation()), innerLayerMissingHits(other.innerLayerMissingHits), sigma_IEtaIEta(
                    other.sigma_IEtaIEta), dPhi_In(other.dPhi_In), dEta_In(other.dEta_In), hadOverEm(other.hadOverEm),
            ecalDriven(other.ecalDriven), trackerDriven(other.trackerDriven), swissCross(other.swissCross) {

}

Electron::Electron(float energy, float px, float py, float pz) :
    Particle(energy, px, py, pz), usedAlgorithm(Electron::Calo), robustLooseId(false), robustTightId(false),
            superCluser_Eta(123456789), ecal_Isolation(123456789), hcal_Isolation(123456789), tracker_Isolation(
                    123456789), innerLayerMissingHits(123456789), sigma_IEtaIEta(0), dPhi_In(0), dEta_In(0), hadOverEm(
                    0), ecalDriven(false), trackerDriven(false), swissCross(1) {
}

Electron::~Electron() {
}

float Electron::superClusterEta() const {
    return superCluser_Eta;
}
float Electron::ecalIsolation() const {
    return ecal_Isolation;
}

float Electron::hcalIsolation() const {
    return hcal_Isolation;
}

float Electron::trackerIsolation() const {
    return tracker_Isolation;
}

float Electron::relativeIsolation() const {
    return (ecal_Isolation + hcal_Isolation + tracker_Isolation) / this->et();
}

bool Electron::isIsolated() const {
    return this->relativeIsolation() < Electron::isolatedElectronMaximalRelativeIsolation;
}

bool Electron::isHEEPIsolated() const {
    if (isInBarrelRegion())
        return (ecal_Isolation + hcal_Isolation) < 2 + 0.03 * et();
    else if (isInEndCapRegion() && et() < 50)
        return (ecal_Isolation + hcal_Isolation) < 2.5;
    else if (isInEndCapRegion() && et() >= 50)
        return (ecal_Isolation + hcal_Isolation) < 2.5 + 0.03 * (et() - 50);
    else
        return false;
}

Electron::Algorithm Electron::getUsedAlgorithm() const {
    return usedAlgorithm;
}

void Electron::setEcalIsolation(float isolation) {
    ecal_Isolation = isolation;
}

void Electron::setHcalIsolation(float isolation) {
    hcal_Isolation = isolation;
}

void Electron::setTrackerIsolation(float isolation) {
    tracker_Isolation = isolation;
}

void Electron::setSuperClusterEta(float eta) {
    superCluser_Eta = eta;
}

void Electron::setRobustLooseID(bool id) {
    robustLooseId = id;
}

void Electron::setRobustTightID(bool id) {
    robustTightId = id;
}

void Electron::setSigmaIEtaIEta(float sigma) {
    sigma_IEtaIEta = sigma;
}

void Electron::setDPhiIn(float dphi) {
    dPhi_In = dphi;
}

void Electron::setDEtaIn(float deta) {
    dEta_In = deta;
}

void Electron::setHadOverEm(float HoverE) {
    hadOverEm = HoverE;
}

void Electron::setIsEcalDriven(bool eDriven) {
    ecalDriven = eDriven;
}

void Electron::setIsTrackerDriven(bool tDriven) {
    trackerDriven = tDriven;
}

bool Electron::isLoose() const {
    bool passesEt = et() > Electron::looseElectronMinimalEt;
    bool passesEta = fabs(eta()) < Electron::looseElectronMaximalAbsoluteEta;
    bool passesIsolation = relativeIsolation() < Electron::looseIsolatedElectronMaximalRelativeIsolation;
    return passesEt && passesEta && passesIsolation && robustLooseId;
}

bool Electron::isGood() const {
    bool passesEt = et() > Electron::goodElectronMinimalEt;
    bool passesEta = fabs(superClusterEta()) < goodElectronMaximalAbsoluteEta && !isInCrack();
    bool passesD0 = fabs(d0()) < goodElectronMaximalDistanceFromInteractionPoint;
    bool passesID = VBTF_W70_ElectronID();
    return passesEt && passesEta && passesD0 && passesID;
}

bool Electron::isInBarrelRegion() const {
    return fabs(superClusterEta()) < Detector::Barrel::MaximalAbsoluteEta;
}

bool Electron::isInCrack() const {
    bool passesMinimalEta = fabs(superClusterEta()) > Detector::Crack::MinimalAbsoluteEta;
    bool passesMaximalEta = fabs(superClusterEta()) < Detector::Crack::MaximalAbsoluteEta;
    return passesMinimalEta && passesMaximalEta;
}

bool Electron::isInEndCapRegion() const {
    return fabs(superClusterEta()) > Detector::EndCap::MinimalAbsoluteEta;
}

bool Electron::isFromConversion() const {
    return innerLayerMissingHits > Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion;
}

bool Electron::VBTF_W70_ElectronID() const {
    if (isInBarrelRegion())
        return getVBTF_W70_ElectronID_Barrel();
    else if (isInEndCapRegion())
        return getVBTF_W70_ElectronID_Endcap();
    else
        return false;
}

float Electron::sigmaIEtaIEta() const {
    return sigma_IEtaIEta;
}

float Electron::dPhiIn() const {
    return dPhi_In;
}

float Electron::dEtaIn() const {
    return dEta_In;
}

float Electron::HadOverEm() const {
    return hadOverEm;
}

float Electron::HEEPet() const {
    return energy() * sin(fourvector.Theta());
}
bool Electron::isEcalDriven() const {
    return ecalDriven;
}

bool Electron::isTrackerDriven() const {
    return trackerDriven;
}

bool Electron::RobustLooseID() const {
    return robustLooseId;
}

bool Electron::RobustTightID() const {
    return robustTightId;
}

void Electron::setNumberOfMissingInnerLayerHits(float missingHits) {
    innerLayerMissingHits = missingHits;
}

unsigned short Electron::getClosestJetID(const JetCollection& jets) const {//#TODO fix definition in Particles!!!
    unsigned short idOfClosest = 999;
    float closestDR = 999.;
    for (unsigned short index = 0; index < jets.size(); ++index) {
        float DR = deltaR(jets.at(index));
        if (DR < closestDR) {
            closestDR = DR;
            idOfClosest = index;
        }
    }
    return idOfClosest;
}

void Electron::setUsedAlgorithm(Electron::Algorithm algo) {
    usedAlgorithm = algo;
}

bool Electron::getVBTF_W70_ElectronID_Barrel() const {
    bool passesSigmaIEta = sigma_IEtaIEta < VBTF_W70::MaximalSigmaIEtaIEta_BarrelRegion;
    bool passesDPhiIn = dPhi_In < VBTF_W70::MaximalDPhiIn_BarrelRegion;
    bool passesDEtaIn = dEta_In < VBTF_W70::MaximalDEtaIn_BarrelRegion;
    bool passesHadOverEm = hadOverEm < VBTF_W70::MaximalHadOverEm_BarrelRegion;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool Electron::getVBTF_W70_ElectronID_Endcap() const {
    bool passesSigmaIEta = sigma_IEtaIEta < VBTF_W70::MaximalSigmaIEtaIEta_EndcapRegion;
    bool passesDPhiIn = dPhi_In < VBTF_W70::MaximalDPhiIn_EndcapRegion;
    bool passesDEtaIn = dEta_In < VBTF_W70::MaximalDEtaIn_EndcapRegion;
    bool passesHadOverEm = hadOverEm < VBTF_W70::MaximalHadOverEm_EndcapRegion;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

}
