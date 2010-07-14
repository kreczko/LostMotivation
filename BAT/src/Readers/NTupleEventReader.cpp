/*
 * NTupleEventReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/Readers/NTupleEventReader.h"

namespace BAT {
const char * NTupleEventReader::EVENT_CHAIN = "configurableAnalysis/eventB";
const char * NTupleEventReader::HLT_TRIGGER_CHAIN = "configurableAnalysis/eventB";

NTupleEventReader::NTupleEventReader() :
	numberOfEvents(0), currentEventEntry(0), numberOfFiles(0), input(new TChain(NTupleEventReader::EVENT_CHAIN)),
			hltTriggerInput(new TChain(NTupleEventReader::HLT_TRIGGER_CHAIN)), electronReader(new ElectronReader(input)), areReadersSet(false) {
	input->AddFriend(hltTriggerInput.get());
}

NTupleEventReader::~NTupleEventReader() {
}

void NTupleEventReader::addInputFile(const char * fileName) {
	numberOfFiles += input->Add(fileName);
	hltTriggerInput->Add(fileName);
}

Event* NTupleEventReader::getNextEvent() {
	initiateReadersIfNotSet();
	selectNextNtupleEvent();
	Event* event = new Event();
	event->addElectrons(electronReader->getElectrons());
	return event;
}

void NTupleEventReader::selectNextNtupleEvent() {
	if (currentEventEntry < getNumberOfEvents()) {
		input->GetEntry(currentEventEntry);
		currentEventEntry++;
	}
}

unsigned long NTupleEventReader::getNumberOfEvents() {
	initateNumberOfEventsIfNotSet();
	return numberOfEvents;
}

void NTupleEventReader::initateNumberOfEventsIfNotSet() {
	if (numberOfEvents == 0) {
		numberOfEvents = input->GetEntries();
	}
}

void NTupleEventReader::initiateReadersIfNotSet() {
	if (areReadersSet == false) {
		electronReader->initialise();
		areReadersSet = true;
	}
}

}
