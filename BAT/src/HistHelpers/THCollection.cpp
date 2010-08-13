/*
 * THCollection.cpp
 *
 *  Created on: 9 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/HistHelpers/THCollection.h"

namespace BAT {
template<>
void THCollection<TH1>::add(std::string name, std::string title, unsigned int numberOfBins, double xmin, double xmax) {
    histMap[name] = boost::shared_ptr<TH1>(new TH1D(name.c_str(), title.c_str(), numberOfBins, xmin, xmax));
}

template<>
void THCollection<TH2>::add(std::string name, std::string title, unsigned int numberOfXBins, double xmin, double xmax,
        unsigned int numberOfYBins, double ymin, double ymax) {
    histMap[name] = boost::shared_ptr<TH2>(new TH2D(name.c_str(), title.c_str(), numberOfXBins, xmin, xmax,
            numberOfYBins, ymin, ymax));
}
}
