/*
 * DummyTTbarEvent.cpp
 *
 *  Created on: 25 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/OnlyForTests/DummyTTbarEvent.h"

namespace BAT {

DummyTTbarEvent::DummyTTbarEvent():BAT::TopPairEventCandidate() {

}

DummyTTbarEvent::~DummyTTbarEvent() {
}

void DummyTTbarEvent::setElectronFromW(ElectronPointer electron){
    electronFromW = electron;
}

}
