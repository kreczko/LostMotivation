/*
 * Event.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef EVENT_H_
#define EVENT_H_

namespace BAT {

class Event {
public:
	Event();
	virtual ~Event();
	bool isRealData();
	unsigned short getMCType();
	void setMCType(unsigned short mcType);
};

}

#endif /* EVENT_H_ */
