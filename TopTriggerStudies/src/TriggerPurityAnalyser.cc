/*
 * PurityAnalyser.cpp
 *
 *  Created on: 4 Oct 2011
 *      Author: kreczko
 */

#include "TopQuarkAnalysis/TopTriggerStudies/interface/TriggerPurityAnalyser.h"

// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerPurityAnalyser::TriggerPurityAnalyser(const edm::ParameterSet& iConfig)

{
	//now do what ever initialization is needed

}

TriggerPurityAnalyser::~TriggerPurityAnalyser() {

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called for each event  ------------
void TriggerPurityAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
	using namespace edm;

}

// ------------ method called once each job just before starting event loop  ------------
void TriggerPurityAnalyser::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------
void TriggerPurityAnalyser::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void TriggerPurityAnalyser::beginRun(edm::Run const&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a run  ------------
void TriggerPurityAnalyser::endRun(edm::Run const&, edm::EventSetup const&) {
}

// ------------ method called when starting to processes a luminosity block  ------------
void TriggerPurityAnalyser::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

// ------------ method called when ending the processing of a luminosity block  ------------
void TriggerPurityAnalyser::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TriggerPurityAnalyser::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerPurityAnalyser);
