from ROOT import *
from math import fsum
from tdrStyle import *

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
            allHists[sample] = {}
            fg = file.Get
            gROOT.cd()
            for hist in self.hists:
                allHists[sample][hist] = fg(hist).Clone()
        return allHists
    
    def addSampleSum(self, hists = {}):
        qcdList = {}
        mc_all_list = {}
        singleTopList = {}
        
#        for x in hists.values():
#            qcdList.append(None)
#            mc_all_list.append(None)
#            singleTopList.append(None)
        
        qcdSamples = ['bce1', 'bce2', 'bce3', 'enri1', 'enri2','enri3', 'pj1', 'pj2', 'pj3']
        allMCSamples = ['ttbar', 'wjets', 'zjets','tW', 'tchan', 'bce1', 'bce2', 'bce3', 'enri1', 
                        'enri2','enri3', 'pj1', 'pj2', 'pj3']
        singleTopSamples = ['tW', 'tchan']
        
        
        for sample, histlist in hists.iteritems():
            for histname,hist in histlist.iteritems():
                if sample in qcdSamples:
                    if not qcdList.has_key(histname):
                        qcdList[histname] = hist.Clone('qcd')
                    else:
                        qcdList[histname].Add(hist)
                        
                if sample in allMCSamples:
                    if not mc_all_list.has_key(histname):
                        mc_all_list[histname] = hist.Clone('all_mc')
                    else:
                        mc_all_list[histname].Add(hist)
                        
                if sample in singleTopSamples:
                    if not singleTopList.has_key(histname):
                        singleTopList[histname] = hist.Clone('singleTop')
                    else:
                        singleTopList[histname].Add(hist)
                    
        hists['qcd'] = qcdList
        hists['allMC'] = mc_all_list
        hists['singleTop'] = singleTopList
        
        return hists
    
    def addJetSum(self, hists):
        allhists = ['QCDest_CombRelIso_0jet', 'QCDest_CombRelIso_1jet', 'QCDest_CombRelIso_2jets', 
                        'QCDest_CombRelIso_3jets', 'QCDest_CombRelIso_4orMoreJets']
        oneOrMore = ['QCDest_CombRelIso_1jet', 'QCDest_CombRelIso_2jets', 
                        'QCDest_CombRelIso_3jets', 'QCDest_CombRelIso_4orMoreJets']
        twoOrMore = ['QCDest_CombRelIso_2jets', 
                        'QCDest_CombRelIso_3jets', 'QCDest_CombRelIso_4orMoreJets']
        threeOrMore = ['QCDest_CombRelIso_3jets', 'QCDest_CombRelIso_4orMoreJets']
        for sample, histlist in hists.iteritems():
            print sample, hists[sample].keys()
            if(len(hists[sample].keys()) == 0):
                continue
            hists[sample]['QCDest_CombRelIso_0orMoreJets'] = self.addUpHistograms(hists[sample], allhists)
            hists[sample]['QCDest_CombRelIso_1orMoreJets'] = self.addUpHistograms(hists[sample], oneOrMore)
            hists[sample]['QCDest_CombRelIso_2orMoreJets'] = self.addUpHistograms(hists[sample], twoOrMore)
            hists[sample]['QCDest_CombRelIso_3orMoreJets'] = self.addUpHistograms(hists[sample], threeOrMore)
        return hists
    
    def addUpHistograms(self, dictOfHists, histsToAdd):
        hist = dictOfHists[histsToAdd[0]].Clone()
        hadd = hist.Add
        [hadd(h) for name, h in dictOfHists.iteritems() if name in histsToAdd[1:]]
        return hist
        
        
    def setStyle(self):
        tdrStyle = setTDRStyle();

        #slight adaptation
        tdrStyle.SetPadRightMargin(0.05); #originally was 0.02, too narrow!
        tdrStyle.SetStatH(0.2);
        #tdrStyle.SetOptStat(1110);//off title
        tdrStyle.SetOptStat(0);#off title
        tdrStyle.SetOptFit(0);#off title
        tdrStyle.cd();
        gROOT.ForceStyle();
        
        
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
    HG.setStyle()
    hists = HG.getHistsFromFiles()
    hists = HG.addSampleSum(hists)
    hists = HG.addJetSum(hists)
    qcdSamples = ['bce1', 'bce2', 'bce3', 'enri1', 'enri2','enri3', 'pj1', 'pj2', 'pj3']
    allMCSamples = ['ttbar', 'wjets', 'zjets','tW', 'tchan', 'bce1', 'bce2', 'bce3', 'enri1', 
                        'enri2','enri3', 'pj1', 'pj2', 'pj3']
    singleTopSamples = ['tW', 'tchan']
    
    nqcd = 0
    nstop = 0
    nmc = 0
    nqcd = fsum([hists[sample]['QCDest_CombRelIso_0jet'].Integral() for sample in qcdSamples if hists.has_key(sample)])
#    nstop = sum([hists[sample][0].Integral() for sample in singleTopSamples if hists.has_key(sample)])
    nmc = fsum([hists[sample]['QCDest_CombRelIso_0jet'].Integral() for sample in allMCSamples if hists.has_key(sample)])
    print hists['qcd']['QCDest_CombRelIso_0jet'].Integral(), nqcd
#    print hists['singleTop'][0].Integral(), nstop
    print hists['allMC']['QCDest_CombRelIso_0jet'].Integral(), nmc
    print
    print hists['allMC']['QCDest_CombRelIso_0orMoreJets'].Integral(), hists['allMC']['QCDest_CombRelIso_0jet'].Integral()
    print hists['allMC']['QCDest_CombRelIso_1orMoreJets'].Integral(), hists['allMC']['QCDest_CombRelIso_1jet'].Integral()
    print hists['allMC']['QCDest_CombRelIso_2orMoreJets'].Integral(), hists['allMC']['QCDest_CombRelIso_2jets'].Integral()
    print hists['allMC']['QCDest_CombRelIso_3orMoreJets'].Integral(), hists['allMC']['QCDest_CombRelIso_3jets'].Integral()
    print hists['allMC']['QCDest_CombRelIso_4orMoreJets'].Integral()
    print hists['allMC'].keys()
    c = []
    for histname, hist in hists['allMC'].iteritems():
        c.append(TCanvas("cname" + histname, histname, 800, 600))
        c[-1].cd()
        hist.Draw()
        
    a = raw_input()
        