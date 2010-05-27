'''
Created on Nov 18, 2009

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch
'''
'''
Created on Nov 18, 2009

@author: Lukasz Kreczko

Email: Lukasz.Kreczko@cern.ch
'''
from mod_python import apache
import os

# Default directories to add to the path
_currentdir = os.path.dirname(__file__)
#===============================================================================
# Get the src directory
#===============================================================================
_applicationRoot = _currentdir.rstrip(os.path.basename(_currentdir))


def load(module):
    """
    Loads a module with the apache import function from subfolders
    """
    mod =module.split(".")
    return apache.import_module(mod[1], path=[_applicationRoot + mod[0]])
