/*
 * MCParticle.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MCPARTICLE_H_
#define MCPARTICLE_H_
#include "Particle.h"

namespace BAT {

class MCParticle : public Particle{
public:
	float id;
	MCParticle();
	virtual ~MCParticle();
};

}

#endif /* MCPARTICLE_H_ */
