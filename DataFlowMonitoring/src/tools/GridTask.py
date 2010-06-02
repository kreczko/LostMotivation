'''
Created on 2 Jun 2010

@author: kreczko
'''
from __future__ import division

class GridTask(object):


    def __init__(self):
        self.listOfGridJobs = []
        self.NumberOfTerminatedJobs = 0
        self.NumberOfSuccessfulJobs = 0
        self.NumberOfRunningJobs = 0
        self.NumberOfPendingJobs = 0
        self.NumberOfFailedJobs = 0
        self.MonitorID = ''
        self.NumberOfJobs = 0
        
    def getPercentageOfPendingOrRunningJobs(self):
        return (self.NumberOfRunningJobs + self.NumberOfPendingJobs) / self.NumberOfJobs
        
    def getPercentageOfMissingOrFailedJobs(self):
        return (self.NumberOfFailedJobs + self.NumberOfTerminatedJobs) / self.NumberOfJobs
    
    def getPercentageOfSuccessfulJobs(self):
        return self.NumberOfSuccessfulJobs / self.NumberOfJobs
