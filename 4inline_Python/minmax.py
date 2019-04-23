from four_in_line import *

class Node:
    state = None
    value = 0

    parent = None
    children = []

    def __init__(self, state, parent):
        self.state = state
        self.parent = parent

    def expand(self, player):
        for i in range( self.state.X_Size ):
            nstate = self.state.cpy()
            nstate.play(player, i)
            nnode = Node(nstate, self)
            self.children.append( nnode )

class MinMaxTree:
    root = None
    size = 0

    def __init__( self , inithial_state):
        self.root = Node( inithial_state, None )
        self.size += 1

    def minmax_rec(self, node, prof):
        
        c = node.state.term()

        # leaf #
        if( c != 0 ):
            val = node.state.val()
            node.val = val
            return val
        
        # branch #
        node.expand()
        l = []

        for i in node.children():
            val = minmax_rec( i, prof+1 )
            i.val = val
            l.append( val )

        if( (prof % 2) == 0 ):
            val = min(l)
        else:
            val = max(l)

        node.val = val
        return val

        pass

    def minmax(self):
        inithial = self.root
        c = inithial.state.term()
        
        if( c != 0 ):
            return c

        val = minmax_rec( inithial, 0 )

if __name__ == "__main__":
    istate = State()
    tree = MinMaxTree( istate )

    tree.minmax()

    for i in tree.root.children:
        print()
        i.state.show()