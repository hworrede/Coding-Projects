# CSE30 PA4
# Hagos Worrede
# calculator.py
from stack import Stack
from tree import ExpTree
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
def infix_to_postfix(infix):
    output = ""
    opstack = Stack()
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
    
    
def calculate(infix):
	postfix = infix_to_postfix(infix)
	
	postfix = postfix.split()
# 	tree = ExpTree.make_tree(postfix)
	return ExpTree.evaluate(tree)
	
	
# a driver to test calculate module
if __name__ == '__main__':
    # test infix_to_postfix function
    assert infix_to_postfix('(5+2)*3') == '5 2 + 3 *'
    assert infix_to_postfix('5+2*3') == '5 2 3 * +'
    # test calculate function
    assert calculate('(5+2)*3') == 21.0
    assert calculate('5+2*3') == 11.0
    
    