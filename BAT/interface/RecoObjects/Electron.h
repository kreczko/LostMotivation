/*
 * Electron.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRON_H_
#define ELECTRON_H_

namespace BAT {

class Electron {
public:
	static float goodElectronMinimalEt;
	static float goodElectronMaximalAbsoluteEta;
	static float isolatedElectronMaximalRelativeIsolation;
	Electron();
	virtual ~Electron();
	bool isIsolated();
	bool isInBarrelRegion();
	bool isInCrack();
	bool isInEndCapRegion();
};

}

#endif /* ELECTRON_H_ */
