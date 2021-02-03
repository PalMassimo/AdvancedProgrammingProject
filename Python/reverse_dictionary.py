#!/usr/bin/env python3
dictionary  = {"a": [1, 2, 3], "b": [45, 6], "c": [2, 45]}

print("The original dictionary is ", dictionary)

rd = dict()
my_set = set()

for value in dictionary.values():
	my_set = my_set.union(set(value))

for elem in my_set:
	rd[elem] = list()

for elem in rd.keys():
	for key, value in dictionary.items():
		for list_elem in value:
			if(elem == list_elem):
				#print("rd[elem]", elem, rd[elem])
				rd[elem].append(key)

print("The final reversed dictionary ", rd)
rd2 = {1: ["a"], 2: ["a", "c"], 3: ["a"], 6: ["b"], 45: ["b", "c"]}

if (rd==rd2): 
	print("The computed reversed dictionary is correct")
else: 
	print("something went wrong")
