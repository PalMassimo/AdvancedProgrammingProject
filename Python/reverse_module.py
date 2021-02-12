def reverse_dictionary(d):
    rd = dict()

    for elem in set([value for values_list in d.values() for value in values_list]):
	    rd[elem] = list(set([key for key, value in d.items()
	                    for list_elem in value if elem == list_elem]))

    return rd
    