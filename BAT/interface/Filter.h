/*
 * Filter.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "../interface/RecoObjects/Electron.h"
#include "../interface/RecoObjects/Jet.h"
#include "../interface/RecoObjects/MET.h"
#include "../interface/RecoObjects/PrimaryVertex.h"
#include "../interface/RecoObjects/Muon.h"
namespace BAT {

class Filter {
public:
	Filter();
	virtual ~Filter();
	static Filter* makeStandardFilter();

	void setGoodVertexMinimalNumberOfDegreesOfFreedom(unsigned int minimalNDOF);
	void setGoodVertexMaximalAbsoluteZPosition(float absoluteZ);
	void setGoodVertexMaximalRho(float rho);

	void setGoodJetMinimalEt(float minimalEt);
	void setGoodJetMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setGoodJetMinimalElectromagneticFraction(float minimalElectromagneticFraction);
	void setGoodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy(float n90Hits);
	void setGoodJetMaximalFractionOfEnergyIntheHottestHPDReadout(float fHPD);

	void setGoodElectronMinimalEt(float minimalEt);
	void setGoodElectronMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setGoodElectronMaximalDistanceFromInteractionPoint(float maximalDistance);

	void setLooseElectronMinimalEt(float minimalEt);
	void setLooseElectronMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation);
	void setLooseIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation);

	void setGoodMETMinimalEt(float minimalEt);

	void setGoodMuonMinimalPt(float pt);
	void setGoodMuonMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setIsolatedMuonMinimalRelativeIsolation(float isolation);

	static void resetSelectionValues(){
		Electron::resetSelectionValues();
		Jet::resetSelectionValues();
		MET::resetSelectionValues();
		PrimaryVertex::resetSelectionValues();
		Muon::resetSelectionValues();
	}
};

}

#endif /* FILTER_H_ */
