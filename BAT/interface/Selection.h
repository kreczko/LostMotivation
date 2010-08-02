#ifndef SELECTION_H_
#define SELECTION_H_

namespace BAT {
namespace TTbarEPlusJetsSelection {
enum Step {
	HighLevelTrigger,
	GoodPrimaryvertex,
	OneIsolatedElectron,
	ConversionRejection,
	LooseMuonVeto,
	AtLeastFourGoodJets,
	Zveto,
	NUMBER_OF_SELECTION_STEPS
};
}
}
#endif //SELECTION_H_
