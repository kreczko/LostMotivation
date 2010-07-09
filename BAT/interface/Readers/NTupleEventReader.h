/*
 * NTupleEventReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef NTUPLEEVENTREADER_H_
#define NTUPLEEVENTREADER_H_
#include "../Event.h"
#include <boost/scoped_ptr.hpp>
#include "TChain.h"

namespace BAT {

class NTupleEventReader {
public:
	NTupleEventReader();
	virtual ~NTupleEventReader();
	unsigned int getNumberOfEvents();
	Event* getNextEvent();
private:
	unsigned long currentEventEntry;
	boost::scoped_ptr<TChain> input;
	boost::scoped_ptr<TChain> hltInput;
	void constructEvent();
	void selectNextNtupleEvent();
};

}

#endif /* NTUPLEEVENTREADER_H_ */
