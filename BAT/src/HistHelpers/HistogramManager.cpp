/*
 * HistogramManager.cpp
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#include "../../interface/HistHelpers/HistogramManager.h"

namespace BAT {

HistogramManager::HistogramManager() :
    jetBinned1DHists(boost::extents[DataType::NUMBER_OF_DATA_TYPES][5]), seenDataTypes(), collection(), collection2D(),
            currentDataType(DataType::DATA), currentJetbin(0), currentBJetbin(0), currentIntegratedLumi(0) {
}

HistogramManager::~HistogramManager() {
}

void HistogramManager::addH1D(std::string name, std::string title, unsigned int numberOfBins, float xmin, float xmax) {
    for (unsigned short type = DataType::DATA; type < DataType::NUMBER_OF_DATA_TYPES; ++type) {
        if (seenDataTypes.at(type)) {
            collection[type]->add(name, title, numberOfBins, xmin, xmax);
        }
    }

}

void HistogramManager::addH1D_JetBinned(std::string name, std::string title, unsigned int numberOfBins, float xmin,
        float xmax) {
    for (unsigned short jetbin = 0; jetbin < 5; ++jetbin) {
        for (unsigned short type = DataType::DATA; type < DataType::NUMBER_OF_DATA_TYPES; ++type) {
            if (seenDataTypes.at(type)) {
                jetBinned1DHists[jetbin][type]->add(name, title, numberOfBins, xmin, xmax);
            }
        }
    }

}

void HistogramManager::setCurrentDataType(DataType::value type) {
    currentDataType = type;
}

void HistogramManager::setCurrentJetBin(unsigned int jetbin) {
    currentJetbin = jetbin;
}

void HistogramManager::setCurrentBJetBin(unsigned int jetbin) {
    currentBJetbin = jetbin;
}

void HistogramManager::setCurrentLumi(float lumi) {
    currentIntegratedLumi = lumi;
}

boost::shared_ptr<TH1> HistogramManager::operator [](std::string histname) {
    return jetBinned1DHists[currentDataType][currentJetbin]->get(histname);
}

boost::shared_ptr<TH1> HistogramManager::H1D(std::string histname) {
    return collection[currentDataType]->get(histname);
}
boost::shared_ptr<TH2> HistogramManager::operator ()(std::string histname) {
    return collection2D[currentDataType]->get(histname);
}

void HistogramManager::createAllHistograms() {
    collection[DataType::DATA]->add("mttbar", "mttbar", 5000, 0, 5000);
}

void HistogramManager::prepairForSeenDataTypes(const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES>& seenDataTypes) {
    this->seenDataTypes = seenDataTypes;
    for (unsigned type = 0; type < DataType::NUMBER_OF_DATA_TYPES; ++type) {
        if (seenDataTypes.at(type)) {
            const std::string filename = assembleFilename((DataType::value) type);
            boost::shared_ptr<TFile> file(new TFile(filename.c_str(), "RECREATE"));
            collection.at(type) = TH1CollectionRef(new TH1Collection(file));
        }

    }
}

const std::string HistogramManager::assembleFilename(DataType::value type) const {
    const std::string name = DataType::names[type];
    std::stringstream str;
    str << name << "_" << currentIntegratedLumi << "pb.root";
    return str.str();

}

void HistogramManager::writeToDisk() {
    for (unsigned type = 0; type < DataType::NUMBER_OF_DATA_TYPES; ++type) {
        if (seenDataTypes.at(type))
            collection.at(type)->writeToFile();
    }
}

}
