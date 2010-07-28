#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestJetReader.h"
#include "Readers/JetReader.h"

using namespace BAT;

static boost::shared_ptr<TChain> input;
static JetReader* reader;
//static VariableReader<unsigned int>* numberOfJetsReader;//left here to demonstrate that the normal way doesn't work
void setUpJetReader() {
	input = boost::shared_ptr<TChain>(new TChain("configurableAnalysis/eventB"));
	reader = new JetReader(input);
	input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
	input->SetBranchStatus("*", 0);
	//	numberOfJetsReader = new VariableReader<unsigned int>(input, "Njets");//left here to demonstrate that the normal way doesn't work
	reader->initialise();
	//	numberOfJetsReader->initialise();//left here to demonstrate that the normal way doesn't work
	input->GetEntry(1);
}

void tearDownJetReader(){
	delete reader;
}
void testReadJetsSize() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	//	reading the same variable two times produces a segmentation fault!
	//	ASSERT_EQUAL(numberOfJetsReader->getVariable(), jets.size());//left here to demonstrate that the normal way doesn't work
	ASSERT_EQUAL(8, jets.size());
	tearDownJetReader();
}

void testReadFirstJetEnergy() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	Jet firstJet = jets.front();
	ASSERT_EQUAL_DELTA(210.836, firstJet.energy(), 0.001);
	tearDownJetReader();
}

void testReadFirstJetEMF() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	Jet firstJet = jets.front();
	ASSERT_EQUAL_DELTA(0.436829, firstJet.emf(), 0.00001);
	tearDownJetReader();
}

void testReadFirstJetn90Hits() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	Jet firstJet = jets.front();
	ASSERT_EQUAL_DELTA(136, firstJet.n90Hits(), 0.1);
	tearDownJetReader();
}

void testReadFirstJetfHPD() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	Jet firstJet = jets.front();
	ASSERT_EQUAL_DELTA(0.378509, firstJet.fHPD(), 0.00001);
	tearDownJetReader();
}

cute::suite make_suite_TestJetReader() {
	cute::suite s;
	s.push_back(CUTE(testReadJetsSize));
	s.push_back(CUTE(testReadFirstJetEnergy));
	s.push_back(CUTE(testReadFirstJetEMF));
	s.push_back(CUTE(testReadFirstJetn90Hits));
	s.push_back(CUTE(testReadFirstJetfHPD));
	return s;
}

