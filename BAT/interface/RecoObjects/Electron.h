/*
 * Electron.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRON_H_
#define ELECTRON_H_

namespace BAT {

class Electron {
public:
	static float goodElectronMinimalEt;
	static float goodElectronMaximalAbsoluteEta;
	static float goodElectronMaximalDistanceFromInteractionPoint;

	static float isolatedElectronMaximalRelativeIsolation;
	Electron();
	virtual ~Electron();
	bool isGood();
	bool isIsolated();
	bool isInBarrelRegion();
	bool isInCrack();
	bool isInEndCapRegion();
private:
	float energy, transversalEnergy;
	float px, py, pz, pt;
	float eta, phi;
	bool robustLooseId, robustTightId;
	float calorimeterIsolation, trackerIsolation, relativeIsolation;
	float innerLayerMissingHits;

};

}

#endif /* ELECTRON_H_ */
