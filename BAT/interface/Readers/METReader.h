/*
 * METReader.h
 *
 *  Created on: 4 Aug 2010
 *      Author: kreczko
 */

#ifndef METREADER_H_
#define METREADER_H_
#include "VariableReader.h"
#include "../RecoObjects/MET.h"

namespace BAT {

class METReader {
public:
    const static std::string algorithmPrefixes[MET::NUMBER_OF_METALGORITHMS];

    METReader();
    METReader(TChainPointer input, MET::Algorithm algo = MET::DEFAULT);
    const MET& getMET();
    virtual ~METReader();
    void initialise();
private:
    VariableReader<MultiFloatPointer> exReader;
    VariableReader<MultiFloatPointer> eyReader;
    MET met;
    MET::Algorithm usedAlgorithm;
    void readMET();
};

}

#endif /* METREADER_H_ */
