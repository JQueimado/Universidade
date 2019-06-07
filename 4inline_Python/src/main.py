from minmax import *
from four_in_line import *

if __name__ == "__main__":
    istate = State()

    tree = MinMaxTree( istate )

    print( tree.minmax( 8 ) )