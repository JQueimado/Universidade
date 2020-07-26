from nim import *
from minmax_nim import *
from alfabetacut_nim import *
AI = P1
US = P2

if __name__ == "__main__":
    exp = int(input("nivel de expanção:"))
    alg = input("minmax ou alfabeta?")
    
    nV = int(input("numero de varas:"))
    fp = input("jogar primeiro:")
        
    V = []
    for i in range(nV):
        V.append(int(input("vara "+str(i)+":")))

    state = State(V)
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
        while True:
            print("Joga")
            state.show()
            vara = int( input("vara a jogar:") )
            val = int(input("nos a tirar:"))
            if state.play(US, vara, val):
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