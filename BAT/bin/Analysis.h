/*
 * Analysis.h
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#ifndef ANALYSIS_H_
#define ANALYSIS_H_
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "../interface/Readers/NTupleEventReader.h"
#include "../interface/Filter.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "../interface/Selection.h"
#include "../interface/Event.h"
#include "../interface/TopPairEventCandidate.h"

class Analysis {
private:
	boost::scoped_ptr<BAT::NTupleEventReader> eventReader;
	boost::scoped_ptr<BAT::Filter> eventFilter;
	BAT::Event currentEvent;
	BAT::TopPairEventCandidate ttbarCandidate;
	unsigned long numberOfGoodElectrons;
	boost::shared_ptr<TDirectory> testingDirectory;
	boost::shared_ptr<TH1F> h_et;
	boost::shared_ptr<TH1F> h_diElectronMass;
	boost::shared_ptr<TH2F> h_ptRel_vs_DRmin;
	boost::shared_ptr<TFile> outputfile;
	boost::array<unsigned long, BAT::TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS> cutflow;
	boost::array<unsigned long, BAT::TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS> singleCuts;
public:
	Analysis();
	virtual ~Analysis();
	void analyze();
	void addInputFile(const char * fileName);
	void setMaximalNumberOfEvents(long maxEvents);
private:
	void printNumberOfProccessedEventsEvery(unsigned long printEvery);
	void doDiElectronAnalysis();
	void doTTBarAnalysis();
	void doTTbarCutFlow();
	void printSummary();
};

#endif /* ANALYSIS_H_ */
