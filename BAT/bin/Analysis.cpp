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
        printNumberOfProccessedEventsEvery(100000);
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
    std::vector<InterestingEvent> eventsToInspect;
        eventsToInspect.push_back(InterestingEvent(144112, 1793794380, ""));
        eventsToInspect.push_back(InterestingEvent(144112, 2019949875, ""));
        eventsToInspect.push_back(InterestingEvent(144011, 176799946, ""));
        eventsToInspect.push_back(InterestingEvent(144086, 282508280, ""));
        eventsToInspect.push_back(InterestingEvent(144112, 194482467, ""));
        eventsToInspect.push_back(InterestingEvent(144112, 210965064, ""));
        eventsToInspect.push_back(InterestingEvent(144112, 338800668, ""));
        eventsToInspect.push_back(InterestingEvent(144112, 200726415, ""));
        eventsToInspect.push_back(InterestingEvent(144089, 200726415, ""));

    for (unsigned int index = 0; index < eventsToInspect.size(); ++index) {
        if ((ttbarCandidate.runnumber() == eventsToInspect.at(index).runNumber && ttbarCandidate.eventnumber()
                == eventsToInspect.at(index).eventNumber)) {
            cout << "file: " << eventReader->getCurrentFile() << endl;
            ttbarCandidate.inspect();
        }
    }

}

void Analysis::doEcalSpikeAnalysis() {
    const ElectronCollection electrons = currentEvent.getElectrons();
    for (unsigned short index = 0; index < electrons.size(); ++index) {
        const ElectronPointer electron = electrons.at(index);
        h_swissCrossAllEle->Fill(electron->swissCross());
    }
}

void Analysis::doTTbarCutFlow() {
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        if (ttbarCandidate.passesSelectionStep((TTbarEPlusJetsSelection::Step) cut)) {
            ++singleCuts[cut];
            singleCutsPerFile[eventReader->getCurrentFile()][cut]++;
        }

        if (ttbarCandidate.passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) cut)) {
            cutflow[cut] += 1;
            cutflowPerFile[eventReader->getCurrentFile()][cut]++;
        }
    }
}
void Analysis::doDiElectronAnalysis() {
    ElectronCollection electrons = currentEvent.getGoodElectrons();
    if (electrons.size() == 2) {
        numberOfGoodElectrons += 2;
        ElectronPointer leadingElectron = electrons.front();
        ElectronPointer secondElectron = electrons.at(1);
        h_diElectronMass->Fill(leadingElectron->invariantMass(secondElectron));
    }
}

void Analysis::doTTBarAnalysis() {
    if (ttbarCandidate.passesNMinus1(TTbarEPlusJetsSelection::AtLeastFourGoodJets)) {
        h_numberOfJets->Fill(ttbarCandidate.getGoodJets().size());
    }

    if (ttbarCandidate.passesSelectionStepUpTo(TTbarEPlusJetsSelection::GoodPrimaryvertex)
            && ttbarCandidate.hasNoIsolatedMuon() && ttbarCandidate.isNotAZBosonEvent()
            && ttbarCandidate.hasAtLeastFourGoodJets()) {
        const ElectronCollection coll = ttbarCandidate.getElectrons();
        for (unsigned int index = 0; index < coll.size(); ++index) {
            const ElectronPointer electron = coll.at(index);
            bool passesEt = electron->et() > Electron::goodElectronMinimalEt;
            bool passesEta = fabs(electron->superClusterEta()) < Electron::goodElectronMaximalAbsoluteEta
                    && electron->isInCrack() == false;
            bool passesID = electron->VBTF_W70_ElectronID();
            bool isNotEcalSpike = electron->isEcalSpike() == false;
            bool noConversion = electron->isFromConversion() == false;
            if (passesEt && passesEta && passesID && isNotEcalSpike && noConversion) {
                h_electronD0->Fill(electron->d0());
                if (electron->isIsolated())
                    h_electronD0->Fill(electron->d0());
            }
        }
    }
    if (ttbarCandidate.passesFullTTbarEPlusJetSelection()) {
        ElectronPointer isolatedElectron = currentEvent.getGoodIsolatedElectrons().front();
        JetCollection jets = currentEvent.getGoodJets();
        unsigned int closestID = isolatedElectron->getClosestJetID(jets);
        float minDR = isolatedElectron->deltaR(jets.at(closestID));
        float ptRel = isolatedElectron->relativePtTo(jets.at(closestID));
        h_ptRel_vs_DRmin->Fill(minDR, ptRel);
        h_numberOfBJets->Fill(ttbarCandidate.getGoodBJets().size());
        ttbarCandidate.reconstructUsingChi2();
        h_mleptonicTop->Fill(ttbarCandidate.getLeptonicTop()->mass());
        h_mhadronicTop->Fill(ttbarCandidate.getHadronicTop()->mass());
        h_mAllTop->Fill(ttbarCandidate.getLeptonicTop()->mass());
        h_mAllTop->Fill(ttbarCandidate.getHadronicTop()->mass());

        h_met->Fill(ttbarCandidate.getMET()->et());
        h_HT->Fill(ttbarCandidate.fullHT());
        h_leadingJetMass->Fill(ttbarCandidate.getGoodJets().front()->mass());
        h_mtW->Fill(ttbarCandidate.transverseWmass());
        h_m3->Fill(ttbarCandidate.M3());

        const ParticlePointer ressonance = ttbarCandidate.getRessonance();
        double mttbar = ttbarCandidate.mttbar();
        h_mttbar->Fill(mttbar);
        h_ttbar_pt->Fill(ressonance->pt());
        h_et->Fill(ttbarCandidate.getElectronFromWDecay()->et());
        h_neutrino_pz->Fill(ttbarCandidate.getNeutrinoFromWDecay()->pz());

        if (std::isnan(mttbar)) {
            ttbarCandidate.inspectReconstructedEvent();
        }
        if (ttbarCandidate.isRealData()) {
            cout << "run " << ttbarCandidate.runnumber() << ", event " << ttbarCandidate.eventnumber() << endl;
            cout << "top pair invariant mass=" << mttbar << endl;
            interestingEvents .push_back(InterestingEvent(ttbarCandidate, eventReader->getCurrentFile()));
        }
    }
}

void Analysis::printInterestingEvents() {
    cout << "Interesting events:" << endl;
    for (unsigned int index = 0; index < interestingEvents.size(); ++index) {
        interestingEvents.at(index).print();
    }
}

void Analysis::printSummary() {
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
                    "electron_et", "electron_et", 500, 0, 500)), h_diElectronMass(new TH1F("diElectronMass",
                    "diElectronMass", 1000, 0, 1000)), h_ptRel_vs_DRmin(new TH2F("ptRel_vs_DRmin", "ptRel_vs_DRmin",
                    100, 0, 1, 300, 0, 300)), h_mttbar(new TH1F("mttbar", "mttbar", 5000, 0, 5000)), h_mleptonicTop(
                    new TH1F("mLeptonicTop", "mLeptonicTop", 500, 0, 500)), h_mhadronicTop(new TH1F("mHadronicTop",
                    "mHadronicTop", 500, 0, 500)), h_mAllTop(new TH1F("mAllTop", "mAllTop", 500, 0, 500)),
            h_swissCrossAllEle(new TH1F("swissCross", "swissCross", 200, -1, 1)), h_m3(new TH1F("m3", "m3", 5000, 0,
                    5000)), h_ttbar_pt(new TH1F("ttbar_pt", "ttbar_pt", 5000, 0, 5000)), h_HT(new TH1F("HT", "HT",
                    5000, 0, 5000)), h_numberOfJets(new TH1F("numberOfJets", "numberOfJets", 10, 0, 10)),
            h_numberOfBJets(new TH1F("numberOfBJets", "numberOfBJets", 10, 0, 10)), h_met(new TH1F("MET", "MET", 5000,
                    0, 5000)), h_leadingJetMass(new TH1F("leadingJetMass", "leadingJetMass", 200, 0, 200)), h_mtW(
                    new TH1F("mtW", "mtW", 600, 0, 600)), h_electronD0(new TH1F("electronD0", "electronD0", 1000, 0,
                    0.2)), h_electronD0_iso(new TH1F("electronD0_iso", "electronD0", 1000, 0, 0.2)), h_neutrino_pz(
                    new TH1F("neutrino_pz", "neutrino_pz", 1000, -500, 500)), outputfile(new TFile(
                    "egammaAnalysis.root", "RECREATE")), cutflow(), singleCuts(), cutflowPerFile(),
            singleCutsPerFile(), interestingEvents(), xSections() {
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        cutflow[cut] = 0;
        singleCuts[cut] = 0;
    }
}

Analysis::~Analysis() {
    boost::shared_ptr<TH1F> h_mttbar_rebinned((TH1F*) h_mttbar->Clone("mttbar_rebinned"));
    boost::shared_ptr<TH1F> h_mleptonicTop_rebinned((TH1F*) h_mleptonicTop->Clone("mleptonicTop_rebinned"));
    boost::shared_ptr<TH1F> h_mhadronicTop_rebinned((TH1F*) h_mhadronicTop->Clone("mhadronicTop_rebinned"));
    boost::shared_ptr<TH1F> h_mAllTop_rebinned((TH1F*) h_mAllTop->Clone("mAllTop_rebinned"));
    h_mttbar_rebinned->Rebin(50);
    h_mleptonicTop_rebinned->Rebin(20);
    h_mhadronicTop_rebinned->Rebin(20);
    h_mAllTop_rebinned->Rebin(20);
    outputfile->mkdir(testingDirectory->GetName())->cd();
    h_et->Write();
    h_diElectronMass->Write();
    h_ptRel_vs_DRmin->Write();
    h_mttbar->Write();
    h_mleptonicTop->Write();
    h_mhadronicTop->Write();
    h_mAllTop->Write();
    h_m3->Write();
    h_ttbar_pt->Write();
    h_HT->Write();
    h_numberOfJets->Write();
    h_numberOfBJets->Write();
    h_met->Write();
    h_leadingJetMass->Write();
    h_mtW->Write();
    h_electronD0->Write();
    h_electronD0_iso->Write();
    h_neutrino_pz->Write();

    h_mttbar_rebinned->Write();
    h_mleptonicTop_rebinned->Write();
    h_mhadronicTop_rebinned->Write();
    h_mAllTop_rebinned->Write();

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

void Analysis::setUsedNeutrinoSelectionForTopPairReconstruction(NeutrinoSelectionCriterion::value selection) {
    TopPairEventCandidate::usedNeutrinoSelection = selection;
}
