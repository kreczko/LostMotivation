/*
 * TtbarHypothesis.cpp
 *
 *  Created on: Dec 4, 2010
 *      Author: lkreczko
 */

#include "../interface/TtbarHypothesis.h"

namespace BAT {

TtbarHypothesis::TtbarHypothesis() :
	chi2(99999.), hadronicTop(), leptonicTop(), leptonicW(), hadronicW(), ressonance(), neutrinoFromW(),
			leptonicBjet(), hadronicBJet(), jet1FromW(), jet2FromW(), electronFromW(), met() {

}

TtbarHypothesis::~TtbarHypothesis(){

}

TtbarHypothesis::operator <(const TtbarHypothesis hyp) const{
	return chi2 < hyp.chi2;
}

TtbarHypothesis::operator ==(const TtbarHypothesis hyp) const{
	return chi2 == hyp.chi2;
}

} // namespace BAT
