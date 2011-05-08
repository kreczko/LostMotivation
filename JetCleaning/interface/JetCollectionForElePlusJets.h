#ifndef JetCollectionForElePlusJets_h
#define JetCollectionForElePlusJets_h

/** \class JetCollectionForElePlusJets
 *
 *
 *  This class is an EDProducer implementing an HLT
 *  trigger for electron and jet objects, cutting on
 *  variables relating to the jet 4-momentum representation.
 *  The producer checks for overlaps between electrons and jets and if a
 *  combination of one electron + jets cleaned against this electrons satisfy the cuts.
 *  These jets are then added to a cleaned jet collection which is put into the event.
 *
 *  $Date: 2011/05/04 11:01:55 $
 *  $Revision: 1.0 $
 *
 *  \author Lukasz Kreczko
 *
 */


// user include files
#include "TVector3.h"
#include <vector>
//
// class declaration
//
class JetCollectionForElePlusJets{
public:
    explicit JetCollectionForElePlusJets(double minJetPt, double maxAbsJetEta, unsigned int minNJets, float minDeltaR);
    ~JetCollectionForElePlusJets();

    std::vector<TVector3> getCleanedJets(std::vector<TVector3> selectedElectrons, std::vector<TVector3> theCaloJetCollection);

    double minJetPt_; // jet pt threshold in GeV
    double maxAbsJetEta_; // jet |eta| range
    unsigned int minNJets_; // number of required jets passing cuts after cleaning

    float minDeltaR_; //min dR for jets and electrons not to match


    // ----------member data ---------------------------
};
#endif //JetCollectionForElePlusJets_h
