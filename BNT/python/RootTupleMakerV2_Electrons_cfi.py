import FWCore.ParameterSet.Config as cms

rootTupleElectrons = cms.EDProducer("RootTupleMakerV2_Electrons",
    TracksInputTag = cms.InputTag('generalTracks'),
    DCSInputTag = cms.InputTag('scalersRawToDigi'),
    InputTag = cms.InputTag('cleanPatElectrons'),
    InputTag2 = cms.InputTag('cleanPatEle2'),
    InputTag3 = cms.InputTag('cleanPatEle3'),
    Prefix = cms.string('Electron'),
    Suffix = cms.string(''),
    MaxSize = cms.uint32(10),
    ElectronIso = cms.double(0.1),
    MuonPt = cms.double(10.),
    MuonIso = cms.double(0.05),
    MuonID = cms.string('GlobalMuonPromptTight'),
    VertexInputTag = cms.InputTag('offlinePrimaryVertices')
)
