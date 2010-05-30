'''
Created on 27 May 2010

@author: kreczko
'''

import unittest
from tools.Database import Database
from tools.DummyDatabase import DummyDatabase
from tools.User import User
from tools.Dataset import Dataset

class TestDatabase(unittest.TestCase):
    
    def setUp(self):
        self.db = DummyDatabase('test.db')
        self.username = 'Lukasz Kreczko'
        self.user = User('Lukasz Kreczko')
        self.user.setPreferredStorageElementPath('/store/user/kreczko/')
        self.invalidUser = User(self.username)
        
        
        self.realData = '/EG/Run2010A-PromptReco-v1/RECO'
        self.validSQLResult = {'name': self.realData, 'twikiPage': Dataset.LumiTwiki2010Data, 'isData':True}
        self.invalidSQLResultNoDataflag = {'name': self.realData, 'twikiPage': Dataset.LumiTwiki2010Data, 'isData':None}
        
        self.validDBDataset = Dataset.createDatasetFromSQLResult(self.validSQLResult)
        self.invalidDBDatasetNoDataFlag = Dataset.createDatasetFromSQLResult(self.invalidSQLResultNoDataflag)
        
    def getNameOfFirstTable(self, listOfTables):
        return listOfTables[0]['name']
    
    def testConstructorInvalidFileRaisesException(self):
        self.failUnlessRaises(IOError, Database, 'this_file_does_not_exist')
    
    def testCreateDataSetTable(self):
        self.db.createDatasetTable()
        listOfTables = self.db.getListOfTables()
        self.assertEquals(1+1, len(listOfTables))
        self.assertEquals('datasets', self.getNameOfFirstTable(listOfTables))
        
    def testCreateConfigurationTable(self):
        self.db.createConfigurationTable()
        listOfTables = self.db.getListOfTables()
        self.assertEquals(1+1, len(listOfTables))
        self.assertEquals('configurations', self.getNameOfFirstTable(listOfTables))
    
    def testCreateUsersTable(self):
        self.db.createUsersTable()
        listOfTables = self.db.getListOfTables()
        self.assertEquals(1+1, len(listOfTables))
        self.assertEquals('users', self.getNameOfFirstTable(listOfTables))
        
    def testCreateCopyjobsTable(self):
        self.db.createCopyjobsTable()
        listOfTables = self.db.getListOfTables()
        self.assertEquals(1+1, len(listOfTables))
        self.assertEquals('copyjobs', self.getNameOfFirstTable(listOfTables)) 
        
    def testCreateGridjobsTable(self):
        self.db.createGridjobsTable()
        listOfTables = self.db.getListOfTables()
        self.assertEquals(1+1, len(listOfTables))
        self.assertEquals('gridjobs', self.getNameOfFirstTable(listOfTables)) 
        
    def testCreateValidationjobsTable(self):
        self.db.createValidationjobsTable()
        listOfTables = self.db.getListOfTables()
        self.assertEquals(1+1, len(listOfTables))
        self.assertEquals('validationjobs', self.getNameOfFirstTable(listOfTables))
        
    def testNumberOfCreatedTables(self):
        self.db.createTables() 
        listOfTables = self.db.getListOfTables()
        self.assertEquals(6+1, len(listOfTables))
        
    def testAddUser(self):
        self.db.createUsersTable()
        self.db.addUser(self.user)
        self.assertEquals(1,len(self.db.getListOfUsers()))
    
    def testNoAddInvalidUser(self):
        self.db.createUsersTable()
        self.db.addUser(self.invalidUser)
        self.assertEquals(0,len(self.db.getListOfUsers()))
        
    def testGetUser(self):
        self.db.createUsersTable()
        self.db.addUser(self.user)
        user = self.db.getUser(self.username)
        self.assertEquals(self.username, user.getName())
        
    def testGetNotAvailableUser(self):
        self.db.createUsersTable()
        self.db.addUser(self.user)
        user = self.db.getUser('not known')
        self.assertFalse(user.isValid())
    
    def testAddDataset(self):
        self.db.createDatasetTable()
        self.db.addDataset(self.validDBDataset)
        self.assertEquals(1, len(self.db.getListOfDatasets()))
        
    def testNoAddInvalidDataset(self):
        self.db.createDatasetTable()
        self.db.addDataset(self.invalidDBDatasetNoDataFlag)
        self.assertEquals(0, len(self.db.getListOfDatasets()))
        
    def testGetDataset(self):
        self.db.createDatasetTable()
        self.db.addDataset(self.validDBDataset)
        self.dataset = self.db.getDataset(self.validDBDataset.Name)
        self.assertEquals(self.validDBDataset,self.dataset)
        
        
