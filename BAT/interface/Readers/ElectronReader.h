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
class ElectronReader{
public:
	ElectronReader();
	ElectronReader(TChainPointer input);
	virtual ~ElectronReader();
	const ElectronCollection& getElectrons();
	void initialise();
private:
	VariableReader<unsigned int> numberOfElectronsReader;
	VariableReader<MultiFloatPointer> energyReader;
	VariableReader<MultiFloatPointer> pxReader;
	VariableReader<MultiFloatPointer> pyReader;
	VariableReader<MultiFloatPointer> pzReader;
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

	ElectronCollection electrons;
	void readElectrons();
	bool getVBTF_W70_ElectronID_Barrel(unsigned int index);
	bool getVBTF_W70_ElectronID_Endcap(unsigned int index);


};

}

#endif /* ELECTRONREADER_H_ */
