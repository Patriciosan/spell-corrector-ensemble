#sg
#This script creates the subs matrix
#note on scoring :
#The value subs[x, y] is the number of times x was wrongly typed as y.
#Egsuppose we have "affort" wrongly typed as "afforr" will cause subs[t, r] += 1
#the value trans[x, y] is the number of times "xy" was written as "yx".
#Eg, "would" typed as "woudl" will cause trans[l][d] += 1
correctionFile = open("kc.txt", "r")

subs = [[0 for i in range(26)] for j in range(26)]
trans = [[0 for i in range(26)] for j in range(26)]
de = [[0 for i in range(26)] for j in range(26)]
ins = [[0 for i in range(26)] for j in range(26)]

for correctionEntry in correctionFile:

    correctionEntry = correctionEntry.strip().lower()
    ce  = correctionEntry.split(' ')
    
    if(len(ce) == 2): #there are 2 elements in the list
        
        if (len(ce[0]) == len(ce[1])): #lengths equal? : either substitution or xposition (Assuming that either of the 4 errors happens at a time)
            
            #test for substitution

            for i in range(len(ce[1])): #iterate through characters and find out same characters
                if(ce[1][i] != ce[0][i]): #some character substituted
                    ri = ord(ce[1][i]) - 97 #row index
                    ci = ord(ce[0][i]) - 97 #column index
                    #print ri, ci
                    if(ri <= 25 and ri >= 0 and ci <= 25 and ci >= 0): #avoiding unicode
                        subs[ri][ci] += 1

            #test for transposition
            
            for i in range(len(ce[1]) - 1):
                #we test if ci,ci+1 has been typed as ci+1,ci 
                if(ce[1][i] == ce[0][i + 1] and ce[1][i + 1] == ce[0][i]): #Xposition detected
                    ri = ord(ce[1][i]) - 97 #row index
                    ci = ord(ce[1][i + 1]) - 97 #column index
                    #print ri, ci
                    if(ri <= 25 and ri >= 0 and ci <= 25 and ci >= 0): #avoiding unicode
                        trans[ri][ci] += 1

        elif(len(ce[1]) > len(ce[0])): #correct word is longer, deletion happened
            '''i,j element of the deletion matrix dl stores the number of 
            times i was written instead of ij'''
            i = 0
            #skip the common prefix
            while( i < len(ce[0]) and ce[0][i] == ce[1][i]):
                i += 1
                #in *any* case, ce[1][i] now refers to the deleted character
                ri = ord(ce[0][i - 1]) - 97 #row index
                ci = ord(ce[1][i]) - 97 #column index
                '''now i points to the character that was deleted
                so, ce[0][i - 1] was written instead of ce[1][i - 1],ce[1][i]'''
                if(ri >= 0 and ri <= 25 and ci >= 0 and ci <= 25):
                    de[ri][ci] += 1
        
        else: #length of incorrect word is longer than correct word, insertion
            '''i,j element of the deletion matrix dl stores the number of 
            times i was written instead of ij'''
            i = 0
              #skip the common prefix
              
            while( i < len(ce[1]) and ce[0][i] == ce[1][i]):
                i += 1
                '''in *any* case, ce[0][i] now refers to the inserted character
                We should have typed ce[0][i - 1] only, but we have written ce[0][i]
                '''
                ri = ord(ce[0][i - 1]) - 97 #row index
                ci = ord(ce[0][i]) - 97 #column index
                '''now i points to the character that was deleted
                so, ce[0][i - 1] was written instead of ce[1][i - 1],ce[1][i]'''
                if(ri >= 0 and ri <= 25 and ci >= 0 and ci <= 25):
                    ins[ri][ci] += 1
        
 




for i in range(26):
        print subs[i]
for i in range(26):
        print trans[i]
for i in range(26):
        print de[i]
for i in range(26):
        print ins[i]
