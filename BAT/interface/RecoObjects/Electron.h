/*
 * Electron.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRON_H_
#define ELECTRON_H_
#include "Particle.h"
#include <vector>

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
	bool isGood() const;
	bool isIsolated() const;
	bool isInBarrelRegion() const;
	bool isInCrack() const;
	bool isInEndCapRegion() const;
	void setRobustLooseID(bool id);
	void setRobustTightID(bool id);
	void setEcalEtSumInDr03(float etSum);
	void setHcalEtSumInDr03(float etSum);
	void setTrackPtSumInDr03(float ptSum);
	float relativeIsolation() const;
private:

	bool robustLooseId, robustTightId;
	float ecalEtSumInDr03, hcalEtSumInDr03, trackPtSumInDr03;
	float innerLayerMissingHits;

};

typedef std::vector<Electron> ElectronCollection;

}

#endif /* ELECTRON_H_ */
