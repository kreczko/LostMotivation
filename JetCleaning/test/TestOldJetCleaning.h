/*
 * TestOldJetCleaning.h
 *
 *  Created on: 8 May 2011
 *      Author: kreczko
 */

#ifndef TESTOLDJETCLEANING_H_
#define TESTOLDJETCLEANING_H_

#include "cute/cute.h"
#include "cute/cute_suite.h"
#include "../interface/JetCollectionForEleHT.h"

struct TestOldJetCleaning {

private:
    JetCollectionForEleHT jetCleaning;
public:
    TestOldJetCleaning() :
        jetCleaning(0.3) {
    }

    //    void blankTest(){
    //        ASSERT(true);
    //    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus1Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = jetCleaning.getCleanedJets(electrons, jets);
        ASSERT(cleanedJets.size() >= 1);
    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus2Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = jetCleaning.getCleanedJets(electrons, jets);
        ASSERT(cleanedJets.size() >= 2);
    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus3Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = jetCleaning.getCleanedJets(electrons, jets);
        ASSERT(! (cleanedJets.size() >= 3));
    }

    void ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus4Jet() {
        std::pair<v3Collection, v3Collection> p(Scenarios::ElectronAndJetInElectronCollectionEPlus2JetEvent());
        v3Collection electrons = p.first;
        v3Collection jets = p.second;

        v3Collection cleanedJets = jetCleaning.getCleanedJets(electrons, jets);
        ASSERT(! (cleanedJets.size() >= 4));
    }
};

extern cute::suite make_suite_TestOldJetCleaning() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestOldJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus1Jet));
    s.push_back(CUTE_SMEMFUN(TestOldJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventPassesEPlus2Jet));
    s.push_back(CUTE_SMEMFUN(TestOldJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus3Jet));
    s.push_back(CUTE_SMEMFUN(TestOldJetCleaning, ElectronAndJetInElectronCollectionEPlus2JetEventFailsEPlus4Jet));
    return s;
}

#endif /* TESTOLDJETCLEANING_H_ */
