/*
 * Jet.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JET_H_
#define JET_H_

namespace BAT {

class Jet {
public:
	static float goodJetPtCut;
	static float goodJetEtaCut;
	Jet();
	virtual ~Jet();
	bool isGoodJet();
};

}

#endif /* JET_H_ */
