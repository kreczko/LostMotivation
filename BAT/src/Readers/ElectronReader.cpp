/*
 * ElectronReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/ElectronReader.h"
namespace BAT {

ElectronReader::ElectronReader() :
	numberOfElectronsReader(), energyReader(), pxReader(), pyReader(), pzReader(), electrons() {

}
ElectronReader::ElectronReader(TChain* input) :
	numberOfElectronsReader(input, "Nels"), energyReader(input, "els_energy"), pxReader(input, "els_px"), pyReader(
			input, "els_py"), pzReader(input, "els_pz"), electrons() {

}

ElectronReader::~ElectronReader() {
	// TODO Auto-generated destructor stub
}

std::vector<Electron> ElectronReader::getElectrons() {
	if (electrons.empty())
		readElectrons();
	return electrons;
}

void ElectronReader::readElectrons() {
	unsigned int numberOfElectrons = numberOfElectronsReader.getVariable();
	for (unsigned int electronIndex = 0; electronIndex < numberOfElectrons; electronIndex++) {
		float energy = energyReader.getVariable()->at(electronIndex);
		float px = pxReader.getVariable()->at(electronIndex);
		float py = pyReader.getVariable()->at(electronIndex);
		float pz = pzReader.getVariable()->at(electronIndex);
		Electron electron(energy, px, py, pz);
		electrons.push_back(electron);
	}
}

}

