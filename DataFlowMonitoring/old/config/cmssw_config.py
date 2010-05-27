import FWCore.ParameterSet.Config as cms

# import the PatTuple sequence
from Workspace.ConfigurableAnalysis.FBtestFromAOD_cfg import *

# rename output file
#process.out.fileName = 'S9pat_enri1.root'
process.TFileService.fileName = outputfile
