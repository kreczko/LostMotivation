#ifndef SELECTION_H_
#define SELECTION_H_
#include <string>

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

const std::string StringSteps[NUMBER_OF_SELECTION_STEPS] = { "High Level Trigger", "good primary vertex",
		"exactly one isolated electron", "Conversion veto", "loose muon veto", ">= 4 jets", "Z veto" };
}
}
#endif //SELECTION_H_
