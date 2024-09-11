# CSE30 PA4
# Hagos Worrede
# stack.py
class Stack:
    def __init__(self):
        self.stack = []

    def isEmpty(self):
        if(len(self.stack) > 0):
            return False
        else:
            return True

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        return self.stack.pop()

    def peek(self):
        top = self.stack.pop()
        self.stack.append(top)
        return top

    def size(self):
        return len(self.stack)
# a driver program for class Stack
if __name__ == '__main__':
    
    data_in = ['hello', 'how', 'are', 'you']
    s = Stack()
    for i in data_in:
        s.push(i)
           
    assert s.size() == len(data_in)
    assert s.peek() == data_in[-1]
    data_out = []
    while not s.isEmpty():
        data_out.append(s.pop())
    assert data_out == data_in[::-1]
    assert s.size() == 0
    assert s.peek() == None