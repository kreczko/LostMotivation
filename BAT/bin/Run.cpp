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
    Analysis::useJetAlgorithm(Jet::ParticleFlow);
    Analysis::useElectronAlgorithm(Electron::Calo);
    Analysis::useMETAlgorithm(MET::ParticleFlowMET);
    Analysis::luminosity = 11.;

    boost::scoped_ptr<Analysis> myAnalysis(new Analysis());
    //    myAnalysis->setMaximalNumberOfEvents(10000);
    myAnalysis->setUsedNeutrinoSelectionForTopPairReconstruction(NeutrinoSelectionCriterion::chi2);

    //Synchronisation exercise:
    myAnalysis->addInputFile("/storage/top/mc/Synch/nTuple_ttjet.root");
    //data Run2010A 38X
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Run2010A-Sep17ReReco/*.root");
//3.1pb-1 till here
//Run2010B 38X
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_3/*.root");
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_146804_147116/*.root");
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147116_extra/*.root");
    //7.22pb-1 till here
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147115_147454/*.root");
    // 11pb-1 till here
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147757_148058/*.root");
//    myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_148822_148864/*.root");
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
    myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_3/e20skim_nTuple_data_1_1_HHo.root");

    cout << "starting analysis" << endl;
    myAnalysis->analyze();
    watch.Stop();
    watch.Print();

    return 0;
}
