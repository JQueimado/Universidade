from four_in_line import *
import pickle;

FILE_NAME = "cache.bin"

class Node:
    fp = -1
    value = 0

    children = []

    def __init__(self, state):
        self.dump(state)
        self.children = []

    def load(self):
        f = open(FILE_NAME, "rb")
        f.seek(self.fp)
        return pickle.load(f)

    def dump(self, state):
        f = open(FILE_NAME, "ab")
        self.fp = f.tell()
        pickle.dump(state, f, pickle.HIGHEST_PROTOCOL)

    def get_state(self):
        return self.load()

    def expand(self, player):

        if( len(self.children) != 0 ):
            return

        states = self.get_state().expand_state( player )

        for s in states:
            nnode = Node( s )
            self.children.append( nnode )
        
class MinMaxTree:
    root = None

    def __init__( self , inithial_state):
        self.root = Node( inithial_state )

    def minmax_rec(self, node, prof, player, plim):
        
        state = node.get_state()
        c = state.term()

        inf = float('inf')

        if( c == 1 ):
            state.show()
            print( "win" )
            return inf

        if( c == -1):
            state.show()
            print( "lose" )
            return -inf

        if( plim == prof ):
            return state.val()

        node.expand( player )

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


    def minmax(self, plim):
        inithial = self.root
        c = inithial.get_state().term()
        
        if( c != 0 ):
            return c

        val = self.minmax_rec( inithial, 0, 1, plim)

        return val
