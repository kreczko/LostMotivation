/*
 * Enumerators.h
 *
 *  Created on: Jun 30, 2010
 *      Author: lkreczko
 */

#ifndef ENUMERATORS_H_
#define ENUMERATORS_H_
#include <string>
#include <boost/array.hpp>

namespace BAT {
namespace DataType {
enum value {
    DATA,
    ttbar,
    Wjets,
    Zjets,
    QCD_BCtoE_Pt20to30,
    QCD_BCtoE_Pt30to80,
    QCD_BCtoE_Pt80to170,
    QCD_EMEnriched_Pt20to30,
    QCD_EMEnriched_Pt30to80,
    QCD_EMEnriched_Pt80to170,//10
    PhotonJets_Pt40to100,
    PhotonJets_Pt100to200,
    PhotonJets_Pt200toInf,
    VQQ,
    singleTop_And_W,
    singleTopTChannel,
    singleTopSChannel,
    Zprime_M500GeV_W5GeV,
    Zprime_M500GeV_W50GeV,
    Zprime_M750GeV_W7500MeV,//20
    Zprime_M1TeV_W10GeV,
    Zprime_M1TeV_W100GeV,
    Zprime_M1250GeV_W12500MeV,
    Zprime_M1500GeV_W15GeV,
    Zprime_M1500GeV_W150GeV,
    Zprime_M2TeV_W20GeV,
    Zprime_M2TeV_W200GeV,
    Zprime_M3TeV_W30GeV,
    Zprime_M3TeV_W300GeV,
    Zprime_M4TeV_W40GeV,//30
    Zprime_M4TeV_W400GeV,
    //    QCD_ALL,
    //    singleTop_ALL,
    NUMBER_OF_DATA_TYPES
};

const boost::array<std::string, DataType::NUMBER_OF_DATA_TYPES> names = { {
        "data",
        "ttjet",
        "wj",
        "zj",
        "bce1",
        "bce2",
        "bce3",
        "enri1",
        "enri2",
        "enri3",//10
        "pj1",
        "pj2",
        "pj3",
        "VqqJets",
        "tW",
        "tchan",
        "schan",
        "Zprime_M500GeV_W5GeV",
        "Zprime_M500GeV_W50GeV",
        "Zprime_M750GeV_W7500MeV",//20
        "Zprime_M1TeV_W10GeV",
        "Zprime_M1TeV_W100GeV",
        "Zprime_M1250GeV_W12500MeV",
        "Zprime_M1500GeV_W15GeV",
        "Zprime_M1500GeV_W150GeV",
        "Zprime_M2TeV_W20GeV",
        "Zprime_M2TeV_W200GeV",
        "Zprime_M3TeV_W30GeV",
        "Zprime_M3TeV_W300GeV",
        "Zprime_M4TeV_W40GeV",//30
        "Zprime_M4TeV_W400GeV" } };
}

namespace NeutrinoSelectionCriterion {
enum value {
    pzClosestToLepton, mostCentral, pzClosestToLeptonOrMostcentralIfAbove300, largestValueOfCosine, chi2, TopMassDifference
};
}

namespace HLT {
enum trigger {

};
}

namespace JetBin {
enum value {
    NoJet,
    OneJet,
    TwoJets,
    ThreeJets,
    FourOrMoreJets,
    NUMBER_OF_JET_BINS
};

const boost::array<std::string, JetBin::NUMBER_OF_JET_BINS> names = {
        { "0jet", "1jet", "2jets", "3jets", "4orMoreJets"
        } };
}

namespace JetBinSummed {
enum value {
    allJet,
    OneOrMoreJets,
    TwoOrMoreJets,
    ThreeOrMoreJets,
    NUMBER_OF_SUMMED_JET_BINS
};

const boost::array<std::string, JetBinSummed::NUMBER_OF_SUMMED_JET_BINS> names = { {
        "allJets",
        "1orMoreJets",
        "2orMoreJets",
        "3orMoreJets" } };
}

namespace BJetBin {
enum value {
    NoBtag,
    OneBTag,
    TwoBtags,
    ThreeBtags,
    FourOrMoreBTags,
    NUMBER_OF_BJET_BINS
};

const boost::array<std::string, BJetBin::NUMBER_OF_BJET_BINS> names = { {
        "0btag",
        "1btag",
        "2btags",
        "3btags",
        "4orMoreBtags" } };
}

namespace BJetBinSummed {
enum value {
    allBtags,
    OneOrMoreBTags,
    TwoOrMoreBTags,
    ThreeOrMoreBTags,
    NUMBER_OF_SUMMED_BJET_BINS
};

const boost::array<std::string, BJetBinSummed::NUMBER_OF_SUMMED_BJET_BINS> names = { {
        "allBtags",
        "1orMoreBtag",
        "2orMoreBtags",
        "3orMoreBtags" } };
}

namespace JetAlgorithm {
enum value {
    Calo_AntiKT_Cone05,
    JPT_AntiKt_ConeDR05,
    ParticleFlow,
    PF2PAT,
    NUMBER_OF_JETALGORITHMS
};
//for nTuple branch names
const boost::array<std::string, JetAlgorithm::NUMBER_OF_JETALGORITHMS> prefixes = { {
        "jets",
        "jetsJPTAK5",
        "PFJets2",
        "PFJets" } };

const boost::array<std::string, JetAlgorithm::NUMBER_OF_JETALGORITHMS> names = { {
        "CaloJets",
        "JPT",
        "PFJets",
        "PF2PATJets" } };
}

namespace METAlgorithm {
enum value {
    Calo,
    tcMET,
    ParticleFlowMET,
    NUMBER_OF_METALGORITHMS
};

const boost::array<std::string, METAlgorithm::NUMBER_OF_METALGORITHMS> prefixes = { {
        "mets",
        "tcmets",
        "PFMets"  } };

const boost::array<std::string, METAlgorithm::NUMBER_OF_METALGORITHMS> names = { {
        "CaloMET",
        "TCMET",
        "PFMET" } };
}

namespace ElectronAlgorithm {
enum value {
    Calo,
    ParticleFlow,
    NUMBER_OF_ELECTRONALGORITHMS
};

const boost::array<std::string, ElectronAlgorithm::NUMBER_OF_ELECTRONALGORITHMS> prefixes = { {
        "els",
        "PFElsAll"  } };

const boost::array<std::string, ElectronAlgorithm::NUMBER_OF_ELECTRONALGORITHMS> names = { {
        "CaloElectron",
        "PFElectron"} };
}

}

#endif /* ENUMERATORS_H_ */
