/*
 * Event.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Event.h"
#include "../interface/Taggers/BJetTagger.h"
#include <iostream>
using namespace std;

namespace BAT {
bool Event::useCustomConversionTagger = false;
bool Event::usePFIsolation = false;
Event::Event() :
    HLTs(new std::vector<int>()),
    primaryVertex(),
    tracks(),
    allElectrons(),
    goodElectrons(),
    goodIsolatedElectrons(),
    goodPFIsolatedElectrons(),
    looseElectrons(),
    qcdElectrons(),
    allJets(),
    goodJets(),
    goodBJets(),
    allMuons(),
    goodMuons(),
    goodIsolatedMuons(),
    genParticles(),
    met(),
    dataType(DataType::DATA),
    runNumber(0),
    eventNumber(0),
    lumiBlock(0),
    eventWeight(1.),
    jetCleaningEfficiency(1.),
    numberOfHighPurityTracks(0),
    isBeamScraping(true){
}

Event::~Event() {
}

bool Event::isRealData() const {
    return dataType == DataType::DATA;
}

const DataType::value Event::getDataType() const {
    return dataType;
}

void Event::setDataType(DataType::value type) {
    dataType = type;
}

void Event::setPrimaryVertex(PrimaryVertexPointer vertex) {
    primaryVertex = vertex;
}

void Event::setTracks(TrackCollection tracks) {
    this->tracks = tracks;
    numberOfHighPurityTracks = 0;
    for (unsigned int index = 0; index < tracks.size(); ++index) {
        if (tracks.at(index)->isHighPurity())
            numberOfHighPurityTracks++;
    }
}

void Event::setGenParticles(MCParticleCollection genParticles) {
	this->genParticles = genParticles;
}

void Event::setElectrons(ElectronCollection electrons) {
    allElectrons.clear();
    allElectrons = electrons;
    selectElectronsByQuality();
}

void Event::selectElectronsByQuality() {
    goodElectrons.clear();
    goodIsolatedElectrons.clear();
    goodPFIsolatedElectrons.clear();
    for (unsigned int index = 0; index < allElectrons.size(); ++index) {
        ElectronPointer electron = allElectrons.at(index);

        if (electron->isGood())
            goodElectrons.push_back(electron);

        if(electron->isGood(20))
            qcdElectrons.push_back(electron);

        if (electron->isGood() && electron->isIsolated())
            goodIsolatedElectrons.push_back(electron);

        if(electron->algorithm() == ElectronAlgorithm::ParticleFlow){
            if(electron->isGood() && electron->isPFIsolated())
                goodPFIsolatedElectrons.push_back(electron);
        }

        if (electron->isGood() == false && electron->isLoose())
            looseElectrons.push_back(electron);
    }
}

void Event::setJets(JetCollection jets) {
    allJets.clear();
    allJets = jets;
    selectGoodJets();
}

void Event::setGenJets(JetCollection jets) {
    genJets.clear();
    genJets = jets;
}


void Event::selectGoodJets() {
    goodJets.clear();
    for (unsigned int index = 0; index < allJets.size(); ++index) {
        const JetPointer jet = allJets.at(index);
        if (jet->isGood()) {
            goodJets.push_back(jet);
        }
    }
    cleanGoodJets();
    for (unsigned int index = 0; index < goodJets.size(); ++index) {
        const JetPointer jet = goodJets.at(index);
        if (jet->isBJetAccordingToBtagAlgorithm(BJetTagger::SimpleSecondaryVertex))
            goodBJets.push_back(jet);
    }
}

void Event::cleanGoodJets() {
    if (goodIsolatedElectrons.size() > 0 && goodJets.size() > 0)
        cleanGoodJetsAgainstIsolatedElectrons();
    else if (allElectrons.size() > 0 && goodJets.size() > 0)
        cleanGoodJetsAgainstMostIsolatedElectron();
}

void Event::cleanGoodJetsAgainstIsolatedElectrons() {
    unsigned int initialGoodJets = goodJets.size();
    for (unsigned int jetIndex = 0; jetIndex < goodJets.size(); ++jetIndex) {
        for (unsigned int electronIndex = 0; electronIndex < goodIsolatedElectrons.size(); ++electronIndex) {
            if (goodJets.at(jetIndex)->isWithinDeltaR(0.3, goodIsolatedElectrons.at(electronIndex))) {
                goodJets.erase(goodJets.begin() + jetIndex);
                --jetIndex;
                break;
            }
        }
    }
    jetCleaningEfficiency = goodJets.size() / initialGoodJets;
}

void Event::cleanGoodJetsAgainstMostIsolatedElectron() {
    const ElectronPointer mostIsolatedElectron = MostIsolatedElectron(Event::usePFIsolation);
    unsigned int initialGoodJets = goodJets.size();
    for (unsigned int jetIndex = 0; jetIndex < goodJets.size(); ++jetIndex) {
        if (goodJets.at(jetIndex)->isWithinDeltaR(0.3, mostIsolatedElectron)) {
            goodJets.erase(goodJets.begin() + jetIndex);
            --jetIndex;
        }
    }
    jetCleaningEfficiency = goodJets.size() / initialGoodJets;
}

const ElectronPointer Event::MostIsolatedElectron(bool usePFIso) const {
    float bestIsolation = 999999999;
    unsigned int bestIsolatedElectron = 990;
    for (unsigned int index = 0; index < allElectrons.size(); ++index) {
        float currentIsolation = 999999999;
        if(usePFIso)
            currentIsolation = allElectrons.at(index)->pfIsolation();
        else
            currentIsolation = allElectrons.at(index)->relativeIsolation();

        if (currentIsolation < bestIsolation) {
            bestIsolation = currentIsolation;
            bestIsolatedElectron = index;
        }
    }
    return allElectrons.at(bestIsolatedElectron);
}

const ElectronPointer Event::MostIsolatedElectron() const{
    return MostIsolatedElectron(false);
}

const ElectronPointer Event::MostPFIsolatedElectron() const{
    return MostIsolatedElectron(true);
}


void Event::setMuons(MuonCollection muons) {
    allMuons.clear();
    allMuons = muons;
    selectMuonsByQuality();
}

void Event::selectMuonsByQuality() {
    goodMuons.clear();
    goodIsolatedMuons.clear();
    for (unsigned int index = 0; index < allMuons.size(); ++index) {
        Muon muon = allMuons.at(index);

        if (muon.isGood())
            goodMuons.push_back(muon);

        if (muon.isGood() && muon.isIsolated())
            goodIsolatedMuons.push_back(muon);
    }
}

void Event::setHLTs(const boost::shared_ptr<std::vector<int> > triggers){
    HLTs = triggers;
}

void Event::setMET(const METPointer met) {
    this->met = met;
}

void Event::setRunNumber(unsigned long number) {
    runNumber = number;
}

void Event::setEventNumber(unsigned long number) {
    eventNumber = number;
}

void Event::setLocalEventNumber(unsigned long number) {
    localEventNumber = number;
}

void Event::setLumiBlock(unsigned long block) {
    lumiBlock = block;
}

void Event::setEventWeight(float weight) {
    eventWeight = weight;
}

void Event::setBeamScrapingVeto(bool isScraping){
    isBeamScraping = isScraping;
}

const PrimaryVertexPointer Event::PrimaryVertex() const {
    return primaryVertex;
}

const TrackCollection& Event::Tracks() const {
    return tracks;
}

const ElectronCollection& Event::Electrons() const {
    return allElectrons;
}

const ElectronCollection& Event::GoodElectrons() const {
    return goodElectrons;
}

const ElectronCollection& Event::GoodIsolatedElectrons() const {
    return goodIsolatedElectrons;
}

const ElectronCollection& Event::GoodPFIsolatedElectrons() const {
    return goodPFIsolatedElectrons;
}

const ElectronCollection& Event::QCDElectrons() const{
    return qcdElectrons;
}

const JetCollection& Event::Jets() const {
    return allJets;
}

const JetCollection& Event::GenJets() const {
    return genJets;
}


const JetCollection& Event::GoodJets() const {
    return goodJets;
}

const JetCollection& Event::GoodBJets() const {
    return goodBJets;
}

const MuonCollection& Event::Muons() const {
    return allMuons;
}

const MuonCollection& Event::GoodMuons() const {
    return goodMuons;
}

const MuonCollection& Event::GoodIsolatedMuons() const {
    return goodIsolatedMuons;
}

const METPointer Event::MET() const {
    return met;
}

unsigned long Event::runnumber() const {
    return runNumber;
}

unsigned long Event::eventnumber() const {
    return eventNumber;
}

unsigned long Event::localnumber() const {
    return localEventNumber;
}

unsigned long Event::lumiblock() const {
    return lumiBlock;
}

float Event::weight() const {
    return eventWeight;
}

void Event::inspect() const {
    cout << "run " << runNumber << ", event number " << eventNumber << ", lumi section " << lumiBlock << endl;

    cout << "number of tracks: " << tracks.size() << endl;
    cout << "number of high purity tracks: " << numberOfHighPurityTracks << endl;

    cout << "number of jets: " << allJets.size() << endl;
    EventContentPrinter::printJets(allJets);
    cout << "number of good jets: " << goodJets.size() << endl;
    EventContentPrinter::printJets(goodJets);

    cout << "number of good isolated electrons: " << goodIsolatedElectrons.size() << endl;
    EventContentPrinter::printElectrons(goodIsolatedElectrons);

    cout << "number of good electrons: " << goodElectrons.size() << endl;
    EventContentPrinter::printElectrons(goodElectrons);

    cout << "number of electrons: " << allElectrons.size() << endl;
    EventContentPrinter::printElectrons(allElectrons);
}

bool Event::HLT(HLTriggers::value trigger) const{
    return HLTs->at(trigger) > 0;
}

}
