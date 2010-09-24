/*
 * PrimaryVertex.h
 *
 *  Created on: 25 Jul 2010
 *      Author: kreczko
 */

#ifndef PRIMARYVERTEX_H_
#define PRIMARYVERTEX_H_

namespace BAT {

class PrimaryVertex {
public:
	static unsigned int goodVertexMinimalNumberOfDegreesOfFreedom;
	static float goodVertexMaximalAbsoluteZPosition;
	static float goodVertexMaximalAbsoluteZPositionForRealData;
	static float goodVertexMaximalAbsoluteRho;

	static void resetSelectionValues() {
	    PrimaryVertex::goodVertexMinimalNumberOfDegreesOfFreedom = 4;
	    PrimaryVertex::goodVertexMaximalAbsoluteZPosition = 15;
	    PrimaryVertex::goodVertexMaximalAbsoluteZPositionForRealData = 24;
	    PrimaryVertex::goodVertexMaximalAbsoluteRho = 2.0;
	}

	PrimaryVertex();
	virtual ~PrimaryVertex();
	bool isGood() const;
	bool isGoodInRealData() const;
	bool isFake() const;
	unsigned int ndof() const;
	float absoluteZPosition() const;
	float absoluteRho() const;
	void setFake(bool fake);
	void setDegreesOfFreedom(unsigned int ndof);
	void setZPosition(float z);
	void setRho(float rho);
private:
	bool is_fake;
	unsigned int degreesOfFreedom;
	float z_position;
	float rho;

};

}

#endif /* PRIMARYVERTEX_H_ */
