// -*- C++ -*-
//
// Package:    JetCollectionForEleHT
// Class:      JetCollectionForEleHT
// 
/**\class JetCollectionForEleHT JetCollectionForEleHT.cc HLTrigger/JetCollectionForEleHT/src/JetCollectionForEleHT.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Massimiliano Chiorboli,40 4-A01,+41227671535,
//         Created:  Mon Oct  4 11:57:35 CEST 2010
// $Id: JetCollectionForEleHT.cc,v 1.6 2011/04/28 06:22:41 gruen Exp $
//
//


// system include files
#include <memory>

#include "../interface/JetCollectionForEleHT.h"

JetCollectionForEleHT::JetCollectionForEleHT(float minDeltaR) :
    minDeltaR_(minDeltaR) {
}

JetCollectionForEleHT::~JetCollectionForEleHT() {

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}

// ------------ method called to produce the data  ------------
std::vector<TVector3> JetCollectionForEleHT::getCleanedJets(std::vector<TVector3> selectedElectrons,
        std::vector<TVector3> theCaloJetCollection) {

    std::vector<TVector3> theFilteredCaloJetCollection;

    bool isOverlapping;

    for (unsigned int j = 0; j < theCaloJetCollection.size(); j++) {

        isOverlapping = false;
        for (unsigned int i = 0; i < selectedElectrons.size(); i++) {

            TVector3 JetP = theCaloJetCollection.at(j);
            double DR = selectedElectrons[i].DeltaR(JetP);

            if (DR < minDeltaR_) {
                isOverlapping = true;
                break;
            }
        }

        if (!isOverlapping)
            theFilteredCaloJetCollection.push_back(theCaloJetCollection.at(j));
    }

    return theFilteredCaloJetCollection;

}


