/*
 * NTupleEventReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/NTupleEventReader.h"
#include "TFile.h"
namespace BAT {

const char * NTupleEventReader::EVENT_CHAIN = "configurableAnalysis/eventB";
const char * NTupleEventReader::HLT_TRIGGER_CHAIN = "configurableAnalysis/eventB";

const boost::array<std::string, 12> NTupleEventReader::FileTypes = { { "ttbar", "ttjet", "tchan", "tW", "wj", "zj",
		"bce1", "bce2", "bce3", "enri1", "enri2", "enri3" } };

const std::string NTupleEventReader::FilePrefix = "nTuple_";

NTupleEventReader::NTupleEventReader() :
	processedEvents(0), maximalNumberOfEvents(999999999), currentEventEntry(0), numberOfFiles(0), input(new TChain(
			NTupleEventReader::EVENT_CHAIN)), hltTriggerInput(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)),
			electronReader(new ElectronReader(input)), jetReader(new JetReader(input)), muonReader(
					new MuonReader(input)), areReadersSet(false), currentEvent() {
	input->AddFriend(hltTriggerInput.get());
}

NTupleEventReader::~NTupleEventReader() {
}

void NTupleEventReader::addInputFile(const char * fileName) {
	numberOfFiles += input->Add(fileName);
	hltTriggerInput->Add(fileName);
}

const Event& NTupleEventReader::getNextEvent() {
	initiateReadersIfNotSet();
	selectNextNtupleEvent();
	currentEvent = Event();
	currentEvent.setElectrons(electronReader->getElectrons());
	currentEvent.setJets(jetReader->getJets());
	currentEvent.setMuons(muonReader->getMuons());
	currentEvent.setDataType(getDataType());
	return currentEvent;
}

void NTupleEventReader::selectNextNtupleEvent() {
	if (hasNextEvent()) {
		input->GetEntry(currentEventEntry);
		currentEventEntry++;
		processedEvents++;
	}
}

Event::DataType NTupleEventReader::getDataType() {
	std::string fileType = findCurrentFileType();
	if (fileType == "ttbar" || fileType == "ttjet")
		return Event::ttbar;
	else if (fileType == "tchan")
		return Event::singleTopTChannel;
	else if (fileType == "tW")
		return Event::singleTop_And_W;
	else if (fileType == "wj")
		return Event::Wjets;
	else if (fileType == "zj")
		return Event::Zjets;
	else if (fileType == "bce1")
		return Event::QCD_BCtoE_Pt20to30;
	else if (fileType == "bce2")
		return Event::QCD_BCtoE_Pt30to80;
	else if (fileType == "bce3")
		return Event::QCD_BCtoE_Pt80to170;
	else if (fileType == "enri1")
		return Event::QCD_EMEnriched_Pt20to30;
	else if (fileType == "enri2")
		return Event::QCD_EMEnriched_Pt30to80;
	else if (fileType == "enri3")
		return Event::QCD_EMEnriched_Pt80to170;
	else
		return Event::DATA;
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

void NTupleEventReader::initiateReadersIfNotSet() {
	if (areReadersSet == false) {
		input->SetBranchStatus("*", 0);
		hltTriggerInput->SetBranchStatus("*", 0);
		electronReader->initialise();
		jetReader->initialise();
		muonReader->initialise();
		areReadersSet = true;
	}
}

bool NTupleEventReader::hasNextEvent() {
	bool hasNextInNTuple = input->LoadTree(currentEventEntry) >= 0;
	bool isWithinEventRange = currentEventEntry < maximalNumberOfEvents;
	return hasNextInNTuple && isWithinEventRange;
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
