/*
 * ElectronReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/ElectronReader.h"
namespace BAT {

const std::string ElectronReader::algorithmPrefixes[Electron::NUMBER_OF_ELECTRONALGORITHMS] = { "els", "PFElsAll" };

ElectronReader::ElectronReader() :
	numberOfElectronsReader(), energyReader(), pxReader(), pyReader(), pzReader(), superClusterEtaReader(), d0Reader(),
			numberOfInnerLayerMissingHitsReader(), ecalIsolationReader(), hcalIsolationReader(),
			trackerIsolationReader(), robustLooseIDReader(), robustTightIDReader(), sigmaIEtaIEtaReader(),
			dPhiInReader(), dEtaInReader(), hadOverEmReader(), electrons() {

}
ElectronReader::ElectronReader(TChainPointer input, Electron::Algorithm algo) :
	numberOfElectronsReader(input, "N" + algorithmPrefixes[algo]), energyReader(input, algorithmPrefixes[algo]
			+ "_energy"), pxReader(input, algorithmPrefixes[algo] + "_px"), pyReader(input, algorithmPrefixes[algo]
			+ "_py"), pzReader(input, algorithmPrefixes[algo] + "_pz"), superClusterEtaReader(input,
			algorithmPrefixes[algo] + "_scEta"), d0Reader(input, algorithmPrefixes[algo] + "3_d0_bs"),
			numberOfInnerLayerMissingHitsReader(input, algorithmPrefixes[algo] + "_innerLayerMissingHits"),
			ecalIsolationReader(input, algorithmPrefixes[algo] + "_dr03EcalRecHitSumEt"), hcalIsolationReader(input,
					algorithmPrefixes[algo] + "_dr03HcalTowerSumEt"), trackerIsolationReader(input,
					algorithmPrefixes[algo] + "_dr03TkSumPt"), robustLooseIDReader(input, algorithmPrefixes[algo]
					+ "_robustLooseId"), robustTightIDReader(input, algorithmPrefixes[algo] + "_robustTightId"),
			sigmaIEtaIEtaReader(input, algorithmPrefixes[algo] + "_sigmaIEtaIEta"), dPhiInReader(input,
					algorithmPrefixes[algo] + "_dPhiIn"), dEtaInReader(input, algorithmPrefixes[algo] + "_dEtaIn"),
			hadOverEmReader(input, algorithmPrefixes[algo] + "_hadOverEm"), electrons() {

}

ElectronReader::~ElectronReader() {
}

const ElectronCollection& ElectronReader::getElectrons() {
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
		electron.setSigmaIEtaIEta(sigmaIEtaIEtaReader.getVariableAt(index));
		electron.setDPhiIn(dPhiInReader.getVariableAt(index));
		electron.setDEtaIn(dEtaInReader.getVariableAt(index));
		electron.setHadOverEm(hadOverEmReader.getVariableAt(index));
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

//bool ElectronReader::getVBTF_W70_ElectronID_Barrel(unsigned int index) {
//	bool passesSigmaIEta = sigmaIEtaIEtaReader.getVariableAt(index) < VBTF_W70::MaximalSigmaIEtaIEta_BarrelRegion;
//	bool passesDPhiIn = dPhiInReader.getVariableAt(index) < VBTF_W70::MaximalDPhiIn_BarrelRegion;
//	bool passesDEtaIn = dEtaInReader.getVariableAt(index) < VBTF_W70::MaximalDEtaIn_BarrelRegion;
//	bool passesHadOverEm = hadOverEmReader.getVariableAt(index) < VBTF_W70::MaximalHadOverEm_BarrelRegion;
//	return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
//}
//
//bool ElectronReader::getVBTF_W70_ElectronID_Endcap(unsigned int index) {
//	bool passesSigmaIEta = sigmaIEtaIEtaReader.getVariableAt(index) < VBTF_W70::MaximalSigmaIEtaIEta_EndcapRegion;
//	bool passesDPhiIn = dPhiInReader.getVariableAt(index) < VBTF_W70::MaximalDPhiIn_EndcapRegion;
//	bool passesDEtaIn = dEtaInReader.getVariableAt(index) < VBTF_W70::MaximalDEtaIn_EndcapRegion;
//	bool passesHadOverEm = hadOverEmReader.getVariableAt(index) < VBTF_W70::MaximalHadOverEm_EndcapRegion;
//	return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
//}

}

