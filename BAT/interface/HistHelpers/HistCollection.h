/*
 * HistCollection.h
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#ifndef HISTCOLLECTION_H_
#define HISTCOLLECTION_H_
#include "boost/scoped_ptr.hpp"
#include "TFile.h"
#include "TDirectory.h"
#include "TMap.h"

namespace BAT {

template<typename histType>
class HistCollection {
public:
	HistCollection() :
		histogramFile(0), directories(0) {

	}

	HistCollection(TFile* file) :
		histogramFile(file), directories(0) {

	}

	~HistCollection() {
	}
	void mkdir(TString directory);
	void mkdir(TString parentDirectory, TString directory);
	void cd(TString directory);

	void setDataType(unsigned int dataType);

private:
	boost::scoped_ptr<TFile> histogramFile;
	boost::scoped_ptr<TMap> directories;
};

}

#endif /* HISTCOLLECTION_H_ */
