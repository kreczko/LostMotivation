/*
 * Filter.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef FILTER_H_
#define FILTER_H_

namespace BAT {

class Filter {
public:
	Filter();
	virtual ~Filter();
	Filter* createStandardFilter();
	void setGoodJetPtCut(float ptCut);
	void setGoodJetEtaCut(float etaCut);
	void setGoodElectronPtCut(float ptCut);
	void setGoodElectronEtaCut(float etaCut);
};

}

#endif /* FILTER_H_ */
