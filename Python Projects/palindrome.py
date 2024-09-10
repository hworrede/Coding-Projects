def is_palindrome(s):
    stack = Stack()
    for char in s:  
        stack.push(char)

    figure_stack = True
    while figure_stack:

        first_stack = Stack()
        option_one = stack.pop()
        
        while stack.size() > 1:
            second_stack = stack.pop()
            first_stack.push(second_stack)
        
        third_stack = stack.pop()
        
        if option_one != third_stack:
            figure_stack = False
            return False
        else:
            stack = first_stack
        if stack.size() == 1:
            return True
    

class Deque:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def addFront(self, item):
        self.items.append(item)

    def addRear(self, item):
        self.items.insert(0,item)

    def removeFront(self):
        return self.items.pop()

    def removeRear(self):
        return self.items.pop(0)

    def size(self):
        return len(self.items)

class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)

class Stack():
    def __init__(self):
         self.items = []

    def isEmpty(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items)-1]

    def size(self):
        return len(self.items)

if __name__ == '__main__':
    print(is_palindrome("hello"))
    print(is_palindrome("madam"))