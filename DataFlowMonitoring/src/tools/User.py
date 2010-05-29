'''
Created on 29 May 2010

@author: kreczko
'''

class User(object):
    storage_path_userarea = '/store/user/'
    
    def __init__(self, name):
        if name == '':
            raise ValueError
        self.__name = name
        self.__SEPath = ''
        
    
    def setPreferredStorageElementPath(self, path):
        if path == '':
            raise ValueError('Tried to set empty Preferred Storage Element Path')
        elif not path.startswith(User.storage_path_userarea):
            raise ValueError('Specified Storage Element Path is not in user area')
        self.__SEPath = path
        
    def getName(self):
        return self.__name
    
    def getPreferredStorageElementPath(self):
        if self.__SEPath == '':
            raise ValueError('Preferred Storage Element Path is not set.')
        return self.__SEPath