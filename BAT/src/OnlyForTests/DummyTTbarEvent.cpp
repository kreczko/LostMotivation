/*
 * DummyTTbarEvent.cpp
 *
 *  Created on: 25 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/OnlyForTests/DummyTTbarEvent.h"
#include <iostream>

using namespace std;
namespace BAT {

DummyTTbarEvent::DummyTTbarEvent() :
    BAT::TopPairEventCandidate(), passScraping(false), passHLT(false), passPV(false), passElectronCut(false),
            passConversion(false), passesMuon(false), passesJetCuts(false), passesZveto(false), useCustomReturnValues(
                    false) {

}

DummyTTbarEvent::~DummyTTbarEvent() {
}

void DummyTTbarEvent::setElectronFromW(ElectronPointer electron) {
    electronFromW = electron;
}

bool DummyTTbarEvent::passesScrapingFilter() const {
    if (useCustomReturnValues)
        return passScraping;
    else
        return TopPairEventCandidate::passesScrapingFilter();
}

bool DummyTTbarEvent::passesHighLevelTrigger() const {
    if (useCustomReturnValues)
        return passHLT;
    else
        return TopPairEventCandidate::passesHighLevelTrigger();
}

bool DummyTTbarEvent::hasOneGoodPrimaryVertex() const {
    if (useCustomReturnValues)
        return passPV;
    else
        return TopPairEventCandidate::hasOneGoodPrimaryVertex();
}

bool DummyTTbarEvent::hasOnlyOneGoodIsolatedElectron() const {
    if (useCustomReturnValues)
        return passElectronCut;
    else
        return TopPairEventCandidate::hasOnlyOneGoodIsolatedElectron();
}

bool DummyTTbarEvent::isolatedElectronDoesNotComeFromConversion() const {
    if (useCustomReturnValues)
        return passConversion;
    else
        return TopPairEventCandidate::isolatedElectronDoesNotComeFromConversion();
}

bool DummyTTbarEvent::hasNoIsolatedMuon() const {
    if (useCustomReturnValues)
        return passesMuon;
    else
        return TopPairEventCandidate::hasNoIsolatedMuon();
}

bool DummyTTbarEvent::hasAtLeastFourGoodJets() const {
    if (useCustomReturnValues)
        return passesJetCuts;
    else
        return TopPairEventCandidate::hasAtLeastFourGoodJets();
}

bool DummyTTbarEvent::isNotAZBosonEvent() const {
    if (useCustomReturnValues)
        return passesZveto;
    else
        return TopPairEventCandidate::isNotAZBosonEvent();
}

bool DummyTTbarEvent::passesNMinus1(enum TTbarEPlusJetsSelection::Step omitted) const {
    bool passes(true);

    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        if (cut == (unsigned int) omitted)
            continue;
        passes = passes && passesSelectionStep((TTbarEPlusJetsSelection::Step) cut);
    }
    return passes;
}

bool DummyTTbarEvent::passesSelectionStep(enum TTbarEPlusJetsSelection::Step step) const {
    switch (step) {
    case TTbarEPlusJetsSelection::FilterOutScraping:
        return passesScrapingFilter();
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
