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
#include <boost/shared_ptr.hpp>

namespace BAT {
class ElectronReader{
public:
	ElectronReader();
	ElectronReader(boost::shared_ptr<TChain> input);
	virtual ~ElectronReader();
	std::vector<Electron> getElectrons();
	void initialise();
private:
	VariableReader<unsigned int> numberOfElectronsReader;
	VariableReader<MultiFloatPointer> energyReader;
	VariableReader<MultiFloatPointer> pxReader;
	VariableReader<MultiFloatPointer> pyReader;
	VariableReader<MultiFloatPointer> pzReader;
	VariableReader<MultiFloatPointer> d0Reader;
	VariableReader<MultiFloatPointer> ecalIsolationReader;
	VariableReader<MultiFloatPointer> hcalIsolationReader;
	VariableReader<MultiFloatPointer> trackerIsolationReader;

	std::vector<Electron> electrons;
	void readElectrons();

};

}

#endif /* ELECTRONREADER_H_ */
