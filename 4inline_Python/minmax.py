from four_in_line import *

class Node:
    state = None
    value = 0

    children = []

    def __init__(self, state):
        self.state = state

    def expand(self, player):
        for i in range( self.state.X_Size ):
            nstate = self.state.cpy()
            nstate.play(player, i)
            nnode = Node(nstate)
            self.children.append( nnode )

class MinMaxTree:
    root = None
    size = 0

    def __init__( self , inithial_state):
        self.root = Node( inithial_state )
        self.size += 1

    def minmax_rec(self, node, prof, player, plim):
       
        c = node.state.term()

        if( c != 0 or prof == plim ):
            return node.state.val()

        node.expand( player )

        print( len( node.children ) )

        if( player == 1 ):
            player = 2
        else:
            player = 1

        for n in node.children:
            print
            n.state.show()
            self.minmax_rec( node, prof+1, player, plim)

        return node.state.val()

        

    def minmax(self):
        inithial = self.root
        c = inithial.state.term()
        
        if( c != 0 ):
            return c

        val = self.minmax_rec( inithial, 0, 1, 2)

if __name__ == "__main__":
    istate = State()
    tree = MinMaxTree( istate )

    tree.minmax()