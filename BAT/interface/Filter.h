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

namespace BAT {

class Filter {
public:
	Filter();
	virtual ~Filter();
	static Filter* makeStandardFilter();

	void setGoodJetMinimalEt(float minimalEt);
	void setGoodJetMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setGoodJetMinimalElectromagneticFraction(float minimalElectromagneticFraction);

	void setGoodElectronMinimalEt(float minimalEt);
	void setGoodElectronMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setGoodElectronMaximalDistanceFromInteractionPoint(float maximalDistance);

	void setLooseElectronMinimalEt(float minimalEt);
	void setLooseElectronMaximalAbsoluteEta(float maximalAbsoluteEta);
	void setIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation);
	void setLooseIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation);

	void setGoodMETMinimalEt(float minimalEt);

	static void resetSelectionValues(){
		Electron::resetSelectionValues();
		Jet::resetSelectionValues();
		MET::resetSelectionValues();
	}
};

}

#endif /* FILTER_H_ */
