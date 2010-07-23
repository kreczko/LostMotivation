/*
 * JetReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JETREADER_H_
#define JETREADER_H_
#include "../RecoObjects/Jet.h"
#include "VariableReader.h"
#include <vector>
#include "TChain.h"
#include <boost/shared_ptr.hpp>
#include <string>
namespace BAT {

class JetReader {
public:
	const static unsigned short numberOfVariables = 11;
	const static std::string algorithmPrefixes[Jet::NUMBER_OF_JETALGORITHMS];
	
	JetReader();
	JetReader(boost::shared_ptr<TChain> input, Jet::Algorithm algo = Jet::DEFAULT);
	virtual ~JetReader();
	std::vector<Jet> getJets();
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

	std::vector<Jet> jets;
	void readJets();
};

}

#endif /* JETREADER_H_ */
