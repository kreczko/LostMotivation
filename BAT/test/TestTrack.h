/*
 * TestTrack.h
 *
 *  Created on: 19 Sep 2010
 *      Author: kreczko
 */

#ifndef TESTTRACK_H_
#define TESTTRACK_H_
#include "cute/cute.h"
#include "cute/cute_suite.h"
#include "../interface/RecoObjects/Track.h"

using namespace BAT;

struct TestTrack {
private:
    ParticlePointer particle1, particle2;
    TrackPointer track1, track2;
public:
    TestTrack() :
        particle1(new Particle(40, 40, 0, 0)), particle2(new Particle(40, -40, 0, 0)), track1(new Track(
                particle1->phi(), particle1->eta(), particle1->pt(), particle1->theta())), track2(new Track(
                particle2->phi(), particle2->eta(), particle2->pt(), particle2->theta())) {
        track1->setCharge(1);
        track2->setCharge(-1);
        track1->setD0(1);
        track2->setD0(1);
    }

    void testCurvatureWithSTDBField() {
        ASSERT_EQUAL(-0.3 * 3.8 * track1->charge() / track1->pt() / 100., track1->curvature());
    }

    void testCurvatureWithCustomBField() {
        ASSERT_EQUAL(-0.3 * 4 * track1->charge() / track1->pt() / 100., track1->curvature(4.));
    }

    void testRadiusWithSTDBField() {
        ASSERT_EQUAL(fabs(1 / track1->curvature()), track1->radius());
    }

    void testRadiusWithCustomBField() {
        ASSERT_EQUAL(fabs(1 / track1->curvature(5)), track1->radius(5));
    }

    void testXWithSTDBField() {
        ASSERT_EQUAL((-track1->radius() - track1->d0()) * sin(track1->phi()), track1->x());
    }

    void testXWithCustomBField() {
        ASSERT_EQUAL((-track1->radius(3) - track1->d0()) * sin(track1->phi()), track1->x(3));
    }

    void testYWithSTDBField() {
        ASSERT_EQUAL((track1->radius() - track1->d0()) * cos(track1->phi()), track1->y());
    }

    void testYWithCustomBField() {
        ASSERT_EQUAL((track1->radius(3) - track1->d0()) * cos(track1->phi()), track1->y(3));
    }

    void testDeltaCotThetaWithSTDBField() {
        ASSERT_EQUAL(fabs(1 / tan(track1->theta()) - 1 / tan(track2->theta())), track1->deltaCotTheta(track2));
    }

    void testDistanceWithSTDBfield() {
        double dx = track1->x() - track2->x();
        double dy = track1->y() - track2->y();
        double dist = sqrt(dx * dx + dy * dy);
        dist = fabs(dist - (track1->radius() + track2->radius()));
        ASSERT_EQUAL(dist, track1->distance(track2));
        ASSERT_EQUAL(track1->distance(track2), track2->distance(track1));
    }

    void testDistanceWithCustomBfield() {
        double field = 3.2;
        double dx = track1->x(field) - track2->x(field);
        double dy = track1->y(field) - track2->y(field);
        double dist = sqrt(dx * dx + dy * dy);
        dist = fabs(dist - (track1->radius(field) + track2->radius(field)));
        ASSERT_EQUAL(dist, track1->distance(track2, field));
        ASSERT_EQUAL(track1->distance(track2, field), track2->distance(track1, field));
    }

    void testEta() {
        ASSERT_EQUAL(0, track1->eta());
    }

    void testPhi() {
        ASSERT_EQUAL(true, track1->phi() > -10);
    }

    void testPt() {
        ASSERT_EQUAL(true, track1->pt() > 0);
    }

    void testTheta() {
        ASSERT_EQUAL(true, track1->theta() > 0);
    }

    void testCustomEta() {
        TrackPointer track = TrackPointer(new Track(1, 0.5, 12.5, 23.5));
        ASSERT_EQUAL(0.5, track->eta());
    }

    void testCustomPhi() {
        TrackPointer track = TrackPointer(new Track(1, 0.5, 12.5, 23.5));
        ASSERT_EQUAL(1, track->phi());
    }

    void testCustomPt() {
        TrackPointer track = TrackPointer(new Track(1, 0.5, 12.5, 23.5));
        ASSERT_EQUAL(12.5, track->pt());
    }

    void testCustomTheta() {
        TrackPointer track = TrackPointer(new Track(1, 0.5, 12.5, 23.5));
        ASSERT_EQUAL(23.5, track->theta());
    }
};

extern cute::suite make_suite_TestTrack() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestTrack, testCurvatureWithSTDBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testCurvatureWithCustomBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testRadiusWithSTDBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testRadiusWithCustomBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testXWithSTDBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testXWithCustomBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testYWithSTDBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testYWithCustomBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testDeltaCotThetaWithSTDBField));
    s.push_back(CUTE_SMEMFUN(TestTrack, testDistanceWithSTDBfield));
    s.push_back(CUTE_SMEMFUN(TestTrack, testDistanceWithCustomBfield));
    s.push_back(CUTE_SMEMFUN(TestTrack, testEta));
    s.push_back(CUTE_SMEMFUN(TestTrack, testPhi));
    s.push_back(CUTE_SMEMFUN(TestTrack, testPt));
    s.push_back(CUTE_SMEMFUN(TestTrack, testTheta));
    s.push_back(CUTE_SMEMFUN(TestTrack, testCustomEta));
    s.push_back(CUTE_SMEMFUN(TestTrack, testCustomPhi));
    s.push_back(CUTE_SMEMFUN(TestTrack, testCustomPt));
    s.push_back(CUTE_SMEMFUN(TestTrack, testCustomTheta));
    return s;
}
#endif /* TESTTRACK_H_ */
