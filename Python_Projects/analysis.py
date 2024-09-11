# CSE30 Lab 7
# Hagos Worrede
# analysis.py
from timeit import Timer, timeit
from random import choice
import matplotlib.pyplot as plt

# bubbleSort method
def bubbleSort(items):
    for i in range(len(items)-1,0,-1): 
        for n in range(i):            
            if items[ n] > items[n+1]:
                items[ n], items[n+1] = items[n+1], items[ n]          


def mergeSort(items):  
    if len(items)>1:
        mergepoint = len(items)//2
        first_point = items[:mergepoint]
        second_point = items[mergepoint:]
        mergeSort(first_point)
        mergeSort(second_point)
        
        i, n, j = 0, 0, 0
        while i < len(first_point) and n < len(second_point):
            if first_point[ i] <= second_point[ n]:
                items[ j] = first_point[ i]
                i += 1
            else:
                items[ j] = second_point[ n]
                n += 1
            j += 1
        while i < len(first_point):
            items[ j] = first_point[ i]
            i, j = i+1, j+1
        while n < len(second_point):
            items[ j] = second_point[ n]
            n, j = n+1, j+1
            

def count_sort(fin, fin2, k):
    counts = [0 for i in range(11)] 
    for i in fin:
        i = str(i)
        while len(i) < k: 
            i = '0' + i 
        i = int(i[ fin2])
        counts[ i] += 1
    for i in range(10):
        counts[ i] += counts[ i-1]

    output = [0 for i in range(len(fin))]
    for i in range(len(fin)-1, -1, -1):
        n = str(fin[ i])
        while len(n) < k:
            n = '0' + n
        n = int(n[ fin2])
        output[counts[ n]-1] = fin[ i]
        counts[ n] -= 1

    return output

def radixSort(fin, fin2):
    for i in range(fin2-1, -1, -1):
        fin = count_sort(fin,i,fin2)
    return fin

list_ = list(range(0,500))      
d1 = [choice(list_) for i in range(10)]  # random list of size 10
d2 = [choice(list_) for i in range(20)]  # random list of size 20
d3 = [choice(list_) for i in range(50)]  
d4 = [choice(list_) for i in range(100)] 
d5 = [choice(list_) for i in range(200)] 
d6 = [choice(list_) for i in range(500)] 

data = [d1, d2, d3, d4, d5, d6]  
times1 = [] 
times2 = []
times3 = []
    

for i in data:
    t_item1 = Timer(f"bubbleSort({i})", "from __main__ import bubbleSort")
    print("bubblesort ",t_item1.timeit(number=3), "milliseconds")
    times1.append(t_item1.timeit(number=3)) 

for m in data:
    t_item2 = Timer(f"mergeSort({m})", "from __main__ import mergeSort")
    print("mergeSort ", t_item2.timeit(number=1), "milliseconds")
    times2.append(t_item2.timeit(number=1))
    
b = 3 
for n in data:
    t_item3 = Timer(f"radixSort({n}, {b})", "from __main__ import radixSort")
    print("radixSort ", t_item3.timeit(number=2), "milliseconds")
    times3.append(t_item3.timeit(number=2))


x_intercept1 = [len(d1),len(d2),len(d3),len(d4),len(d5),len(d6)] 
y_intercept1 = times1

x_intercept3 = [len(d1),len(d2),len(d3),len(d4),len(d5),len(d6)] 
y_intercept3 = times2 

x_intercept2 = [len(d1),len(d2),len(d3),len(d4),len(d5),len(d6)] 
y_intercept2 = times3 



plt.plot(x_intercept1,y_intercept1, label="bubbleSort line [0(n^2)]")
plt.plot(x_intercept3, y_intercept3, label="mergeSort line [O(nlogn)]")
plt.plot(x_intercept2, y_intercept2, label="radixSort line [0(n)]")
plt.xlabel("x size")
plt.ylabel("y-intercept ")
plt.legend()
plt.show()