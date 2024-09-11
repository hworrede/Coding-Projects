class Hashtable():

    def __init__(self):
        self.size = 8
        self.data = [None] * self.size

    def get(self, key):
        index = hash(key) % self.size
        if self.data[index] != None:
            for k in self.data[index]:
                if k[0] == key:
                    return k[1]
            return None


    def get_size(self):
        return len(self.data)
    
    def add(self, key, value):
        index = hash(key) % self.size
        main_value = [key, value]
        if self.data[index] == None:
            self.data[index] = list([main_value])
            return True
        else:
            for k in self.data[index]:
                if k[0] == key:
                    k[1] = value
                    return True
            self.data[index].append(main_value)
            return True

    def remove(self, key):
        index = hash(key) % self.size
        if self.data[index] == None:
            return False
        for k in range(0, len(self.data[index])):
            if self.data[index][k][0] == key:
                self.data[index].pop(k)
                return True
            

    def is_empty(self):
        index = hash(key) % self.size
        if self.data[index] == None or self.data[index] == []:
            return True
        else:
            return False


data = ['goat', 'pig', 'chicken', 'dog', 'lion', 'tiger', 'cow', 'cat']

# make a hash table with key-value pairs: 'goat': 0, 'pig': 1, 'chicken': 2, etc. 
h = Hashtable()
for i in range(len(data)):
    h.add(data[i], i)       # the key is data[i], the value is i

# print the hash table items
for key in data:
    print(h.get(key))
 
# test the method get() and if items in the hash table are correct
for i in range(len(data)): 
    assert h.get(data[i]) == i 

# test the method get_size()
n = h.get_size() # it depends on the default value of your hash table
assert n == 8 

# test the method remove() and is_empty()
for i in data: 
    h.remove(i) 
print(h.is_empty()) 
assert h.is_empty()