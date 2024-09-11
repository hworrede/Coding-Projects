# imports
from timeit import Timer
from random import choice



def bubbleSort(items):
    for i in range(len(items) - 1, 0, -1):
        for j in range(i):
            if items[j] > items[j + 1]:
                items[j], items[j + 1] = items[j + 1], items[j]
            


def selectionSort(items):
    for i in range(len(items)):
        min_index = i
        for j in range(i + 1, len(items)):
            if items[j] < items[min_index]:
                min_index = j
        items[i], items[min_index] = items[min_index], items[i]



def insertionSort(items):
    for i in range(1, len(items)):
        key = items[i]
        j = i - 1
        while (j >= 0 and key < items[j]):
            items[j + 1] = items[j]
            j = j - 1
        items[j + 1] = key



def shellSort(items):
  
    n = len(items)
    gap = n // 2
  
    while gap > 0:  
        for i in range(gap, n):  
            key = items[i]

            j = i
            while  j >= gap and key < items[j-gap] :
                items[j] = items[j-gap]
                j = j - gap
  
            items[j] = key
        gap = gap // 2



def partition(items, low, high):
    # pivot element
    pivot = items[high]
    i = low - 1
    for j in range(low, high):
        if (items[j] <= pivot):
            i = i + 1
            items[i], items[j] = items[j], items[i]
    items[i + 1], items[high] = items[high], items[i + 1]
    return i + 1

# recursively sorts the items using quick sort
def quickSortRec(items, low, high):
    # check if the items is valid
    if (low < high):
        # partition the items
        j = partition(items, low, high)
        # recursively sort the subitemss
        quickSortRec(items, low, j - 1)
        quickSortRec(items, j + 1, high)

def quickSort(items):
    # sort the items using recursive quick sort
    quickSortRec(items, 0, len(items) - 1)







# merges sorted items[low...mid] and items[mid+1...high]
def merge(items, low, mid, high):
    # take a copy of the original items
    aux = items.copy();
    # use for indexing
    i = low
    j = mid + 1
    # fill the entries
    for k in range(low, high + 1):
        # if left items is exhausted then copy from right
        if (i == mid + 1): 
            items[k] = aux[j]
            j = j + 1
        # if right items is exhausted then copy from left
        elif (j == high + 1):
            items[k] = aux[i]
            i = i + 1
        # if both items has elements then compare
        elif (aux[i] <= aux[j]):
            items[k] = aux[i]
            i = i + 1
        else:
            items[k] = aux[j]
            j = j + 1
            
# sorts the items using recursive merge sort
def mergeSortRec(items, low, high):
    # check if items is valid
    if (low < high):
        # split the items into two halves
        mid = low + (high - low) // 2
        # sort the halves recursively
        mergeSortRec(items, low, mid)
        mergeSortRec(items, mid + 1, high)
        # merge the sorted halves
        merge(items, low, mid, high)
        
# sorts the items using merge sort
def mergeSort(items):
    # sort the items using recursive function
    mergeSortRec(items, 0, len(items) - 1)




# To heapify subtree rooted at index i.
# n is size of heap
def heapify(items, n, i):
    # assume root is the largest
    largest = i         
    # get the index of left and right child
    l = 2 * i + 1
    r = 2 * i + 2
  
    # See if left child of root exists and is
    # greater than root
    if l < n and items[i] < items[l]:
        largest = l
  
    # See if right child of root exists and is
    # greater than max. so far
    if r < n and items[largest] < items[r]:
        largest = r
  
    # Change root, if needed
    if largest != i:
        # swap
        items[i],items[largest] = items[largest],items[i]  
        # Heapify the root.
        heapify(items, n, largest)
  
# sorts the items using the heap sort algorithm
def heapSort(items):
    # get the number of elements in items
    n = len(items)
  
    # Build a maxheap.
    # Since last parent will be at ((n//2)-1) we can start at that location.
    for i in range(n // 2 - 1, -1, -1):
        heapify(items, n, i)
  
    # One by one extract elements
    for i in range(n-1, 0, -1):
         # swap
        items[i], items[0] = items[0], items[i]  
        heapify(items, i, 0)



# sorts the items using count sort
def countSort(items):
    # The output item say that will have sorted items
    aux = [0 for i in range(len(items))]    
    # find the maximum element in the items
    maxEl = max(aux)
    # Create a count item say to store count of inidividul
    # item and initialize count item say as 0
    count = [0 for i in range(maxEl + 1)]
    # Store count of each item
    for item in aux:
        count[item] += 1 
    # Change count[i] so that count[i] now contains actual
    # position of this item in output item say
    for i in range(1, maxEl + 1):
        count[i] += count[i-1] 
    # Build the output character item say
    for i in range(len(items)):
        items[count[aux[i]]-1] = aux[i]
        count[aux[i]] -= 1
 



# A function to do counting sort of items[] according to
# the digit represented by exp.
def countingSortForRadix(items, exp1):
    # get the number of elements in the items
    n = len(items) 
    # The output items elements that will have sorted items
    output = [0] * (n)
    # initialize count items as 0
    count = [0] * (10)

    # Store count of occurrences in count[]
    for i in range(0, n):
        index = (items[i] / exp1)
        count[int(index % 10)] += 1
 
    # Change count[i] so that count[i] now contains actual
    # position of this digit in output items
    for i in range(1, 10):
        count[i] += count[i - 1]
 
    # Build the output items
    i = n - 1
    while i >= 0:
        index = (items[i] / exp1)
        output[count[int(index % 10)] - 1] = items[i]
        count[int(index % 10)] -= 1
        i -= 1
 
    # Copying the output items to items[],
    # so that items now contains sorted numbers
    i = 0
    for i in range(0, len(items)):
        items[i] = output[i]
 
# Method to do Radix Sort
def radixSort(items): 
    # Find the maximum number to know number of digits
    max1 = max(items)
    # Do counting sort for every digit. Note that instead
    # of passing digit number, exp is passed. exp is 10^i
    # where i is current digit number
    exp = 1
    while max1 / exp > 0:
        countingSortForRadix(items, exp)
        exp *= 10




# using bucket sort
def insertionSortForBucket(b):
    for i in range(1, len(b)):
        up = b[i]
        j = i - 1
        while j >= 0 and b[j] > up:
            b[j + 1] = b[j]
            j -= 1
        b[j + 1] = up    
    return b    

# sorts teh array using bucket sort  
def bucketSort(items):
    aux = []
    # 10 means 10 slots, each
    # slot's size is 0.1
    slot_num = 10 
    for i in range(slot_num):
        aux.append([])
         
    # Put items elements in different buckets
    for item in items:
        index_b = int(slot_num * item) % slot_num
        aux[index_b].append(item)
     
    # Sort individual buckets
    for i in range(slot_num):
        aux[i] = insertionSortForBucket(aux[i])
         
    # concatenate the result
    k = 0
    for i in range(slot_num):
        for j in range(len(aux[i])):
            items[k] = aux[i][j]
            k += 1






# original list of numbers
list_ = list(range(0, 500))
# the sizes we have to test
sizes = [5, 10, 20, 40, 80, 160, 320, 500]
# algorithms we have
algorithms = ['bubbleSort', 'selectionSort', 'insertionSort', 'shellSort', 'quickSort', 'mergeSort', 'heapSort', 'countSort', 'radixSort', 'bucketSort']


# print the header
print("{:>5s}".format("Size"), end='')
for algorithm in algorithms:
    print("{:>15s}".format(algorithm), end='')
print()

# iterate through each size
for size in sizes:
    # create an items of given size
    data = [choice(list_) for i in range(size)]
    # print the size
    print("{:>5d}".format(size), end='')
    # test out all algorithms
    for algorithm in algorithms:
        # take a copy of the original items
        d = data.copy()
        # sort the items
        t1 = Timer(f"{algorithm}({d})", f"from __main__ import {algorithm}")
        print("{:>15f}".format(t1.timeit(number=1)), end='')
    # print the newline
    print()