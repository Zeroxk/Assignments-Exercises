import sys
import random
import math
import itertools
import collections

global x,f
global visitedF, visitedX

'''
#CREDZ OVIN DA TEIG
def genTT(lengths):
    indexes = []
    for i in lengths:
        indexes.append(0)
    for i in range(2**len(lengths)):
        yield indexes
        val = 0
        for j in range(len(indexes)):
            if j == 0:
                indexes[j] = (indexes[j]+1)%lengths[j]
            elif indexes[j-1] == 0 and val == 0:
                indexes[j] = (indexes[j]+1)%lengths[j]
            val += indexes[j]
'''
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

def isUnitMarg(nodeVals):
    for i in nodeVals:
        if i != 1:
            return False
                
#    print str(nodeVals) + " is unit marg, returning"
    return True

#Generate random numbers according to gaussian distribution using box-muller method
def genAWGN(R, Eb, N0):

    Ec = R * Eb
    variance = N0/2
    SNR = Eb/N0
    t = -math.sqrt(Ec)


    z0 = z1 = 0
    while True:
        u = random.uniform(-1,1)
        v = random.uniform(-1,1)

##print "u:" + str(u) + "v:" + str(v)
        s = u**2 + v**2
##print "s:" + str(s)

        if not (s == 0 or s >= 1):
            z0 = u * math.sqrt((-2*math.log(s)/s))
            z1 = v * math.sqrt((-2*math.log(s)/s))
            break
        
    
    v = math.sqrt(variance)*z0
    r = t + v

    P1 = 1/(1 + (math.exp(-2*math.sqrt(Ec)*r/variance)))
    P0 = 1 - P1

    print "P0 " + str(P0) + "P1 " + str(P1)
    return [P0,P1]

def computeMarginal(neigh,node, res, nodeVals):
    #print "neighs " + str(neigh)
#print "nodeVals " + str(nodeVals)
#print "res " + str(res) 
    if isUnitMarg(nodeVals):
        return res

    TT = genTT(len(neigh))
    ind = 0
    ones = zeroes =  0
    indNode = neigh.index(node)
    ret = []
    marginals = [[] for _ in range(len(neigh)-1)]
    #cnt = 1
#   print "Indnode: " + str(indNode)
    #print len(neigh)
    for i in TT:
        prod = 1
#       print i
        cnt = (indNode+1)%len(i)
#cnt = (indNode+1)%len(neigh)
        index = 0
        for j in flatten(res):
#           print "j " + str(j)
            if isUnitMarg(j):
               continue
#           print "cnt is " + str(cnt)
            #print "i[cnt]: " + str(i[cnt])
            tmp = j[0] if i[cnt] == 0 else j[1]
            prod *= tmp
            marginals[index].append( tmp )

            cnt = (cnt+1)%len(i)
            #if cnt == indNode:
                #cnt = (cnt+1)%len(neigh)
            index += 1
            
            #prod *= j[ind%len(j)]
       
#print "ind " + str(ind)
        #print "nodeVals: " + str(nodeVals[ind])
        prod *= nodeVals[ind]
        #print "Prod " + str(prod)
        ind += 1
        ret.append(prod)
          
        if i[indNode] == 0:
            zeroes += prod
        else:
            ones += prod
    #print "marginals " + str(marginals)
    #print "Ret sumProduct " + str(ret)
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
#   print "Curr: " + str(curr) + " Prev: " + str(prev) + " Flag: " + fc
    
    visited[curr] = 1
    #print neighs
    if len(neighs[0]) == 1 and neighs[0][0] == prev:
#       print str(fc) + "_" + str(curr) + " has Unit marginal " + str(neighs[1])
        return neighs[1]

    for i in neighs[0]:
        #print i
        if otherVis[i] == -1:
#           print "Visiting: " + str(notFc) + "_" + str(i)
            res.append(rootedTree(i,curr, (flag + 1) % 2))
        else:
#           print str(notFc) + "_" + str(i) + " already visited"
            None
            
    #print "Computing message from " + str(fc) + "_" + str(curr) + " to " + str(notFc) + "_" + str(prev)

    if flag == 0:
        rs = flatten(res)
        '''
        length = 1
        for i in rs:
            print "rs_i " + str(i)
            length = max(len(i),length)
        print "length " + str(length)
        rs = flatten(res)
        ret = [1 for _ in range(length)]
        '''
        ret = [1,1]
        for i in rs:
            for j in range(len(ret)):
                ret[j] *= i[j]
        #print "ret X " + str(ret)
        return ret
    else:
        ret = computeMarginal(neighs[0],prev,res,neighs[1])
        #print "ret F" + str(ret)
        return ret
    
###################
#####  MAIN  ######
###################

inFile = 'MP.txt'

if(len(sys.argv) == 2):
    inFile = sys.argv[1]

with open(inFile) as f:
    lines = []
    for line in f:
        lines.append(line)
    lines = [line.rstrip('\n').rstrip('\r') for line in lines]
    lines = iter(lines)

noVars = int(lines.next())
states = lines.next()
noStates = int(states[0])
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
print singleVars

x = [[] for _ in range(noVars+noStates)]
f = boolFuncTT

#Create adjacency lists for X
for i in range(len(boolFuncTT)):
    neighs = boolFuncTT[i][0]
    #print neighs
    for j in neighs:
        x[j].append(i)

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
    x = [[i,[1,1]] for i in x]
    print x
    print f

    if root == "a":
        print "Computing all marginals"
        for i in range(noVars):
            #print "Computing marginal for X_" + str(i)
            visitedF = list(itertools.repeat(-1, len(f)))
            visitedX = list(itertools.repeat(-1, len(x)))
            marg = rootedTree(i,-1,0)
            print "Marginal for X_" + str(i) + " is " + str(marg)
        
    else:
        rootedTree(int(root),-1,0)
elif decMode == "C":
    states = [int(i) for i in states[2:] if i.isdigit()]
    print "States " + str(states)

    for i in f:
        #print i
        i[1] = [int(j) for j in str(i[1]) if j.isdigit() ]
    print x
#print f
    msgPassVariant = lines.next()
    noIndepDec = int(lines.next())
    codeRate = float(lines.next())
    bitEnergy = float(lines.next())
    noise = float(lines.next())

    x = [[i,[]] for i in x]
    ind = 0
    for i,x_i in enumerate(x):
        if i >= noVars:
            x_i[1] = [1 for _ in range(states[ind])]
            ind += 1
        elif i < singleVars[0]:
            x_i[1] = [1,1]
    print x
    for i in singleVars:
        x[i][1] = genAWGN(codeRate,bitEnergy,noise)
    print x
    visitedF = list(itertools.repeat(-1, len(f)))
    visitedX = list(itertools.repeat(-1, len(x)))

    print rootedTree(noVars,-1,0)
else:
    print "Nothing here"

