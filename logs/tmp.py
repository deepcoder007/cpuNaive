import sys

f=open(sys.argv[1],'r')

ln = ''

for x in f:
    ln = x

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
