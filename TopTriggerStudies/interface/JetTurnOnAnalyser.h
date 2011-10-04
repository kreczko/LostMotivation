/*
 * JetTurnOnAnalyser.h
 *
 *  Created on: 4 Oct 2011
 *      Author: kreczko
 */
#ifndef TopTriggerStudyJetTurnOnAnalyser
#define TopTriggerStudyJetTurnOnAnalyser
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

class JetTurnOnAnalyser : public edm::EDAnalyzer {
   public:
      explicit JetTurnOnAnalyser(const edm::ParameterSet&);
      ~JetTurnOnAnalyser();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
};

#endif

