/*
 * HistogramManager.h
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#ifndef HISTOGRAMMANAGER_H_
#define HISTOGRAMMANAGER_H_
#include "THCollection.h"
#include "TH1F.h"
#include "TH2F.h"
#include "../Taggers/BJetTagger.h"
#include "../../interface/Enumerators.h"
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
namespace BAT {
typedef unsigned short ushort;
class HistogramManager {
public:
	HistogramManager();
	virtual ~HistogramManager();
	void createAllHistograms();

	void fillHistogram(ushort histogram, const float value, const double weight);
	void fill2DHistograms(ushort histogram, const float Xvalue, const float Yvalue, const double weight);
	void fillLevelBinnedHistogram(const ushort histogram, ushort level, const float value, const float weight);
	void fillLevelBinnedHistogram(const ushort hist, ushort level, const float valueX, const float valueY,
			const float weight);
	void fillNjetBinnedHistogram(ushort histogram, const float value, const double w);
	void fillHisto_btag_DataAndMC(BJetTagger::Algorithm btagAlgorithm, ushort histogram, const float value, const double w);
	void setCurrentDataType(DataType::value type);
	void prepairForSeenDataTypes(const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES>& seenDataTypes);
private:
	TH1Collection collection;
	TH2Collection collection2D;
	DataType::value currentDataType;
};

}

#endif /* HISTOGRAMMANAGER_H_ */
