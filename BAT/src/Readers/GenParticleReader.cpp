/*
 * GenParticleReader.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: phzss
 */

#include "../../interface/Readers/GenParticleReader.h"
namespace BAT {

GenParticleReader::GenParticleReader() :
	pdgIdReader(),
	pxReader(),
	pyReader(),
	pzReader(),
	energyReader(),
	statusReader(),
	motherIndexReader() {

}

GenParticleReader::GenParticleReader(TChainPointer input) :
	pdgIdReader(input, "GenParticle.PdgId"),
    pxReader(input, "GenParticle.Px"),
    pyReader(input, "GenParticle.Py"),
    pzReader(input, "GenParticle.Pz"),
    energyReader(input, "GenParticle.Energy"),
    statusReader(input, "GenParticle.Status"),
    motherIndexReader(input, "GenParticle.MotherIndex") {

}


GenParticleReader::~GenParticleReader() {
}

const MCParticleCollection& GenParticleReader::getGenParticles() {
    if (genParticles.empty() == false)
        genParticles.clear();
    readGenParticles();
    return genParticles;
}

void GenParticleReader::readGenParticles() {
    for (unsigned int index = 0; index < pxReader.size(); index++) {
    	int pdgId = pdgIdReader.getIntVariableAt(index);
        float px = pxReader.getVariableAt(index);
        float py = pyReader.getVariableAt(index);
        float pz = pzReader.getVariableAt(index);
        float energy = energyReader.getVariableAt(index);
        int motherIndex = motherIndexReader.getIntVariableAt(index);
        int status = statusReader.getIntVariableAt(index);

        MCParticlePointer genParticle(new MCParticle(energy, px, py, pz));
        genParticle->setPdgId(pdgId);
        genParticle->setMotherIndex(motherIndex);
        genParticle->setStatus(status);

        genParticles.push_back(genParticle);
    }
}


void GenParticleReader::initialise() {
	pdgIdReader.initialiseBlindly();
	pxReader.initialiseBlindly();
    pyReader.initialiseBlindly();
    pzReader.initialiseBlindly();
    energyReader.initialiseBlindly();
    statusReader.initialiseBlindly();
}

}
