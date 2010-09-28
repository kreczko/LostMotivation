/*
 * TestTrackReader.hh
 *
 *  Created on: 20 Sep 2010
 *      Author: kreczko
 */

#ifndef TESTTRACKREADER_HH_
#define TESTTRACKREADER_HH_
#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "../interface/RecoObjects/Track.h"
#include "../interface/Readers/TrackReader.h"
#include "../interface/Readers/NTupleEventReader.h"
#include <iostream>

using namespace BAT;

struct TestTrackReader {
private:
    boost::shared_ptr<TChain> input, input2, input3;
    boost::scoped_ptr<TrackReader> trackReader;
    boost::scoped_ptr<VariableReader<unsigned int> > numberOfTracksReader;
    TrackCollection tracks;
    TrackPointer firstTrack;
public:
    TestTrackReader() :
        input(new TChain(NTupleEventReader::EVENT_CHAIN)), input2(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
                input3(new TChain(NTupleEventReader::ADDITIONAL_CHAIN)), trackReader(new TrackReader(input)),
                numberOfTracksReader(new VariableReader<unsigned int> (input, "e_num")), tracks(), firstTrack() {
        input->AddFriend(input2.get());
        input->AddFriend(input3.get());

        input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
        input2->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
        input3->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");

        input->LoadTree(1);
        input->SetBranchStatus("*", 0);
        input2->SetBranchStatus("*", 0);
        input3->SetBranchStatus("*", 0);
        numberOfTracksReader->initialise();
        trackReader->initialise();
        input->GetEntry(1);
        tracks = trackReader->getTracks();
        firstTrack = tracks.front();
    }

    void testReadTracksSize() {
        ASSERT_EQUAL(121, tracks.size());
    }

    void testReadFirstTrackPhi() {
        ASSERT_EQUAL(true, fabs(firstTrack->phi()) < 2*TMath::Pi()+0.1);
    }

    void testFirstTrackCharge() {
        ASSERT_EQUAL(1, fabs(firstTrack->charge()));
    }

    void testFirstTrackD0() {
        ASSERT_EQUAL_DELTA(-0.0156184, firstTrack->d0(), 0.0000001);
    }

    void testFirstTrackIsHighPurity() {
        ASSERT_EQUAL(true, firstTrack->isHighPurity());
    }

    void testNumberOfHighPurityTracks() {
        unsigned int numberOfHighPurityTracks = 0;
        for (unsigned int index = 0; index < tracks.size(); ++index) {
            if (tracks.at(index)->isHighPurity())
                numberOfHighPurityTracks++;
        }
        ASSERT_EQUAL(111, numberOfHighPurityTracks);
    }

};
extern cute::suite make_suite_TestTrackReader() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestTrackReader, testReadTracksSize));
    s.push_back(CUTE_SMEMFUN(TestTrackReader, testReadFirstTrackPhi));
    s.push_back(CUTE_SMEMFUN(TestTrackReader, testFirstTrackCharge));
    s.push_back(CUTE_SMEMFUN(TestTrackReader, testFirstTrackD0));
    s.push_back(CUTE_SMEMFUN(TestTrackReader, testFirstTrackIsHighPurity));
    s.push_back(CUTE_SMEMFUN(TestTrackReader, testNumberOfHighPurityTracks));
    return s;
}

#endif /* TESTTRACKREADER_HH_ */
