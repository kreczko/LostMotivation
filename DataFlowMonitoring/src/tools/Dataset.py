'''
Created on 29 May 2010

@author: kreczko

Email: kreczko@cern.ch
'''
import urllib
import urllib2

class Dataset(object):
    searchURL = "http://cmsweb.cern.ch/dbs_discovery/aSearch?"
    Summer09Twikipage = 'https://twiki.cern.ch/twiki/bin/view/CMS/ProductionSummer2009at7TeV'
    Spring10Twikipage = 'https://twiki.cern.ch/twiki/bin/viewauth/CMS/ProductionReProcessingSpring10'
    LumiTwiki2010Data = 'https://twiki.cern.ch/twiki/bin/view/CMS/LumiWiki2010Data'
    validTwikis = [Summer09Twikipage, Spring10Twikipage, LumiTwiki2010Data]
    
    def __init__(self, name):
        self.Name = name
        self.isData = None
        self.TwikiPage = None
        
    def __getDataType(self):
        searchstring = "find datatype where dataset =" + self.Name
        return Dataset.search(searchstring)[0]
    
    def __selectTwikiPage(self):
        if 'Summer09' in self.Name:
            self.TwikiPage = Dataset.Summer09Twikipage
        elif 'Spring10' in self.Name:
            self.TwikiPage = Dataset.Spring10Twikipage
        else:
            self.TwikiPage = Dataset.LumiTwiki2010Data 
    
    def setTwikiPage(self, twikipage):
        self.__twikipage = twikipage
        
    def exists(datasetName):
        return len(Dataset.search(datasetName)) == 1
    exists = staticmethod(exists)
    
    def search(searchstring):
        searchstring = searchstring.strip()
        searchParameters = Dataset.createSearchParameters(searchstring)
        urlParameterString = urllib.unquote(urllib.urlencode(searchParameters))
        response = urllib2.urlopen(Dataset.searchURL + urlParameterString)
        result = response.read()
        if 'Exception' in result:
            return []
        else:
            datasetlist = result.strip().split('\n')
            return datasetlist[1:]
    search = staticmethod(search)
    
    def createSearchParameters(searchstring):
        parameters = {}
        parameters["userInput"] = searchstring
        parameters["dbsInst"] = "cms_dbs_prod_global"
        parameters["caseSensitive"] = "off"
        parameters["method"] = "dbsapi"
        parameters["html"] = "0"
        parameters["userMode"] = "user"
        parameters["details"] = "0"
        parameters["sortOrder"] = "asc"
        
        return parameters
    createSearchParameters = staticmethod(createSearchParameters)
    
    def isValid(self):
        return Dataset.exists(self.Name) and Dataset.isValidDataflag(self.isData) and Dataset.isValidTwikipage(self.TwikiPage)
    
    def isValidDataflag(dataflag):
        return type(dataflag) is bool
    isValidDataflag = staticmethod(isValidDataflag)
    
    def isValidTwikipage(twikiPage):
        return twikiPage in Dataset.validTwikis
    isValidTwikipage = staticmethod(isValidTwikipage)
    
    def retrieveProperties(self):
        if Dataset.exists(self.Name):
            self.isData = self.__getDataType() == 'data'
            self.__selectTwikiPage()
        else:
            raise IOError('Dataset "%s" does not exist!' % self.Name)
        
    def createDatasetFromSQLResult(result):
        dataset = Dataset(result['name'])
        dataset.TwikiPage = result['twikiPage']
        if not result['isData'] is None:
            dataset.isData = bool(result['isData'])
        return dataset
    createDatasetFromSQLResult = staticmethod(createDatasetFromSQLResult)
    
    def createDatasetFromUserInput(datasetName):
        dataset = Dataset(datasetName)
        dataset.retrieveProperties()
        return dataset
    createDatasetFromUserInput = staticmethod(createDatasetFromUserInput)
    
    def __cmp__(self, other):
        if self.Name > other.Name:
            return 1
        elif self.Name < other.Name:
            return -1
        else:
            return 0
        
    def __eq__(self, other):
        return self.Name == other.Name and self.TwikiPage == other.TwikiPage and self.isData == other.isData
