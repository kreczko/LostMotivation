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

Summer09Twikipage = Dataset.Summer09Twikipage
Spring10Twikipage = Dataset.Spring10Twikipage
LumiTwiki2010Data = Dataset.LumiTwiki2010Data

invalidDatasetName = 'this_dataset_does_not_exist'
datasetMC = Dataset.createDatasetFromUserInput(correctDatasetMC)
datasetMCSpring10 = Dataset.createDatasetFromUserInput(correctDatasetMCSpring10)
dataset = Dataset.createDatasetFromUserInput(realData)
invalidDataset = Dataset('')

validSQLResult = {'name': realData, 'twikiPage': LumiTwiki2010Data, 'isData':True}
invalidSQLResultNoTwiki = {'name': realData, 'twikiPage': '', 'isData':True}
invalidSQLResultNoDataflag = {'name': realData, 'twikiPage': LumiTwiki2010Data, 'isData':None}
validDBDataset = Dataset.createDatasetFromSQLResult(validSQLResult)
validDBDataset2 = Dataset.createDatasetFromSQLResult(validSQLResult)
invalidDBDatasetNoTwikiPage = Dataset.createDatasetFromSQLResult(invalidSQLResultNoTwiki)
invalidDBDatasetNoDataFlag = Dataset.createDatasetFromSQLResult(invalidSQLResultNoDataflag)

class TestDataset(unittest.TestCase):
        
    def testDatasetExists(self):
        self.assertFalse(Dataset.exists(invalidDatasetName))
        self.assertTrue(Dataset.exists(correctDatasetMC))
        
    def testSetDatasetInvalidDatasetRaisesException(self):
        self.failUnlessRaises(IOError, dataset.createDatasetFromUserInput, invalidDatasetName)
        
    def testIsDatasetRealDataOrSimulation(self):
        self.assertFalse(datasetMC.isData)
        self.assertTrue(dataset.isData)
        
    def testDatasetTwikiPage(self):
        self.assertEquals(Spring10Twikipage, datasetMCSpring10.TwikiPage)
        self.assertEquals(Summer09Twikipage, datasetMC.TwikiPage)
        self.assertEquals(LumiTwiki2010Data, dataset.TwikiPage)
    
    def testIsValdiDataset(self):
        self.assertTrue(dataset.isValid())
        self.assertTrue(datasetMC.isValid())
        self.assertFalse(invalidDataset.isValid())
        self.assertFalse(invalidDBDatasetNoTwikiPage.isValid())
        self.assertFalse(invalidDBDatasetNoDataFlag.isValid())
        
    def testCompare(self):
        self.assertEquals(validDBDataset, validDBDataset2)
        self.assertTrue(datasetMC > dataset)