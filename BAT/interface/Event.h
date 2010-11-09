/*
 * Event.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "RecoObjects/Electron.h"
#include "RecoObjects/Jet.h"
#include "RecoObjects/Muon.h"
#include "RecoObjects/PrimaryVertex.h"
#include "RecoObjects/MET.h"
#include "Selection.h"
#include "Constants.h"
#include "Printers/EventContentPrinter.h"

namespace BAT {

class Event {
protected:
    bool HLT_Photon10_TO20, HLT_Photon15_TO20, HLT_Photon15_Cleaned_TO20, HLT_Emulated_Photon15,
            HLT_Photon20_Cleaned_L1R, HLT_Emulated_Photon20;
    bool HLT_Ele10_LW_L1R,  HLT_Ele15_SW_L1R, HLT_Ele15_SW_CaloEleId_L1R, HLT_Ele17_SW_CaloEleId_L1R;
    bool HLT_Ele17_SW_TightEleId_L1R;
    bool HLT_Ele22_SW_TighterEleId_L1R_v2;
    bool HLT_Ele22_SW_TighterEleId_L1R_v3;
    PrimaryVertexPointer primaryVertex;
    TrackCollection tracks;
    ElectronCollection allElectrons;
    ElectronCollection goodElectrons;
    ElectronCollection goodIsolatedElectrons;
    ElectronCollection looseElectrons;
    ElectronCollection qcdElectrons;

    JetCollection allJets;
    JetCollection goodJets;
    JetCollection goodBJets;

    MuonCollection allMuons;
    MuonCollection goodMuons;
    MuonCollection goodIsolatedMuons;

    METPointer met;

    DataType::value dataType;
    unsigned long runNumber;
    unsigned long eventNumber;
    unsigned long localEventNumber;
    unsigned long lumiBlock;
    float eventWeight;

    float jetCleaningEfficiency;
    unsigned int numberOfHighPurityTracks;

public:
    Event();
    virtual ~Event();
    bool isRealData() const;
    const DataType::value getDataType() const;
    void setDataType(DataType::value type);
    void setPrimaryVertex(PrimaryVertexPointer vertex);
    void setTracks(TrackCollection tracks);
    void setElectrons(ElectronCollection electrons);
    void setJets(JetCollection electrons);
    void setMuons(MuonCollection muons);
    void setMET(const METPointer met);
    void setHLT_Photon10_TO20(bool hltTrigger);
    void setHLT_Photon15_TO20(bool hltTrigger);
    void setHLT_Photon15_Cleaned_TO20(bool hltTrigger);
    void setHLT_Emulated_Photon15(bool hltTrigger);
    void setHLT_Photon20_Cleaned_L1R(bool hltTrigger);
    void setHLT_Emulated_Photon20(bool hltTrigger);
    void setHLT_Ele10_LW_L1R(bool hltTrigger);
    void setHLT_Ele15_SW_L1R(bool hltTrigger);
    void setHLT_Ele15_SW_CaloEleId_L1R(bool hltTrigger);
    void setHLT_Ele17_SW_CaloEleId_L1R(bool hltTrigger);
    void setHLT_Ele17_SW_TightEleId_L1R(bool hltTrigger);
    void setHLT_Ele22_SW_TighterEleId_L1R_v2(bool hltTrigger);
    void setHLT_Ele22_SW_TighterEleId_L1R_v3(bool hltTrigger);
    void setRunNumber(unsigned long number);
    void setEventNumber(unsigned long number);
    void setLocalEventNumber(unsigned long number);
    void setLumiBlock(unsigned long block);
    void setEventWeight(float weight);

    const PrimaryVertexPointer PrimaryVertex() const;
    const TrackCollection& Tracks() const;
    const ElectronCollection& Electrons() const;
    const ElectronCollection& GoodElectrons() const;
    const ElectronCollection& GoodIsolatedElectrons() const;
    const ElectronCollection& QCDElectrons() const;
    const JetCollection& Jets() const;
    const JetCollection& GoodJets() const;
    const JetCollection& GoodBJets() const;
    const MuonCollection& Muons() const;
    const MuonCollection& GoodMuons() const;
    const MuonCollection& GoodIsolatedMuons() const;
    const METPointer MET() const;
    const ElectronPointer MostIsolatedElectron() const;
    unsigned long runnumber() const;
    unsigned long eventnumber() const;
    unsigned long localnumber() const;
    unsigned long lumiblock() const;
    float weight() const;
    void inspect() const;

private:
    void selectElectronsByQuality();
    void cleanGoodJets();
    void cleanGoodJetsAgainstIsolatedElectrons();
    void cleanGoodJetsAgainstMostIsolatedElectron();
    void selectGoodJets();
    void selectMuonsByQuality();
};

}

#endif /* EVENT_H_ */
