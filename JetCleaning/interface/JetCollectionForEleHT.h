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
// $Id: JetCollectionForEleHT.h,v 1.2 2011/02/11 20:55:23 wdd Exp $
//
//


#include "TVector3.h"
#include <vector>



//
// class declaration
//

class JetCollectionForEleHT{
   public:
      explicit JetCollectionForEleHT(float minDeltaR);
      ~JetCollectionForEleHT();
      std::vector<TVector3> getCleanedJets(std::vector<TVector3> selectedElectrons, std::vector<TVector3> jets);
  
  float minDeltaR_; //min dR for jets and electrons not to match

      
      // ----------member data ---------------------------
};
