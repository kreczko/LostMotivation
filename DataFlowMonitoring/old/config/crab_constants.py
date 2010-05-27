'''
Created on Nov 4, 2009

@author: lkreczko
'''
#------------------------------------------------------------------------------ 
# CRAB
#------------------------------------------------------------------------------ 
crab = {}
crab['jobtype'] = "cmssw"
crab['scheduler'] = "glite"
#crab server, change?
crab['server_name'] = "cern"


#------------------------------------------------------------------------------ 
# CMSSW
#------------------------------------------------------------------------------
#Datasetpath = not a constant
#pset = not a constant
cmssw = {}
cmssw['total_number_of_events'] = -1
cmssw['events_per_job'] = 10000 # as suggested for OctX
cmssw['pset'] = 'cmssw.py'
#output_file = not a constant
 
#------------------------------------------------------------------------------ 
# USER
#------------------------------------------------------------------------------ 
user = {}
user['storage_element'] = "lcgse02.phy.bris.ac.uk"
user['storage_path'] = "/srm/managerv2?SFN=/cms"
user['storage_port'] = 8444
user['thresholdlevel'] = 50
user['email'] = "kreczko@cern.ch"
user['return_data'] = 0
user['use_central_bossDB'] = 0
user['use_boss_rt'] = 0
user['copy_data'] = 1
#------------------------------------------------------------------------------ 
# GRID
#------------------------------------------------------------------------------ 
grid = {}
grid['rb'] = "CERN"
grid['proxy_server'] = "myproxy.cnaf.infn.it"
grid['virtual_organization'] = "cms"
grid['retry_count'] = 10
grid['lcg_catalog_type'] = 'lfc'
grid['lfc_host'] = 'lfc-cms-test.cern.ch'
grid['lfc_name'] = '/grid/cms'
#useful for analysis
#grid['se_white_list'] = ''
#grid['ce_White_List'] = '' 

#------------------------------------------------------------------------------ 
# specific
#------------------------------------------------------------------------------ 
Filename_Prefix = "S9nTuple"
STD_config_path = '../../files/std.cfg'
nTuple_Version_prefix = "nTuple"
User_Remote_Dir_Base = "/store/user"
destination_mc = "/storage/top/mc/"
destination_data = "/storage/top/data"

raw_cmssw_cfg = """
import FWCore.ParameterSet.Config as cms
# import the PatTuple sequence
from Workspace.ConfigurableAnalysis.FBtestFromAOD_cfg import *
# rename output file
process.TFileService.fileName = '%(filename)s'
"""