/*
 * TrackReader.cpp
 *
 *  Created on: 20 Sep 2010
 *      Author: kreczko
 */

#include "../../interface/Readers/TrackReader.h"

namespace BAT {

TrackReader::TrackReader() :
    numberOfTracksReader(), pxReader(), pyReader(), pzReader(), chargeReader(), d0Reader(), highPurityReader() {

}

TrackReader::TrackReader(TChainPointer input) :
    numberOfTracksReader(input, "Ntracks"), pxReader(input, "tracks_px"), pyReader(input, "tracks_py"), pzReader(input,
            "tracks_pz"), chargeReader(input, "tracks_chg"), d0Reader(input, "tracks_d0dum"), highPurityReader(input,
            "tracks_highPurity") {

}

TrackReader::~TrackReader() {
}

const TrackCollection& TrackReader::getTracks() {
    if (tracks.empty() == false)
        tracks.clear();
    readTracks();
    return tracks;
}

void TrackReader::readTracks() {
    unsigned int numberOfTracks = numberOfTracksReader.getVariable();
    for (unsigned int index = 0; index < numberOfTracks; index++) {
        float px = pxReader.getVariableAt(index);
        float py = pyReader.getVariableAt(index);
        float pz = pzReader.getVariableAt(index);
        float energy = sqrt(px * px + py * py + pz * pz);
        TrackPointer track(new Track(energy, px, py, pz));
        track->setCharge(chargeReader.getVariableAt(index));
        track->setD0(d0Reader.getVariableAt(index));
        track ->setHighPurity(highPurityReader.getVariableAt(index) > 0);

        tracks.push_back(track);
    }
}

void TrackReader::initialise() {
    numberOfTracksReader.initialise();
    pxReader.initialise();
    pyReader.initialise();
    pzReader.initialise();
    chargeReader.initialise();
    d0Reader.initialise();
    highPurityReader.initialise();
}

}
