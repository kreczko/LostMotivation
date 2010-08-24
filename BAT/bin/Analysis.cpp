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
#include <cmath>

using namespace BAT;
using namespace std;

void Analysis::analyze() {
    while (eventReader->hasNextEvent()) {
        printNumberOfProccessedEventsEvery(10000);
        currentEvent = eventReader->getNextEvent();
        ttbarCandidate = TopPairEventCandidate(currentEvent);
        inspectEvents();
        doEcalSpikeAnalysis();
        doTTbarCutFlow();
        doDiElectronAnalysis();
        doTTBarAnalysis();

    }
    printInterestingEvents();
    printSummary();
}

void Analysis::printNumberOfProccessedEventsEvery(unsigned long printEvery) {
    unsigned long eventIndex = eventReader->getNumberOfProccessedEvents();
    if (eventIndex % printEvery == 0)
        cout << "Analysing event no " << eventIndex << endl;
}

void Analysis::inspectEvents() {
    if ((ttbarCandidate.runnumber() == 142558 && ttbarCandidate.eventnumber() == 99024502)) {
        cout << "file: " << eventReader->getCurrentFile() << endl;
        ttbarCandidate.inspect();
    }

}

void Analysis::doEcalSpikeAnalysis(){
    const ElectronCollection electrons = currentEvent.getElectrons();
    for(unsigned short index = 0; index < electrons.size(); ++index){
        const ElectronPointer electron = electrons.at(index);
        h_swissCrossAllEle->Fill(electron->swissCross());
    }
}

void Analysis::doTTbarCutFlow() {
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        if (ttbarCandidate.passesSelectionStep((TTbarEPlusJetsSelection::Step) cut)) {
            singleCuts[cut] += 1;
            if ((ttbarCandidate.runnumber() == 142558 && ttbarCandidate.eventnumber() == 99024502))
                cout << "passes cut " << cut << endl;
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

        ttbarCandidate.reconstructUsingChi2();
        h_mleptonicTop->Fill(ttbarCandidate.getLeptonicTop()->mass());
        h_mhadronicTop->Fill(ttbarCandidate.getHadronicTop()->mass());
        h_mAllTop->Fill(ttbarCandidate.getLeptonicTop()->mass());
        h_mAllTop->Fill(ttbarCandidate.getHadronicTop()->mass());
        double mttbar = ttbarCandidate.mttbar();
        h_mttbar->Fill(mttbar);
        const ParticlePointer ressonance = ttbarCandidate.getRessonance();
        if (std::isnan(mttbar)) {
            ttbarCandidate.inspectReconstructedEvent();
        }
        if (mttbar > 700) {
            cout << "run " << ttbarCandidate.runnumber() << ", event " << ttbarCandidate.eventnumber() << endl;
            cout << "top pair invariant mass=" << mttbar << endl;
        }

        if(ttbarCandidate.getLeptonicTop()->mass() <= 0 || ttbarCandidate.getHadronicTop()->mass() <=0){
            ttbarCandidate.inspectReconstructedEvent();
        }

        interestingEvents .push_back(InterestingEvent(ttbarCandidate.runnumber(), ttbarCandidate.eventnumber(),
                eventReader->getCurrentFile()));
    }
}

void Analysis::printInterestingEvents() {
    for (unsigned int index = 0; index < interestingEvents.size(); ++index) {
        interestingEvents.at(index).print();
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
                    "electron_et", "electron_et", 100, 0, 100)), h_diElectronMass(new TH1F("diElectronMass",
                    "diElectronMass", 500, 0, 500)), h_ptRel_vs_DRmin(new TH2F("ptRel_vs_DRmin", "ptRel_vs_DRmin", 100,
                    0, 1, 300, 0, 300)), h_mttbar(new TH1F("mttbar", "mttbar", 5000, 0, 5000)), h_mleptonicTop(
                    new TH1F("mLeptonicTop", "mLeptonicTop", 500, 0, 500)), h_mhadronicTop(new TH1F("mHadronicTop",
                    "mHadronicTop", 500, 0, 500)), h_mAllTop(new TH1F("mAllTop", "mAllTop", 500, 0, 500)),
            h_swissCrossAllEle(new TH1F("swissCross", "swissCross", 200, -1, 1)), outputfile(new TFile(
                    "egammaAnalysis.root", "RECREATE")), cutflow(), singleCuts(), interestingEvents(), xSections() {
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
    h_mttbar->Write();
    h_mleptonicTop->Write();
    h_mhadronicTop->Write();
    h_mAllTop->Write();
    h_swissCrossAllEle->Write();
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
