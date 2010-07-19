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
#include <boost/array.hpp>

namespace BAT {
//make sure the IDs and their string representations are identical
//

class Electron: public Particle {
public:
	enum ElectronID {
		loose, tight, robustLoose, robustTight, VBTF_W70, HEEP, NUMBER_OF_ELECTRONIDS
	};
	static const boost::array<std::string, NUMBER_OF_ELECTRONIDS> ElectronIDNames;
	static float goodElectronMinimalEt;
	static float goodElectronMaximalAbsoluteEta;
	static float goodElectronMaximalDistanceFromInteractionPoint;

	static float looseElectronMinimalEt;
	static float looseElectronMaximalAbsoluteEta;

	static float MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion;

	static ElectronID goodElectronID;

	static float isolatedElectronMaximalRelativeIsolation;
	static float looseIsolatedElectronMaximalRelativeIsolation;

	static std::string getElectronIDAsString(ElectronID id){
		return Electron::ElectronIDNames.at(id);
	}

	static void resetSelectionValues(){
		Electron::goodElectronMinimalEt = 0;
		Electron::goodElectronMaximalAbsoluteEta = 5;
		Electron::goodElectronMaximalDistanceFromInteractionPoint = 5000;

		Electron::looseElectronMinimalEt = 0;
		Electron::looseElectronMaximalAbsoluteEta = 5;
		Electron::looseIsolatedElectronMaximalRelativeIsolation = 5000;

		Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion = 500;

		Electron::isolatedElectronMaximalRelativeIsolation = 2;
	}

	Electron();
	Electron(float energy, float px, float py, float pz);
	virtual ~Electron();
	bool isGood() const;
	bool isIsolated() const;
	bool isFromConversion() const;
	bool isLoose() const;

	float ecalIsolation() const;
	float hcalIsolation() const;
	float trackerIsolation() const;
	float superClusterEta() const;

	void setRobustLooseID(bool id);
	void setRobustTightID(bool id);
	void setVBTF_W70_ElectronID(bool id);

	void setSuperClusterEta(float eta);
	void setEcalIsolation(float isolation);
	void setHcalIsolation(float isolation);
	void setTrackerIsolation(float isolation);
	void setNumberOfMissingInnerLayerHits(float missingHits);

	float relativeIsolation() const;

	bool isInBarrelRegion() const;
	bool isInCrack() const;
	bool isInEndCapRegion() const;

private:

	bool robustLooseId, robustTightId, VBTF_W70_ElectronID;
	float superCluser_Eta;
	float ecal_Isolation, hcal_Isolation, tracker_Isolation;
	float innerLayerMissingHits;

};

typedef std::vector<Electron> ElectronCollection;

}

#endif /* ELECTRON_H_ */
