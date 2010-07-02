/*
 * Electron.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRON_H_
#define ELECTRON_H_
#include "Particle.h"

namespace BAT {

class Electron: public Particle {
public:
	static float goodElectronMinimalEt;
	static float goodElectronMaximalAbsoluteEta;
	static float goodElectronMaximalDistanceFromInteractionPoint;

	static float isolatedElectronMaximalRelativeIsolation;

	Electron();
	Electron(float energy, float px, float py, float pz);
	virtual ~Electron();
	bool isGood();
	bool isIsolated();
	bool isInBarrelRegion();
	bool isInCrack();
	bool isInEndCapRegion();
private:

	bool robustLooseId, robustTightId;
	float calorimeterIsolation, trackerIsolation, relativeIsolation;
	float innerLayerMissingHits;

};

}

#endif /* ELECTRON_H_ */
