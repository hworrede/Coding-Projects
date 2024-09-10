

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

        
opstack = Stack()


# opstack = []
output = ""

input1 = "5+2*3"
input3 = ""
def expression_to_list(expr):
    number = ['1', '2', '3', '4', '5', '6', '7', '8', '9']
    operators = ['+', '-', '*', '/', '(', ')']
    out = ""
    inserted_str = ""
    for index, i in enumerate(expr):
        if(i in operators):
            if(inserted_str != ""):
                out += inserted_str + " "
            out += i + " "
            inserted_str = ""
        else:
            inserted_str += i
            if(index == len(expr) -1):
                out += inserted_str + " "
        
    out = out.split(" ")
    out.pop()
    return out

exprList = expression_to_list(input1)

def infix_to_postfix(infix):
    output = ""
    exprList = expression_to_list(infix)
    number = ['1', '2', '3', '4', '5', '6', '7', '8', '9']
    operators = ['+', '-', '*', '/']
    high_precedance = ['*', '/']
    low_precedance = ['+', '-']
    for i in exprList:
        if(i in number):
            output += i + " "
        if(i == "("):
            opstack.push(i)
        if(i == ")"):
            top = opstack.pop()
            while(top != "("):
                output += top + " "
                top = opstack.pop()

        if(i in operators):
            if(not opstack.isEmpty()):
                top = opstack.peek()
            else:
                top = "NULL"
            if(top in high_precedance):
                while(top in high_precedance and not opstack.isEmpty()):
                    output += top + " "
                    top = opstack.pop()
            # else:
            #     while(top in operators and not opstack.isEmpty()):
            #         output += top + " "
            #         top = opstack.pop()

            opstack.push(i)
        # print(output)
        # print(opstack.stack)
    while(not opstack.isEmpty()):
        top = opstack.pop()
        output += top + " "
    return output
            

posttest = infix_to_postfix(input1)

print(posttest)






