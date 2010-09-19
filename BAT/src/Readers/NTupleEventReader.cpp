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

Jet::Algorithm NTupleEventReader::jetAlgorithm = Jet::Calo_AntiKT_Cone05;
Electron::Algorithm NTupleEventReader::electronAlgorithm = Electron::Calo;
MET::Algorithm NTupleEventReader::metAlgorithm = MET::DEFAULT;

const boost::array<std::string, 27> NTupleEventReader::FileTypes = { {
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
        "enri3",
        "VqqJets",
        "Zprime_M500GeV_W5GeV",
        "Zprime_M500GeV_W50GeV",
        "Zprime_M750GeV_W7500MeV",
        "Zprime_M1TeV_W10GeV",
        "Zprime_M1TeV_W100GeV",
        "Zprime_M1250GeV_W12500MeV",
        "Zprime_M1500GeV_W15GeV",
        "Zprime_M1500GeV_W150GeV",
        "Zprime_M2TeV_W20GeV",
        "Zprime_M2TeV_W200GeV",
        "Zprime_M3TeV_W30GeV",
        "Zprime_M3TeV_W300GeV",
        "Zprime_M4TeV_W40GeV",
        "Zprime_M4TeV_W400GeV" } };

const std::string NTupleEventReader::FilePrefix = "nTuple_";

NTupleEventReader::NTupleEventReader() :
    processedEvents(0),
    maximalNumberOfEvents(999999999),
    currentEventEntry(0),
    numberOfFiles(0),
    input(new TChain(NTupleEventReader::EVENT_CHAIN)),
    hltTriggerInput(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
    ecalSpikeCleaningInput(new TChain(NTupleEventReader::ECAL_SPIKE_CLEANING_CHAIN)),
    HLTPhoton15Reader(new VariableReader<double> (hltTriggerInput, "HLT_Photon15_L1R")),
    HLTPhoton15CleanedReader(new VariableReader<double> (hltTriggerInput, "HLT_Photon15_Cleaned_L1R")),
    HLTPhoton20CleanedReader(new VariableReader<double> (hltTriggerInput, "HLT_Photon20_Cleaned_L1R")),
    HLTEmulatedPhoton15Reader(new VariableReader<bool> (ecalSpikeCleaningInput, "pass_photon15")),
    primaryReader(new PrimaryVertexReader(input)),
    electronReader(new ElectronReader(input, NTupleEventReader::electronAlgorithm)),
    jetReader(new JetReader(input, NTupleEventReader::jetAlgorithm)),
    muonReader(new MuonReader(input)),
    metReader(new METReader(input, NTupleEventReader::metAlgorithm)),
    runNumberReader(new VariableReader<unsigned int> (input, "run")),
    eventNumberReader(new VariableReader<unsigned int> (input, "event")),
    lumiBlockReader(new VariableReader<unsigned int> (input, "lumiblock")),
    areReadersSet(false),
    currentEvent(),
    seenDataTypes() {
    input->AddFriend(hltTriggerInput.get());
    input->AddFriend(ecalSpikeCleaningInput.get());
}

NTupleEventReader::~NTupleEventReader() {
}

void NTupleEventReader::addInputFile(const char * fileName) {
    numberOfFiles += input->Add(fileName);
    hltTriggerInput->Add(fileName);
    ecalSpikeCleaningInput->Add(fileName);
    seenDataTypes.at(getDataType(fileName)) = true;
}

const Event& NTupleEventReader::getNextEvent() {
    selectNextNtupleEvent();
    currentEvent = Event();
    currentEvent.setHLT_Photon15_L1R(HLTPhoton15Reader->getVariable() > 0);
    currentEvent.setHLT_Photon15_Cleaned_L1R(HLTPhoton15CleanedReader->getVariable() > 0);
    currentEvent.setHLT_Photon20_Cleaned_L1R(HLTPhoton20CleanedReader->getVariable() > 0);
    currentEvent.setHLT_Emulated_Photon15(HLTEmulatedPhoton15Reader->getVariable());
    currentEvent.setPrimaryVertex(primaryReader->getVertex());
    currentEvent.setElectrons(electronReader->getElectrons());
    currentEvent.setJets(jetReader->getJets());
    currentEvent.setMuons(muonReader->getMuons());
    currentEvent.setMET(metReader->getMET());
    currentEvent.setDataType(getDataType(getCurrentFile()));
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
        HLTPhoton15Reader->initialise();
        if (HLTPhoton15CleanedReader->doesVariableExist())
            HLTPhoton15CleanedReader->initialise();
        if(HLTPhoton20CleanedReader->doesVariableExist())
            HLTPhoton20CleanedReader->initialise();
        HLTEmulatedPhoton15Reader->initialise();
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

DataType::value NTupleEventReader::getDataType(const std::string filename) {
    std::string fileType = findFileType(filename);
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

std::string NTupleEventReader::findFileType(const std::string filename) {
    std::string filetype = "";
    //    const std::string nameOfCurrentFile(input->GetCurrentFile()->GetName());

    for (unsigned int index = 0; index < NTupleEventReader::FileTypes.size(); ++index) {
        const std::string searchString(NTupleEventReader::FilePrefix + NTupleEventReader::FileTypes.at(index));

        if (filename.find(searchString) != std::string::npos) {
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

const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES>& NTupleEventReader::getSeenDatatypes() {
    return seenDataTypes;
}

const char* NTupleEventReader::getCurrentFile() const{
    return input->GetCurrentFile()->GetName();
}
}
