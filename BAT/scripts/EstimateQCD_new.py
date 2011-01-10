from __future__ import division


from HistGetter import *
from tdrStyle import *
from ROOT import *
from math import pow, exp

class QCDEstimator:
    luminosity = 36.145#pb-1
    mc_luminosity = 36.145#pb-1
    scale = luminosity/mc_luminosity
    jetBins = ['0jet', 'allJets', '1jet', '1orMoreJets', '2jets', '2orMoreJets', '3jets', '3orMoreJets', '4orMoreJets']
    rebin = 10
    
    def __init__( self, files ):
        self.files = files
        HistGetter.samplefiles = files
        self.histograms = {}
        self.histGetter = HistGetter()
        self.histGetter.setStyle()
        self.getHistograms()
        self.applyStyleAndCreateStack()

    def getHistograms( self ):
        relIsoHists = ['QCDest_CombRelIso_' + jetbin for jetbin in self.jetBins]
        pfIsoHists =  ['QCDest_PFIsolation_' + jetbin for jetbin in self.jetBins]
        allHists = relIsoHists
        allHists.extend(pfIsoHists)
        HistGetter.hists = allHists
        
        self.histograms = self.histGetter.getHistsFromFiles()
        self.histograms = self.histGetter.addSampleSum(self.histograms)
    
    def applyStyleAndCreateStack(self):
        samplesOfInterest = ['data', 'qcd', 'zjets', 'wjets', 'singleTop', 'ttbar']
        colors = {'ttbar' :  kRed + 1,
                  'wjets' :  kGreen - 3,
                  'zjets' :  kAzure - 2,
                  'qcd' :  kYellow,
                  'singleTop' :  kMagenta}
        
        mcStack = {}
        
        for sample in samplesOfInterest:#sample
            for histname in self.histograms[sample].keys():
                self.histograms[sample][histname].Rebin(self.rebin)
                if not sample == 'data':
                    self.histograms[sample][histname].Scale(self.scale)
                    self.histograms[sample][histname].SetFillStyle(1001)
                    self.histograms[sample][histname].SetFillColor(colors[sample])
                    if not mcStack.has_key(histname):
                        mcStack[histname] = THStack("MC_" + histname, "MC_" + histname);
                    mcStack[histname].Add(self.histograms[sample][histname])
                else:
                    self.histograms[sample][histname].SetMarkerStyle(8);
                
    
        self.histograms['MCStack'] = mcStack



if __name__ == '__main__':
    path = '/storage/workspace/BristolAnalysisTools/outputfiles/Fall10_NovRereco_PfIso/'
    files = {'data': path + "data_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'ttbar' :  path + "ttjet_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'wjets' :  path + "wj_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'zjets' :  path + "zj_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'bce1' :  path + "bce1_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'bce2' :  path + "bce2_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'bce3' :  path + "bce3_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'enri1' : path + "enri1_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'enri2' :  path + "enri2_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'enri3' :  path + "enri3_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'pj1' :  path + "pj1_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'pj2' :  path + "pj2_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'pj3' :  path + "pj3_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'tW' :  path + "tW_36.145pb_PFElectron_PF2PATJets_PFMET.root",
    'tchan' :  path + "tchan_36.145pb_PFElectron_PF2PATJets_PFMET.root"}
    q = QCDEstimator( files )
    print q.histograms
