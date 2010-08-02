/*
 * MuonReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/MuonReader.h"

namespace BAT {

MuonReader::MuonReader() :
	numberOfMuonsReader(), energyReader(), pxReader(), pyReader(), pzReader(), ecalIsolationReader(),
			hcalIsolationReader(), trackerIsolationReader(), isGlobalReader() {

}

MuonReader::MuonReader(TChainPointer input) :
	numberOfMuonsReader(input, "Nmus"), energyReader(input, "mus_energy"), pxReader(input, "mus_px"), pyReader(input,
			"mus_py"), pzReader(input, "mus_pz"), ecalIsolationReader(input, "mus_iso03_emEt"), hcalIsolationReader(
			input, "mus_iso03_hadEt"), trackerIsolationReader(input, "mus_iso03_sumPt"), isGlobalReader(input,
			"mus_id_AllGlobalMuons") {

}

void MuonReader::initialise() {
	numberOfMuonsReader.initialise();
	energyReader.initialise();
	pxReader.initialise();
	pyReader.initialise();
	pzReader.initialise();

	ecalIsolationReader.initialise();
	hcalIsolationReader.initialise();
	trackerIsolationReader.initialise();

	isGlobalReader.initialise();
}

const MuonCollection& MuonReader::getMuons() {
	if (muons.empty() == false)
		muons.clear();
	readMuons();
	return muons;
}

void MuonReader::readMuons(){
	unsigned int numberOfMuons = numberOfMuonsReader.getVariable();
		for (unsigned int index = 0; index < numberOfMuons; index++) {
			float energy = energyReader.getVariableAt(index);
			float px = pxReader.getVariableAt(index);
			float py = pyReader.getVariableAt(index);
			float pz = pzReader.getVariableAt(index);
			Muon muon(energy, px, py, pz);
			muon.setEcalIsolation(ecalIsolationReader.getVariableAt(index));
			muon.setHcalIsolation(hcalIsolationReader.getVariableAt(index));
			muon.setTrackerIsolation(trackerIsolationReader.getVariableAt(index));
			muon.makeGlobal(isGlobalReader.getVariableAt(index) == 1);
			muons.push_back(muon);
		}
}
MuonReader::~MuonReader() {
}

}
