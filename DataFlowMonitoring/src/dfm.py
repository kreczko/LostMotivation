'''
Created on 28 May 2010

@author: kreczko
'''
import sys
sys.stdout = sys.stderr

import atexit
#import threading
import cherrypy

cherrypy.config.update({'environment': 'embedded'})

if cherrypy.__version__.startswith('3.0') and cherrypy.engine.state == 0:
    cherrypy.engine.start(blocking=False)
    atexit.register(cherrypy.engine.stop)
    

class DataFlowApplication(object):
    def index(self):
        return "Under Construction"
    index.exposed = True
    
application = cherrypy.Application(DataFlowApplication(), script_name=None, config=None)