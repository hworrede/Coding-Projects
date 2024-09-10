# CSE30 PA4
# Hagos Worrede
# tree.py
from stack import Stack
class BinaryTree:
    def __init__(self, rootObj):
        self.key = rootObj
        self.leftChild = None
        self.rightChild = None

    def insertLeft(self, newNode):
        if self.leftChild == None:
            self.leftChild = BinaryTree(newNode)
        else:
            t = BinaryTree(newNode)
            t.leftChild = self.leftChild
            self.leftChild = t

    def insertRight(self, newNode):
        if self.rightChild == None:
            self.rightChild = BinaryTree(newNode)
        else:
            t = BinaryTree(newNode)
            t.rightChild = self.rightChild
            self.rightChild = t

    def getLeftChild(self):
        return self.leftChild
        
    def getRightChild(self):
        return self.rightChild
        
    def setRootVal(self, newobj):
        self.key = newobj

    def getRootVal(self):
        return self.key


    def __str__(self):
        s = f"{self.key}"
        s += '('
        if self.leftChild != None:
            s += str(self.leftChild)
        s += ')('
        if self.rightChild != None:
            s += str(self.rightChild)
        s += ')'
        return s
        
class ExpTree(BinaryTree):   
    def make_tree(postfix):
        operator_main = set(['+', '-', '*', '/', '(', ')', '^'])
        s= Stack()
        for x in postfix:
            t1= ExpTree(x)
            if x in operator_main:
                main_pop1 = s.pop()
                main_pop2 = s.pop()
                t1.rightChild = main_pop1
                t1.leftChild= main_pop2
            s.push(t1)
        t1 = s.pop()
        return t1

    def preorder(tree):
        Value_tree = ""
        Value_tree =   Value_tree + str(tree.key)
        if tree.leftChild != None:
            Value_tree = Value_tree + ExpTree.preorder(tree.getLeftChild())
        if tree.rightChild != None:
            Value_tree = Value_tree + ExpTree.preorder(tree.getRightChild())
        return Value_tree
        
    def inorder(tree):
        Value_tree = ""
        if tree.leftChild != None:
            Value_tree = "("+ ExpTree.inorder(tree.getLeftChild())
        Value_tree =   Value_tree + str(tree.getRootVal()) 
        if tree.rightChild != None:
            Value_tree = Value_tree + ExpTree.inorder(tree.getRightChild()) +")"
        return Value_tree
      
    def postorder(tree):
        Value_tree = ""
        if tree.leftChild != None:
            Value_tree = ExpTree.postorder(tree.getLeftChild())
        if tree.rightChild != None:
            Value_tree = Value_tree + ExpTree.postorder(tree.getRightChild())
        Value_tree =   Value_tree + str(tree.getRootVal())
        return Value_tree
        
    def evaluate(tree):
        operator_main = set(['+', '-', '*', '/', '(', ')', '^'])
        if tree == None:
            return 0
        else:
#         	print(tree.key)
        	if tree.key not in operator_main:
        		return tree.key
        	else:
        		left_sum = float(ExpTree.evaluate(tree.leftChild))
        		right_sum = float(ExpTree.evaluate(tree.rightChild))
        		if tree.key == "+":
        			return left_sum + right_sum
        		if tree.key == "-":
        			return left_sum - right_sum
        		if tree.key == "*":
        			return left_sum * right_sum
        		if tree.key == "/":
        			return left_sum / right_sum     
        		if tree.key == "^":
        			return left_sum**right_sum 
                    
                    
    def __str__(self):
        return ExpTree.inorder(self) 
        

# a driver for testing BinaryTree and ExpTree
if __name__ == '__main__':
    # test a BinaryTree
    
    r = BinaryTree('a')
    assert r.getRootVal() == 'a'
    assert r.getLeftChild()== None
    assert r.getRightChild()== None
    assert str(r) == 'a()()'
    
    r.insertLeft('b')
    assert r.getLeftChild().getRootVal() == 'b'
    assert str(r) == 'a(b()())()'
    
    r.insertRight('c')
    assert r.getRightChild().getRootVal() == 'c'
    assert str(r) == 'a(b()())(c()())'
    
    r.getLeftChild().insertLeft('d')
    r.getLeftChild().insertRight('e')
    r.getRightChild().insertLeft('f')
    assert str(r) == 'a(b(d()())(e()()))(c(f()())())'
    assert str(r.getRightChild()) == 'c(f()())()'
    assert r.getRightChild().getLeftChild().getRootVal() == 'f'
    
    # test an ExpTree
    
    postfix = '5 2 3 * +'.split()
    tree = ExpTree.make_tree(postfix)
    assert str(tree) == '(5+(2*3))'
    assert ExpTree.inorder(tree) == '(5+(2*3))'
    assert ExpTree.postorder(tree) == '523*+'
    assert ExpTree.preorder(tree) == '+5*23'
    assert ExpTree.evaluate(tree) == 11.0
    postfix = '5 2 + 3 *'.split()
    tree = ExpTree.make_tree(postfix)
    assert str(tree) == '((5+2)*3)'
    assert ExpTree.inorder(tree) == '((5+2)*3)'
    assert ExpTree.postorder(tree) == '52+3*'
    assert ExpTree.preorder(tree) == '*+523'
    assert ExpTree.evaluate(tree) == 21.0