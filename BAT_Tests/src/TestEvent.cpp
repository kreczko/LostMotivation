#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TestEvent.h"
#include "Event.h"

static BAT::Event* event;

void setUpEvents(){
	event = new BAT::Event();
}


cute::suite make_suite_TestEvent(){
	cute::suite s;
	return s;
}



