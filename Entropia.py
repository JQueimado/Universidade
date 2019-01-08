

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
    
    counter1 = 0
    counter = 0

    for i in ff:

        counter += 1

        if i == '1':

            counter1 += 1
    
    return counter1 ,counter

if __name__ == "__main__":
    
    ff,_,_ = read_file("j.pbm")

    print(entropia1(ff))

    print("Done.")