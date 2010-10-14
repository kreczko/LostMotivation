/*
 * ElectronReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/ElectronReader.h"
namespace BAT {

const std::string ElectronReader::algorithmPrefixes[Electron::NUMBER_OF_ELECTRONALGORITHMS] = { "els", "PFElsAll" };

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
    algorithm(Electron::Calo),
    electrons() {

}

ElectronReader::ElectronReader(TChainPointer input, TChainPointer input2, Electron::Algorithm algo) :
    numberOfElectronsReader(input, "N" + algorithmPrefixes[algo]),
    energyReader(input, algorithmPrefixes[algo] + "_energy"),
    pxReader(input, algorithmPrefixes[algo] + "_px"),
    pyReader(input, algorithmPrefixes[algo] + "_py"),
    pzReader(input, algorithmPrefixes[algo] + "_pz"),
    chargeReader(input, algorithmPrefixes[algo] + "_charge"),
    superClusterEtaReader(input, algorithmPrefixes[algo] + "_scEta"),
    d0_BS_Reader(input, algorithmPrefixes[algo] + "3_d0_bs"),
    d0_PV_Reader(input, algorithmPrefixes[algo] + "_dB"),
    numberOfInnerLayerMissingHitsReader(input, algorithmPrefixes[algo] + "_innerLayerMissingHits"),
    ecalIsolationReader(input, algorithmPrefixes[algo] + "_dr03EcalRecHitSumEt"),
    hcalIsolationReader(input, algorithmPrefixes[algo] + "_dr03HcalTowerSumEt"),
    trackerIsolationReader(input,algorithmPrefixes[algo] + "_dr03TkSumPt"),
    robustLooseIDReader(input, algorithmPrefixes[algo] + "_robustLooseId"),
    robustTightIDReader(input, algorithmPrefixes[algo] + "_robustTightId"),
    sigmaIEtaIEtaReader(input, algorithmPrefixes[algo] + "_sigmaIEtaIEta"),
    dPhiInReader(input, algorithmPrefixes[algo] + "_dPhiIn"),
    dEtaInReader(input, algorithmPrefixes[algo] + "_dEtaIn"),
    hadOverEmReader(input, algorithmPrefixes[algo] + "_hadOverEm"),
    sharedFractionInnerHits(input, algorithmPrefixes[algo] + "_shFracInnerHits"),
    trackIDReader(input, algorithmPrefixes[algo] + "_closestCtfTrackRef"),
    track_phi(input, algorithmPrefixes[algo] + "_tk_phi"),
    track_eta(input, algorithmPrefixes[algo] + "_tk_eta"),
    track_pt(input, algorithmPrefixes[algo] + "_tk_pt"),
    track_theta(input, algorithmPrefixes[algo] + "_tk_theta"),
    track_charge(input, algorithmPrefixes[algo] + "_tk_charge"),
    vertex_z(input, algorithmPrefixes[algo] + "_vz"),
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
        if(algorithm == Electron::Calo)
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

