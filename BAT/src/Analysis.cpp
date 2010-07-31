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
#include "TFile.h"
#include <boost/scoped_ptr.hpp>

using namespace BAT;
using namespace std;
using namespace boost;

Analysis::Analysis() :
	eventReader(new NTupleEventReader()), eventFilter(Filter::makeStandardFilter()) {

}

Analysis::~Analysis() {
}

void Analysis::addInputFile(const char* fileName) {
	eventReader->addInputFile(fileName);
}

void Analysis::analyze() {
	scoped_ptr<TH1F> h_et(new TH1F("histname", "histtitle", 100, 0, 100));
	scoped_ptr<TH1F> h_diElectronMass(new TH1F("diElectronMass", "diElectronMass", 500, 0, 500));
	scoped_ptr<TFile> outputfile(new TFile("egammaAnalysis.root", "RECREATE"));
	unsigned long numberOfGoodElectrons = 0;
	eventReader->setMaximumNumberOfEvents(100000);
	while (eventReader->hasNextEvent()) {
		unsigned long eventIndex = eventReader->getNumberOfProccessedEvents();
		if (eventIndex % 10000 == 0)
			cout << "Analysing event no " << eventIndex << endl;
		Event event = eventReader->getNextEvent();
		ElectronCollection electrons = event.getGoodElectrons();
		if (electrons.size() == 2) {
			numberOfGoodElectrons += 2;
			Electron leadingElectron = electrons.front();
			Electron secondElectron = electrons.at(1);
			h_et->Fill(leadingElectron.et());
			h_diElectronMass->Fill(leadingElectron.invariantMass(secondElectron));
		}
	}
	//	for (unsigned long eventIndex = 0; eventIndex < eventReader->getNumberOfEvents() && eventIndex < 100000; eventIndex++) {

	//	}
	cout << "finished analysis, number of good leading electrons: " << numberOfGoodElectrons << endl;
	cout << "total number of processed events: " << eventReader->getNumberOfProccessedEvents() << endl;

	//	TCanvas * c = new TCanvas("name", "title", 800, 600);
	h_et->Write();
	h_diElectronMass->Write();
	outputfile->Write();
	outputfile->Close();
	//	c->Update();
	//	c->Draw();
	//	c->SaveAs("h_et.png");

	//	c = new TCanvas("invMass", "title", 800, 600);
	//	h_diElectronMass->Draw();
	//	c->Update();
	//	c->Draw();
	//	c->SaveAs("h_DiElectronInvariantMass.png");
	//	delete c;

}
