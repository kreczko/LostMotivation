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

void setUpOnce() {
    //needed to proper link vector<float> etc.
    gROOT->ProcessLine("#include <vector>");
    //prevent automatic ownership of ROOT objects
    TH1F::AddDirectory(false);
}

int main(int argc, char **argv) {
    setUpOnce();
    TStopwatch watch;
    watch.Start();
    boost::scoped_ptr<Analysis> myAnalysis(new Analysis());
    myAnalysis->setMaximalNumberOfEvents(10000);

    cout << "adding files" << endl;
    //Input files
    myAnalysis->addInputFile("/storage/top/data/HCP/EG_Run2010A-Jul16-v4_RECO_139559_140159/*.root");
    myAnalysis->addInputFile("/storage/top/data/HCP/EG_Run2010A-Jun14thReReco_v1_RECO/*.root");
    myAnalysis->addInputFile("/storage/top/data/HCP/EG_Run2010A-PromptReco-v4/*.root");

    //    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-Jul16-v4_RECO_139559_140159/*.root");
    //    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-Jun14thReReco_v1_RECO/*.root");
    //    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4/*.root");

    cout << "starting analysis" << endl;
    myAnalysis->analyze();
    watch.Stop();
    watch.Print();

    return 0;
}
