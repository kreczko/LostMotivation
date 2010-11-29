import os

selection = "Data"
if os.environ.has_key('selection'):
    selection = os.environ['selection']

runOn_Data                = bool(0)
runOn_Data_EG             = bool(0)
runOn_MinBias_MC          = bool(0)
runOn_Spring10_Physics_MC = bool(0)

useREDIGI = False
runOnMC = False

if selection=="Data":
    runOn_Data = True
elif selection=="Data_EG":
    runOn_Data_EG = True
elif selection=="MinBias_MC":
    runOn_MinBias_MC = True
    runOnMC = True
else:
    runOn_Spring10_Physics_MC = True
    runOnMC = True
    
realData         = True
useREDIGI        = False
JECSetName       = "Spring10"
wantPatTuple     = bool(0)
doPDFweights     = bool(0)
applyBSCTrigOnMC = bool(1)
runOn35xInput    = bool(0)
outname          = "nTuple_data.root"
patname          = "pat_data.root"


if runOn_Data_EG:
    outname          = "nTuple_data_EG.root"
    patname          = "pat_data_EG.root"

elif runOn_MinBias_MC:
    realData         = False
    runOn35xInput    = True #check
    outname          = "nTuple_minbias.root"
    patname          = "pat_minbias.root"

elif runOn_Spring10_Physics_MC:
    realData         = False
    useREDIGI        = True
    applyBSCTrigOnMC = False
    runOn35xInput    = True
    outname          = "nTuple_mc.root"
    patname          = "pat_mc.root"


print "***********************************"
if runOn_Data:
    print " Running on Data"
if runOn_Data_EG:
    print " Running on Data EG skim"
if runOn_MinBias_MC:
    print " Running on MinBias MC"
if runOn_Spring10_Physics_MC:
    print " Running on Spring10 physics MC"
    
print "***********************************"
print "Switches:"
print "  realData:         ", realData
print "  useREDIGI:        ", useREDIGI
print "  JECSetName:       ", JECSetName
print "  wantPatTuple:     ", wantPatTuple
print "  doPDFweights:     ", doPDFweights
print "  applyBSCTrigOnMC: ", applyBSCTrigOnMC
print "  runOn35xInput:    ", runOn35xInput
print "***********************************"

if not realData and applyBSCTrigOnMC:
    print "***********************************"
    print " Running on MC, take note that following L1 Tech Trg BSC bits are required!!!"
    print "   (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39)"
    print "***********************************"

    
print "loading PF2PAT"
from BristolAnalysis.NTupleTools.PF2PAT_cfi import * 
process = PF2PAtProcess(realData)
###################
#  Add JPT jets
###################
# Ref: https://twiki.cern.ch/twiki/bin/view/CMS/JetPlusTracksCorrections
process.load("RecoJets.Configuration.RecoJPTJets_cff")

# Jet Correction (in 3_6_0)
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# to run on 35X input sample
# ref: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuidePATRecipes#CMSSW_3_6_X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
#if runOn35xInput:
#    run36xOn35xInput( process )




process.GlobalTag.globaltag =   cms.string('GR_R_38X_V13::All') #TL, 16 Apr
#START3X_V20 



from PhysicsTools.PatAlgos.tools.coreTools import *

#switch off new tau features introduced in 33X to restore 31X defaults
# new feaures: - shrinkingConeTaus instead of fixedCone ones
#              - TaNC discriminants attached for shrinkingConeTaus
#              - default preselection on cleaningLayer1
from PhysicsTools.PatAlgos.tools.tauTools import *
#switchTo31Xdefaults(process)



# turn off MC matching for the process
if realData:
    print "*********************"
    print "Turn off MC matching"
    print "*********************"
    removeMCMatching(process, ["All"])




# set jet corrections
#print "*******************************************************"
#print "Calling switchJECSet() to set jet energy corrections: ", JECSetName
#print "*******************************************************"
#from PhysicsTools.PatAlgos.tools.jetTools import switchJECSet
#switchJECSet( process, JECSetName )

from PhysicsTools.PatAlgos.tools.jetTools import *

# remove the tag infos
# need to keep tag infos to access SV info via pat::jet->tagInfoSecondaryVertex()
process.patJets.addTagInfos = False
# require jet pt > 10 (L2+L3 corrected)
process.selectedPatJets.cut = cms.string('pt > 10')
# look for at least one jet
process.countPatJets.minNumber = 0












### 6-1-10 ###
## TL added 6-1-10: add new jet collections
## Refer to PhysicsTools/PatAlgos/test/patLayer1_fromAOD_jetSuite_full_cfg.py
## The following block needs to be after 'removeMCMatching', otherwise will get error of 'genMetCalo not found'.
# uncomment the following line to add tcMET to the event content
from PhysicsTools.PatAlgos.tools.metTools import *
addTcMET(process, 'TC')
##addPfMET(process, 'PF')  ##<-- gives error of genMetCalo not found if put before removeMCMatching

# produce jpt corrected calo jets, which are not on AOD per default
#process.load("PhysicsTools.PatAlgos.recoLayer0.jetPlusTrack_cff")



print "*******************************"
print "Calling addJetCollection()"
print " Note: b-tagging and SSV info are not stored for the extra jet collections"
print "*******************************"

print process.patJetCorrFactors.corrSample



# add ak5GenJets as they are not in the Spring10 physics MC
# ref: https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/899/1/1/1/1.html

# ak5GenJets are NOT there: First load the needed modules
if runOn_Spring10_Physics_MC:
    process.load("RecoJets.Configuration.GenJetParticles_cff")
    process.load("RecoJets.JetProducers.ak5GenJets_cfi")
# process.p = cms.Path(process.genParticlesForJets *
#                      process.ak5GenJets )
                        

####################################
## JEC for the defaul jet collection
####################################
#process.patJetCorrFactors.corrSample = JECSetName
#The default in 382 appears to be spring10 

####################################
##
##    Add extra jet collections
##
####################################
# JPT jets
addJetCollection(process,cms.InputTag('JetPlusTrackZSPCorJetAntiKt5'),
                 'AK5', 'JPT',
                 doJTA        = True,
                 doBTagging   = True, #off
                 jetCorrLabel = ('AK5','JPT'), #None,
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection = cms.InputTag("ak5GenJets"),
                 doJetID      = True,
                 jetIdLabel   = "ak5"
                 )


# no btag for extra jets
#process.patJetsKT4Calo.addTagInfos = False
#process.patJetsKT6Calo.addTagInfos = False
process.patJetsAK5JPT.addTagInfos  =  False
#process.patJetsAK5PF.addTagInfos   = True
process.patJetsPF.addTagInfos   = False#True

process.patJets.addBTagInfo = False

################################
##  Jet Energy Correction
################################

#process.patJetCorrFactorsKT4Calo.corrSample = JECSetName
#process.patJetCorrFactorsKT6Calo.corrSample = JECSetName
#process.patJetCorrFactorsAK5JPT.corrSample  = JECSetName
###process.patJetCorrFactorsAK5PF.corrSample   = JECSetName
#process.patJetCorrFactorsPF.corrSample   = JECSetName



# Input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()



# test real data (copied from PatExample)
readFiles.extend( [
    'file:/storage/top/FED5D572-8DBA-DF11-B636-0030487FA609.root' ##re-reco Sep3 sample
   # 'file:/storage/top/6625EA96-45C7-DF11-860F-001D09F24F65.root' #2010B AOD sample
    ] );


if realData:
    process.source.fileNames = readFiles
else:
    if runOn_MinBias_MC:
        ## test using Spring10 MinBias MC
        process.source.fileNames = cms.untracked.vstring(
            '/store/mc/Spring10/MinBias/GEN-SIM-RECO/START3X_V26A_356ReReco-v1/0007/00536B4F-E23D-DF11-A2CF-003048678B26.root'
            )
    else:
        ## test using Spring10 ttjet: /TTbarJets-madgraph/Spring10_START3X_V26_S09-v1/GEN-SIM-RECO (need run33xOnReReco)
        process.source.fileNames = cms.untracked.vstring(
            #'rfio:/castor/cern.ch/user/t/tcheng/A4121AB4-0747-DF11-8984-0030487F171B.root'
        )

            

# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
if realData:
    
    process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0')
    
else:
    #    if applyBSCTrigOnMC:
    process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('(40 OR 41) AND NOT (36 OR 37 OR 38 OR 39)')
    




## TL 16 Apr
## - Added physics declared, scraping filter, pv filter
## - following the example in PhysicsTools/PatExamples/test/patLayer1_fromRECO_7TeV_firstdata_cfg.py
# require physics declared
#process.hltPhysicsDeclared = cms.EDFilter("PhysDecl",
#   applyfilter = cms.untracked.bool(True),
#   HLTriggerResults = cms.InputTag("TriggerResults","","HLT")
#)
# Update for 357
if runOn_Data and not runOn_Data_EG:
    process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
    process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'

    
# HLT Trigger Report
# process.hlTrigReport
#myHLT="HLT" #"REDIGI"
myHLT = "HLT"
if useREDIGI:
    myHLT = "REDIGI"
process.hlTrigReport = cms.EDAnalyzer("HLTrigReport",
    HLTriggerResults = cms.InputTag("TriggerResults","",myHLT)
)




# reduce verbosity
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)
#process.MessageLogger.cerr.INFO.limit = 10
#process.MessageLogger.cerr.threshold = "DEBUG"
process.MessageLogger.categories.append("HLTrigReport")
#process.MessageLogger.hlTrigReport.limit = 1000




# process all the events
process.maxEvents.input = -1 #20000
process.options.wantSummary = True

#process.out.outputCommands += (['keep *_*_*_*'
#                               ])


#from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent

process.out = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('pat_dataPATLayer1_Output.fromAOD_full.root'),
    outputCommands = cms.untracked.vstring('keep *',#'drop *',
                                           #*patEventContent)
                                           'keep *_patElectrons_*_*',
                                           'keep *_patElectronsToto_*_*',
                                           'keep *_patElectronsPF_*_*',
                                           'keep *_selectedPatElectronsToto_*_*',
                                           'keep *_selectedPatElectronsPF_*_*',
                                           'keep *_selectedPatMuonsPF_*_*',
                                           'keep *_selectedPatJetsPF_*_*',
                                           
                                           'keep *_cleanPatElectrons_*_*',
                                           'keep *_cleanPatEle2_*_*',
                                           'keep *_cleanPatEle3_*_*',
                                           'keep *_cleanPatMuons_*_*',
                                           'keep *_cleanPatMu2_*_*',
                                           'keep *_cleanPatMu3_*_*',
                                           'keep *_cleanPatJets_*_*',
                                           'keep *_cleanPatJetsAK5PF_*_*',
                                           'keep *_cleanPatJetsAK5JPT_*_*',
                                           'keep *_patMETs_*_*',
                                           'keep *_patMETsPF_*_*',
                                           'keep *_patMETsTC_*_*',
                                           'keep *_cleanPatPhotons_*_*',
                                           'keep *_cleanPatTaus_*_*',
                                           'keep recoSuperCluster_*_*_*',
                                           'keep recoTracks_generalTracks_*_*',
                                           'keep edmTriggerResults_TriggerResults_*_*',
                                           'keep *_offlinePrimaryVertices_*_*',
                                           'keep *_offlinePrimaryVerticesWithBS_*_*',
                                           'keep *_offlineBeamSpot_*_*'
                                           
                                           )
    )

process.out.fileName = patname
################# Above are examples from PhysicsTools ##############################

#commented next line out as not available (yet) in 38X 
#process.load("RecoEgamma.EgammaTools.correctedElectronsProducer_cfi")
print "WARNING"
print "Electrons have not been corrected for alignment"

#from RecoEgamma.EgammaTools.correctedElectronsProducer_cfi import *
#process.patElectrons.electronSource = "gsfElectrons::PAT"



# add PDFWeightProducer (8-2-2010)

if doPDFweights:
    process.pdfWeights = cms.EDProducer(
        "PdfWeightProducer",
        PdfInfoTag = cms.untracked.InputTag("generator"),
        PdfSetNames = cms.untracked.vstring("cteq66.LHgrid"
                                            #, "MRST2006nnlo.LHgrid"
                                            #, "MRST2007lomod.LHgrid"
                                            )
        )



#####################################################################
#
# Add second electron collections for d0 w.r.t beam-constrained PV
# TL: 10 May 2010
#
#####################################################################
#process.patElectrons.pvSrc = "offlinePrimaryVerticesWithBS"

import PhysicsTools.PatAlgos.producersLayer1.electronProducer_cfi as eleProducer
process.patEle2 = eleProducer.patElectrons.clone(
    pvSrc = "offlinePrimaryVerticesWithBS"
    )

process.patEle3 = eleProducer.patElectrons.clone(
    usePV = False,
    beamLineSrc = "offlineBeamSpot"
    )

import PhysicsTools.PatAlgos.cleaningLayer1.electronCleaner_cfi as eleCleaner
process.cleanPatEle2 = eleCleaner.cleanPatElectrons.clone(
    src = "patEle2"
    )
process.cleanPatEle3 = eleCleaner.cleanPatElectrons.clone(
    src = "patEle3"
    )

process.patElectronsPF.pvSrc = "offlinePrimaryVertices"


################
#  muons d0
################
import PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi as muProducer
process.patMu2 = muProducer.patMuons.clone(
    pvSrc = "offlinePrimaryVerticesWithBS"
    )
process.patMu3 = muProducer.patMuons.clone(
    usePV = False,
    beamLineSrc = "offlineBeamSpot"
    )

    
import PhysicsTools.PatAlgos.cleaningLayer1.muonCleaner_cfi as muCleaner
process.cleanPatMu2 = muCleaner.cleanPatMuons.clone(
    src = "patMu2"
    )
process.cleanPatMu3 = muCleaner.cleanPatMuons.clone(
    src = "patMu3"
    )


process.myExtraLepton = cms.Sequence(
        process.patEle2 *
        process.patEle3 *
        process.patMu2 *
        process.patMu3 *
        process.cleanPatEle2 *
        process.cleanPatEle3 *
        process.cleanPatMu2 *
        process.cleanPatMu3 *
        process.morePFElectron

)


### put the usual cff fragment here
process.InputTagDistributorService = cms.Service( "InputTagDistributorService" )

process.VariableHelperService = cms.Service( "VariableHelperService" )

process.UpdaterService = cms.Service( "UpdaterService" )

process.TFileService = cms.Service( "TFileService",
                           fileName = cms.string( 'ntuple.root' )
                           )

    
print "loading CFA config"
#from NTupler_cfi import *
#process.configurableAnalysis = getConfigurableAnalysis(runOnMC, useREDIGI)
process.load('Leptoquarks.RootTupleMakerV2.Ntuple_cff')
process.load("CommonTools.RecoAlgos.HBHENoiseFilter_cfi")
# RootTupleMakerV2 tree
process.rootTupleTree = cms.EDAnalyzer("RootTupleMakerV2_Tree",
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_rootTupleEvent_*_*',
        'keep *_rootTupleEventExtra_*_*',
        'keep *_rootTupleEventSelection_*_*',
        'keep *_rootTupleCaloJets_*_*',
        'keep *_rootTuplePFJets_*_*',
        'keep *_rootTupleElectrons_*_*',
        'keep *_rootTupleCaloMET_*_*',
        'keep *_rootTupleTCMET_*_*',
        'keep *_rootTuplePFMET_*_*',
        'keep *_rootTupleMuons_*_*',
        'keep *_rootTupleSuperClusters_*_*',
        'keep *_rootTupleTrigger_*_*',
        'keep *_rootTupleVertex_*_*',
        'keep *_rootTupleGenEventInfo_*_*',
        'keep *_rootTupleGenParticles_*_*',
        'keep *_rootTupleGenJets_*_*',
        'keep *_rootTupleGenMETTrue_*_*'
    )
)
process.TFileService.fileName = outname    

#to prevent patTuple output, delete the outpath:
if not wantPatTuple:
    del process.outpath
    
# let it run
if runOn_Data: 
    process.p = cms.Path(
        process.hltLevel1GTSeed*
        process.hltPhysicsDeclared*
        process.hlTrigReport *
        process.recoJPTJets * #jpt in 3_6
        #process.jptCaloJets* #jpt in 3_5
        process.patDefaultSequence *
        getattr(process,"patPF2PATSequence"+postfix) *
        process.myExtraLepton
#        process.configurableAnalysis
        )
    
elif runOn_Data_EG:
    process.p = cms.Path(
        process.HBHENoiseFilter *
        process.hlTrigReport *
        #process.myJPT *
        #process.gsfElectrons *
        #process.eIdSequence *
        process.patDefaultSequence *
        getattr(process,"patPF2PATSequence"+postfix) *
        process.myExtraLepton 
        )


elif runOn_MinBias_MC:
    
    process.p = cms.Path(
        process.hltLevel1GTSeed *
        process.hlTrigReport *
        #process.myJPT *
        process.patDefaultSequence *
        process.myExtraLepton *
        getattr(process,"patPF2PATSequence"+postfix)
        )

    if not applyBSCTrigOnMC:
        process.p.remove( process.hltLevel1GTSeed )
        

        
elif runOn_Spring10_Physics_MC:
    
    process.p = cms.Path(
        process.hlTrigReport *
        process.genParticlesForJets *
        process.ak5GenJets *
        #process.myJPT *
        process.patDefaultSequence *
        process.myExtraLepton *
        getattr(process,"patPF2PATSequence"+postfix)
        )
        
    ## add PDF weighs as required
    if doPDFweights:
        process.p *= process.pdfWeights
        
process.p *= (
    process.rootTupleEvent+
    process.rootTupleEventSelection+
    process.rootTupleCaloJets+
#    process.rootTuplePFJets+
    process.rootTupleElectrons+
    process.rootTupleCaloMET+
    process.rootTupleTCMET+
    process.rootTuplePFMET+
    process.rootTupleMuons+
#    process.rootTupleSuperClusters+
    process.rootTupleTrigger+
    process.rootTupleVertex+
    process.rootTupleGenEventInfo+
    process.rootTupleGenParticles+
    process.rootTupleGenJets+
    process.rootTupleGenMETTrue
    )*process.rootTupleTree
    