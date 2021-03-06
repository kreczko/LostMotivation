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
#include "RecoObjects/MCParticle.h"
#include "Selection.h"
#include "Constants.h"
#include "Printers/EventContentPrinter.h"

namespace BAT {

class Event {
protected:
    boost::shared_ptr<std::vector<int> > HLTs;
    PrimaryVertexPointer primaryVertex;
    TrackCollection tracks;
    ElectronCollection allElectrons;
    ElectronCollection goodElectrons;
    ElectronCollection goodIsolatedElectrons;
    ElectronCollection goodPFIsolatedElectrons;
    ElectronCollection looseElectrons;
    ElectronCollection qcdElectrons;

    JetCollection allJets;
    JetCollection genJets;
    JetCollection goodJets;
    JetCollection goodBJets;

    MuonCollection allMuons;
    MuonCollection goodMuons;
    MuonCollection goodIsolatedMuons;

    MCParticleCollection genParticles;

    METPointer met;

    DataType::value dataType;
    unsigned long runNumber;
    unsigned long eventNumber;
    unsigned long localEventNumber;
    unsigned long lumiBlock;
    float eventWeight;

    float jetCleaningEfficiency;
    unsigned int numberOfHighPurityTracks;
    bool isBeamScraping;

public:
    Event();
    virtual ~Event();
    bool isRealData() const;
    const DataType::value getDataType() const;
    void setDataType(DataType::value type);
    void setPrimaryVertex(PrimaryVertexPointer vertex);
    void setTracks(TrackCollection tracks);
    void setGenParticles(MCParticleCollection genParticles);
    void setElectrons(ElectronCollection electrons);
    void setJets(JetCollection jets);
    void setGenJets(JetCollection genJets);
    void setMuons(MuonCollection muons);
    void setMET(const METPointer met);
    void setHLTs(const boost::shared_ptr<std::vector<int> >);
    void setRunNumber(unsigned long number);
    void setEventNumber(unsigned long number);
    void setLocalEventNumber(unsigned long number);
    void setLumiBlock(unsigned long block);
    void setEventWeight(float weight);
    void setBeamScrapingVeto(bool isScraping);

    const PrimaryVertexPointer PrimaryVertex() const;
    const TrackCollection& Tracks() const;
    const MCParticleCollection& GenParticles() const;
    const ElectronCollection& Electrons() const;
    const ElectronCollection& GoodElectrons() const;
    const ElectronCollection& GoodIsolatedElectrons() const;
    const ElectronCollection& GoodPFIsolatedElectrons() const;
    const ElectronCollection& QCDElectrons() const;
    const JetCollection& Jets() const;
    const JetCollection& GenJets() const;
    const JetCollection& GoodJets() const;
    const JetCollection& GoodBJets() const;
    const MuonCollection& Muons() const;
    const MuonCollection& GoodMuons() const;
    const MuonCollection& GoodIsolatedMuons() const;
    const METPointer MET() const;
    const ElectronPointer MostIsolatedElectron(bool usePFIso) const;
    const ElectronPointer MostIsolatedElectron() const;
    const ElectronPointer MostPFIsolatedElectron() const;
    unsigned long runnumber() const;
    unsigned long eventnumber() const;
    unsigned long localnumber() const;
    unsigned long lumiblock() const;
    float weight() const;
    void inspect() const;
    bool HLT(HLTriggers::value trigger) const;
    static bool useCustomConversionTagger;
    static bool usePFIsolation;

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
