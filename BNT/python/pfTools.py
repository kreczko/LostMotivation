import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.tauTools import *

from PhysicsTools.PatAlgos.tools.helpers import listModules, applyPostfix


def warningIsolation():
    print "WARNING: particle based isolation must be studied"

def adaptPFMuons(process,module,postfix="" ):    
    print "Adapting PF Muons "
    print "***************** "
    warningIsolation()
    print 
    module.useParticleFlow = True
    module.userIsolation   = cms.PSet()
    module.isoDeposits = cms.PSet(
        pfChargedHadrons = cms.InputTag("isoDepMuonWithCharged" + postfix),
        pfNeutralHadrons = cms.InputTag("isoDepMuonWithNeutral" + postfix),
        pfPhotons = cms.InputTag("isoDepMuonWithPhotons" + postfix)
        )
    module.isolationValues = cms.PSet(
        pfChargedHadrons = cms.InputTag("isoValMuonWithCharged" + postfix),
        pfNeutralHadrons = cms.InputTag("isoValMuonWithNeutral" + postfix),
        pfPhotons = cms.InputTag("isoValMuonWithPhotons" + postfix)
        )
    # matching the pfMuons, not the standard muons.
    applyPostfix(process,"muonMatch",postfix).src = module.pfMuonSource

    print " muon source:", module.pfMuonSource
    print " isolation  :",
    print module.isolationValues
    print " isodeposits: "
    print module.isoDeposits
    print 
    

def adaptPFElectrons(process,module, postfix):
    # module.useParticleFlow = True
    print "Adapting PF Electrons "
    print "********************* "
    warningIsolation()
    print 
    module.useParticleFlow = True
    module.userIsolation   = cms.PSet()
    module.isoDeposits = cms.PSet(
        pfChargedHadrons = cms.InputTag("isoDepElectronWithCharged" + postfix),
        pfNeutralHadrons = cms.InputTag("isoDepElectronWithNeutral" + postfix),
        pfPhotons = cms.InputTag("isoDepElectronWithPhotons" + postfix)
        )
    module.isolationValues = cms.PSet(
        pfChargedHadrons = cms.InputTag("isoValElectronWithCharged" + postfix),
        pfNeutralHadrons = cms.InputTag("isoValElectronWithNeutral" + postfix),
        pfPhotons = cms.InputTag("isoValElectronWithPhotons" + postfix)
        )

    # COLIN: since we take the egamma momentum for pat Electrons, we must
    # match the egamma electron to the gen electrons, and not the PFElectron.  
    # -> do not uncomment the line below.
    # process.electronMatch.src = module.pfElectronSource
    # COLIN: how do we depend on this matching choice? 

    print " PF electron source:", module.pfElectronSource
    print " isolation  :"
    print module.isolationValues
    print " isodeposits: "
    print module.isoDeposits
    print 
    
    print "removing traditional isolation"

    removeIfInSequence(process,  "patElectronIsolation",  "patDefaultSequence", postfix)

def adaptPFPhotons(process,module):
    raise RuntimeError, "Photons are not supported yet"

from RecoTauTag.RecoTau.TauDiscriminatorTools import adaptTauDiscriminator, producerIsTauTypeMapper 

def reconfigurePF2PATTaus(process,
      tauType='shrinkingConePFTau', 
      pf2patSelection=["DiscriminationByIsolation", "DiscriminationByLeadingPionPtCut"],
      selectionDependsOn=["DiscriminationByLeadingTrackFinding"],
      producerFromType=lambda producer: producer+"Producer",
      postfix = ""):
   print "patTaus will be produced from taus of type: %s that pass %s" \
	 % (tauType, pf2patSelection)

   # Get the prototype of tau producer to make, i.e. fixedConePFTauProducer
   producerName = producerFromType(tauType) + postfix
   # Set as the source for the pf2pat taus (pfTaus) selector
   applyPostfix(process,"pfTaus", postfix).src = producerName
   # Start our pf2pat taus base sequence
   setattr(process,"pfTausBaseSequence"+postfix, cms.Sequence(getattr(process,
      producerName)))
   baseSequence = getattr(process,"pfTausBaseSequence"+postfix)
   
   #make custom mapper to take postfix into account (could have gone with lambda of lambda but... )
   def producerIsTauTypeMapperWithPostfix(tauProducer):
       return lambda x: producerIsTauTypeMapper(tauProducer)+x.group(1)+postfix

   def recoTauTypeMapperWithGroup(tauProducer):
       return "%s(.*)"%recoTauTypeMapper(tauProducer)

   # Get our prediscriminants
   for predisc in selectionDependsOn:
      # Get the prototype
      originalName = tauType+predisc # i.e. fixedConePFTauProducerDiscriminationByLeadingTrackFinding
      clonedName = "pfTausBase"+predisc+postfix
      clonedDisc = getattr(process, originalName).clone()
      # Register in our process
      setattr(process, clonedName, clonedDisc)
      baseSequence += getattr(process, clonedName)
      clonedDisc.PFTauProducer = cms.InputTag(clonedDisc.PFTauProducer.value()+postfix)
      # Adapt this discriminator for the cloned prediscriminators 
      adaptTauDiscriminator(clonedDisc, newTauProducer="pfTausBase", 
                            oldTauTypeMapper=recoTauTypeMapperWithGroup,
                            newTauTypeMapper=producerIsTauTypeMapperWithPostfix,
                            preservePFTauProducer=True)
   # Reconfigure the pf2pat PFTau selector discrimination sources
   applyPostfix(process,"pfTaus", postfix).discriminators = cms.VPSet()
   for selection in pf2patSelection:
      # Get our discriminator that will be used to select pfTaus
      originalName = tauType+selection
      clonedName = "pfTausBase"+selection+postfix
      clonedDisc = getattr(process, originalName).clone()
      # Register in our process
      setattr(process, clonedName, clonedDisc)
      clonedDisc.PFTauProducer = cms.InputTag(clonedDisc.PFTauProducer.value()+postfix)
      # Adapt our cloned discriminator to the new prediscriminants
      adaptTauDiscriminator(clonedDisc, newTauProducer="pfTausBase",
                            oldTauTypeMapper=recoTauTypeMapperWithGroup,
                            newTauTypeMapper=producerIsTauTypeMapperWithPostfix,
                            preservePFTauProducer=True)
      baseSequence += clonedDisc
      # Add this selection to our pfTau selectors
      applyPostfix(process,"pfTaus", postfix).discriminators.append(cms.PSet(
         discriminator=cms.InputTag(clonedName), selectionCut=cms.double(0.5)))


def adaptPFTaus(process,tauType = 'shrinkingConePFTau', postfix = ""):
    oldTaus =  applyPostfix(process,"patTaus", postfix).tauSource

    # Set up the collection used as a preselection to use this tau type    
    reconfigurePF2PATTaus(process, tauType, postfix=postfix)
    applyPostfix(process,"patTaus", postfix).tauSource = cms.InputTag("pfTaus"+postfix)
    
    redoPFTauDiscriminators(process, 
                            cms.InputTag(tauType+'Producer'),
                            applyPostfix(process,"patTaus", postfix).tauSource,
                            tauType, postfix=postfix)


    #switchToAnyPFTau(process, oldTaus, process.patTaus.tauSource, tauType)
    switchToPFTauByType(process, pfTauType=tauType,
                        pfTauLabelNew=applyPostfix(process,"patTaus", postfix).tauSource,
                        pfTauLabelOld=oldTaus,postfix=postfix)

    applyPostfix(process,"makePatTaus", postfix).remove(
        applyPostfix(process,"patPFCandidateIsoDepositSelection", postfix)
        )

#helper function for PAT on PF2PAT sample
def tauTypeInPF2PAT(process,tauType='shrinkingConePFTau', postfix = ""): 
    process.load("PhysicsTools.PFCandProducer.pfTaus_cff")
    applyPostfix(process, "pfTaus",postfix).src = cms.InputTag(tauType+'Producer'+postfix)
            

def addPFCandidates(process,src,patLabel='PFParticles',cut="",postfix=""):
    from PhysicsTools.PatAlgos.producersLayer1.pfParticleProducer_cfi import patPFParticles
    # make modules
    producer = patPFParticles.clone(pfCandidateSource = src)
    filter   = cms.EDFilter("PATPFParticleSelector", 
                    src = cms.InputTag("pat" + patLabel), 
                    cut = cms.string(cut))
    counter  = cms.EDFilter("PATCandViewCountFilter",
                    minNumber = cms.uint32(0),
                    maxNumber = cms.uint32(999999),
                    src       = cms.InputTag("pat" + patLabel))
    # add modules to process
    setattr(process, "pat"         + patLabel, producer)
    setattr(process, "selectedPat" + patLabel, filter)
    setattr(process, "countPat"    + patLabel, counter)
    # insert into sequence
    getattr(process, "patDefaultSequence"+postfix).replace(
        applyPostfix(process, "patCandidateSummary", postfix),
        producer+applyPostfix(process, "patCandidateSummary", postfix)
    )
    getattr(process, "patDefaultSequence"+postfix).replace(
        applyPostfix(process, "selectedPatCandidateSummary", postfix),
        filter+applyPostfix(process, "selectedPatCandidateSummary", postfix)
    )

    tmpCountPatCandidates = applyPostfix(process, "countPatCandidates", postfix)
    tmpCountPatCandidates+=counter
    # summary tables
    applyPostfix(process, "patCandidateSummary", postfix).candidates.append(cms.InputTag('pat' + patLabel))
    applyPostfix(process, "selectedPatCandidateSummary", postfix).candidates.append(cms.InputTag('selectedPat' + patLabel))

        
def switchToPFMET(process,input=cms.InputTag('pfMET'), postfix=""):
    print 'MET: using ', input
    oldMETSource = applyPostfix(process, "patMETs",postfix).metSource
    applyPostfix(process, "patMETs",postfix).metSource = input
    applyPostfix(process, "patMETs",postfix).addMuonCorrections = False
    getattr(process, "patDefaultSequence"+postfix).remove(
        applyPostfix(process, "patMETCorrections",postfix)
        )

def switchToPFJets(process, input=cms.InputTag('pfNoTau'), algo='IC5', postfix = ""):

    print "Switching to PFJets,  ", algo
    print "************************ "

    if( algo == 'IC5' ):
        genJetCollection = cms.InputTag('iterativeCone5GenJetsNoNu')
    elif algo == 'AK5':
        genJetCollection = cms.InputTag('ak5GenJetsNoNu')
    else:
        print 'bad jet algorithm:', algo, '! for now, only IC5 and AK5 are allowed. If you need other algorithms, please contact Colin'
        sys.exit(1)
        
    # changing the jet collection in PF2PAT:
    from PhysicsTools.PFCandProducer.Tools.jetTools import jetAlgo
    process.allPfJets = jetAlgo( algo );    
    switchJetCollection(process,
                        input,
                        jetIdLabel = algo,
                        doJTA=True,
                        doBTagging=True,
                        jetCorrLabel=( algo, 'PF' ), 
                        doType1MET=False,
                        genJetCollection = genJetCollection,
                        doJetID = True,
			postfix = postfix
                        )
    
    applyPostfix(process, "patJets", postfix).embedCaloTowers   = False
    applyPostfix(process, "patJets", postfix).embedPFCandidates   = True

#-- Remove MC dependence ------------------------------------------------------
def removeMCMatchingPF2PAT( process, postfix="" ):
    from PhysicsTools.PatAlgos.tools.coreTools import removeMCMatching
    removeIfInSequence(process,  "genForPF2PATSequence",  "patDefaultSequence", postfix)
    removeMCMatching(process, ['All'],postfix)


def usePF2PAT(process, runPF2PAT=True, jetAlgo='IC5', runOnMC=True, postfix = ""):
    # PLEASE DO NOT CLOBBER THIS FUNCTION WITH CODE SPECIFIC TO A GIVEN PHYSICS OBJECT.
    # CREATE ADDITIONAL FUNCTIONS IF NEEDED. 


    """Switch PAT to use PF2PAT instead of AOD sources. if 'runPF2PAT' is true, we'll also add PF2PAT in front of the PAT sequence"""

    # -------- CORE ---------------
    if runPF2PAT:
        process.load("PhysicsTools.PFCandProducer.PF2PAT_cff")
		
        process.pfIsolatedElectronsToto = process.pfIsolatedElectrons.clone()
        process.pfIsolatedElectronsToto.combinedIsolationCut = cms.double(10000)
        process.pfElectronSequence = cms.Sequence(
			process.pfAllElectrons +
			process.pfElectronsPtGt5 +
			# computing isolation variables:
			process.pfElectronIsolationSequence +
			# selecting isolated electrons:
			process.pfIsolatedElectrons +
			process.pfIsolatedElectronsToto
		)
		
        #add Pf2PAT *before* cloning so that overlapping modules are cloned too
        #process.patDefaultSequence.replace( process.patCandidates, process.PF2PAT+process.patCandidates)
        process.patPF2PATSequence = cms.Sequence( process.PF2PAT + process.patDefaultSequence)
    else:
        process.patPF2PATSequence = cms.Sequence( process.patDefaultSequence )
        

    if not postfix == "":
        from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet
        cloneProcessingSnippet(process, process.patPF2PATSequence, postfix)
        #delete everything pat PF2PAT modules! if you want to test the postfixing for completeness
        #from PhysicsTools.PatAlgos.tools.helpers import listModules,listSequences
        #for module in listModules(process.patDefaultSequence):
        #    if not module.label() is None: process.__delattr__(module.label())
        #for sequence in listSequences(process.patDefaultSequence):
        #    if not sequence.label() is None: process.__delattr__(sequence.label())
        #del process.patDefaultSequence

    removeCleaning(process, postfix=postfix)

    # -------- OBJECTS ------------
    # Muons
    adaptPFMuons(process, 
                 applyPostfix(process,"patMuons",postfix),
                 postfix)

    
    # Electrons
    adaptPFElectrons(process,
                     applyPostfix(process,"patElectrons",postfix),
                     postfix)
    # Photons
    print "Temporarily switching off photons completely"

    removeSpecificPATObjects(process,['Photons'],False,postfix)
    removeIfInSequence(process,  "patPhotonIsolation",  "patDefaultSequence", postfix)

    # Jets
    switchToPFJets( process, cms.InputTag('pfNoTau'+postfix), jetAlgo, postfix=postfix )
    
    # Taus
    #adaptPFTaus( process ) #default (i.e. shrinkingConePFTau)
    adaptPFTaus( process, tauType='shrinkingConePFTau', postfix=postfix )

    # MET
    switchToPFMET(process, cms.InputTag('pfMET'+postfix), postfix=postfix)
    
    # Unmasked PFCandidates
    addPFCandidates(process,cms.InputTag('pfNoJet'+postfix),patLabel='PFParticles',cut="",postfix=postfix)

    if runOnMC:
        process.load("PhysicsTools.PFCandProducer.genForPF2PAT_cff")
        getattr(process, "patDefaultSequence"+postfix).replace(
            applyPostfix(process,"patCandidates",postfix),
            process.genForPF2PATSequence+applyPostfix(process,"patCandidates",postfix)
            )
    else:
        removeMCMatchingPF2PAT( process, postfix )
