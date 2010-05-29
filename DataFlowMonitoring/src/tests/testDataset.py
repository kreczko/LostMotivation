'''
Created on 29 May 2010

@author: kreczko

Email: kreczko@cern.ch
'''
from tools.Dataset import Dataset
import unittest

correctDatasetMC = '/WJets-madgraph/Summer09-MC_31X_V3_7TeV-v3/GEN-SIM-RECO'
correctDatasetMCSpring10 = '/WJets-madgraph/Spring10-START3X_V26_S09-v1/GEN-SIM-RECO'
realData = '/EG/Run2010A-PromptReco-v1/RECO'
Summer09Twikipage = 'https://twiki.cern.ch/twiki/bin/view/CMS/ProductionSummer2009at7TeV'
Spring10Twikipage = 'https://twiki.cern.ch/twiki/bin/viewauth/CMS/ProductionReProcessingSpring10'
LumiTwiki2010Data = 'https://twiki.cern.ch/twiki/bin/view/CMS/LumiWiki2010Data'
falseDataset = 'this_dataset_does_not_exist'
datasetMC = Dataset(correctDatasetMC)
datasetMCSpring10 = Dataset(correctDatasetMCSpring10)
dataset = Dataset(realData)

class TestDataset(unittest.TestCase):
        
    def testDatasetExists(self):
        self.assertFalse(Dataset.exists(falseDataset))
        self.assertTrue(Dataset.exists(correctDatasetMC))
        
    def testConstructorInvalidDatasetRaisesException(self):
        self.failUnlessRaises(IOError, Dataset, falseDataset)
        
    def testIsDatasetRealDataOrSimulation(self):
        self.assertFalse(datasetMC.isData())
        self.assertTrue(dataset.isData())
        
    def testDatasetTwikiPage(self):
        self.assertEquals(Spring10Twikipage, datasetMCSpring10.TwikiPage())
        self.assertEquals(Summer09Twikipage, datasetMC.TwikiPage())
        self.assertEquals(LumiTwiki2010Data, dataset.TwikiPage())
        