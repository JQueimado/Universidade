from four_in_line import *
from minmax_4il import *
from alfabetacut_4il import *

AI = P1
US = P2

if __name__ == "__main__":
    exp = int(input("nivel de expanção:"))
    alg = input("minmax ou alfabeta?")
    
    fp = input("jogar primeiro:")

    state = State()
    if alg == "minmax":
        tree = MinMaxTree( state )
    else:
        tree = AlfaBetaCut( state )

    if fp != "s":
        tree.minmax(exp, AI, AI)
    
        for i in tree.root.children:
            if i.value == tree.root.value:
                state = i.get_state()
                break

    f = state.term_state(AI)
    if f == 1:
        print("GANHEI") 
    elif f == -1:
        print("Ganhas-te")

    while state.term_state(P1) == 0:
        matrix = state.generate_state()
        while True:
            print("Joga")
            state.show()
            vara = int( input("linha a jogar:") )
            vara -= 1
            if state.play( matrix, US, vara ):
                state.add_move(US, vara)
                break
            print("Jogada invalida")

        f = state.term_state(AI)
        if f == 1:
            print("GANHEI")
            break
        elif f == -1:
            print("Ganhas-te")
            break

        tree = MinMaxTree( state.cpy() )
        tree.minmax( exp, AI, AI )

        for i in tree.root.children:
            if i.value == tree.root.value:
                state = i.get_state()
                break

        f = state.term_state(AI)
        if f == 1:
            print("GANHEI")
            break
        elif f == -1:
            print("Ganhas-te")
            break