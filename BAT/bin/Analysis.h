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
#include <boost/unordered_map.hpp>
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
#include "../interface/HistHelpers/HistogramManager.h"

struct InterestingEvent {
    InterestingEvent(unsigned long run, unsigned long event, std::string file) :
        candidate(), runNumber(run), eventNumber(event), fileName(file) {

    }

    InterestingEvent(BAT::TopPairEventCandidate cand, std::string file) :
        candidate(cand), runNumber(cand.runnumber()), eventNumber(cand.eventnumber()), fileName(file) {

    }
    ~InterestingEvent() {

    }
    BAT::TopPairEventCandidate candidate;
    unsigned long runNumber, eventNumber;
    std::string fileName;

    void print() {
        std::cout << "run " << candidate.runnumber() << ", event " << candidate.eventnumber() << " (Mttbar: "
                << candidate.mttbar() << ")" << std::endl;
        std::cout << "located in: " << fileName << std::endl << std::endl;
    }
};
typedef boost::array<unsigned long, BAT::TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS> cutarray;
typedef boost::unordered_map<std::string, cutarray> cutmap;

class Analysis {
private:
    boost::scoped_ptr<BAT::NTupleEventReader> eventReader;
    boost::scoped_ptr<BAT::Filter> eventFilter;
    BAT::Event currentEvent;
    BAT::TopPairEventCandidate ttbarCandidate;
    BAT::HistogramManager histMan;
//    boost::shared_ptr<TDirectory> testingDirectory;
//    boost::shared_ptr<TH1F> h_et;
//    boost::shared_ptr<TH1F> h_diElectronMass;
//    boost::shared_ptr<TH2F> h_ptRel_vs_DRmin;
//    boost::shared_ptr<TH1F> h_mttbar;
//    boost::shared_ptr<TH1F> h_mleptonicTop;
//    boost::shared_ptr<TH1F> h_mhadronicTop;
//    boost::shared_ptr<TH1F> h_mAllTop;
//    boost::shared_ptr<TH1F> h_swissCrossAllEle;
//    boost::shared_ptr<TH1F> h_m3, h_ttbar_pt, h_HT, h_numberOfJets, h_numberOfBJets, h_met, h_leadingJetMass, h_mtW,
//            h_electronD0, h_electronD0_iso, h_neutrino_pz;
//    boost::shared_ptr<TFile> outputfile;
    cutarray cutflow;
    cutarray singleCuts;
    cutmap cutflowPerFile;
    cutmap singleCutsPerFile;
    std::vector<InterestingEvent> interestingEvents;
    BAT::CrossSectionProvider weights;
    float weight;
public:
    static float luminosity;
    Analysis();
    virtual ~Analysis();
    void analyze();
    void addInputFile(const char * fileName);
    void setMaximalNumberOfEvents(long maxEvents);
    void setUsedNeutrinoSelectionForTopPairReconstruction(BAT::NeutrinoSelectionCriterion::value selection);
    static void useJetAlgorithm(BAT::Jet::Algorithm algo) {
        BAT::NTupleEventReader::jetAlgorithm = algo;
    }
    static void useElectronAlgorithm(BAT::Electron::Algorithm algo) {
        BAT::NTupleEventReader::electronAlgorithm = algo;
    }
    static void useMETAlgorithm(BAT::MET::Algorithm algo) {
        BAT::NTupleEventReader::metAlgorithm = algo;
    }
private:
    void printNumberOfProccessedEventsEvery(unsigned long printEvery);
//    void doEcalSpikeAnalysis();
    void doDiElectronAnalysis();
    void doTTBarAnalysis();
    void doTTbarCutFlow();
    void doSynchExercise();
    void printInterestingEvents();
    void printSummary();
    void inspectEvents();
    void createHistograms();
};

#endif /* ANALYSIS_H_ */
