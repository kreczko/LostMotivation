/*
 * NTupleEventReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/NTupleEventReader.h"
#include "TFile.h"
#include <iostream>
using namespace std;
namespace BAT {

const char * NTupleEventReader::EVENT_CHAIN = "configurableAnalysis/eventB";
const char * NTupleEventReader::HLT_TRIGGER_CHAIN = "configurableAnalysis/eventV";
const char * NTupleEventReader::ECAL_SPIKE_CLEANING_CHAIN = "configurableAnalysis/eventA";

const boost::array<std::string, 12> NTupleEventReader::FileTypes = { {
        "ttbar",
        "ttjet",
        "tchan",
        "tW",
        "wj",
        "zj",
        "bce1",
        "bce2",
        "bce3",
        "enri1",
        "enri2",
        "enri3" } };

const std::string NTupleEventReader::FilePrefix = "nTuple_";

NTupleEventReader::NTupleEventReader() :
    processedEvents(0), maximalNumberOfEvents(999999999), currentEventEntry(0), numberOfFiles(0), input(new TChain(
            NTupleEventReader::EVENT_CHAIN)), hltTriggerInput(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
            ecalSpikeCleaningInput(new TChain(NTupleEventReader::ECAL_SPIKE_CLEANING_CHAIN)), HLTReader(
                    new VariableReader<double> (hltTriggerInput, "HLT_Photon15_L1R")), primaryReader(
                    new PrimaryVertexReader(input)), electronReader(new ElectronReader(input)), jetReader(
                    new JetReader(input)), muonReader(new MuonReader(input)), metReader(new METReader(input)),
            runNumberReader(new VariableReader<unsigned int> (input, "run")), eventNumberReader(new VariableReader<
                    unsigned int> (input, "event")), lumiBlockReader(new VariableReader<unsigned int> (input,
                    "lumiblock")), areReadersSet(false), currentEvent() {
    input->AddFriend(hltTriggerInput.get());
    input->AddFriend(ecalSpikeCleaningInput.get());
}

NTupleEventReader::~NTupleEventReader() {
}
//TODO: implement algorithms, throw exception if they are set AFTER initialisation of readers

void NTupleEventReader::addInputFile(const char * fileName) {
    numberOfFiles += input->Add(fileName);
    hltTriggerInput->Add(fileName);
    ecalSpikeCleaningInput->Add(fileName);
}

const Event& NTupleEventReader::getNextEvent() {
    selectNextNtupleEvent();
    currentEvent = Event();
    currentEvent.setHLT_Photon15_L1R(HLTReader->getVariable() > 0);
    currentEvent.setPrimaryVertex(primaryReader->getVertex());
    currentEvent.setElectrons(electronReader->getElectrons());
    currentEvent.setJets(jetReader->getJets());
    currentEvent.setMuons(muonReader->getMuons());
    currentEvent.setMET(metReader->getMET());
    currentEvent.setDataType(getDataType());
    currentEvent.setRunNumber(runNumberReader->getVariable());
    currentEvent.setEventNumber(eventNumberReader->getVariable());
    currentEvent.setLocalEventNumber(currentEventEntry);
    currentEvent.setLumiBlock(lumiBlockReader->getVariable());
    return currentEvent;
}

void NTupleEventReader::selectNextNtupleEvent() {
    if (hasNextEvent()) {
        initiateReadersIfNotSet();
        input->GetEntry(currentEventEntry);
        currentEventEntry++;
        processedEvents++;
    }
}

bool NTupleEventReader::hasNextEvent() {
    bool hasNextInNTuple = input->LoadTree(currentEventEntry) >= 0;
    bool isWithinEventRange = currentEventEntry < maximalNumberOfEvents;
    return hasNextInNTuple && isWithinEventRange;
}

void NTupleEventReader::initiateReadersIfNotSet() {
    if (areReadersSet == false) {
        input->SetBranchStatus("*", 0);
        hltTriggerInput->SetBranchStatus("*", 0);
        ecalSpikeCleaningInput->SetBranchStatus("*", 0);
        HLTReader->initialise();
        primaryReader->initialise();
        electronReader->initialise();
        jetReader->initialise();
        muonReader->initialise();
        metReader->initialise();
        runNumberReader->initialise();
        eventNumberReader->initialise();
        lumiBlockReader->initialise();
        areReadersSet = true;
    }
}

DataType::value NTupleEventReader::getDataType() {
    std::string fileType = findCurrentFileType();
    if (fileType == "ttbar" || fileType == "ttjet")
        return DataType::ttbar;
    else if (fileType == "tchan")
        return DataType::singleTopTChannel;
    else if (fileType == "tW")
        return DataType::singleTop_And_W;
    else if (fileType == "wj")
        return DataType::Wjets;
    else if (fileType == "zj")
        return DataType::Zjets;
    else if (fileType == "bce1")
        return DataType::QCD_BCtoE_Pt20to30;
    else if (fileType == "bce2")
        return DataType::QCD_BCtoE_Pt30to80;
    else if (fileType == "bce3")
        return DataType::QCD_BCtoE_Pt80to170;
    else if (fileType == "enri1")
        return DataType::QCD_EMEnriched_Pt20to30;
    else if (fileType == "enri2")
        return DataType::QCD_EMEnriched_Pt30to80;
    else if (fileType == "enri3")
        return DataType::QCD_EMEnriched_Pt80to170;
    else
        return DataType::DATA;
}

std::string NTupleEventReader::findCurrentFileType() {
    std::string filetype = "";
    const std::string nameOfCurrentFile(input->GetCurrentFile()->GetName());

    for (unsigned int index = 0; index < NTupleEventReader::FileTypes.size(); ++index) {
        const std::string searchString(NTupleEventReader::FilePrefix + NTupleEventReader::FileTypes.at(index));

        if (nameOfCurrentFile.find(searchString) != std::string::npos) {
            filetype = NTupleEventReader::FileTypes.at(index);
        }
    }
    return filetype;
}

unsigned long NTupleEventReader::getNumberOfProccessedEvents() const {
    return processedEvents;
}

unsigned long NTupleEventReader::getCurrentLocalEventNumber() const {
    return currentEventEntry;
}

void NTupleEventReader::skipNumberOfEvents(unsigned long skipNextNEvents) {
    currentEventEntry += skipNextNEvents;
}

void NTupleEventReader::setMaximumNumberOfEvents(unsigned long maxNumberOfEvents) {
    maximalNumberOfEvents = maxNumberOfEvents;
}
}
