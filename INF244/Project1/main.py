import os

f = open('MP.txt')
noVars = int(f.readline())
noStateVars = int(f.readline())
noFuncs = int(f.readline())
funcs = []
for i in xrange(0,noFuncs):
    funcs.append(f.readline())
decMode = f.readline()
if decMode == "A":
    noIterations = f.readline()
    noIndDec = f.readline()
    codeRate = f.readline()
    bitEnergy = f.readline()
    noise = f.readline()
elif decMode == "B":
    root = f.readline()
elif decMode == "C":
    variant = f.readline()
    noIndDec = f.readline()
    codeRate = f.readline()
    bitEnergy = f.readline()
    noise = f.readline()
f.close()
print noVars
print noStateVars
print noFuncs
print funcs
