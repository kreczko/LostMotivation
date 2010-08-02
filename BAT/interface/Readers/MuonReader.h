/*
 * MuonReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MUONREADER_H_
#define MUONREADER_H_
#include "VariableReader.h"
#include "../RecoObjects/Muon.h"

namespace BAT {

class MuonReader {
public:
	MuonReader();
	MuonReader(TChainPointer input);
	virtual ~MuonReader();
	const MuonCollection& getMuons();
	void initialise();

private:
	VariableReader<unsigned int> numberOfMuonsReader;
	VariableReader<MultiFloatPointer> energyReader;
	VariableReader<MultiFloatPointer> pxReader;
	VariableReader<MultiFloatPointer> pyReader;
	VariableReader<MultiFloatPointer> pzReader;

	VariableReader<MultiFloatPointer> ecalIsolationReader;
	VariableReader<MultiFloatPointer> hcalIsolationReader;
	VariableReader<MultiFloatPointer> trackerIsolationReader;

	VariableReader<MultiFloatPointer> isGlobalReader;

	MuonCollection muons;
	void readMuons();
};

}

#endif /* MUONREADER_H_ */
