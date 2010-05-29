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
    
    def __init__(self, name):
        if not Dataset.exists(name):
            raise IOError
        self.__name = name
        self.__isData = self.__getDataType() == 'data'
        self.__selectTwikiPage()
    
    def __getDataType(self):
        searchstring = "find datatype where dataset =" + self.__name
        return Dataset.search(searchstring)[0]
    
    def __selectTwikiPage(self):
        if 'Summer09' in self.__name:
            self.__twikipage = Dataset.Summer09Twikipage
        elif 'Spring10' in self.__name:
            self.__twikipage = Dataset.Spring10Twikipage
        else:
            self.__twikipage = Dataset.LumiTwiki2010Data 
    
    def isData(self):
        return self.__isData
    
    def TwikiPage(self):
        return self.__twikipage
    
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
