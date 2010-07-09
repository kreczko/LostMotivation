/*
 * ObjectReader.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef OBJECTREADER_H_
#define OBJECTREADER_H_
#include "TChain.h"
#include <boost/shared_ptr.hpp>

namespace BAT {

class ObjectReader {
public:
	ObjectReader();
	ObjectReader(TChain* input);
	virtual ~ObjectReader();

protected:
	boost::shared_ptr<TChain> input;
	virtual void readObject();
};

}

#endif /* OBJECTREADER_H_ */
