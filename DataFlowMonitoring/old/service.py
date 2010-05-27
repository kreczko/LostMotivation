import os
from mod_python import apache
from datetime import datetime
#===============================================================================
# Own imports
#===============================================================================
#_currentdir = os.path.dirname(__file__)
#_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))
#_templatepath = _currentdir + '/templates/'
#_cfgpath = _currentdir + 'configs/'
try:
    #import wrapper to import modules form application root
    import module
except:
    module = apache.import_module('tools/module')
    
try:
    from tools import dfm
except:
    dfm =  module.load("tools.dfm")  

#sooling group path
group_path = '/storage/top/'
se_path = '/gpfs_phys/storm/cms/'

def index():
    return 'you are in the wrong place'

def request_files_to_copy():
    return dfm.getFilesToCopy()
#    files = []
#       
#    finished_jobs = db.get_jobs_by_status(status = 'success', limit=5)
#    #test if jobs are already copied
#    copied = False
#    for job in finished_jobs: 
#        file = _createLFN(job['file'])
#        file['config_id'] = job['config_id']
#        if not db.is_copied(file):
#            db.create_copy_job(file)
#            #return file #
#            files.append(file)  
#    return files

def confirm_copied_file(req):
    dfm.confirmCopy(req.form)
#    db.update_copy_job(req.form)
    return 'ok'

#def _createLFN(location):
#    location = location.lstrip('/')
#    lfn = {}
#    lfn['location'] = se_path + location
#    #remove /store/user/username/ from the location
#    path = location.split('/')[3:]
#    path = ''.join([x+'/' for x in path])
#    #remove last /
#    path = path.rstrip('/')
#    lfn['destination'] = group_path + path
#    return lfn

def update():
    dfm.updateDashboard()
    d = datetime.today()
    d = '%s %02d %02d - %02d:%02d:%02d' % (d.year, d.month, d.day, d.hour, d.minute, d.second)
    return 'update ok - ' + d
