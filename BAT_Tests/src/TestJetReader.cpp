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
	input->Add("/storage/top/mc/spring10_7TeV_v4/MG/e20skim_ttjet/*_1.root");
	input->GetEntries();
	input->SetBranchStatus("*", 0);
	reader = new JetReader(input);
	//	numberOfJetsReader = new VariableReader<unsigned int>(input, "Njets");//left here to demonstrate that the normal way doesn't work
	reader->initialise();
	//	numberOfJetsReader->initialise();//left here to demonstrate that the normal way doesn't work
	input->GetEntry(1);
}

void testReadJetsSize() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	//	reading the same variable two times produces a segmentation fault!
	//	ASSERT_EQUAL(numberOfJetsReader->getVariable(), jets.size());//left here to demonstrate that the normal way doesn't work
	ASSERT_EQUAL(8, jets.size());
}

void testReadFirstJetEnergy() {
	setUpJetReader();
	std::vector<Jet> jets = reader->getJets();
	Jet firstJet = jets.front();
	ASSERT_EQUAL_DELTA(210.836, firstJet.energy(), 0.001);
}

cute::suite make_suite_TestJetReader() {
	cute::suite s;
	s.push_back(CUTE(testReadJetsSize));
	s.push_back(CUTE(testReadFirstJetEnergy));
	return s;
}

