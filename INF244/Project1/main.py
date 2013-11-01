import sys
import random
import math
import itertools

#Generate random numbers according to gaussian distribution using box-muller method
def genAWGN():

    while True:
        u = random.uniform(-1,1)
        v = random.uniform(-1,1)
        ##print "u:" + str(u) + "v:" + str(v)
        
        s = u**2 + v**2
        ##print "s:" + str(s)

        z0 = 0
        z1 = 0
        if not (s == 0 or s == 1 or s > 1):
            z0 = u * math.sqrt((-2*math.log(s)/s))
            z1 = v * math.sqrt((-2*math.log(s)/s))
            break

        #print str(z0) + " " + str(z1)

    #We only need one sample so we just pick z0
    return z0

###################
#####  MAIN  ######
###################

with open(sys.argv[1]) as f:
    lines = []
    for line in f:
        lines.append(line)
    lines = [line.rstrip('\n') for line in lines]
    lines = iter(lines)

noVars = int(lines.next())
noStateVars = int(lines.next())
noFuncs = int(lines.next())

#print lines
funcs = []
for i in xrange(0,noFuncs):
    funcs.append(lines.next())

funcs = [(x.split(']')[0].lstrip('['),x.split(']')[1]) for x in funcs] 
#print funcs


boolFuncTT = []
singleVars = []
for i in funcs:
#print i
    if i[1] == "G":
        singleVars.append(int(i[0]))
    else:
        tmp = map(int, i[0].split(','))
        tmp.append(map(int,i[1].split(',')))
        boolFuncTT.append(tmp)

print boolFuncTT
print singleVars

for i in boolFuncTT:
    n = len(i)-1
    print "Printing truth table for " + str(i)
    it = itertools.product([0,1], repeat=n)
    ind = 0
    for j in it:
        print str(j[::-1]) + " " + str(i[len(i)-1][ind])
        ind += 1

decMode = lines.next()

print "DecMode is: " + decMode

noIterations = noIndepDec = codeRate = bitEnergy = noise = root = msgPassVariant = 0
if decMode == "A":
    noIterations = int(lines.next())
    noIndepDec = int(lines.next())
    codeRate = float(lines.next())
    bitEnergy = float(lines.next())
    noise = float(lines.next())
elif decMode == "B":
    root = lines.next()
elif decMode == "C":
    msgPassVariant = lines.next()
    noIndepDec = int(lines.next())
    codeRate = float(lines.next())
    bitEnergy = float(lines.next())
    noise = float(lines.next())

'''
for i in range(0,100):
    z = math.sqrt(noise/2.0)*genAWGN()
    print z
'''

