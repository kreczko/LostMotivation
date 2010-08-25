/*
 * EventPrinter.cpp
 *
 *  Created on: 22 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/Printers/EventPrinter.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace BAT {
namespace EventPrinter {

extern void printJets(const JetCollection jets) {
    for (unsigned short index = 0; index < jets.size(); ++index) {
        const JetPointer jet = jets.at(index);
        cout << "Jet " << index + 1 << endl;
        printJet(jet);
    }
}

extern void printJet(const JetPointer jet) {
    printParticle(jet);
    cout << setw(30) << "emf" << setw(30) << "n90Hits" << setw(30) << "fHPD" << setw(30) << "B tag(SSV)" << endl;
    cout << setw(30) << jet->emf() << setw(30) << jet->n90Hits() << setw(30) << jet->fHPD() << setw(30)
            << jet->isBJetAccordingToBtagAlgorithm(BJetTagger::SimpleSecondaryVertex) << endl << endl;
}

extern void printElectrons(const ElectronCollection electrons) {
    for (unsigned short index = 0; index < electrons.size(); ++index) {
        const ElectronPointer electron = electrons.at(index);
        cout << "Electron " << index + 1 << endl;
        printElectron(electron);
    }
}

extern void printElectron(const ElectronPointer electron) {
    printParticle(electron);
    cout << setw(30) << "VBTF70" << setw(30) << "VBTF95" << setw(30) << "robust loose" << setw(30) << "robust tight"
            << endl;
    cout << setw(30) << electron->VBTF_W70_ElectronID() << setw(30) << "" << setw(30) << electron->RobustLooseID()
            << setw(30) << electron->RobustTightID() << endl;

    cout << setw(30) << "sigma_{ieta ieta}" << setw(30) << "|Delta phi_{in}|" << setw(30) << "|Delta eta_{in}|"
            << setw(30) << "HadOverEm" << endl;
    cout << setw(30) << electron->sigmaIEtaIEta() << setw(30) << fabs(electron->dPhiIn()) << setw(30) << fabs(
            electron->dEtaIn()) << setw(30) << electron->HadOverEm() << endl;

    cout << setw(30) << "isSpike" << setw(30) << "rel. iso." << setw(30) << "isFromConversion" << setw(30)
            << "superClusterEta" << endl;
    cout << setw(30) << electron->isEcalSpike() << setw(30) << electron->relativeIsolation() << setw(30)
            << electron->isFromConversion() << setw(30) << electron->superClusterEta() << endl << endl;

    cout << setw(30) << "isTrackerDriven" << setw(30) << "swiss_cross" << setw(30) << "isLoose" << setw(30)
            << "isEcalDriven" << endl;
    cout << setw(30) << electron->isTrackerDriven() << setw(30) << electron->swissCross() << setw(30)
            << electron->isLoose() << setw(30) << electron->isEcalDriven() << endl << endl;
}

extern void printParticle(const ParticlePointer particle) {
    cout << setw(30) << "pt" << setw(30) << "px" << setw(30) << "py" << setw(30) << "pz" << endl;
    cout << setw(30) << particle->pt() << setw(30) << particle->px() << setw(30) << particle->py() << setw(30)
            << particle->pz() << endl;

    cout << setw(30) << "energy" << setw(30) << "et" << setw(30) << "eta" << setw(30) << "phi" << endl;
    cout << setw(30) << particle->energy() << setw(30) << particle->et() << setw(30) << particle->eta() << setw(30)
            << particle->phi() << endl;

    cout << setw(30) << "d0" << setw(30) << "dyn. mass" << setw(30) << "fix. mass" << setw(30) << "charge" << endl;
    cout << setw(30) << particle->d0() << setw(30) << particle->massFromEnergyAndMomentum() << setw(30)
            << particle->mass() << setw(30) << particle->charge() << endl;
}
}
}