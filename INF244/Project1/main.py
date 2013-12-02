import sys
import random
import math
import itertools
import collections

global x,f
global visitedF, visitedX

def genTT(n):
    l = itertools.product([0,1], repeat=n)
    for i in l:
        yield list(i)[::-1]

def flatten(l):
    for el in l:
    #print el[0]
        if not isinstance(el,collections.Iterable):         
            #print el
            yield el
        elif isinstance(el[0], collections.Iterable):
            for sub in flatten(el):
                yield sub
        else:
            yield el

#Generate random numbers according to gaussian distribution using box-muller method
def genAWGN():

    while True:
        u = random.uniform(-1,1)
        v = random.uniform(-1,1)
        ##print "u:" + str(u) + "v:" + str(v)
        
        s = u**2 + v**2
        ##print "s:" + str(s)

        z0 = z1 = 0
        if not (s == 0 or s == 1 or s > 1):
            z0 = u * math.sqrt((-2*math.log(s)/s))
            z1 = v * math.sqrt((-2*math.log(s)/s))
            break

        #print str(z0) + " " + str(z1)

    #We only need one sample so we just pick z0
    return z0

def computeMarginal(neigh,node, res, nodeVals):
    TT = genTT(len(neigh))
    ind = 0
    ones = zeroes =  0
    indNode = neigh.index(node)
    #cnt = 1
    #print "Indnode: " + str(indNode)
    #print len(neigh)
    for i in TT:
        prod = 1
        print i
        cnt = 0
        for j in flatten(res):
            print j

            if cnt != 0:
                #print "cnt is " + str(cnt)
                print "i[cnt]: " + str(i[cnt])
                prod *= j[0] if i[cnt] == 0 else j[1]

            cnt = (cnt+1)%(len(neigh))
            
            #prod *= j[ind%len(j)]
        
        #print "nodeVals: " + str(nodeVals[ind])
        prod *= nodeVals[ind]
        print "Prod " + str(prod)
        ind += 1
            
        if i[0] == 0:
            zeroes += prod
        else:
            ones += prod
    print "Marginal for " + str(node) + " is " + str([zeroes,ones])
    
    return [zeroes,ones]

#Flag tells whether we are in X or F list, X=0, F=1
def rootedTree(curr, prev, flag):
    res = []
    visited = []
    otherVis = []
    neighs = []
    fc = 0
    notFc = 0
    if flag == 0:
        visited = visitedX
        otherVis = visitedF
        neighs = x[curr]
        fc = 'X'
        notFc = 'F'
    elif flag == 1:
        visited = visitedF
        otherVis = visitedX
        neighs = f[curr]
        fc = 'F'
        notFc = 'X'
    print "Curr: " + str(curr) + " Prev: " + str(prev) + " Flag: " + fc
    
    visited[curr] = 1
    print neighs
    #res.append(neighs[1])
    if len(neighs[0]) == 1 and neighs[0][0] == prev:
        print str(fc) + "_" + str(curr) + " has Unit marginal " + str(neighs[1])
        return neighs[1]

    for i in neighs[0]:
        #print i
        if otherVis[i] == -1:
            print "Visiting: " + str(notFc) + "_" + str(i)
#time.sleep(5)
            res.append(rootedTree(i,curr, (flag + 1) % 2))
        else:
            print str(notFc) + "_" + str(i) + " already visited"

    if len(res) == len(neighs[0]):
        print "Computing marginal for " + str(fc) + "_" + str(curr)
        return computeMarginal(neighs[0], curr, res, neighs[1])
    else:
        return res

###################
#####  MAIN  ######
###################

inFile = 'MPC.txt'

if(len(sys.argv) == 2):
    inFile = sys.argv[1]

with open(inFile) as f:
    lines = []
    for line in f:
        lines.append(line)
    lines = [line.rstrip('\n') for line in lines]
    lines = iter(lines)

noVars = int(lines.next())
noStateVars = lines.next()
noFuncs = int(lines.next())

#print lines
funcs = []
for i in range(noFuncs):
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
        boolFuncTT.append([map(int, i[0].split(',')),map(int,i[1].split(','))])

#print boolFuncTT
#print singleVars

x = [[] for _ in range(noVars)]
f = boolFuncTT

#Create adjacency lists for X
for i in range(len(boolFuncTT)):
    neighs = boolFuncTT[i][0]
    #print neighs
    for j in neighs:
        x[j].append(i)

x = [[i,[1,1]] for i in x]
print x
print f

visitedF = list(itertools.repeat(-1, len(f)))
visitedX = list(itertools.repeat(-1, len(x)))

'''
for i in boolFuncTT:
    n = len(i)-1
    print "Printing truth table for " + str(i)
    it = itertools.product([0,1], repeat=n)
    ind = 0
    for j in it:
        print str(list(j[::-1])) + " " + str(i[len(i)-1][ind])
        ind += 1
'''
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
    if root == "a":
        #for i in range(noVars):
            #dfs(i,-1,0)
        print "Computing all marginals"
    else:
        rootedTree(int(root),-1,0)
elif decMode == "C":
    msgPassVariant = lines.next()
    noIndepDec = int(lines.next())
    codeRate = float(lines.next())
    bitEnergy = float(lines.next())
    noise = float(lines.next())
else:
    print "Nothing here"
'''
for i in range(0,100):
    z = math.sqrt(noise/2.0)*genAWGN()
    print z
'''

