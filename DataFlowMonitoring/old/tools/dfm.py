#DFM interface
import os
try:
    #import wrapper to import modules form application root
    import module
except:
    module = apache.import_module('tools/module')
try: 
    from tools import DBS
    from tools import crab
    from tools import database as db
    from tools import dashboard
except:
    DBS = module.load('tools.DBS')
    crab = module.load('tools.crab')
    db = module.load('tools.database')
    dashboard = module.load('tools.dashboard')

#absolute paths
_currentdir = os.path.dirname(__file__)
_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))
#_src = _applicationRoot + 'src/'
_templatepath = _applicationRoot + 'templates/'  
_cfgpath = _applicationRoot + 'configs/'
_dbname = _applicationRoot + 'db/dfm_alpha.db'
db.set_database(_dbname)

def createConfig(info):
    pass

def readTemplate(template):
    return readFile(template + '.html')

def readFile(filename):
    config = _cfgpath + filename
    template = _templatepath + filename
    isconfig = os.path.exists(_cfgpath + filename)
    istemplate = os.path.exists(_templatepath + filename)
    
    if istemplate:
        filename = template
    elif isconfig:
        filename = config
    else:
        ret = 'File not found or access not allowed\n'
        raise ret + str(filename)
    f = open(filename)
    ret = f.read()
    f.close()
    return ret

def searchDBS(dataset):
    ds = DBS.getDataset(search_str) 
    if ds['error'] == True:
        return ds['result']
    dbs_list = []
    for dbs in ds['result']:
        d = {}
        d['dbs_sample'] = dbs 
#        d['primType'] = primType
        dbs_list.append(d)
    return dbs_list

def getAllDatasets():
    return db.get_all_datasets()

def getAvailableDatasets():
    return db.get_available_datasets()

def numberOfConfigs(dataset_name):
    return len(getConfigs(dataset_name))

def getPrimType(dataset_name):
    return DBS.getType(dataset_name)

def getConfigs(dataset_name):
    return db.get_config(dataset_name)

def getProgress(config_id):
    return {'grid': db.get_grid_status(config_id),
            'soolin': db.get_copy_status(config_id),
            'validation': db.get_validation_status(config_id)}
    
def getCopyJobs(config_id):
    return db.get_copy_jobs(config_id)

def updateDashboard():
    config_ids = db.getNotFinishedGridConfigs()
    for id in config_ids:
        link = db.get_dashboard_link(id)#get the dashboard link
        jobstats = dashboard.get_job_status(link)#get the jobs status
        db.update_jobs(jobstats, id)#write the new status to the database
#    db.update_dashboard(config_ids)
    
def getFilesToCopy():
    files = []
       
    finished_jobs = db.get_jobs_by_status(status='success', limit=5)
    #test if jobs are already copied
    copied = False
    for job in finished_jobs: 
        file = _createLFN(job['file'])
        file['config_id'] = job['config_id']
        if not db.is_copied(file):
            db.create_copy_job(file)
            #return file #
            files.append(file)  
    return files

def confirmCopy(info):
    db.update_copy_job(req.form)

def deleteConfig(info):
    db.delete_config(req.form)    

def _createLFN(location):
    #sooling group path
    group_path = '/storage/top/'
    se_path = '/gpfs_phys/storm/cms/'
    location = location.lstrip('/')
    lfn = {}
    lfn['location'] = se_path + location
    #remove /store/user/username/ from the location
    path = location.split('/')[3:]
    path = ''.join([x + '/' for x in path])
    #remove last /
    path = path.rstrip('/')
    lfn['destination'] = group_path + path
    return lfn
