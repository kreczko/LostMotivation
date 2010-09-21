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
    numberOfElectronsReader(), energyReader(), pxReader(), pyReader(), pzReader(), chargeReader(),
            superClusterEtaReader(), d0Reader(), numberOfInnerLayerMissingHitsReader(), ecalIsolationReader(),
            hcalIsolationReader(), trackerIsolationReader(), robustLooseIDReader(), robustTightIDReader(),
            sigmaIEtaIEtaReader(), dPhiInReader(), dEtaInReader(), hadOverEmReader(), isEcalDrivenReader(),
            isTrackerDrivenReader(), swissCrossReader(), electrons() {

}
ElectronReader::ElectronReader(TChainPointer input,TChainPointer input2,  Electron::Algorithm algo) :
    numberOfElectronsReader(input, "N" + algorithmPrefixes[algo]), energyReader(input, algorithmPrefixes[algo]
            + "_energy"), pxReader(input, algorithmPrefixes[algo] + "_px"), pyReader(input, algorithmPrefixes[algo]
            + "_py"), pzReader(input, algorithmPrefixes[algo] + "_pz"), chargeReader(input, algorithmPrefixes[algo]
            + "_charge"), superClusterEtaReader(input, algorithmPrefixes[algo] + "_scEta"), d0Reader(input,
            algorithmPrefixes[algo] + "3_d0_bs"), numberOfInnerLayerMissingHitsReader(input, algorithmPrefixes[algo]
            + "_innerLayerMissingHits"), ecalIsolationReader(input, algorithmPrefixes[algo] + "_dr03EcalRecHitSumEt"),
            hcalIsolationReader(input, algorithmPrefixes[algo] + "_dr03HcalTowerSumEt"), trackerIsolationReader(input,
                    algorithmPrefixes[algo] + "_dr03TkSumPt"), robustLooseIDReader(input, algorithmPrefixes[algo]
                    + "_robustLooseId"), robustTightIDReader(input, algorithmPrefixes[algo] + "_robustTightId"),
            sigmaIEtaIEtaReader(input, algorithmPrefixes[algo] + "_sigmaIEtaIEta"), dPhiInReader(input,
                    algorithmPrefixes[algo] + "_dPhiIn"), dEtaInReader(input, algorithmPrefixes[algo] + "_dEtaIn"),
            hadOverEmReader(input, algorithmPrefixes[algo] + "_hadOverEm"), isEcalDrivenReader(input,
                    algorithmPrefixes[algo] + "_isEcalDriven"), isTrackerDrivenReader(input, algorithmPrefixes[algo]
                    + "_isTrackerDriven"), swissCrossReader(input2, "e_swissCross"), electrons() {

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
        electron->setCharge(chargeReader.getVariableAt(index));
        electron->setD0(d0Reader.getVariableAt(index));
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

        electron->setIsEcalDriven(isEcalDrivenReader.getVariableAt(index) == 1);
        electron->setIsTrackerDriven(isTrackerDrivenReader.getVariableAt(index) == 1);
        electron->setSwissCross(swissCrossReader.getVariableAt(index));

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
    d0Reader.initialise();
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

    isEcalDrivenReader.initialise();
    isTrackerDrivenReader.initialise();
    swissCrossReader.initialise();
}

}

