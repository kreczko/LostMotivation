/*
 * TopPairEventCandidate.cpp
 *
 *  Created on: 9 Jul 2010
 *      Author: kreczko
 */

#include "../interface/TopPairEventCandidate.h"
#include "../interface/Taggers/BJetTagger.h"
#include <iostream>
#include <iomanip>
using namespace std;
namespace BAT {

double const TopPairEventCandidate::matched_angle = 0.945666;
double const TopPairEventCandidate::matched_angle_sigma = 0.311091;
double const TopPairEventCandidate::matched_leptonic_top_mass = 178.377;
double const TopPairEventCandidate::matched_leptonic_top_mass_sigma = 31.050;
double const TopPairEventCandidate::matched_hadronic_W_mass = 89.9153;
double const TopPairEventCandidate::matched_hadronic_W_mass_sigma = 13.8711;
double const TopPairEventCandidate::matched_hadronic_top_mass = 182.191;
double const TopPairEventCandidate::matched_hadronic_top_mass_sigma = 22.1484;
double const TopPairEventCandidate::matched_ptratio = 0.18552;
double const TopPairEventCandidate::matched_ptratio_sigma = 0.401973;
double const TopPairEventCandidate::matched_pt_ttbarSystem = 0.0760939;
double const TopPairEventCandidate::matched_pt_ttbarSystem_sigma = 0.0700391;
double const TopPairEventCandidate::matched_HTSystem = 1;
double const TopPairEventCandidate::matched_HTSystem_sigma = 0.1;
double const TopPairEventCandidate::W_mass = 80.389;

NeutrinoSelectionCriterion::value TopPairEventCandidate::usedNeutrinoSelection = NeutrinoSelectionCriterion::chi2;

TopPairEventCandidate::TopPairEventCandidate() :
    Event(), electronFromW(), leptonicBJet(), hadronicBJet(), jet1FromW(), jet2FromW(), neutrino1(), neutrino2(),
            leptonicW1(), leptonicW2(), hadronicW(), leptonicTop1(), leptonicTop2(), hadronicTop(),
            selectedNeutrino(0), currentSelectedNeutrino(0), hadronicBIndex(0), leptonicBIndex(0), jet1FromWIndex(0),
            jet2FromWIndex(0), doneReconstruction(false), conversionTagger(new ConversionTagger()),
            doneConversionTagging(false) {
}

TopPairEventCandidate::TopPairEventCandidate(const Event& event) :
    Event(event), electronFromW(), leptonicBJet(), hadronicBJet(), jet1FromW(), jet2FromW(), neutrino1(), neutrino2(),
            leptonicW1(), leptonicW2(), hadronicW(), leptonicTop1(), leptonicTop2(), hadronicTop(),
            selectedNeutrino(0), currentSelectedNeutrino(0), hadronicBIndex(0), leptonicBIndex(0), jet1FromWIndex(0),
            jet2FromWIndex(0), doneReconstruction(false), conversionTagger(new ConversionTagger()),
            doneConversionTagging(false) {

}

TopPairEventCandidate::~TopPairEventCandidate() {
}

bool TopPairEventCandidate::passesScrapingFilter() const {
    if (tracks.size() > 10) {
        if (numberOfHighPurityTracks / (1.0 * tracks.size()) > 0.25)
            return true;
        else
            return false;
    } else
        return true;
}

bool TopPairEventCandidate::passesHighLevelTrigger() const {
    if (isRealData()) {
        if (runNumber < 137029)
            return HLT_Photon10_TO20;
        else if (runNumber >= 137029 && runNumber < 140042)
            return HLT_Photon15_TO20;
        else if (runNumber >= 140042 && runNumber < 141900)
            return HLT_Photon15_Cleaned_TO20;
        else if (runNumber >= 141900)
            return HLT_Photon20_Cleaned_L1R;
        else
            return false;
    } else
        return HLT_Emulated_Photon15;
}

bool TopPairEventCandidate::hasOneGoodPrimaryVertex() const {
    if (isRealData())
        return primaryVertex.isGoodInRealData();
    else
        return primaryVertex.isGood();
}

bool TopPairEventCandidate::hasOnlyOneGoodIsolatedElectron() const {
    return goodIsolatedElectrons.size() == 1;
}

bool TopPairEventCandidate::isolatedElectronDoesNotComeFromConversion() const {
    if (goodIsolatedElectrons.size() > 0)
        return goodIsolatedElectrons.front()->isFromConversion() == false;
    else
        return false;
}

bool TopPairEventCandidate::isolatedElectronNotTaggedAsFromConversion() const{
    if (goodIsolatedElectrons.size() > 0) {
        if (doneConversionTagging == false) {
            conversionTagger->calculateConversionVariables(goodIsolatedElectrons.front(), tracks, 3.8, 0.45);
        }
        return conversionTagger->isFromConversion(0.02, 0.02) == false;

    } else
        return false;

}

bool TopPairEventCandidate::hasNoIsolatedMuon() const {
    return goodIsolatedMuons.size() == 0;
}

bool TopPairEventCandidate::hasAtLeastOneGoodJet() const {
    return goodJets.size() >= 1;
}

bool TopPairEventCandidate::hasAtLeastTwoGoodJets() const {
    return goodJets.size() >= 2;
}

bool TopPairEventCandidate::hasAtLeastThreeGoodJets() const {
    return goodJets.size() >= 3;
}

bool TopPairEventCandidate::hasAtLeastFourGoodJets() const {
    return goodJets.size() >= 4;
}

bool TopPairEventCandidate::isNotAZBosonEvent() const {
    float invariantMass = 0;
    if (goodIsolatedElectrons.size() == 2)
        invariantMass = goodIsolatedElectrons.at(0)->invariantMass(goodIsolatedElectrons.at(1));
    else if (goodIsolatedElectrons.size() == 1 && looseElectrons.size() > 0)
        invariantMass = goodIsolatedElectrons.front()->invariantMass(looseElectrons.front());

    bool passesLowerLimit = invariantMass >= 76;
    bool passesUpperLimit = invariantMass <= 106;
    return (passesLowerLimit && passesUpperLimit) == false;
}

bool TopPairEventCandidate::passesFullTTbarEPlusJetSelection() const {
    unsigned int newstep = (int) TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS - 1;
    return passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) newstep);
}

bool TopPairEventCandidate::passesSelectionStepUpTo(enum TTbarEPlusJetsSelection::Step step) const {
    if (step == TTbarEPlusJetsSelection::FilterOutScraping)
        return passesSelectionStep(step);
    else {
        unsigned int newstep = (int) step - 1;
        return passesSelectionStep(step) && passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) newstep);
    }
}

bool TopPairEventCandidate::passesNMinus1(enum TTbarEPlusJetsSelection::Step omitted) const {
    bool passes(true);

    for (unsigned int cut = 0; cut < TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS; ++cut) {
        if (cut == (unsigned int) omitted)
            continue;
        passes = passes && passesSelectionStep((TTbarEPlusJetsSelection::Step) cut);
    }
    return passes;
}

bool TopPairEventCandidate::passesSelectionStep(enum TTbarEPlusJetsSelection::Step step) const {
    switch (step) {
    case TTbarEPlusJetsSelection::FilterOutScraping:
        return passesScrapingFilter();
    case TTbarEPlusJetsSelection::HighLevelTrigger:
        return passesHighLevelTrigger();
    case TTbarEPlusJetsSelection::GoodPrimaryvertex:
        return hasOneGoodPrimaryVertex();
    case TTbarEPlusJetsSelection::OneIsolatedElectron:
        return hasOnlyOneGoodIsolatedElectron();
    case TTbarEPlusJetsSelection::ConversionRejection:
        return isolatedElectronDoesNotComeFromConversion();
    case TTbarEPlusJetsSelection::ConversionFinder:
        return isolatedElectronNotTaggedAsFromConversion();
    case TTbarEPlusJetsSelection::LooseMuonVeto:
        return hasNoIsolatedMuon();
    case TTbarEPlusJetsSelection::AtLeastFourGoodJets:
        return hasAtLeastFourGoodJets();
    case TTbarEPlusJetsSelection::Zveto:
        return isNotAZBosonEvent();
    default:
        return false;
    }
}

void TopPairEventCandidate::reconstructUsingChi2() {
    if (goodJets.size() < 4)
        throw ReconstructionException("Not enough jets available to reconstruct top event using Chi2 method.");
    electronFromW = goodIsolatedElectrons.front();
    reconstructNeutrinos();

    double chosen_Chi2Total(9999999.);

    for (unsigned short hadBindex = 0; hadBindex < goodJets.size(); ++hadBindex) {
        for (unsigned short lepBindex = 0; lepBindex < goodJets.size(); ++lepBindex) {
            if (lepBindex == hadBindex)
                continue;
            for (unsigned short jet1Index = 0; jet1Index < goodJets.size(); ++jet1Index) {
                if (jet1Index == lepBindex || jet1Index == hadBindex)
                    continue;
                for (unsigned short jet2Index = 0; jet2Index < goodJets.size(); ++jet2Index) {
                    if (jet2Index == jet1Index || jet2Index == lepBindex || jet2Index == hadBindex)
                        continue;
                    hadronicBJet = goodJets.at(hadBindex);
                    leptonicBJet = goodJets.at(lepBindex);
                    jet1FromW = goodJets.at(jet1Index);
                    jet2FromW = goodJets.at(jet2Index);

                    leptonicW1 = ParticlePointer(new Particle(*neutrino1 + *goodIsolatedElectrons.front()));
                    leptonicW2 = ParticlePointer(new Particle(*neutrino2 + *goodIsolatedElectrons.front()));
                    hadronicW = ParticlePointer(new Particle(*jet1FromW + *jet2FromW));
                    leptonicTop1 = ParticlePointer(new Particle(*leptonicBJet + *leptonicW1));
                    leptonicTop2 = ParticlePointer(new Particle(*leptonicBJet + *leptonicW2));
                    hadronicTop = ParticlePointer(new Particle(*hadronicBJet + *hadronicW));

                    selectNeutrinoSolution();
                    double chi2 = getTotalChi2(currentSelectedNeutrino);
                    if (chi2 < chosen_Chi2Total) {
                        hadronicBIndex = hadBindex;
                        leptonicBIndex = lepBindex;
                        jet1FromWIndex = jet1Index;
                        jet2FromWIndex = jet2Index;
                        chosen_Chi2Total = chi2;
                        selectedNeutrino = currentSelectedNeutrino;
                    }
                }
            }
        }
    }

    hadronicBJet = goodJets.at(hadronicBIndex);
    leptonicBJet = goodJets.at(leptonicBIndex);
    jet1FromW = goodJets.at(jet1FromWIndex);
    jet2FromW = goodJets.at(jet2FromWIndex);
    leptonicW1 = ParticlePointer(new Particle(*neutrino1 + *goodIsolatedElectrons.front()));
    leptonicW2 = ParticlePointer(new Particle(*neutrino2 + *goodIsolatedElectrons.front()));
    hadronicW = ParticlePointer(new Particle(*jet1FromW + *jet2FromW));
    leptonicTop1 = ParticlePointer(new Particle(*leptonicBJet + *leptonicW1));
    leptonicTop2 = ParticlePointer(new Particle(*leptonicBJet + *leptonicW2));
    hadronicTop = ParticlePointer(new Particle(*hadronicBJet + *hadronicW));
    if (selectedNeutrino == 1)
        ttbarResonance = ParticlePointer(new Particle(*leptonicTop1 + *hadronicTop));
    else
        ttbarResonance = ParticlePointer(new Particle(*leptonicTop2 + *hadronicTop));

    doneReconstruction = true;
}

void TopPairEventCandidate::reconstructNeutrinos() {
    boost::array<double, 2> neutrinoPzs = computeNeutrinoPz();
    double energy1 = sqrt(met->et() * met->et() + neutrinoPzs.at(0) * neutrinoPzs.at(0));
    double energy2 = sqrt(met->et() * met->et() + neutrinoPzs.at(0) * neutrinoPzs.at(1));
    neutrino1 = ParticlePointer(new Particle(energy1, met->px(), met->py(), neutrinoPzs.at(0)));
    neutrino2 = ParticlePointer(new Particle(energy2, met->px(), met->py(), neutrinoPzs.at(1)));

    if (isnan(neutrino1->energy()) && isnan(neutrino2->energy()))
        throw ReconstructionException("No physical neutrino solution found");
    else if (isnan(neutrino1->energy()))
        neutrino1 = neutrino2;
    else if (isnan(neutrino2->energy()))
        neutrino2 = neutrino1;
}

const boost::array<double, 2> TopPairEventCandidate::computeNeutrinoPz() {
    if (electronFromW == 0)
        throw ReconstructionException("Could not reconstruct neutrinos: no isolated electrons found");
    if (met->energy() == 0)
        throw ReconstructionException("Could not reconstruct neutrinos: no MET found");
    boost::array<double, 2> neutrinoPzs;
    //    const ElectronPointer electron = goodIsolatedElectrons.front();

    double pz1(0), pz2(0);
    //    double M_W = 80.389;
    double M_e = 0.0005;
    double ee = electronFromW->energy();
    double pxe = electronFromW->px();
    double pye = electronFromW->py();
    double pze = electronFromW->pz();
    double pxnu = met->px();
    double pynu = met->py();

    double a = W_mass * W_mass - M_e * M_e + 2.0 * pxe * pxnu + 2.0 * pye * pynu;
    double A = 4.0 * (ee * ee - pze * pze);
    double B = -4.0 * a * pze;
    double C = 4.0 * ee * ee * (pxnu * pxnu + pynu * pynu) - a * a;

    double tmproot = B * B - 4.0 * A * C;
    if (tmproot < 0) {
        pz1 = pz2 = -B / (2 * A);
    } else {
        pz1 = (-B + TMath::Sqrt(tmproot)) / (2.0 * A);
        pz2 = (-B - TMath::Sqrt(tmproot)) / (2.0 * A);

    }
    neutrinoPzs[0] = pz1;
    neutrinoPzs[1] = pz2;
    return neutrinoPzs;
}

//bool TopPairEventCandidate::hasNextJetCombination(){
//    unsigned short njets = goodJets.size();
//    return (hadronicBIndex == njets && leptonicBJet == njets-1 && jet1FormWIndex == njets -2 && jet2);
//}
//
//void TopPairEventCandidate::selectNextJetCombination(){
//
//}

void TopPairEventCandidate::selectNeutrinoSolution() {

    if (leptonicTop1->mass() < 0 && leptonicTop2->mass() < 0) {
        inspectReconstructedEvent();
        throw ReconstructionException("No valid neutrino solution found");
    } else if (leptonicTop1->mass() < 0 && leptonicTop2->mass() > 0) {
        currentSelectedNeutrino = 2;
    } else if (leptonicTop1->mass() > 0 && leptonicTop2->mass() < 0) {
        currentSelectedNeutrino = 1;
    } else {// both solutions give positive mass
        switch (usedNeutrinoSelection) {
        case NeutrinoSelectionCriterion::chi2:
            getTotalChi2(1) < getTotalChi2(2) ? currentSelectedNeutrino = 1 : currentSelectedNeutrino = 2;
            break;

        case NeutrinoSelectionCriterion::pzClosestToLepton:
            fabs(neutrino1->pz() - goodIsolatedElectrons.front()->pz()) < fabs(neutrino2->pz()
                    - goodIsolatedElectrons.front()->pz()) ? currentSelectedNeutrino = 1 : currentSelectedNeutrino = 2;
            break;

        case NeutrinoSelectionCriterion::mostCentral:
            fabs(neutrino1->pz()) < fabs(neutrino2->pz()) ? currentSelectedNeutrino = 1 : currentSelectedNeutrino = 2;
            break;

        case NeutrinoSelectionCriterion::pzClosestToLeptonOrMostcentralIfAbove300:
            fabs(neutrino1->pz() - goodIsolatedElectrons.front()->pz()) < fabs(neutrino2->pz()
                    - goodIsolatedElectrons.front()->pz()) ? currentSelectedNeutrino = 1 : currentSelectedNeutrino = 2;
            if (fabs(neutrino1->pz()) > 300 || fabs(neutrino2->pz()) > 300)
                fabs(neutrino1->pz()) < fabs(neutrino2->pz()) ? currentSelectedNeutrino = 1 : currentSelectedNeutrino
                        = 2;
            break;

        case NeutrinoSelectionCriterion::largestValueOfCosine:
            TVector3 p3W, p3e;
            //TODO clean up
            p3W = leptonicW1->getFourVector().Vect();
            p3e = electronFromW->getFourVector().Vect();

            double sinthcm1 = 2. * (p3e.Perp(p3W)) / W_mass;
            p3W = leptonicW2->getFourVector().Vect();
            double sinthcm2 = 2. * (p3e.Perp(p3W)) / W_mass;

            double costhcm1 = TMath::Sqrt(1. - sinthcm1 * sinthcm1);
            double costhcm2 = TMath::Sqrt(1. - sinthcm2 * sinthcm2);
            costhcm1 > costhcm2 ? currentSelectedNeutrino = 1 : currentSelectedNeutrino = 2;
            break;

        }
    }

}

double TopPairEventCandidate::getTotalChi2() {
    double totalChi2(9999999);
    double firstTotalChi2 = getTotalChi2(1);
    double secondTotalChi2 = getTotalChi2(2);
    selectedNeutrino == 1 ? totalChi2 = firstTotalChi2 : totalChi2 = secondTotalChi2;
    //    if (firstTotalChi2 < secondTotalChi2) {
    //        selectedNeutrino = 1;
    //        totalChi2 = firstTotalChi2;
    //    } else {
    //        selectedNeutrino = 2;
    //        totalChi2 = secondTotalChi2;
    //    }
    return totalChi2;
}

double TopPairEventCandidate::getTotalChi2(unsigned short int neutrinoSolution) const {
    return getLeptonicChi2(neutrinoSolution) + getHadronicChi2() + getGlobalChi2(neutrinoSolution);
}

double TopPairEventCandidate::getLeptonicChi2(unsigned short int neutrinoSolution) const {
    double topMass(0);
    double angle = leptonicBJet->angle(goodIsolatedElectrons.front());
    if (neutrinoSolution == 1)
        topMass = leptonicTop1->mass();
    else
        topMass = leptonicTop2->mass();

    return getLeptonicChi2(topMass, angle);
}

double TopPairEventCandidate::getLeptonicChi2(double topMass, double angle) const {
    double massDifference = TMath::Power(topMass - matched_leptonic_top_mass, 2);
    double massError = 2 * matched_leptonic_top_mass_sigma * matched_leptonic_top_mass_sigma;
    double massTerm = massDifference / massError;

    double angleDifference = TMath::Power(angle - matched_angle, 2);
    double angleError = 2 * matched_angle_sigma * matched_angle_sigma;
    double angleTerm = angleDifference / angleError;
    return 1 / sqrt(2) * (angleTerm + massTerm);
}

double TopPairEventCandidate::getHadronicChi2() const {
    double ptRatioDifference = TMath::Power(PtRatio() - matched_ptratio, 2);
    double ptRatioError = 2 * matched_ptratio_sigma * matched_ptratio_sigma;
    double ptRatioTerm = ptRatioDifference / ptRatioError;

    double WmassDifference = TMath::Power(hadronicW->mass() - matched_hadronic_W_mass, 2);
    double WmassError = 2 * matched_hadronic_W_mass_sigma * matched_hadronic_W_mass_sigma;
    double WmassTerm = WmassDifference / WmassError;

    double topMassDifference = TMath::Power(hadronicTop->mass() - matched_hadronic_top_mass, 2);
    double topMassError = 2 * matched_hadronic_top_mass_sigma * matched_hadronic_top_mass_sigma;
    double topMassTerm = topMassDifference / topMassError;
    return 1 / sqrt(3) * (topMassTerm + WmassTerm + ptRatioTerm);
    return 0;
}

double TopPairEventCandidate::PtRatio() const {
    return TMath::Log(hadronicTop->pt() / hadronicW->pt());
}

double TopPairEventCandidate::getGlobalChi2(unsigned short neutrinoSolution) const {
    double pttbar = PtTtbarSystem(neutrinoSolution);
    double pttbarTerm = pttbar / (2 * matched_pt_ttbarSystem_sigma * matched_pt_ttbarSystem_sigma);

    double htSystemDifference = TMath::Power(HTSystem() - matched_HTSystem, 2);
    double htSystemError = matched_HTSystem_sigma * matched_HTSystem_sigma * 2;
    double htSystemTerm = htSystemDifference / htSystemError;
    return 1 / sqrt(2) * (pttbarTerm + htSystemTerm);
}

double TopPairEventCandidate::PtTtbarSystem(unsigned short neutrinoSolution) const {
    ParticlePointer combined;
    if (neutrinoSolution == 1)
        combined = ParticlePointer(new Particle(*leptonicTop1 + *hadronicTop));
    else
        combined = ParticlePointer(new Particle(*leptonicTop2 + *hadronicTop));
    return combined->pt() / HT(8);
}

double TopPairEventCandidate::HT(unsigned short jetLimit) const {
    double HT(0);
    unsigned short limit = goodJets.size();
    if (limit > jetLimit + 1)
        limit = jetLimit + 1;

    for (unsigned short index = 0; index < limit; ++index)
        HT += goodJets.at(index)->pt();

    return HT;
}

double TopPairEventCandidate::HTSystem() const {
    return sumPt() / HT(8);
}

double TopPairEventCandidate::sumPt() const {
    return leptonicBJet->pt() + hadronicBJet->pt() + jet1FromW->pt() + jet2FromW->pt();
}

void TopPairEventCandidate::throwExpeptionIfNotReconstructed() const {
    if (doneReconstruction == false)
        throw ReconstructionException("Can't access reconstructed particles before reconstruction.");
}

const ElectronPointer TopPairEventCandidate::getElectronFromWDecay() const {
    return goodIsolatedElectrons.front();
}

const ParticlePointer TopPairEventCandidate::getNeutrinoFromWDecay() const {
    throwExpeptionIfNotReconstructed();
    if (selectedNeutrino == 1)
        return neutrino1;
    else
        return neutrino2;
}

const JetPointer TopPairEventCandidate::getHadronicBJet() const {
    throwExpeptionIfNotReconstructed();
    return hadronicBJet;
}

const JetPointer TopPairEventCandidate::getLeptonicBJet() const {
    throwExpeptionIfNotReconstructed();
    return leptonicBJet;
}

const JetPointer TopPairEventCandidate::getJet1FromHadronicW() const {
    throwExpeptionIfNotReconstructed();
    return jet1FromW;
}

const ParticlePointer TopPairEventCandidate::getLeptonicTop() const {
    throwExpeptionIfNotReconstructed();
    if (selectedNeutrino == 1)
        return leptonicTop1;
    else
        return leptonicTop2;
}

const ParticlePointer TopPairEventCandidate::getHadronicTop() const {
    throwExpeptionIfNotReconstructed();
    return hadronicTop;
}

const ParticlePointer TopPairEventCandidate::getRessonance() const {
    throwExpeptionIfNotReconstructed();
    return ttbarResonance;
}

double TopPairEventCandidate::M3() const {
    double m3(0), max_pt(0);
    if (goodJets.size() >= 3) {
        for (unsigned int index1 = 0; index1 < goodJets.size() - 2; ++index1) {
            for (unsigned int index2 = index1 + 1; index2 < goodJets.size() - 1; ++index2) {
                for (unsigned int index3 = index2 + 1; index3 < goodJets.size(); ++index3) {
                    FourVector m3Vector(goodJets.at(index1)->getFourVector() + goodJets.at(index2)->getFourVector()
                            + goodJets.at(index3)->getFourVector());
                    double currentPt = m3Vector.Pt();
                    if (currentPt > max_pt) {
                        max_pt = currentPt;
                        m3 = m3Vector.M();
                    }
                }
            }
        }
    }

    return m3;
}

double TopPairEventCandidate::mttbar() const {
    return getRessonance()->mass();
}

void TopPairEventCandidate::inspectReconstructedEvent() const {
    cout << "run " << runNumber << ", event " << eventNumber << endl;
    cout << "leptonic b jet, goodJet index " << leptonicBIndex << endl;
    EventPrinter::printJet(leptonicBJet);

    cout << "electron from W" << endl;
    EventPrinter::printElectron(goodIsolatedElectrons.front());

    cout << "MET" << endl;
    EventPrinter::printParticle(met);
    cout << endl;

    cout << "reconstructed neutrino 1(selected: " << selectedNeutrino << ")" << endl;
    EventPrinter::printParticle(neutrino1);
    cout << endl;

    cout << "reconstructed neutrino 2(selected: " << selectedNeutrino << ")" << endl;
    EventPrinter::printParticle(neutrino2);
    cout << endl;

    cout << "leptonic W 1 (selected: " << selectedNeutrino << ")" << endl;
    EventPrinter::printParticle(leptonicW1);
    cout << endl;

    cout << "leptonic W 2 (selected: " << selectedNeutrino << ")" << endl;
    EventPrinter::printParticle(leptonicW2);
    cout << endl;

    cout << "leptonic top 1 (selected: " << selectedNeutrino << ")" << endl;
    EventPrinter::printParticle(leptonicTop1);
    cout << endl;

    cout << "leptonic top 2 (selected: " << selectedNeutrino << ")" << endl;
    EventPrinter::printParticle(leptonicTop2);
    cout << endl;

    cout << "hadronic b jet, goodJet index " << hadronicBIndex << endl;
    EventPrinter::printJet(hadronicBJet);

    cout << "jet1 from W, goodJet index " << jet1FromWIndex << endl;
    EventPrinter::printJet(jet1FromW);

    cout << "jet 2 from W, goodJet index " << jet2FromWIndex << endl;
    EventPrinter::printJet(jet2FromW);

    cout << "hadronic W" << endl;
    EventPrinter::printParticle(hadronicW);
    cout << endl;

    cout << "hadronic top" << endl;
    EventPrinter::printParticle(hadronicTop);
    cout << endl;
}

double TopPairEventCandidate::fullHT() const {
    double ht(met->pt());

    for (unsigned int index = 0; index < goodIsolatedElectrons.size(); ++index) {
        ht += goodIsolatedElectrons.at(index)->pt();
    }

    for (unsigned int index = 0; index < goodIsolatedMuons.size(); ++index) {
        ht += goodIsolatedMuons.at(index).pt();
    }

    for (unsigned int index = 0; index < goodJets.size(); ++index) {
        ht += goodJets.at(index)->pt();
    }
    return ht;
}

double TopPairEventCandidate::transverseWmass() const {
    const ElectronPointer electron = goodIsolatedElectrons.front();
    double energySquared = pow(electron->et() + met->et(), 2);
    double momentumSquared = pow(electron->px() + met->px(), 2) + pow(electron->py() + met->py(), 2);
    double tMassSquared = energySquared - momentumSquared;

    if (tMassSquared > 0)
        return sqrt(tMassSquared);
    else
        return -1;
}

}
