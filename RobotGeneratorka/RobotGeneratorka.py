import random

n = 10
k = 15
print("{0} {1}".format(n,k))

for x in range(n):
	for y in range(n):
		if random.randint(0,4)==1 :
			print("{0}".format("X"),end = '')
		else:
			print("{0}".format("."),end = '')
	print("")


