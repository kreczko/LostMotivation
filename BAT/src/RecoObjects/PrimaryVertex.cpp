/*
 * PrimaryVertex.cpp
 *
 *  Created on: 25 Jul 2010
 *      Author: kreczko
 */

#include "../../interface/RecoObjects/PrimaryVertex.h"
#include <math.h>
namespace BAT {
unsigned int PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom = 0;
float PrimaryVertex::goodVertexMaximalAbsoluteZPosition = 5000;
float PrimaryVertex::goodVertexMaximalAbsoluteZPositionForRealData = 5000;
float PrimaryVertex::goodVertexMaximalAbsoluteRho = 5000;


PrimaryVertex::PrimaryVertex() :
	is_fake(false), degreesOfFreedom(0), z_position(0), rho(0) {

}

PrimaryVertex::~PrimaryVertex() {
}

void PrimaryVertex::setDegreesOfFreedom(unsigned int ndof) {
	degreesOfFreedom = ndof;
}

void PrimaryVertex::setZPosition(float z) {
	z_position = z;
}

void PrimaryVertex::setRho(float rho) {
	this->rho = rho;
}

void PrimaryVertex::setFake(bool fake) {
	is_fake = fake;
}

unsigned int PrimaryVertex::ndof() const {
	return degreesOfFreedom;
}

float PrimaryVertex::absoluteZPosition() const {
	return fabs(z_position);
}

float PrimaryVertex::absoluteRho() const {
	return fabs(rho);
}

bool PrimaryVertex::isFake() const {
	return is_fake;
}

bool PrimaryVertex::isGood() const {
	bool passesNDOF = ndof() >= PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom;
	bool passesZ = absoluteZPosition() <= PrimaryVertex::goodVertexMaximalAbsoluteZPosition;
	bool passesRho = absoluteRho() <= PrimaryVertex::goodVertexMaximalAbsoluteRho;
	bool isNotFake = isFake() == false;
	return passesNDOF && passesZ && passesRho && isNotFake;
}

bool PrimaryVertex::isGoodInRealData() const {
    bool passesNDOF = ndof() >= PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom;
    bool passesZ = absoluteZPosition() <= PrimaryVertex::goodVertexMaximalAbsoluteZPositionForRealData;
    bool passesRho = absoluteRho() <= PrimaryVertex::goodVertexMaximalAbsoluteRho;
    bool isNotFake = isFake() == false;
    return passesNDOF && passesZ && passesRho && isNotFake;
}
}
