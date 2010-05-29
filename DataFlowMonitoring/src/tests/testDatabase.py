'''
Created on 27 May 2010

@author: kreczko
'''

import unittest
from tools.Database import Database
from tools.DummyDatabase import DummyDatabase
from tools.User import User

class TestDatabase(unittest.TestCase):
    
    def setUp(self):
        self.db = DummyDatabase('test.db')
        self.user = User('Lukasz Kreczko')
        self.user.setPreferredStorageElementPath('/store/user/kreczko/')
        
    def getNameOfFirstTable(self, listOfTables):
        return listOfTables[0]['name']
    
    def testConstructorInvalidFileRaisesException(self):
        self.failUnlessRaises(IOError, Database, 'this_file_does_not_exist')
    
    def testCreateDataSetTable(self):
        self.db.createDatabaseTable()
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
        
    def testSetUser(self):
        self.db.createUsersTable()
        self.db.addUser(self.user)
        self.assertEquals(1,len(self.db.getListOfUsers()))
        
