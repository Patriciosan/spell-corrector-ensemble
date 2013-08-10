#sg
import sys
import os.path
from mat import createMatrices
'''General notations : 
    cw => correct word
    icw => incorrect word
'''

'''
creates a set out of list of words
'''
def makeSet(fileName):
    return set(line.strip() for line in open(str(fileName)))

'''
generates all the words at edit distance of 1
copy pasted from norvig.com/spell.
This function returns a dictionary of sets instead of a set as in original
My implementation in c++ can be found in edb/
'''
def frequencyDist(fileName):
    from collections import defaultdict
    dist = defaultdict(float)
    total = 0
    for line in open(str(fileName)):
        for w in line.split(' '):
            total += 1 #total words
            dist[w.strip().lower()] += 1
    for word in dist.keys():
        dist[word] = dist[word] / total
    
    return dist

def edits1(word):
   alphabet = 'abcdefghijklmnopqrstuvwxyz'
   splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
   deletes    = [a + b[1:] for a, b in splits if b]
   transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
   substitutions = [a + c + b[1:] for a, b in splits for c in alphabet if b]
   inserts    = [a + c + b     for a, b in splits for c in alphabet]
   return {'del' : set(deletes), 'trans' : set(transposes), 'subs' : set(substitutions), 'ins' : set(inserts)}


def main(argv):
    suggestedSentence = ''
    wordSet = makeSet("../data/wordlist.txt")
    matrixDict = createMatrices("se.txt")
    char = matrixDict['char']
    charBi = matrixDict['charBi']
    fdist = frequencyDist("../data/big.txt")
    '''if(!os.path.isfile("fdist.txt")):
        createFrequencyDistFile("../data/big.txt", "fdist.txt")

    The candidates dict has a set for each type of mistakes that can happen'''
    for iw in argv[1:]:
        candidatesDict = edits1(iw)
        results = {}
        for k in candidatesDict.keys():
            if(iw in candidatesDict[k]):
                candidatesDict[k].remove(iw)

        findFuncs = {'subs':findSubstituionChar, 'trans':findTranspositionChar, 'del':findInsertionChar,
                    'ins':findDeletionChar}

        index  = ['subs', 'trans', 'del', 'ins']
        total = 0
        for i in index:
            for word in candidatesDict[i]:
                if(word in wordSet):
                    index = findFuncs[i](word, iw)
                    bigram = index[0] + index[1]
                    ri = ord(index[0]) - 97
                    ci = ord(index[1]) - 97
                    operP = matrixDict[i][ri][ci]
                    prior = fdist[word]
                    results[word] = prior * operP
                    total += prior * operP
                    #print word, operP, prior, prior * operP
        dispResults(results, fdist, total)
        suggestedSentence += (max(results, key = results.get) + ' ')
    
    print suggestedSentence




def loadFrequencyFile(fileName):
    for line in open(str(fileName)):
        dist[line]

def createfrequencydistfile(wordfilename, ofilename):
    from collections import defaultdict
    dist = defaultdict(float)
    total = 0
    for line in open(str(wordfilename)):
        for w in line.split(' '):
            total += 1 #total words
            dist[w.strip().lower()] += 1
    for word in dist.keys():
        dist[word] = dist[word] / total
    for k in dist.keys():
        print "%s %20f\n" %(k, dist[k])
    ffile = open(ofilename, 'w+')
    ffile.write(str(dist))
    ffile.close()
    return dist 

def dispResults(results, fdist, total):

    print "\n\n%-10s %-20s %-20s %-20s%-20s\n" %("Word", "p(c|w)", "p(w)", "p(w) * p(c|w)", "Score") 
    for k in sorted(results, key = results.get, reverse = True):
        prior = fdist[k]
        pro = results[k]
        if(prior == 0):
            continue
        print "%-10s %-.15f %-.15f %-.15f %-.5f %%"  %(k, pro / prior, prior, results[k], (results[k] / total) * 100)
    print '\n\n'
def findDeletionChar(cw, icw):
    i = 0
    while(i < len(icw) and cw[i] == icw[i]):
        i += 1
    #now cw[i] is the character that was deleted
    #it should have been icw[i - 1], icw[i] but was instead just icw[i]
    return [cw[i - 1], cw[i]]

def findInsertionChar(cw, icw):
    return findDeletionChar(icw, cw) #attr Naman 

def findSubstituionChar(cw, icw):
    i = 0
    while(i < len(cw) and cw[i] == icw[i]):
        i += 1
    if(i == len(cw)):
        return ['0', '0']

    return [cw[i], icw[i]]

def findTranspositionChar(cw, icw):
    i = 0
    while(cw[i] == icw[i]):
        i += 1
    #the point of mismatch tells us about first point of conflict
    #now, cw[i], cw[i + 1] has been typed as icw[i], icw[i + 1]
    return [cw[i], cw[i + 1]]

if __name__ == "__main__":
    main(sys.argv[0:])
