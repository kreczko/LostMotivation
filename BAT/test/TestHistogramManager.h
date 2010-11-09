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
#include "../interface/Constants.h"
#include <boost/filesystem.hpp>

using namespace BAT;

struct TestHistogramManager {
private:
    HistogramManager man;
    float lumi;
public:
    TestHistogramManager() :
        man(), lumi(1.5) {
        boost::array<bool, DataType::NUMBER_OF_DATA_TYPES> seenDataTypes = boost::array<bool,
                DataType::NUMBER_OF_DATA_TYPES>();

        seenDataTypes[DataType::DATA] = true;
        seenDataTypes[DataType::ttbar] = true;

        man.setCurrentLumi(lumi);
        man.prepareForSeenDataTypes(seenDataTypes);
        man.addH1D("myHist", "Testing", 10, 0., 1);
        man.addH2D("myHist2D", "Testing", 10, 0., 1, 10, 0., 1);
        man.addH1D_JetBinned("myHistJeted", "Testing", 10, 0., 1);
    }

    ~TestHistogramManager() {
        if (boost::filesystem::exists("data_1.5pb.root"))
            boost::filesystem::remove("data_1.5pb.root");
        if (boost::filesystem::exists("ttjet_1.5pb.root"))
            boost::filesystem::remove("ttjet_1.5pb.root");
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
        ASSERT(boost::filesystem::exists("data_1.5pb.root"));
    }

    void testPreparationData2D() {
        man.setCurrentDataType(DataType::DATA);
        ASSERT(man.H2D("myHist2D") != 0);
    }

    void testPreparationDatajetBinned() {
        man.setCurrentDataType(DataType::DATA);
        man.setCurrentJetBin(0);
        ASSERT(man.H1D_JetBinned("myHistJeted") != 0);
    }

    void testNumberOfHistsInFile(){
        man.writeToDisk();
        boost::shared_ptr<TFile> file(new TFile("data_1.5pb.root"));
        ASSERT_EQUAL(2 + JetBin::NUMBER_OF_JET_BINS, file->GetNkeys());
    }

    void testJetBinnedHistInFile(){
            man.writeToDisk();
            boost::shared_ptr<TFile> file(new TFile("data_1.5pb.root"));
            ASSERT(file->Get("myHistJeted_0jet") != 0);
        }

};

extern cute::suite make_suite_TestHistogramManager() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testPreparationData));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testPreparationTtbar));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testDataFile));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testPreparationData2D));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testPreparationDatajetBinned));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testNumberOfHistsInFile));
    s.push_back(CUTE_SMEMFUN(TestHistogramManager, testJetBinnedHistInFile));
    return s;
}

