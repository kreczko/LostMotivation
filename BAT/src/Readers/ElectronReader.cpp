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
ElectronReader::ElectronReader(boost::shared_ptr<TChain> input) :
	numberOfElectronsReader(input, "Nels"), energyReader(input, "els_energy"), pxReader(input, "els_px"), pyReader(
			input, "els_py"), pzReader(input, "els_pz"), d0Reader(input, "els3_d0_bs"), ecalIsolationReader(input,
			"els_dr03EcalRecHitSumEt"), hcalIsolationReader(input, "els_dr03HcalTowerSumEt"), trackerIsolationReader(
			input, "els_dr03TkSumPt"), electrons() {

}

ElectronReader::~ElectronReader() {
}

std::vector<Electron> ElectronReader::getElectrons() {
	if (electrons.empty() == false)
		electrons.clear();
	readElectrons();
	return electrons;
}

void ElectronReader::readElectrons() {
	unsigned int numberOfElectrons = numberOfElectronsReader.getVariable();
	for (unsigned int index = 0; index < numberOfElectrons; index++) {
		float energy = energyReader.getVariable()->at(index);
		float px = pxReader.getVariable()->at(index);
		float py = pyReader.getVariable()->at(index);
		float pz = pzReader.getVariable()->at(index);
		Electron electron(energy, px, py, pz);
		electron.setD0(d0Reader.getVariable()->at(index));
		electron.setEcalIsolation(ecalIsolationReader.getVariable()->at(index));
		electron.setHcalIsolation(hcalIsolationReader.getVariable()->at(index));
		electron.setTrackerIsolation(trackerIsolationReader.getVariable()->at(index));
		electrons.push_back(electron);
	}
}

void ElectronReader::initialise() {
	numberOfElectronsReader.initialise();
	energyReader.initialise();
	pxReader.initialise();
	pyReader.initialise();
	pzReader.initialise();
	d0Reader.initialise();
	ecalIsolationReader.initialise();
	hcalIsolationReader.initialise();
	trackerIsolationReader.initialise();
}

}

