#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestElectron.h"
#include "RecoObjects/Electron.h"

using namespace BAT;

static Electron electron1;
static Electron electron2;

void setUpTestElectron(){
	electron1 =  Electron();
	electron2 =  Electron(20.,10.,0.,0.);
}



cute::suite make_suite_TestElectron(){
	cute::suite s;
	return s;
}



