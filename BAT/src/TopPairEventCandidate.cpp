/*
 * TopPairEventCandidate.cpp
 *
 *  Created on: 9 Jul 2010
 *      Author: kreczko
 */

#include "../interface/TopPairEventCandidate.h"

namespace BAT {

TopPairEventCandidate::TopPairEventCandidate() :
    Event() {
}

TopPairEventCandidate::TopPairEventCandidate(const Event& event): Event(event){

}

TopPairEventCandidate::~TopPairEventCandidate() {
}


bool TopPairEventCandidate::passesHighLevelTrigger() const {
    return HLT_PHOTON15_L1R;
}

bool TopPairEventCandidate::hasOneGoodPrimaryVertex() const {
    return primaryVertex.isGood();
}

bool TopPairEventCandidate::hasOnlyOneGoodIsolatedElectron() const {
    return goodIsolatedElectrons.size() == 1;
}

bool TopPairEventCandidate::isolatedElectronDoesNotComeFromConversion() const {
    if (goodIsolatedElectrons.size() > 0)
        return goodIsolatedElectrons.front().isFromConversion() == false;
    else
        return false;
}

bool TopPairEventCandidate::hasNoIsolatedMuon() const {
    return goodIsolatedMuons.size() == 0;
}

bool TopPairEventCandidate::hasAtLeastOneGoodJet() const {
    return goodJets.size() >= 1;
}

bool TopPairEventCandidate::hasAtLeastTwoGoodJets() const {
    return goodJets.size() >= 2;
}

bool TopPairEventCandidate::hasAtLeastThreeGoodJets() const {
    return goodJets.size() >= 3;
}

bool TopPairEventCandidate::hasAtLeastFourGoodJets() const {
    return goodJets.size() >= 4;
}

bool TopPairEventCandidate::isNotAZBosonEvent() const {
    float invariantMass = 0;
    if (goodIsolatedElectrons.size() == 2)
        invariantMass = goodIsolatedElectrons.at(0).invariantMass(goodIsolatedElectrons.at(1));
    else if (goodIsolatedElectrons.size() == 1 && looseElectrons.size() > 0)
        invariantMass = goodIsolatedElectrons.front().invariantMass(looseElectrons.front());

    bool passesLowerLimit = invariantMass >= 76;
    bool passesUpperLimit = invariantMass <= 106;
    return (passesLowerLimit && passesUpperLimit) == false;
}

bool TopPairEventCandidate::passesFullTTbarEPlusJetSelection() const {
    unsigned int newstep = (int) TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS - 1;
    return passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) newstep);
}

bool TopPairEventCandidate::passesSelectionStepUpTo(enum TTbarEPlusJetsSelection::Step step) const {
    if (step == TTbarEPlusJetsSelection::HighLevelTrigger)
        return passesSelectionStep(step);
    else {
        unsigned int newstep = (int) step - 1;
        return passesSelectionStep(step) && passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) newstep);
    }
}

bool TopPairEventCandidate::passesSelectionStep(enum TTbarEPlusJetsSelection::Step step) const {
    switch (step) {
    case TTbarEPlusJetsSelection::HighLevelTrigger:
        return passesHighLevelTrigger();
    case TTbarEPlusJetsSelection::GoodPrimaryvertex:
        return hasOneGoodPrimaryVertex();
    case TTbarEPlusJetsSelection::OneIsolatedElectron:
        return hasOnlyOneGoodIsolatedElectron();
    case TTbarEPlusJetsSelection::ConversionRejection:
        return isolatedElectronDoesNotComeFromConversion();
    case TTbarEPlusJetsSelection::LooseMuonVeto:
        return hasNoIsolatedMuon();
    case TTbarEPlusJetsSelection::AtLeastFourGoodJets:
        return hasAtLeastFourGoodJets();
    case TTbarEPlusJetsSelection::Zveto:
        return isNotAZBosonEvent();
    default:
        return false;
    }
}

}
