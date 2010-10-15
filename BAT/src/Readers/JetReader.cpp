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
    numberOfJetsReader(), energyReader(), pxReader(), pyReader(), pzReader(), massReader(), emfReader(),
            n90HitsReader(), fHPDReader(), NODReader(), CEFReader(), NHFReader(), NEFReader(), CHFReader(),
            NCHReader(), btagSimpleSecondaryVertexReader(), btagTrackCountingHighPurityReader(),
            btagTrackCountingHighEfficiencyReader(), jets(), usedAlgorithm(
                    Jet::Calo_AntiKT_Cone05) {

}
JetReader::JetReader(TChainPointer input, Jet::Algorithm algo) :
    numberOfJetsReader(input, "N" + algorithmPrefixes[algo]),
    energyReader(input, algorithmPrefixes[algo] + "_energy"),
    pxReader(input, algorithmPrefixes[algo] + "_px"),
    pyReader(input, algorithmPrefixes[algo] + "_py"),
    pzReader(input, algorithmPrefixes[algo] + "_pz"),
    massReader(input, algorithmPrefixes[algo] + "_mass"),
    emfReader(input, algorithmPrefixes[algo] + "_emf"),
    n90HitsReader(input, algorithmPrefixes[algo] + "_id_hitsInN90"),
    fHPDReader(input, algorithmPrefixes[algo] + "_id_fHPD"),
    NODReader(input, algorithmPrefixes[algo] + "_nConstituents"),
    CEFReader(input, algorithmPrefixes[algo] + "_CEF"),
    NHFReader(input, algorithmPrefixes[algo] + "_NHF"),
    NEFReader(input, algorithmPrefixes[algo] + "_NEF"),
    CHFReader(input, algorithmPrefixes[algo] + "_CHF"),
    NCHReader(input, algorithmPrefixes[algo] + "_chg_Mult"),
    btagSimpleSecondaryVertexReader(input, algorithmPrefixes[algo] + "_btag_secVertex"),
    btagSimpleSecondaryVertexReaderData(input, algorithmPrefixes[algo] + "_btag_ssvHE"),
    btagTrackCountingHighPurityReader(input, algorithmPrefixes[algo] + "_btag_TC_highPur"),
    btagTrackCountingHighEfficiencyReader(input, algorithmPrefixes[algo] + "_btag_TC_highEff"),
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
    unsigned int numberOfJets = numberOfJetsReader.getVariable();
    for (unsigned int jetIndex = 0; jetIndex < numberOfJets; jetIndex++) {
        float energy = energyReader.getVariableAt(jetIndex);
        float px = pxReader.getVariableAt(jetIndex);
        float py = pyReader.getVariableAt(jetIndex);
        float pz = pzReader.getVariableAt(jetIndex);
        JetPointer jet(new Jet(energy, px, py, pz));
        jet->setUsedAlgorithm(usedAlgorithm);
        jet->setMass(massReader.getVariableAt(jetIndex));
        jet->setEMF(emfReader.getVariableAt(jetIndex));
        jet->setN90Hits(n90HitsReader.getVariableAt(jetIndex));
        jet->setFHPD(fHPDReader.getVariableAt(jetIndex));
        jet->setDiscriminatorForBtagType(btagSimpleSecondaryVertexReader.getVariableAt(jetIndex),
                BJetTagger::SimpleSecondaryVertex);
        jet->setDiscriminatorForBtagType(btagTrackCountingHighPurityReader.getVariableAt(jetIndex),
                BJetTagger::TrackCountingHighPurity);
        jet->setDiscriminatorForBtagType(btagTrackCountingHighEfficiencyReader.getVariableAt(jetIndex),
                BJetTagger::TrackCountingHighEfficiency);
        jet->setBtagForData(btagSimpleSecondaryVertexReaderData.getVariableAt(jetIndex));
        if (usedAlgorithm == Jet::ParticleFlow){
            jet->setNOD(NODReader.getVariableAt(jetIndex));
            jet->setCEF(CEFReader.getVariableAt(jetIndex));
            jet->setNHF(NHFReader.getVariableAt(jetIndex));
            jet->setNEF(NEFReader.getVariableAt(jetIndex));
            jet->setCHF(CHFReader.getVariableAt(jetIndex));
            jet->setNCH(NCHReader.getVariableAt(jetIndex));
        }
        jets.push_back(jet);
    }
}
void JetReader::initialise() {
    numberOfJetsReader.initialise();
    energyReader.initialise();
    pxReader.initialise();
    pyReader.initialise();
    pzReader.initialise();
    massReader.initialise();
    emfReader.initialise();
    n90HitsReader.initialise();
    fHPDReader.initialise();
    btagSimpleSecondaryVertexReader.initialise();
    btagSimpleSecondaryVertexReaderData.initialise();
    btagTrackCountingHighPurityReader.initialise();
    btagTrackCountingHighEfficiencyReader.initialise();
    if (usedAlgorithm == Jet::ParticleFlow) {
        NODReader.initialise();
        CEFReader.initialise();
        NHFReader.initialise();
        NEFReader.initialise();
        CHFReader.initialise();
        NCHReader.initialise();
    }
}
}
