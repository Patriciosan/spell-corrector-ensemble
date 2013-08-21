#sg
 
import string
def isLegal(s):
    for c in s:
        if c not in string.ascii_letters:
            return False
    return True

def tester(trainFile, testFilePath):
    from kernighan import Kernighan
    k = Kernighan(trainFile)
    testerFile = open(testFilePath, "r")
    correctWord = ""
    totalWords = 0 #total incorrect words tested
    hits = 0 #number of incorrect words corrected

    for line in testerFile: #for each line in testfile
        cw = line.split(":")[0].strip().lower() #split the line on ':'
        incorrectWordList = (line.split(":")[1]).split(","); #get the incorrections
        for icw in incorrectWordList: #for each icw in list
            icw = icw.strip().lower() 
            if(isLegal(icw) == False):
                continue
            res = k.correction(icw)
            if(res == "nothing" or res == "dw"): #incorrection a dictionary word
                continue
            totalWords = totalWords + 1
           # print "%s -> %s  (%s)" % (icw, k.correction(icw), cw.lower())
            if(res == cw): #find the correction
                hits = hits + 1
                
    print float(hits) / totalWords

def tester1(trainFile, testFilePath):
    from kernighan import Kernighan
    k = Kernighan(trainFile)
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
        if(isLegal(icw) == False):
            continue
        res = k.correction(icw)
        if(res == "nothing" or res == "dw"): #incorrection a dictionary word
            continue
        totalTest = totalTest + 1
       # print "%s -> %s  (%s)" % (icw, k.correction(icw), cw.lower())
        if(res == cw): #find the correction
            hits = hits + 1
    return float(hits) / totalTest


testFiles = ["data/test1.txt", "data/test2.txt", "data/test3.txt", "data/test4.txt", "data/test5.txt"]
trainFiles = ["data/train1.txt", "data/train2.txt", "data/train3.txt", "data/train4.txt", "data/train5.txt"]
total = float(0)
for i in range(0,5):
    temp = tester(testFiles[i], trainFiles[i])
    total = total + temp 
print "Average : %f" % float(total) / 5
#tester1("data/se.txt", "data/kc.txt")
