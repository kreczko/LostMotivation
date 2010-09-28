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
    ConversionFinder,
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
        "Conversion veto (missing hits)",
        "Conversion finder (partner track)",
        "loose muon veto",
        "Z veto",
        ">= 4 jets" };
}
}
#endif //SELECTION_H_
