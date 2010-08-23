/*
 * EventPrinter.h
 *
 *  Created on: 22 Aug 2010
 *      Author: kreczko
 */

#ifndef EVENTPRINTER_H_
#define EVENTPRINTER_H_
#include "../RecoObjects/Particle.h"
#include "../RecoObjects/Electron.h"
#include "../RecoObjects/Jet.h"

namespace BAT {

namespace EventPrinter {
    extern void printJets(const JetCollection jets);
    extern void printElectrons(const ElectronCollection electrons);

    extern void printJet(const JetPointer jet);
    extern void printElectron(const ElectronPointer electron);
    extern void printParticle(const ParticlePointer particle);
}
}
#endif /* EVENTPRINTER_H_ */
