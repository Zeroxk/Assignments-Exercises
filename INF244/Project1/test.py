import itertools

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
    yield list(l)[::-1]

global visitedF, visitedX
visitedF = list(itertools.repeat(-1, len(f)))
visitedX = list(itertools.repeat(-1, len(x)))

def dfs(curr, prev, flag):
    print "Curr: " + str(curr) + " Prev: " + str(prev) + " Flag: " + flag
    res = []
    if flag == 'X':
        visitedX[curr] = 1
        print x[curr]
        if len(x[curr][0]) == 1:
            return x[curr][1]
        for i in x[curr][0]:
            print i
            if visitedF[i] == -1:
                print "Visiting " + str(i)
                res.append(dfs(i, curr, 'F'))
            else:
                print str(i) + " already visited"
    elif flag == 'F':
        visitedF[curr] = 1
        print f[curr]
        if len(f[curr][0]) == 1:
                return f[curr][1]
        for i in f[curr][0]:
            print i
            if visitedX[i] == -1:
                print "Visiting " + str(i)
                res.append(dfs(i,curr, 'X'))
            else:
                print str(i) + " already visited"
    return res

print dfs(0,0,'X')


