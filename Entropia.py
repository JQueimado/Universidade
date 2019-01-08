

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
    
    print(read_file("j.pbm"))

    print("Done.")