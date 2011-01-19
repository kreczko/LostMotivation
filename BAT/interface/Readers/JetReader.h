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
//	const static std::string algorithmPrefixes[JetAlgorithm::NUMBER_OF_JETALGORITHMS];
	
	JetReader();
	JetReader(TChainPointer, JetAlgorithm::value algo = JetAlgorithm::Calo_AntiKT_Cone05);
	virtual ~JetReader();
	const JetCollection& getJets();
	void initialise();
private:
	VariableReader<unsigned int> numberOfJetsReader;
	VariableReader<MultiDoublePointer> energyReader;
	VariableReader<MultiDoublePointer> pxReader;
	VariableReader<MultiDoublePointer> pyReader;
	VariableReader<MultiDoublePointer> pzReader;
	VariableReader<MultiDoublePointer> massReader;

	VariableReader<MultiDoublePointer> emfReader;
	VariableReader<MultiIntPointer> n90HitsReader;
	VariableReader<MultiDoublePointer> fHPDReader;

	VariableReader<MultiIntPointer> NODReader;
	VariableReader<MultiDoublePointer> CEFReader;
	VariableReader<MultiDoublePointer> NHFReader;
	VariableReader<MultiDoublePointer> NEFReader;
	VariableReader<MultiDoublePointer> CHFReader;
	VariableReader<MultiIntPointer> NCHReader;

	VariableReader<MultiDoublePointer> btagSimpleSecondaryVertexReader;
//	VariableReader<MultiDoublePointer> btagSimpleSecondaryVertexReaderData;
	VariableReader<MultiDoublePointer> btagTrackCountingHighPurityReader;
	VariableReader<MultiDoublePointer> btagTrackCountingHighEfficiencyReader;

	JetCollection jets;
	JetAlgorithm::value usedAlgorithm;
	void readJets();
};

}

#endif /* JETREADER_H_ */
