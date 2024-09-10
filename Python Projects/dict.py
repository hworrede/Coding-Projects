def make_dict(list_to_make_dict):
	dict = {}
	for i in list_to_make_dict:
		if len(i) not in dict.keys():
			if(len(i)) > 10:
				dict[10] = [i]
			else:
				dict[len(i)] = [i]
		else:
			if(len(i) > 10):
				dict[else].append(i)
			else:
				dict[len(i)].append(i)
			
	return dict
			
			
if __name__ == '__main__':
    
    d = {2: ['at', 'to', 'no'], 3: ['add', 'sun'], 10: ['Hello! How are you?']}
    dictionary = make_dict(['at', 'add', 'sun', 'to', 'no', 'Hello! How are you?'])
    print (dictionary)
    assert dictionary == d
    print('Everything works correctly!')