'''
Created on 2 Jun 2010

@author: kreczko

Email: kreczko@cern.ch
'''
import unittest
from tools.GridJob import GridJob

class TestGridJob(unittest.TestCase):
    def setUp(self):
        self.gridjob = GridJob()
        self.gridjob.ID = 33
        self.gridjob.NumberOfRetries = 4
        self.expectedWildcard = '*_33_4.root'
        
    def testStatusSuccess(self):
        self.assertFalse(self.gridjob.isSuccessful())
        self.gridjob.Status = 'S'
        self.assertTrue(self.gridjob.isSuccessful())
    
    def testStatusFailed(self):
        self.assertFalse(self.gridjob.isFailed())
        self.gridjob.Status = 'F'
        self.assertTrue(self.gridjob.isFailed())
        
    def testStatusPending(self):
        self.assertFalse(self.gridjob.isPending())
        self.gridjob.Status = 'P'
        self.assertTrue(self.gridjob.isPending())
        
    def testStatusRunning(self):
        self.assertFalse(self.gridjob.isRunning())
        self.gridjob.Status = 'R'
        self.assertTrue(self.gridjob.isRunning())
        
    def testStatusUnknown(self):
        self.assertFalse(self.gridjob.hasUnknownStatus())
        self.gridjob.Status = 'U'
        self.assertTrue(self.gridjob.hasUnknownStatus())
        
    def testGetFileWildcard(self):
        self.assertEquals(self.expectedWildcard, self.gridjob.getFileWildcard())
        