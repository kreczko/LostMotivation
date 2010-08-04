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
	Particle() {
}

MET::MET(float energy, float ex, float ey) :
	Particle(energy, ex, ey, 0) {

}

MET::~MET() {
}

bool MET::isGood() const{
	return et() > MET::goodMETMinimalEt;
}

}
