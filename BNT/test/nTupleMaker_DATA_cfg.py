import FWCore.ParameterSet.Config as cms
# Starting with a skeleton process which gets imported with the following line

import sys
print sys.argv
import os
# Select input type ("Data", "Data_EG", "MinBias_MC" or "Spring10_Physics_MC")
os.environ['selection'] = "Data_EG"

from BristolAnalysis.NTupleTools.runBasics_cfi import process

process.source.fileNames = cms.untracked.vstring(
            'file:/storage/top/FED5D572-8DBA-DF11-B636-0030487FA609.root'
            )

process.TFileService.fileName = 'testNtupler.root'