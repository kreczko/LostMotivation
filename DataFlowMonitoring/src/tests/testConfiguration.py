'''
Created on 1 Jun 2010

@author: kreczko
'''
import unittest
from tools.Configuration import Configuration
from tools.Dataset import Dataset
from tools.User import User

class TestConfiguration(unittest.TestCase):
    
    def setUp(self):
        self.datasetName = '/EG/Run2010A-PromptReco-v1/RECO'
        self.pathToBeCreated = 'EG_Run2010A-PromptReco-v1_RECO'
        
        self.validSQLResult = {'name': self.datasetName, 'twikiPage': Dataset.LumiTwiki2010Data, 'isData':True}
        self.validDBDataset = Dataset.createDatasetFromSQLResult(self.validSQLResult)
        
        self.validUser = User('Lukas Kreczko')
        self.validUser.setPreferredStorageElementPath('/store/user/kreczko/')
        self.configuration = Configuration.create(self.validDBDataset, self.validUser)
        
        self.validDashboardLink = 'http://dashb-cms-job-task.cern.ch/taskmon.html#task=kreczko_30May_dataEG_v2_6x7us4'
        self.invalidDashboardLink = 'www.google.com'
        self.invalidDashboardLink2 = 'http://www.google.com'
        
    def testCreateFilePath(self):
        self.assertEquals(self.pathToBeCreated, Configuration.createPathFromDatasetName(self.datasetName))
        
    def testCreate(self):
        self.assertEquals(self.validUser, self.configuration.user)
        self.assertEquals(self.validDBDataset, self.configuration.dataset)
        self.assertEquals(self.validUser.getPreferredStorageElementPath() + self.pathToBeCreated, self.configuration.storagePath)
        
    def testIsValidDashboardLink(self):
        self.assertTrue(Configuration.isValidDashboardLink(self.validDashboardLink))
        self.assertFalse(Configuration.isValidDashboardLink(self.invalidDashboardLink))
        self.assertFalse(Configuration.isValidDashboardLink(self.invalidDashboardLink2))
        
    def testSetDashboardLink(self):
        self.configuration.setDashboardLink(self.validDashboardLink)
        self.assertEquals(self.validDashboardLink, self.configuration.getDashboardLink())
        self.assertTrue(self.configuration.getSubmissionTime() > 0)
        
    def testInvalidDashboardLinkRaisesException(self):
        self.failUnlessRaises(ValueError, self.configuration.setDashboardLink, self.invalidDashboardLink)
        
    def testIsSubmitted(self):
        self.assertFalse(self.configuration.isSubmitted())
        self.configuration.setDashboardLink(self.validDashboardLink)
        self.assertTrue(self.configuration.isSubmitted())
        
        