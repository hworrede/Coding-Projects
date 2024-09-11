import numpy as np
from itertools import permutations
def Queens(elements):
    main_end=[] 
    main_second=[] 
    number_elem=0
    #using the permutations
    for k in permutations(range(elements)): 
        # First_element = np.zeros(elements*elements).reshape(elements,elements)      
        permutation_main =0 
        for m in range(elements):
            if permutation_main!=m*(m-1)/2:
                break
            for n in range(1,elements):
                if m >= n:
                #checking for when it attacks
                    if  k[m] ==k[m-n]-n or k[m] ==k[m-n]+n: 
                        permutation_main = 0
                        break
                    else:
                        permutation_main += 1
                else:
                    continue
            if permutation_main == elements*(elements-1)/2:
                number_elem+=1
                for r in range(elements):
                    main_end.append(k[r]+1)
                main_second.append(main_end)
                main_end=[]  
            else:
                pass
    print("The",elements,"Queens puzzle has",number_elem,"solutions:")
    return main_second
	
if __name__ == '__main__':
    num = int(input("Enter a number of queens:\n"))
    input_answer=Queens(num)
    for m in input_answer: 
        print(m)