'''
Created on Sep 28, 2009

@author: lkreczko
'''
try:
    #sqlite 1 on webpp
    import sqlite as db
except:
    from sqlite3 import dbapi2 as db
import time, os
from datetime import date
from datetime import datetime
try:
    import config.crab_constants as const
    import database as db
except:
    import module
    const = module.load("config.crab_constants")
    db = module.load("tools.database")  

_currentdir = os.path.dirname(__file__)
_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))
_cfgpath = _applicationRoot + 'configs/'


        
def create_path_and_filename(info, runnumber = 0):
    #the DBS sample name, strip the leading /
    dbs_sample = info['dbs_sample'].lstrip('/')
    private_str = info['private_string']
    user = info['user']
    #nTuple_Version = '%s_%s' % (const.nTuple_Version_prefix, nTuple_Version)
    path = ''
    filename = ''
    #first get the different parts of the DBS name:
    filename = dbs_sample.replace('/', '_') 
#    stype, production, format = dbs_sample.split("/")
    if runnumber >0:
        path = dbs_sample.replace("/", "_") + '_' + private_str + '/' + str(runnumber)
    else:
        path = dbs_sample.replace("/", "_") + '_' + private_str
    filename = path.replace('/', '_') + '.root'
#    filename = (''.join([x + '_' for x in (stype, production, format, private_str)])).rstrip('_') + '.root'
    #filename = '%s_%s.root' % (stype, production, format, )
    #productionpath = production.replace('_', '/')
    result = {}
    #result['user_remote_dir'] = ''.join([x + '/' for x in (const.User_Remote_Dir_Base, productionpath, format, nTuple_Version, stype)])
    result['user_remote_dir'] = const.User_Remote_Dir_Base + '/' + user + '/' + info['primType'] + '/' + path
    result['output_file'] = const.nTuple_Version_prefix + '_' + filename
    today = datetime.fromtimestamp(time.time())
    if info['primType'] == 'data':
        result['working_dir'] = '%s_%s_%s' % (dbs_sample.split('/')[0], dbs_sample.split('/')[1], private_str)
    else:
        result['working_dir'] = '%s_%s' % (dbs_sample.split('/')[0], private_str)
    
    return result

def create_config(info):
    dbs_sample = info['dbs_sample']
    private_str = info['private_string']
    primType = info['primType']
    run_number = ''
    if primType == 'data':
        run_number = info['run_number']
    uo = create_path_and_filename(info, run_number)
    
    const.user['user_remote_dir'] = uo['user_remote_dir']
    const.cmssw['output_file'] = uo['output_file']
    const.cmssw['datasetpath'] = dbs_sample
    if not run_number == '':
        const.cmssw['runselection'] = run_number
    
    today = date.fromtimestamp(time.time())
    const.user['ui_working_dir'] = uo['working_dir']
    cfg_file_prefix = datetime.now().strftime("%Y_%m_%d_%H-%M-%S")
    type = dbs_sample.lstrip('/').replace('/', '_')
    cfgfile = '%s_%s_%s.cfg' % (cfg_file_prefix, type, private_str)
    
    CRAB = create_section(const.crab, '[CRAB]')
    GRID = create_section(const.grid, '[GRID]')    
    USER = create_section(const.user, '[USER]')
    CMSSW = create_section(const.cmssw, '[CMSSW]')
    
    cfg = ''.join(CRAB)
    cfg = cfg + '\n' * 3 + ''.join(CMSSW)
    cfg = cfg + '\n' * 3 + ''.join(USER)
    cfg = cfg + '\n' * 3 + ''.join(GRID)
    
    file = open(_cfgpath + cfgfile, 'wb')
    file.write(cfg)
    file.close()
    #TODO: make this easier
    #config_id = db.add_config(dbs_sample=dbs_sample, filepath=_cfgpath + cfgfile, crab_output_filename=uo['output_file'], crab_storage_path=uo['user_remote_dir'])
    info['crab_output_filename'] = uo['output_file']
    info['filepath'] = cfgfile
    info['crab_storage_path'] = uo['user_remote_dir']
#    params = {'dbs_sample':dbs_sample, 
#              'crab_output_filename': uo['output_file'],
#              'crab_storage_path':uo['user_remote_dir'],
#              'filepath': _cfgpath + cfgfile,
#              'primType' :info['primType']}
    config_id = db.add_configuration(info)
    return {"config_path":_cfgpath, "config_name": cfgfile, 'config_id': config_id, 'dbs_sample': dbs_sample}


def create_section(variables, str):
    ret = ['%s = %s \n' % (k, v) for k, v in variables.iteritems()]
    ret.insert(0, '%s \n' % str)
    return ''.join(ret)

        
        
if __name__ == '__main__':
    #get_failed_jobs()
    #get_unique_states()
    create_config('../../tmp/test.cfg', "/QCD_EMEnriched_Pt30to80/Summer09-MC_31X_V3_SD_Ele15-v1/GEN-SIM-RECO", 'V1')
