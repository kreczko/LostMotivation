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
	myAnalysis->setMaximalNumberOfEvents(10000);

	cout << "adding files" << endl;
	//Input files
//	myAnalysis->addInputFile("/storage/top/data/250nb/EG_Run2010A-Jun14thReReco_v1_RECO/*.root");
//	myAnalysis->addInputFile("/storage/top/data/250nb/EG_Run2010A-Jul16-v4_RECO_139559_140159_withCleanTrig/*.root");
//	myAnalysis->addInputFile("/storage/top/data/250nb/EG_Run2010A-PromptReco-v4_RECO_140160_140399/*.root");
	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v4/MG/e20skim_ttjet/*.root");

	cout << "starting analysis" << endl;
	myAnalysis->analyze();
	watch.Stop();
	watch.Print();

	return 0;
}
