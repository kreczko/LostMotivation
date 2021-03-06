import FWCore.ParameterSet.Config as cms

rootTupleCaloMET = cms.EDProducer( "RootTupleMakerV2_MET",
    InputTag = cms.InputTag( 'patMETs' ),
    Prefix = cms.string( 'Calo' ),
    Suffix = cms.string( '' ),
    StoreUncorrectedMET = cms.bool( True )
 )

rootTupleTCMET = cms.EDProducer( "RootTupleMakerV2_MET",
    InputTag = cms.InputTag( 'patMETsTC' ),
    Prefix = cms.string( 'TC' ),
    Suffix = cms.string( '' ),
    StoreUncorrectedMET = cms.bool( False )
 )

rootTuplePFMET = cms.EDProducer( "RootTupleMakerV2_MET",
    InputTag = cms.InputTag( 'patMETsPF' ),
    Prefix = cms.string( 'PF' ),
    Suffix = cms.string( '' ),
    StoreUncorrectedMET = cms.bool( False )
 )

rootTuplePFMETType1Cor = cms.EDProducer( "RootTupleMakerV2_MET_Extra",
    InputTag = cms.InputTag( 'patMETsPFType1Cor' ),
    Prefix = cms.string( 'PF' ),
    Suffix = cms.string( 'Type1Cor' ),
    StoreUncorrectedMET = cms.bool( False )
 )

rootTupleCaloMETExtra = cms.EDProducer( "RootTupleMakerV2_MET_Extra",
    InputTag = cms.InputTag( 'patMETs' ),
    Prefix = cms.string( 'Calo' ),
    Suffix = cms.string( '' ),
    StoreUncorrectedMET = cms.bool( True )
 )

rootTupleTCMETExtra = cms.EDProducer( "RootTupleMakerV2_MET_Extra",
    InputTag = cms.InputTag( 'patMETsTC' ),
    Prefix = cms.string( 'TC' ),
    Suffix = cms.string( '' ),
    StoreUncorrectedMET = cms.bool( False )
 )

rootTuplePFMETExtra = cms.EDProducer( "RootTupleMakerV2_MET_Extra",
    InputTag = cms.InputTag( 'patMETsPF' ),
    Prefix = cms.string( 'PF' ),
    Suffix = cms.string( '' ),
    StoreUncorrectedMET = cms.bool( False )
 )

rootTuplePFMETType1CorExtra = cms.EDProducer( "RootTupleMakerV2_MET_Extra",
    InputTag = cms.InputTag( 'patMETsPFType1Cor' ),
    Prefix = cms.string( 'PF' ),
    Suffix = cms.string( 'Type1Cor' ),
    StoreUncorrectedMET = cms.bool( False )
    )


rootTupleMETSequence = cms.Sequence( rootTupleCaloMET + rootTuplePFMET  
                                     + rootTupleCaloMETExtra + rootTuplePFMETExtra)
