/*
 * JetReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/JetReader.h"

namespace BAT {

JetReader::JetReader() :
	numberOfJetsReader(), energyReader(), pxReader(), pyReader(), pzReader(), emfReader(),
			btagSimpleSecondaryVertexReader(), btagTrackCountingHighPurityReader(),
			btagTrackCountingHighEfficiencyReader(), jets() {

}
JetReader::JetReader(boost::shared_ptr<TChain> input) :
	numberOfJetsReader(input, "Njets"), energyReader(input, "jets_energy"), pxReader(input, "jets_px"), pyReader(input,
			"jets_py"), pzReader(input, "jets_pz"), emfReader(input, "jets_emf"), btagSimpleSecondaryVertexReader(
			input, "jets_btag_secVertex"), btagTrackCountingHighPurityReader(input, "jets_btag_TC_highPur"),
			btagTrackCountingHighEfficiencyReader(input, "jets_btag_TC_highEff"), jets() {

}
JetReader::~JetReader() {
}

std::vector<Jet> JetReader::getJets() {
	if (jets.empty() == false)
		jets.clear();
	readJets();
	return jets;
}

void JetReader::readJets() {
	unsigned int numberOfJets = numberOfJetsReader.getVariable();
	for (unsigned int jetIndex = 0; jetIndex < numberOfJets; jetIndex++) {
		float energy = energyReader.getVariable()->at(jetIndex);
		float px = pxReader.getVariable()->at(jetIndex);
		float py = pyReader.getVariable()->at(jetIndex);
		float pz = pzReader.getVariable()->at(jetIndex);
		Jet jet(energy, px, py, pz);
		jet.setEMF(emfReader.getVariable()->at(jetIndex));
		jet.setDiscriminatorForBtagType(btagSimpleSecondaryVertexReader.getVariable()->at(jetIndex),
				BJetTagger::SimpleSecondaryVertex);
		jet.setDiscriminatorForBtagType(btagTrackCountingHighPurityReader.getVariable()->at(jetIndex),
				BJetTagger::TrackCountingHighPurity);
		jet.setDiscriminatorForBtagType(btagTrackCountingHighEfficiencyReader.getVariable()->at(jetIndex),
				BJetTagger::TrackCountingHighEfficiency);
		jets.push_back(jet);
	}
}
void JetReader::initialise() {
	numberOfJetsReader.initialise();
	energyReader.initialise();
	pxReader.initialise();
	pyReader.initialise();
	pzReader.initialise();
	emfReader.initialise();
	btagSimpleSecondaryVertexReader.initialise();
	btagTrackCountingHighPurityReader.initialise();
	btagTrackCountingHighEfficiencyReader.initialise();
}
}
