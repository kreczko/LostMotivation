/*
 * TTbarHypothesis.h
 *
 *  Created on: Dec 4, 2010
 *      Author: lkreczko
 */

#ifndef TTBARHYPOTHESIS_H_
#define TTBARHYPOTHESIS_H_
#include "RecoObjects/Electron.h"
#include "RecoObjects/Jet.h"
#include "RecoObjects/MET.h"
#include "RecoObjects/Particle.h"

namespace BAT {
class TtbarHypothesis {
public:
	TtbarHypothesis();
	virtual ~TtbarHypothesis();
	double totalChi2, leptonicChi2, hadronicChi2, globalChi2;
	ParticlePointer hadronicTop, leptonicTop, leptonicW, hadronicW, ressonance, neutrinoFromW;
	JetPointer leptonicBjet, hadronicBJet, jet1FromW, jet2FromW;
	ElectronPointer electronFromW;
	METPointer met;

	bool operator==(const TtbarHypothesis& hyp) const;
	bool operator<(const TtbarHypothesis& hyp) const;

};

typedef boost::shared_ptr<TtbarHypothesis> TtbarHypothesisPointer;
} // namespace BAT

#endif /* TTBARHYPOTHESIS_H_ */
