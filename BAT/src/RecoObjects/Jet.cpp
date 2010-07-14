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

Jet::Jet(): Particle() {

}

Jet::~Jet() {
}

}
