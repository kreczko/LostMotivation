#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "TChain.h"
#include "../interface/Readers/MuonReader.h"
#include "InputFiles.h"

using namespace BAT;

struct TestMuonReader {
private:
	boost::shared_ptr<TChain> input;
	boost::scoped_ptr<MuonReader> reader;
	MuonCollection muons;
	Muon leadingMuon;
public:
	TestMuonReader() :
		input(new TChain("configurableAnalysis/eventB")),
		reader(new MuonReader(input)),
		muons(),
		leadingMuon() {
		input->Add(InputFile::ttbar);
		input->SetBranchStatus("*", 0);
		reader->initialise();
		input->GetEntry(1);
		muons = reader->getMuons();
		leadingMuon = muons.front();
	}

	void testNumberOfMuons(){
		ASSERT_EQUAL(1, muons.size());
	}

	void testLeadingMuonFourVector(){
		ASSERT_EQUAL_DELTA(29.6267, leadingMuon.energy(), 0.0001);
		ASSERT_EQUAL_DELTA(-27.3677, leadingMuon.px(), 0.0001);
		ASSERT_EQUAL_DELTA(8.21059, leadingMuon.py(), 0.0001);
		ASSERT_EQUAL_DELTA(7.83097, leadingMuon.pz(), 0.0001);
	}

	void testLeadingMuonRelativeIsolation(){
		ASSERT_EQUAL_DELTA(0.90083, leadingMuon.relativeIsolation(), 0.00001);
	}

	void testLeadingMuonIsGlobal(){
		ASSERT_EQUAL(true, leadingMuon.isGlobal());
	}
};

extern cute::suite make_suite_TestMuonReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestMuonReader,testNumberOfMuons));
	s.push_back(CUTE_SMEMFUN(TestMuonReader,testLeadingMuonFourVector));
	s.push_back(CUTE_SMEMFUN(TestMuonReader,testLeadingMuonRelativeIsolation));
	s.push_back(CUTE_SMEMFUN(TestMuonReader,testLeadingMuonIsGlobal));
	return s;
}
