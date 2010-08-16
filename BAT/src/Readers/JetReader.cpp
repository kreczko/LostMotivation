/*
 * JetReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/JetReader.h"

namespace BAT {

const std::string JetReader::algorithmPrefixes[Jet::NUMBER_OF_JETALGORITHMS] = {
        "jets",
        "jetsJPTAK5",
        "jetsKT4",
        "jetsKT6",
        "PFJets",
        "jetsSC5",
        "jetsSC7" };

JetReader::JetReader() :
    numberOfJetsReader(), energyReader(), pxReader(), pyReader(), pzReader(), emfReader(), n90HitsReader(),
            fHPDReader(), btagSimpleSecondaryVertexReader(), btagTrackCountingHighPurityReader(),
            btagTrackCountingHighEfficiencyReader(), jets(), usedAlgorithm(Jet::Calo_AntiKT_Cone05) {

}
JetReader::JetReader(TChainPointer input, Jet::Algorithm algo) :
    numberOfJetsReader(input, "N" + algorithmPrefixes[algo]), energyReader(input, algorithmPrefixes[algo] + "_energy"),
            pxReader(input, algorithmPrefixes[algo] + "_px"), pyReader(input, algorithmPrefixes[algo] + "_py"),
            pzReader(input, algorithmPrefixes[algo] + "_pz"), emfReader(input, algorithmPrefixes[algo] + "_emf"),
            n90HitsReader(input, algorithmPrefixes[algo] + "_id_hitsInN90"), fHPDReader(input, algorithmPrefixes[algo]
                    + "_id_fHPD"), btagSimpleSecondaryVertexReader(input, algorithmPrefixes[algo] + "_btag_secVertex"),
            btagTrackCountingHighPurityReader(input, algorithmPrefixes[algo] + "_btag_TC_highPur"),
            btagTrackCountingHighEfficiencyReader(input, algorithmPrefixes[algo] + "_btag_TC_highEff"), jets(),
            usedAlgorithm(algo) {

}
JetReader::~JetReader() {
}

const JetCollection& JetReader::getJets() {
    if (jets.empty() == false)
        jets.clear();
    readJets();
    return jets;
}

void JetReader::readJets() {
    unsigned int numberOfJets = numberOfJetsReader.getVariable();
    for (unsigned int jetIndex = 0; jetIndex < numberOfJets; jetIndex++) {
        float energy = energyReader.getVariableAt(jetIndex);
        float px = pxReader.getVariableAt(jetIndex);
        float py = pyReader.getVariableAt(jetIndex);
        float pz = pzReader.getVariableAt(jetIndex);
        JetPointer jet(new Jet(energy, px, py, pz));
        jet->setUsedAlgorithm(usedAlgorithm);
        jet->setEMF(emfReader.getVariableAt(jetIndex));
        jet->setN90Hits(n90HitsReader.getVariableAt(jetIndex));
        jet->setFHPD(fHPDReader.getVariableAt(jetIndex));
        jet->setDiscriminatorForBtagType(btagSimpleSecondaryVertexReader.getVariableAt(jetIndex),
                BJetTagger::SimpleSecondaryVertex);
        jet->setDiscriminatorForBtagType(btagTrackCountingHighPurityReader.getVariableAt(jetIndex),
                BJetTagger::TrackCountingHighPurity);
        jet->setDiscriminatorForBtagType(btagTrackCountingHighEfficiencyReader.getVariableAt(jetIndex),
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
    n90HitsReader.initialise();
    fHPDReader.initialise();
    btagSimpleSecondaryVertexReader.initialise();
    btagTrackCountingHighPurityReader.initialise();
    btagTrackCountingHighEfficiencyReader.initialise();
}
}
