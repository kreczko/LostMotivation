/*
 * JetReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JETREADER_H_
#define JETREADER_H_
#include "VariableReader.h"
#include "../RecoObjects/Jet.h"
#include <string>
namespace BAT {

class JetReader {
public:
	const static unsigned short numberOfVariables = 11;
	const static std::string algorithmPrefixes[Jet::NUMBER_OF_JETALGORITHMS];
	
	JetReader();
	JetReader(TChainPointer, Jet::Algorithm algo = Jet::Calo_AntiKT_Cone05);
	virtual ~JetReader();
	const JetCollection& getJets();
	void initialise();
private:
	VariableReader<unsigned int> numberOfJetsReader;
	VariableReader<MultiFloatPointer> energyReader;
	VariableReader<MultiFloatPointer> pxReader;
	VariableReader<MultiFloatPointer> pyReader;
	VariableReader<MultiFloatPointer> pzReader;

	VariableReader<MultiFloatPointer> emfReader;
	VariableReader<MultiFloatPointer> n90HitsReader;
	VariableReader<MultiFloatPointer> fHPDReader;

	VariableReader<MultiFloatPointer> btagSimpleSecondaryVertexReader;
	VariableReader<MultiFloatPointer> btagTrackCountingHighPurityReader;
	VariableReader<MultiFloatPointer> btagTrackCountingHighEfficiencyReader;

	JetCollection jets;
	Jet::Algorithm usedAlgorithm;
	void readJets();
};

}

#endif /* JETREADER_H_ */
