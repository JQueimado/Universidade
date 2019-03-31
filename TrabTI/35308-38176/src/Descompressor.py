FILE_NAME = "j.best"

FILE_TERM = ".pbm"

FILE_OUTPUT = FILE_NAME[:-5]+"_exported"+FILE_TERM

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
            
            for it in dout:
                out.append(it)
        
        else:

            temp = str(d.get(n))

            for it in temp:
                out.append(it)

            dout = str(d.get(c)) + str(d.get(n))[0]

        d[i] = dout

        i += 1

    return out

def write_file (fo, s, n):

    w = 0
    h = 0

    i = 0

    temp = ""
    
    for c in s:
        i += 1
        if c == ' ':
            break
    
    w = int( s[:-i] )

    f = open(n, 'w+')

    f.write("P1\n")
    f.write(s+'\n')

    i = 0

    for c in fo:
        
        f.write(c)
        i += 1
        
        if i == w:
            f.write('\n')
            i = 0
        else:
            f.write(' ')



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
    
    fn = ""

    while True:
        
        fn = input("Enter file name:")
        
        if not fn.endswith(".best"):
            print("ERROR:File format not suported, must end in .best")
        else:
            break

    s, fa = read_file(fn)

    a = descompress(fa)

    fo = fn[:-5] + "_exported" + FILE_TERM

    write_file(a, s, fo)

    print("Done. File at: " + fo)
