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
public:
    TestCrossSectionProvider() :
        xSectionProvider() {

    }

    ~TestCrossSectionProvider() {

    }

    void testGetExpectedTTbarEventsFor20pb() {
        ASSERT_EQUAL(157.5*20, xSectionProvider.getExpectedNumberOfEvents(DataType::ttbar, 20));
    }

    void testGetExpectedWjetsEventsFor20pb() {
        ASSERT_EQUAL(31314.*20, xSectionProvider.getExpectedNumberOfEvents(DataType::Wjets, 20));
    }

    void testGetExpectedZjetsEventsFor20pb() {
        ASSERT_EQUAL(3048.*20, xSectionProvider.getExpectedNumberOfEvents(DataType::Zjets, 20));
    }

    void testGetExpectedQCD_EMEnriched_Pt20to30EventsFor20pb() {
        ASSERT_EQUAL(0.2355e9 * 0.0073*20, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_EMEnriched_Pt20to30, 20));
    }

    void testGetExpectedQCD_EMEnriched_Pt30to80EventsFor20pb() {
        ASSERT_EQUAL(0.0593e9 * 0.059*20, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_EMEnriched_Pt30to80, 20));
    }

    void testGetExpectedQCD_EMEnriched_Pt80to170EventsFor20pb() {
        ASSERT_EQUAL(0.906e6 * 0.148*20, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_EMEnriched_Pt80to170, 20));
    }

    void testGetExpectedQCD_BCtoE_Pt20to30EventsFor20pb() {
        ASSERT_EQUAL(0.2355e9 * 0.00046*20, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_BCtoE_Pt20to30, 20));
    }

    void testGetExpectedQCD_BCtoE_Pt30to80EventsFor20pb() {
        ASSERT_EQUAL(0.0593e9 * 0.00234*20, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_BCtoE_Pt30to80, 20));
    }

    void testGetExpectedQCD_BCtoE_Pt80to170EventsFor20pb() {
        ASSERT_EQUAL(0.906e6 * 0.0104*20, xSectionProvider.getExpectedNumberOfEvents(DataType::QCD_BCtoE_Pt80to170, 20));
    }

    void testGetExpectedVQQEventsFor20pb() {
        ASSERT_EQUAL(36.*20, xSectionProvider.getExpectedNumberOfEvents(DataType::VQQ, 20));
    }

    void testGetExpectedsingleTop_And_WEventsFor20pb() {
        ASSERT_EQUAL(10.6*20, xSectionProvider.getExpectedNumberOfEvents(DataType::singleTop_And_W, 20));
    }

    void testGetExpectedsingleTopTChannelEventsFor20pb() {
        ASSERT_EQUAL_DELTA(21.53*20, xSectionProvider.getExpectedNumberOfEvents(DataType::singleTopTChannel, 20), 0.1);
    }

    void testGetExpectedsingleTopSChannelEventsFor20pb() {
        ASSERT_EQUAL(1.40*20, xSectionProvider.getExpectedNumberOfEvents(DataType::singleTopSChannel, 20));
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

    return s;
}

