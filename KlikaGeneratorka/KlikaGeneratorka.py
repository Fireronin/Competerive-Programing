import random 
n = 200
d = 20000
top = 10000
bottom = -10000
print(n);
print(d);

for x in range(n):
	a =  random.randint(bottom,top)
	b = random.randint(bottom,top)
	print("{0} {1}".format(a,b))


