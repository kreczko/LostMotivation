'''
Created on Nov 17, 2009

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch
'''
import sys, os
from datetime import datetime
from mod_python import apache

#===============================================================================
# Own imports
#===============================================================================
_currentdir = os.path.dirname(__file__)
_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))
#_applicationRoot = '/var/app/dfm/'
_src = _applicationRoot + 'src/'
_templatepath = _currentdir + '/templates/'  
_cfgpath = _applicationRoot + 'configs/'
#test =  apache.import_module('templates/test')
#tools = apache.import_module('/var/app/dfm/src/tools/__init__')
try:
    #import wrapper to import modules form application root
    import module
except:
    module = apache.import_module('tools/module')
#import DBS module
try: 
    from tools import DBS
    from tools import crab
    from tools import database as db
    from tools import dfm
except:
    DBS = apache.import_module('tools/DBS')
    crab = apache.import_module('tools/crab')
    db =  module.load("tools.database")
    dfm = module.load('tools.dfm')
#
#def dfm.readTemplate(tplname):
#    f = open(_templatepath + tplname + '.html')
#    ret = f.read()
#    f.close()
#    return ret

def index():
    s = dfm.readTemplate('index')
    return s 

def TODO():
    s = dfm.readTemplate('ind')
    return s
   
def search_dbs(req):
    search_str = req.form['dbs_search']
#    primType = req.form['primType']
    ds = DBS.getDataset(search_str) 
    if ds['error'] == True:
        return ds['result']
    dbs_list = []
    for dbs in ds['result']:
        d = {}
        d['name'] = dbs 
#        d['primType'] = primType
        dbs_list.append(d)
    
    return _dbs_view(dbs_list)

def display_file(req): 
    file = req.form['filepath']
    return dfm.readFile(file)
#    file = open(req.form['filepath'])
#    f = file.read()
#    file.close()
#    return f

def show_all_datasets():
    ds = db.get_all_datasets()
    return _dbs_view(ds)

def show_available_datasets():
    ds = db.get_available_datasets()
    return _dbs_view(ds)

def _dbs_view(dbs_sample_list):
    table = ''
    row = dfm.readTemplate('DBS_results_row')
    data = {}
    for d in dbs_sample_list:
        numberOfConfigs = len(db.get_config(d['name']))
        data['disabled'] = 'disabled'
        if numberOfConfigs >0:
            data['disabled'] = ''
        data['dbs_sample'] = d['name']
        data['configs'] = numberOfConfigs
        table +=  row % data
        
    tpl = dfm.readTemplate('DBS_results')
    
    return tpl % (len(dbs_sample_list),table)

def create_config(req):
    form = req.form
    #TODO: change to db.create_config
    cfg = crab.create_config(form)
    #cfgfile = cfg['config_name']
    cfg['config_path'] = '../configs/' + cfg['config_name']
    #cfg['dbs_sample'] =  form['dbs_sample']
    #cfg['primType'] = form['primType']
    out = dfm.readTemplate('created') % cfg
    #db.add_config(dbs_sample, filepath=_cfgpath + cfgfile)
    return out

def prepair_config(req):
    form = {}
    form['dbs_sample'] = req.form['dbs_sample']
    dbs_sample = form['dbs_sample']
    primType = DBS.getType(dbs_sample)
    form['primType'] = primType
#    runnumber = """<p>run number</p>
#    <input type="text" name="run_number" %(run_number_form)s>"""
    if primType == 'data':
        form['run_number_form'] = ''
    else:
        form['run_number_form'] = 'disabled'
    
    return dfm.readTemplate('prepair_cfg') % form

def show_configs(req):
    dbs_sample = req.form['dbs_sample']
    cfgs = db.get_config(dbs_sample)
    tpl = dfm.readTemplate('cfg_list')
    
    table = ''
    row = dfm.readTemplate('cfg_row')
    for cfg in cfgs:
        cfg['filepath'] = cfg['filepath'].replace(_currentdir + '/', '')
#        return cfg['filepath']
        cfg['creation_date'] = _format_date(cfg['creation_date'])
        cfg['submission_date'] = _format_date(cfg['submission_date'])
        cfg['dbs_sample'] = dbs_sample
        cfgname = cfg['filepath'].split('/')[-1]
        table += row % (cfg) 
    tpl = tpl %(dbs_sample, table)
    return tpl
    
def _format_date(timestamp):
    if timestamp:
        try:
            timestamp = float(timestamp)
        except ValueError:
            return '-'*3
        d = datetime.fromtimestamp(timestamp)
        d = '%s %02d %02d - %02d:%02d:%02d' % (d.year, d.month, d.day, d.hour, d.minute, d.second)
        return d
    
def _format_time(seconds):
    h = 0
    m = 0
    s = 0
    ft = ""
    if seconds >= 3600:
        h = (seconds - seconds%3600)/3600
        seconds = seconds -h*3600
    if seconds >= 60:
        m = (seconds - seconds%60)/60
        seconds = seconds-m*60
            
    s = seconds
    if h > 0:
        ft = round(h,0).__str__() + "h "
    if m > 0:
        ft = ft + round(m, 0).__str__() + "m "
    ft =  ft + round(s,2).__str__() + "s"  
    return ft

def _progress(pr):
    ps = ""
    done = pr['done']
    running = pr['running']
    for x in range(0,100,5):
        if x < done:
            ps += "<td class='done' nowrap='nowrap'>&nbsp;</td>"
        elif x >= done and x < done + running:
            ps += "<td class='running' nowrap='nowrap'>&nbsp;</td>"
        else:
            ps += "<td class='missing' nowrap='nowrap'>&nbsp;</td>"
    #s = dfm.readTemplate('progress') % ('%', ps)
    return ps

def show_progress(req):
    dbs_sample = req.form['dbs_sample']
    config_id = req.form['config_id']
    grid = db.get_grid_status(config_id)
    soolin = db.get_copy_status(config_id)
    val = db.get_validation_status(config_id)
    #tpl = dfm.readTemplate('status') 
    s = {'config_id': config_id, 
         'dbs_sample': dbs_sample,
         'grid':_progress(grid),
         'soolin':_progress(soolin),
         'validation': _progress(val),
         'table_width': '100%',
         'dashboard_link':db.get_dashboard_link(config_id)}
    #s = dfm.readTemplate('status') % s
    return dfm.readTemplate('status') % s

def show_details_soolin(req):
    jobs = db.get_copy_jobs(req.form['config_id'])
    template = dfm.readTemplate('details_progress_copy')
    row = dfm.readTemplate('row_progress_copy')
    if not jobs:
        return 'No copy started'
    all = jobs[0]
    all['table_rows'] =''
    all['config_id'] = req.form['config_id']
    x = 2
    for job in jobs:
        job['started'] = _format_date(job['started'])
        job['finished'] = _format_date(job['finished'])
        time = 0
        try:
            time = float(job['copy_time'])/100
            time = _format_time(1.0*time)
        except ValueError:
            time = '-'*3
#        job['copy_time'] = _format_time(job['copy_time']/100)
        job['copy_time'] = time
        if x%2 == 0:
            job['row_class'] = 'one'
        else:
            job['row_class'] = 'two'
        all['table_rows'] += row % job
        x+=1
    return template % all

def show_details_validation(req):
    return 'TODO'

def show_plots(req):
    return 'TODO'

def prepair_dashlink(req):
    return dfm.readTemplate('dashlink') % req.form

def add_dashlink(req):
    db.add_info(req.form)
    return "Configuration has been updated"

#def test_paths(req):
#    dbs_sample = req.form['dbs_sample']
#    primType = req.form['primType']
#    tmp = _create(dbs_sample, primType)
#    ret = """<html><body>sample: %s (<i>%s</i>) <br><br>
#    soolin path:<br>
#    <b>%s</b><br><br>
#    filename:<br>
#    <b>%s</b> <br><br>
#    remote dir (SE path):<br>
#    <b>%s</b>
#    </body></html>
#    """ %(dbs_sample, primType, tmp['folder'], tmp['file'],tmp['remote_dir']) 
#    return ret
    
#def _create(dbs_sample, primType):
#    res = crab.create_path_and_filename({'dbs_sample':dbs_sample, 'private_string' :'private_str', 'user':'username'})
#    data = '/storage/top/data/'
#    mc = '/storage/top/mc/'
#    output = {'file' : '', 'folder':''}
##    input = dbs_sample.lstrip('/')
##    tmp = input.split('/')
##    format = tmp[-1]
##    type = tmp[-2]
##    rest = tmp[:-2]
#    rest = res['user_remote_dir'].split('/')[4:]
#    output['file'] = res['output_file'] #= filename#type + '_nTuple_V1.root'
#    output['remote_dir'] = res['user_remote_dir']
#    if primType == 'data':
#        output['folder'] = data
#    elif primType == 'mc':
#        output['folder'] = mc
#        
#    for f in rest:
#        output['folder'] = output['folder'] +  f + '/'
#    return output

def delete_config(req):
    dfm.deleteConfig(req.form)
    return "Configuration deleted"
 
def delete_copy_request(req):
    config_id = req.form['config_id']
    db.delete_copy_request(config_id)
    return 'all requests deleted'

def show_datasets_in_progress(req):
    sort = 'dbs_sample'
    if req.form.has_key('sort_by'):
        sort = req.form['sort_by']
    if sort == 'dbs_sample' :
        return _datasets_in_progress_by_sample()
    elif sort == 'user' :
        return _datasets_in_progress_by_user()

def _datasets_in_progress_by_user():
    users = {}
    all = ''
    tables = ''
    ds_header = """<h2>Status for </h2>
                    <h3>%s</h3>"""
    ds = db.get_datasets_in_progress()
    for data in ds:
        configs = db.get_config(data['name'])
        for config in configs:
            user = config['submitted_by']
            if not users.has_key(user):
                users[user] = {}
            if not users[user].has_key(data['name']):
                users[user][data['name']] = []
            users[user][data['name']].append(config)
    users.keys().sort()
    
    for user,datasets in sorted(users.iteritems()):
        all += "<hr /><h2>Submitted by %s</h2><hr />" % user
        for ds, configs in datasets.iteritems():
            all += ds_header % ds
            for config in configs:
                config_id = config['config_id']
                grid = db.get_grid_status(config_id)
                soolin = db.get_copy_status(config_id)
                val = db.get_validation_status(config_id)
                s = {'config_id': config_id, 
                 'dbs_sample': data['name'],
                 'grid':_progress(grid),
                 'soolin':_progress(soolin),
                 'validation': _progress(val),
                 'table_width': '100%',
                 'dashboard_link':db.get_dashboard_link(config_id)}
                tables += dfm.readTemplate('progress_table') %s
            all += tables
            tables = ''
        all += '<hr /><br />'
    return dfm.readTemplate('progress_multi_ds') % all
        
        
def _datasets_in_progress_by_sample():
    ds = db.get_datasets_in_progress()
    tables = ''
    ds_header = """<h2>Status for </h2>
                    <h3>%s</h3>"""
    all = ''
    for data in ds:
        header = ds_header % data['name']
        configs = db.get_config(data['name'])
        for config in configs:
            config_id = config['config_id']
            grid = db.get_grid_status(config_id)
            soolin = db.get_copy_status(config_id)
            val = db.get_validation_status(config_id)
            s = {'config_id': config_id, 
                 'dbs_sample': data['name'],
                 'grid':_progress(grid),
                 'soolin':_progress(soolin),
                 'validation': _progress(val),
                 'table_width': '100%',
                 'dashboard_link':db.get_dashboard_link(config_id)}
            tables += dfm.readTemplate('progress_table') %s
        all += header + tables
        tables = ''
            
    return dfm.readTemplate('progress_multi_ds') % all

def add_dataset_manually():
    return dfm.readTemplate('add_dataset')

def add_dataset(req):
    db.add_dbs_sample(dbs_sample = req.form['name'], primtype= req.form['name'])
    
def remove_dataset(req):
    db.remove_dbs_sample(req.form['name'])
