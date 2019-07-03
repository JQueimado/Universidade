from copy import deepcopy

X_Size = 7
Y_Size = 6

P1 = 1
P2 = 2
EP = 0

WIN = 4

################################## State ###################################

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

    ############################## Auciliares ##############################

    def get_line(self, l, matrix):
        return matrix[l]
    
    def get_colum(self, c, matrix):
        l = []
        for i in range(Y_Size):
            l.append( matrix[i][c] )
        return l

    def get_diag_up_bot(self, n, matrix):
        l = []

        if( n < Y_Size ):
            x = 0
            y = Y_Size-1 - n
            for i in range(n+1):
                l.append( matrix[y][x] )
                x += 1
                y += 1
        elif ( n >= Y_Size ):
            n = n - Y_Size + 1
            x = n
            y = 0
            for i in range( X_Size - n):
                l.append( matrix[y][x] )
                x+=1
                y+=1
        return l

    def get_diag_bot_up(self, n, matrix):
        l = []

        if( n < Y_Size ):
            x = 0
            y = n
            for i in range(n+1):
                l.append( matrix[y][x] )
                x += 1
                y -= 1
        elif ( n >= Y_Size ):
            n = n - Y_Size + 1
            x = n
            y = Y_Size - 1
            for i in range( X_Size - n):
                l.append( matrix[y][x] )
                x+=1
                y-=1
        return l

    ############################## End Game Checks ################################

    # check #
    def check(self, line, t_player):
        val = 0
        count1 = 0
        count2 = 0

        for elm in line:
            if( elm == t_player ):
                count1 += 1
                count2 = 0
            elif( elm != t_player and elm != EP ):
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
    def check_lines(self, matrix, t_player):
        for i in range(Y_Size):
            c = self.check( self.get_line(i, matrix), t_player )
            if( c != 0):
                return c
        return 0

    # check_colums #
    def check_colums(self, matrix, t_player):
        for i in range(X_Size):
            c = self.check( self.get_colum(i, matrix), t_player )
            if( c != 0):
                return c
        return 0

    # check_diagonal #
    def check_diagonal_1(self, matrix, t_player):
        for i in range(Y_Size + X_Size -1):
            c = self.check( self.get_diag_bot_up(i, matrix), t_player )
            if( c != 0):
                return c
        return 0

    # check_diagonal_2 #
    def check_diagonal_2(self, matrix, t_player):
        for i in range(Y_Size + X_Size -1):
            c = self.check( self.get_diag_up_bot(i, matrix), t_player )
            if( c != 0):
                return c
        return 0

    def term_state(self, t_player):
        matrix = self.generate_state()
        
        c = self.check_lines(matrix, t_player)
        if c != 0:
            return c

        c = self.check_colums(matrix, t_player)
        if c != 0:
            return c

        c = self.check_diagonal_1(matrix, t_player)
        if c != 0:
            return c

        c = self.check_diagonal_2(matrix, t_player)
        if c != 0:
            return c

        return 0

    ####################### Eval State ############################

    def val_four(self, l, player):
        for e in l:
            if e != player and e != EP:
                return 0
        if l.count(EP) == 0:
            return 0
        return l.count(player)

    def val_lis(self, l, player):
        val = 0
        for i in range( len(l)-(WIN-1) ):
            val += self.val_four( l[i:(i+WIN)], player )
        return val

    def val_lines(self, matrix, player ):
        val = 0
        for i in range(Y_Size):
            val += self.val_lis( self.get_line(i,matrix), player)
        return val

    def val_colums(self, matrix, player ):
        val = 0
        for i in range(X_Size):
            val += self.val_lis( self.get_colum(i,matrix), player)
        return val

    def val_diag_1(self, matrix, player ):
        val = 0
        for i in range(X_Size + Y_Size - 1):
            val += self.val_lis( self.get_diag_bot_up(i,matrix), player)
        return val

    def val_diag_2(self, matrix, player ):
        val = 0
        for i in range(X_Size + Y_Size - 1):
            val += self.val_lis( self.get_diag_up_bot(i,matrix), player)
        return val

    def val(self, player, t_player):
        val = 0
        matrix = self.generate_state()
        val += self.val_lines( matrix, player)
        val += self.val_colums( matrix, player)
        val += self.val_diag_1( matrix, player)
        val += self.val_diag_2( matrix, player)

        if player != t_player:
            return -val

        return val

####################### Main ############################

if __name__ == "__main__":
    state0 = State()

    #state0.add_move(1,0)
    #state0.add_move(1,1)
    #state0.add_move(1,2)
    #state0.add_move(1,3)
    #state0.add_move(1,4)
    state0.add_move(1,5)
    state0.add_move(1,5)

    state0.show()

    print( state0.val(P1, P1) )

    for i in range(X_Size + Y_Size -1):
        if( i == Y_Size):
            print("Done")
        print( state0.get_diag_bot_up(i, state0.generate_state() ))