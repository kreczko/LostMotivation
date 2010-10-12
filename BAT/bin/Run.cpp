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
    Analysis::useMETAlgorithm(MET::Calo);
    Analysis::luminosity = 7.22;

    boost::scoped_ptr<Analysis> myAnalysis(new Analysis());
    //    myAnalysis->setMaximalNumberOfEvents(10000);
    myAnalysis->setUsedNeutrinoSelectionForTopPairReconstruction(NeutrinoSelectionCriterion::chi2);

    //Synchronisation exercise:
    myAnalysis->addInputFile("/storage/top/mc/Synch/nTuple_ttjet.root");
    //data Run2010A
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-Jul16-v4_RECO_139559_140159/*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-Jun14thReReco_v1_RECO/*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4/*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_143181_143328/*.root");
//    myAnalysis->addInputFile(
//            "/storage/top/data/e20skim/e20skim_MinimumBias_Commissioning10-SD_EG-Jun14thSkim_v1_RECO/*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim_EG_Run2010A-PromptReco-v4_143657_143835/*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim_EG_Run2010A-PromptReco-v4_143953_144114/*.root");
    //--------------- 2.9pb-1 until here --------------------------------------------------
    //--------new lumi count
    //data Run2010A 38X
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Run2010A-Sep17ReReco/*.root");
//3.1pb-1 till here
//Run2010B 38X
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_3/*.root");
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_146804_147116/*.root");
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147116_extra/*.root");
//MC
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_ttjet/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_wjet/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_zjet/*.root");
    //QCD
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/pythia/e20skim_bce1/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/pythia/e20skim_bce2/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/pythia/e20skim_bce3/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/pythia/e20skim_enri1/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/pythia/e20skim_enri2/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/pythia/e20skim_enri3/*.root");
    // photon + jets
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_pj1/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_pj2/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_pj3/*.root");
    //Vector boson + heavy flavour
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_vqq/*.root");
    //Zprime samples
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M500GeV_W5GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M500GeV_W50GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M750GeV_W7500MeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1TeV_W10GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1TeV_W100GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1250GeV_W12500MeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1500GeV_W15GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1500GeV_W150GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M2TeV_W20GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M2TeV_W200GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M3TeV_W30GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M3TeV_W300GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M4TeV_W40GeV/*.root");
//    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M4TeV_W400GeV/*.root");
    //for testing:
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_23*.root");
//    myAnalysis->addInputFile("/storage/top/data/e20skim/e20skim_EG_Run2010A-PromptReco-v4_142928_143179/e20skim_nTuple_data_24*.root");

    cout << "starting analysis" << endl;
    myAnalysis->analyze();
    watch.Stop();
    watch.Print();

    return 0;
}
