#sg
#This script creates the subs matrix
#note on scoring :
#The value subs[x, y] is the number of times x was wrongly typed as y.
#Egsuppose we have "affort" wrongly typed as "afforr" will cause subs[t, r] += 1
#the value trans[x, y] is the number of times "xy" was written as "yx".
#Eg, "would" typed as "woudl" will cause trans[l][d] += 1
correctionFile = open("kc.txt", "r")

de = [[0 for i in range(26)] for j in range(26)]

for correctionEntry in correctionFile:
    correctionEntry = correctionEntry.strip().lower()
    ce  = correctionEntry.split(' ')
    
    if(len(ce) == 2): #there are 2 elements in the list
         '''i,j element of the deletion matrix dl stores the number of times
         i was written instead of ij'''

         if(len(ce[1]) > len(ce[0])): #correct word is longer, deletion happened
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





for i in range(26):
    print de[i]








