from four_in_line import *
import pickle;

FILE_NAME = "cache.bin"

inf = 100000000

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
        
class AlfaBetaCut:
    root = None

    def __init__( self , inithial_state):
        self.root = Node( inithial_state )

    def minmax_rec(self, node, prof, t_player, player, plim, alfa, beta):
        
        state = node.get_state()
        c = state.term_state()

        if( c == 1 ):
            state.show()
            print( "win" )
            v = state.val(player, t_player)
            node.value = v
            return v

        if( c == -1):
            state.show()
            print( "lose" )
            v = state.val(player, t_player)
            node.val = v
            return v

        if( plim == prof ):
            v = state.val(player, t_player)
            node.value = v
            return v

        node.expand( player )

        if( player == 1 ):
            p = 2
        else:
            p = 1

        val = 0
        if player == t_player:
            maxval = -inf
            for n in node.children:
                v = self.minmax_rec( n, prof+1, t_player, p, plim, alfa, beta )
                maxval = max( maxval, v )
                alfa = max( alfa, v )
                if beta <= alfa:
                    break
            node.value = maxval
            val = maxval
        else:
            minval = inf
            for n in node.children:
                v = self.minmax_rec( n, prof+1, t_player, p, plim, alfa, beta )
                minval = min(minval,v)
                beta = min( beta, v )
                if beta <= alfa:
                    break
            node.value = minval
            val = minval

        return val


    def build_caminho(self, node):
        val = self.root.value
        node = self.root
        l = []
        while True:
            l.append( node )
            
            if len( node.children ) == 0:
                break

            for e in node.children:
                if e.value == val:
                    node = e
                    break
        return l

    def minmax(self, plim, player):
        inithial = self.root
        c = inithial.get_state().term_state()
        
        if( c != 0 ):
            return c

        val = self.minmax_rec( inithial, 0, 1, player, plim, -inf, inf )

        l = self.   build_caminho( self.root )

        return val, l
