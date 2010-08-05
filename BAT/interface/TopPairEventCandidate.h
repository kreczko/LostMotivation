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

class TopPairEventCandidate: public Event {

private:
    float getLeptonicChi2();
    float getHadronicChi2();
    float getGlobalChi2();
    float getTotalChi2();

public:
    TopPairEventCandidate();
    TopPairEventCandidate(const Event& event);
    virtual ~TopPairEventCandidate();

    //	static constTopPairEventCandidate* getCandidateByChi2();
    //	static TopPairEventCandidate* getCandidateByJetSubstructure();
    //	static TopPairEventCandidate* getCandidateByMCTruthMatching();

    const Jet& getLeptonicBJet() const;
    const Jet& getHadronicBJet() const;
    const Jet& getJet1FromHadronicW() const;
    const Jet& getJet2FromHadronicW() const;
    const Electron& getElectronFromWDecay() const;
    const Particle& getNeutrinoFromWDecay() const;

    bool passesSelectionStep(TTbarEPlusJetsSelection::Step step) const;
    bool passesSelectionStepUpTo(TTbarEPlusJetsSelection::Step upToStep) const;

    bool passesHighLevelTrigger() const;
    bool hasOneGoodPrimaryVertex() const;
    bool hasOnlyOneGoodIsolatedElectron() const;
    bool isolatedElectronDoesNotComeFromConversion() const;
    bool hasNoIsolatedMuon() const;

    bool hasAtLeastOneGoodJet() const;
    bool hasAtLeastTwoGoodJets() const;
    bool hasAtLeastThreeGoodJets() const;
    bool hasAtLeastFourGoodJets() const;

    bool isNotAZBosonEvent() const;
    bool passesFullTTbarEPlusJetSelection() const;
    bool hasIsolatedElectronInBarrelRegion() const;

};

}

#endif /* TOPPAIREVENTCANDIDATE_H_ */
