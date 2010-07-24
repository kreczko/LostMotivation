#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestEvent.h"
#include "Event.h"
#include "RecoObjects/Electron.h"
#include "RecoObjects/Jet.h"

using namespace BAT;
using namespace std;

static Event event;

void setUpEvents() {
	event = Event();
	ElectronCollection electrons;
	Electron goodElectron = Electron(30., 20., 5., 2.);
	goodElectron.setHcalIsolation(0.5);
	goodElectron.setEcalIsolation(0.3);
	goodElectron.setTrackerIsolation(0.4);
	goodElectron.setVBTF_W70_ElectronID(true);

	electrons.push_back(goodElectron);
	electrons.push_back(goodElectron);
	electrons.push_back(goodElectron);
	electrons.push_back(Electron(20, 10, 10, 0));

	JetCollection jets;
	Jet goodJet = Jet(290., 200., 200., 0.);
	goodJet.setEMF(0.1);
	goodJet.setN90Hits(2.);
	goodJet.setFHPD(0.5);
	jets.push_back(goodJet);
	jets.push_back(goodJet);
	jets.push_back(goodJet);
	jets.push_back(Jet(40, 20, 20, 0));

	event.setElectrons(electrons);
	event.setJets(jets);

}

void testNumberOfElectrons() {
	setUpEvents();
	ASSERT_EQUAL(4, event.getElectrons().size());
}

void testNumberOfGoodElectrons() {
	setUpEvents();
	ASSERT_EQUAL(3, event.getGoodElectrons().size());
}

void testNumberOfJets() {
	setUpEvents();
	ASSERT_EQUAL(4, event.getJets().size());
}

void testNumberOfGoodJets() {
	setUpEvents();
	ASSERT_EQUAL(3, event.getGoodJets().size());
}

cute::suite make_suite_TestEvent() {
	cute::suite s;
	s.push_back(CUTE(testNumberOfElectrons));
	s.push_back(CUTE(testNumberOfGoodElectrons));
	s.push_back(CUTE(testNumberOfJets));
	s.push_back(CUTE(testNumberOfGoodJets));
	return s;
}

