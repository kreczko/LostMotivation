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
    Particle(), usedAlgorithm(MET::DEFAULT) {
}

MET::MET(float ex, float ey) :
    Particle(sqrt(ex * ex + ey * ey), ex, ey, 0), usedAlgorithm(MET::DEFAULT) {

}

MET::~MET() {
}

bool MET::isGood() const {
    return et() > MET::goodMETMinimalEt;
}

void MET::setUsedAlgorithm(MET::Algorithm algo) {
    usedAlgorithm = algo;
}

MET::Algorithm MET::getUsedAlgorithm() const {
    return usedAlgorithm;
}

}
