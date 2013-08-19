#sg
 
import string
def isLegal(s):
    for c in s:
        if c not in string.ascii_letters:
            return False
    return True

def tester(testFilePath):
    from kernighan import Kernighan
    k = Kernighan()
    testerFile = open(testFilePath, "r")
    correctWord = ""
    totalTest = 0 #total incorrect words tested
    hits = 0 #number of incorrect words corrected
    for line in testerFile: #for each line in testfile
        cw = line.split(":")[0].strip(); #split the line on ':'
        incorrectWordList = (line.split(":")[1]).split(", "); #get the incorrections
        for icw in incorrectWordList: #for each icw in list
            icw = icw.strip().lower() 
            if(isLegal(icw) == False or k.correction(icw) == "nothing"):
                continue
            totalTest = totalTest + 1
 #           print "%s -> %s  (%s)" % (icw, k.correction(icw), cw.lower())
            if(k.correction(icw) == cw): #find the correction
                hits = hits + 1
                
    print float(hits) / totalTest

def tester1(testFilePath):
    from kernighan import Kernighan
    k = Kernighan()
    testerFile = open(testFilePath, "r")
    correctWord = ""
    totalTest = 0 #total incorrect words tested
    hits = 0 #number of incorrect words corrected
    for line in testerFile: #for each line in testfile
        ws = line.split(' ')
        if(len(ws) != 2):
            continue
        icw = ws[0].strip().lower()
        cw = ws[1].strip().lower()
        icw = icw.strip().lower() 
        if(isLegal(icw) == False or k.correction(icw) == "nothing"):
            continue
        totalTest = totalTest + 1
 #           print "%s -> %s  (%s)" % (icw, k.correction(icw), cw.lower())
        if(k.correction(icw) == cw): #find the correction
            hits = hits + 1
    print float(hits) / totalTest
tester1("testbed/kc.txt")
