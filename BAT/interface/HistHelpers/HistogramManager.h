/*
 * HistogramManager.h
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#ifndef HISTOGRAMMANAGER_H_
#define HISTOGRAMMANAGER_H_
#include "THCollection.h"
#include "TH1D.h"
#include "TH2D.h"
#include "../Taggers/BJetTagger.h"
#include "../../interface/Enumerators.h"
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include "TFile.h"
#include <string>

namespace BAT {
typedef unsigned short ushort;
class HistogramManager {
public:
    HistogramManager();
    virtual ~HistogramManager();
    void createAllHistograms();
    void addH1D(std::string name, std::string title, unsigned int nBins, float xmin, float xmax);
    void addH1D_JetBinned(std::string name, std::string title, unsigned int nBins, float xmin, float xmax);
    void addH1D_BJetBinned(std::string name, std::string title, unsigned int nBins, float xmin, float xmax);

    void addH2D(std::string name, std::string title, unsigned int nXBins, float xmin, float xmax, unsigned int nYBins,
            float ymin, float ymax);

    void setCurrentDataType(DataType::value type);
    void setCurrentJetBin(unsigned int jetbin);
    void setCurrentBJetBin(unsigned int jetbin);
    void setCurrentLumi(float lumi);
    void prepareForSeenDataTypes(const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES>& seenDataTypes);

    boost::shared_ptr<TH1> operator[](std::string);
    boost::shared_ptr<TH1> H1D(std::string);
    boost::shared_ptr<TH1> H1D_JetBinned(std::string);
    boost::shared_ptr<TH1> H1D_BJetBinned(std::string);
    boost::shared_ptr<TH2> operator()(std::string);
    boost::shared_ptr<TH2> H2D(std::string);
    boost::shared_ptr<TH2> H2D_JetBinned(std::string);
    boost::shared_ptr<TH2> H2D_BJetBinned(std::string);

    void createSummaryHistograms();

    void writeToDisk();
private:
    boost::multi_array<TH1CollectionRef, 2> jetBinned1DHists;
    boost::array<bool, DataType::NUMBER_OF_DATA_TYPES> seenDataTypes;
    boost::array<boost::shared_ptr<TFile>, DataType::NUMBER_OF_DATA_TYPES> histFiles;
    boost::array<TH1CollectionRef, DataType::NUMBER_OF_DATA_TYPES> collection;// move to array of DataTypes
    boost::array<TH2CollectionRef, DataType::NUMBER_OF_DATA_TYPES> collection2D;
    DataType::value currentDataType;
    unsigned int currentJetbin;
    unsigned int currentBJetbin;
    float currentIntegratedLumi;

    const std::string assembleFilename(DataType::value) const;
};

}

#endif /* HISTOGRAMMANAGER_H_ */
