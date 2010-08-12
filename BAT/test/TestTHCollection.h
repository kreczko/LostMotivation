/*
 * TestTH1Collection.h
 *
 *  Created on: 9 Aug 2010
 *      Author: kreczko
 */

#include "cute/cute.h"
#include "cute/cute_suite.h"
#include "../interface/HistHelpers/THCollection.h"
#include "TH1F.h"
#include "TFile.h"
#include <boost/shared_ptr.hpp>

using namespace BAT;

struct TestTHCollection {
private:
        TH1Collection collection;
    boost::shared_ptr<TFile> histFile;
        TH1Collection collectionWithPath;

public:
    TestTHCollection() :collection(),
        histFile(new TFile("testTHCollection.root", "RECREATE")){
    }

    ~TestTHCollection() {
    }

    void testInitialSize() {
                ASSERT_EQUAL(0, collection.size());
//        ASSERT(true);
    }

    void testSize() {
                collection.add("test", "test", 100, 0, 100);
                ASSERT_EQUAL(1, collection.size());
//        ASSERT(true);
    }

};

extern cute::suite make_suite_TestTHCollection() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testInitialSize));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testSize));
    return s;
}

