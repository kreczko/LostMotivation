/*
 * Jet.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JET_H_
#define JET_H_
#include "../Taggers/BJetTagger.h"
#include "Particle.h"
#include "Electron.h"

#include <vector>
namespace BAT {

class Jet: public Particle {
public:
	enum Algorithm {
		DEFAULT,
		JPT_AntiKt_ConeDR05,
		KT_Cone04,
		KT_Cone06,
		ParticleFlow,
		SiS_Cone05,
		SiS_Cone07,
		NUMBER_OF_JETALGORITHMS
	};

	static float goodJetMinimalEt;
	static float goodJetMaximalAbsoluteEta;
	static float goodJetMinimalElectromagneticFraction;
	static float goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy;
	static float goodJetMaximalFractionOfEnergyIntheHottestHPDReadout;


	static void resetSelectionValues() {
		Jet::goodJetMaximalAbsoluteEta = 5;
		Jet::goodJetMinimalEt = 0;
		Jet::goodJetMinimalElectromagneticFraction = 0;
		Jet::goodJetMinimalNumberOfRecHitsContaining90PercentOfTheJetEnergy = 0.;
		Jet::goodJetMaximalFractionOfEnergyIntheHottestHPDReadout = 5000;
	}
	Jet();
	Jet(float energy, float px, float py, float pz);
	virtual ~Jet();
	bool isGoodJet() const;
	bool isBJetAccordingToBtagAlgorithm(BJetTagger::Algorithm btag) const;
	float emf();
	float n90Hits();
	float fHPD();
	void setEMF(float emf);
	void setDiscriminatorForBtagType(float discriminator, BJetTagger::Algorithm type);
private:
	float electroMagneticFraction;
	std::vector<float> btag_discriminators;
	bool isCloseToElectron(const std::vector<Electron>& electrons) const;
};

}

#endif /* JET_H_ */
