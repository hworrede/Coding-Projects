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
    	Operators = set(['+', '-', '*', '/', '(', ')', '^'])
        s= Stack()
        for x in postfix:
            # print("read " + x + " and created a node ")
            t= ExpTree(x)
#             if isOperator(x):
            if x in Operators:
                # print(x + "is an operator")
                branch1 = s.pop()
                # print("popped " + branch1.key)
                branch2 = s.pop()
                # print("popped " + branch2.key)
                t.rightChild = branch1
                t.leftChild= branch2
            # else:
            #     print(x + " is an operand  ")
            s.push(t)
            # print(f"push {t.key} into stack")
        t = s.pop()

        # print(f"pop {t.key} ")
        return t

    def preorder(tree):
        # if tree:
        #     print(tree.getRootVal())
        #     ExpTree.preorder(tree.getLeftChild())
        #     ExpTree.preorder(tree.getRightChild())
        
        sVal = ""
        sVal =   sVal + str(tree.key)
        if tree.leftChild != None:
            sVal = sVal + ExpTree.preorder(tree.getLeftChild())
        if tree.rightChild != None:
            sVal = sVal + ExpTree.preorder(tree.getRightChild())
        return sVal
        
    def inorder(tree):
        sVal = ""
        if tree.leftChild != None:
            sVal = "("+ ExpTree.inorder(tree.getLeftChild())
        sVal =   sVal + str(tree.getRootVal()) 
        if tree.rightChild != None:
            sVal = sVal + ExpTree.inorder(tree.getRightChild()) +")"
        return sVal
      
    def postorder(tree):
        sVal = ""
        if tree.leftChild != None:
            sVal = ExpTree.postorder(tree.getLeftChild())
        if tree.rightChild != None:
            sVal = sVal + ExpTree.postorder(tree.getRightChild())
        sVal =   sVal + str(tree.getRootVal())
        return sVal
        
    def evaluate(tree):
        Operators = set(['+', '-', '*', '/', '(', ')', '^'])

        if tree == None:
            return 0
        else: 
            if tree.leftChild not in Operators:
                return tree.leftChild
            if tree.rightChild not in Operators:
                return tree.rightChild
            else:
                left_sum = ExpTree.evaluate(tree.leftChild)
                right_sum = ExpTree.evaluate(tree.rightChild)
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