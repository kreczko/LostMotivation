/*
 * DummyTTbarEvent.h
 *
 *  Created on: 25 Aug 2010
 *      Author: kreczko
 */

#ifndef DUMMYTTBAREVENT_H_
#define DUMMYTTBAREVENT_H_

#include "../TopPairEventCandidate.h"

namespace BAT {

class DummyTTbarEvent: public TopPairEventCandidate {
public:
    DummyTTbarEvent();
    virtual ~DummyTTbarEvent();
    void setElectronFromW(const ElectronPointer electron);
    bool passScraping, passHLT, passPV, passElectronCut, passConversion, passesMuon, passesJetCuts, passesZveto,
            useCustomReturnValues;

    bool passesScrapingFilter() const;
    bool passesHighLevelTrigger() const;
    bool hasOneGoodPrimaryVertex() const;
    bool hasOnlyOneGoodIsolatedElectron() const;
    bool isolatedElectronDoesNotComeFromConversion() const;
    bool hasNoIsolatedMuon() const;
    bool hasAtLeastFourGoodJets() const;

    bool isNotAZBosonEvent() const;
    bool passesNMinus1(TTbarEPlusJetsSelection::Step omittedStep) const;
    bool passesSelectionStep(enum TTbarEPlusJetsSelection::Step step) const;
};

}

#endif /* DUMMYTTBAREVENT_H_ */
