from four_in_line import *

class Node:
    state = None
    value = 0

    children = []

    def __init__(self, state):
        self.state = state
        self.children = []

    def expand(self, player):

        if( len(self.children) != 0 ):
            return

        for i in range( self.state.X_Size ):
            nstate = self.state.cpy()
            if( not nstate.play(player, i) ):
                continue
            nnode = Node( nstate )
            self.children.append( nnode )

class MinMaxTree:
    root = None

    def __init__( self , inithial_state):
        self.root = Node( inithial_state )

    def minmax_rec(self, node, prof, player, plim):
       
        print(id(node), prof)
        node.state.show()

        c = node.state.term()

        inf = float('inf')

        if( c == 1 ):
            print( "win" )
            return inf

        if( c == -1):
            print( "lose" )
            return -inf

        if( plim == prof ):
            print ("leaf")
            return node.state.val()

        node.expand( player )

        count = 0
        for n in node.children:
            print(count)
            n.state.show()
            count += 1

        if( player == 1 ):
            p = 2
        else:
            p = 1

        l = []

        for n in node.children:
            l.append( self.minmax_rec( n, prof+1, p, plim) )

        if( player == 1 ):
            val = max(l)
        else:
            val = min(l)

        return val


    def minmax(self):
        inithial = self.root
        c = inithial.state.term()
        
        if( c != 0 ):
            return c

        val = self.minmax_rec( inithial, 0, 1, 10)

        return val

if __name__ == "__main__":
    istate = State()

    tree = MinMaxTree( istate )

    print( tree.minmax() )