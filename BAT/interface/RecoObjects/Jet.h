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
#include <vector>
namespace BAT {

class Jet: public Particle {
public:
	enum Algorithm {
		Calo_AntiKT_Cone05,
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
	float electromagneticFraction;
	float numberOfRecHitsContaining90PercentOfTheJetEnergy;
	float fractionOfEnergyIntheHottestHPDReadout;
	std::vector<float> btag_discriminators;
};
typedef boost::shared_ptr<Jet> JetPointer;
typedef std::vector<JetPointer> JetCollection;
}

#endif /* JET_H_ */
