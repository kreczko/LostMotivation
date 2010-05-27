from subprocess import *
import sqlite3.dbapi2 as db

def ls(URL):
    output = "None"
    try:
        command = "lcg-ls %s" %URL
        output = Popen(command, shell=True, stdout=PIPE).communicate()[0]
    except OSError, e:
        print "Execution failed:", e
    return output

def copy(SE_URL, dest_URL):
    Popen("lcg-ls -l %s" %URL)
    
if "__main__" in __name__:
    files = ls("srm://lcgse02.phy.bris.ac.uk:8444/cms/store/user/OctEx09/SD/enri2/")
    