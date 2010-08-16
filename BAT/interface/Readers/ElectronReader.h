/*
 * ElectronReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRONREADER_H_
#define ELECTRONREADER_H_
#include "VariableReader.h"
#include "../RecoObjects/Electron.h"
#include "../VBTF_ElectronID.h"

namespace BAT {
class ElectronReader {
public:
	const static unsigned short numberOfVariables = 11;
	const static std::string algorithmPrefixes[Electron::NUMBER_OF_ELECTRONALGORITHMS];
	ElectronReader();
	ElectronReader(TChainPointer input, Electron::Algorithm algo = Electron::Calo);
	virtual ~ElectronReader();
	const ElectronCollection& getElectrons();
	void initialise();
private:
	VariableReader<unsigned int> numberOfElectronsReader;
	VariableReader<MultiFloatPointer> energyReader;
	VariableReader<MultiFloatPointer> pxReader;
	VariableReader<MultiFloatPointer> pyReader;
	VariableReader<MultiFloatPointer> pzReader;
	VariableReader<MultiFloatPointer> chargeReader;
	VariableReader<MultiFloatPointer> superClusterEtaReader;
	VariableReader<MultiFloatPointer> d0Reader;
	VariableReader<MultiFloatPointer> numberOfInnerLayerMissingHitsReader;

	VariableReader<MultiFloatPointer> ecalIsolationReader;
	VariableReader<MultiFloatPointer> hcalIsolationReader;
	VariableReader<MultiFloatPointer> trackerIsolationReader;

	VariableReader<MultiFloatPointer> robustLooseIDReader;
	VariableReader<MultiFloatPointer> robustTightIDReader;
	VariableReader<MultiFloatPointer> sigmaIEtaIEtaReader;
	VariableReader<MultiFloatPointer> dPhiInReader;
	VariableReader<MultiFloatPointer> dEtaInReader;
	VariableReader<MultiFloatPointer> hadOverEmReader;

	VariableReader<MultiFloatPointer> isEcalDrivenReader;
	VariableReader<MultiFloatPointer> isTrackerDrivenReader;

	ElectronCollection electrons;
	void readElectrons();

};

}

#endif /* ELECTRONREADER_H_ */
