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
#include <boost/array.hpp>
#include "TChain.h"
#include "../Event.h"
#include "ElectronReader.h"
#include "JetReader.h"
#include "MuonReader.h"
#include "VariableReader.h"
#include "PrimaryVertexReader.h"
#include <string>

namespace BAT {

class NTupleEventReader {
public:
	static const char * EVENT_CHAIN;
	static const char * HLT_TRIGGER_CHAIN;
	static const char * ECAL_SPIKE_CLEANING_CHAIN;
	static const boost::array<std::string, 12> FileTypes;
	static const std::string FilePrefix;

	NTupleEventReader();
	virtual ~NTupleEventReader();
	const Event& getNextEvent();
	bool hasNextEvent();
	void addInputFile(const char* fileName);
	void addInputFile(const char* fileName, Event::DataType type);
	void skipNumberOfEvents(unsigned long skipNextNEvents);
	unsigned long getNumberOfProccessedEvents() const;
	unsigned long getCurrentLocalEventNumber() const;
	void setMaximumNumberOfEvents(unsigned long maxNumberOfEvents);
private:
	unsigned long processedEvents;
	unsigned long maximalNumberOfEvents;
	unsigned long currentEventEntry;
	unsigned long numberOfFiles;
	boost::shared_ptr<TChain> input;
	boost::shared_ptr<TChain> hltTriggerInput;
	boost::shared_ptr<TChain> ecalSpikeCleaningInput;
	boost::scoped_ptr<VariableReader<double> > HLTReader;
	boost::scoped_ptr<PrimaryVertexReader> primaryReader;
	boost::scoped_ptr<ElectronReader> electronReader;
	boost::scoped_ptr<JetReader> jetReader;
	boost::scoped_ptr<MuonReader> muonReader;

	boost::scoped_ptr<VariableReader<unsigned int> > runNumberReader;
	boost::scoped_ptr<VariableReader<unsigned int> > eventNumberReader;
	boost::scoped_ptr<VariableReader<unsigned int> > lumiBlockReader;
	bool areReadersSet;
	Event currentEvent;
	void selectNextNtupleEvent();
	void initiateReadersIfNotSet();
	Event::DataType getDataType();
	std::string findCurrentFileType();
};
}

#endif /* NTUPLEEVENTREADER_H_ */
