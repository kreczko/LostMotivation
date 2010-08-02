/*
 * Analysis.h
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#ifndef ANALYSIS_H_
#define ANALYSIS_H_
#include <boost/scoped_ptr.hpp>
#include "../interface/Readers/NTupleEventReader.h"
#include "../interface/Filter.h"

class Analysis {
private:
	boost::scoped_ptr<BAT::NTupleEventReader> eventReader;
	boost::scoped_ptr<BAT::Filter> eventFilter;
public:
	Analysis();
	virtual ~Analysis();
	void analyze();
	void addInputFile(const char * fileName);
};

#endif /* ANALYSIS_H_ */
