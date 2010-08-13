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
    boost::shared_ptr<TFile> histFile;
    TH1Collection collection;
    TH1Collection collectionWithPath;
    TH2Collection collection2D;
public:
    TestTHCollection() :
        histFile(new TFile("testTHCollection.root", "RECREATE")), collection(histFile), collectionWithPath(histFile,
                "mc/ttbar"), collection2D(histFile) {
    }

    ~TestTHCollection() {
    }

    void testInitialSize() {
        ASSERT_EQUAL(0, collection.size());
    }

    void testSize() {
        collection.add("test", "test", 100, 0, 100);
        ASSERT_EQUAL(1, collection.size());
    }

    void test2DSize(){
        collection2D.add("test", "test", 100, 0, 100, 50, 0, 50);
        ASSERT_EQUAL(1, collection2D.size());
    }

    void testInterference() {
        collection.add("test", "test", 100, 0, 100);
        collectionWithPath.add("test", "test", 100, 0, 100);
        collection.get("test")->Fill(1);
        collectionWithPath.get("test")->Fill(1);
        ASSERT_EQUAL(1, collectionWithPath.get("test")->GetEntries());
    }

    void testWriteInterference() {
        collection.add("test", "test", 100, 0, 100);
        collectionWithPath.add("test", "test", 100, 0, 100);
        collection.get("test")->Fill(1);
        collectionWithPath.get("test")->Fill(1);
        collection.writeToFile();
        collectionWithPath.writeToFile();
        ASSERT(histFile->Get("test") != 0);
        ASSERT(histFile->Get("mc/ttbar/test") != 0);
    }

    void testWriteFileWithoutFolder() {
        collection.add("test", "test", 100, 0, 100);
        collection.writeToFile();
        ASSERT(histFile->Get("test") != 0);
    }

    void testWriteFileWithFolderFirstDirectory() {
        collectionWithPath.add("test", "test", 100, 0, 100);
        collectionWithPath.writeToFile();
        ASSERT(histFile->Get("mc") != 0);

    }

    void testWriteFileWithFolderSubDirectory() {
        collectionWithPath.add("test", "test", 100, 0, 100);
        collectionWithPath.writeToFile();
        ASSERT(histFile->Get("mc/ttbar") != 0);
    }

    void testWriteFileWithFolder() {
        collectionWithPath.add("test", "test", 100, 0, 100);
        collectionWithPath.writeToFile();
        ASSERT(histFile->Get("mc/ttbar/test") != 0);
    }

};

extern cute::suite make_suite_TestTHCollection() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testInitialSize));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testSize));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, test2DSize));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testInterference));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testWriteInterference));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testWriteFileWithoutFolder));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testWriteFileWithFolderFirstDirectory));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testWriteFileWithFolderSubDirectory));
    s.push_back(CUTE_SMEMFUN(TestTHCollection, testWriteFileWithFolder));
    return s;
}

