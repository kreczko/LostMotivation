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
#include <math.h>

using namespace BAT;
using namespace std;
float Analysis::luminosity = 7.22;

void Analysis::analyze() {
    createHistograms();
    cout << "detected samples:" << endl;
    for (unsigned int sample = 0; sample < DataType::NUMBER_OF_DATA_TYPES; ++sample) {
        if (eventReader->getSeenDatatypes()[sample])
            cout << DataType::names[sample] << endl;
    }
    while (eventReader->hasNextEvent()) {
        printNumberOfProccessedEventsEvery(100000);
        initiateEvent();
        inspectEvents();
        //        doEcalSpikeAnalysis();
        //                doSynchExercise();
        doTTbarCutFlow();
        doDiElectronAnalysis();
        doTTBarAnalysis();
        doNotePlots();
        doQCDStudy();
    }
    printInterestingEvents();
    printSummary();
}

void Analysis::printNumberOfProccessedEventsEvery(unsigned long printEvery) {
    unsigned long eventIndex = eventReader->getNumberOfProccessedEvents();
    if (eventIndex % printEvery == 0)
        cout << "Analysing event no " << eventIndex << endl;
}

void Analysis::initiateEvent() {
    currentEvent = eventReader->getNextEvent();
    ttbarCandidate = TopPairEventCandidate(currentEvent);
    weight = weights.getWeight(currentEvent.getDataType());
    histMan.setCurrentDataType(ttbarCandidate.getDataType());
    histMan.setCurrentJetBin(currentEvent.GoodJets().size());
    histMan.setCurrentBJetBin(currentEvent.GoodBJets().size());
}

void Analysis::inspectEvents() {
    std::vector<InterestingEvent> eventsToInspect;

    for (unsigned int index = 0; index < eventsToInspect.size(); ++index) {
        if ((ttbarCandidate.runnumber() == eventsToInspect.at(index).runNumber && ttbarCandidate.eventnumber()
                == eventsToInspect.at(index).eventNumber)) {
            cout << "file: " << eventReader->getCurrentFile() << endl;
            ttbarCandidate.inspect();
        }
    }

}

void Analysis::doSynchExercise() {
    if (ttbarCandidate.passesSelectionStepUpTo(TTbarEPlusJetsSelection::ConversionFinder)) {
        ElectronPointer electron = ttbarCandidate.GoodIsolatedElectrons().front();
        cout << ttbarCandidate.runnumber() << ":" << ttbarCandidate.eventnumber() << ":" << endl;//electron->et() << endl;
        if (ttbarCandidate.eventnumber() == 450622) {
            ttbarCandidate.inspect();
        }
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
            unsigned int njet = ttbarCandidate.GoodJets().size();
            if (njet >= JetBin::NUMBER_OF_JET_BINS)
                njet = JetBin::NUMBER_OF_JET_BINS - 1;
            cutflowPerSample.increase(ttbarCandidate.getDataType(), cut, njet, weight);
        }
    }
}
void Analysis::doDiElectronAnalysis() {
    ElectronCollection electrons = currentEvent.GoodElectrons();
    if (electrons.size() == 2) {
        ElectronPointer leadingElectron = electrons.front();
        ElectronPointer secondElectron = electrons.at(1);
        histMan.H1D_JetBinned("diElectronMass")->Fill(leadingElectron->invariantMass(secondElectron), weight);
    }
}

void Analysis::doTTBarAnalysis() {
    if (ttbarCandidate.passesNMinus1(TTbarEPlusJetsSelection::AtLeastFourGoodJets)) {
        histMan.H1D("numberOfJets")->Fill(ttbarCandidate.GoodJets().size());
    }

    if (ttbarCandidate.passesSelectionStepUpTo(TTbarEPlusJetsSelection::GoodPrimaryvertex)
            && ttbarCandidate.hasNoIsolatedMuon() && ttbarCandidate.isNotAZBosonEvent()
            && ttbarCandidate.hasAtLeastFourGoodJets()) {
        const ElectronCollection coll = ttbarCandidate.Electrons();
        for (unsigned int index = 0; index < coll.size(); ++index) {
            const ElectronPointer electron = coll.at(index);
            bool passesEt = electron->et() > Electron::goodElectronMinimalEt;
            bool passesEta = fabs(electron->superClusterEta()) < Electron::goodElectronMaximalAbsoluteEta
                    && electron->isInCrack() == false;
            bool passesID = electron->VBTF_W70_ElectronID();
            //            bool isNotEcalSpike = electron->isEcalSpike() == false;
            bool noConversion = electron->isFromConversion() == false;
            if (passesEt && passesEta && passesID && noConversion) {
                histMan.H1D("electronD0")->Fill(electron->d0(), weight);
            }
        }
    }
    if (ttbarCandidate.passesFullTTbarEPlusJetSelection()) {
        histMan.H1D("numberOfBJets")->Fill(ttbarCandidate.GoodBJets().size(), weight);
        ttbarCandidate.reconstructUsingChi2(ttbarCandidate.GoodIsolatedElectrons().front());
        histMan.H1D("mLeptonicTop")->Fill(ttbarCandidate.getLeptonicTop()->mass(), weight);
        histMan.H1D("mHadronicTop")->Fill(ttbarCandidate.getHadronicTop()->mass(), weight);
        histMan.H1D("mAllTop")->Fill(ttbarCandidate.getLeptonicTop()->mass(), weight);
        histMan.H1D("mAllTop")->Fill(ttbarCandidate.getHadronicTop()->mass(), weight);

        histMan.H1D("MET")->Fill(ttbarCandidate.MET()->et(), weight);
        histMan.H1D("HT")->Fill(ttbarCandidate.fullHT(), weight);
        histMan.H1D("leadingJetMass")->Fill(ttbarCandidate.GoodJets().front()->mass(), weight);
        histMan.H1D("mtW")->Fill(ttbarCandidate.transverseWmass(ttbarCandidate.GoodIsolatedElectrons().front()), weight);
        histMan.H1D("m3")->Fill(ttbarCandidate.M3(), weight);

        const ParticlePointer resonance = ttbarCandidate.getRessonance();
        double mttbar = ttbarCandidate.mttbar();
        histMan.H1D("mttbar")->Fill(mttbar, weight);
        histMan.H1D_BJetBinned("mttbar")->Fill(mttbar, weight);

        if (ttbarCandidate.MET()->et() < 20) {
            histMan.H1D("mttbar_QCDEnriched")->Fill(mttbar, weight);
            histMan.H1D_BJetBinned("mttbar_QCDEnriched")->Fill(mttbar, weight);
            histMan.H1D("ttbar_pt_QCDEnriched")->Fill(resonance->pt());
        }

        histMan.H1D("ttbar_pt")->Fill(resonance->pt(), weight);
        histMan.H1D("ttbar_px")->Fill(resonance->px(), weight);
        histMan.H1D("ttbar_py")->Fill(resonance->py(), weight);
        histMan.H1D("ttbar_pz")->Fill(resonance->pz(), weight);
        histMan.H1D("electron_et")->Fill(ttbarCandidate.getElectronFromWDecay()->et(), weight);
        histMan.H1D("neutrino_pz")->Fill(ttbarCandidate.getNeutrinoFromWDecay()->pz(), weight);
        if(ttbarCandidate.MET()->pt() > 20){
        	if(ttbarCandidate.GoodJets().front()->pt() > 70 && ttbarCandidate.GoodJets().at(1)->pt() > 50){

        	}
        }
        if (mttbar != mttbar) {//isnan
            ttbarCandidate.inspectReconstructedEvent();
        }
        if (ttbarCandidate.isRealData()) {
            cout << "run " << ttbarCandidate.runnumber() << ", event " << ttbarCandidate.eventnumber() << ", lumi "
                    << ttbarCandidate.lumiblock();
            cout << ", top pair invariant mass = " << mttbar << " GeV" << endl;
            interestingEvents .push_back(InterestingEvent(ttbarCandidate, eventReader->getCurrentFile()));

            if (resonance->pt() > 100) {
                cout << "top pair pt = " << resonance->pt() << " GeV" << endl;
                ttbarCandidate.inspect();
                ttbarCandidate.inspectReconstructedEvent();
            }
        }

    }
}

void Analysis::doNotePlots() {
    if (ttbarCandidate.GoodElectrons().size() >= 1 && ttbarCandidate.Jets().size() >= 2) {
        const ElectronCollection electrons = ttbarCandidate.GoodElectrons();
        ElectronCollection nonConversionElectrons;
        for (unsigned int index = 0; index < electrons.size(); ++index) {
            const ElectronPointer electron = electrons.at(index);
            if (electron->isFromConversion() == false) {
                ConversionTagger tagger = ConversionTagger();
                tagger.calculateConversionVariables(electron, ttbarCandidate.Tracks(), 3.8, 0.45);
                if (tagger.isFromConversion(0.02, 0.02) == false)
                    nonConversionElectrons.push_back(electron);
            }
        }
        if (nonConversionElectrons.size() == 1) {
            const ElectronPointer electron = nonConversionElectrons.front();
            JetCollection goodjets;
            for (unsigned index = 0; index < ttbarCandidate.Jets().size(); ++index) {
                if (ttbarCandidate.Jets().at(index)->isGood())
                    goodjets.push_back(ttbarCandidate.Jets().at(index));
            }
            if (goodjets.size() >= 2) {
                unsigned int closestID = electron->getClosestJetID(goodjets);
                float minDR = electron->deltaR(goodjets.at(closestID));
                float ptRel = electron->relativePtTo(goodjets.at(closestID));
                histMan.H2D("ptRel_vs_DRmin")->Fill(minDR, ptRel, weight);
                if (ttbarCandidate.MET()->et() < 20 && ttbarCandidate.transverseWmass(electron) < 35) {
                    histMan.H1D("DRmin_QCDenriched")->Fill(minDR, weight);
                    histMan.H1D("ptRel_QCDenriched")->Fill(ptRel, weight);
                } else if (ttbarCandidate.MET()->et() > 30 && ttbarCandidate.transverseWmass(electron) > 50) {
                    histMan.H1D("DRmin_WZenriched")->Fill(minDR, weight);
                    histMan.H1D("ptRel_WZenriched")->Fill(ptRel, weight);
                }
            }
        }

    }
}

void Analysis::doQCDStudy() {
    if (ttbarCandidate.passesRelIsoSelection()) {
        const ElectronPointer electron = ttbarCandidate.MostIsolatedElectron();
        histMan.H1D_JetBinned("QCDest_CombRelIso")->Fill(electron->relativeIsolation(), weight);
        if (ttbarCandidate.GoodBJets().size() >= 1)
            histMan.H1D_JetBinned("QCDest_CombRelIso_1btag")->Fill(electron->relativeIsolation(), weight);
        if (ttbarCandidate.GoodBJets().size() >= 2)
            histMan.H1D_JetBinned("QCDest_CombRelIso_2btag")->Fill(electron->relativeIsolation(), weight);
    }

    if (ttbarCandidate.passesQCDSelection()) {
        const ElectronPointer electron = ttbarCandidate.MostIsolatedElectron();
        histMan.H1D_JetBinned("QCDest_CombRelIso_controlRegion")->Fill(electron->relativeIsolation(), weight);
        if (ttbarCandidate.GoodBJets().size() >= 1)
            histMan.H1D_JetBinned("QCDest_CombRelIso_controlRegion_1btag")->Fill(electron->relativeIsolation(), weight);
        if (ttbarCandidate.GoodBJets().size() >= 2)
            histMan.H1D_JetBinned("QCDest_CombRelIso_controlRegion_2btag")->Fill(electron->relativeIsolation(), weight);
    }

    if (ttbarCandidate.passesRelIsoSelection() && ttbarCandidate.hasAtLeastFourGoodJets()) {
        const ElectronPointer electron = ttbarCandidate.MostIsolatedElectron();
        if (electron->isIsolated() == false && !isnan(electron->relativeIsolation()) && !isinf(
                electron->relativeIsolation())) {
            cout << "QCD: electron et: " << electron->et() << endl;
            try {
                ttbarCandidate.reconstructUsingChi2(electron);
                const ParticlePointer resonance = ttbarCandidate.getRessonance();
                histMan.H1D("mttbar_controlRegion")->Fill(resonance->mass(), weight);
            } catch (ReconstructionException& e) {
                cout << "Could not reconstruct event: " << e.what() << endl;
            }
        }
    }

    if (ttbarCandidate.passesConversionSelection()) {
        const ElectronPointer electron = ttbarCandidate.GoodIsolatedElectrons().front();
        if (electron->pt() < 10000 && !isnan(electron->relativeIsolation()) && !isinf(
                electron->relativeIsolation())) {
            cout << "QCD: electron et: " << electron->et() << endl;
            try {
                ttbarCandidate.reconstructUsingChi2(electron);
                const ParticlePointer resonance = ttbarCandidate.getRessonance();
                histMan.H1D("mttbar_conversions")->Fill(resonance->mass(), weight);
            } catch (ReconstructionException& e) {
                cout << "Could not reconstruct event: " << e.what() << endl;
            }

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

void Analysis::createHistograms() {
    histMan.setCurrentLumi(Analysis::luminosity);
    histMan.prepareForSeenDataTypes(eventReader->getSeenDatatypes());
    histMan.addH1D("electron_et", "electron_et", 500, 0, 500);
    histMan.addH1D_JetBinned("diElectronMass", "diElectronMass", 1000, 0, 1000);
    histMan.addH1D("mttbar", "mttbar", 5000, 0, 5000);
    histMan.addH1D("mttbar_QCDEnriched", "mttbar", 5000, 0, 5000);
    histMan.addH1D("mttbar_controlRegion", "mttbar", 5000, 0, 5000);
    histMan.addH1D("mttbar_conversions", "mttbar", 5000, 0, 5000);
    histMan.addH1D_BJetBinned("mttbar", "mttbar", 5000, 0, 5000);
    histMan.addH1D_BJetBinned("mttbar_QCDEnriched", "mttbar", 5000, 0, 5000);
    histMan.addH1D_BJetBinned("mttbar_controlRegion", "mttbar", 5000, 0, 5000);
    histMan.addH1D("mLeptonicTop", "mLeptonicTop", 500, 0, 500);
    histMan.addH1D("mHadronicTop", "mHadronicTop", 500, 0, 500);
    histMan.addH1D("mAllTop", "mAllTop", 500, 0, 500);
    histMan.addH1D("m3", "m3", 5000, 0, 5000);
    histMan.addH1D("ttbar_pt", "ttbar_pt", 5000, 0, 5000);
    histMan.addH1D("ttbar_px", "ttbar_px", 5000, 0, 5000);
    histMan.addH1D("ttbar_py", "ttbar_py", 5000, 0, 5000);
    histMan.addH1D("ttbar_pz", "ttbar_pz", 5000, 0, 5000);
    histMan.addH1D("ttbar_pt_QCDEnriched", "ttbar_pt", 5000, 0, 5000);
    histMan.addH1D("HT", "HT", 5000, 0, 5000);
    histMan.addH1D("numberOfJets", "numberOfJets", 10, 0, 10);
    histMan.addH1D("numberOfBJets", "numberOfBJets", 10, 0, 10);
    histMan.addH1D("MET", "MET", 5000, 0, 5000);
    histMan.addH1D("leadingJetMass", "leadingJetMass", 200, 0, 200);
    histMan.addH1D("mtW", "mtW", 600, 0, 600);
    histMan.addH1D("electronD0", "electronD0", 1000, 0, 0.2);
    histMan.addH1D("neutrino_pz", "neutrino_pz", 1000, -500, 500);
    histMan.addH2D("ptRel_vs_DRmin", "ptRel_vs_DRmin", 100, 0, 1, 300, 0, 300);
    histMan.addH1D("ptRel_QCDenriched", "ptRel_QCDenriched", 300, 0, 300);
    histMan.addH1D("DRmin_QCDenriched", "DRmin_QCDenriched", 100, 0, 1);
    histMan.addH1D("ptRel_WZenriched", "ptRel_WZenriched", 300, 0, 300);
    histMan.addH1D("DRmin_WZenriched", "DRmin_WZenriched", 100, 0, 1);
    histMan.addH1D_JetBinned("QCDest_CombRelIso", "RelIso", 1000, 0, 10);
    histMan.addH1D_JetBinned("QCDest_CombRelIso_controlRegion", "RelIso control region", 1000, 0, 10);
    histMan.addH1D_JetBinned("QCDest_CombRelIso_1btag", "RelIso (>=1 btag)", 1000, 0, 10);
    histMan.addH1D_JetBinned("QCDest_CombRelIso_controlRegion_1btag", "RelIso control region", 1000, 0, 10);
    histMan.addH1D_JetBinned("QCDest_CombRelIso_2btag", "RelIso (>=2 btag)", 1000, 0, 10);
    histMan.addH1D_JetBinned("QCDest_CombRelIso_controlRegion_2btag", "RelIso control region", 1000, 0, 10);
}

Analysis::Analysis() :
    eventReader(new NTupleEventReader()), eventFilter(Filter::makeTopPairEPlusJetsFilter()), currentEvent(),
            ttbarCandidate(), histMan(), cutflow(), singleCuts(), cutflowPerFile(), singleCutsPerFile(),
            interestingEvents(), weights(Analysis::luminosity/*current lumi*/), weight(0), cutflowPerSample(
                    DataType::NUMBER_OF_DATA_TYPES, TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS,
                    JetBin::NUMBER_OF_JET_BINS) {
    //    outputfile->SetCompressionLevel(7);
    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        cutflow[cut] = 0;
        singleCuts[cut] = 0;
    }
}

Analysis::~Analysis() {
    histMan.writeToDisk();
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

