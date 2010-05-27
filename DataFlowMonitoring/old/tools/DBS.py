'''
Created on Nov 6, 2009

@author: lkreczko
'''
#!/usr/bin/env python

import urllib, urllib2

base_files = "http://cmsweb.cern.ch/dbs_discovery/getLFNsForSite?"
base_dataset = "http://cmsweb.cern.ch/dbs_discovery/aSearch?"

def getDataset(searchstring, **kwargs):
        searchstring = searchstring.strip()
#        print "Looking for datasets matching %s" % (searchstring)
#TODO: change to find more than 10 results.
        opt = {
            "dbsInst":"cms_dbs_prod_global",
            "caseSensitive":"off",
            "method":"dbsapi",
            "html":"0",
            "userInput":searchstring,
            "userMode":"user",
            "details":"0",
            "sortOrder":"asc"
#            "pagerStep":"-1",
#            "cff":"1"
            }
        for key, value in kwargs.iteritems():
            opt[key] = value

        optstring = urllib.unquote(urllib.urlencode(opt))

        response = urllib2.urlopen(base_dataset + optstring)
        res = response.read()
        err = False
        if 'Exception' in res:
            err = True
            return {'error' : err, 'result': res}
        else:
            datasetlist = res.strip().split('\n')
            return {'error' : err, 'result': datasetlist[1:]}

def auto(searchstring):
        results = getDataset(searchstring)
        if len(results) == 1:
            print "Search found one matching dataset, %s" % (results[0])
            return getFiles(results[0])
        elif len(results) == 0:
            print "Search returned no matching dataset."
            return None
        else:
            print "Search returned multiple results"
            for i, r in enumerate(results):
                print "[%s] %s" % (i, r)
            user = ""
            while not (user.isdigit() and int(user) < len(results)):
                user = raw_input(">")
            filelist = getFiles(results[int(user)])
            return filelist
                
def getFiles(dataset, **kwargs):
        dataset = dataset.strip()
        print "Getting file list for dataset %s" % (dataset)
        opt = {
            "dbsInst":"cms_dbs_prod_global",
            "site":"None",
            "datasetPath":dataset,
            "what":"txt"
            }
        for key, value in kwargs.iteritems():
            opt[key] = value

        optstring = urllib.unquote(urllib.urlencode(opt))
        response = urllib2.urlopen(base_files + optstring)
        filelist = response.read().strip().split('\n')
        return filelist

    #__call__ = staticmethod(__call__)
    #getFiles = staticmethod(getFiles)
    #getDataset = staticmethod(getDataset)
def getType(dataset):
    #dataset=/MinBias/Summer09-MC_3XY_V9B_900GeV-v2/GEN-SIM-RAW&_idx=0&ajax=0&userMode=user
    searchstring = "find datatype where dataset = %s" %dataset
    opt = {
            "dbsInst":"cms_dbs_prod_global",
            "caseSensitive":"on",
            "method":"dbsapi",
            "html":"0",
            "userInput":searchstring,
            "userMode":"user",
            "details":"0",
            "sortOrder":"desc"
#            "pagerStep":"-1",
#            "cff":"1"
            }
    optstring = urllib.unquote(urllib.urlencode(opt))
    response = urllib2.urlopen(base_dataset + optstring)
    res = response.read().strip().split('\n')
    type = res[1:][0]
    return type

if __name__ == '__main__':
    print getDataset('zprime_ttbar')
#    for i in getDataset('test t'):
#        print i
#    print getType('/MinBias/Summer09-MC_3XY_V9B_900GeV-v2/GEN-SIM-RAW')
#    print getType('/MinimumBias/BeamCommissioning09-Dec19thReReco_336p3_v2/RECO')
#    import sys
#    if len(sys.argv) == 2:
#        auto(sys.argv[1])
#    else:
#        print "Please enter a search term or dataset name"
#        search = raw_input(">")
#        print len(auto(search))
        
