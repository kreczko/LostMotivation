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
using namespace ROOT;
using namespace std;
int main(int argc, char **argv) {
	gROOT->ProcessLine("#include <vector>");
	//	gROOT->ProcessLine("gErrorIgnoreLevel = 2001;");
	TStopwatch watch;
	watch.Start();
	Analysis* myAnalysis = new Analysis();


	cout << "adding files" << endl;
	//Input files
	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_new/MG/e20skim_ttjet/e20skim_nTuple_ttjet_99_1.root");
//	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_new/MG/e20skim_ttjet/e20skim_nTuple_ttjet_*.root");
//	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_new/MG/e20skim_vqq/*.root");
	//	myana->SetInputFile("/storage/top/mc/spring10_7TeV_new/_zjet/*.root");

//	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_new/pythia/e20skim_bce1/*.root");
//	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_new/pythia/e20skim_bce2/*.root");
//	myAnalysis->addInputFile("/storage/top/mc/spring10_7TeV_new/pythia/e20skim_bce3/*.root");

	//	myana->addInputFile("/storage/top/mc/spring10_7TeV/pythia/e20skim_enri1/*.root");//old
	//	myana->addInputFile("/storage/top/mc/spring10_7TeV_new/pythia/e20skim_enri2/*.root");
	//	myana->addInputFile("/storage/top/mc/spring10_7TeV_new/pythia/e20skim_enri3/*.root");

	//	myana->addInputFile("/storage/top/mc/spring10_7TeV_new/MG/e20skim_tchan/*.root");
	//	myana->addInputFile("/storage/top/mc/spring10_7TeV_new/MG/e20skim_tW/*.root");

	//myana->addInputFile("/storage/top/mc/link_spring10_tchan/*.root");
	//myana->addInputFile("/storage/top/mc/link_spring10_tW/*.root");


	cout << "starting analysis" << endl;
	myAnalysis->analyze();
	watch.Stop();
	watch.Print();
	return 0;
}
