/*
 * Electron.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRON_H_
#define ELECTRON_H_
#include "Particle.h"
#include <vector>
#include <string>
#include <boost/static_assert.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include "Jet.h"
#include "Track.h"

namespace BAT {
//make sure the IDs and their string representations are identical
//

class Electron: public Particle {
public:
    enum Algorithm {
        Calo, ParticleFlow, NUMBER_OF_ELECTRONALGORITHMS
    };

    enum ElectronID {
        loose, tight, robustLoose, robustTight, VBTF_W70, HEEP, NUMBER_OF_ELECTRONIDS
    };
    static const boost::array<std::string, NUMBER_OF_ELECTRONIDS> ElectronIDNames;
    static float goodElectronMinimalEt;
    static float goodElectronMaximalAbsoluteEta;
    static float goodElectronMaximalDistanceFromInteractionPoint;

    static float looseElectronMinimalEt;
    static float looseElectronMaximalAbsoluteEta;

    static float MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion;

    static float isolatedElectronMaximalRelativeIsolation;
    static float looseIsolatedElectronMaximalRelativeIsolation;

    static std::string getElectronIDAsString(ElectronID id) {
        return Electron::ElectronIDNames.at(id);
    }

    static void resetSelectionValues() {
        Electron::goodElectronMinimalEt = 0;
        Electron::goodElectronMaximalAbsoluteEta = 5;
        Electron::goodElectronMaximalDistanceFromInteractionPoint = 5000;

        Electron::looseElectronMinimalEt = 0;
        Electron::looseElectronMaximalAbsoluteEta = 5;
        Electron::looseIsolatedElectronMaximalRelativeIsolation = 5000;

        Electron::MaximalNumberOfMissingInnerLayerHitsBeforeCalledConversion = 500;

        Electron::isolatedElectronMaximalRelativeIsolation = 2;
    }

    Electron();
    Electron(const Electron& other);
    Electron(float energy, float px, float py, float pz);
    virtual ~Electron();
    bool isGood() const;
    bool isIsolated() const;
    bool isHEEPIsolated() const;
    bool isFromConversion() const;
    bool isLoose() const;

    float ecalIsolation() const;
    float hcalIsolation() const;
    float trackerIsolation() const;
    float superClusterEta() const;
    float sigmaIEtaIEta() const;
    float dPhiIn() const;
    float dEtaIn() const;
    float HadOverEm() const;
    float HEEPet() const;
    bool VBTF_W70_ElectronID() const;
    bool VBTF_W95_ElectronID() const;
    bool RobustLooseID() const;
    bool RobustTightID() const;
    unsigned short getClosestJetID(const JetCollection& jets) const;
    Algorithm getUsedAlgorithm() const;
    const TrackPointer GSFTrack() const;
    int closestCTFTrackID() const;
    float shFracInnerLayer() const;

    void setRobustLooseID(bool id);
    void setRobustTightID(bool id);

    void setSuperClusterEta(float eta);
    void setEcalIsolation(float isolation);
    void setHcalIsolation(float isolation);
    void setTrackerIsolation(float isolation);
    void setNumberOfMissingInnerLayerHits(float missingHits);
    void setUsedAlgorithm(Algorithm algo);
    void setSigmaIEtaIEta(float sigma);
    void setDPhiIn(float dphi);
    void setDEtaIn(float deta);
    void setHadOverEm(float HoverE);
    void setGSFTrack(const TrackPointer track);
    void setClosestTrackID(const int trackID);
    void setSharedFractionInnerHits(float hits);
    void setElectronVertexZPosition(float z);
    void setZDistanceToPrimaryVertex(float dist);

    float relativeIsolation() const;

    bool isInBarrelRegion() const;
    bool isInCrack() const;
    bool isInEndCapRegion() const;

    float vz() const;

private:
    Algorithm usedAlgorithm;
    bool robustLooseId, robustTightId;
    float superCluser_Eta;
    float ecal_Isolation, hcal_Isolation, tracker_Isolation;
    float innerLayerMissingHits;
    //used for HEEP
    float sigma_IEtaIEta, dPhi_In, dEta_In, hadOverEm;
    TrackPointer gsfTrack;
    int closesTrackID;
    float sharedFractionInnerHits;
    float vertex_z, zDistanceToPrimaryVertex;


    bool getVBTF_W70_ElectronID_Barrel() const;
    bool getVBTF_W70_ElectronID_Endcap() const;
    bool getVBTF_W95_ElectronID_Barrel() const;
    bool getVBTF_W95_ElectronID_Endcap() const;

};

typedef boost::shared_ptr<Electron> ElectronPointer;
typedef std::vector<ElectronPointer> ElectronCollection;

}

#endif /* ELECTRON_H_ */
