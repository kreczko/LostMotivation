'''
Created on 2 Jun 2010

@author: kreczko
'''
import XMLParser

class GridJob(object):
    basicFileWildcard = '*_%d_%d.root'
    XMLObjectRoot = 'item'
    
    def __init__(self):
        self.Status = ''
        self.ID = 0
        self.NumberOfRetries = 0
        self.submissionDate = ''
        self.finishDate = ''
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
    
    def createFromXMLNode(node):
        idNode = XMLParser.getSubNode(node, 'EventRange')
        statusNode = XMLParser.getSubNode(node, 'STATUS')
        numberOfRetriesNode = XMLParser.getSubNode(node, 'resubmissions')
        submissionDateNode = XMLParser.getSubNode(node, 'submitted')
        finishDateNode = XMLParser.getSubNode(node, 'finished')
        startDateNode = XMLParser.getSubNode(node, 'started')
        
        gridjob = GridJob()
        gridjob.ID = int(XMLParser.getText(idNode))
        gridjob.NumberOfRetries = int(XMLParser.getText(numberOfRetriesNode))
        gridjob.Status = XMLParser.getText(statusNode)
        gridjob.submissionDate = XMLParser.getText(submissionDateNode)
        gridjob.finishDate = XMLParser.getText(finishDateNode)
        gridjob.startDate = XMLParser.getText(startDateNode)
        return gridjob
    createFromXMLNode = staticmethod(createFromXMLNode)
    
    def __eq__(self, other):
        return self.ID == other.ID
    
    def __cmp__(self, other):
        if self.ID > other.ID:
            return 1
        elif self.ID < other.ID:
            return -1
        else:
            return 0
