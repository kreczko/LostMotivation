/*
 * TopPairEventCandidate.h
 *
 *  Created on: 9 Jul 2010
 *      Author: kreczko
 */

#ifndef TOPPAIREVENTCANDIDATE_H_
#define TOPPAIREVENTCANDIDATE_H_

#include <boost/shared_ptr.hpp>
#include "Event.h"
#include "RecoObjects/Particle.h"
#include "RecoObjects/Electron.h"
#include "RecoObjects/Jet.h"

namespace BAT {

class TopPairEventCandidate {

private:
	boost::shared_ptr<Event> event;
	float getLeptonicChi2();
	float getHadronicChi2();
	float getGlobalChi2();
	float getTotalChi2();

public:
	TopPairEventCandidate();
	virtual ~TopPairEventCandidate();

	static TopPairEventCandidate* getCandidateByChi2();
	static TopPairEventCandidate* getCandidateByJetSubstructure();
	static TopPairEventCandidate* getCandidateByMCTruthMatching();

	Jet getLeptonicBJet();
	Jet getHadronicBJet();
	Jet getJet1FromHadronicW();
	Jet getJet2FromHadronicW();
	Electron getElectron();
	Particle getNeutrino();

};

}

#endif /* TOPPAIREVENTCANDIDATE_H_ */
