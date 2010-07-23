#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestNTupleReader.h"
#include "Readers/NTupleEventReader.h"
#include "Event.h"

using namespace BAT;
static NTupleEventReader* TTbarReader;
static NTupleEventReader* QCDenri1Reader;
static NTupleEventReader* QCDenri2Reader;
static NTupleEventReader* QCDenri3Reader;

static NTupleEventReader* QCDbce1Reader;
static NTupleEventReader* QCDbce2Reader;
static NTupleEventReader* QCDbce3Reader;

static NTupleEventReader* WjetsReader;
static NTupleEventReader* ZJetsReader;
static NTupleEventReader* TWReader;
static NTupleEventReader* TChanReader;
static NTupleEventReader* DataReader;
static TChain* chain;

void setUpNTupleReader() {
	TTbarReader = new NTupleEventReader();

	QCDenri1Reader = new NTupleEventReader();
	QCDenri2Reader = new NTupleEventReader();
	QCDenri3Reader = new NTupleEventReader();

	QCDbce1Reader = new NTupleEventReader();
	QCDbce2Reader = new NTupleEventReader();
	QCDbce3Reader = new NTupleEventReader();

	WjetsReader = new NTupleEventReader();
	ZJetsReader = new NTupleEventReader();
	TWReader = new NTupleEventReader();
	TChanReader = new NTupleEventReader();
	TChanReader = new NTupleEventReader();
	DataReader  = new NTupleEventReader();

	TTbarReader->addInputFile("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
	QCDenri1Reader->addInputFile("/storage/top/mc/V4/pythia/e20skim_enri1/e20skim_nTuple_enri1_f_1_3_aGl.root");
	QCDenri2Reader->addInputFile("/storage/top/mc/V4/pythia/e20skim_enri2/e20skim_nTuple_enri2_f_999_1_IDK.root");
	QCDenri3Reader->addInputFile("/storage/top/mc/V4/pythia/e20skim_enri3/e20skim_nTuple_enri3_f_99_2_uQi.root");

	QCDbce1Reader->addInputFile("/storage/top/mc/V4/pythia/e20skim_bce1/e20skim_nTuple_bce1_f_99_2_ucg.root");
	QCDbce2Reader->addInputFile("/storage/top/mc/V4/pythia/e20skim_bce2/e20skim_nTuple_bce2_f_9.root");
	QCDbce3Reader->addInputFile("/storage/top/mc/V4/pythia/e20skim_bce3/e20skim_nTuple_bce3_f_99_1_ocw.root");

	WjetsReader->addInputFile("/storage/top/mc/V4/MG/e20skim_wjet/e20skim_nTuple_wj_f_9.root");
	ZJetsReader->addInputFile("/storage/top/mc/V4/MG/e20skim_zjet/e20skim_nTuple_zj_f_9.root");
	TWReader->addInputFile("/storage/top/mc/V4/MG/e20skim_tW/e20skim_nTuple_tW_f_9.root");
	TChanReader->addInputFile("/storage/top/mc/V4/MG/e20skim_tchan/e20skim_nTuple_tchan_f_9.root");
	DataReader->addInputFile(
			"/storage/top/data/200710/EG_Run2010A-Jul16-v4_RECO_139559_140159_withCleanTrig/nTuple_data_1_1_qwM.root");

	chain = new TChain("configurableAnalysis/eventB");
	chain->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
}

void tearDownNTupleReader() {
	delete TTbarReader;
	delete QCDenri1Reader;
	delete QCDenri2Reader;
	delete QCDenri3Reader;

	delete QCDbce1Reader;
	delete QCDbce2Reader;
	delete QCDbce3Reader;

	delete WjetsReader;
	delete ZJetsReader;
	delete TWReader;
	delete TChanReader;
	delete DataReader;
	delete chain;
}

void testNumberOfEvents() {
	setUpNTupleReader();
	ASSERT_EQUAL(chain->GetEntries(), TTbarReader->getNumberOfEvents());
	tearDownNTupleReader();
}

void testTTbarType() {
	setUpNTupleReader();
	Event* currentEvent = TTbarReader->getNextEvent();
	ASSERT_EQUAL(Event::ttbar, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testQCD_EMEnriched_80_to_170Type() {
	setUpNTupleReader();
	Event* currentEvent = QCDenri3Reader->getNextEvent();
	ASSERT_EQUAL(Event::QCD_EMEnriched_Pt80to170, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testQCD_EMEnriched_30_to_80Type() {
	setUpNTupleReader();
	Event* currentEvent = QCDenri2Reader->getNextEvent();
	ASSERT_EQUAL(Event::QCD_EMEnriched_Pt30to80, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testQCD_EMEnriched_20_to_30Type() {
	setUpNTupleReader();
	Event* currentEvent = QCDenri1Reader->getNextEvent();
	ASSERT_EQUAL(Event::QCD_EMEnriched_Pt20to30, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testQCD_BCtoE_80_to_170Type() {
	setUpNTupleReader();
	Event* currentEvent = QCDbce3Reader->getNextEvent();
	ASSERT_EQUAL(Event::QCD_BCtoE_Pt80to170, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testQCD_BCtoE_30_to_80Type() {
	setUpNTupleReader();
	Event* currentEvent = QCDbce2Reader->getNextEvent();
	ASSERT_EQUAL(Event::QCD_BCtoE_Pt30to80, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testQCD_BCtoE_20_to_30Type() {
	setUpNTupleReader();
	Event* currentEvent = QCDbce1Reader->getNextEvent();
	ASSERT_EQUAL(Event::QCD_BCtoE_Pt20to30, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testWjetsType() {
	setUpNTupleReader();
	Event* currentEvent = WjetsReader->getNextEvent();
	ASSERT_EQUAL(Event::Wjets, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testZjetsType() {
	setUpNTupleReader();
	Event* currentEvent = ZJetsReader->getNextEvent();
	ASSERT_EQUAL(Event::Zjets, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testTWType() {
	setUpNTupleReader();
	Event* currentEvent = TWReader->getNextEvent();
	ASSERT_EQUAL(Event::singleTop_And_W, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testTChanType() {
	setUpNTupleReader();
	Event* currentEvent = TChanReader->getNextEvent();
	ASSERT_EQUAL(Event::singleTopTChannel, currentEvent->getDataType());
	tearDownNTupleReader();
}

void testDataType() {
	setUpNTupleReader();
	Event* currentEvent = DataReader->getNextEvent();
	ASSERT_EQUAL(Event::DATA, currentEvent->getDataType());
	tearDownNTupleReader();
}
cute::suite make_suite_TestNTupleReader() {
	cute::suite s;
	s.push_back(CUTE(testNumberOfEvents));

	s.push_back(CUTE(testTTbarType));

	s.push_back(CUTE(testQCD_EMEnriched_20_to_30Type));
	s.push_back(CUTE(testQCD_EMEnriched_30_to_80Type));
	s.push_back(CUTE(testQCD_EMEnriched_80_to_170Type));

	s.push_back(CUTE(testQCD_BCtoE_20_to_30Type));
	s.push_back(CUTE(testQCD_BCtoE_30_to_80Type));
	s.push_back(CUTE(testQCD_BCtoE_80_to_170Type));

	s.push_back(CUTE(testWjetsType));
	s.push_back(CUTE(testZjetsType));
	s.push_back(CUTE(testTWType));
	s.push_back(CUTE(testTChanType));

	s.push_back(CUTE(testDataType));
	return s;
}

