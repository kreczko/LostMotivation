/*
 * EventCounter.h
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#ifndef EVENTCOUNTER_H_
#define EVENTCOUNTER_H_
#include "boost/multi_array.hpp"

typedef boost::multi_array<unsigned long, 3> integerCounter;
typedef integerCounter::size_type size_type_int;

typedef boost::multi_array<double, 3> floatCounter;
typedef floatCounter::size_type size_type_float;

struct Counter {
private:
	integerCounter unweightedEntries;
	floatCounter weightedEntries;
	unsigned int eventType;

public:
	Counter() {
	}

	Counter(const int dimension1, const int dimension2, const int dimension3) :
		unweightedEntries(boost::extents[dimension1][dimension2][dimension3]), weightedEntries(
				boost::extents[dimension1][dimension2][dimension3]) {
	}

	~Counter() {
	}

	void increase(const unsigned int dimension1, const unsigned int dimension2, const unsigned int dimension3,
			const double weight = 1.0) {
		unweightedEntries[dimension1][dimension2][dimension3]++;
		weightedEntries[dimension1][dimension2][dimension3] += weight;
	}

	unsigned int getUnweightedEntries(unsigned int dimension1, unsigned int dimension2, unsigned int dimension3) {
		return unweightedEntries[dimension1][dimension2][dimension3];
	}

	float getWeightedEntries(unsigned int dimension1, unsigned int dimension2, unsigned int dimension3) {
		return weightedEntries[dimension1][dimension2][dimension3];
	}

	unsigned int getSizeOfFirstDimension() {
		return unweightedEntries.size();
	}

	unsigned int getSizeOfSecondDimension() {
		return unweightedEntries.shape()[1];
	}

	unsigned int getSizeOfThirdDimension() {
		return unweightedEntries.shape()[2];
	}

	//TODO: subcount

};
#endif /* EVENTCOUNTER_H_ */
