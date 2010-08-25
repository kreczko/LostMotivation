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
#include <vector>
#include <utility>
#include "../interface/CrossSections.h"
#include <iostream>
#include <string>
#include "../interface/Enumerators.h"

struct InterestingEvent {
    InterestingEvent(unsigned long run, unsigned long event, std::string file) :
        runNumber(run), eventNumber(event), fileName(file) {

    }
    ~InterestingEvent(){

    }
    unsigned long runNumber, eventNumber;
    std::string fileName;

    void print(){
        std::cout << "run " << runNumber << ", event " << eventNumber << std::endl;
        std::cout << "located in: " << fileName << std::endl << std::endl;
    }
};

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
    boost::shared_ptr<TH1F> h_mttbar;
    boost::shared_ptr<TH1F> h_mleptonicTop;
    boost::shared_ptr<TH1F> h_mhadronicTop;
    boost::shared_ptr<TH1F> h_mAllTop;
    boost::shared_ptr<TH1F> h_swissCrossAllEle;
    boost::shared_ptr<TFile> outputfile;
    boost::array<unsigned long, BAT::TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS> cutflow;
    boost::array<unsigned long, BAT::TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS> singleCuts;
    std::vector<InterestingEvent> interestingEvents;
    BAT::CrossSectionProvider xSections;
public:
    Analysis();
    virtual ~Analysis();
    void analyze();
    void addInputFile(const char * fileName);
    void setMaximalNumberOfEvents(long maxEvents);
    void setUsedNeutrinoSelectionForTopPairReconstruction(BAT::NeutrinoSelectionCriterion::value selection);
private:
    void printNumberOfProccessedEventsEvery(unsigned long printEvery);
    void doEcalSpikeAnalysis();
    void doDiElectronAnalysis();
    void doTTBarAnalysis();
    void doTTbarCutFlow();
    void printInterestingEvents();
    void printSummary();
    void inspectEvents();
};

#endif /* ANALYSIS_H_ */
