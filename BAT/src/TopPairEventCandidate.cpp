/*
 * TopPairEventCandidate.cpp
 *
 *  Created on: 9 Jul 2010
 *      Author: kreczko
 */

#include "../interface/TopPairEventCandidate.h"
#include <iostream>

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

TopPairEventCandidate::TopPairEventCandidate() :
    Event(), leptonicBJet(), hadronicBJet(), jet1FromW(), jet2FromW(), neutrino1(), neutrino2(), leptonicW1(),
            leptonicW2(), hadronicW(), leptonicTop1(), leptonicTop2(), hadronicTop(), selectedNeutrino(0),
            hadronicBIndex(0), leptonicBIndex(0), jet1FromWIndex(0), jet2FromWIndex(0), doneReconstruction(false) {
}

TopPairEventCandidate::TopPairEventCandidate(const Event& event) :
    Event(event), leptonicBJet(), hadronicBJet(), jet1FromW(), jet2FromW(), neutrino1(), neutrino2(), leptonicW1(),
            leptonicW2(), hadronicW(), leptonicTop1(), leptonicTop2(), hadronicTop(), selectedNeutrino(0),
            hadronicBIndex(0), leptonicBIndex(0), jet1FromWIndex(0), jet2FromWIndex(0), doneReconstruction(false) {

}

TopPairEventCandidate::~TopPairEventCandidate() {
}

bool TopPairEventCandidate::passesHighLevelTrigger() const {
    if (isRealData() && runNumber >= 137029)
        return HLT_Photon15_Cleaned_L1R;
    else
        return HLT_Emulated_Photon15;
}

bool TopPairEventCandidate::hasOneGoodPrimaryVertex() const {
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
    if (step == TTbarEPlusJetsSelection::HighLevelTrigger)
        return passesSelectionStep(step);
    else {
        unsigned int newstep = (int) step - 1;
        return passesSelectionStep(step) && passesSelectionStepUpTo((TTbarEPlusJetsSelection::Step) newstep);
    }
}

bool TopPairEventCandidate::passesSelectionStep(enum TTbarEPlusJetsSelection::Step step) const {
    switch (step) {
    case TTbarEPlusJetsSelection::HighLevelTrigger:
        return passesHighLevelTrigger();
    case TTbarEPlusJetsSelection::GoodPrimaryvertex:
        return hasOneGoodPrimaryVertex();
    case TTbarEPlusJetsSelection::OneIsolatedElectron:
        return hasOnlyOneGoodIsolatedElectron();
    case TTbarEPlusJetsSelection::ConversionRejection:
        return isolatedElectronDoesNotComeFromConversion();
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
                    double chi2 = getTotalChi2();
                    if (chi2 < chosen_Chi2Total) {
                        hadronicBIndex = hadBindex;
                        leptonicBIndex = lepBindex;
                        jet1FromWIndex = jet1Index;
                        jet2FromWIndex = jet2Index;
                        chosen_Chi2Total = chi2;
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
    double energy1 = sqrt(met.et() * met.et() + neutrinoPzs.at(0) * neutrinoPzs.at(0));
    double energy2 = sqrt(met.et() * met.et() + neutrinoPzs.at(0) * neutrinoPzs.at(1));
    neutrino1 = ParticlePointer(new Particle(energy1, met.px(), met.py(), neutrinoPzs.at(0)));
    neutrino2 = ParticlePointer(new Particle(energy2, met.px(), met.py(), neutrinoPzs.at(1)));
}

const boost::array<double, 2> TopPairEventCandidate::computeNeutrinoPz() {
    if (goodIsolatedElectrons.size() == 0)
        throw ReconstructionException("Could not reconstruct neutrinos: no isolated electrons found");
    if (met.energy() == 0)
        throw ReconstructionException("Could not reconstruct neutrinos: no MET found");
    boost::array<double, 2> neutrinoPzs;
    const ElectronPointer electron = goodIsolatedElectrons.front();
    double pz1(0), pz2(0);
    double Wmass = 80.389;
    double k = Wmass * Wmass * 0.5 + (electron->px() * met.px() + electron->py() * met.py());
    double l = electron->energy() * electron->energy() - electron->pz() * electron->pz();
    double b = electron->pz() * k / l;
    double q = (k * k - electron->energy() * electron->energy() * met.et() * met.et()) / l;
    double root = b * b + q;
    if (root >= 0) {
        pz1 = b + sqrt(root);
        pz2 = b - sqrt(root);
    } else {
        pz1 = pz2 = b;
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

double TopPairEventCandidate::getTotalChi2() {
    double totalChi2(9999999);
    double firstTotalChi2 = getTotalChi2(1);
    double secondTotalChi2 = getTotalChi2(2);

    if (firstTotalChi2 < secondTotalChi2) {
        selectedNeutrino = 1;
        totalChi2 = firstTotalChi2;
    } else {
        selectedNeutrino = 2;
        totalChi2 = secondTotalChi2;
    }
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

const ParticlePointer TopPairEventCandidate::getLeptonicTop() const {
    if (selectedNeutrino == 1)
        return leptonicTop1;
    else
        return leptonicTop2;
}

const ParticlePointer TopPairEventCandidate::getHadronicTop() const {
    return hadronicTop;
}

double TopPairEventCandidate::mttbar() const {
    if (doneReconstruction == false)
        throw ReconstructionException("Can't access reconstructed particles before reconstruction.");
    return ttbarResonance->mass();
}

void TopPairEventCandidate::inspectEvent() const {
    cout << "number of jets: " << allJets.size() << endl;
    cout << "number of good jets: " << goodJets.size() << endl;
    for (unsigned short index = 0; index < goodJets.size(); ++index) {
        const JetPointer jet = goodJets.at(index);
        cout << "Jet No " << index << endl;
        cout << "pt\t px\t py\t pz" << endl;
        cout << jet->pt() << "\t" << jet->px() << "\t" << jet->py() << "\t" << jet->pz() << endl;
        cout << "emf\t eta\t n90Hits\t fHPD" << endl;
        cout << jet->emf() << "\t" << jet->eta() << "\t" << jet->n90Hits() << "\t" << jet->fHPD() << endl;
    }

    cout << "number of electrons: " << allElectrons.size() << endl;
    cout << "number of good electrons: " << goodElectrons.size() << endl;
    cout << "number of good isolated electrons: " << goodIsolatedElectrons.size() << endl;

}
}
