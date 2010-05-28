'''
Created on 27 May 2010

@author: kreczko
'''

from Database import Database
import os

class DummyDatabase(Database):
    dummyDB = 'test.db'
    
    def __init__(self, database):
        database = open(self.dummyDB, 'w')
        database.close()
        Database.__init__(self, self.dummyDB)
    
    def createDatabaseTable(self):
        self._createDatasetTable()
        
    def createConfigurationTable(self):
        self._createConfigurationsTable()
    
    def createUsersTable(self):
        self._createUsersTable()
        
    def createCopyjobsTable(self):
        self._createCopyjobsTable()
        
    def createGridjobsTable(self):
        self._createGridjobsTable()
        
    def createValidationjobsTable(self):
        self._createValidationjobsTable()
        
    def fillData(self):
        pass
    
    def __del__(self):
        if os.path.exists(self.dummyDB):
            os.remove(self.dummyDB)
        
        
        
if __name__ == '__main__':
    db = DummyDatabase()
    print os.path.exists(DummyDatabase.dummyDB)
    del db
    print os.path.exists(DummyDatabase.dummyDB)
    
    
        