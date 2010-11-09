#!/env

import os
import sys
import glob

def getFiles(path):
    path += "/*.root"
    files = glob.glob(path)
    return files

def groupFilesToSize(files, finalSize = 1024*1024*1024*2):# < 3 GB
    groupSize = 0
    groups = [[]]
    groupIndex = 0
    for file in files:
        size = os.path.getsize(file)
        if (groupSize + size) > finalSize:#start new group
            groupIndex += 1
            groups.append([])
            groupSize = 0
        groupSize += size    
        groups[groupIndex].append(file)
    return groups

def fuseFiles(groupedFiles):
    group = 1
    
    for files in groupedFiles:
        outputFile = getProcess(files[0]) + '_merged_%d' % group
        outputFile += '.root'
        command = 'hadd -f7 %s ' % outputFile
        for file in files:
            command += file + ' '
        command.rstrip(' ')
        print 'Executing:'
        print command
        os.system(command)
        group += 1

def getProcess(filepath):
    file = filepath.split('/')[-1]
    a = file.split('_')
    process = a[0] + '_' + a[1] + '_' + a[2]
    return process

    
if __name__ == "__main__":
    args = sys.argv
    if not len(args) == 2:
        print "Please specify a folder to merge files in."
        sys.exit()
        
    path = sys.argv[1]
    files = getFiles(path)
    groupedFiles = groupFilesToSize(files)
    print 'Total number of files:', len(files)
    print 'Process recognised:', getProcess(files[0])
    print 'Input files per output file:', len(groupedFiles)
    fuseFiles(groupedFiles)