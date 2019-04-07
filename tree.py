class Node:

    def __init__(self, value, tipo):
        self.value = value
        self.type = tipo
        self.left_child = None
        self.right_child = None

class Tree:
    def __init__(self):
        self.root = None
    
    def insert(self, value, tipo):
        if self.root == None:
            self.root = Node(value, tipo)

        elif self.root.left_child == None:
            self.root.left_child.value = value
            self.root.left_child.type = tipo
        
        elif self.root.right_child == None:
            self.root.right_child.value = value
            self.root.right_child.type = tipo
        
        else:
            self.root.left_child.insert(value, tipo)
            self.root.right_child.insert(value, tipo)
        
    def printTree(self):
        if self.root:
            self.root.printTree()
            print("")

