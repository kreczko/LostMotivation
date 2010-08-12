/*
 * THCollection.h
 *
 *  Created on: 9 Aug 2010
 *      Author: kreczko
 */

#ifndef THCOLLECTION_H_
#define THCOLLECTION_H_
#include <string>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>

#include "StringOperations.h"

namespace BAT {

template<class histType>
class THCollection {
    typedef boost::unordered_map<std::string, boost::shared_ptr<histType> > map;

protected:
    boost::shared_ptr<TFile> histogramFile;
    std::vector<std::string> directories;
    map histMap;
public:
    THCollection() :
        histogramFile(), directories(), histMap() {

    }

    THCollection(boost::shared_ptr<TFile> histFile, std::string virtualPath = "") :
        histogramFile(histFile), directories(getDirectoriesFromPath(virtualPath)), histMap() {

    }

    ~THCollection() {

    }

    void add(std::string name, std::string title, unsigned int numberOfBins, double xmin, double xmax);
    void add(std::string name, std::string title, unsigned int numberOfXBins, double xmin, double xmax,
            unsigned int numberOfYBins, double ymin, double ymax);

    boost::shared_ptr<histType> get(std::string name) {
        return histMap[name];
    }

    void setSavePath(TString path);

    unsigned int size() const {
        return histMap.size();
    }

    void writeToFile() {

    }

};

typedef THCollection<TH1> TH1Collection;
typedef THCollection<TH2> TH2Collection;

}

#endif /* THCOLLECTION_H_ */
