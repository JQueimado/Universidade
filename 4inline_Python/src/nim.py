from copy import deepcopy

P1 = 1
P2 = 2

class State:
    tab = []
    player = 0
    def __init__(self, varas):
        self.tab = varas
        self.player = 0

    # copy state #
    def cpy( self ):
        ns = State([])
        ns.tab = deepcopy( self.tab )
        ns.player = 0
        return ns

    def play(self, player, colum, val):
        matrix = self.tab
        if( colum < 0 or colum >= len(matrix) ):
            return False
        if(matrix[colum] == 0 or matrix[colum] < val):
            return False
        else:
            matrix[colum] -= val
            self.player = player
        return True

    def generate_state(self):
        return self.tab

    def term_state(self, t_player):
        for e in self.tab:
            if e != 0:  
                return 0
        if self.player == t_player:
            return 1
        else:
            return -1

    def show(self):
        aux_state = self.cpy()
        l = []
        while( not aux_state.term_state(1) ):
            l.append( deepcopy( aux_state.tab ))
            for i in range(len(aux_state.tab)):
                aux_state.play( 1, i, 1)

        l.reverse()
        for e in l:
            s=""
            for i in e:
                s += " "
                if( i != 0 ):
                    s+="."
                else:
                    s+=" "
            print(s)
        s = ""
        for e in self.tab:
            s+= " " + str(e)
        print(s, "player "+ str(self.player))

    def expand_state(self, player):
        l = []
        for e in range( len( self.tab ) ):
            if self.tab[e] == 0:
                continue
            for i in range( 1, self.tab[e]+1 ):
                ns = self.cpy()
                if not ns.play( player, e, i ):
                    continue
                l.append(ns)
        return l

    def val(self, player, t_player):
        n = sum(self.tab)
        if( player == t_player):
            return n
        return -n

if __name__ == "__main__":
    V = [1,2,3,4]
    state = State(V)
    state.show()
    l = state.expand_state(P1)
    print("expande pra: ")
    for e in l:
        e.show()