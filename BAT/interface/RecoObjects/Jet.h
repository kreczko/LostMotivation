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
	Jet(const Particle& particle);
	Jet(float energy, float px, float py, float pz);
	virtual ~Jet();
	bool isGood() const;
	bool isBJetAccordingToBtagAlgorithm(BJetTagger::Algorithm btag) const;
	Algorithm getUsedAlgorithm() const;
	float emf() const;
	float n90Hits() const;
	float fHPD() const;
	void setUsedAlgorithm(Algorithm algo);
	void setEMF(float emf);
	void setN90Hits(float n90Hits);
	void setFHPD(float fHPD);
	void setDiscriminatorForBtagType(float discriminator, BJetTagger::Algorithm type);
private:
	Algorithm usedAlgorithm;
	float electroMagneticFraction;
	float numberOfRecHitsContaining90PercentOfTheJetEnergy;
	float fractionOfEnergyIntheHottestHPDReadout;
	std::vector<float> btag_discriminators;
};
typedef std::vector<Jet> JetCollection;
}

#endif /* JET_H_ */
