import itertools
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

#Flag tells whether we are in X or F list, X=0, F=1
def dfs(curr, prev, flag):
    fc = 'X' if flag == 0 else 'F'
    print "Curr: " + str(curr) + " Prev: " + str(prev) + " Flag: " + fc
    
    res = []
    visited = []
    otherVis = []
    nodes = []
    if flag == 0:
        visited = visitedX
        otherVis = visitedF
        nodes = x
    elif flag == 1:
        visited = visitedF
        otherVis = visitedX
        nodes = f

    visited[curr] = 1
    print nodes[curr]

    if len(nodes[curr][0]) == 1 and nodes[curr][0][0] == prev:
        print str(curr) + " has Unit marginal"
        return nodes[curr][1]
    for i in nodes[curr][0]:
        print i
        if otherVis[i] == -1:
            print "Visiting: " + str(i)
#time.sleep(5)
            res.append(dfs(i,curr, (flag + 1) % 2))
        else:
            print str(i) + " already visited"
    return computeMarginal(nodes[curr][0], curr, res)
#return res

print dfs(0,-1,0)

def computeMarginal(neigh,node, res):
    TT = genTT(len(neigh))
    ind = 0
    offset = 2**len(neigh)
    ones = zeroes =  0
    for i in TT:
        prod = 1
        for j in res:
            prod *= j[ind]
            ind += 1
        indNode = neigh.index(node)
        if indNode == 0:
            zeroes += prod
        else:
            ones += prod
    print "Marginal for " + str(node) + " is " + str([ones,zeroes])
    
    return [ones,zeroes]


