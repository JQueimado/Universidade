
# const #

FILE_TREM = ".best"

def compress (f):
    
    d = {"0":0 , "1":1}
    i = 2

    p = ''

    c = ''

    out = []

    for c in f:
        
        pc = p + c

        if pc in d:
            
            p = pc
        
        else:

            d[pc] = i
            i += 1

            out.append( d.get( p ) )

            p = c

    return out

def write_file (fo, s, fn):

    f = open(fn, 'w+')
    f.write(s)

    for c in fo:
        f.write(' '+ str(c) )

    f.close()

def read_file(fn):
    
    f = open (fn, "r")

    t = f.readline()[:-1]

    s = f.readline()[:-1]

    ff = []

    for l in f:
        for c in l:
            if c != ' ' and c !='\n':
                ff.append(c)

    f.close()

    return ff , t , s

if __name__ == "__main__":
    
    fn = input("Enter image file name:")

    ff,_,s = read_file(fn)

    fo = fn[:-4]+FILE_TREM

    write_file( compress ( ff ), s, fo )

    print("Done.")






