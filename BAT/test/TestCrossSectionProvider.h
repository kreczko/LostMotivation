/*
 * TestCrossSectionProvider.h
 *
 *  Created on: 16 Aug 2010
 *      Author: kreczko
 */

#include "cute/cute.h"
#include "cute/cute_suite.h"
#include "../interface/CrossSections.h"
#include "../interface/Enumerators.h"

using namespace BAT;

struct TestCrossSectionProvider {
private:
    CrossSectionProvider xSectionProvider;
    float lumi;
public:
    TestCrossSectionProvider() :
        xSectionProvider(), lumi(20) {
        xSectionProvider.useSkimEfficiency(false);
    }

    ~TestCrossSectionProvider() {

    }

    void testGetExpectedTTbarEventsFor20pb() {
        ASSERT_EQUAL(157.5*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::ttbar, lumi));
    }

    void testGetExpectedWjetsEventsFor20pb() {
        ASSERT_EQUAL(31314.*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::Wjets, lumi));
    }

    void testGetExpectedZjetsEventsFor20pb() {
        ASSERT_EQUAL(3048.*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::Zjets, lumi));
    }

    void testGetExpectedQCD_EMEnriched_Pt20to30EventsFor20pb() {
        ASSERT_EQUAL(0.2355e9 * 0.0073*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_EMEnriched_Pt20to30, lumi));
    }

    void testGetExpectedQCD_EMEnriched_Pt30to80EventsFor20pb() {
        ASSERT_EQUAL(0.0593e9 * 0.059*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_EMEnriched_Pt30to80, lumi));
    }

    void testGetExpectedQCD_EMEnriched_Pt80to170EventsFor20pb() {
        ASSERT_EQUAL(0.906e6 * 0.148*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_EMEnriched_Pt80to170, lumi));
    }

    void testGetExpectedQCD_BCtoE_Pt20to30EventsFor20pb() {
        ASSERT_EQUAL(0.2355e9 * 0.00046*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_BCtoE_Pt20to30, lumi));
    }

    void testGetExpectedQCD_BCtoE_Pt30to80EventsFor20pb() {
        ASSERT_EQUAL(0.0593e9 * 0.00234*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_BCtoE_Pt30to80, lumi));
    }

    void testGetExpectedQCD_BCtoE_Pt80to170EventsFor20pb() {
        ASSERT_EQUAL(0.906e6 * 0.0104*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_BCtoE_Pt80to170, lumi));
    }

    void testGetExpectedVQQEventsFor20pb() {
        ASSERT_EQUAL(36.*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::VQQ, lumi));
    }

    void testGetExpectedsingleTop_And_WEventsFor20pb() {
        ASSERT_EQUAL(10.6*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::singleTop_And_W, lumi));
    }

    void testGetExpectedsingleTopTChannelEventsFor20pb() {
        ASSERT_EQUAL_DELTA(21.53*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::singleTopTChannel, lumi), 0.1);
    }

    void testGetExpectedsingleTopSChannelEventsFor20pb() {
        ASSERT_EQUAL(1.40*lumi, xSectionProvider.getExpectedNumberOfEvents(DataType::singleTopSChannel, lumi));
    }

    void testGetExpectedDataEventsFor20pb() {
        ASSERT_EQUAL(0, xSectionProvider.getExpectedNumberOfEvents(DataType::DATA, lumi));
    }

};

extern cute::suite make_suite_TestCrossSectionProvider() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedTTbarEventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedWjetsEventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedZjetsEventsFor20pb));

    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedQCD_EMEnriched_Pt20to30EventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedQCD_EMEnriched_Pt30to80EventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedQCD_EMEnriched_Pt80to170EventsFor20pb));

    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedQCD_BCtoE_Pt20to30EventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedQCD_BCtoE_Pt30to80EventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedQCD_BCtoE_Pt80to170EventsFor20pb));

    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedVQQEventsFor20pb));

    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedsingleTop_And_WEventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedsingleTopTChannelEventsFor20pb));
    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedsingleTopSChannelEventsFor20pb));

    s.push_back(CUTE_SMEMFUN(TestCrossSectionProvider, testGetExpectedDataEventsFor20pb));

    return s;
}

