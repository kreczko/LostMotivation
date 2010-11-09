/*
 * MET.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/MET.h"

namespace BAT {

float MET::goodMETMinimalEt = 0;

MET::MET() :
    Particle(), usedAlgorithm(METAlgorithm::Calo) {
}

MET::MET(float ex, float ey) :
    Particle(sqrt(ex * ex + ey * ey), ex, ey, 0), usedAlgorithm(METAlgorithm::Calo) {

}

MET::~MET() {
}

bool MET::isGood() const {
    return et() > MET::goodMETMinimalEt;
}

void MET::setUsedAlgorithm(METAlgorithm::value algo) {
    usedAlgorithm = algo;
}

METAlgorithm::value MET::getUsedAlgorithm() const {
    return usedAlgorithm;
}

}
