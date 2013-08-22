#sg
def makeSet(fileName):
    return set(line.strip() for line in open(str(fileName)))

pdict = {}
for line in open("data/dic/pdic.dic"):
    wl = line.split(" ")
    if(len(wl) != 2):
        print wl
        continue
    pdict[wl[0]] = wl[1]

def makeSet(fileName):
    return set(line.strip() for line in open(str(fileName)))


def pronuncMatch(p1, p2):
    total = 0
    for i in range(len(p1)):
        pl = 0
        while((i < len(p2)) and (i < len(p1)) and (p1[i] == p2[i])):
            pl = pl + 1
            i = i + 1
        total = total + pl * pl
    return total


#start testing
def edits1(word):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
    deletes    = [a + b[1:] for a, b in splits if b]
    transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
    substitutions = [a + c + b[1:] for a, b in splits for c in alphabet if b]
    inserts    = [a + c + b     for a, b in splits for c in alphabet]
    return set(inserts + deletes + transposes + substitutions)

def isecLen(l1, l2):
    from collections import defaultdict
    d = defaultdict(int) 
    total = 0
    for ll1 in l1:
        for ll2 in l2:
            if(ll1 == ll2):
                d[ll1] = d[ll1] + 1    
    return total
wordFile = open("../data/kc.txt", "r")
wordSet = makeSet("../data/wordlist.txt")
total = 0
hits = 0
inLoop = 0
for line in wordFile:
    inLoop = 0
    icw = (line.split(" ")[0]).lower().strip()
    cw = (line.split(" ")[1]).lower().strip()
    corrections = edits1(icw)
    if(icw in corrections):
        corrections.remove(icw)
    theCorr = ''
    #scan and find the best match
    l = 0
    for correction in corrections:
        proicw = pdict[icw].replace("\n", "").split('.')
        if(correction in wordSet): #no need to check dictionary again
            inLoop = 1
            procw = pdict[correction].split('.')
            #isectP = set(proicw).intersection(set(procw))
            #lr = len(isectP)
            #lr = isecLen(proicw, procw) 
            #print lr, len(isectP)
            #if(len(isectP) >= l):
            lr = pronuncMatch(proicw, procw)
            #print ("%d, %d, %d") %(lr, lr2, len(isectP))
            if(lr >= l):
                l = lr
                #l = len(isectP)
                theCorr = correction
    if(inLoop != 0):
        total = total + 1
    #see if the match is a hit
    if(theCorr == cw):
        hits = hits + 1
    else:
        hits = hits + 0
        #print "%s => %s != %s" % (icw, cw, theCorr)

print (float(hits) / total) * 100
print total
