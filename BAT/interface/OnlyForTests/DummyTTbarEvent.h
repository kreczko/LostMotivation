/*
 * DummyTTbarEvent.h
 *
 *  Created on: 25 Aug 2010
 *      Author: kreczko
 */

#ifndef DUMMYTTBAREVENT_H_
#define DUMMYTTBAREVENT_H_

#include "../TopPairEventCandidate.h"

namespace BAT {

class DummyTTbarEvent: public TopPairEventCandidate {
public:
    DummyTTbarEvent();
    virtual ~DummyTTbarEvent();
    void setElectronFromW(const ElectronPointer electron);

};

}

#endif /* DUMMYTTBAREVENT_H_ */
