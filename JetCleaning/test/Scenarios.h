/*
 * Scenarios.h
 *
 *  Created on: 8 May 2011
 *      Author: kreczko
 */

#ifndef SCENARIOS_H_
#define SCENARIOS_H_
#include "TVector3.h"

typedef std::vector<TVector3> v3Collection;

class Scenarios{
public:
    Scenarios(){

    }

    static std::pair<v3Collection, v3Collection> ElectronAndJetInElectronCollectionEPlus2JetEvent(){
        v3Collection electrons, jets;
        TVector3 electron(300,0,0);
        TVector3 jet1(0,300,0);
        TVector3 jet2(0,60,300);

        electrons.push_back(electron);
        electrons.push_back(jet1);

        jets.push_back(electron);
        jets.push_back(jet1);
        jets.push_back(jet2);

        //all objects well separated
        assert(electron.DeltaR(jet1) > 0.3);
        assert(electron.DeltaR(jet2) > 0.3);
        assert(jet1.DeltaR(jet2) > 0.3);

        //jets have enough Pt
        assert(jet1.Pt() > 30);
        assert(jet2.Pt() > 30);

        //are in the right eta range
        assert(std::fabs(jet1.Eta()) < 100);
        assert(std::fabs(jet2.Eta()) < 100);
        return std::pair<v3Collection,v3Collection>(electrons, jets);
    }

};

#endif /* SCENARIOS_H_ */
