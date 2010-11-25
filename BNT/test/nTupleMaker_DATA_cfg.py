from BristolAnalysis.NTupleTools.runBasics_DATA_cfi import process

process.source.fileNames = cms.untracked.vstring(
            'file:/storage/top/Nov4ReReco_example.root'
            )
process.ak5CaloL2Relative.useCondDB = False
process.ak5CaloL3Absolute.useCondDB = False
process.ak5CaloResidual.useCondDB = False
process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False
process.TFileService.fileName = 'testNtupler_DATA.root'

process.maxEvents.input = -1 