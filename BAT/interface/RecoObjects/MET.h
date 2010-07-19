/*
 * MET.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MET_H_
#define MET_H_
#include "Particle.h"

namespace BAT {

class MET: public Particle {
public:
	enum Type {
		DEFAULT, CalorimeterMET_mujes, SC5, SC7, KT4, KT6, tcMET, ParticleFlowMET, MCTruth, NUMBER_OF_METALGORITHMS
	};

	static float goodMETMinimalEt;

	static void resetSelectionValues() {
		MET::goodMETMinimalEt = 0;
	}
	MET();
	virtual ~MET();
	bool isGood();
};

}

#endif /* MET_H_ */
