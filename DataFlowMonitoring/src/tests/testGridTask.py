'''
Created on 2 Jun 2010

@author: kreczko
'''
import unittest
from tools.GridTask import GridTask

class TestGridTask(unittest.TestCase):
    
    def setUp(self):
        self.gridtask = GridTask()
        self.gridtask.NumberOfFailedJobs = 20
        self.gridtask.NumberOfPendingJobs = 20
        self.gridtask.NumberOfRunningJobs = 20
        self.gridtask.NumberOfSuccessfulJobs = 20
        self.gridtask.NumberOfTerminatedJobs = 20
        self.gridtask.NumberOfJobs = 100
        
    def testGetPercentageOfPendingOrRunningJobs(self):
        self.assertEquals(0.4, self.gridtask.getPercentageOfPendingOrRunningJobs())
        
    def testGetPercentageOfMissingOrFailedJobs(self):
        self.assertEquals(0.4, self.gridtask.getPercentageOfMissingOrFailedJobs())
        
    def testGetPercentageOfSuccessfulJobs(self):
        self.assertEquals(0.2, self.gridtask.getPercentageOfSuccessfulJobs())
        
