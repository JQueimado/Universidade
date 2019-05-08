from copy import deepcopy

X_Size = 7
Y_Size = 6

P1 = 1
P2 = 2
EP = 0

WIN = 4

class State:
    moves = []

    # constuc #
    def __init__ (self):
        self.moves = []

    # copy state #
    def cpy( self ):
        ns = State()
        ns.moves = deepcopy( self.moves )
        return ns

    # create empty matrix #
    def generate_empty(self):
        matrix = []
        for i in range(Y_Size):
            sub = []
            for j in range(X_Size):
                sub.append(EP)
            matrix.append(sub)
        return matrix

    # play #
    def play(self, matrix, player, colum):
        pos = 0

        if( matrix[0][colum] != 0 ):
            return False

        for pos in range(Y_Size):
            if( matrix[pos][colum] != 0 ):
                pos -= 1
                break

        matrix[pos][colum] = player
        return True

    # recreate state #
    def generate_state(self):
        matrix = self.generate_empty()
        for m in self.moves:
            p, c = m
            self.play(matrix, p, c)
        return matrix

    # prints state #
    def show(self):
        matrix = self.generate_state()

        for i in range(Y_Size):
            s = ""
            for j in range(X_Size):
                s += str(matrix[i][j]) + " "
            print(s)

    # add move #
    def add_move(self, player, colum):
        self.moves.append((player, colum))

    # expand state #
    def expand_state(self, player):
        l = []
        for i in range(X_Size):
            temp = self.cpy()
            matrix = temp.generate_state()
            if ( self.play(matrix, player, i) ):
                temp.add_move(player, i)
                l.append(temp)
        return l

    ############################## End Game Checks ################################

    # check #
    def check(self, line):
        val = 0
        count1 = 0
        count2 = 0

        for elm in line:
            if( elm == P1 ):
                count1 += 1
                count2 = 0
            elif( elm == P2 ):
                count1 = 0
                count2 += 1

            if( elm == EP ):
                count1 = 0
                count2 = 0

            if( count1 == WIN ):
                return 1

            if( count2 == WIN ):
                return -1
        
        return 0

    # check lines #
    def check_lines(self):
        matrix = self.generate_state()
        for i in range(Y_Size):
            c = self.check( matrix[i] )
            if( c != 0):
                return c
        return 0

    # get colum #
    def get_colum(self, colum):
        matrix = self.generate_state()
        c = []
        matrix = self.generate_state()
        for i in range(Y_Size):
            line = matrix[i]
            c.append(line[colum])
        return c

    # check_colums #
    def check_colums(self):
        
        for i in range(X_Size):
            col = self.get_colum(i)

            c = self.check(col)

            if( c != 0 ):
                return c
        
        return 0

    # check_diagonal #
    def check_diagonal_1(self):
        matrix = self.generate_state()
        # 0 to half #
        for i in range(Y_Size - 1, -1, -1):
            l = []
            x = 0
            y = i

            for j in range( Y_Size - i):
                l.append( matrix[y][x] )
                x += 1
                y += 1

            c = self.check(l)

            if( c != 0):
                return c

        # half to 7 #
        for i in range(1, X_Size):
            l = []
            x = i
            y = 0

            for j in range( Y_Size - i + 1 ):
                l.append( matrix[y][x] )
                x += 1
                y += 1

            c = self.check(l)

            if( c != 0):
                return c

        return 0

    # check_diagonal_2 #
    def check_diagonal_2(self):
        matrix = self.generate_state()

        for i in range(X_Size - 1):
            l = []
            x = i
            y = 0

            for j in range( i + 1 ):
                l.append( matrix[y][x] )
                x -= 1 
                y += 1

            c = self.check(l)

            if( c != 0):
                return c

        for i in range( Y_Size ):
            l = []
            x = X_Size -1
            y = i

            for j in range( Y_Size - i, 0, -1):
                l.append( matrix[y][x] )
                x -= 1
                y += 1

            c = self.check(l)

            if( c != 0):
                return c
        
        return 0

    # end game #
    def term(self):
        c = self.check_lines()
        if( c != 0 ):
            return c

        c = self.check_colums()
        if( c != 0 ):
            return c

        c = self.check_diagonal_1()
        if( c != 0 ):
            return c

        c = self.check_diagonal_2()
        if( c != 0 ):
            return c

        return 0

    ####################### Eval State ############################

    # evals colums #
    def val_col(self):
        s = 0

        for i in range(Y_Size):
            # gets colum values #
            l = self.get_colum( i )

            # finds possible winner #
            c = 0

            for e in l:
                if( e != EP ):
                    break
                c += 1

            # if no player then valueles #
            if( c >= len( l ) ):
                continue

            # gets chances for player #
            t = l[c]
            p = 1

            if( t == P2 ):
                p = -1

            count = 0
            j = 0

            for j in range( c, len( l ) ):
                if( l[j] != t ):
                    break
                count += p

            # if any player cant win then its valueles #
            if( j < WIN ):
                continue

            s += count

        return s

    def val_line(self, l):
        count = 0
        val = 0
        t = EP

        i = 0
        while True:
            e = l[i]
            i += 1

            if( e == P1 or e == EP):
                val += 1

            if( e == P2):
                pass

            if( i >= len(l)):
                break

        return count

    def val_lines( self ):
        matrix = self.generate_state()
        s = 0
        for l in matrix:
            self.val_line(l)

    # val #
    def val(self):
        s = self.val_col()

        return s

####################### Main ############################

if __name__ == "__main__":
    state0 = State()

    state0.add_move(1,1)
    state0.add_move(1,2)
    state0.add_move(1,3)
    state0.add_move(1,4)
    state0.add_move(2,6)

    state0.show()

    expancion = state0.expand_state(1)

    print()
    print( state0.term() )

    print()
    print( state0.val() )

    for ex in expancion:
        print()
        ex.show()
