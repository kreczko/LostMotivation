/*
 * ConversionTagger.h
 *
 *  Created on: Jun 30, 2010
 *      Author: lkreczko
 */

#ifndef CONVERSIONTAGGER_H_
#define CONVERSIONTAGGER_H_
#include "../RecoObjects/Electron.h"
#include "../RecoObjects/Track.h"

namespace BAT {

class ConversionTagger {
public:
	ConversionTagger();
	virtual ~ConversionTagger();
	void calculateConversionVariables(const ElectronPointer electron, const TrackCollection tracks);
};

}

#endif /* CONVERSIONTAGGER_H_ */
