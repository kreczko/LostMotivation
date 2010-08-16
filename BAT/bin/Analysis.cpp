/*
 * Analysis.cpp
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#include "Analysis.h"
#include "TROOT.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>
#include "../interface/EventCounter.h"

using namespace BAT;
using namespace std;

void Analysis::analyze() {
    while (eventReader->hasNextEvent()) {
        printNumberOfProccessedEventsEvery(10000);
        currentEvent = eventReader->getNextEvent();
        ttbarCandidate = TopPairEventCandidate(currentEvent);
        doTTbarCutFlow();
        doDiElectronAnalysis();
        doTTBarAnalysis();
    }
    printSummary();
}

void Analysis::printNumberOfProccessedEventsEvery(unsigned long printEvery) {
    unsigned long eventIndex = eventReader->getNumberOfProccessedEvents();
    if (eventIndex % printEvery == 0)
        cout << "Analysing event no " << eventIndex << endl;
}

void Analysis::doTTbarCutFlow() {
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        if (ttbarCandidate.passesSelectionStep((TTbarEPlusJetsSelection::Step) cut)) {
            singleCuts[cut] += 1;
        }

        if (ttbarCandidate.passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) cut)) {
            cutflow[cut] += 1;
        }
    }
}
void Analysis::doDiElectronAnalysis() {
    ElectronCollection electrons = currentEvent.getGoodElectrons();
    if (electrons.size() == 2) {
        numberOfGoodElectrons += 2;
        ElectronPointer leadingElectron = electrons.front();
        ElectronPointer secondElectron = electrons.at(1);
        cout << "charge:" << leadingElectron->charge() << endl;
        h_et->Fill(leadingElectron->et());
        h_diElectronMass->Fill(leadingElectron->invariantMass(secondElectron));
    }
}

void Analysis::doTTBarAnalysis() {
    if (ttbarCandidate.passesFullTTbarEPlusJetSelection()) {
        ElectronPointer isolatedElectron = currentEvent.getGoodIsolatedElectrons().front();
        JetCollection jets = currentEvent.getGoodJets();
        unsigned int closestID = isolatedElectron->getClosestJetID(jets);
        float minDR = isolatedElectron->deltaR(jets.at(closestID));
        float ptRel = isolatedElectron->relativePtTo(jets.at(closestID));
        h_ptRel_vs_DRmin->Fill(minDR, ptRel);
    }
}

void Analysis::printSummary() {
    cout << "finished analysis, number of good leading electrons: " << numberOfGoodElectrons << endl;
    cout << "total number of processed events: " << eventReader->getNumberOfProccessedEvents() << endl;
    cout << endl;
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        cout << "Selection step '" << TTbarEPlusJetsSelection::StringSteps[cut] << "'" << endl;
        cout << "passed events (single cut): " << singleCuts.at(cut) << endl;
        if (cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS)
            cout << "passed events (up to this cut):" << cutflow.at(cut) << endl;
        else
            cout << "passed events (full selection):" << cutflow.at(cut) << endl;
        cout << endl;
    }
}

Analysis::Analysis() :
    eventReader(new NTupleEventReader()), eventFilter(Filter::makeTopPairEPlusJetsFilter()), currentEvent(),
            ttbarCandidate(), numberOfGoodElectrons(0), testingDirectory(gROOT->mkdir("testing")), h_et(new TH1F(
                    "histname", "histtitle", 100, 0, 100)), h_diElectronMass(new TH1F("diElectronMass",
                    "diElectronMass", 500, 0, 500)), h_ptRel_vs_DRmin(new TH2F("ptRel_vs_DRmin", "ptRel_vs_DRmin", 100,
                    0, 1, 300, 0, 300)), outputfile(new TFile("egammaAnalysis.root", "RECREATE")) {
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        cutflow[cut] = 0;
        singleCuts[cut] = 0;
    }
}

Analysis::~Analysis() {
    outputfile->mkdir(testingDirectory->GetName())->cd();
    h_et->Write();
    h_diElectronMass->Write();
    h_ptRel_vs_DRmin->Write();
    testingDirectory->Write();
    outputfile->Write();
    outputfile->Close();
}

void Analysis::addInputFile(const char* fileName) {
    eventReader->addInputFile(fileName);
}

void Analysis::setMaximalNumberOfEvents(long maxEvents) {
    if (maxEvents > 0) {
        eventReader->setMaximumNumberOfEvents(maxEvents);
    }
}
