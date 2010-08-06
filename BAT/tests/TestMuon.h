#include "cute/cute.h"
#include "cute/cute_suite.h"

#include "../interface/RecoObjects/Muon.h"

using namespace BAT;

struct TestMuon {
private:
	Muon goodNonIsolatedMuon;
	Muon goodIsolatedMuon;
	Muon nonGlobalMuon;
	Muon badMuonLowPt;
	Muon badEtaMuon;

	void setMuonConditions() {
		Muon::goodMuonMinimalPt = 15;
		Muon::goodMuonMaximalAbsoluteEta = 2.5;
		Muon::isolatedMuonMaximalRelativeIsolation = 0.2;
	}
	void setUpGoodMuon() {
		goodNonIsolatedMuon.makeGlobal(true);
		goodNonIsolatedMuon.setEcalIsolation(200);
		goodNonIsolatedMuon.setHcalIsolation(200);
		goodNonIsolatedMuon.setTrackerIsolation(200);
	}

	void setUpGoodIsolatedMuon() {
		goodIsolatedMuon.makeGlobal(true);
		goodIsolatedMuon.setEcalIsolation(2);
		goodIsolatedMuon.setHcalIsolation(2);
		goodIsolatedMuon.setTrackerIsolation(2);
	}

	void setUpNonGlobalMuon() {
		nonGlobalMuon.makeGlobal(false);
	}

	void setUpBadMuonLowPt() {
		badMuonLowPt.makeGlobal(true);
	}

	void setUpBadEtaMuon() {
		badEtaMuon.makeGlobal(true);
		assert(fabs(badEtaMuon.eta()) > Muon::goodMuonMaximalAbsoluteEta);
		assert(badEtaMuon.pt() > Muon::goodMuonMinimalPt);
	}
public:
	TestMuon() :
		goodNonIsolatedMuon(200, 199, 1, 1), goodIsolatedMuon(goodNonIsolatedMuon), nonGlobalMuon(goodNonIsolatedMuon),
				badMuonLowPt(15., 14., 1., 1.), badEtaMuon(450., 50., 50., 444.) {
		setMuonConditions();
		setUpGoodMuon();
		setUpGoodIsolatedMuon();
		setUpNonGlobalMuon();
		setUpBadMuonLowPt();
		setUpBadEtaMuon();
	}

	void testGlobalMuon() {
		ASSERT_EQUAL(true, goodNonIsolatedMuon.isGlobal());
		goodNonIsolatedMuon.makeGlobal(false);
		ASSERT_EQUAL(false, goodNonIsolatedMuon.isGlobal());
	}

	void testEcalIsolation() {
		goodNonIsolatedMuon.setEcalIsolation(1234.);
		ASSERT_EQUAL(1234., goodNonIsolatedMuon.ecalIsolation());
	}

	void testHcalIsolation() {
		goodNonIsolatedMuon.setHcalIsolation(1234.);
		ASSERT_EQUAL(1234., goodNonIsolatedMuon.hcalIsolation());
	}

	void testTrackerIsolation() {
		goodNonIsolatedMuon.setTrackerIsolation(1234.);
		ASSERT_EQUAL(1234., goodNonIsolatedMuon.trackerIsolation());
	}

	void testRelativeIsolation() {
		float relativeIsolation = (goodNonIsolatedMuon.ecalIsolation() + goodNonIsolatedMuon.hcalIsolation()
				+ goodNonIsolatedMuon.trackerIsolation()) / goodNonIsolatedMuon.pt();
		ASSERT_EQUAL(relativeIsolation, goodNonIsolatedMuon.relativeIsolation());
	}

	void testIsIsolated() {
		ASSERT_EQUAL(true, goodIsolatedMuon.isIsolated());
	}

	void testIsNotIsolated() {
		ASSERT_EQUAL(false, goodNonIsolatedMuon.isIsolated());
	}

	void testIsGoodMuon() {
		ASSERT_EQUAL(true, goodNonIsolatedMuon.isGood());
		ASSERT_EQUAL(true, goodIsolatedMuon.isGood());
	}

	void testNonGlobalMuonIsGood() {
		ASSERT_EQUAL(false, nonGlobalMuon.isGood());
	}

	void testBadMuonLowPtIsGood() {
		ASSERT_EQUAL(false, badMuonLowPt.isGood());
	}

	void testBadEtaMuonIsGood() {
		ASSERT_EQUAL(false, badEtaMuon.isGood());
	}
};

extern cute::suite make_suite_TestMuon() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestMuon, testGlobalMuon));
	s.push_back(CUTE_SMEMFUN(TestMuon, testEcalIsolation));
	s.push_back(CUTE_SMEMFUN(TestMuon, testHcalIsolation));
	s.push_back(CUTE_SMEMFUN(TestMuon, testTrackerIsolation));
	s.push_back(CUTE_SMEMFUN(TestMuon, testRelativeIsolation));

	s.push_back(CUTE_SMEMFUN(TestMuon, testIsIsolated));
	s.push_back(CUTE_SMEMFUN(TestMuon, testIsNotIsolated));
	s.push_back(CUTE_SMEMFUN(TestMuon, testIsGoodMuon));
	s.push_back(CUTE_SMEMFUN(TestMuon, testNonGlobalMuonIsGood));
	s.push_back(CUTE_SMEMFUN(TestMuon, testBadMuonLowPtIsGood));
	s.push_back(CUTE_SMEMFUN(TestMuon, testBadEtaMuonIsGood));

	return s;
}
