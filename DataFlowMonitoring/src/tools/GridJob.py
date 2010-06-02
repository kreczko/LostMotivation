'''
Created on 2 Jun 2010

@author: kreczko
'''

class GridJob(object):
    basicFileWildcard = '*_%d_%d.root'
    def __init__(self):
        self.Status = ''
        self.ID = 0
        self.NumberOfRetries = 0
        self.submittedDate = ''
        self.finishedDate = ''
        self.startDate = ''
        
    def isSuccessful(self):
        return self.Status == 'S'
    
    def isFailed(self):
        return self.Status == 'F'
    
    def isPending(self):
        return self.Status == 'P'
    
    def isRunning(self):
        return self.Status == 'R'
    
    def hasUnknownStatus(self):
        return self.Status == 'U'
    
    def getFileWildcard(self):
        return GridJob.basicFileWildcard % (self.ID, self.NumberOfRetries)
