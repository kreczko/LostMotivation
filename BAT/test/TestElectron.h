#include "cute/cute.h"
#include "cute/cute_suite.h"

#include "../interface/RecoObjects/Electron.h"
#include "../interface/VBTF_ElectronID.h"

using namespace BAT;

struct TestElectron {
private:
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
        isolatedElectron(30., 10., 0., 0.), goodElectron(30., 20., 5., 2.), badEtElectron(20., 10., 0., 5.),
                badEtaElectron(400., 50., 50., 380), badInCrackElectron(400., 50., 50., 380), badD0Electron(40., 5.,
                        5., 0.), badElectronFromConversion(400., 50., 50., 380), looseElectron(40., 20., 20., 0.),
                badLooseElectronNoID(30., 20., 5., 2.), badElectronNoID(30., 20., 5., 2.) {
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
        Electron::goodElectronMaximalDistanceFromInteractionPoint = 200.;
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
        goodElectron.setVBTF_W70_ElectronID(true);

        ASSERT(fabs(goodElectron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
        ASSERT(fabs(goodElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        ASSERT(goodElectron.et() > Electron::goodElectronMinimalEt);
    }

    void setBadEtElectron() {
        badEtElectron.setD0(100.);
        badEtElectron.setVBTF_W70_ElectronID(true);
        ASSERT(fabs(badEtElectron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
        ASSERT(fabs(badEtElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        //and fails the selected
        ASSERT(badEtElectron.et() < Electron::goodElectronMinimalEt);
    }

    void setBadEtaElectron() {
        badEtaElectron.setSuperClusterEta(2.6);
        badEtaElectron.setVBTF_W70_ElectronID(true);
        //make sure it passes all other requirements
        ASSERT(badEtaElectron.et() > Electron::goodElectronMinimalEt);
        ASSERT(fabs(badEtaElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        //and fails the selected
        ASSERT(fabs(badEtaElectron.superClusterEta()) > Electron::goodElectronMaximalAbsoluteEta);
    }

    void setBadD0Electron() {
        badD0Electron.setD0(300.);
        badD0Electron.setVBTF_W70_ElectronID(true);
        //make sure it passes all other requirements
        ASSERT(badD0Electron.et() > Electron::goodElectronMinimalEt);
        ASSERT(fabs(badD0Electron.eta()) < Electron::goodElectronMaximalAbsoluteEta);
        //and fails the selected
        ASSERT(fabs(badD0Electron.d0()) > Electron::goodElectronMaximalDistanceFromInteractionPoint);
    }

    void setBadInCrackElectron() {
        badInCrackElectron.setVBTF_W70_ElectronID(true);
        badInCrackElectron.setSuperClusterEta(1.5);
        //make sure it passes all other requirements
        ASSERT(badInCrackElectron.et() > Electron::goodElectronMinimalEt);
        ASSERT(fabs(badInCrackElectron.d0()) < Electron::goodElectronMaximalDistanceFromInteractionPoint);
        //and fails the selected
        ASSERT(fabs(badInCrackElectron.superClusterEta()) < Electron::goodElectronMaximalAbsoluteEta);
        ASSERT(badInCrackElectron.isInCrack());
    }

    void setElectronFromConversion() {
        badElectronFromConversion = Electron(400., 50., 50., 380);
        badElectronFromConversion.setNumberOfMissingInnerLayerHits(1);
        badElectronFromConversion.setVBTF_W70_ElectronID(true);
    }

    void setLooseElectron() {
        looseElectron = Electron(40., 20., 20., 0.);
        looseElectron.setRobustLooseID(true);
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
        ASSERT(badD0Electron.isLoose() == false);
        ASSERT(looseElectron.isLoose());
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
    return s;
}
