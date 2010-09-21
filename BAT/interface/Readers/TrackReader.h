/*
 * TrackReader.h
 *
 *  Created on: 20 Sep 2010
 *      Author: kreczko
 */

#ifndef TRACKREADER_H_
#define TRACKREADER_H_
#include "../RecoObjects/Track.h"
#include "VariableReader.h"

namespace BAT {

class TrackReader {
private:
    VariableReader<unsigned int> numberOfTracksReader;
    VariableReader<MultiFloatPointer> pxReader;
    VariableReader<MultiFloatPointer> pyReader;
    VariableReader<MultiFloatPointer> pzReader;
    VariableReader<MultiFloatPointer> chargeReader;
    VariableReader<MultiFloatPointer> d0Reader;
    VariableReader<MultiFloatPointer> highPurityReader;

    TrackCollection tracks;
    void readTracks();
public:
    TrackReader();
    TrackReader(TChainPointer input);
    virtual ~TrackReader();
    const TrackCollection& getTracks();
    void initialise();
};

}

#endif /* TRACKREADER_H_ */
