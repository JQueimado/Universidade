class Node:

    def __init__(self, value, tipo):
        self.value = value
        self.type = tipo
        self.left_child = None
        self.right_child = None

    def print_node(self):
        print(str(self.value) + "-" + str(self.type))

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
            self.root.print_node()
            self.root.left_child.printTree()
            self.root.right_child.printTree()
            print("")

if __name__ == "__main__":
    
    tree = Tree()

    tree.insert(1, "cona")
    tree.insert(2, "cona")
    tree.insert(3, "cona")


    tree.printTree()