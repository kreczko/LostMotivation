/*
 * NTupleEventReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef NTUPLEEVENTREADER_H_
#define NTUPLEEVENTREADER_H_
#include "../Event.h"
namespace BAT {

class NTupleEventReader {
public:
	NTupleEventReader();
	virtual ~NTupleEventReader();
	unsigned int getNumberOfEvents();
	Event* getNextEvent();
private:
	void constructEvent();
	void selectNextNtupleEvent();
};

}

#endif /* NTUPLEEVENTREADER_H_ */
