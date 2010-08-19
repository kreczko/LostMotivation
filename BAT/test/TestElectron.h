#include "cute/cute.h"
#include "cute/cute_suite.h"

#include "../interface/RecoObjects/Electron.h"
#include "../interface/VBTF_ElectronID.h"

using namespace BAT;

struct TestElectron {
private:
    float invalidSwissCross;
    Electron isolatedElectron;
    Electron goodElectron;
    Electron badEtElectron;
    Electron badEtaElectron;
    Electron badInCrackElectron;
    Electron badD0Electron;
    Electron badElectronFromConversion;
    Electron looseElectron;
    Electron badLooseElectronNoID;
    Electron badElectronNoID;
public:
    TestElectron() :
        invalidSwissCross(2), isolatedElectron(30., 10., 0., 0.), goodElectron(30., 20., 5., 2.), badEtElectron(20.,
                10., 0., 5.), badEtaElectron(400., 50., 50., 380), badInCrackElectron(400., 50., 50., 380),
                badD0Electron(40., 5., 5., 0.), badElectronFromConversion(400., 50., 50., 380), looseElectron(40., 20.,
                        20., 0.), badLooseElectronNoID(30., 20., 5., 2.), badElectronNoID(30., 20., 5., 2.) {
        setElectronConditions();
        setIsolatedElectron();
        setGoodElectron();
        setBadEtElectron();
        setBadEtaElectron();
        setBadD0Electron();
        setBadInCrackElectron();
        setElectronFromConversion();
        setLooseElectron();
        setBadLooseElectronNoID();
        setBadElectronNoID();
    }

private:
    void setElectronConditions() {
        Electron::isolatedElectronMaximalRelativeIsolation = 0.1;
        Electron::goodElectronMaximalAbsoluteEta = 2.1;
        Electron::goodElectronMinimalEt = 20.;
        Electron::goodElectronMaximalDistanceFromInteractionPoint = 0.02;
        Electron::goodElectronMaximalSwissCross = 0.95;
        Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion = 0;
        Electron::looseElectronMaximalAbsoluteEta = 2.5;
        Electron::looseElectronMinimalEt = 25;
        Electron::looseIsolatedElectronMaximalRelativeIsolation = 1.0;
    }
    void setIsolatedElectron() {
        isolatedElectron.setEcalIsolation(1.);
        isolatedElectron.setHcalIsolation(1.);
        isolatedElectron.setTrackerIsolation(0.9);
    }

    void setGoodElectron() {
        goodElectron.setHcalIsolation(0.5);
        goodElectron.setEcalIsolation(0.3);
        goodElectron.setTrackerIsolation(0.4);
        goodElectron.setSuperClusterEta(1);
        goodElectron.setD0(0.01);
        assert(fabs(goodElectron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
        assert(fabs(goodElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        assert(goodElectron.et() > Electron::goodElectronMinimalEt);
    }

    void setBadEtElectron() {
        badEtElectron.setD0(0.01);
        badEtElectron.setSuperClusterEta(1);
        assert(fabs(badEtElectron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
        assert(fabs(badEtElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        //and fails the selected
        assert(badEtElectron.et() < Electron::goodElectronMinimalEt);
    }

    void setBadEtaElectron() {
        badEtaElectron.setSuperClusterEta(2.6);
        badEtaElectron.setD0(0.001);
        //make sure it passes all other requirements
        assert(badEtaElectron.et() > Electron::goodElectronMinimalEt);
        assert(fabs(badEtaElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        //and fails the selected
        assert(fabs(badEtaElectron.superClusterEta()) > Electron::goodElectronMaximalAbsoluteEta);
    }

    void setBadD0Electron() {
        badD0Electron.setD0(300.);
        //make sure it passes all other requirements
        assert(badD0Electron.et() > Electron::goodElectronMinimalEt);
        assert(fabs(badD0Electron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
        //and fails the selected
        assert(fabs(badD0Electron.d0()) > Electron::goodElectronMaximalDistanceFromInteractionPoint);
    }

    void setBadInCrackElectron() {
        badInCrackElectron.setSuperClusterEta(1.5);
        //make sure it passes all other requirements
        assert(badInCrackElectron.et() > Electron::goodElectronMinimalEt);
        assert(fabs(badInCrackElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        //and fails the selected
        assert(fabs(badInCrackElectron.superClusterEta()) < Electron::goodElectronMaximalAbsoluteEta);
        assert(badInCrackElectron.isInCrack());
    }

    void setElectronFromConversion() {
        badElectronFromConversion = Electron(400., 50., 50., 380);
        badElectronFromConversion.setNumberOfMissingInnerLayerHits(1);
    }

    void setLooseElectron() {
        looseElectron = Electron(40., 20., 20., 0.);
        looseElectron.setRobustLooseID(true);
        looseElectron.setSuperClusterEta(1);
        looseElectron.setEcalIsolation(0);
        looseElectron.setTrackerIsolation(0);
        looseElectron.setHcalIsolation(0);
    }

    void setBadLooseElectronNoID() {
        badLooseElectronNoID = Electron(30., 20., 5., 2.);
        badLooseElectronNoID.setHcalIsolation(0.5);
        badLooseElectronNoID.setEcalIsolation(0.3);
        badLooseElectronNoID.setTrackerIsolation(0.4);
    }

    void setBadElectronNoID() {
        badElectronNoID = Electron(30., 20., 5., 2.);
        badElectronNoID.setHcalIsolation(0.5);
        badElectronNoID.setEcalIsolation(0.3);
        badElectronNoID.setTrackerIsolation(0.4);
        badElectronNoID.setSigmaIEtaIEta(VBTF_W70::MaximalDEtaIn_BarrelRegion + 2);
    }

public:
    void testEcalIsolation() {
        ASSERT_EQUAL_DELTA(0.3, goodElectron.ecalIsolation(), 0.01);
    }

    void testHcalIsolation() {
        ASSERT_EQUAL_DELTA(0.5, goodElectron.hcalIsolation(), 0.01);
    }

    void testTrackerIsolation() {
        ASSERT_EQUAL_DELTA(0.4, goodElectron.trackerIsolation(), 0.01);
    }

    void testBadEtElectron() {
        ASSERT(badEtElectron.isGood() == false);
    }

    void testBadEtaElectron() {
        ASSERT(badEtaElectron.isGood() == false);
    }

    void testBadInCrackElectron() {
        ASSERT(badInCrackElectron.isGood() == false);
    }

    void testElectronFromConversion() {
        ASSERT(badElectronFromConversion.isFromConversion());
    }
    void testBadD0Electron() {
        ASSERT(badD0Electron.isGood() == false);
    }

    void testLooseElectron() {
        ASSERT_EQUAL(false, badD0Electron.isLoose());
        ASSERT_EQUAL(true, looseElectron.isLoose());
    }

    void testRelativeIsolation() {
        ASSERT_EQUAL_DELTA(2.9 / 30., isolatedElectron.relativeIsolation(), 0.01);
        ASSERT(isolatedElectron.isIsolated());
    }

    void testGoodElectron() {
        ASSERT(goodElectron.isGood());
    }

    void testBadLooseElectronNoID() {
        ASSERT(badLooseElectronNoID.isLoose() == false);
    }

    void testBadElectronNoID() {
        ASSERT(badElectronNoID.isGood() == false);
    }

    void testVBTFW70Barrel() {
        Electron electron = Electron(50, 40, 30, 0);
        electron.setSigmaIEtaIEta(VBTF_W70::MaximalSigmaIEtaIEta_BarrelRegion - 0.01);
        electron.setDPhiIn(VBTF_W70::MaximalDPhiIn_BarrelRegion - 0.01);
        electron.setDEtaIn(VBTF_W70::MaximalDEtaIn_BarrelRegion - 0.01);
        electron.setHadOverEm(VBTF_W70::MaximalHadOverEm_BarrelRegion - 0.01);
        electron.setSuperClusterEta(0);
        assert(electron.isInBarrelRegion());
        ASSERT_EQUAL(true, electron.VBTF_W70_ElectronID());
    }

    void testVBTFW70Endcap() {
        Electron electron = Electron(50, 3, 0, 40);
        electron.setSigmaIEtaIEta(VBTF_W70::MaximalSigmaIEtaIEta_EndcapRegion - 0.01);
        electron.setDPhiIn(VBTF_W70::MaximalDPhiIn_EndcapRegion - 0.01);
        electron.setDEtaIn(VBTF_W70::MaximalDEtaIn_EndcapRegion - 0.01);
        electron.setHadOverEm(VBTF_W70::MaximalHadOverEm_EndcapRegion - 0.01);
        electron.setSuperClusterEta(2.6);
        assert(electron.isInEndCapRegion());
        ASSERT_EQUAL(true, electron.VBTF_W70_ElectronID());
    }

    void testElectronCharge() {
        Electron electron = Electron(50, 3, 0, 40);
        electron.setCharge(2);
        ASSERT_EQUAL(2, electron.charge());
    }

    void testElectronChargeInCopy() {
        Electron electron = Electron(50, 3, 0, 40);
        electron.setCharge(2);
        Electron copyElectron(electron);
        ASSERT_EQUAL(2, copyElectron.charge());
    }

    void testElectronInCollection() {
        ElectronCollection coll;
        ElectronPointer electron(new Electron(50, 3, 0, 40));
        ElectronPointer electron2(new Electron(50, 3, 0, 40));
        electron->setCharge(2);
        electron2->setCharge(2);
        coll.push_back(electron);
        coll.push_back(electron2);
        ASSERT_EQUAL(2, coll.front()->charge());
    }

    void testElectronInSTDCollection() {
        std::vector<Electron> coll;
        Electron electron(50, 3, 0, 40);
        Electron electron2(50, 3, 0, 40);
        electron.setCharge(2);
        electron2.setCharge(2);
        coll.push_back(electron);
        coll.push_back(electron2);
        ASSERT_EQUAL(2, coll.front().charge());
    }

    void testElectronSetMass() {
        Electron electron = Electron(50, 3, 0, 40);
        electron.setMass(500);
        ASSERT_EQUAL(500, electron.mass());
    }

    void testSwissCrossBarrel() {
        goodElectron.setSuperClusterEta(1);
        goodElectron.setSwissCross(invalidSwissCross);
        goodElectron.setIsEcalDriven(true);
        ASSERT_EQUAL(true, goodElectron.isEcalSpike());
        ASSERT_EQUAL(false, goodElectron.isGood());
    }

    void testSwissCrossEndcap() {
        goodElectron.setSuperClusterEta(2);
        goodElectron.setSwissCross(invalidSwissCross);
        goodElectron.setIsEcalDriven(true);
        ASSERT_EQUAL(false, goodElectron.isEcalSpike());
        ASSERT_EQUAL(true, goodElectron.isGood());
    }

    void testSwissCrossNotEcalDriven() {
        goodElectron.setSuperClusterEta(2);
        goodElectron.setSwissCross(invalidSwissCross);
        goodElectron.setIsEcalDriven(false);
        ASSERT_EQUAL(false, goodElectron.isEcalSpike());
        ASSERT_EQUAL(true, goodElectron.isGood());
    }

};
extern cute::suite make_suite_TestElectron() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestElectron, testRelativeIsolation));
    s.push_back(CUTE_SMEMFUN(TestElectron, testGoodElectron));
    s.push_back(CUTE_SMEMFUN(TestElectron, testBadEtElectron));
    s.push_back(CUTE_SMEMFUN(TestElectron, testBadEtaElectron));
    s.push_back(CUTE_SMEMFUN(TestElectron, testBadD0Electron));
    s.push_back(CUTE_SMEMFUN(TestElectron, testBadInCrackElectron));
    s.push_back(CUTE_SMEMFUN(TestElectron, testElectronFromConversion));
    s.push_back(CUTE_SMEMFUN(TestElectron, testEcalIsolation));
    s.push_back(CUTE_SMEMFUN(TestElectron, testHcalIsolation));
    s.push_back(CUTE_SMEMFUN(TestElectron, testTrackerIsolation));
    s.push_back(CUTE_SMEMFUN(TestElectron, testLooseElectron));
    s.push_back(CUTE_SMEMFUN(TestElectron, testBadLooseElectronNoID));
    s.push_back(CUTE_SMEMFUN(TestElectron, testBadElectronNoID));
    s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFW70Barrel));
    s.push_back(CUTE_SMEMFUN(TestElectron, testVBTFW70Endcap));
    s.push_back(CUTE_SMEMFUN(TestElectron, testElectronCharge));
    s.push_back(CUTE_SMEMFUN(TestElectron, testElectronChargeInCopy));
    s.push_back(CUTE_SMEMFUN(TestElectron, testElectronInCollection));
    s.push_back(CUTE_SMEMFUN(TestElectron, testElectronSetMass));
    s.push_back(CUTE_SMEMFUN(TestElectron, testElectronInSTDCollection));
    s.push_back(CUTE_SMEMFUN(TestElectron, testSwissCrossBarrel));
    s.push_back(CUTE_SMEMFUN(TestElectron, testSwissCrossEndcap));
    s.push_back(CUTE_SMEMFUN(TestElectron, testSwissCrossNotEcalDriven));
    return s;
}
