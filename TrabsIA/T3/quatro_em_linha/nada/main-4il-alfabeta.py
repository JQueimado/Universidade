from alfabetacut_4il import *
from four_in_line import *

EXPAN = 7

if __name__ == "__main__":
    istate = State()

    tree = AlfaBetaCut( istate )
    val , nn_node = tree.minmax( EXPAN, P1, P1 )

    print( "MINMAX value: " + str( val ) )
    print( nn_node )