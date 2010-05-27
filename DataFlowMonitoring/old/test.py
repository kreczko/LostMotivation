'''
Created on Dec 1, 2009

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch
'''
import sys, os
from mod_python import apache
_currentdir = os.path.dirname(__file__)
_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))

def index(req):
    if 'test' in req.form.keys():
        str = req.form['test']
        f = open(_currentdir + '/configs/test.txt', 'w')
        f.write(str)
        f.close()
    return _currentdir + '<br>' + _applicationRoot + '<br>' + _applicationRoot + 'test.txt'

def tt(req):
    if 'test' in req.form.keys():
        str = req.form['test'] + "\nyes///thioksdflk"
        f = open(_currentdir + 'configs/test.txt', 'w')
        f.write(str)
        f.close()
    return 'successfull\n'




