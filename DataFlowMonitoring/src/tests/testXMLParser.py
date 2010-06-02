'''
Created on 2 Jun 2010

@author: kreczko

Email: kreczko@cern.ch
'''
import unittest
from xml.dom.minidom import parseString
from tools import XMLParser

class TestXMLParser(unittest.TestCase):
    
    def setUp(self):
        self.containedString = 'Something'
        self.xmlString = "<text>%s</text>" % self.containedString
        self.xml = parseString(self.xmlString)
        self.textNode = self.xml.getElementsByTagName('text')
        
    def testGetText(self):
        self.assertEquals(self.containedString, XMLParser.getText(self.textNode[0]))
    
    def testGetSubNodes(self):
        self.assertEquals(len(self.textNode), len(XMLParser.getSubNodes(self.xml, 'text')))
        
    def testGetSubNode(self):
        self.assertEquals(self.containedString,  XMLParser.getText(XMLParser.getSubNode(self.xml, 'text')))