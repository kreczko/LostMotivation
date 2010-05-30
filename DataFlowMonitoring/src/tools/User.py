'''
Created on 29 May 2010

@author: kreczko
'''

class User(object):
    storage_path_userarea = '/store/user/'
    
    def __init__(self, name):
        self.__name = name
        self.__SEPath = ''
        
    
    def setPreferredStorageElementPath(self, path):
        if path == '':
            raise ValueError('Tried to set empty Preferred Storage Element Path')
        elif not path.startswith(User.storage_path_userarea):
            raise ValueError('Specified Storage Element Path is not in user area')
        
        if not path.endswith('/'):
            path += '/'
        self.__SEPath = path
        
    def getName(self):
        return self.__name
    
    def setName(self, name):
        if not User.isValidName(name):
            raise ValueError('Trying to set empty user name')
        self.__name = name
    
    def getPreferredStorageElementPath(self):
        if self.__SEPath == '':
            raise ValueError('Preferred Storage Element Path is not set.')
        return self.__SEPath
    
    def isValid(self):
        return User.isValidName(self.__name) and User.isValidStorageElementPath(self.__SEPath)
    
    def isValidName(name):
        return not name is None and not name.strip() == ''
    isValidName = staticmethod(isValidName)
    
    def isValidStorageElementPath(path):
        return not path is None and not path == '' and path.startswith(User.storage_path_userarea)
    isValidStorageElementPath = staticmethod(isValidStorageElementPath)
