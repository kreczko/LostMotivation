/*
 * THCollection.cpp
 *
 *  Created on: 9 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/HistHelpers/THCollection.h"

namespace BAT {
template<>
void THCollection<TH1>::add(std::string name, std::string title, unsigned int numberOfBins, double xmin, double xmax){
    histMap[name] = boost::shared_ptr<TH1>(new TH1D(name.c_str(), title.c_str(), numberOfBins, xmin, xmax));
}
}
