#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/cute_runner.h"

#include "TestNewJetCleaning.h"
#include "TestOldJetCleaning.h"
#include "TROOT.h"

void setUpOnce() {
    //needed to proper link vector<float> etc.
    gROOT->ProcessLine("#include <vector>");
    //prevent automatic ownership of ROOT objects
}

void runSuite() {
    setUpOnce();
    cute::suite s = make_suite_TestNewJetCleaning();
    s += make_suite_TestOldJetCleaning();
    cute::ide_listener lis;
    cute::makeRunner(lis)(s, "Testing Jet Cleaning");
}

int main() {
    runSuite();
    return 0;
}

