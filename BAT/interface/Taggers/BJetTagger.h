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
	static float simpleSecondaryVertexHighEfficiencyMediumCut;

	//	BJetTagger();
	//	virtual ~BJetTagger();
	static bool tag(BTag::Algorithm type, float discriminator) {
		switch (type) {
		case BTag::NONE:
			return true;
		default:
			break;
		}
	}

};
}

#endif /* BJETTAGGER_H_ */
