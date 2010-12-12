/*
 * JetReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/JetReader.h"

namespace BAT {

//const std::string JetReader::algorithmPrefixes[JetAlgorithm::NUMBER_OF_JETALGORITHMS] = {
//        "jets",
//        "jetsJPTAK5",
//        "jetsKT4",
//        "jetsKT6",
//        "PFJets",
//        "jetsSC5",
//        "jetsSC7" };

JetReader::JetReader() :
//    numberOfJetsReader(),
    energyReader(),
    pxReader(),
    pyReader(),
    pzReader(),
    massReader(),
    emfReader(),
    n90HitsReader(),
    fHPDReader(),
    NODReader(),
    CEFReader(),
    NHFReader(),
    NEFReader(),
    CHFReader(),
    NCHReader(),
    btagSimpleSecondaryVertexReader(),
    btagTrackCountingHighPurityReader(),
    btagTrackCountingHighEfficiencyReader(),
    jets(),
    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05) {

}
JetReader::JetReader(TChainPointer input, JetAlgorithm::value algo) :
//    numberOfJetsReader(input, "N" + JetAlgorithm::prefixes.at(algo)),
    energyReader(input, JetAlgorithm::prefixes.at(algo) + ".Energy"),
    pxReader(input, JetAlgorithm::prefixes.at(algo) + ".Px"),
    pyReader(input, JetAlgorithm::prefixes.at(algo) + ".Py"),
    pzReader(input, JetAlgorithm::prefixes.at(algo) + ".Pz"),
    massReader(input, JetAlgorithm::prefixes.at(algo) + ".Mass"),
    emfReader(input, JetAlgorithm::prefixes.at(algo) + ".EMF"),
    n90HitsReader(input, JetAlgorithm::prefixes.at(algo) + ".n90Hits"),
    fHPDReader(input, JetAlgorithm::prefixes.at(algo) + ".fHPD"),
    NODReader(input, JetAlgorithm::prefixes.at(algo) + ".NConstituents"),
    CEFReader(input, JetAlgorithm::prefixes.at(algo) + ".ChargedEmEnergyFraction"),
    NHFReader(input, JetAlgorithm::prefixes.at(algo) + ".NeutralHadronEnergyFraction"),
    NEFReader(input, JetAlgorithm::prefixes.at(algo) + ".NeutralEmEnergyFraction"),
    CHFReader(input, JetAlgorithm::prefixes.at(algo) + ".ChargedHadronEnergyFraction"),
    NCHReader(input, JetAlgorithm::prefixes.at(algo) + ".ChargedMultiplicity"),
    btagSimpleSecondaryVertexReader(input, JetAlgorithm::prefixes.at(algo) + ".SimpleSecondaryVertexHighEffBTag"),
//    btagSimpleSecondaryVertexReaderData(input, JetAlgorithm::prefixes.at(algo) + ".btag_ssvHE"),
    btagTrackCountingHighPurityReader(input, JetAlgorithm::prefixes.at(algo) + ".TrackCountingHighPurBTag"),
    btagTrackCountingHighEfficiencyReader(input, JetAlgorithm::prefixes.at(algo) + ".TrackCountingHighEffBTag"),
    jets(),
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
//    unsigned int numberOfJets = numberOfJetsReader.getVariable();
    for (unsigned int jetIndex = 0; jetIndex < energyReader.size(); jetIndex++) {
        float energy = energyReader.getVariableAt(jetIndex);
        float px = pxReader.getVariableAt(jetIndex);
        float py = pyReader.getVariableAt(jetIndex);
        float pz = pzReader.getVariableAt(jetIndex);
        JetPointer jet(new Jet(energy, px, py, pz));
        jet->setUsedAlgorithm(usedAlgorithm);
        jet->setMass(massReader.getVariableAt(jetIndex));
        if(usedAlgorithm == JetAlgorithm::Calo_AntiKT_Cone05 || usedAlgorithm == JetAlgorithm::JPT_AntiKt_ConeDR05){
            jet->setEMF(emfReader.getVariableAt(jetIndex));
            jet->setN90Hits(n90HitsReader.getIntVariableAt(jetIndex));
            jet->setFHPD(fHPDReader.getVariableAt(jetIndex));
        }

        jet->setDiscriminatorForBtagType(btagSimpleSecondaryVertexReader.getVariableAt(jetIndex),
                BJetTagger::SimpleSecondaryVertex);
        jet->setDiscriminatorForBtagType(btagTrackCountingHighPurityReader.getVariableAt(jetIndex),
                BJetTagger::TrackCountingHighPurity);
        jet->setDiscriminatorForBtagType(btagTrackCountingHighEfficiencyReader.getVariableAt(jetIndex),
                BJetTagger::TrackCountingHighEfficiency);
//        jet->setBtagForData(btagSimpleSecondaryVertexReaderData.getVariableAt(jetIndex));

        if (usedAlgorithm == JetAlgorithm::ParticleFlow || usedAlgorithm == JetAlgorithm::PF2PAT){
            jet->setNOD(NODReader.getIntVariableAt(jetIndex));
            jet->setCEF(CEFReader.getVariableAt(jetIndex));
            jet->setNHF(NHFReader.getVariableAt(jetIndex));
            jet->setNEF(NEFReader.getVariableAt(jetIndex));
            jet->setCHF(CHFReader.getVariableAt(jetIndex));
            jet->setNCH(NCHReader.getIntVariableAt(jetIndex));
        }
        jets.push_back(jet);
    }
}
void JetReader::initialise() {
//    numberOfJetsReader.initialise();
    energyReader.initialise();
    pxReader.initialise();
    pyReader.initialise();
    pzReader.initialise();
    massReader.initialise();
    if(usedAlgorithm == JetAlgorithm::Calo_AntiKT_Cone05 || usedAlgorithm == JetAlgorithm::JPT_AntiKt_ConeDR05){
        emfReader.initialise();
        n90HitsReader.initialise();
        fHPDReader.initialise();
    }
    btagSimpleSecondaryVertexReader.initialise();
//    btagSimpleSecondaryVertexReaderData.initialise();
    btagTrackCountingHighPurityReader.initialise();
    btagTrackCountingHighEfficiencyReader.initialise();
    if (usedAlgorithm == JetAlgorithm::ParticleFlow || usedAlgorithm == JetAlgorithm::PF2PAT) {
        NODReader.initialise();
        CEFReader.initialise();
        NHFReader.initialise();
        NEFReader.initialise();
        CHFReader.initialise();
        NCHReader.initialise();
    }
}
}
