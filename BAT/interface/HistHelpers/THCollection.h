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
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include "StringOperations.h"

using namespace boost;
namespace BAT {

template<class histType>
class THCollection {
    typedef shared_ptr<histType> histPointer;
    typedef unordered_map<std::string, histPointer> map;

protected:
    boost::shared_ptr<TFile> histogramFile;
    std::string path;
    std::vector<std::string> directories;
    map histMap;
public:
    THCollection() :
        histogramFile(), directories(), histMap() {

    }

    THCollection(boost::shared_ptr<TFile> histFile, std::string virtualPath = "") :
        histogramFile(histFile), path(virtualPath), directories(getDirectoriesFromPath(path)), histMap() {

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
        histogramFile->cd();
        writeDirectories();
        histogramFile->Cd(path.c_str());
        writeHistograms();
    }

private:

    void writeDirectories() {
        std::string currentPath = "";

        for (unsigned short index = 0; index < directories.size(); ++index) {
            const std::string dir = directories.at(index);

            if (index == 0) {
                histogramFile->mkdir(dir.c_str());
                currentPath = dir;
            } else {
                TDirectory* currentDir = (TDirectory*) histogramFile->Get(currentPath.c_str());
                assert(currentDir != 0);
                currentDir->mkdir(dir.c_str());
                currentPath += "/" + dir;
            }
        }
    }
    void writeHistograms() {
        for (typename map::const_iterator iter = histMap.begin(); iter != histMap.end(); ++iter) {
            iter->second->Write();
        }
    }

};

typedef THCollection<TH1> TH1Collection;
typedef THCollection<TH2> TH2Collection;

}

#endif /* THCOLLECTION_H_ */
