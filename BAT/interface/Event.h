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
#include "Selection.h"

namespace BAT {

class Event {
public:
	enum DataType {
		DATA,
		ttbar,
		Wjets,
		Zjets,
		QCD_BCtoE_Pt20to30,
		QCD_BCtoE_Pt30to80,
		QCD_BCtoE_Pt80to170,
		QCD_EMEnriched_Pt20to30,
		QCD_EMEnriched_Pt30to80,
		QCD_EMEnriched_Pt80to170,
		VQQ,
		singleTop_And_W,
		singleTopTChannel,
		singleTopSChannel,
		Zprime_M500GeV_W5GeV,
		Zprime_M500GeV_W50GeV,
		Zprime_M750GeV_W7500MeV,
		Zprime_M1TeV_W10GeV,
		Zprime_M1TeV_W100GeV,
		Zprime_M1250GeV_W12500MeV,
		Zprime_M1500GeV_W15GeV,
		Zprime_M1500GeV_W150GeV,
		Zprime_M2TeV_W20GeV,
		Zprime_M2TeV_W200GeV,
		Zprime_M3TeV_W30GeV,
		Zprime_M3TeV_W300GeV,
		Zprime_M4TeV_W40GeV,
		Zprime_M4TeV_W400GeV,
		QCD_ALL,
		singleTop_ALL,
		NUMBER_OF_DATA_TYPES
	};
protected:
	bool HLT_PHOTON15_L1R;
	PrimaryVertex primaryVertex;
	ElectronCollection allElectrons;
	ElectronCollection goodElectrons;
	ElectronCollection goodIsolatedElectrons;
	ElectronCollection looseElectrons;

	JetCollection allJets;
	JetCollection goodJets;

	MuonCollection allMuons;
	MuonCollection goodMuons;
	MuonCollection goodIsolatedMuons;

	DataType dataType;
	unsigned long runNumber;
	unsigned long eventNumber;
	unsigned long localEventNumber;
	unsigned long lumiBlock;
	float eventWeight;

public:
	Event();
	virtual ~Event();
	bool isRealData() const;
	const DataType getDataType() const;
	void setDataType(DataType type);
	void setPrimaryVertex(PrimaryVertex vertex);
	void setElectrons(ElectronCollection electrons);
	void setJets(JetCollection electrons);
	void setMuons(MuonCollection muons);
	void setHLT_Photon15_L1R(bool hltTrigger);
	void setRunNumber(unsigned long number);
	void setEventNumber(unsigned long number);
	void setLocalEventNumber(unsigned long number);
	void setLumiBlock(unsigned long block);
	void setEventWeight(float weight);

	const PrimaryVertex& getPrimaryVertex() const;
	const ElectronCollection& getElectrons() const;
	const ElectronCollection& getGoodElectrons() const;
	const ElectronCollection& getGoodIsolatedElectrons() const;
	const JetCollection& getJets() const;
	const JetCollection& getGoodJets() const;
	const MuonCollection& getMuons() const;
	const MuonCollection& getGoodMuons() const;
	const MuonCollection& getGoodIsolatedMuons() const;
	unsigned long runnumber() const;
	unsigned long eventnumber() const;
	unsigned long localnumber() const;
	unsigned long lumiblock() const;
	float weight() const;

	bool passesSelectionStep(TTbarEPlusJetsSelection::Step step) const;
	bool passesSelectionStepUpTo(TTbarEPlusJetsSelection::Step upToStep) const;

	bool passesHighLevelTrigger() const;
	bool hasOneGoodPrimaryVertex() const;
	bool hasOnlyOneGoodIsolatedElectron() const;
	bool isolatedElectronDoesNotComeFromConversion() const;
	bool hasNoIsolatedMuon() const;

	bool hasAtLeastOneGoodJet() const;
	bool hasAtLeastTwoGoodJets() const;
	bool hasAtLeastThreeGoodJets() const;
	bool hasAtLeastFourGoodJets() const;

	bool isNotAZBosonEvent() const;
	bool hasIsolatedElectronInBarrelRegion() const;

private:
	void selectElectronsByQuality();
	void selectGoodJets();
	void selectMuonsByQuality();
};

}

#endif /* EVENT_H_ */
