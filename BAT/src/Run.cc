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
	TStopwatch watch;
	watch.Start();
	Analysis* myAnalysis = new Analysis();


	cout << "adding files" << endl;
	//Input files
	myAnalysis->addInputFile("/storage/top/mc/V4/MG/e20skim_ttjet/e20skim_nTuple_ttjet_f_1.root");

	cout << "starting analysis" << endl;
	myAnalysis->analyze();
	watch.Stop();
	watch.Print();
	return 0;
}
