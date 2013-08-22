#sg
def edits1(word):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
    deletes    = [a + b[1:] for a, b in splits if b]
    transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
    substitutions = [a + c + b[1:] for a, b in splits for c in alphabet if b]
    inserts    = [a + c + b     for a, b in splits for c in alphabet]
    return inserts + deletes + transposes + substitutions;

def makeSet(fileName):
    return set(line.strip() for line in open(str(fileName)))
 
wordset = makeSet("../data/wordlist.txt")

kcfile = open("../data/kc.txt", "r")
bagOfWords = set([]) 

#the final list whose pronunciation is to be obtained

for line in kcfile:
    icw = (line.split(" ")[0]).lower().strip()
    ws = edits1(icw)
    bagOfWords.add(icw)
    for w in ws:
        if(w in wordset):
            bagOfWords.add(w)

for word in bagOfWords:
    print word
