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
#include "../interface/Constants.h"

using namespace ROOT;
using namespace std;
using namespace BAT;

void setUpOnce() {
    //needed to proper link vector<float> etc.
    gROOT->ProcessLine("#include <vector>");
    //prevent automatic ownership of ROOT objects
    TH1F::AddDirectory(false);
    //ignore ROOT errors (temporaly due to different nTuple content)
    gROOT->ProcessLine("gErrorIgnoreLevel = 3001;");
}

int main(int argc, char **argv) {
    setUpOnce();
    TStopwatch watch;
    watch.Start();
    Analysis::useJetAlgorithm(JetAlgorithm::PF2PAT);
    Analysis::useElectronAlgorithm(ElectronAlgorithm::ParticleFlow);
    Analysis::useMETAlgorithm(METAlgorithm::ParticleFlowMET);
    Analysis::luminosity = 35.;

    boost::scoped_ptr<Analysis> myAnalysis(new Analysis());
    //    myAnalysis->setMaximalNumberOfEvents(10000);
    myAnalysis->setUsedNeutrinoSelectionForTopPairReconstruction(NeutrinoSelectionCriterion::TopMassDifference);

    //Synchronisation exercise:
//            myAnalysis->addInputFile("/storage/top/mc/Synch/nTuple_ttjet.root");
//    myAnalysis->addInputFile("/storage/top/mc/38Xrereco/e20skim_QCD_BCtoE_Pt80to170_Spring10-START3X_V26_S09-v1/*_1_2_*.root");
//    myAnalysis->addInputFile("/storage/top/mc/38Xrereco/e20skim_QCD_BCtoE_Pt80to170_Spring10-START3X_V26_S09-v1/*_2_2_*.root");

    //data Run2010A 38X
    // //      myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Run2010A-Sep17ReReco/*.root");
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Run2010A-Sep17ReReco_v2_3rdtry/*.root");

    ////3.1pb-1 till here
    ////Run2010B 38X
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_3/*.root");
          myAnalysis->addInputFile(
                  "/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_146804_147116/*.root");
          myAnalysis->addInputFile(
                  "/storage/top/data_38X/e20skim/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147116_extra/*.root");
    ////7.22pb-1 till here
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147115_147454/*.root");
    //// 11pb-1 till here
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_147757_148058/*.root");
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_148822_148864/*.root");
         //should be 22pb - is 21.5
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_148952_149442/*.root");
          myAnalysis->addInputFile("/storage/top/data_38X/e20skim_Electron_Run2010B-PromptReco-v2_AOD_149181_149442/*.root");
        //should be 35pb-1 is 35
        //    //MC
          myAnalysis->addInputFile("/storage/top/mc/38Xrepro/e20skim_TTbarJets-madgraph_Spring10-START3X_V26_S09-v1/*.root");
          myAnalysis->addInputFile("/storage/top/mc/38Xrepro/e20skim_WJets-madgraph_Spring10-START3X_V26_S09-v1/*.root");
          myAnalysis->addInputFile("/storage/top/mc/38Xrepro/e20skim_ZJets-madgraph_Spring10-START3X_V26_S09-v1/*.root");
   //      myAnalysis->addInputFile("/storage/top/mc/38Xrereco/e20skim_SingleTop_tChannel-madgraph_Spring10-START3X_V26_S09-v1/*.root");
   //      myAnalysis->addInputFile("/storage/top/mc/38Xrereco/e20skim_SingleTop_tWChannel-madgraph_Spring10-START3X_V26_S09-v1/*.root");
        //  //QCD
          //      myAnalysis->addInputFile("/storage/top/mc/38Xrepro/e20skim_QCD_BCtoE_Pt30to80_Spring10-START3X_V26_S09-v1/*.root");
          //      myAnalysis->addInputFile("/storage/top/mc/38Xrepro/e20skim_QCD_BCtoE_Pt80to170_Spring10-START3X_V26_S09-v1/*.root");
          //      myAnalysis->addInputFile(
          //              "/storage/top/mc/38Xrepro/e20skim_QCD_EMEnriched_Pt20to30_Spring10-START3X_V26_S09-v1/*.root");
          //      myAnalysis->addInputFile(
          //             "/storage/top/mc/38Xrepro/e20skim_QCD_EMEnriched_Pt30to80_Spring10-START3X_V26_S09-v1/*.root");
          //      myAnalysis->addInputFile(
          //              "/storage/top/mc/38Xrepro/e20skim_QCD_EMEnriched_Pt80to170_Spring10-START3X_V26_S09-v3/*.root");
          //// photon + jets
          //      myAnalysis->addInputFile(
          //              "/storage/top/mc/38Xrepro/e20skim_PhotonJets_Pt40to100-madgraph_Spring10-START3X_V26_S09-v1/*.root");
          //      myAnalysis->addInputFile(
          //             "/storage/top/mc/38Xrepro/e20skim_PhotonJets_Pt100to200-madgraph_Spring10-START3X_V26_S09-v1/*.root");
          //      myAnalysis->addInputFile(
          //             "/storage/top/mc/38Xrepro/e20skim_PhotonJets_Pt200toInf-madgraph_Spring10-START3X_V26_S09-v1/*.root");

    //Vector boson + heavy flavour
    //    myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_vqq/*.root");
    //Zprime samples
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M500GeV_W5GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M500GeV_W50GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M750GeV_W7500MeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1TeV_W10GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1TeV_W100GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1250GeV_W12500MeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1500GeV_W15GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M1500GeV_W150GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M2TeV_W20GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M2TeV_W200GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M3TeV_W30GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M3TeV_W300GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M4TeV_W40GeV/*.root");
    //        myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_v5/MG/e20skim_Zprime_M4TeV_W400GeV/*.root");

    cout << "starting analysis" << endl;
    myAnalysis->analyze();
    watch.Stop();
    watch.Print();

    return 0;
}
