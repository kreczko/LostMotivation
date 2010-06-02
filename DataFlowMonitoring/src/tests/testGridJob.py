'''
Created on 2 Jun 2010

@author: kreczko

Email: kreczko@cern.ch
'''
import unittest
from tools.GridJob import GridJob
from xml.dom.minidom import parseString
class TestGridJob(unittest.TestCase):
    def setUp(self):
        self.gridjob = GridJob()
        self.gridjob.ID = 2
        self.gridjob.NumberOfRetries = 4
        self.expectedWildcard = '*_2_4.root'
        self.XMLNodeString = """<item>
            <STATUS>S</STATUS>
            <resubmissions>4</resubmissions>
            <EventRange>2</EventRange>
            <started>2010-06-02 12:05:06</started>
            <GridEndId>D</GridEndId>
            <AppGenericStatusReasonValue>Application finished properly
            </AppGenericStatusReasonValue>
            <finished>2010-06-02 13:48:21</finished>
            <submitted>2010-06-02 11:52:03</submitted>
            <Site>hep.ph.ic.ac.uk</Site>
            <TaskJobId>164721888</TaskJobId>
            <JobExecExitCode>0</JobExecExitCode>
            <SchedulerJobId>https://lb006.cnaf.infn.it:9000/MHgePlRGyLKD_L9q79qcRA
            </SchedulerJobId>
            <GridEndReason>Job terminated successfully</GridEndReason>
        </item>"""
        self.XMLNode = parseString(self.XMLNodeString)
        self.XMLgridjob = GridJob.createFromXMLNode(self.XMLNode)
        
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
        
    def testCreateFromXMLNodeStatus(self):
        self.assertTrue(self.XMLgridjob.isSuccessful())
        
    def testCreateFromXMLNodeNumberOfRetries(self):
        self.assertEquals(4, self.XMLgridjob.NumberOfRetries)
        
    def testCreateFromXMLNodeJobID(self):
        self.assertEquals(2, self.XMLgridjob.ID)
        
    def testCreateFromXMLNodeStartDate(self):
        self.assertEquals('2010-06-02 12:05:06', self.XMLgridjob.startDate)
        
    def testCreateFromXMLNodeFinishDate(self):
        self.assertEquals('2010-06-02 13:48:21', self.XMLgridjob.finishDate)
        
    def testCreateFromXMLNodeSubmissionDate(self):
        self.assertEquals('2010-06-02 11:52:03', self.XMLgridjob.submissionDate)
        
    def testEquals(self):
        self.assertEquals(self.gridjob, self.XMLgridjob)
    
    def testCompare(self):
        self.gridjob.ID = 44
        self.assertTrue(self.gridjob > self.XMLgridjob)
        self.assertTrue(self.XMLgridjob, self.gridjob)