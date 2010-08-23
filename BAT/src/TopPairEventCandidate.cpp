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
    if (isRealData() && runNumber >= 137029 && runNumber < 141900)
        return HLT_Photon15_Cleaned_L1R;
    else if (isRealData() && runNumber >= 141900)
        return HLT_Photon20_Cleaned_L1R;
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
    double energy1 = sqrt(met->et() * met->et() + neutrinoPzs.at(0) * neutrinoPzs.at(0));
    double energy2 = sqrt(met->et() * met->et() + neutrinoPzs.at(0) * neutrinoPzs.at(1));
    neutrino1 = ParticlePointer(new Particle(energy1, met->px(), met->py(), neutrinoPzs.at(0)));
    neutrino2 = ParticlePointer(new Particle(energy2, met->px(), met->py(), neutrinoPzs.at(1)));

    if(isnan(neutrino1->energy()) && isnan(neutrino2->energy()))
            throw ReconstructionException("No physical neutrino solution found");
        else if(isnan(neutrino1->energy()))
            neutrino1 = neutrino2;
        else if(isnan(neutrino2->energy()))
            neutrino2 = neutrino1;
}

const boost::array<double, 2> TopPairEventCandidate::computeNeutrinoPz() {
    if (goodIsolatedElectrons.size() == 0)
        throw ReconstructionException("Could not reconstruct neutrinos: no isolated electrons found");
    if (met->energy() == 0)
        throw ReconstructionException("Could not reconstruct neutrinos: no MET found");
    boost::array<double, 2> neutrinoPzs;
    const ElectronPointer electron = goodIsolatedElectrons.front();

    double pz1(0), pz2(0);
    double M_W = 80.389;
    double M_e = 0.0005;
    double ee = electron->energy();
    double pxe = electron->px();
    double pye = electron->py();
    double pze = electron->pz();
    double pxnu = met->px();
    double pynu = met->py();

    double a = M_W * M_W - M_e * M_e + 2.0 * pxe * pxnu + 2.0 * pye * pynu;
    double A = 4.0 * (ee * ee - pze * pze);
    double B = -4.0 * a * pze;
    double C = 4.0 * ee * ee * (pxnu * pxnu + pynu * pynu) - a * a;

    double tmproot = B * B - 4.0 * A * C;
    //    double k = Wmass * Wmass * 0.5 + (electron->px() * met->px() + electron->py() * met->py());
    //    double l = electron->energy() * electron->energy() - electron->pz() * electron->pz();
    //    double b = electron->pz() * k / l;
    //    double q = (k * k - electron->energy() * electron->energy() * met->et() * met->et()) / l;
    //    double root = b * b + q;
    //    if (root >= 0) {
    //        pz1 = b + sqrt(root);
    //        pz2 = b - sqrt(root);
    //    } else {
    //        pz1 = pz2 = b;
    //    }
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

//void TopPairEventCandidate::inspectEvent() const {
//    cout << "number of jets: " << allJets.size() << endl;
//    cout << "number of good jets: " << goodJets.size() << endl;
//    inspectJets(goodJets);
//
//    cout << "number of good isolated electrons: " << goodIsolatedElectrons.size() << endl;
//    inspectElectrons(goodIsolatedElectrons);
//
//    cout << "number of good electrons: " << goodElectrons.size() << endl;
//    inspectElectrons(goodElectrons);
//
//    cout << "number of electrons: " << allElectrons.size() << endl;
//    inspectElectrons(allElectrons);
//
//}

//void TopPairEventCandidate::inspectJets(const JetCollection jets) const {
//    for (unsigned short index = 0; index < jets.size(); ++index) {
//        const JetPointer jet = jets.at(index);
//        cout << "Jet " << index + 1 << endl;
//        inspectJet(jet);
//    }
//}
//
//void TopPairEventCandidate::inspectElectrons(const ElectronCollection electrons) const {
//    for (unsigned short index = 0; index < electrons.size(); ++index) {
//        const ElectronPointer electron = electrons.at(index);
//        cout << "Electron " << index + 1 << endl;
//        inspectElectron(electron);
//    }
//}
//
//void TopPairEventCandidate::inspectParticle(const ParticlePointer particle) const {
//    cout << setw(30) << "pt" << setw(30) << "px" << setw(30) << "py" << setw(30) << "pz" << endl;
//    cout << setw(30) << particle->pt() << setw(30) << particle->px() << setw(30) << particle->py() << setw(30)
//            << particle->pz() << endl;
//
//    cout << setw(30) << "energy" << setw(30) << "et" << setw(30) << "eta" << setw(30) << "phi" << endl;
//    cout << setw(30) << particle->energy() << setw(30) << particle->et() << setw(30) << particle->eta() << setw(30)
//            << particle->phi() << endl;
//
//    cout << setw(30) << "d0" << setw(30) << "dyn. mass" << setw(30) << "fix. mass" << setw(30) << "charge" << endl;
//    cout << setw(30) << particle->d0() << setw(30) << particle->massFromEnergyAndMomentum() << setw(30)
//            << particle->mass() << setw(30) << particle->charge() << endl;
//}

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

double TopPairEventCandidate::mttbar() const {
    return getRessonance()->mass();
}

void TopPairEventCandidate::inspectReconstructedEvent() const {
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

    cout << "reconstructed neutrino 1(selected: " << selectedNeutrino << ")" << endl;
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

//void TopPairEventCandidate::inspectJet(const JetPointer jet) const {
//    inspectParticle(jet);
//    cout << setw(30) << "emf" << setw(30) << "n90Hits" << setw(30) << "fHPD" << setw(30) << "B tag(SSV)" << endl;
//    cout << setw(30) << jet->emf() << setw(30) << jet->n90Hits() << setw(30) << jet->fHPD() << setw(30)
//            << jet->isBJetAccordingToBtagAlgorithm(BJetTagger::SimpleSecondaryVertex) << endl << endl;
//}
//
//void TopPairEventCandidate::inspectElectron(const ElectronPointer electron) const {
//    inspectParticle(electron);
//    cout << setw(30) << "VBTF70" << setw(30) << "VBTF85" << setw(30) << "robust loose" << setw(30) << "robust tight"
//            << endl;
//    cout << setw(30) << electron->VBTF_W70_ElectronID() << setw(30) << "" << setw(30) << electron->RobustLooseID()
//            << setw(30) << electron->RobustTightID() << endl;
//
//    cout << setw(30) << "sigma_{ieta ieta}" << setw(30) << "|Delta phi_{in}|" << setw(30) << "|Delta eta_{in}|"
//            << setw(30) << "HadOverEm" << endl;
//    cout << setw(30) << electron->sigmaIEtaIEta() << setw(30) << fabs(electron->dPhiIn()) << setw(30) << fabs(
//            electron->dEtaIn()) << setw(30) << electron->HadOverEm() << endl;
//
//    cout << setw(30) << "isSpike" << setw(30) << "rel. iso." << setw(30) << "isFromConversion" << setw(30)
//            << "superClusterEta" << endl;
//    cout << setw(30) << electron->isEcalSpike() << setw(30) << electron->relativeIsolation() << setw(30)
//            << electron->isFromConversion() << setw(30) << electron->superClusterEta() << endl << endl;
//
//}
}
