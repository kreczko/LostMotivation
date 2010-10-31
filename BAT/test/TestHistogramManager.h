/*
 * TestTH1Collection.h
 *
 *  Created on: 9 Aug 2010
 *      Author: kreczko
 */

#include "cute/cute.h"
#include "cute/cute_suite.h"
#include "../interface/HistHelpers/HistogramManager.h"
#include <boost/array.hpp>
#include "../interface/Enumerators.h"
#include <boost/filesystem.hpp>

using namespace BAT;

struct TestHistogramManager {
private:
    HistogramManager man;
    float lumi;
public:
    TestHistogramManager() :
        man(), lumi(1.5) {
        boost::array<bool, DataType::NUMBER_OF_DATA_TYPES> seenDataTypes = boost::array<bool, DataType::NUMBER_OF_DATA_TYPES>();

//        for (unsigned int type = 0; type < DataType::NUMBER_OF_DATA_TYPES; ++type) {
//            seenDataTypes[type] = false;
//        }
        seenDataTypes[DataType::DATA] = true;
        seenDataTypes[DataType::ttbar] = true;

        man.setCurrentLumi(lumi);
        man.prepairForSeenDataTypes(seenDataTypes);
        man.addH1D("myHist", "Testing", 10, 0., 1);
    }

    ~TestHistogramManager() {

    }

    void testPreparationData() {
        man.setCurrentDataType(DataType::DATA);
        ASSERT(man.H1D("myHist") != 0);
    }

    void testPreparationTtbar() {
        man.setCurrentDataType(DataType::ttbar);
        ASSERT(man.H1D("myHist") != 0);
    }

    void testDataFile() {
        man.writeToDisk();
        boost::filesystem::path path("data_1.5pb.root");
        ASSERT(boost::filesystem::exists(path));
    }

};

extern cute::suite make_suite_TestHistogramManager() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testPreparationData));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testPreparationTtbar));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testDataFile));
    return s;
}

