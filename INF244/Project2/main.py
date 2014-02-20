


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
    biases[key] = [int(x) for x in list(line[3:].replace(',',''))]

print biases

##############
###END MAIN###
##############
