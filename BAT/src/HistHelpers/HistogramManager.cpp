/*
 * HistogramManager.cpp
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#include "../../interface/HistHelpers/HistogramManager.h"

namespace BAT {

HistogramManager::HistogramManager() :
    collection(), collection2D(), currentDataType(DataType::DATA) {

}

HistogramManager::~HistogramManager() {
}

void HistogramManager::setCurrentDataType(DataType::value type) {
    currentDataType = type;
}

boost::shared_ptr<TH1> HistogramManager::operator [](std::string histname) {
    return collection.get(histname);
}

boost::shared_ptr<TH2> HistogramManager::operator ()(std::string histname) {
    return collection2D.get(histname);
}

}
