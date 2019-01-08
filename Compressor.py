
# const #

FILE_TREM = ".best"

def compress (f):
    
    d = {"0":0 , "1":1}
    i = 2

    out = []

    while f != "":         

        p = ""
        s = ""
        count = 0
        
        for s in f:
            if p+s in d:
                p = p+s
                count += 1
            else:
                break

        f = f[count:]
        out.append( d.get( p ) )
        d[p+s] = i
        i += 1
                
                

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

    ff = ""

    for l in f:
        for c in l:
            if c != ' ' and c !='\n':
                ff += c

    f.close()

    return ff , t , s

if __name__ == "__main__":
    
    fn = ""

    while True:
        
        fn = input("Enter file name:")
        
        if not fn.endswith(".pbm"):
            print("ERROR:File format not suported, must end in .pbm")
        else:
            break

    ff,_,s = read_file(fn)

    fo = fn[:-4]+FILE_TREM

    write_file( compress ( ff ), s, fo )

    print("Done. File at: "+ fo)






