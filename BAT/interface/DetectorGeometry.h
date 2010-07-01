/*
 * DetectorGeometry.h
 *
 *  Created on: Jun 30, 2010
 *      Author: lkreczko
 */

#ifndef DETECTORGEOMETRY_H_
#define DETECTORGEOMETRY_H_
namespace BAT {

namespace Detector {

namespace Barrel {
static const float MaximalAbsoluteEta = 1.442;
}

namespace Crack {
static const float MinimalAbsoluteEta = 1.442;
static const float MaximalAbsoluteEta = 1.56;
}

namespace EndCap {
static const float MinimalAbsoluteEta = 1.56;
}

}
}
#endif /* DETECTORGEOMETRY_H_ */
