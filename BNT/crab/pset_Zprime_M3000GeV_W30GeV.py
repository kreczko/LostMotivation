from pset_default_MC import *

# rename output file
proc = 'Zprime_M3000GeV_W30GeV'
process.TFileService.fileName = 'nTuple_%s.root' %proc
process.out.fileName          = 'pat_%s.root' %proc