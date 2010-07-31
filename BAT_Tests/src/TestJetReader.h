#include "cute_suite.h"
#include "Readers/JetReader.h"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace BAT;

struct TestJetReader {
private:
	boost::shared_ptr<TChain> input;
	boost::scoped_ptr<JetReader> reader;

public:
	TestJetReader() :
		input(new TChain("configurableAnalysis/eventB")), reader(new JetReader(input)) {
		input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
		input->SetBranchStatus("*", 0);
		//	numberOfJetsReader = new VariableReader<unsigned int>(input, "Njets");//left here to demonstrate that the normal way doesn't work
		reader->initialise();
		//	numberOfJetsReader->initialise();//left here to demonstrate that the normal way doesn't work
		input->GetEntry(1);
	}

	void testReadJetsSize() {
		std::vector<Jet> jets = reader->getJets();
		//	reading the same variable two times produces a segmentation fault!
		//	ASSERT_EQUAL(numberOfJetsReader->getVariable(), jets.size());//left here to demonstrate that the normal way doesn't work
		ASSERT_EQUAL(8, jets.size());
	}

	void testReadFirstJetEnergy() {
		std::vector<Jet> jets = reader->getJets();
		Jet firstJet = jets.front();
		ASSERT_EQUAL_DELTA(210.836, firstJet.energy(), 0.001);
	}

	void testReadFirstJetEMF() {
		std::vector<Jet> jets = reader->getJets();
		Jet firstJet = jets.front();
		ASSERT_EQUAL_DELTA(0.436829, firstJet.emf(), 0.00001);
	}

	void testReadFirstJetn90Hits() {
		std::vector<Jet> jets = reader->getJets();
		Jet firstJet = jets.front();
		ASSERT_EQUAL_DELTA(136, firstJet.n90Hits(), 0.1);
	}

	void testReadFirstJetfHPD() {
		std::vector<Jet> jets = reader->getJets();
		Jet firstJet = jets.front();
		ASSERT_EQUAL_DELTA(0.378509, firstJet.fHPD(), 0.00001);
	}
};
extern cute::suite make_suite_TestJetReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestJetReader,testReadJetsSize));
	s.push_back(CUTE_SMEMFUN(TestJetReader,testReadFirstJetEnergy));
	s.push_back(CUTE_SMEMFUN(TestJetReader,testReadFirstJetEMF));
	s.push_back(CUTE_SMEMFUN(TestJetReader,testReadFirstJetn90Hits));
	s.push_back(CUTE_SMEMFUN(TestJetReader,testReadFirstJetfHPD));
	return s;
}
