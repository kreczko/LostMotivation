'''
Created on 2 Jun 2010

@author: kreczko

Email: kreczko@cern.ch
'''

def getText(nodelist):
    text = []
    for node in nodelist.childNodes:
        if node.nodeType == node.TEXT_NODE:
            text.append(node.data)
    return ''.join(text)

def getSubNode(node, subNodeTag):
    return getSubNodes(node, subNodeTag)[0]

def getSubNodes(node, subNodeTag):
    return node.getElementsByTagName(subNodeTag)