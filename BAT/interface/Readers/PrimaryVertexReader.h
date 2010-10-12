/*
 * PrimaryVertexReader.h
 *
 *  Created on: 25 Jul 2010
 *      Author: kreczko
 */

#ifndef PRIMARYVERTEXREADER_H_
#define PRIMARYVERTEXREADER_H_
#include "VariableReader.h"
#include "../RecoObjects/PrimaryVertex.h"
namespace BAT {

class PrimaryVertexReader {
public:
	PrimaryVertexReader();
	PrimaryVertexReader(TChainPointer input);
	virtual ~PrimaryVertexReader();
	const PrimaryVertexPointer getVertex();
	void initialise();
private:
	VariableReader<MultiFloatPointer> ndofReader;
	VariableReader<MultiFloatPointer> zReader;
	VariableReader<MultiFloatPointer> rhoReader;
	VariableReader<MultiFloatPointer> isfakeReader;

	PrimaryVertexPointer vertex;
	void readVertex();
};

}

#endif /* PRIMARYVERTEXREADER_H_ */
