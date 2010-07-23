/*
 * Event.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "RecoObjects/Electron.h"
#include <vector>
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
	ElectronCollection goodElectrons;
	ElectronCollection goodBarrelElectrons;
	ElectronCollection goodEndcapElectrons;

	ElectronCollection goodIsolatedElectrons;
	ElectronCollection goodIsolatedBarrelElectrons;
	ElectronCollection goodIsolatedEndcapElectrons;

	ElectronCollection allElectrons;
	//	ElectronCollection goodNonIsolatedElectrons;
	//	ElectronCollection goodNonIsolatedBarrelElectrons;
	//	ElectronCollection goodNonIsolatedEndcapElectrons;

	DataType dataType;
public:
	Event();
	virtual ~Event();
	bool isRealData() const;
	const DataType getDataType() const;
	void setDataType(DataType type);
	void addElectrons(ElectronCollection electrons);
	const ElectronCollection& getElectrons() const;
	const ElectronCollection& getGoodElectrons() const;

	bool passesSelectionStep(Selection::SelectionSteps step) const;
	bool passesSelectionStepUpTo(Selection::SelectionSteps upToStep) const;

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
	bool isIsolatedElectronInBarrelRegion() const;
};

}

#endif /* EVENT_H_ */
