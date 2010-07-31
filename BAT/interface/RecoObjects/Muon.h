/*
 * Muon.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MUON_H_
#define MUON_H_
#include "Particle.h"
#include <vector>

namespace BAT {

class Muon: public Particle {
public:
	static float goodMuonMinimalPt;
	static float goodMuonMaximalAbsoluteEta;
	static float isolatedMuonMaximalRelativeIsolation;

	static void resetSelectionValues() {
		Muon::goodMuonMinimalPt = 0;
		Muon::goodMuonMaximalAbsoluteEta = 5;
		Muon::isolatedMuonMaximalRelativeIsolation = 5000;
	}
	Muon();
	Muon(float energy, float px, float py, float pz);
	virtual ~Muon();
	bool isGood() const;
	bool isIsolated() const;
	bool isGlobal() const;
	float ecalIsolation() const;
	float hcalIsolation() const;
	float trackerIsolation() const;
	float relativeIsolation() const;

	void makeGlobal(bool global);
	void setEcalIsolation(float isolation);
	void setHcalIsolation(float isolation);
	void setTrackerIsolation(float isolation);
private:
	bool is_Global;
	float ecal_Isolation, hcal_Isolation, tracker_Isolation;
};

typedef std::vector<Muon> MuonCollection;
}

#endif /* MUON_H_ */
