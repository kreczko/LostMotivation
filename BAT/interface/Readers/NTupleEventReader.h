/*
 * NTupleEventReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef NTUPLEEVENTREADER_H_
#define NTUPLEEVENTREADER_H_
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "TChain.h"
#include "../Event.h"
#include "ElectronReader.h"

namespace BAT {

class NTupleEventReader {
	static const char * EVENT_CHAIN;
	static const char * HLT_TRIGGER_CHAIN;
public:
	NTupleEventReader();
	virtual ~NTupleEventReader();
	unsigned long getNumberOfEvents();
	Event* getNextEvent();
	void addInputFile(const char* fileName);
	void addInputFile(const char* fileName, Event::DataType type);
private:
	unsigned long numberOfEvents;
	unsigned long currentEventEntry;
	unsigned long numberOfFiles;
	boost::shared_ptr<TChain> input;
	boost::shared_ptr<TChain> hltTriggerInput;
	boost::scoped_ptr<ElectronReader> electronReader;
	bool areReadersSet;
	void selectNextNtupleEvent();
	void initateNumberOfEventsIfNotSet();
	void initiateReadersIfNotSet();
};
}

#endif /* NTUPLEEVENTREADER_H_ */
