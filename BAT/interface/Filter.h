/*
 * Filter.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef FILTER_H_
#define FILTER_H_

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
	void setIsolatedElectronMaximalRelativeIsolation(float maximalRelativeIsolation);

	void setGoodMETMinimalEt(float minimalEt);

	void setSimpleSecondaryVertexHighEfficiencyMediumCut(float cut);
};

}

#endif /* FILTER_H_ */
