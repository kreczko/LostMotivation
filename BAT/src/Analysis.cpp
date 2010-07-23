/*
 * Analysis.cpp
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#include "Analysis.h"
#include <iostream>
#include "TH1F.h"
#include "TCanvas.h"

using namespace BAT;
using namespace std;
Analysis::Analysis() :
	eventReader(new NTupleEventReader()), eventFilter(Filter::makeStandardFilter()) {

}

Analysis::~Analysis() {
}

void Analysis::addInputFile(const char* fileName) {
	eventReader->addInputFile(fileName);
}

void Analysis::analyze() {
	unsigned long numberOfEvents = eventReader->getNumberOfEvents();
	cout << "total number of events to analyse: " << numberOfEvents << endl;
	TH1F* h_energy = new TH1F("histname", "histtitle", 500, 0, 500);
	unsigned long numberOfGoodElectrons = 0;
	for (unsigned long eventIndex = 0; eventIndex < numberOfEvents; eventIndex++) {
		Event* event = eventReader->getNextEvent();
		Electron leadingElectron = event->getElectrons().front();
		if (leadingElectron.isGood())
			numberOfGoodElectrons++;
		h_energy->Fill(leadingElectron.energy());
	}
	cout << "finished analysis, number of good leading electrons: " << numberOfGoodElectrons << endl;
	TCanvas * c = new TCanvas("name", "title", 800, 600);
	h_energy->Draw();
	c->Update();
	c->Draw();
	c->SaveAs("h_energy.png");
	delete c;
	delete h_energy;
}
