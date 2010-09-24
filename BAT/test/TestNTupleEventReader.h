#include "cute/cute.h"
#include "cute/cute_suite.h"
#include <boost/scoped_ptr.hpp>

#include "../interface/Event.h"
#include "../interface/TopPairEventCandidate.h"
#include "../interface/Readers/NTupleEventReader.h"

using namespace BAT;

struct TestNTupleEventReader {
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
    boost::scoped_ptr<NTupleEventReader> DataReader2;
    boost::scoped_ptr<NTupleEventReader> AllMCReader;

public:
    TestNTupleEventReader() :
        TTbarReader(new NTupleEventReader()),
        QCDenri1Reader(new NTupleEventReader()),
        QCDenri2Reader(new NTupleEventReader()),
        QCDenri3Reader(new NTupleEventReader()),
        QCDbce1Reader(new NTupleEventReader()),
        QCDbce2Reader(new NTupleEventReader()),
        QCDbce3Reader(new NTupleEventReader()),
        WjetsReader(new NTupleEventReader()),
        ZJetsReader(new NTupleEventReader()),
        TWReader(new NTupleEventReader()),
        TChanReader(new NTupleEventReader()),
        DataReader(new NTupleEventReader()),
        DataReader2(new NTupleEventReader()),
        AllMCReader(new NTupleEventReader()) {
        TTbarReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
        QCDenri1Reader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_enri1/e20skim_nTuple_enri1_f_1_3_aGl.root");
        QCDenri2Reader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_enri2/e20skim_nTuple_enri2_f_999_1_IDK.root");
        QCDenri3Reader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_enri3/e20skim_nTuple_enri3_f_99_2_uQi.root");

        QCDbce1Reader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_bce1/e20skim_nTuple_bce1_f_99_2_ucg.root");
        QCDbce2Reader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_bce2/e20skim_nTuple_bce2_f_9.root");
        QCDbce3Reader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_bce3/e20skim_nTuple_bce3_f_99_1_ocw.root");

        WjetsReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_wjet/e20skim_nTuple_wj_f_9.root");
        ZJetsReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_zjet/e20skim_nTuple_zj_f_9.root");
        TWReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_tW/e20skim_nTuple_tW_f_9.root");
        TChanReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_tchan/e20skim_nTuple_tchan_f_9.root");
        DataReader->addInputFileWithoutCheck(
                "/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_24*.root");
        DataReader->addInputFileWithoutCheck(
                "/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_23*.root");
        DataReader2->addInputFileWithoutCheck(
                "/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_23*.root");
        DataReader2->addInputFileWithoutCheck(
                "/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_24*.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_enri1/e20skim_nTuple_enri1_f_1_3_aGl.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_enri2/e20skim_nTuple_enri2_f_999_1_IDK.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_enri3/e20skim_nTuple_enri3_f_99_2_uQi.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_bce1/e20skim_nTuple_bce1_f_99_2_ucg.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_bce2/e20skim_nTuple_bce2_f_9.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/pythia/e20skim_bce3/e20skim_nTuple_bce3_f_99_1_ocw.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_wjet/e20skim_nTuple_wj_f_9.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_zjet/e20skim_nTuple_zj_f_9.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_tW/e20skim_nTuple_tW_f_9.root");
        AllMCReader->addInputFileWithoutCheck("/storage/top/mc/V4/MG/e20skim_tchan/e20skim_nTuple_tchan_f_9.root");

    }

    void testTTbarType() {
        Event currentEvent = TTbarReader->getNextEvent();
        ASSERT_EQUAL(DataType::ttbar, currentEvent.getDataType());
    }

    void testQCD_EMEnriched_80_to_170Type() {
        Event currentEvent = QCDenri3Reader->getNextEvent();
        ASSERT_EQUAL(DataType::QCD_EMEnriched_Pt80to170, currentEvent.getDataType());
    }

    void testQCD_EMEnriched_30_to_80Type() {
        Event currentEvent = QCDenri2Reader->getNextEvent();
        ASSERT_EQUAL(DataType::QCD_EMEnriched_Pt30to80, currentEvent.getDataType());
    }

    void testQCD_EMEnriched_20_to_30Type() {
        Event currentEvent = QCDenri1Reader->getNextEvent();
        ASSERT_EQUAL(DataType::QCD_EMEnriched_Pt20to30, currentEvent.getDataType());
    }

    void testQCD_BCtoE_80_to_170Type() {
        Event currentEvent = QCDbce3Reader->getNextEvent();
        ASSERT_EQUAL(DataType::QCD_BCtoE_Pt80to170, currentEvent.getDataType());
    }

    void testQCD_BCtoE_30_to_80Type() {
        Event currentEvent = QCDbce2Reader->getNextEvent();
        ASSERT_EQUAL(DataType::QCD_BCtoE_Pt30to80, currentEvent.getDataType());
    }

    void testQCD_BCtoE_20_to_30Type() {
        Event currentEvent = QCDbce1Reader->getNextEvent();
        ASSERT_EQUAL(DataType::QCD_BCtoE_Pt20to30, currentEvent.getDataType());
    }

    void testWjetsType() {
        Event currentEvent = WjetsReader->getNextEvent();
        ASSERT_EQUAL(DataType::Wjets, currentEvent.getDataType());
    }

    void testZjetsType() {
        Event currentEvent = ZJetsReader->getNextEvent();
        ASSERT_EQUAL(DataType::Zjets, currentEvent.getDataType());
    }

    void testTWType() {
        Event currentEvent = TWReader->getNextEvent();
        ASSERT_EQUAL(DataType::singleTop_And_W, currentEvent.getDataType());
    }

    void testTChanType() {
        Event currentEvent = TChanReader->getNextEvent();
        ASSERT_EQUAL(DataType::singleTopTChannel, currentEvent.getDataType());
    }

    void testDataType() {
        Event currentEvent = DataReader->getNextEvent();
        ASSERT_EQUAL(DataType::DATA, currentEvent.getDataType());
    }

    void testReadDataType() {
        Event currentEvent = DataReader->getNextEvent();
        ASSERT_EQUAL(true, currentEvent.isRealData());
    }

    void testNumberOfTracksInEvent1() {
        Event currentEvent = TTbarReader->getNextEvent();
        ASSERT_EQUAL(144, currentEvent.getTracks().size());
    }

    void testNumberOfElectronsInEvent1() {
        Event currentEvent = TTbarReader->getNextEvent();
        ASSERT_EQUAL(3, currentEvent.getElectrons().size());
    }

    void testNumberOfJetsInEvent1() {
        Event currentEvent = TTbarReader->getNextEvent();
        ASSERT_EQUAL(8, currentEvent.getJets().size());
    }

    void testNumberOfMuonsInEvent1() {
        Event currentEvent = TTbarReader->getNextEvent();
        ASSERT_EQUAL(1, currentEvent.getMuons().size());
    }

    void testHasNextEvent() {
        ASSERT_EQUAL(true, TTbarReader->hasNextEvent());
    }

    void testHasNotNextEvent() {
        TTbarReader->skipNumberOfEvents(123456789);
        ASSERT(TTbarReader->hasNextEvent() == false);
    }

    void testGetProccessedNumberOfEvents() {
        TTbarReader->getNextEvent();
        ASSERT_EQUAL(1, TTbarReader->getNumberOfProccessedEvents());
        TTbarReader->getNextEvent();
        ASSERT_EQUAL(2, TTbarReader->getNumberOfProccessedEvents());
    }

    void testGetProccessedNumberOfEventsWithSkippedEvents() {
        TTbarReader->getNextEvent();
        TTbarReader->skipNumberOfEvents(100);
        ASSERT_EQUAL(1, TTbarReader->getNumberOfProccessedEvents());
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

    void testMCRunNumber() {
        ASSERT_EQUAL(1, TTbarReader->getNextEvent().runnumber());
    }

    void testMCLumiBlock() {
        ASSERT_EQUAL(2, TTbarReader->getNextEvent().lumiblock());
    }

    void testLocalEventNumber() {
        ASSERT_EQUAL(1, TTbarReader->getNextEvent().localnumber());
    }

    void testInitialEventWeigth() {
        ASSERT_EQUAL(1., TTbarReader->getNextEvent().weight());
    }

    void testPrimaryVertex() {
        ASSERT_EQUAL(true, TTbarReader->hasNextEvent());
        ASSERT_EQUAL(true, TTbarReader->getNextEvent().getPrimaryVertex().isGood());
    }

    void testHLTTrigger() {
        TopPairEventCandidate candidate = TopPairEventCandidate(TTbarReader->getNextEvent());
        ASSERT_EQUAL(true, candidate.passesHighLevelTrigger());
    }

    void testEventChainConstant() {
        ASSERT_EQUAL(0, strcmp("configurableAnalysis/eventB", NTupleEventReader::EVENT_CHAIN));
    }

    void testHLTChainConstant() {
        ASSERT_EQUAL(0, strcmp("configurableAnalysis/eventV", NTupleEventReader::HLT_TRIGGER_CHAIN));
    }

    void testECALCleanlingChainConstant() {
        ASSERT_EQUAL(0, strcmp("configurableAnalysis/eventA", NTupleEventReader::ADDITIONAL_CHAIN));
    }

    void testTTbarEventMET() {
        Event event = TTbarReader->getNextEvent();
        ASSERT_EQUAL_DELTA(47.9642,event.getMET()->et(), 0.001);
    }

    void testSeenTTbar() {
        const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES> seenTypes = TTbarReader->getSeenDatatypes();

        for (unsigned short index = 0; index < DataType::NUMBER_OF_DATA_TYPES; ++index) {
            if (index == DataType::ttbar)
                ASSERT_EQUAL(true, seenTypes.at(index));
                else
                ASSERT_EQUAL(false, seenTypes.at(index));
        }
    }

    void testSeenAllMC() {
        const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES> seenTypes = AllMCReader->getSeenDatatypes();

        for (unsigned short index = 0; index < DataType::NUMBER_OF_DATA_TYPES; ++index) {
            if (index == DataType::DATA || index >= DataType::Zprime_M500GeV_W5GeV || index
                    == DataType::singleTopSChannel || index == DataType::VQQ)
                ASSERT_EQUAL(false, seenTypes.at(index));
            else {
                std::string msg("index ");
                std::stringstream stream;
                stream << index;
                msg += stream.str();
                ASSERT_EQUALM(msg.c_str(), true, seenTypes.at(index));
            }

        }
    }

    void testHLT() {
        unsigned int passedHLT = 0;
        while (DataReader->hasNextEvent()) {
            TopPairEventCandidate cand = TopPairEventCandidate(DataReader->getNextEvent());
            if (cand.passesHighLevelTrigger())
                passedHLT++;
        }

        unsigned int passedHLT2 = 0;
        while (DataReader2->hasNextEvent()) {
            TopPairEventCandidate cand = TopPairEventCandidate(DataReader2->getNextEvent());
            if (cand.passesHighLevelTrigger())
                passedHLT2++;
        }
        ASSERT_EQUAL(passedHLT, passedHLT2);
    }

    void testAddInputFileNoFileThrowsException() {
        boost::scoped_ptr<NTupleEventReader> reader(new NTupleEventReader());
        ASSERT_THROWS(reader->addInputFile("dfjndkjvnvh"), NoFileFoundException);
    }

};

extern cute::suite make_suite_TestNTupleEventReader() {
    cute::suite s;
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testTTbarType));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testQCD_EMEnriched_20_to_30Type));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testQCD_EMEnriched_30_to_80Type));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testQCD_EMEnriched_80_to_170Type));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testQCD_BCtoE_20_to_30Type));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testQCD_BCtoE_30_to_80Type));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testQCD_BCtoE_80_to_170Type));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testWjetsType));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testZjetsType));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testTWType));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testTChanType));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testDataType));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testReadDataType));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testNumberOfTracksInEvent1));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testNumberOfElectronsInEvent1));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testNumberOfJetsInEvent1));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testNumberOfMuonsInEvent1));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testHasNextEvent));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testHasNotNextEvent));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testGetProccessedNumberOfEvents));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testGetProccessedNumberOfEventsWithSkippedEvents));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testSkipEvents));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testGetCurrentLocalEventNumber));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testSetMaximumNumberOfEventsWithSkippedEvents));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testSetMaximumNumberOfEvents));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testMCRunNumber));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testMCLumiBlock));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testLocalEventNumber));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testInitialEventWeigth));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testPrimaryVertex));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testHLTTrigger));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testEventChainConstant));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testHLTChainConstant));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testECALCleanlingChainConstant));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testTTbarEventMET));

    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testSeenTTbar));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testSeenAllMC));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testHLT));
    s.push_back(CUTE_SMEMFUN(TestNTupleEventReader, testAddInputFileNoFileThrowsException));
    return s;
}
