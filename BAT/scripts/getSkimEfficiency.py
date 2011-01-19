from __future__ import division

from optparse import OptionParser
import sys
from fileInfo import *
from ROOT import *
from mergeROOTFilesWithCompression import getProcess

pathToSkimHist = "LJFilter/EventCount/EventCounter"

def getSkimInfo(files):
    skimHist = getSkimHist(files)
    numberOfTotalEvents = skimHist.GetBinContent(1)
    numberOfSkimmedEvents = skimHist.GetBinContent(2)
    skimEfficiency = numberOfSkimmedEvents/numberOfTotalEvents
    return {'total': numberOfTotalEvents, 'skimmed':numberOfSkimmedEvents, 'efficiency':skimEfficiency}
            
def getSkimHist(files):
    skimHist = None
    
    TfOpen = TFile.Open
    gcd = gROOT.cd
    
    for file in files:
        f = TfOpen(file)
        gcd()
        if skimHist is None:
            skimHist = f.Get(pathToSkimHist)
            if skimHist is None:
                print 'Could not find histogram', pathToSkimHist, 'in file', file
                continue
        else:
            hist = f.Get(pathToSkimHist)
            if hist is None:
                print 'Could not find histogram', pathToSkimHist, 'in file', file
                continue
            skimHist.Add(hist)
    return skimHist
            

if __name__ == "__main__":
    args = sys.argv
    if not len(args) == 2:
        print "Please specify a folder to merge files in."
        sys.exit()
        
    path = sys.argv[1]
    files = getROOTFiles(path)
    events = getSkimInfo(files)
    
    print 'Total number of files:', len(files)
    print 'Process recognised:', getProcess(files[0])
    print 'Total number of events:', int(events['total'])
    print 'Skimmed number of events:', int(events['skimmed'])
    print 'Skim efficiency:', events['efficiency']
