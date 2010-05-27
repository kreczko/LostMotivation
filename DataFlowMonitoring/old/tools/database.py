'''
Created on Dec 2, 2009

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch
'''
try:
    #sqlite 1 on webpp
    import sqlite as db
except:
    #on VM and local machine
    from sqlite3 import dbapi2 as db
import os
#from datetime import date
import time
import dashboard
    
_currentdir = os.path.dirname(__file__)
_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))
_dbname = _applicationRoot + 'db/dfm_alpha.db'
#_db_schema = 'tools/db'
#_dbname = '/var/www/html/dfm/db/dfm_alpha.db'


def set_database(dbname):
    if dbname:
        _dbname = dbname


def _query(sql):
    res = None
    try:
        con = db.connect(_dbname)
        cur = con.cursor()
        cur.execute(sql)
        res = cur.fetchall()
        con.commit()
        con.close()
    except:
        s = 'Could not access database:2 ' + _dbname + ' while trying ' + sql
        raise s
    return res

def update_jobs(jobs, config_id):
    update = "UPDATE dashboard SET status='%(status)s', last_checked='%(now)s'WHERE job_id=%(id)d AND config_id=%(config_id)d"
    check = "SELECT id from dashboard WHERE job_id=%(id)d AND config_id=%(config_id)d"
    insert = "INSERT INTO dashboard"
    fields = '(config_id, job_id, last_checked, status)'
    values = '(%(config_id)d, "%(id)d", "%(now)s", "%(status)s");'
    insert += fields + ' VALUES ' + values
    if jobs:
        for job in jobs:
            job['now'] = time.time()
            job['config_id'] = config_id
            existing_jobs = _query(check % job)
            if existing_jobs and len(existing_jobs) > 0:
                _query(update % job)
            else:
                _query(insert % job)
                

def _is_cfg_grid_finished(id):
    sql = 'select status from dashboard where config_id = %d' % id
    alldone = True
    for status in _query(sql):
        if not status == 'success':
            alldone = False
    return alldone

def _remove_grid_jobs(config_id):
    sql = 'Delete from dashboard where config_id=%d' % config_id
    _query(sql)
    
    
def get_jobs_by_status(status, limit=10):
    #needed: config_id, output filename, job_id, crab_storage path, 
    #for all not finished configs!!
    configs = "SELECT id, crab_storage_path, crab_output_filename from config_files WHERE (finished_grid <>1 OR finished_grid IS NULL) AND dashlink IS NOT NULL"
    tasks = _query(configs)
    #ok till here
    selectedjobs = []
    for task in tasks:
        info = {}
        info['id'] = task[0]
        info['outpath'] = task[1]
        info['filename'] = task[2]
        info['limit'] = limit
        if len(selectedjobs) >= limit:
            return selectedjobs
#        jobs = dashboard.get_job_status(task[0])
        jobs = get_jobs_by_cid(info)
#        _update_jobs(jobs, info['id'])
        outputfilename = info['filename'].rstrip('.root')
        for job in jobs:
            if job['status'] == status:
                job['file'] = info['outpath'] + '/' + outputfilename + '_' + str(job['id']) + '.root'
                selectedjobs.append(job)
    return selectedjobs
    
def get_config(dbs_sample, sort='dbs_sample'):
    if not sort:
        sort = 'dbs_sample'
    sort_by = ''
    if sort == 'dbs_sample':
        sort_by = 'ORDER BY dbs_samples.name ASC'
    elif sort == 'user':
        sort_by = 'ORDER BY config_files.submitted_by ASC'
    
    select = 'filepath, creation_date, crab_output_filename, crab_storage_path, submission_date, submitted_by, dashlink, config_files.id'
    sql = 'Select ' + select + ' from dbs_samples,config_files where dbs_samples.name="%s" AND dbs_samples.id = config_files.DBS_sample_id %s' % (dbs_sample, sort_by)
    #sql = 'Select cfg from DBS_cfg config where dbs_name="%s"' %dbs_sample
    cfgs = _query(sql)
    c = []
    if cfgs:
        for i in cfgs:
            config = {}
            config['filepath'] = i[0]
            config['creation_date'] = i[1]
            config['crab_output_filename'] = i[2]
            config['crab_storage_path'] = i[3]
            config['submission_date'] = i[4]
            config['submitted_by'] = i[5]
            config['dashlink'] = i[6]
            config['config_id'] = i[7]
            
            c.append(config)
    return c

#def add_config(dbs_sample, crab_output_filename, crab_storage_path, filepath):
#    dbs_id = _get_DBS_id(dbs_sample)
#    vals = {}
#    vals['dbs_id'] = dbs_id
#    vals['crab_output_filename'] = crab_output_filename
#    vals['crab_storage_path'] = crab_storage_path
#    vals['filepath'] = filepath 
#    cmd = 'INSERT INTO config_files'
#    vals['date'] = time.time()
#    fields = '(DBS_sample_id, crab_output_filename, crab_storage_path, creation_date, filepath)'
#    values = '(%(dbs_id)s, "%(crab_output_filename)s", "%(crab_storage_path)s", %(date)s, "%(filepath)s");' % vals
#    sql = cmd + ' ' + fields + ' VALUES ' + values
#    _query(sql)
#    sql = 'SELECT id from config_files where filepath = "%s"' % vals['filepath']
#    return _query(sql)[0][0]

def add_configuration(vals):
    dbs_id = _get_DBS_id(vals)
    vals['dbs_id'] = dbs_id
    cmd = 'INSERT INTO config_files'
    vals['date'] = time.time()
    fields = '(DBS_sample_id, crab_output_filename, crab_storage_path, creation_date, filepath)'
    values = '(%(dbs_id)s, "%(crab_output_filename)s", "%(crab_storage_path)s", %(date)s, "%(filepath)s");' % vals
    sql = cmd + ' ' + fields + ' VALUES ' + values
    _query(sql)
    sql = 'SELECT id from config_files where filepath = "%s"' % vals['filepath']
    return _query(sql)[0][0]
    
def _get_DBS_id(vals):
    sql = 'Select id from dbs_samples where name="%s"' % vals['dbs_sample'] 
    res = _query(sql)
    if not res:
        add_dbs_sample(vals)
        res = _query(sql)
    id = res[0][0]
    return id

def get_all_datasets():
    sql = 'SELECT name, luminosity, twiki_page, primType from dbs_samples'
    res = _query(sql)
    samples = _format_dataset(res)
    return samples

#shows all datasets where all grid & copy jobs are completed
def get_available_datasets():
    sql = 'SELECT DBS_sample_id from config_files where finished_grid=1 AND finished_copy=1'
    sql = 'SELECT DBS_sample_id from config_files where finished_grid=0'
    sql_ds = 'SELECT name, luminosity, twiki_page, primType from dbs_samples where id IN (%s)'
    ids = _query(sql)
    ids = [x[0].__str__() for x in ids]
    ids = ','.join(ids)
    sql_ds = sql_ds % ids
    res = _query(sql_ds)
    samples = _format_dataset(res)
    return samples

def get_dbs_sample_by_field(field, value):
    
    pass

def add_dbs_sample(vals):#dbs_sample, luminosity=0, primtype = 'mc', twiki_page=''):
    if not vals.has_key('luminosity'):
        vals['luminosity'] = 0.0
    if not vals.has_key('twiki_page'):
        vals['twiki_page'] = 'https://twiki.cern.ch/twiki/bin/viewauth/CMS/ProductionSummer2009at7TeV'
    sql = """INSERT INTO dbs_samples (id, luminosity, name, twiki_page, primType) 
    VALUES (null, %(luminosity)s, "%(dbs_sample)s", "%(twiki_page)s", "%(primType)s")""" % vals 
    _query(sql)
    
def remove_dbs_sample(dbs_sample):
    sql = """DELETE from dbs_samples where name = '%s';""" % dbs_sample
    _query(sql)
    
def get_grid_status(config_id):
    sql = 'SELECT finished_grid from config_files where id = %s' % config_id
    finished = _query(sql)[0]
    if finished == 1:
        return {'done':100, 'running':0, 'missing':0}
    
    sql = 'SELECT status, id from dashboard where config_id = %s' % config_id
#    sql = 'SELECT dashlink from config_files where id = %s' % config_id
    
    jobs = [{'status': x[0], 'id':x[1]} for x in _query(sql)]
#    dashlink = _query(sql)[0][0]
#    jobs = dashboard.get_job_status(dashlink)
#    _update_jobs(jobs, config_id)
    if not jobs:
        return {'done':0, 'running':0, 'missing':0}
    njobs = len(jobs)
    done = 0
    running = 0
    missing = njobs
    for job in jobs:
        if job['status'] == 'success':
            done += 1.0 / njobs * 100
        elif job['status'] == 'running':
            running += 1.0 / njobs * 100
    done = round(done)
    running = round(running)
    missing = missing - done - running
    return {'done':done, 'running':running, 'missing':missing}

def get_copy_status(config_id):
    #all files marked for copy
    sql = 'select done_date from copy_jobs where config_id=%s' % config_id
    sql2 = 'SELECT dashboard.id from dashboard where dashboard.config_id =%s ' % config_id
    copy_entries = _query(sql)
    numberOfGridFiles = len(_query(sql2))
    done = 0
    running = 0
    missing = 100
    if not numberOfGridFiles == 0:
        for e in copy_entries:
            done_date = e[0]
            if done_date:
                done += 1.0 / numberOfGridFiles * 100
            else:
                running += 1.0 / numberOfGridFiles * 100
    done = round(done)
    running = round(running)
    missing = missing - done - running 
    #if done_date => done
    #if not done_date  => running
    #if  missing
    return {'done':done, 'running':running, 'missing':missing}

def get_validation_status(config_id):
    sql = 'select done_date from validation_jobs where config_id=%s' % config_id
    sql2 = 'select id from copy_jobs where config_id=%s' % config_id
    numberOfCopiedFiles = len(_query(sql2))
    val_entries = _query(sql)
    done = 0
    running = 0
    missing = 100
    if not numberOfCopiedFiles == 0:
        for e in val_entries:
            done_date = e[0]
            if done_date:
                done += 1. / numberOfCopiedFiles * 100
            else:
                running += 1. / numberOfCopiedFiles * 100
    done = round(done)
    running = round(running)
    missing = missing - done - running 
    return {'done':done, 'running':running, 'missing':missing}

def get_dashboard_link(config_id):
    sql = 'SELECT dashlink from config_files where id = %s' % config_id
    dashlink = _query(sql)[0][0]
    return dashlink
    #return dashboard.getLink(dashlink)

def add_info(info):
    dashlink = info['dashlink']
    config_id = info['config_id']
    user = dashboard.get_taskinfo(dashlink)['user']
    now = time.time()
    sql = 'UPDATE config_files SET dashlink = "%s", submitted_by="%s", submission_date=%s  where id = %s' % (dashlink, user, now, config_id)
    _query(sql)
    
def create_copy_job(info):
    info['request_date'] = time.time()
    sql = """INSERT INTO copy_jobs (id,config_id, destination, location, request_date)
    VALUES (null, %(config_id)s, '%(destination)s', '%(location)s', %(request_date)s)""" % info
    _query(sql)
    
def update_copy_job(info):
    info['done_date'] = time.time()
    sql = "UPDATE copy_jobs SET done_date=%(done_date)s where location = '%(location)s'" % info
    _query(sql)
    
def get_copy_jobs(config_id):
    sql = 'SELECT location, destination, request_date, done_date, id from copy_jobs where config_id=%s' % config_id
    result = _query(sql)
    jobs = []
    for res in result:
        job = {}
        location = res[0]
        job['file'] = location.split('/')[-1]
        job['location_folder'] = location.replace(job['file'], '')
        job['destination_folder'] = res[1].replace(job['file'], '')
        job['started'] = res[2]
        job['finished'] = res[3]
        job['id'] = res[4]
        if job['finished']:
            job['copy_time'] = float(job['finished']) - float(job['started'])
        else:
            job['finished'] = '-' * 3
            job['copy_time'] = '-' * 3
        jobs.append(job)
    return jobs

def is_copied(job):
#    sql = 'DELETE from copy_jobs where id>84'
#    _query(sql)
    sql = 'SELECT done_date from copy_jobs where location="%s"' % job['location']
    res = _query(sql)
    ret = False
    if res and res[0]:
        ret = True
    return ret

def delete_config(info):
    sql = 'Select filepath from config_files where id=%(config_id)s' % info
    file = _query(sql)[0][0]
    if os.path.exists(file):
        os.remove(file)
    sql = 'DELETE from config_files where id=%(config_id)s' % info
    _query(sql)

def is_config_finished(info):
    sql = 'Select finished from config_files where id=%(config_id)' % info
    finished = _query(sql)[0][0] == 1
    return finished

def isConfigFinishedOn(config_id, subprocess='grid'):
    sql = ''
    #construct query
    if subprocess == 'grid':
        #get the finish flag for grid
        sql = 'SELECT finished_grid from config_files where id=%d;' %config_id
    elif subprocess == 'copy':
        #get the finish flag for copy
        sql = 'SELECT finished_copy from config_files where id=%d;' %config_id
    else:#unknown subprocess
        return
    #execute query
    finished = _query(sql)[0][0]
    return finished == 1

def markConfigAsFinishedOn(config_id, subprocess = 'grid'):
    sql = ''
    #construct query
    if subprocess == 'grid':
        #set the finish flag for grid
        sql = 'UPDATE config_files SET finished_grid=1 where id=%d;' %config_id
        #delete obsolete entries in dashboard table
        sql += 'DELETE from dashboard where config_id=%d' %config_id
    elif subprocess == 'copy':
        #set the finish flag for copy
        sql = 'UPDATE config_files SET finished_copy=1;'
        #delete obsolete entries in copy_jobs table
        sql += 'DELETE from copy_jobs where config_id=%d' %config_id
    else:#unknown subprocess
        return
    #execute query
    _query(sql)
    
    
#def mark_config_as_finished(info):
#    sql = 'Insert into config_files (finished) VALUES (1) where config_id=%(config_id)' % info
#    _query(sql)
    
def delete_copy_request(config_id):
    sql = 'DELETE from copy_jobs where config_id = %s' % config_id
    _query(sql)

#update job status of oll not finished configs
#def update_dashboard(config_ids):
##    sql = 'select id from config_files where (finished_grid <>1 OR finished_grid is NULL) AND not dashlink is NULL'
##    ids = _query(sql)
#    for id in config_ids:
#        link = get_dashboard_link(id)
#        _update_jobs(dashboard.get_job_status(link), id)
    
def getNotFinishedGridConfigs(): 
    sql = 'select id from config_files where (finished_grid <>1 OR finished_grid is NULL) AND not dashlink is NULL'
    ids = _query(sql)
    #convert to list
    ret = []
    for i in ids:
        ret.append(i[0])
    return ret
   
def _format_dataset(res):
    samples = []
    for s in res:
        sample = {}
        sample['name'] = s[0]
        sample['luminosity'] = s[1]
        sample['twiki_page'] = s[2]
        sample['primType'] = s[3]
        samples.append(sample)
    return samples

def get_jobs_by_cid(info):
    sql = 'SELECT config_id, id, status from dashboard where config_id=%(id)d limit 0,%(limit)d' % info
    jobs = _query(sql)
    selected_jobs = []
    for job in jobs:
        j = {}
        j['id'] = job[1]
        j['config_id'] = job[0]
        j['status'] = job[2]
        selected_jobs.append(j)
    return selected_jobs 

def get_datasets_in_progress():
#    sql = 'SELECT DBS_sample_id from config_files where finished_grid=1 AND finished_copy=1'
    sql = """SELECT DBS_sample_id from config_files where (finished_grid<>1 or finished_grid is NULL)
            AND (finished_copy <>1 OR finished_copy is NULL);"""
    sql_ds = 'SELECT name, luminosity, twiki_page, primType from dbs_samples where id IN (%s)'
    ids = _query(sql)
    ids = [x[0].__str__() for x in ids]
    ids = ','.join(ids)
    sql_ds = sql_ds % ids
    res = _query(sql_ds)
    samples = _format_dataset(res)
    return samples
    
