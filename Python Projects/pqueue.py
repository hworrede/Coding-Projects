from stack import Stack

class PQueue:
    def __init__(self):
        self.stack = Stack()

    def __str__(self):
        return str(self.stack)

    def empty(self):
        return self.stack.isEmpty()

    def enqueue(self, item):
        # your code goes here
        if(self.stack.isEmpty()):
            self.stack.push(item)
            return

        if(self.stack.peek() <= item):
            self.stack.push(item)
        else:
            temp_val = self.stack.pop()
            self.enqueue(item)
            self.enqueue(temp_val)


    def dequeue(self):
        # your code goes here
        return self.stack.pop()
    
if __name__ == '__main__':
    pq = PQueue()
    data = [1, 3, 5, 2, 0, 6, 4]
    for i in data:
        pq.enqueue(i)
        print('adding', i)
        print(pq)
        
    while not pq.empty():
        print('removing', pq.dequeue())
        print(pq)