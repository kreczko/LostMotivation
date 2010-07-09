/*
 * HistogramManager.h
 *
 *  Created on: 4 Jul 2010
 *      Author: kreczko
 */

#ifndef HISTOGRAMMANAGER_H_
#define HISTOGRAMMANAGER_H_
#include "HistCollection.h"
#include "TH1F.h"
#include "TH2F.h"
#include "../Taggers/BJetTagger.h"

namespace BAT {

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
private:
	boost::scoped_ptr<HistCollection<TH1F*> > collection;
	boost::scoped_ptr<HistCollection<TH2F*> > collection2D;
};

}

#endif /* HISTOGRAMMANAGER_H_ */
