cf = open("kc.txt", "r")
af = open("asout.txt", "r")
adict = {}
cdict = {}

for line in af:
    icw = (line.split(" ")[0]).lower().strip()
    cw = (line.split(" ")[1]).lower().strip()
    adict[icw] = cw

for line in cf:
    icw = (line.split(" ")[0]).lower().strip()
    cw = (line.split(" ")[1]).lower().strip()
    cdict[icw] = cw

total = 0
hit = 0
for w in adict.keys():
    total = total + 1
    if(adict[w] == cdict[w]):
        hit = hit + 1
print float(hit) / total
