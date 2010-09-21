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
using namespace BAT;

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
    Analysis::useJetAlgorithm(Jet::Calo_AntiKT_Cone05);
    Analysis::useElectronAlgorithm(Electron::Calo);
    Analysis::useMETAlgorithm(MET::DEFAULT);

    boost::scoped_ptr<Analysis> myAnalysis(new Analysis());
    //    myAnalysis->setMaximalNumberOfEvents(10000);
    myAnalysis->setUsedNeutrinoSelectionForTopPairReconstruction(NeutrinoSelectionCriterion::chi2);

    cout << "adding files" << endl;
    //data
    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-Jul16-v4_RECO_139559_140159/*.root");
    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-Jun14thReReco_v1_RECO/*.root");
    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4/*.root");
    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/*.root");
    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_143181_143328/*.root");
    myAnalysis->addInputFile(
            "/storage/top/data/e20skim/e20skim_MinimumBias_Commissioning10-SD_EG-Jun14thSkim_v1_RECO/*.root");
    myAnalysis->addInputFile("/storage/top/data/e20skim_EG_Run2010A-PromptReco-v4_143657_143835/*.root");
    myAnalysis->addInputFile("/storage/top/data/e20skim_EG_Run2010A-PromptReco-v4_143953_144114/*.root");
    //--------------- 2.9pb-1 until here --------------------------------------------------
    //for testing:
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_23*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_24*.root");

    cout << "starting analysis" << endl;
    myAnalysis->analyze();
    watch.Stop();
    watch.Print();

    return 0;
}
