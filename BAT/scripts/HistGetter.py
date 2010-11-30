from ROOT import *
from math import fsum
class HistGetter:

    hists = []
    samples = []
    files = []
    sampleIdentifiers = []
    samplefiles = {}
    
    def getHists(self):
        if(len(self.files) == 1):
            return self.getHistsFromSingleFile()
        elif(len(self.files) > 1):
            return self.getHistsFromFiles()
        else:
            raise "No files specified"
        
    def getHistsfromSingleFile(self):
        print
        
    def getHistsFromFiles(self):
        tfiles = []
        TFileOpen = TFile.Open
#        [tfiles.append(TFileOpen(x)) for x in self.samplefiles.values()]
        
        allHists = {}
        for sample, file in self.samplefiles.iteritems():
#            print file, sample
            file = TFileOpen(file)
            allHists[sample] = []
            fg = file.Get
            gROOT.cd()
            for hist in self.hists:
                allHists[sample].append(fg(hist).Clone())
        return allHists
    
    def addSampleSum(self, hists = {}):
        qcdList = []
        mc_all_list = []
        singleTopList = []
        
        for x in hists.values():
            qcdList.append(None)
            mc_all_list.append(None)
            singleTopList.append(None)
        
        qcdSamples = ['bce1', 'bce2', 'bce3', 'enri1', 'enri2','enri3', 'pj1', 'pj2', 'pj3']
        allMCSamples = ['ttbar', 'wjets', 'zjets','tW', 'tchan', 'bce1', 'bce2', 'bce3', 'enri1', 
                        'enri2','enri3', 'pj1', 'pj2', 'pj3']
        singleTopSamples = ['tW', 'tchan']
        
        
        for sample, histlist in hists.iteritems():
            for x in range(0, len(histlist)):
                hist = histlist[x]
                if sample in qcdSamples:
                    if qcdList[x] is None:
                        qcdList[x] = hist.Clone('qcd')
                    else:
                        qcdList[x].Add(hist)
                        
                if sample in allMCSamples:
                    if mc_all_list[x] is None:
                        mc_all_list[x] = hist.Clone('all_mc')
                    else:
                        mc_all_list[x].Add(hist)
                        
                if sample in singleTopSamples:
                    if singleTopList[x] is None:
                        singleTopList[x] = hist.Clone('singleTop')
                    else:
                        singleTopList[x].Add(hist)
                    
        hists['qcd'] = qcdList
        hists['allMC'] = mc_all_list
        hists['singleTop'] = singleTopList
        
        return hists
    
    def addJetSum(self, hists):
        return 0
        
                
if __name__ == "__main__":
    HistGetter.hists = ['QCDest_CombRelIso_0jet', 'QCDest_CombRelIso_1jet', 'QCDest_CombRelIso_2jets', 
                        'QCDest_CombRelIso_3jets', 'QCDest_CombRelIso_4orMoreJets']
#    HistGetter.samples = ["data", "ttbar"]
#    HistGetter.files = ['/storage/workspace/BristolAnalysisTools/outputfiles/new/data_35pb_PFElectron_PF2PATJets_PFMET.root',
#                        '/storage/workspace/BristolAnalysisTools/outputfiles/new/ttjet_35pb_PFElectron_PF2PATJets_PFMET.root']
    files = {'data':"/storage/workspace/BristolAnalysisTools/outputfiles/new/data_35pb_PFElectron_PF2PATJets_PFMET.root",
    'ttbar' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/ttjet_35pb_PFElectron_PF2PATJets_PFMET.root",
    'wjets' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/wj_35pb_PFElectron_PF2PATJets_PFMET.root",
    'zjets' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/zj_35pb_PFElectron_PF2PATJets_PFMET.root",
#    'bce1' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/bce1_35pb.root",
    'bce2' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/bce2_35pb_PFElectron_PF2PATJets_PFMET.root",
    'bce3' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/bce3_35pb_PFElectron_PF2PATJets_PFMET.root",
    'enri1' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/enri1_35pb_PFElectron_PF2PATJets_PFMET.root",
    'enri2' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/enri2_35pb_PFElectron_PF2PATJets_PFMET.root",
    'enri3' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/enri3_35pb_PFElectron_PF2PATJets_PFMET.root",
    'pj1' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/pj1_35pb_PFElectron_PF2PATJets_PFMET.root",
    'pj2' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/pj2_35pb_PFElectron_PF2PATJets_PFMET.root",
    'pj3' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/pj3_35pb_PFElectron_PF2PATJets_PFMET.root"}
#    'tW' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/tW_35pb_PFElectron_PF2PATJets_PFMET.root",
#    'tchan' : "/storage/workspace/BristolAnalysisTools/outputfiles/new/tchan_35pb_PFElectron_PF2PATJets_PFMET.root"}
    HistGetter.samplefiles = files
    HG = HistGetter()
    hists = HG.getHistsFromFiles()
    hists = HG.addSampleSum(hists)
    qcdSamples = ['bce1', 'bce2', 'bce3', 'enri1', 'enri2','enri3', 'pj1', 'pj2', 'pj3']
    allMCSamples = ['ttbar', 'wjets', 'zjets','tW', 'tchan', 'bce1', 'bce2', 'bce3', 'enri1', 
                        'enri2','enri3', 'pj1', 'pj2', 'pj3']
    singleTopSamples = ['tW', 'tchan']
    
    nqcd = 0
    nstop = 0
    nmc = 0
    nqcd = fsum([hists[sample][0].Integral() for sample in qcdSamples if hists.has_key(sample)])
#    nstop = sum([hists[sample][0].Integral() for sample in singleTopSamples if hists.has_key(sample)])
    nmc = fsum([hists[sample][0].Integral() for sample in allMCSamples if hists.has_key(sample)])
    print hists['qcd'][0].Integral(), nqcd
#    print hists['singleTop'][0].Integral(), nstop
    print hists['allMC'][0].Integral(), nmc
        