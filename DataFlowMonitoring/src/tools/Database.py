'''
Created on 27 May 2010

@author: kreczko
'''
import sqlite3
import os

class Database:
    
    def __init__(self, database):
        if not os.path.exists(database):
            raise IOError('Could not find database')
        self.database = database
    
    def _queryDatabase(self, query):
        result = []
        try:
            connection = sqlite3.connect(self.database)
            connection.row_factory = sqlite3.Row
            cursor = connection.cursor()
            cursor.execute(query)
            result = cursor.fetchall()
            connection.commit()
            connection.close()
        except sqlite3.Error, e:
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
        return result
    
    def addUser(self, user):
        sqlCommand = 'INSERT INTO users(name, preferred_se_directory) VALUES ("%s", "%s")'
        sqlCommand = sqlCommand % (user.getName(), user.getPreferredStorageElementPath())
        self._queryDatabase(sqlCommand)
        
    def getListOfUsers(self):
        result = self._queryDatabase('SELECT * from users')
        return result
