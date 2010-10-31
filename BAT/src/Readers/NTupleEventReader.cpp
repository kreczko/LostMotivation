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
const char * NTupleEventReader::ADDITIONAL_CHAIN = "configurableAnalysis/eventA";

Jet::Algorithm NTupleEventReader::jetAlgorithm = Jet::Calo_AntiKT_Cone05;
Electron::Algorithm NTupleEventReader::electronAlgorithm = Electron::Calo;
MET::Algorithm NTupleEventReader::metAlgorithm = MET::Calo;

const std::string NTupleEventReader::FilePrefix = "nTuple_";

NTupleEventReader::NTupleEventReader() :
    processedEvents(0),
    maximalNumberOfEvents(999999999),
    currentEventEntry(0),
    numberOfFiles(0),
    input(new TChain(NTupleEventReader::EVENT_CHAIN)),
    hltTriggerInput(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
    additionalInput(new TChain(NTupleEventReader::ADDITIONAL_CHAIN)),
    HLTPhoton10_TO20Reader(new VariableReader<bool> (additionalInput, "pass_photon10_TO20")),
    HLTPhoton15_TO20Reader(new VariableReader<bool> (additionalInput, "pass_photon15_TO20")),
    HLTPhoton15_TO20CleanedReader(new VariableReader<bool> (additionalInput, "pass_photon15clean_TO20")),
    HLTPhoton20CleanedReader(new VariableReader<double> (hltTriggerInput, "HLT_Photon20_Cleaned_L1R")),
    HLTEmulatedPhoton15Reader(new VariableReader<bool> (additionalInput, "pass_photon15")),
    HLT_Ele10_LW_L1R(new VariableReader<double>( hltTriggerInput, "HLT_Ele10_LW_L1R")),
    HLT_Ele15_SW_L1R(new VariableReader<double>( hltTriggerInput, "HLT_Ele15_SW_L1R")),
    HLT_Ele15_SW_CaloEleId_L1R(new VariableReader<double>( hltTriggerInput, "HLT_Ele15_SW_CaloEleId_L1R")),
    HLT_Ele17_SW_CaloEleId_L1R(new VariableReader<double>( hltTriggerInput, "HLT_Ele17_SW_CaloEleId_L1R")),
    HLT_Ele17_SW_TightEleId_L1R(new VariableReader<double>( hltTriggerInput, "HLT_Ele17_SW_TightEleId_L1R")),
    HLT_Ele22_SW_TighterEleId_L1R_v2(new VariableReader<double>( hltTriggerInput, "HLT_Ele22_SW_TighterEleId_L1R_v2")),
    primaryReader(new PrimaryVertexReader(input)),
    trackReader(new TrackReader(input)),
    electronReader(new ElectronReader(input, additionalInput, NTupleEventReader::electronAlgorithm)),
    jetReader(new JetReader(input, NTupleEventReader::jetAlgorithm)),
    muonReader(new MuonReader(input)),
    metReader(new METReader(input, NTupleEventReader::metAlgorithm)),
    runNumberReader(new VariableReader<unsigned int> (input, "run")),
    eventNumberReader(new VariableReader<unsigned int> (input, "event")),
    lumiBlockReader(new VariableReader<unsigned int> (input, "lumiblock")),
    areReadersSet(false),
    currentEvent(),
    seenDataTypes() {
}

NTupleEventReader::~NTupleEventReader() {
}

void NTupleEventReader::addInputFile(const char * fileName) {
    unsigned long filesAdded = input->Add(fileName, -1);
    if(filesAdded <= 0)
        throw NoFileFoundException("No file found in '" + TString(fileName) + "'");
    numberOfFiles += filesAdded;
    hltTriggerInput->Add(fileName);
    additionalInput->Add(fileName);
    seenDataTypes.at(getDataType(fileName)) = true;
}

void NTupleEventReader::addInputFileWithoutCheck(const char * fileName) {
    numberOfFiles += input->Add(fileName);
    hltTriggerInput->Add(fileName);
    additionalInput->Add(fileName);
    seenDataTypes.at(getDataType(fileName)) = true;
}

const Event& NTupleEventReader::getNextEvent() {
    selectNextNtupleEvent();
    currentEvent = Event();
    currentEvent.setDataType(getDataType(getCurrentFile()));
    currentEvent.setHLT_Photon10_TO20(HLTPhoton10_TO20Reader->getVariable());
    currentEvent.setHLT_Photon15_TO20(HLTPhoton15_TO20Reader->getVariable());
    currentEvent.setHLT_Photon15_Cleaned_TO20(HLTPhoton15_TO20CleanedReader->getVariable());
    currentEvent.setHLT_Photon20_Cleaned_L1R(HLTPhoton20CleanedReader->getVariable() >0.5);
    currentEvent.setHLT_Emulated_Photon15(HLTEmulatedPhoton15Reader->getVariable());
    currentEvent.setHLT_Ele10_LW_L1R(HLT_Ele10_LW_L1R->getVariable());
    currentEvent.setHLT_Ele15_SW_L1R(HLT_Ele15_SW_L1R->getVariable());
    currentEvent.setHLT_Ele15_SW_CaloEleId_L1R(HLT_Ele15_SW_CaloEleId_L1R->getVariable());
    currentEvent.setHLT_Ele17_SW_CaloEleId_L1R(HLT_Ele17_SW_CaloEleId_L1R->getVariable());
    currentEvent.setHLT_Ele17_SW_TightEleId_L1R(HLT_Ele17_SW_TightEleId_L1R->getVariable());
    currentEvent.setHLT_Ele22_SW_TighterEleId_L1R_v2(HLT_Ele22_SW_TighterEleId_L1R_v2->getVariable());

    currentEvent.setPrimaryVertex(primaryReader->getVertex());
    currentEvent.setTracks(trackReader->getTracks());
    currentEvent.setElectrons(electronReader->getElectrons());
    currentEvent.setJets(jetReader->getJets());
    currentEvent.setMuons(muonReader->getMuons());
    currentEvent.setMET(metReader->getMET());
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
        hltTriggerInput->GetEntry(currentEventEntry);
        additionalInput->GetEntry(currentEventEntry);
        currentEventEntry++;
        processedEvents++;
    }
}

bool NTupleEventReader::hasNextEvent() {
    if(numberOfFiles == 0)
            throw NoFileFoundException("No input file found!");
    bool hasNextInNTuple = input->LoadTree(currentEventEntry) >= 0;
    bool isWithinEventRange = currentEventEntry < maximalNumberOfEvents;
    return hasNextInNTuple && isWithinEventRange;
}

void NTupleEventReader::initiateReadersIfNotSet() {
    if (areReadersSet == false) {
        input->SetBranchStatus("*", 0);
        hltTriggerInput->SetBranchStatus("*", 0);
        additionalInput->SetBranchStatus("*", 0);
        if (HLTPhoton10_TO20Reader->doesVariableExist())
            HLTPhoton10_TO20Reader->initialise();
        if (HLTPhoton15_TO20Reader->doesVariableExist())
            HLTPhoton15_TO20Reader->initialise();
        if (HLTPhoton15_TO20CleanedReader->doesVariableExist())
            HLTPhoton15_TO20CleanedReader->initialise();
        if (HLTPhoton20CleanedReader->doesVariableExist())
            HLTPhoton20CleanedReader->initialise();
        if (HLTEmulatedPhoton15Reader->doesVariableExist())
            HLTEmulatedPhoton15Reader->initialise();
        if(HLT_Ele10_LW_L1R->doesVariableExist())
            HLT_Ele10_LW_L1R->initialise();
        if(HLT_Ele15_SW_L1R->doesVariableExist())
            HLT_Ele15_SW_L1R->initialise();
        if(HLT_Ele15_SW_CaloEleId_L1R->doesVariableExist())
            HLT_Ele15_SW_CaloEleId_L1R->initialise();
        if(HLT_Ele17_SW_CaloEleId_L1R->doesVariableExist())
            HLT_Ele17_SW_CaloEleId_L1R->initialise();
        if(HLT_Ele17_SW_TightEleId_L1R->doesVariableExist())
            HLT_Ele17_SW_TightEleId_L1R->initialise();
        if(HLT_Ele22_SW_TighterEleId_L1R_v2->doesVariableExist())
            HLT_Ele22_SW_TighterEleId_L1R_v2->initialise();
        primaryReader->initialise();
        trackReader->initialise();
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
    else if(fileType == "pj1")
        return DataType::PhotonJets_Pt40to100;
    else if(fileType == "pj2")
         return DataType::PhotonJets_Pt100to200;
    else if(fileType == "pj3")
         return DataType::PhotonJets_Pt200toInf;
    else if(fileType == "VqqJets")
        return DataType::VQQ;
    else if(fileType == "Zprime_M500GeV_W5GeV")
        return DataType::Zprime_M500GeV_W5GeV;
    else if(fileType == "Zprime_M500GeV_W50GeV")
        return DataType::Zprime_M500GeV_W50GeV;
    else if(fileType == "Zprime_M750GeV_W7500MeV")
        return DataType::Zprime_M750GeV_W7500MeV;
    else if(fileType == "Zprime_M1TeV_W10GeV")
            return DataType::Zprime_M1TeV_W10GeV;
    else if(fileType == "Zprime_M1TeV_W100GeV")
            return DataType::Zprime_M1TeV_W100GeV;
    else if(fileType == "Zprime_M1250GeV_W12500MeV")
            return DataType::Zprime_M1250GeV_W12500MeV;
    else if(fileType == "Zprime_M1500GeV_W15GeV")
            return DataType::Zprime_M1500GeV_W15GeV;
    else if(fileType == "Zprime_M1500GeV_W150GeV")
            return DataType::Zprime_M1500GeV_W150GeV;
    else if(fileType == "Zprime_M2TeV_W20GeV")
            return DataType::Zprime_M2TeV_W20GeV;
    else if(fileType == "Zprime_M2TeV_W200GeV")
            return DataType::Zprime_M2TeV_W200GeV;
    else if(fileType == "Zprime_M3TeV_W30GeV")
            return DataType::Zprime_M3TeV_W30GeV;
    else if(fileType == "Zprime_M3TeV_W300GeV")
            return DataType::Zprime_M3TeV_W300GeV;
    else if(fileType == "Zprime_M4TeV_W40GeV")
            return DataType::Zprime_M4TeV_W40GeV;
    else if(fileType == "Zprime_M4TeV_W400GeV")
            return DataType::Zprime_M4TeV_W400GeV;
    else
        return DataType::DATA;
}

std::string NTupleEventReader::findFileType(const std::string filename) {
    std::string filetype = "";

    for (unsigned int index = 0; index < DataType::names.size(); ++index) {
        const std::string searchString(NTupleEventReader::FilePrefix + DataType::names.at(index));

        if (filename.find(searchString) != std::string::npos) {
            filetype = DataType::names.at(index);
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

const char* NTupleEventReader::getCurrentFile() const {
    return input->GetCurrentFile()->GetName();
}
}
