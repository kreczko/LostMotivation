/*
 * Jet.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JET_H_
#define JET_H_
#include "../Taggers/BJetTagger.h"
#include "Particle.h"

namespace BAT {

class Jet :public Particle{
public:
	enum Algorithm{
		DEFAULT,
		JPT_AntiKt_ConeDR05,
		KT_Cone04,
		KT_Cone06,
		ParticleFlow,
		SiS_Cone05,
		SiS_Cone07,
		NUMBER_OF_JETALGORITHMS
	};
	static float goodJetMinimalEt;
	static float goodJetMaximalAbsoluteEta;
	static float goodJetMinimalElectromagneticFraction;
	Jet();
	virtual ~Jet();
	bool isGoodJet();
	bool isBJetAccordingToBtagAlgorithm(BJetTagger::Algorithm btag);
};

}

#endif /* JET_H_ */
