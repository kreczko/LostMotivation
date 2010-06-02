'''
Created on 29 May 2010

@author: kreczko
'''

class Configuration(object):
    dashboardLinkStartsWith = 'http://dashb-cms-job-task.cern.ch'
    
    def __init__(self):
        self.user = None
        self.dataset = None
        self.storagePath = ''
        self.__submissionTime = 0
        self.__dashboardLink = ''
    
    def createPathFromDatasetName(datasetName):
        path = datasetName.lstrip('/')
        path = path.replace('/', '_')
        return path
    createPathFromDatasetName = staticmethod(createPathFromDatasetName)
    
    def create(dataset, user):
        config = Configuration()
        config.user = user
        config.dataset = dataset
        config.storagePath = user.getPreferredStorageElementPath() + Configuration.createPathFromDatasetName(dataset.Name)
        return config
    create = staticmethod(create)
    
    def getSubmissionTime(self):
        return self.__submissionTime
    
    def getDashboardLink(self):
        return self.__dashboardLink
    
    def setDashboardLink(self, link):
        pass
    

        