import itertools
import collections
import time

x0 = [[0,1], [1,1]]
x1 = [[1,2], [1,1]]
x2 = [[1,3], [1,1]]

f0 = [[0], [1,2]]
f1 = [[0,1,2],[1,2,3,4,5,6,7,8]]
f2 = [[1], [3,1]]
f3 = [[2], [2,3]]

x0f0 = [1,2,1,2,1,2,1,2]
x1f2 = [3,3,1,1,3,3,1,1]
x2f3 = [2,2,2,2,3,3,3,3]

result = "[78,196]/2"

it = itertools.product([0,1],repeat=3)

global x,f
x = [x0,x1,x2]
f = [f0,f1,f2,f3]

print x
print f

def genTT(n):
    l = itertools.product([0,1], repeat=n)
    for i in l:
        yield list(i)[::-1]

global visitedF, visitedX
visitedF = list(itertools.repeat(-1, len(f)))
visitedX = list(itertools.repeat(-1, len(x)))

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

def computeMarginal(neigh,node, res):
    TT = genTT(len(neigh))
    ind = 0
    ones = zeroes =  0
    indNode = neigh.index(node)
    cnt = 1

    print len(neigh)
    for i in TT:
        prod = 1
        print i
        for j in flatten(res):
            print j
            print "cnt is " + str(cnt)
            prod *= j[0] if i[cnt] == 0 else j[1]
            #prod *= j[ind%len(j)]
            
        ind += 1
        cnt += 1%(len(neigh)-1)
        if cnt == 0:
            cnt = 1
        if i[indNode] == 0:
            zeroes += prod
        else:
            ones += prod
    print "Marginal for " + str(node) + " is " + str([zeroes,ones])
    
    return [zeroes,ones]

#Flag tells whether we are in X or F list, X=0, F=1
def dfs(curr, prev, flag):
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

    if len(neighs[0]) == 1 and neighs[0][0] == prev:
        print str(fc) + "_" + str(curr) + " has Unit marginal " + str(neighs[1])
        return neighs[1]

    for i in neighs[0]:
        #print i
        if otherVis[i] == -1:
            print "Visiting: " + str(notFc) + "_" + str(i)
#time.sleep(5)
            res.append(dfs(i,curr, (flag + 1) % 2))
        else:
            print str(notFc) + "_" + str(i) + " already visited"

    if len(res) == len(neighs[0]):
        print "Computing marginal for " + str(fc) + "_" + str(curr)
        return computeMarginal(neighs[0], curr, res)
    else:
        return res
    
#return res

print dfs(1,-1,1)
#t = [[1,2,3,4,5,6,7,8], [3,3,1,1,3,3,1,1], [2,2,2,2,3,3,3,3]]
#t2 = [0,1,2]

#print computeMarginal(t2,0,t)




