#include "cute_suite.h"
#include "Readers/NTupleEventReader.h"
#include "Event.h"
#include <boost/scoped_ptr.hpp>

using namespace BAT;

struct TestNTupleReader {
private:
	boost::scoped_ptr<NTupleEventReader> TTbarReader;
	boost::scoped_ptr<NTupleEventReader> QCDenri1Reader;
	boost::scoped_ptr<NTupleEventReader> QCDenri2Reader;
	boost::scoped_ptr<NTupleEventReader> QCDenri3Reader;

	boost::scoped_ptr<NTupleEventReader> QCDbce1Reader;
	boost::scoped_ptr<NTupleEventReader> QCDbce2Reader;
	boost::scoped_ptr<NTupleEventReader> QCDbce3Reader;

	boost::scoped_ptr<NTupleEventReader> WjetsReader;
	boost::scoped_ptr<NTupleEventReader> ZJetsReader;
	boost::scoped_ptr<NTupleEventReader> TWReader;
	boost::scoped_ptr<NTupleEventReader> TChanReader;
	boost::scoped_ptr<NTupleEventReader> DataReader;
	boost::scoped_ptr<TChain> chain;

public:
	TestNTupleReader() :
		TTbarReader(new NTupleEventReader()), QCDenri1Reader(new NTupleEventReader()), QCDenri2Reader(
				new NTupleEventReader()), QCDenri3Reader(new NTupleEventReader()), QCDbce1Reader(
				new NTupleEventReader()), QCDbce2Reader(new NTupleEventReader()),
				QCDbce3Reader(new NTupleEventReader()), WjetsReader(new NTupleEventReader()), ZJetsReader(
						new NTupleEventReader()), TWReader(new NTupleEventReader()), TChanReader(
						new NTupleEventReader()), DataReader(new NTupleEventReader()), chain(new TChain(
						"configurableAnalysis/eventB")) {
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
		chain->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
	}

	void testTTbarType() {
		Event currentEvent = TTbarReader->getNextEvent();
		ASSERT_EQUAL(Event::ttbar, currentEvent.getDataType());
	}

	void testQCD_EMEnriched_80_to_170Type() {
		Event currentEvent = QCDenri3Reader->getNextEvent();
		ASSERT_EQUAL(Event::QCD_EMEnriched_Pt80to170, currentEvent.getDataType());
	}

	void testQCD_EMEnriched_30_to_80Type() {
		Event currentEvent = QCDenri2Reader->getNextEvent();
		ASSERT_EQUAL(Event::QCD_EMEnriched_Pt30to80, currentEvent.getDataType());
	}

	void testQCD_EMEnriched_20_to_30Type() {
		Event currentEvent = QCDenri1Reader->getNextEvent();
		ASSERT_EQUAL(Event::QCD_EMEnriched_Pt20to30, currentEvent.getDataType());
	}

	void testQCD_BCtoE_80_to_170Type() {
		Event currentEvent = QCDbce3Reader->getNextEvent();
		ASSERT_EQUAL(Event::QCD_BCtoE_Pt80to170, currentEvent.getDataType());
	}

	void testQCD_BCtoE_30_to_80Type() {
		Event currentEvent = QCDbce2Reader->getNextEvent();
		ASSERT_EQUAL(Event::QCD_BCtoE_Pt30to80, currentEvent.getDataType());
	}

	void testQCD_BCtoE_20_to_30Type() {
		Event currentEvent = QCDbce1Reader->getNextEvent();
		ASSERT_EQUAL(Event::QCD_BCtoE_Pt20to30, currentEvent.getDataType());
	}

	void testWjetsType() {
		Event currentEvent = WjetsReader->getNextEvent();
		ASSERT_EQUAL(Event::Wjets, currentEvent.getDataType());
	}

	void testZjetsType() {
		Event currentEvent = ZJetsReader->getNextEvent();
		ASSERT_EQUAL(Event::Zjets, currentEvent.getDataType());
	}

	void testTWType() {
		Event currentEvent = TWReader->getNextEvent();
		ASSERT_EQUAL(Event::singleTop_And_W, currentEvent.getDataType());
	}

	void testTChanType() {
		Event currentEvent = TChanReader->getNextEvent();
		ASSERT_EQUAL(Event::singleTopTChannel, currentEvent.getDataType());
	}

	void testDataType() {
		Event currentEvent = DataReader->getNextEvent();
		ASSERT_EQUAL(Event::DATA, currentEvent.getDataType());
	}

	void testNumberOfElectronsInEvent1() {
		Event currentEvent = TTbarReader->getNextEvent();
		ASSERT_EQUAL(3, currentEvent.getElectrons().size());
	}

	void testNumberOfJetsInEvent1() {
		Event currentEvent = TTbarReader->getNextEvent();
		ASSERT_EQUAL(8, currentEvent.getJets().size());
	}

	void testHasNextEvent() {
		ASSERT(TTbarReader->hasNextEvent());
	}

	void testHasNotNextEvent() {
		TTbarReader->skipNumberOfEvents(chain->GetEntriesFast());
		ASSERT(TTbarReader->hasNextEvent() == false);
	}

	void testGetProccessedNumberOfEvents() {
		TTbarReader->getNextEvent();
		ASSERT_EQUAL(1,TTbarReader->getNumberOfProccessedEvents());
		TTbarReader->getNextEvent();
		ASSERT_EQUAL(2,TTbarReader->getNumberOfProccessedEvents());
	}

	void testGetProccessedNumberOfEventsWithSkippedEvents() {
		TTbarReader->getNextEvent();
		TTbarReader->skipNumberOfEvents(100);
		ASSERT_EQUAL(1,TTbarReader->getNumberOfProccessedEvents());
	}
	void testSkipEvents() {
		TTbarReader->skipNumberOfEvents(10);
		ASSERT_EQUAL(10, TTbarReader->getCurrentLocalEventNumber());
	}

	void testGetCurrentLocalEventNumber() {
		ASSERT_EQUAL(0, TTbarReader->getCurrentLocalEventNumber());
		TTbarReader->getNextEvent();
		ASSERT_EQUAL(1, TTbarReader->getCurrentLocalEventNumber());
	}

	void testSetMaximumNumberOfEventsWithSkippedEvents() {
		TTbarReader->setMaximumNumberOfEvents(5);
		TTbarReader->skipNumberOfEvents(10);
		ASSERT(TTbarReader->hasNextEvent() == false);
	}

	void testSetMaximumNumberOfEvents() {
		unsigned int maxEvents = 5;
		TTbarReader->setMaximumNumberOfEvents(maxEvents);
		while (TTbarReader->hasNextEvent())
			TTbarReader->getNextEvent();
		ASSERT_EQUAL(maxEvents, TTbarReader->getNumberOfProccessedEvents());
	}
};

extern cute::suite make_suite_TestNTupleReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testTTbarType));

	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testQCD_EMEnriched_20_to_30Type));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testQCD_EMEnriched_30_to_80Type));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testQCD_EMEnriched_80_to_170Type));

	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testQCD_BCtoE_20_to_30Type));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testQCD_BCtoE_30_to_80Type));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testQCD_BCtoE_80_to_170Type));

	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testWjetsType));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testZjetsType));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testTWType));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testTChanType));

	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testDataType));

	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testNumberOfElectronsInEvent1));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testNumberOfJetsInEvent1));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testHasNextEvent));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testHasNotNextEvent));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testGetProccessedNumberOfEvents));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testGetProccessedNumberOfEventsWithSkippedEvents));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testSkipEvents));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testGetCurrentLocalEventNumber));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testSetMaximumNumberOfEventsWithSkippedEvents));
	s.push_back(CUTE_SMEMFUN(TestNTupleReader,testSetMaximumNumberOfEvents));
	return s;
}
