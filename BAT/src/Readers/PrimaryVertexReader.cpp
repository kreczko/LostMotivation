/*
 * PrimaryVertexReader.cpp
 *
 *  Created on: 25 Jul 2010
 *      Author: kreczko
 */

#include "../../interface/Readers/PrimaryVertexReader.h"

namespace BAT {

PrimaryVertexReader::PrimaryVertexReader() :
	ndofReader(), zReader(), rhoReader(), isfakeReader(), vertex() {

}

PrimaryVertexReader::PrimaryVertexReader(TChainPointer input) :
	ndofReader(input, "pv_ndof"), zReader(input, "pv_z"), rhoReader(input, "pv_rho"), isfakeReader(input, "pv_isFake"),
			vertex() {

}

void PrimaryVertexReader::initialise() {
	ndofReader.initialise();
	zReader.initialise();
	rhoReader.initialise();
	isfakeReader.initialise();
}

const PrimaryVertex& PrimaryVertexReader::getVertex() {
	readVertex();
	return vertex;
}

void PrimaryVertexReader::readVertex() {
	vertex = PrimaryVertex();
	vertex.setDegreesOfFreedom(ndofReader.getVariableAt(0));
	vertex.setFake(isfakeReader.getVariableAt(0) > 0);
	vertex.setRho(rhoReader.getVariableAt(0));
	vertex.setZPosition(zReader.getVariableAt(0));
}
PrimaryVertexReader::~PrimaryVertexReader() {
}

}
