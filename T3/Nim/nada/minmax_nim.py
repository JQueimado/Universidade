from nim import *
import pickle;

FILE_NAME = "cache.bin"

N_NODE = 0

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

    def minmax_rec(self, node, prof, t_player, player, plim, n_node):
        
        state = node.get_state()
        c = state.term_state(t_player)

        n_node += 1

        if( c == 1 ):
            #state.show()
            #print( "win" )
            v = state.val(player, t_player)
            node.value = v
            return v, n_node

        if( c == -1):
            #state.show()
            #print( "lose" )
            v = state.val(player, t_player)
            node.val = v
            return v, n_node

        if( plim == prof ):
            #state.show()
            v = state.val(player, t_player)
            node.value = v
            return v, n_node

        node.expand( player )

        if( player == 1 ):
            p = 2
        else:
            p = 1

        l = []

        for n in node.children:
            v = self.minmax_rec( n, prof+1, t_player, p, plim, n_node)
            l.append( v )

        if( player == t_player ):
            val = max(l)
        else:
            val = min(l)

        node.value = val

        return val ,n_node


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

    def minmax(self, plim, player, t_player):
        inithial = self.root
        c = inithial.get_state().term_state(t_player)
        
        if( c != 0 ):
            return c

        val, n_node = self.minmax_rec( inithial, 0, player, t_player, plim, 0)

        l = self.build_caminho( self.root )

        return val, l, n_node 
