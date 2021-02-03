#!/usr/bin/env python3
dictionary = {"a": [1, 2, 3], "b": [45, 6], "c": [2, 45]}

print("The original dictionary is ", dictionary)

rd = dict()

for elem in set([value for values_list in dictionary.values() for value in values_list]):
	rd[elem] = [key for key, value in dictionary.items() for list_elem in value if elem == list_elem]

print("The final reversed dictionary ", rd)
rd2 = {1: ["a"], 2: ["a", "c"], 3: ["a"], 6: ["b"], 45: ["b", "c"]}

if (rd == rd2):
    print("The computed reversed dictionary is correct")
else:
    print("something went wrong: ", rd)
