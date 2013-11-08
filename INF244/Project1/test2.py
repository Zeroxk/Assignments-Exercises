import collections

a = [[1,2,3], [[3,4,5]], [[[5,6,7],[7,8,9]]] ]
#a = [ [1,2,3], [3,4,5], [5,6,7], [7,8,9] ]

def flatten(l):
	for el in l:
		#print el[0]
		if not isinstance(el,collections.Iterable):			
			#print el
			yield el
		elif isinstance(el[0], collections.Iterable):
			for sub in flatten(el):
				yield sub
		else:
			yield el

#print a[1][0]
#print isinstance(a[1][0], collections.Iterable)
for i in flatten(a):
	print i

