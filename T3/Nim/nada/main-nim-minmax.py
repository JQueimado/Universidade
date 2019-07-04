from minmax_nim import *
from nim import *

EXPAN = 4
V = [1,2,3,4]

if __name__ == "__main__":
    istate = State(V)

    tree = MinMaxTree( istate )
    val , n = tree.minmax( EXPAN, P1 ,P1 )
    for i in l:
        print(" result: ")
        i.get_state().show()
    print( "MINMAX value: " + str( val ) )
    print( "Nodes ", )