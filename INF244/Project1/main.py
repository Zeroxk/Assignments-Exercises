import os
import random
import math

global noIterations,noIndepDec,codeRate,bitEnergy,noise,root,msgPassVariant

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

with open('MP.txt') as f:
    lines = []
    for line in f:
        lines.append(line)
    lines = [line.rstrip('\n') for line in lines]

noVars = int(lines[0])
noStateVars = int(lines[1])
noFuncs = int(lines[2])

lines = lines[3:]
#print lines
funcs = []
for i in xrange(0,noFuncs):
    funcs.append(lines[i])

funcs = [(x.split(']')[0].lstrip('['),x.split(']')[1]) for x in funcs] 
print funcs

boolFuncTT = []
singleVars = []
for i in funcs:
#print i
    if i[1] == "G":
        singleVars.append(int(i[0]))
    else:
        tmp = map(lambda x: int(x), i[0].split(','))
        tmp.append(map(lambda x: int(x),i[1]))
        boolFuncTT.append(tmp)

print boolFuncTT
print singleVars

decMode = lines[noFuncs]

print "DecMode is: " + decMode

if decMode == "A":
    noIterations = int(lines[noFuncs+1])
    noIndepDec = int(lines[noFuncs+2])
    codeRate = float(lines[noFuncs+3])
    bitEnergy = float(lines[noFuncs+4])
    noise = float(lines[noFuncs+5])
elif decMode == "B":
    root = int(lines[noFuncs+1])
elif decMode == "C":
    msgPassVariant = lines[noFuncs+1]
    noIndepDec = int(lines[noFuncs+2])
    codeRate = float(lines[noFuncs+3])
    bitEnergy = float(lines[noFuncs+4])
    noise = float(lines[noFuncs+5])
'''
print noVars
print noStateVars
print noFuncs
print funcs
'''
'''
for i in range(0,100):
    z = math.sqrt(noise/2.0)*genAWGN()
    print z
'''

