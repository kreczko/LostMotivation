#include "cute/cute.h"
#include "cute/cute_suite.h"

#include <boost/shared_ptr.hpp>

#include "../interface/Readers/PrimaryVertexReader.h"
#include "TChain.h"

using namespace BAT;

struct TestPrimaryVertexReader {
	boost::shared_ptr<TChain> input;
	boost::shared_ptr<PrimaryVertexReader> reader;
	PrimaryVertex vertex;

	TestPrimaryVertexReader() :
		input(new TChain("configurableAnalysis/eventB")), reader(new PrimaryVertexReader(input)), vertex() {
		input->Add("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");
		input->SetBranchStatus("*", 0);
		reader->initialise();
		input->GetEntry(1);
		vertex = reader->getVertex();
	}

	void testVertexZPosition() {
		ASSERT_EQUAL_DELTA(3.02691, vertex.absoluteZPosition(), 0.00001);
	}

	void testVertexRho(){
		ASSERT_EQUAL_DELTA(0.0368912, vertex.absoluteRho(), 0.000001);
	}

	void testVertexIsFake(){
		ASSERT(vertex.isFake() == false);
	}

	void testVertexNDOF(){
		ASSERT_EQUAL(133, vertex.ndof());
	}
};

cute::suite make_suite_TestPrimaryVertexReader() {
	cute::suite s;
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertexReader, testVertexZPosition));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertexReader, testVertexRho));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertexReader, testVertexIsFake));
	s.push_back(CUTE_SMEMFUN(TestPrimaryVertexReader, testVertexNDOF));
	return s;
}
