# Returns the total node count after each step

import sys

final_tally = []

f=open(sys.argv[1],'r')

ln = ''

for x in f:
    ln = x
    data = ln.strip().split(',')
    if len(data) < 10 :
        continue
    dt = []
    for x in data:
        try:
            dt.append(int(x))
        except:
            pass
    dt = filter( (lambda  x: x<10000), dt )
    final_tally.append(len(dt))

	

f.close()



data = ln.strip().split(',')
dt=[]

for x in data:
    try:
        dt.append(int(x))
    except:
        pass

dt = filter( (lambda x: x<1000), dt)

print dt
print len(dt)

print float(sum(dt))/len(dt)

print 'Path lengths : '
i=1 
for x in final_tally:
    print i,x
    i+=1
