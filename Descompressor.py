FILE_NAME = "j.best"

FILE_TERM = ".pmb"

FILE_OUTPUT = FILE_NAME[:-5]+FILE_TERM

def descompress (f):

    d = {0:"0", 1:"1"}

    i = 2

    c = f[0]

    n = 0

    out = [d.get(c)]

    for nc in range(1,len(f)):
        c = f[nc-1]
        n = f[nc]

        if not n in d:
        
            dout = str(d.get(c)) + str(d.get(c))[0]
            
            out.append(dout)
        
        else:

            out.append( str(d.get(n)) )

            dout = str(d.get(c)) + str(d.get(n))[0]

        d[i] = dout

        i += 1

    return out

def write_file (fo, s, t):

    w, h = 0

    i = 0

    temp = ""
    while fo[i] != " ":
        temp += fo[i]
        i += 1

    w = int( temp )

    temp = ""
    
    while fo[i] != " ":
        temp += fo[i]
        i += 1

        

    pass

def read_file(fn):

    f = open(fn)

    i = 0

    s = ""

    n = ""

    fo = []

    l = f.readline()

    for c in l:
        if c != ' ':
            
            n += c
        
        else:

            i += 1
            
            if i > 2:
                
                fo.append(int(n))
            
            else:
            
                s += n+' '

            n = ''

    fo.append(int (n))
    return s[:-1] , fo


if __name__ == "__main__":
    
    s, fa = read_file(FILE_NAME)

    descompress(fa))
