/*
 * CrossSections.h
 *
 *  Created on: 29 Jul 2010
 *      Author: kreczko
 */

#ifndef CROSSSECTIONS_H_
#define CROSSSECTIONS_H_
//https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries#crosssections

#include "Enumerators.h"
#include <vector>
#include <boost/array.hpp>

namespace BAT {
namespace sevenTeV {
extern boost::array<float, DataType::NUMBER_OF_DATA_TYPES> getXSections();
}

namespace tenTeV{
extern boost::array<float, DataType::NUMBER_OF_DATA_TYPES> getXSections();
}

struct CrossSectionProvider{
private:
    unsigned short tev;
    bool useSkimEff;
    boost::array<float, DataType::NUMBER_OF_DATA_TYPES> xsection;
    boost::array<float, DataType::NUMBER_OF_DATA_TYPES> skimEfficieny;
    void defineSkimEfficiencies();
public:


    CrossSectionProvider(unsigned short tev = 7);
    ~CrossSectionProvider();

    void useSkimEfficiency(bool use);

    float getExpectedNumberOfEvents(DataType::value type, unsigned int lumiInInversePb);

};
}

#endif /* CROSSSECTIONS_H_ */
