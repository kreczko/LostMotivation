'''
Created on 29 May 2010

@author: kreczko
'''
import unittest
from tools.User import User

class TestUser(unittest.TestCase):

    def setUp(self):
        self.emptyString = ''
        self.username = 'Lukasz Kreczko'
        self.preferredStorageElementPath = '/store/user/kreczko/'
        self.storageElementPathWithoutEndingSlash = '/store/user/kreczko'
        self.invalidStorageElementPath = '/kreczko'
        
        self.validUser = User(self.username)
        self.validUser.setPreferredStorageElementPath(self.preferredStorageElementPath)
        
        self.invalidUser = User(self.username)
        
    def testSetUserInvalidNameRaisesException(self):
        self.failUnlessRaises(ValueError, self.validUser.setName, '')
        
    def testGetPreferredStorageElementPathNotSetRaisesException(self):
        self.failUnlessRaises(ValueError, self.invalidUser.getPreferredStorageElementPath)
        
    def testSetPreferredStorageElementPathInvalidPathRaisesException(self):
        self.failUnlessRaises(ValueError, self.validUser.setPreferredStorageElementPath, self.invalidStorageElementPath)
        self.failUnlessRaises(ValueError, self.validUser.setPreferredStorageElementPath, '')
        
    def testGetUsername(self):
        self.assertEquals(self.username, self.validUser.getName())
        
    def testAutomaticCorrectionforSetPreferredStorageElementPath(self):
        self.validUser.setPreferredStorageElementPath(self.storageElementPathWithoutEndingSlash)
        self.assertEquals(self.preferredStorageElementPath, self.validUser.getPreferredStorageElementPath())
        
    def testIsValidUser(self):
        self.assertTrue(self.validUser.isValid())
        self.assertFalse(self.invalidUser.isValid())
        
    def testIsValidUsername(self):
        self.assertTrue(User.isValidName('myname'))
        self.assertFalse(User.isValidName(''))
        self.assertFalse(User.isValidName('   '))
        self.assertFalse(User.isValidName(None))
        
    def testIsValidStorageElementPath(self):
        self.assertTrue(User.isValidStorageElementPath(self.preferredStorageElementPath))
        self.assertTrue(User.isValidStorageElementPath(self.storageElementPathWithoutEndingSlash))
        self.assertFalse(User.isValidStorageElementPath(''))
        self.assertFalse(User.isValidStorageElementPath(None))
        self.assertFalse(User.isValidStorageElementPath('    '))
        self.assertFalse(User.isValidStorageElementPath('/storage'))
        