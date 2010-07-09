/*
 * ElectronReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRONREADER_H_
#define ELECTRONREADER_H_
#include "../RecoObjects/Electron.h"
#include "VariableReader.h"
#include <vector>
#include "TChain.h"

namespace BAT {
class ElectronReader{
public:
	ElectronReader();
	ElectronReader(TChain* input);
	virtual ~ElectronReader();
	std::vector<Electron> getElectrons();
private:
	VariableReader<unsigned int> numberOfElectronsReader;
	VariableReader<MultiFloatPointer> energyReader;
	VariableReader<MultiFloatPointer> pxReader;
	VariableReader<MultiFloatPointer> pyReader;
	VariableReader<MultiFloatPointer> pzReader;

	std::vector<Electron> electrons;
	void readElectrons();

};

}

#endif /* ELECTRONREADER_H_ */
