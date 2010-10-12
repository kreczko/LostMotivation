/*
 * MET.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MET_H_
#define MET_H_
#include "Particle.h"
#include <boost/shared_ptr.hpp>

namespace BAT {

class MET: public Particle {
public:
	enum Algorithm {
		Calo,  KT4, KT6, tcMET, ParticleFlowMET, NUMBER_OF_METALGORITHMS
	};

	static float goodMETMinimalEt;

	static void resetSelectionValues() {
		MET::goodMETMinimalEt = 0;
	}
	MET();
	MET(float ex, float ey);
	virtual ~MET();
	bool isGood() const;
	void setUsedAlgorithm(MET::Algorithm algo);
	MET::Algorithm getUsedAlgorithm() const;
private:
	MET::Algorithm usedAlgorithm;
};

typedef boost::shared_ptr<MET> METPointer;

}

#endif /* MET_H_ */
