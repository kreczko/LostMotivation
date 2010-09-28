/*
 * TrackReader.cpp
 *
 *  Created on: 20 Sep 2010
 *      Author: kreczko
 */

#include "../../interface/Readers/TrackReader.h"

namespace BAT {

TrackReader::TrackReader() :
    numberOfTracksReader(), phiReader(), etaReader(), ptReader(), thetaReader(), chargeReader(), d0Reader(),
            highPurityReader() {

}

TrackReader::TrackReader(TChainPointer input) :
    numberOfTracksReader(input, "Ntracks"), phiReader(input, "tracks_phi"), etaReader(input, "tracks_eta"), ptReader(
            input, "tracks_pt"), thetaReader(input, "tracks_theta"), chargeReader(input, "tracks_chg"), d0Reader(input,
            "tracks_d0dum"), highPurityReader(input, "tracks_highPurity") {

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
        float phi = phiReader.getVariableAt(index);
        float eta = etaReader.getVariableAt(index);
        float pt = ptReader.getVariableAt(index);
        float theta = thetaReader.getVariableAt(index);
        TrackPointer track(new Track(phi, eta, pt, theta));
        track->setCharge(chargeReader.getVariableAt(index));
        track->setD0(d0Reader.getVariableAt(index));
        track ->setHighPurity(highPurityReader.getVariableAt(index) > 0);

        tracks.push_back(track);
    }
}

void TrackReader::initialise() {
    numberOfTracksReader.initialise();
    phiReader.initialise();
    etaReader.initialise();
    ptReader.initialise();
    thetaReader.initialise();
    chargeReader.initialise();
    d0Reader.initialise();
    highPurityReader.initialise();
}

}
