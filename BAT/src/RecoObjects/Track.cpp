/*
 * Track.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Track.h"

namespace BAT {

Track::Track() :
    Particle() {

}

Track::Track(const Track& track) :
    Particle((Particle) track) {

}

Track::Track(float energy, float px, float py, float pz) :
    Particle(energy, px, py, pz) {

}

Track::~Track() {
}

double Track::curvature(double BField) const{
    return -0.3*BField*charge()/pt()/100.;
}

double Track::radius(double Bfield) const{
    return fabs(1/curvature(Bfield));
}

double Track::x(double Bfield) const{
    return (d0()-radius(Bfield))*sin(phi());
}

double Track::y(double Bfield) const{
    return (radius(Bfield) - d0())*cos(phi());
}

double Track::deltaCotTheta(const TrackPointer otherTrack) const{
    return fabs(1/tan(theta()) - 1/tan(otherTrack->theta()));
}

double Track::distance(const TrackPointer otherTrack, double BField) const{
    double dx = x(BField) - otherTrack->x(BField);
    double dy = y(BField) - otherTrack->y(BField);
    double dist = sqrt(pow(dx, 2) + pow(dy,2));
    return fabs(dist - (radius(BField) + otherTrack->radius(BField)));
}

}
