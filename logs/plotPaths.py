import matplotlib.pyplot as plt
import sys

f = open(sys.argv[1],'r')
n = int(sys.argv[2])        # the number of nodes in the graph

input_file = f.readlines()
f.close()


path = [[] for x in range(n)]

# used for filtering numbers
def isNum(x):
    y = -1 
    try :
        y = int(x)
    except:
        pass
    if y > 0 :
        return True
    else:
        return False



# for all line in the input file
for x in input_file:
    splitup = (x.strip().split(','))
    if len(splitup) > 100 :
        splitup2 = filter( lambda x : isNum(x) , splitup )

        splitup = map(int,splitup2)
        for i in range(n):
            if splitup[i] < 20000 :
                path[i].append(splitup[i])


for x in path:
    if len(x) != 0:
        print x
#plt.plot(range(len(path)), path)
#plt.show()
