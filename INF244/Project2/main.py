


##############
#####MAIN#####
##############

with open('IS.txt') as f:
    lines = []
    for line in f:
        lines.append(line)
    lines = [line.rstrip('\n') for line in lines]
    lines = iter(lines)

vertices = int(lines.next())
graph = []
for i in range(vertices):
    neigh = [int(x) for x in list(lines.next())]
    graph.append(neigh)
print graph

algType = lines.next()
if algType == '2':
    print "Decoding on binary graph"
elif algType == '4':
    print "Decoding on F4-additive graph"
elif algType == 'D':
    print "Dynamic decoding on F4-additive graph"

biases = {}
for line in lines:
    key = int(line[0])
    #tmp = line[3:].replace(",","")
    tmp = iter(line[3:])
    res = []
    #print tmp
    for i in tmp:
        #print i
        if i.isdigit():
            res.append(int(i))
        
    biases[key] = res

print biases

##############
###END MAIN###
##############
