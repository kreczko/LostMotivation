/*
 * BJetTagger.h
 *
 *  Created on: Jun 30, 2010
 *      Author: lkreczko
 */

#ifndef BJETTAGGER_H_
#define BJETTAGGER_H_

#include "../Enumerators.h"

namespace BAT {

class BJetTagger {
public:
	enum Algorithm {
		NONE,
		FAKE,
		TrackCountingHighEfficiency,
		TrackCountingHighPurity,
		JetBProbability,
		JetProbability,
		SimpleSecondaryVertex,
		SoftElectron,
		SoftMuon,
		SoftMuonNoIP,
		NUMBER_OF_BTAGALGORITHMS
	};
	static float simpleSecondaryVertexHighEfficiencyMediumCut;

	//	BJetTagger();
	//	virtual ~BJetTagger();
	static bool tag(BJetTagger::Algorithm type, float discriminator) {
		switch (type) {
		case BJetTagger::NONE:
			return true;
		default:
			break;
		}
	}

};
}

#endif /* BJETTAGGER_H_ */
