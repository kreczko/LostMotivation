/*
 * Run.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: lkreczko
 */
//#include "cms_bristol_ana_v3.hh"
#include "TSystem.h"
#include "TStopwatch.h"
#include "TROOT.h"
#include "Analysis.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>
using namespace ROOT;
using namespace std;
int main(int argc, char **argv) {
	gROOT->ProcessLine("#include <vector>");
	TStopwatch watch;
	watch.Start();
	boost::scoped_ptr<Analysis> myAnalysis(new Analysis());


	cout << "adding files" << endl;
	//Input files
	myAnalysis->addInputFile("/storage/top/data/200710/EG_Run2010A-PromptReco-v4_RECO_137437_139558/*.root");

	cout << "starting analysis" << endl;
	myAnalysis->analyze();
	watch.Stop();
	watch.Print();

	return 0;
}
