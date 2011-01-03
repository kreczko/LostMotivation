/*
 * NTupleEventReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/NTupleEventReader.h"
#include "TFile.h"
#include "TChainElement.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;
namespace BAT {

const char * NTupleEventReader::EVENT_CHAIN = "rootTupleTree/tree";

JetAlgorithm::value NTupleEventReader::jetAlgorithm = JetAlgorithm::Calo_AntiKT_Cone05;
ElectronAlgorithm::value NTupleEventReader::electronAlgorithm = ElectronAlgorithm::Calo;
METAlgorithm::value NTupleEventReader::metAlgorithm = METAlgorithm::Calo;
MuonAlgorithm::value NTupleEventReader::muonAlgorithm = MuonAlgorithm::Default;

const std::string NTupleEventReader::FilePrefix = "nTuple_";

NTupleEventReader::NTupleEventReader() :
    processedEvents(0),
    maximalNumberOfEvents(999999999),
    currentEventEntry(0),
    numberOfFiles(0),
    input(new TChain(NTupleEventReader::EVENT_CHAIN)),
    hltReader(new VariableReader<MultiIntPointer>(input, "HLTResults")),
    primaryReader(new PrimaryVertexReader(input)),
//    trackReader(new TrackReader(input)),
    electronReader(new ElectronReader(input, NTupleEventReader::electronAlgorithm)),
    jetReader(new JetReader(input, NTupleEventReader::jetAlgorithm)),
    muonReader(new MuonReader(input, NTupleEventReader::muonAlgorithm)),
    metReader(new METReader(input, NTupleEventReader::metAlgorithm)),
    runNumberReader(new VariableReader<unsigned int> (input, "run")),
    eventNumberReader(new VariableReader<unsigned int> (input, "event")),
    lumiBlockReader(new VariableReader<unsigned int> (input, "ls")),
    areReadersSet(false),
    areDatatypesKnown(false),
    currentEvent(),
    seenDataTypes() {
}

NTupleEventReader::~NTupleEventReader() {
}

void NTupleEventReader::addInputFile(const char * fileName) {
    unsigned long filesAdded = input->Add(fileName, -1);
    if (filesAdded <= 0)
        throw NoFileFoundException("No file found in '" + TString(fileName) + "'");
    numberOfFiles += filesAdded;
}

void NTupleEventReader::addInputFileWithoutCheck(const char * fileName) {
    numberOfFiles += input->Add(fileName);
}

const Event& NTupleEventReader::getNextEvent() {
    selectNextNtupleEvent();
    currentEvent = Event();
    currentEvent.setDataType(getDataType(getCurrentFile()));
    boost::shared_ptr<std::vector<int> > triggers(new std::vector<int>());
    std::cout << hltReader->size() << "expected: " << HLTriggers::NUMBER_OF_HLTS << endl;
    for(unsigned int i = 0; i < hltReader->size(); i++){
//        if(i == HLTriggers::NUMBER_OF_HLTS){
//            cout << endl;
//            cout << "additional entries:" << endl;
//        }
//        cout << hltReader->getIntVariableAt(i) << " ";
        triggers->push_back(hltReader->getIntVariableAt(i));
    }
    cout << endl;
    currentEvent.setHLTs(triggers);
    currentEvent.setPrimaryVertex(primaryReader->getVertex());
//    currentEvent.setTracks(trackReader->getTracks());
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
        currentEventEntry++;
        processedEvents++;
    }
}

bool NTupleEventReader::hasNextEvent() {
    if (numberOfFiles == 0)
        throw NoFileFoundException("No input file found!");
    bool hasNextInNTuple = input->LoadTree(currentEventEntry) >= 0;
    bool isWithinEventRange = currentEventEntry < maximalNumberOfEvents;
    return hasNextInNTuple && isWithinEventRange;
}

void NTupleEventReader::initiateReadersIfNotSet() {
    if (areReadersSet == false) {
        input->SetBranchStatus("*", 0);
        hltReader->initialise();
        primaryReader->initialise();
//        trackReader->initialise();
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
    else if (fileType == "pj1")
        return DataType::PhotonJets_Pt40to100;
    else if (fileType == "pj2")
        return DataType::PhotonJets_Pt100to200;
    else if (fileType == "pj3")
        return DataType::PhotonJets_Pt200toInf;
    else if (fileType == "VqqJets")
        return DataType::VQQ;
    else if (fileType == "Zprime_M500GeV_W5GeV")
        return DataType::Zprime_M500GeV_W5GeV;
    else if (fileType == "Zprime_M500GeV_W50GeV")
        return DataType::Zprime_M500GeV_W50GeV;
    else if (fileType == "Zprime_M750GeV_W7500MeV")
        return DataType::Zprime_M750GeV_W7500MeV;
    else if (fileType == "Zprime_M1TeV_W10GeV")
        return DataType::Zprime_M1TeV_W10GeV;
    else if (fileType == "Zprime_M1TeV_W100GeV")
        return DataType::Zprime_M1TeV_W100GeV;
    else if (fileType == "Zprime_M1250GeV_W12500MeV")
        return DataType::Zprime_M1250GeV_W12500MeV;
    else if (fileType == "Zprime_M1500GeV_W15GeV")
        return DataType::Zprime_M1500GeV_W15GeV;
    else if (fileType == "Zprime_M1500GeV_W150GeV")
        return DataType::Zprime_M1500GeV_W150GeV;
    else if (fileType == "Zprime_M2TeV_W20GeV")
        return DataType::Zprime_M2TeV_W20GeV;
    else if (fileType == "Zprime_M2TeV_W200GeV")
        return DataType::Zprime_M2TeV_W200GeV;
    else if (fileType == "Zprime_M3TeV_W30GeV")
        return DataType::Zprime_M3TeV_W30GeV;
    else if (fileType == "Zprime_M3TeV_W300GeV")
        return DataType::Zprime_M3TeV_W300GeV;
    else if (fileType == "Zprime_M4TeV_W40GeV")
        return DataType::Zprime_M4TeV_W40GeV;
    else if (fileType == "Zprime_M4TeV_W400GeV")
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
    if (areDatatypesKnown == false) {
        readDataTypes();
        areDatatypesKnown = true;
    }
    return seenDataTypes;
}

void NTupleEventReader::readDataTypes() {
    TIter nextFile(input->GetListOfFiles());
    TChainElement* file = 0;
    while ((file = (TChainElement*) nextFile()) != 0) {
        string fileName = file->GetTitle();
        DataType::value type = getDataType(fileName);
        seenDataTypes.at(type) = true;
    }
}

const char* NTupleEventReader::getCurrentFile() const {
    return input->GetCurrentFile()->GetName();
}
}
