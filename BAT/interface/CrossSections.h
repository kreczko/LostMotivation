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
namespace BAT {
namespace sevenTeV {
extern std::vector<float> getXSections();
}

namespace tenTeV{

}
struct CrossSectionProvider;

}

#endif /* CROSSSECTIONS_H_ */
