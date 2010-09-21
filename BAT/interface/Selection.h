#ifndef SELECTION_H_
#define SELECTION_H_
#include <string>

namespace BAT {
namespace TTbarEPlusJetsSelection {
enum Step {
    FilterOutScraping,
    HighLevelTrigger,
    GoodPrimaryvertex,
    OneIsolatedElectron,
    ConversionRejection,
    LooseMuonVeto,
    Zveto,
    AtLeastFourGoodJets,
    NUMBER_OF_SELECTION_STEPS
};

const std::string StringSteps[NUMBER_OF_SELECTION_STEPS] = {
        "Scraping Filter",
        "High Level Trigger",
        "good primary vertex",
        "exactly one isolated electron",
        "Conversion veto",
        "loose muon veto",
        "Z veto",
        ">= 4 jets" };
}
}
#endif //SELECTION_H_
