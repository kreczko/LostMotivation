/*
 * TestNewJetCleaning.h
 *
 *  Created on: 8 May 2011
 *      Author: kreczko
 */

#ifndef TESTNEWJETCLEANING_H_
#define TESTNEWJETCLEANING_H_

#include "cute/cute.h"
#include "cute/cute_suite.h"
#include "Scenarios.h"
#include "../interface/JetCollectionForElePlusJets.h"

struct TestNewJetCleaning {

private:
    JetCollectionForElePlusJets ePlus1Jet;
    JetCollectionForElePlusJets ePlus2Jet;
    JetCollectionForElePlusJets ePlus3Jet;
    JetCollectionForElePlusJets ePlus4Jet;
public:
    TestNewJetCleaning() :
        ePlus1Jet(30, 100, 1, 0.3), ePlus2Jet(30, 100, 2, 0.3), ePlus3Jet(30, 100, 3, 0.3), ePlus4Jet(30, 100, 4, 0.3) {
    }

    //    void blankTest(){
    //        ASSERT(true);
    //    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus1Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = ePlus1Jet.getCleanedJets(electrons, jets);
        ASSERT(cleanedJets.size() >= 1);
    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus2Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = ePlus2Jet.getCleanedJets(electrons, jets);
        ASSERT(cleanedJets.size() >= 2);
    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus3Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = ePlus3Jet.getCleanedJets(electrons, jets);
        ASSERT(! (cleanedJets.size() >= 3));
    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus4Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = ePlus4Jet.getCleanedJets(electrons, jets);
        ASSERT(! (cleanedJets.size() >= 4));
    }
};

extern cute::suite make_suite_TestNewJetCleaning() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestNewJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus1Jet));
    s.push_back(CUTE_SMEMFUN(TestNewJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus2Jet));
    s.push_back(CUTE_SMEMFUN(TestNewJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus3Jet));
    s.push_back(CUTE_SMEMFUN(TestNewJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus4Jet));
    return s;
}

#endif /* TESTNEWJETCLEANING_H_ */
