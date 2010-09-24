/*
 * CrossSections.cpp
 *
 *  Created on: 13 Aug 2010
 *      Author: kreczko
 */

#include "../interface/CrossSections.h"

namespace BAT {

CrossSectionProvider::CrossSectionProvider(unsigned short tev) :
    tev(tev), useSkimEff(true), xsection(), skimEfficieny() {
    if (tev == 7)
        xsection = sevenTeV::getXSections();
    else if (tev == 10)
        xsection = tenTeV::getXSections();
    defineSkimEfficiencies();
}

boost::array<float, DataType::NUMBER_OF_DATA_TYPES> sevenTeV::getXSections() {
    boost::array<float, DataType::NUMBER_OF_DATA_TYPES> xsection;
    xsection[DataType::DATA] = 0;
    xsection[DataType::ttbar] = 157.5;
    xsection[DataType::Zjets] = 3048.;
    xsection[DataType::Wjets] = 31314.;

    xsection[DataType::QCD_EMEnriched_Pt20to30] = 0.2355e9 * 0.0073;//xs 0.2355 mb (filter efficiency=0.0073)
    xsection[DataType::QCD_EMEnriched_Pt30to80] = 0.0593e9 * 0.059; //xs 0.0593 mb
    xsection[DataType::QCD_EMEnriched_Pt80to170] = 0.906e6 * 0.148; //xs 0.906e-3 mb

    xsection[DataType::QCD_BCtoE_Pt20to30] = 0.2355e9 * 0.00046; //xs 0.2355 mb (filter efficiency=0.00046)
    xsection[DataType::QCD_BCtoE_Pt30to80] = 0.0593e9 * 0.00234; //xs 0.0593 mb
    xsection[DataType::QCD_BCtoE_Pt80to170] = 0.906e6 * 0.0104; //xs 0.906e-3 mb
    xsection[DataType::singleTop_And_W] = 10.6; //xs  11 pb (NLO MCFM) inclusive t,W decay
    xsection[DataType::singleTopTChannel] = 21.53; //=64.6/3 15Jul
    xsection[DataType::singleTopSChannel] = 1.40; //=4.21/3 15Jul
    xsection[DataType::VQQ] = 36.;
    xsection[DataType::Zprime_M500GeV_W5GeV] = 50;
    xsection[DataType::Zprime_M500GeV_W50GeV] = 50;
    xsection[DataType::Zprime_M750GeV_W7500MeV] = 50;
    xsection[DataType::Zprime_M1TeV_W10GeV] = 50;
    xsection[DataType::Zprime_M1TeV_W100GeV] = 50;
    xsection[DataType::Zprime_M1250GeV_W12500MeV] = 50;
    xsection[DataType::Zprime_M1500GeV_W15GeV] = 50;
    xsection[DataType::Zprime_M1500GeV_W150GeV] = 50;
    xsection[DataType::Zprime_M2TeV_W20GeV] = 50;
    xsection[DataType::Zprime_M2TeV_W200GeV] = 50;
    xsection[DataType::Zprime_M3TeV_W30GeV] = 50;
    xsection[DataType::Zprime_M3TeV_W300GeV] = 50;
    xsection[DataType::Zprime_M4TeV_W40GeV] = 50;
    xsection[DataType::Zprime_M4TeV_W400GeV] = 50;
    return xsection;
}

boost::array<float, DataType::NUMBER_OF_DATA_TYPES> tenTeV::getXSections() {
    boost::array<float, DataType::NUMBER_OF_DATA_TYPES> xsection;
    xsection[DataType::DATA] = 0;
    xsection[DataType::ttbar] = 0;
    return xsection;
}

void CrossSectionProvider::defineSkimEfficiencies() {
    skimEfficieny[DataType::DATA] = 0;
    skimEfficieny[DataType::ttbar] = 642707. / 1468404.;
    skimEfficieny[DataType::Zjets] = 329061. / 1084921.;
    skimEfficieny[DataType::Wjets] = 1101679. / 5143895.;

    skimEfficieny[DataType::QCD_EMEnriched_Pt20to30] = 917274. / 14607326.;
    skimEfficieny[DataType::QCD_EMEnriched_Pt30to80] = 3639776. / 27403259;
    skimEfficieny[DataType::QCD_EMEnriched_Pt80to170] = 1253958. / 4686413;

    skimEfficieny[DataType::QCD_BCtoE_Pt20to30] =  86392. / 2606023.;
    skimEfficieny[DataType::QCD_BCtoE_Pt30to80] = 441537. / 2470597.;
    skimEfficieny[DataType::QCD_BCtoE_Pt80to170] = 477762. / 998674.;
    skimEfficieny[DataType::singleTop_And_W] = 0;
    skimEfficieny[DataType::singleTopTChannel] = 0;
    skimEfficieny[DataType::singleTopSChannel] = 0;
    skimEfficieny[DataType::VQQ] = 36.;
    skimEfficieny[DataType::Zprime_M500GeV_W5GeV] = 0.453024209517;
    skimEfficieny[DataType::Zprime_M500GeV_W50GeV] = 50;
    skimEfficieny[DataType::Zprime_M750GeV_W7500MeV] = 50;
    skimEfficieny[DataType::Zprime_M1TeV_W10GeV] = 50;
    skimEfficieny[DataType::Zprime_M1TeV_W100GeV] = 50;
    skimEfficieny[DataType::Zprime_M1250GeV_W12500MeV] = 50;
    skimEfficieny[DataType::Zprime_M1500GeV_W15GeV] = 50;
    skimEfficieny[DataType::Zprime_M1500GeV_W150GeV] = 50;
    skimEfficieny[DataType::Zprime_M2TeV_W20GeV] = 50;
    skimEfficieny[DataType::Zprime_M2TeV_W200GeV] = 50;
    skimEfficieny[DataType::Zprime_M3TeV_W30GeV] = 50;
    skimEfficieny[DataType::Zprime_M3TeV_W300GeV] = 50;
    skimEfficieny[DataType::Zprime_M4TeV_W40GeV] = 50;
    skimEfficieny[DataType::Zprime_M4TeV_W400GeV] = 50;
//    pj1: 311575. / 2255228.
  //  pj2: 241590. / 1071393.
    //pj3: 338407. / 960198.


}

CrossSectionProvider::~CrossSectionProvider() {

}

void CrossSectionProvider::useSkimEfficiency(bool use) {
    useSkimEff = use;
}

float CrossSectionProvider::getExpectedNumberOfEvents(DataType::value type, unsigned int lumiInInversePb) {
    if (useSkimEff)
        return xsection[type] * lumiInInversePb * skimEfficieny[type];
    else
        return xsection[type] * lumiInInversePb;
}

} // namespace BAT
