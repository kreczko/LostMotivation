from ROOT import *

class HistGetter:

    hists = []
    samples = []
    files = []
    sampleIdentifiers = []
    
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
        [tfiles.append(TFileOpen(x)) for x in self.files]
        gROOT.cd()
        allHists = {}
        for file, sample in zip(tfiles, self.samples):
            allHists[sample] = []
            fg = file.Get
            for hist in self.hists:
                allHists[sample].append(fg(hist).Clone())
        return allHists
                
if __name__ == "__main__":
    HistGetter.hists = ['QCDest_CombRelIso_0jet', 'QCDest_CombRelIso_1jet']
    HistGetter.samples = ["data", "ttbar"]
    HistGetter.files = ['/storage/workspace/BristolAnalysisTools/outputfiles/backup/data_26.5pb_PFElectron_PF2PATJets_PFMET.root',
                        '/storage/workspace/BristolAnalysisTools/outputfiles/backup/ttjet_19pb_PFElectron_PF2PATJets_PFMET.root']
    
    HG = HistGetter()
    hists = HG.getHistsFromFiles()
    print hists
        