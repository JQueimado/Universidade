from alfabetacut_nim import *
from nim import *

EXPAN = 7
V = [1,2,3,4]

if __name__ == "__main__":
    istate = State(V)

    tree = AlfaBetaCut( istate )
    val , l = tree.minmax( EXPAN, P1 )
    for i in l:
        print(" result: ")
        i.get_state().show()
    print( "MINMAX value: " + str( val ) )