'''
Created on 27 May 2010

@author: kreczko
'''
import cherrypy
class DataFlowApplication:

    def index(self):
        return "This an example"
    index.exposed = True
    

import os.path
tutconf = os.path.join(os.path.dirname(__file__), 'dfm.conf')

if __name__ == '__main__':
    cherrypy.quickstart(DataFlowApplication(), config=tutconf)
else:
    cherrypy.tree.mount(DataFlowApplication(), config=tutconf)