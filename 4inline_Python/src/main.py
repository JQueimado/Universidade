from minmax import *
from four_in_line import *

EXPAN = 7

if __name__ == "__main__":
    istate = State()

    tree = MinMaxTree( istate )
    val , l = tree.minmax( EXPAN, P1 )
    for i in l:
        print(" result: ")
        i.get_state().show()
    print( "MINMAX value: " + str( val ) )