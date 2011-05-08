#include "../interface/JetCollectionForElePlusJets.h"
#include <cmath>
#include "TLorentzVector.h"
JetCollectionForElePlusJets::JetCollectionForElePlusJets(double minJetPt, double maxAbsJetEta,
        unsigned int minNJets, float minDeltaR) :
    minJetPt_(minJetPt),
    maxAbsJetEta_(maxAbsJetEta),
    minNJets_(minNJets),
    minDeltaR_(minDeltaR) {
}

JetCollectionForElePlusJets::~JetCollectionForElePlusJets() {
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}

// ------------ method called to produce the data  ------------
// template <typename T>
std::vector<TVector3> JetCollectionForElePlusJets::getCleanedJets(std::vector<TVector3> selectedElectrons,
        std::vector<TVector3> theCaloJetCollection) {

    std::vector<TVector3> theFilteredCaloJetCollection;

    for (unsigned int i = 0; i < selectedElectrons.size(); i++) {

        for (unsigned int j = 0; j < theCaloJetCollection.size(); j++) {
            TVector3 JetP = theCaloJetCollection.at(j);
            double DR = selectedElectrons[i].DeltaR(JetP);

            if (JetP.Pt() > minJetPt_ && std::fabs(JetP.Eta()) < maxAbsJetEta_ && DR > minDeltaR_)
                theFilteredCaloJetCollection.push_back(JetP);
        }

        if (theFilteredCaloJetCollection.size() >= minNJets_)
            break;
        else
            theFilteredCaloJetCollection.clear();

    }

    return theFilteredCaloJetCollection;

}

