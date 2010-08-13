/*
 * Event.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Event.h"

namespace BAT {

Event::Event() :
    HLT_PHOTON15_L1R(false), primaryVertex(), allElectrons(), goodElectrons(), goodIsolatedElectrons(), met(),
            dataType(DataType::DATA), runNumber(0), eventNumber(0), lumiBlock(0), eventWeight(1.),
            jetCleaningEfficiency(1.) {

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

void Event::setPrimaryVertex(PrimaryVertex vertex) {
    primaryVertex = vertex;
}
void Event::setElectrons(ElectronCollection electrons) {
    allElectrons.clear();
    allElectrons = electrons;
    selectElectronsByQuality();
}

void Event::selectElectronsByQuality() {
    goodElectrons.clear();
    goodIsolatedElectrons.clear();
    for (unsigned int index = 0; index < allElectrons.size(); ++index) {
        Electron electron = allElectrons.at(index);

        if (electron.isGood())
            goodElectrons.push_back(electron);

        if (electron.isGood() && electron.isIsolated())
            goodIsolatedElectrons.push_back(electron);
        if (electron.isGood() == false && electron.isLoose())
            looseElectrons.push_back(electron);
    }
}

void Event::setJets(JetCollection jets) {
    allJets.clear();
    allJets = jets;
    selectGoodJets();
}

void Event::selectGoodJets() {
    goodJets.clear();
    for (unsigned int index = 0; index < allJets.size(); ++index) {
        if (allJets.at(index).isGood())
            goodJets.push_back(allJets.at(index));
    }
    cleanGoodJets();
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
            if (goodJets.at(jetIndex).isWithinDeltaR(0.3, goodIsolatedElectrons.at(electronIndex))) {
                goodJets.erase(goodJets.begin() + jetIndex);
                --jetIndex;
                break;
            }
        }
    }
    jetCleaningEfficiency = goodJets.size() / initialGoodJets;
}

void Event::cleanGoodJetsAgainstMostIsolatedElectron() {
    if (allElectrons.size() > 0) {
        const Electron mostIsolatedElectron = getMostIsolatedElectron();
        unsigned int initialGoodJets = goodJets.size();
        for (unsigned int jetIndex = 0; jetIndex < goodJets.size(); ++jetIndex) {
            if (goodJets.at(jetIndex).isWithinDeltaR(0.3, mostIsolatedElectron)) {
                goodJets.erase(goodJets.begin() + jetIndex);
            }
        }
        jetCleaningEfficiency = goodJets.size() / initialGoodJets;
    }
}

const Electron& Event::getMostIsolatedElectron() const {
    float bestIsolation = 999999999;
    unsigned int bestIsolatedElectron = 990;
    for (unsigned int index = 0; index < allElectrons.size(); ++index) {
        if (allElectrons.at(index).relativeIsolation() < bestIsolation) {
            bestIsolation = allElectrons.at(index).relativeIsolation();
            bestIsolatedElectron = index;
        }
    }
    return allElectrons.at(bestIsolatedElectron);
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

void Event::setHLT_Photon15_L1R(bool hltTrigger) {
    HLT_PHOTON15_L1R = hltTrigger;
}

void Event::setMET(const MET& met) {
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

const PrimaryVertex& Event::getPrimaryVertex() const {
    return primaryVertex;
}

const ElectronCollection& Event::getElectrons() const {
    return allElectrons;
}

const ElectronCollection& Event::getGoodElectrons() const {
    return goodElectrons;
}

const ElectronCollection& Event::getGoodIsolatedElectrons() const {
    return goodIsolatedElectrons;
}

const JetCollection& Event::getJets() const {
    return allJets;
}

const JetCollection& Event::getGoodJets() const {
    return goodJets;
}

const MuonCollection& Event::getMuons() const {
    return allMuons;
}

const MuonCollection& Event::getGoodMuons() const {
    return goodMuons;
}

const MuonCollection& Event::getGoodIsolatedMuons() const {
    return goodIsolatedMuons;
}

const MET& Event::getMET() const {
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

}
