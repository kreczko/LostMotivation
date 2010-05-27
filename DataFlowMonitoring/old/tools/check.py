'''
Created on Oct 13, 2009

@author: lkreczko
'''
from ROOT import TChain, TFile
def files(dir):
    #print "Enter the full path to the ntuples to be checked: "
    #dir = "~/store/summer09_10TeV_3/zee";
    dir = dir
  
    chain = TChain("configurableAnalysis/eventB")
    nfile0 = chain.Add("%s/*root" % dir)
    print "%s/*root" % dir
    print "Total number of files:   " , nfile0
    nTotalEvent = chain.GetEntries() ;
    print "Total number of events in chain: " , nTotalEvent
    fileElements = chain.GetListOfFiles();
    #TIter next(fileElements);
    #TChainElement *chEl=0;


    f = None
    flag_bad = False;
    nfile = 0;
    nbad = 0;
    bad_list =[]
    
    for chEl in fileElements:
        print "+++++++++++++++++++++++++++++++++++++++++++"
        fname = chEl.GetTitle()
        nfile+=1
        flag_bad = False ;#default assume file is good
        f = TFile.Open(fname);
        if not f:
            print " Error opening file"
            flag_bad = True;
        else:
            print fname,":  ", chEl.GetEntries()," events. "
            print "Check eventB: ",
            t = f.Get("configurableAnalysis/eventB");
            if not t:
                print "Not Ok",
                flag_bad = True;
            else:
                print "Ok",
            #Thirdly check eventV
            print ", eventV: ",
            t2 = f.Get("configurableAnalysis/eventV");
            if( t2 ):
                print "Ok"; 
            else:
                print "Not Ok";
                flag_bad = True;
        f.Close();
    
        if flag_bad:
            nbad+=1
            bad_list.append(fname);
            print "  BAD FILE! Should remove."
    print "=============================================="
    print "Total number of files: " ,nfile
    print "Number of invalid files: ",nbad
    print "Total number of events in chain: ",nTotalEvent
    print "List of invalid files:"
    for i in bad_list:
        print i
        
if "__main__" in __name__:
    files("/storage/OctEx09/SD/enri3")
