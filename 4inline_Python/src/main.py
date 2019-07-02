from minmax import *
from four_in_line import *

if __name__ == "__main__":
    istate = State()

    tree = MinMaxTree( istate )
    val , l = tree.minmax( 3, P1 )
    for i in l:
        print(" result: ")
        i.show()
    print( "MINMAX value: " + str( val ) )