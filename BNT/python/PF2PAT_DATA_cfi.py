from BristolAnalysis.NTupleTools.pfTools import *
import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.patTemplate_cfg import *
postfix = "PF"  
postfix_Toto = "Toto"

def PF2PAtProcess():
    
    cloneProcessingSnippet(process, process.makePatElectrons, postfix_Toto)
    getattr(process, "patElectrons"+postfix_Toto).pfElectronSource = cms.InputTag("pfIsolatedElectronsTotoPF")

    process.selectedPatElectronsToto = process.selectedPatElectrons.clone()
    getattr(process, "selectedPatElectrons"+postfix_Toto).src = cms.InputTag("patElectrons"+postfix_Toto)
    
    getattr(process, "patElectrons"+postfix_Toto).useParticleFlow = True
    getattr(process, "patElectrons"+postfix_Toto).userIsolation   = cms.PSet()
    
    getattr(process, "patElectrons"+postfix_Toto).isoDeposits = cms.PSet(
    pfChargedHadrons = cms.InputTag("isoDepElectronWithCharged" + postfix),
    pfNeutralHadrons = cms.InputTag("isoDepElectronWithNeutral" + postfix),
    pfPhotons = cms.InputTag("isoDepElectronWithPhotons" + postfix)
    )
    
    getattr(process, "patElectrons"+postfix_Toto).isolationValues = cms.PSet(
    pfChargedHadrons = cms.InputTag("isoValElectronWithCharged" + postfix),
    pfNeutralHadrons = cms.InputTag("isoValElectronWithNeutral" + postfix),
    pfPhotons = cms.InputTag("isoValElectronWithPhotons" + postfix)
    )

#For this version of PatAlgos, patElectronIsolation is commented out
#getattr(process, "makePatElectrons", postfix_Toto).remove(getattr(process, "patElectronIsolation"+postfix_Toto))

    usePF2PAT( process, runPF2PAT = True, jetAlgo = 'AK5', runOnMC = False, postfix = postfix )
    # turn to false when running on data
    getattr( process, "patElectrons" + postfix ).embedGenMatch = False
    getattr( process, "patElectrons" + postfix_Toto ).addGenMatch = False #TL add 9 Jun
    getattr( process, "patElectrons" + postfix_Toto ).embedGenMatch = False #TL add 9 Jun   
    getattr( process, "patMuons" + postfix ).embedGenMatch = False
    getattr( process, "patJets" + postfix ).embedGenPartonMatch = False
    getattr( process, "patJets" + postfix ).embedGenJetMatch = False



    process.morePFElectron = cms.Sequence(
        getattr(process, "pfMET"+postfix) *
        getattr(process, "pfNoPileUpSequence"+postfix) *
        getattr(process, "pfAllNeutralHadrons"+postfix) *
        getattr(process, "pfAllChargedHadrons"+postfix) *
        getattr(process, "pfAllPhotons"+postfix) *
        getattr(process, "pfMuonSequence"+postfix) *
        getattr(process, "pfMuonSequence"+postfix) *
        getattr(process, "pfNoMuon"+postfix) *
        getattr(process, "pfElectronSequence"+postfix) *
        getattr(process, "makePatElectrons"+postfix_Toto) *
        getattr(process, "selectedPatElectrons"+postfix_Toto)        
        )

    # remove electronMatchToto
    process.makePatElectronsToto.remove(process.electronMatchToto)
########################################################################
    return process
