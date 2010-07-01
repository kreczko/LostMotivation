/*
 * Jet.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JET_H_
#define JET_H_
#include "../Enumerators.h"

namespace BAT {

class Jet {
public:
	static float goodJetMinimalEt;
	static float goodJetMaximalAbsoluteEta;
	static float goodJetMinimalElectromagneticFraction;
	Jet();
	virtual ~Jet();
	bool isGoodJet();
	bool isBJetAccordingToBtagAlgorithm(BTag::Algorithm btag);
};

}

#endif /* JET_H_ */
