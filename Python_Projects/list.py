B = [1, 3, 2, 4]
def list_comprehension(A):
    new_list = [A[x]+A[x+1] for x in range(len(A)-1)]
    print(new_list)
    return new_list
    
list_comprehension(B)