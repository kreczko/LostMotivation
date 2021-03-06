#include "cute_suite.h"
#include "Readers/JetReader.h"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace BAT;

struct TestJetReader {
private:
	boost::shared_ptr<TChain> input;
	boost::scoped_ptr<JetReader> reader, PFreader;
	JetCollection jets, pfjets;
	Jet firstJet, firstPFJet;

public:
	TestJetReader() :
		input(new TChain("configurableAnalysis/eventB")), reader(new JetReader(input)), PFreader(new JetReader(input,
				Jet::ParticleFlow)), jets(), pfjets(), firstJet(), firstPFJet() {
		input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
		input->SetBranchStatus("*", 0);
		reader->initialise();
		PFreader->initialise();
		input->GetEntry(1);
		jets = reader->getJets();
		pfjets = PFreader->getJets();
		firstJet = jets.front();
		firstPFJet = pfjets.front();
	}

	void testReadJetsSize() {
		ASSERT_EQUAL(8, jets.size());
	}

	void testReadFirstJetEnergy() {
		ASSERT_EQUAL_DELTA(210.836, firstJet.energy(), 0.001);
	}

	void testReadFirstJetEMF() {
		ASSERT_EQUAL_DELTA(0.436829, firstJet.emf(), 0.00001);
	}

	void testReadFirstJetn90Hits() {
		ASSERT_EQUAL_DELTA(136, firstJet.n90Hits(), 0.1);
	}

	void testReadFirstJetfHPD() {
		ASSERT_EQUAL_DELTA(0.378509, firstJet.fHPD(), 0.00001);
	}

	void testReadPFJetsSize() {
		ASSERT_EQUAL(7, pfjets.size());
	}

	void testReadFirstPFJetEnergy() {
		ASSERT_EQUAL_DELTA(197.366, firstPFJet.energy(), 0.001);
	}

	void testReadFirstPFJetEMF() {
		ASSERT_EQUAL_DELTA(0, firstPFJet.emf(), 0.00001);
	}

	void testReadFirstPFJetn90Hits() {
		ASSERT_EQUAL_DELTA(0, firstPFJet.n90Hits(), 0.1);
	}

	void testReadFirstPFJetfHPD() {
		ASSERT_EQUAL_DELTA(0, firstPFJet.fHPD(), 0.00001);
	}

	void testUsedAlgorithmDefault(){
		ASSERT_EQUAL(Jet::Calo_AntiKT_Cone05, firstJet.getUsedAlgorithm());
	}

	void testUsedAlgorithmPFJet(){
		ASSERT_EQUAL(Jet::ParticleFlow, firstPFJet.getUsedAlgorithm());
	}
};
extern cute::suite make_suite_TestJetReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadJetsSize));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstJetEnergy));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstJetEMF));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstJetn90Hits));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstJetfHPD));

	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadPFJetsSize));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstPFJetEnergy));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstPFJetEMF));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstPFJetn90Hits));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testReadFirstPFJetfHPD));

	s.push_back(CUTE_SMEMFUN(TestJetReader, testUsedAlgorithmDefault));
	s.push_back(CUTE_SMEMFUN(TestJetReader, testUsedAlgorithmPFJet));
	return s;
}
