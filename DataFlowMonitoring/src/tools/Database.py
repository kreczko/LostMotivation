'''
Created on 27 May 2010

@author: kreczko
'''
from sqlite3 import dbapi2 as sqlite
from sqlite3 import Error
import os

class Result:
    def __init__(self):
        self.innerResult = []
    
    def setQueryResult(self, sqlResult):
        self.sqlResult = sqlResult
        self.__createInnerResult()
        
    def __createInnerResult(self):
        if len(self.sqlResult) > 0:
            keys = self.sqlResult[-1]
        for row in range(len(self.sqlResult) - 1):
            result = {}
            row = self.sqlResult[row]
            for item in range(len(row)):
                value = row[item]
                key = keys[item]
                result[key] = value
            self.innerResult.append(result)
                
    def get(self):
        return self.innerResult
       
    def __str__(self):
        return self.innerResult.__str__()
    
    def __len__(self):
        return len(self.innerResult)
    
    def __getitem__(self, i):
        return self.innerResult[i]

class Database:
#    _currentDirectory = os.path.dirname(__file__)
#    _applicationDirectory = _currentDirectory.rstrip(os.path.basename(_currentDirectory))
#    database = _applicationDirectory + 'db/dfm_alpha.db'
    
    def __init__(self, database):
        if not os.path.exists(database):
            raise IOError('Could not find database')
        self.database = database
        
    def _queryDatabase(self, query):
        result = Result()
        try:
            connection = sqlite.connect(self.database)
            cursor = connection.cursor()
            cursor.execute(query)
            result.setQueryResult(cursor.fetchall())
            connection.commit()
            connection.close()
        except Error, e:
            print 'An error occurred:', e.args[0]
        return result
    
    def createTables(self):
        self._createDatasetTable()
        self._createConfigurationsTable()
        self._createUsersTable()
        self._createCopyjobsTable()
        self._createGridjobsTable()
        self._createValidationjobsTable()
    
    def _createDatasetTable(self):
        sqlCommand = 'CREATE TABLE "datasets" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "name" TEXT NOT NULL,' 
        sqlCommand += '"twikiPage" TEXT, "JSONFILE" TEXT, "isData" TEXT NOT NULL)'
        self._queryDatabase(sqlCommand)
        
    def _createConfigurationsTable(self):
        sqlCommand = 'CREATE TABLE "configurations" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'
        sqlCommand += '"dataset_id" INTEGER NOT NULL, "se_directory" TEXT NOT NULL, "submission_date" REAL,'
        sqlCommand += '"owner_id" INTEGER,"dashboard_link" TEXT)'
        self._queryDatabase(sqlCommand)
        
    def _createUsersTable(self):
        sqlCommand = 'CREATE TABLE "users" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'
        sqlCommand += '"name" TEXT NOT NULL,"preferred_se_directory" TEXT)'
        self._queryDatabase(sqlCommand)
      
    def _createCopyjobsTable(self):
        sqlCommand = 'CREATE TABLE "copyjobs" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'
        sqlCommand += '"config_id" INTEGER NOT NULL,"location" TEXT NOT NULL,"destination" TEXT NOT NULL,'
        sqlCommand += '"file" TEXT NOT NULL,"duration" INTEGER)'
        self._queryDatabase(sqlCommand)
        
    def _createGridjobsTable(self):
        sqlCommand = 'CREATE TABLE "gridjobs" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'
        sqlCommand += '"config_id" INTEGER NOT NULL, "job_id" INTEGER NOT NULL, "status" TEXT NOT NULL)'
        self._queryDatabase(sqlCommand)
        
    def _createValidationjobsTable(self):
        sqlCommand = 'CREATE TABLE "validationjobs" ("id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'
        sqlCommand += '"config_id" INTEGER NOT NULL, "copyjob_id" INTEGER NOT NULL,"output_rootfile" TEXT,'
        sqlCommand += '"isSourceFileValid" INTEGER,"logfile" TEXT, "plot_url" TEXT)'
        self._queryDatabase(sqlCommand)
          
    def getListOfTables(self):
        result = self._queryDatabase("SELECT * FROM sqlite_master WHERE type='table'")
        return result.get()
