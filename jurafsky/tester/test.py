#sg
def tester(testFilePath):
    testerFile = open(testFilePath, "r")
    correctWord = ""
    totalTest = 0 #total incorrect words tested
    hits = 0 #number of incorrect words corrected
    for line in testerFile: #for each line in testfile
        cw = line.split(":")[0].trim(); #split the line on ':'
        incorrectWordList = (line.split(":")[1]).split(", "); #get the incorrections
        for icw in incorrectWordList: #for each icw in list
            totalTest = totalTest + 1
            icw = icw.trim() 
            if(corrector(icw) == cw): #find the correction
                hits = hits + 1
                
    return float(hits) / totalTest



