

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

def entropia1(ff):
    
    counter = 0

    for i in ff:

        if i == '1':

            counter += 1
    
    return counter

def entropiat(ff):
    pass


if __name__ == "__main__":
    
    ff,_,_ = read_file("j.pbm")

    print(entropia1(ff))

    print("Done.")