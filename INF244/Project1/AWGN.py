import random
import math
import csv

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
            return z0
            break
        
    
    v = math.sqrt(variance)*z0
    r = t + v

    P1 = 1/(1 + (math.exp(-2*math.sqrt(Ec)*r/variance)))
    P0 = 1 - P1

    print "P0 " + str(P0) + "P1 " + str(P1)

R = 0.5
Eb = 10.0
N0 = 5.0
res = []
for i in range(100):
    res.append(genAWGN(R,Eb,N0))

with open('test.csv', "wb") as of:
   wr = csv.writer(of, dialect='excel')

   for i in res:
       wr.writerow([i])
