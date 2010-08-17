/*
 * CrossSections.cpp
 *
 *  Created on: 13 Aug 2010
 *      Author: kreczko
 */

#include "../interface/CrossSections.h"

namespace BAT {
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
    return xsection;
}

boost::array<float, DataType::NUMBER_OF_DATA_TYPES> tenTeV::getXSections() {
    boost::array<float, DataType::NUMBER_OF_DATA_TYPES> xsection;
    xsection[DataType::DATA] = 0;
    xsection[DataType::ttbar] = 0;
    return xsection;
}

CrossSectionProvider::CrossSectionProvider(unsigned short tev) :
    tev(tev), useSkimEff(false), xsection() {
    if (tev == 7)
        xsection = sevenTeV::getXSections();
    else if (tev == 10)
        xsection = tenTeV::getXSections();

}

CrossSectionProvider::~CrossSectionProvider() {

}

void CrossSectionProvider::useSkimEfficiency(bool use) {
    useSkimEff = use;
}

float CrossSectionProvider::getExpectedNumberOfEvents(DataType::value type, unsigned int lumiInInversePb) {
    return xsection[type] * lumiInInversePb;
}

} // namespace BAT
