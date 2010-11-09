/*
 * ElectronReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/ElectronReader.h"
namespace BAT {

//const std::string ElectronReader::algorithmPrefixes[Electron::NUMBER_OF_ELECTRONALGORITHMS] = { "els", "PFElsAll" };

ElectronReader::ElectronReader() :
    numberOfElectronsReader(),
    energyReader(),
    pxReader(),
    pyReader(),
    pzReader(),
    chargeReader(),
    superClusterEtaReader(),
    d0_BS_Reader(),
    d0_PV_Reader(),
    numberOfInnerLayerMissingHitsReader(),
    ecalIsolationReader(),
    hcalIsolationReader(),
    trackerIsolationReader(),
    robustLooseIDReader(),
    robustTightIDReader(),
    sigmaIEtaIEtaReader(),
    dPhiInReader(),
    dEtaInReader(),
    hadOverEmReader(),
    sharedFractionInnerHits(),
    trackIDReader(),
    track_phi(),
    track_eta(),
    track_pt(),
    track_theta(),
    track_charge(),
    vertex_z(),
    algorithm(ElectronAlgorithm::Calo),
    electrons() {

}

ElectronReader::ElectronReader(TChainPointer input, TChainPointer input2, ElectronAlgorithm::value algo) :
    numberOfElectronsReader(input, "N" + ElectronAlgorithm::prefixes.at(algo)),
    energyReader(input, ElectronAlgorithm::prefixes.at(algo) + "_energy"),
    pxReader(input, ElectronAlgorithm::prefixes.at(algo) + "_px"),
    pyReader(input, ElectronAlgorithm::prefixes.at(algo) + "_py"),
    pzReader(input, ElectronAlgorithm::prefixes.at(algo) + "_pz"),
    chargeReader(input, ElectronAlgorithm::prefixes.at(algo) + "_charge"),
    superClusterEtaReader(input, ElectronAlgorithm::prefixes.at(algo) + "_scEta"),
    d0_BS_Reader(input, ElectronAlgorithm::prefixes.at(algo) + "3_d0_bs"),
    d0_PV_Reader(input, ElectronAlgorithm::prefixes.at(algo) + "_dB"),
    numberOfInnerLayerMissingHitsReader(input, ElectronAlgorithm::prefixes.at(algo) + "_innerLayerMissingHits"),
    ecalIsolationReader(input, ElectronAlgorithm::prefixes.at(algo) + "_dr03EcalRecHitSumEt"),
    hcalIsolationReader(input, ElectronAlgorithm::prefixes.at(algo) + "_dr03HcalTowerSumEt"),
    trackerIsolationReader(input,ElectronAlgorithm::prefixes.at(algo) + "_dr03TkSumPt"),
    robustLooseIDReader(input, ElectronAlgorithm::prefixes.at(algo) + "_robustLooseId"),
    robustTightIDReader(input, ElectronAlgorithm::prefixes.at(algo) + "_robustTightId"),
    sigmaIEtaIEtaReader(input, ElectronAlgorithm::prefixes.at(algo) + "_sigmaIEtaIEta"),
    dPhiInReader(input, ElectronAlgorithm::prefixes.at(algo) + "_dPhiIn"),
    dEtaInReader(input, ElectronAlgorithm::prefixes.at(algo) + "_dEtaIn"),
    hadOverEmReader(input, ElectronAlgorithm::prefixes.at(algo) + "_hadOverEm"),
    sharedFractionInnerHits(input, ElectronAlgorithm::prefixes.at(algo) + "_shFracInnerHits"),
    trackIDReader(input, ElectronAlgorithm::prefixes.at(algo) + "_closestCtfTrackRef"),
    track_phi(input, ElectronAlgorithm::prefixes.at(algo) + "_tk_phi"),
    track_eta(input, ElectronAlgorithm::prefixes.at(algo) + "_tk_eta"),
    track_pt(input, ElectronAlgorithm::prefixes.at(algo) + "_tk_pt"),
    track_theta(input, ElectronAlgorithm::prefixes.at(algo) + "_tk_theta"),
    track_charge(input, ElectronAlgorithm::prefixes.at(algo) + "_tk_charge"),
    vertex_z(input, ElectronAlgorithm::prefixes.at(algo) + "_vz"),
    algorithm(algo),
    electrons() {

}

ElectronReader::~ElectronReader() {
}

const ElectronCollection& ElectronReader::getElectrons() {
    if (electrons.empty() == false)
        electrons.clear();
    readElectrons();
    return electrons;
}

void ElectronReader::readElectrons() {
    unsigned int numberOfElectrons = numberOfElectronsReader.getVariable();
    for (unsigned int index = 0; index < numberOfElectrons; index++) {
        float energy = energyReader.getVariableAt(index);
        float px = pxReader.getVariableAt(index);
        float py = pyReader.getVariableAt(index);
        float pz = pzReader.getVariableAt(index);
        ElectronPointer electron(new Electron(energy, px, py, pz));
        electron->setUsedAlgorithm(algorithm);
        electron->setCharge(chargeReader.getVariableAt(index));
        if(d0_BS_Reader.doesVariableExist())
            electron->setD0_BS(d0_BS_Reader.getVariableAt(index));
        electron->setD0(d0_PV_Reader.getVariableAt(index));
        electron->setElectronVertexZPosition(vertex_z.getVariableAt(index));
        electron->setNumberOfMissingInnerLayerHits(numberOfInnerLayerMissingHitsReader.getVariableAt(index));
        electron->setEcalIsolation(ecalIsolationReader.getVariableAt(index));
        electron->setHcalIsolation(hcalIsolationReader.getVariableAt(index));
        electron->setTrackerIsolation(trackerIsolationReader.getVariableAt(index));
        electron->setSuperClusterEta(superClusterEtaReader.getVariableAt(index));
        electron->setSigmaIEtaIEta(sigmaIEtaIEtaReader.getVariableAt(index));
        electron->setDPhiIn(dPhiInReader.getVariableAt(index));
        electron->setDEtaIn(dEtaInReader.getVariableAt(index));
        electron->setHadOverEm(hadOverEmReader.getVariableAt(index));
        electron->setRobustLooseID(robustLooseIDReader.getVariableAt(index) == 1);
        electron->setRobustTightID(robustTightIDReader.getVariableAt(index) == 1);

        electron->setSharedFractionInnerHits(sharedFractionInnerHits.getVariableAt(index));
        electron->setClosestTrackID(static_cast<int> (trackIDReader.getVariableAt(index)));
        float trackPhi = track_phi.getVariableAt(index);
        float trackEta = track_eta.getVariableAt(index);
        float trackPt = track_pt.getVariableAt(index);
        float trackTheta = track_theta.getVariableAt(index);
        float trackCharge = track_charge.getVariableAt(index);
        TrackPointer track = TrackPointer(new Track(trackPhi, trackEta, trackPt, trackTheta));
        track->setCharge(trackCharge);
        if(algorithm == ElectronAlgorithm::Calo)
            track->setD0(electron->d0_BS());
        else
            track->setD0(electron->d0());
        electron->setGSFTrack(track);
        electrons.push_back(electron);
    }
}

void ElectronReader::initialise() {
    numberOfElectronsReader.initialise();
    energyReader.initialise();
    pxReader.initialise();
    pyReader.initialise();
    pzReader.initialise();
    chargeReader.initialise();
    superClusterEtaReader.initialise();

    if(d0_BS_Reader.doesVariableExist())
        d0_BS_Reader.initialise();
    d0_PV_Reader.initialise();
    numberOfInnerLayerMissingHitsReader.initialise();

    ecalIsolationReader.initialise();
    hcalIsolationReader.initialise();
    trackerIsolationReader.initialise();

    robustLooseIDReader.initialise();
    robustTightIDReader.initialise();
    sigmaIEtaIEtaReader.initialise();
    dPhiInReader.initialise();
    dEtaInReader.initialise();
    hadOverEmReader.initialise();

    sharedFractionInnerHits.initialise();
    trackIDReader.initialise();
    track_phi.initialise();
    track_eta.initialise();
    track_pt.initialise();
    track_theta.initialise();
    track_charge.initialise();
    vertex_z.initialise();
}

}

