/*
 * ElectronReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/ElectronReader.h"
namespace BAT {

ElectronReader::ElectronReader() :
	numberOfElectronsReader(), energyReader(), pxReader(), pyReader(), pzReader(), superClusterEtaReader(), d0Reader(),
			numberOfInnerLayerMissingHitsReader(), ecalIsolationReader(), hcalIsolationReader(),
			trackerIsolationReader(), robustLooseIDReader(), robustTightIDReader(), sigmaIEtaIEtaReader(),
			dPhiInReader(), dEtaInReader(), hadOverEmReader(), electrons() {

}
ElectronReader::ElectronReader(boost::shared_ptr<TChain> input) :
	numberOfElectronsReader(input, "Nels"), energyReader(input, "els_energy"), pxReader(input, "els_px"), pyReader(
			input, "els_py"), pzReader(input, "els_pz"), superClusterEtaReader(input, "els_scEta"), d0Reader(input,
			"els3_d0_bs"), numberOfInnerLayerMissingHitsReader(input, "els_innerLayerMissingHits"),
			ecalIsolationReader(input, "els_dr03EcalRecHitSumEt"),
			hcalIsolationReader(input, "els_dr03HcalTowerSumEt"), trackerIsolationReader(input, "els_dr03TkSumPt"),
			robustLooseIDReader(input, "els_robustLooseId"), robustTightIDReader(input, "els_robustTightId"),
			sigmaIEtaIEtaReader(input, "els_sigmaIEtaIEta"), dPhiInReader(input, "els_dPhiIn"), dEtaInReader(input,
					"els_dEtaIn"), hadOverEmReader(input, "els_hadOverEm"), electrons() {

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
		float energy = energyReader.getVariableAt(index);
		float px = pxReader.getVariableAt(index);
		float py = pyReader.getVariableAt(index);
		float pz = pzReader.getVariableAt(index);
		Electron electron(energy, px, py, pz);
		electron.setD0(d0Reader.getVariableAt(index));
		electron.setNumberOfMissingInnerLayerHits(numberOfInnerLayerMissingHitsReader.getVariableAt(index));
		electron.setEcalIsolation(ecalIsolationReader.getVariableAt(index));
		electron.setHcalIsolation(hcalIsolationReader.getVariableAt(index));
		electron.setTrackerIsolation(trackerIsolationReader.getVariableAt(index));
		electron.setSuperClusterEta(superClusterEtaReader.getVariableAt(index));
		if (electron.isInBarrelRegion())
			electron.setVBTF_W70_ElectronID(getVBTF_W70_ElectronID_Barrel(index));
		else if (electron.isInEndCapRegion())
			electron.setVBTF_W70_ElectronID(getVBTF_W70_ElectronID_Endcap(index));
		else
			electron.setVBTF_W70_ElectronID(false);
		electron.setRobustLooseID(robustLooseIDReader.getVariableAt(index) == 1);
		electron.setRobustTightID(robustTightIDReader.getVariableAt(index) == 1);
		electrons.push_back(electron);
	}
}

void ElectronReader::initialise() {
	numberOfElectronsReader.initialise();
	energyReader.initialise();
	pxReader.initialise();
	pyReader.initialise();
	pzReader.initialise();
	superClusterEtaReader.initialise();
	d0Reader.initialise();
	numberOfInnerLayerMissingHitsReader.initialise();

	ecalIsolationReader.initialise();
	hcalIsolationReader.initialise();
	trackerIsolationReader.initialise();

	robustLooseIDReader.initialise();
	robustTightIDReader.initialise();
	sigmaIEtaIEtaReader.initialise();
	dPhiInReader.initialise();
	dEtaInReader.initialise();
	hadOverEmReader.initialise();
}

bool ElectronReader::getVBTF_W70_ElectronID_Barrel(unsigned int index) {
	bool passesSigmaIEta = sigmaIEtaIEtaReader.getVariableAt(index) < VBTF_W70::MaximalSigmaIEtaIEta_BarrelRegion;
	bool passesDPhiIn = dPhiInReader.getVariableAt(index) < VBTF_W70::MaximalDPhiIn_BarrelRegion;
	bool passesDEtaIn = dEtaInReader.getVariableAt(index) < VBTF_W70::MaximalDEtaIn_BarrelRegion;
	bool passesHadOverEm = hadOverEmReader.getVariableAt(index) < VBTF_W70::MaximalHadOverEm_BarrelRegion;
	return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool ElectronReader::getVBTF_W70_ElectronID_Endcap(unsigned int index) {
	bool passesSigmaIEta = sigmaIEtaIEtaReader.getVariableAt(index) < VBTF_W70::MaximalSigmaIEtaIEta_EndcapRegion;
	bool passesDPhiIn = dPhiInReader.getVariableAt(index) < VBTF_W70::MaximalDPhiIn_EndcapRegion;
	bool passesDEtaIn = dEtaInReader.getVariableAt(index) < VBTF_W70::MaximalDEtaIn_EndcapRegion;
	bool passesHadOverEm = hadOverEmReader.getVariableAt(index) < VBTF_W70::MaximalHadOverEm_EndcapRegion;
	return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

}

