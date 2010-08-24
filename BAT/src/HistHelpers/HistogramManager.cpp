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

}
