'''
Created on Dec 11, 2009

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch

1 query per function call!
http://dashb-cms-job-task.cern.ch/taskmon.html#task=kreczko_CRABTEST_yp748s
'''
import pyexpat
import urllib, urllib2
import xml.dom.minidom as xml
#_base_url = 'http://dashb-cms-job-task.cern.ch/taskmon.html'
_base_url = 'http://dashb-cms-sam.cern.ch/dashboard/request.py/taskjobsxml?'
_details = 'http://dashb-cms-job-task.cern.ch/dashboard/request.py/taskmonitoring#action=taskJobs&usergridname=undefined&taskmonid=%(task_name)s&what=all'
_headers = {'Accept': 'text/xml'}

def get_job_status(dashlink):
    crabjobname = get_taskinfo(dashlink)['name']
    xjobs = _getjobsXML(crabjobname)
    if xjobs:
        return _parseXMLjobs(xjobs)


#@deprecated
def getLink(task_name):
    return _details % {'task_name': task_name}
#===============================================================================
# get all jobs information
#===============================================================================
def _getjobsXML(crabjobname):
    opt = {"taskmonid" : crabjobname,
           'timerange' : 'lastMonth',
            'what' : 'all'
            }
    if crabjobname:
        optstring = urllib.unquote(urllib.urlencode(opt))
    #response = urllib2.urlopen(_base_url + optstring,headers = _headers)
        req = urllib2.Request(_base_url + optstring,headers = _headers)
        response = urllib2.urlopen(req)
        dom = xml.parse(response)
    
        return  dom


def _parseXMLjobs(dom):
    jobroot = _getChildNodes(dom.childNodes[0], 'jobs')
    if not jobroot:
        return
    jobs =  _getChildNodes(jobroot[0], 'item')
    ret = []
    for job in jobs:
        j = {}
        status = _getText(job, 'STATUS')
        if status == 'S':
            status = 'success'
        elif status == 'P':
            status = 'pending'
        elif status == 'F':
            status = 'failed'
        elif status == 'R':
            status = 'running'
        elif status == 'U':
            status = 'unknown'
        j['status'] = status
        j['id'] = int(_getText(job, 'EventRange'))
        j['submitted'] = _getText(job, 'submitted')
        j['started'] = _getText(job, 'started')
        j['finished'] = _getText(job, 'finished')
        ret.append(j)
    return ret
    
def _getChildNodes(parentnode, name):
        ret = []
        for i in parentnode.childNodes:
            if i.localName == name:
                ret.append(i)
        return ret    
 
def _getText(node, name):
        ret = ""
        node = _getChildNodes(node, name)[0]
        for i in node.childNodes:
            if i.nodeType == i.TEXT_NODE:
                ret += i.data
        return ret
    
def get_taskinfo(dashlink):
    name = dashlink.split('=')[-1]
    user = name.split('_')[0]
    return {'name':name, 'user':user}

           
if __name__ == '__main__':
   # print get_job_status('kreczko_CRABTEST_yp748s')
   # print get_job_status('ferencek_crab_0_091205_143221_r6t8n3')
   # print get_job_status('yuehfenl_crab_0_091209_160005_t4l3p6')
   # print get_job_status('gebbert_MinBias2360GeVMC_1j76uh')
    print get_job_status('http://dashb-cms-job-task.cern.ch/taskmon.html#task=kreczko_MinimumBias_BeamCommissioning09-PromptReco-v2_RECO_patTuple_124023_2010_1_5_7sk96d')
    #print get_job_status('jacksonj_crab_0_091216_162920_k783qm')
