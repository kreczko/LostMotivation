/*
 * TopPairEventCandidate.h
 *
 *  Created on: 9 Jul 2010
 *      Author: kreczko
 */

#ifndef TOPPAIREVENTCANDIDATE_H_
#define TOPPAIREVENTCANDIDATE_H_

#include <boost/shared_ptr.hpp>
#include "Event.h"
#include "Enumerators.h"
#include "RecoObjects/Particle.h"
#include "RecoObjects/Electron.h"
#include "RecoObjects/Jet.h"

namespace BAT {

struct ReconstructionException: public std::exception {
    TString msg;
    ReconstructionException(TString message) :
        msg(message) {
    }
    ~ReconstructionException() throw () {
    }

    const char* what() const throw () {
        return msg;
    }
};

class TopPairEventCandidate: public Event {

private:
    static double const matched_angle;// = 0.945666;
    static double const matched_angle_sigma;// = 0.311091;
    static double const matched_leptonic_top_mass;// = 178.377;
    static double const matched_leptonic_top_mass_sigma;// = 31.050;
    static double const matched_hadronic_W_mass;// = 89.9153;
    static double const matched_hadronic_W_mass_sigma;// = 13.8711;
    static double const matched_hadronic_top_mass;// = 182.191;
    static double const matched_hadronic_top_mass_sigma;// = 22.1484;
    static double const matched_ptratio;// = 0.18552;
    static double const matched_ptratio_sigma;// = 0.401973;
    static double const matched_pt_ttbarSystem;// = 0.0760939;
    static double const matched_pt_ttbarSystem_sigma;// = 0.0700391;
    static double const matched_HTSystem;// = 1;
    static double const matched_HTSystem_sigma;// = 0.1;
    static double const W_mass;

    ElectronPointer electronFromW;
    JetPointer leptonicBJet, hadronicBJet, jet1FromW, jet2FromW;
    ParticlePointer neutrino1, neutrino2, leptonicW1, leptonicW2, hadronicW, leptonicTop1, leptonicTop2, hadronicTop,
            ttbarResonance;
    unsigned short selectedNeutrino, currentSelectedNeutrino, hadronicBIndex, leptonicBIndex, jet1FromWIndex,
            jet2FromWIndex;
    bool doneReconstruction;
public:
    static NeutrinoSelectionCriterion::value usedNeutrinoSelection;
    TopPairEventCandidate();
    TopPairEventCandidate(const Event& event);
    virtual ~TopPairEventCandidate();

    const JetPointer getLeptonicBJet() const;
    const JetPointer getHadronicBJet() const;
    const JetPointer getJet1FromHadronicW() const;
    const JetPointer getJet2FromHadronicW() const;
    const ElectronPointer getElectronFromWDecay() const;
    const ParticlePointer getNeutrinoFromWDecay() const;
    const ParticlePointer getLeptonicW() const;
    const ParticlePointer getHadronicW() const;
    const ParticlePointer getLeptonicTop() const;
    const ParticlePointer getHadronicTop() const;
    const ParticlePointer getRessonance() const;

    bool passesSelectionStep(TTbarEPlusJetsSelection::Step step) const;
    bool passesSelectionStepUpTo(TTbarEPlusJetsSelection::Step upToStep) const;

    bool passesHighLevelTrigger() const;
    bool hasOneGoodPrimaryVertex() const;
    bool hasOnlyOneGoodIsolatedElectron() const;
    bool isolatedElectronDoesNotComeFromConversion() const;
    bool hasNoIsolatedMuon() const;

    bool hasAtLeastOneGoodJet() const;
    bool hasAtLeastTwoGoodJets() const;
    bool hasAtLeastThreeGoodJets() const;
    bool hasAtLeastFourGoodJets() const;

    bool isNotAZBosonEvent() const;
    bool passesFullTTbarEPlusJetSelection() const;
    bool hasIsolatedElectronInBarrelRegion() const;

    void reconstructUsingChi2();
    void reconstructUsingSubjets();
    void reconstructUsingMCTruth();

    double getLeptonicChi2(unsigned short neutrinoSolution) const;
    double getLeptonicChi2(double topMass, double angle) const;
    double getHadronicChi2() const;
    double getGlobalChi2(unsigned short neutrinoSolution) const;
    double getTotalChi2(unsigned short neutrinoSolution) const;
    double getTotalChi2();

    double mttbar() const;
    double sumPt() const;
    double HT(unsigned short jetLimit) const;
    double HTSystem() const;
    double PtRatio() const;
    double PtTtbarSystem(unsigned short neutrinoSolution) const;
    const boost::array<double, 2> computeNeutrinoPz();
    void reconstructNeutrinos();
    bool hasNextJetCombination();
    void selectNextJetCombination();
    void inspectReconstructedEvent() const;
private:
    void throwExpeptionIfNotReconstructed() const;
    void selectNeutrinoSolution();

};

}

#endif /* TOPPAIREVENTCANDIDATE_H_ */
