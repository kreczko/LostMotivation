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
#include <string>
#include <boost/static_assert.hpp>
namespace BAT {
enum ElectronID {
	loose, tight, robustLoose, robustTight, VBTF_W70, HEEP, NUMBER_OF_ELECTRONIDS
};

const std::string ElectronIDNames[] = { "loose ID", "tight ID", "robust loose ID", "robust tight ID",
		"VBTF working point 70%", "High Energy" };
//make sure the IDs and their string representations are identical
BOOST_STATIC_ASSERT(NUMBER_OF_ELECTRONIDS == (int) (sizeof(ElectronIDNames)/sizeof(ElectronIDNames[0])));

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

	void setRobustLooseID(bool id);
	void setRobustTightID(bool id);

	void setEcalIsolation(float isolation);
	void setHcalIsolation(float isolation);
	void setTrackerIsolation(float isolation);

	float relativeIsolation() const;
private:

	bool robustLooseId, robustTightId;
	float ecalIsolation, hcalIsolation, trackerIsolation;
	float innerLayerMissingHits;

};

typedef std::vector<Electron> ElectronCollection;

}

#endif /* ELECTRON_H_ */
