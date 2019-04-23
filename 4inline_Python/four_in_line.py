from copy import deepcopy

class State:
    X_Size = 7
    Y_Size = 6

    P1 = 1
    P2 = 2
    EP = 0

    WIN = 4

    matrix = []

    # constuc #
    def __init__ (self):
        for i in range(self.Y_Size):
            sub = []
            
            for j in range(self.X_Size):
                sub.append(self.EP)
            
            self.matrix.append(sub)

    def cpy( self ):
        ns = State()

        ns.matrix = deepcopy( self.matrix )
        
        return ns

    # play #
    def play(self, player, colum):
        pos = 0

        if( self.matrix[0][colum] != 0 ):
            return

        for pos in range(self.Y_Size):
            if( self.matrix[pos][colum] != 0 ):
                pos -= 1
                break

        self.matrix[pos][colum] = player

    def show(self):
        for i in range(self.Y_Size):
            s = ""
            
            for j in range(self.X_Size):
                s += str(self.matrix[i][j]) + " "

            print(s)

    # check #
    def check(self, line):
        val = 0
        count1 = 0
        count2 = 0

        for elm in line:
            if( elm == self.P1 ):
                count1 += 1
                count2 = 0
            elif( elm == self.P2 ):
                count1 = 0
                count2 += 1

            if( count1 == self.WIN ):
                return 1

            if( count2 == self.WIN ):
                return -1
        
        return 0

    # check lines #
    def check_lines(self):
        for i in range(self.Y_Size):
            c = self.check( self.matrix[i] )
            if( c != 0):
                return c
        return 0

    # get colum #
    def get_colum(self, colum):
        c = []

        for i in range(self.Y_Size):
            line = self.matrix[i]
            c.append(line[colum])

        return c

    # check_colums #
    def check_colums(self):
        
        for i in range(self.X_Size):
            col = self.get_colum(i)

            c = self.check(col)

            if( c != 0 ):
                return c
        
        return 0

    # check_diagonal #
    def check_diagonal_1(self):
       
       # 0 to half #
        for i in range(self.Y_Size - 1, -1, -1):
            l = []
            x = 0
            y = i

            for j in range( self.Y_Size - i):
                l.append( self.matrix[y][x] )
                x += 1
                y += 1

            c = self.check(l)

            if( c != 0):
                return c

        # half to 7 #
        for i in range(1, self.X_Size):
            l = []
            x = i
            y = 0

            for j in range( self.Y_Size - i + 1 ):
                l.append( self.matrix[y][x] )
                x += 1
                y += 1

            c = self.check(l)

            if( c != 0):
                return c

        return 0

    # check_diagonal_2 #
    def check_diagonal_2(self):
        
        for i in range(self.X_Size - 1):
            l = []
            x = i
            y = 0

            for j in range( i + 1 ):
                l.append( self.matrix[y][x] )
                x -= 1 
                y += 1

            c = self.check(l)

            if( c != 0):
                return c

        for i in range( self.Y_Size ):
            l = []
            x = self.X_Size -1
            y = i

            for j in range( self.Y_Size - i, 0, -1):
                l.append( self.matrix[y][x] )
                x -= 1
                y += 1

            c = self.check(l)

            if( c != 0):
                return c
        
        return 0

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

    def val_point(self, x, y ):
        score = 0

        l = []

        print(l)

        return score

    # val #
    def val(self):
        score = 0

        x = 0
        y = 0

        for y in range( self.Y_Size ):
            for x in range( self.X_Size ):
                val = self.matrix[y][x]                    
                    

## main ##
if __name__ == "__main__":
    state0 = State()

    state0.play(1,0)
    state0.play(1,0)
    state0.play(1,0)
    state0.play(1,0)

    state0.show()

    print( state0.val_point( 0, 5 ) )