/*
 * Enumerators.h
 *
 *  Created on: Jun 30, 2010
 *      Author: lkreczko
 */

#ifndef ENUMERATORS_H_
#define ENUMERATORS_H_
namespace BAT {
namespace BTag{

enum Algorithm {
	NONE,
	FAKE,
	TrackCountingHighEfficiency,
	TrackCountingHighPurity,
	JetBProbability,
	JetProbability,
	SimpleSecondaryVertex,
	SoftElectron,
	SoftMuon,
	SoftMuonNoIP,
	NUMBER_OF_BTAGALGORITHMS
};
}

namespace Jet{
enum Algorithm{
	DEFAULT,
	JPT_AntiKt_ConeDR05,
	KT_Cone04,
	KT_Cone06,
	ParticleFlow,
	SiS_Cone05,
	SiS_Cone07,
	NUMBER_OF_JETALGORITHMS
};
}

namespace MET{
enum Type{
	DEFAULT,
	CalorimeterMET_mujes,
	SC5,
	SC7,
	KT4,
	KT6,
	tcMET,
	ParticleFlowMET,
	MCTruth,
	NUMBER_OF_METALGORITHMS
};
}

enum SelectionStages{
	NUMBER_OF_SELECTIONSTAGES
};
}

#endif /* ENUMERATORS_H_ */
