#sg
import sys
import os.path
from mat import createMatrices
'''General notations : 
    cw => correct word
    icw => incorrect word
'''
class Kernighan:
    wordSet = set([])
    matrixDict = {}
    fdist = {}
    def __init__(self):
        self.wordSet = self.makeSet("../data/wordlist.txt")
        self.matrixDict = createMatrices("se.txt", 0)
        self.fdist = self.frequencyDist("../data/big.txt")
         
    def makeSet(self, fileName):
        return set(line.strip() for line in open(str(fileName)))
    
    def frequencyDist(self, fileName):
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
    '''
    generates all the words at edit distance of 1
    copy pasted from norvig.com/spell.
    This function returns a dictionary of sets instead of a set as in original
    My implementation in c++ can be found in edb/
    '''
    def edits1(self, word):
       alphabet = 'abcdefghijklmnopqrstuvwxyz'
       splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
       deletes    = [a + b[1:] for a, b in splits if b]
       transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
       substitutions = [a + c + b[1:] for a, b in splits for c in alphabet if b]
       inserts    = [a + c + b     for a, b in splits for c in alphabet]
       return {'del' : set(deletes), 'trans' : set(transposes), 'subs' : set(substitutions), 'ins' : set(inserts)}
    
    
    def correction(self, iw):
    #This function returns the correction upon receiving an incorrect word
        candidatesDict = self.edits1(iw)
        results = {}
        for k in candidatesDict.keys():
            if(iw in candidatesDict[k]):
                candidatesDict[k].remove(iw)
        
        findFuncs = {'subs':self.findSubstituionChar, 'trans':self.findTranspositionChar, 'del':self.findInsertionChar,
                    'ins':self.findDeletionChar}
    
        operations  = ['subs', 'trans', 'del', 'ins']
        total = 0
        for i in operations:
            for word in candidatesDict[i]:
                
                if(word in self.wordSet): #if the proposed correction is at all an English word
                    index = findFuncs[i](word, iw)
                    bigram = index[0] + index[1]
                    ri = ord(index[0]) - 97
                    ci = ord(index[1]) - 97
                    operP = self.matrixDict[i][ri][ci]
                    prior = self.fdist[word]
                    results[word] = prior * operP
                    total += prior * operP
                    #print word, operP, prior, prior * operP
        if(len(results) == 0):
            return "nothing"    
        return max(results, key = results.get)
    
    def loadFrequencyFile(self, fileName):
        for line in open(str(fileName)):
            dist[line]
    
    def createfrequencydistfile(self, wordfilename, ofilename):
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
    
    def findDeletionChar(self, cw, icw):
        i = 0
        while(i < len(icw) and cw[i] == icw[i]):
            i += 1
        #now cw[i] is the character that was deleted
        #it should have been icw[i - 1], icw[i] but was instead just icw[i]
        return [cw[i - 1], cw[i]]
    
    def findInsertionChar(self, cw, icw):
        return self.findDeletionChar(icw, cw) #attr Naman 
    
    def findSubstituionChar(self, cw, icw):
        i = 0
        while(i < len(cw) and cw[i] == icw[i]):
            i += 1
        if(i == len(cw)):
            return ['0', '0']
    
        return [cw[i], icw[i]]
    
    def findTranspositionChar(self, cw, icw):
        i = 0
        while(cw[i] == icw[i]):
            i += 1
        #the point of mismatch tells us about first point of conflict
        #now, cw[i], cw[i + 1] has been typed as icw[i], icw[i + 1]
        return [cw[i], cw[i + 1]]

