from BristolAnalysis.NTupleTools.runBasics_MC_cfi import process

process.source.fileNames = cms.untracked.vstring(
            'file:/storage/top/mc/ttbarAODSIM38X.root'
            )
process.ak5CaloL2Relative.useCondDB = False
process.ak5CaloL3Absolute.useCondDB = False
process.ak5CaloResidual.useCondDB = False
process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False
process.TFileService.fileName = 'testNtupler_MC.root'

process.maxEvents.input = 100