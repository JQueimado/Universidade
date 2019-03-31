import math

def read_file_comp(fn):

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

def probabilidades(ff):
    
    counter1 = 0
    
    counter = 0

    for i in ff:

        counter += 1

        if i == '1':

            counter1 += 1
        
    p1 = counter1/ counter
    
    p0 = 1 - p1

    return p0, p1

def entropia(p0, p1):
    
    return (- p0 * math.log(p0, 2) - p1 * math.log(p1, 2))

def condicionada(ff, p0, p1):
    
    d = {"00":0, "01":0, "10":0, "11":0}

    for i in range(len(ff)-1):
        
        c = ff[i] + ff[i+1]

        d[c] += 1

    for i in d:
        d[i] =( d.get(i) / (len(ff)-1) ) 

    ent0 = p0 * ( ( d.get("00") ) * math.log( d.get("00"), 2 ) + ( d.get("01") ) * math.log( d.get("01"), 2 ) )

    ent1 = p1 * ( ( d.get("10") ) * math.log( d.get("10") , 2) + ( d.get("11") ) * math.log( d.get("11") , 2) )

    return - ( ent0 + ent1 )




def comprimido(ff):

    d = {}

    for i in ff:
        
        if i in d:

            d[i] += 1

        else:

            d[i] = 1

    for i in d:

        d[i] = ( d.get(i) / len(ff) )

    ent = 0

    for x in d:

       ent += d.get(x) * math.log( (d.get(x)), 2 )

    return -ent 

if __name__ == "__main__":

    f1 = input("Insira o nome do ficheiro não comprimido: ")
    f2 = input("Insira o nome do ficheiro comprimido: ")
    
    ff1,_,_ = read_file(f1)
    _,ff2 = read_file_comp(f2)

    p0, p1 = probabilidades(ff1)

    ent = entropia(p0, p1)
    print( "A entropia é: %.3f bits" % ent)    
    
    entcon = condicionada(ff1, p0, p1)
    print ("A entropia condicionada é: %.3f bits" % entcon)

    entcomp = comprimido(ff2)
    print ("A entropia comprimida é: %.3f bits" % entcomp)
    
