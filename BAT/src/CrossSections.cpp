/*
 * CrossSections.cpp
 *
 *  Created on: 13 Aug 2010
 *      Author: kreczko
 */

#include "../interface/CrossSections.h"

namespace BAT {
std::vector<float> sevenTeV::getXSections() {
    std::vector<float> xsection(DataType::NUMBER_OF_DATA_TYPES);
    xsection[DataType::DATA] = 0;
    xsection[DataType::ttbar] = 157.5;
    return xsection;
}

struct CrossSectionProvider{
private:
    unsigned short tev;
    bool useSkimEff;
public:
    static std::vector<float> xsection;

    CrossSectionProvider(unsigned short tev = 7):tev(tev), useSkimEff(false){

    }
    ~CrossSectionProvider(){

    }

    void useSkimEfficiency(bool use){
        useSkimEff = use;
    }

    unsigned long getExpectedNumberOfEvents(DataType::value type, unsigned int lumiInInversePb){
        return 0;
    }

};

} // namespace BAT
