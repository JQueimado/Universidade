import random

######################################################################################
# Função Extract:                                                                    
#   Função que extrai os valores de um fichero e coloca-os em listas para que possam 
#   ser manipulados mais facilmente pelo programa                                   
# Argumentos:
#   fname: FileName->nome do ficheiro de onde extrair os valores
#           Tipo: String
# Retorno:
#   Tuplo formado por um Dicionario e uma lista:
#       Dicionaro->Chaves:palavras a procurar ; Valores:Lista com a posição incial e
#        final da palavra (inicialmente é uma lista vazia)
#       Lista->lista com as linhas do ficheiro correspondentes a sopa de letras
######################################################################################
def Extract (fname):
    dic=dict()
    lst=list()
    try:
        f=open(fname)
        f.seek(0)
    except IOError:
        print('Ficheiro',fname,'Invalido')
        return dict(),list()
    for l in f:
        if l!='\n' and l!='':
            if l[:len(l)-1].isdigit():
                l=l[:len(l)-1]
                n=int(l)
            elif n>0:
                l=l[:len(l)-1]
                dic[l]=[[-1,-1],[-1,-1]]
                n-=1
            else:
                if l[len(l)-1].isalpha():
                    l=l[:len(l)]
                else:
                    l=l[:len(l)-1]
                lst.append(l.lower())
                    
    f.close()
    return dic,lst

        

######################################################################################
# Função Reverse:                                                                    
#   Função que inverte a ordem dos caracteres de uma string                                 
# Argumentos:
#   st: String->string a inverter
#           Tipo: String
# Retorno:
#   String inverssa a string st
######################################################################################
def Reverse (st):
    ls=list()
    
    for c in st:
        ls.append(c)
        
    ls.reverse()
    
    return ''.join(ls)
    
######################################################################################
# Função Find:                                                                    
#   Função que procura uma palavra numa string                                   
# Argumentos:
#   wrd: Word->palavra a procurar
#          Tipo: String
#        st: String->string na qual se procura a palavra
#          Tipo: String
# Retorno:
#   Um valor inteiro que corresponde a posicao inicial da palavra na string se a
#   palavra foi encontrada e -1 se a palavra não foi encontrada
######################################################################################
def Find (wrd,st):
    for c in range(len(st)):
        if len(st)-c >= len(wrd):
            if wrd == st[c:c+len(wrd)]:
                return c
            
    return -1

######################################################################################
# Função Transpos:                                                                    
#   Função que trasforma uma matriz na sua transposta                                   
# Argumentos:
#   lst: Lista->matriz de strings a transpor
#         Tipo: Lista
# Retorno:
#   Retorna uma lista de strings onde cada coluna da matriz inicial corresponde a
#   uma linha da nova matriz
######################################################################################
def Transpos (lst):
    rl=len(lst)*['']
    
    for c in range(len(lst[0])):
        for l in lst:
            rl[c]+=l[c]
            
    return rl
        
        


######################################################################################
# Função DiagSE:                                                                    
#   Função que retorna uma matriz onde as linhas correspomdem as linhas diagonais de
#   outra matriz(do canto superior esquerdo para o canto inferior direito)
# Argumentos:
#   lst: Lista->matriz de strings a converter
#         Tipo: Lista
# Retorno:
#   Retorna uma lista de strings onde cada linha corresponde a sequencia da diagonal
#   da lista incerida
######################################################################################
def DiagSE(lst):
    rlst=list()
    
    for c in range(len(lst)):
        st=''
        x=0
        y=c
        
        while True:
            l=lst[y]
            st+=l[x]
            x+=1
            y+=1
            if x>=len(lst[y-1]) or y>=len(lst):
                break
            
        rlst.append(st)
        
    rlst.reverse()
    
    for c in range(1,len(lst[0])):
        st=''
        x=c
        y=0
        
        while True:
            l=lst[y]
            st+=l[x]
            x+=1
            y+=1
            if x>=len(lst[y-1]) or y>=len(lst):
                break
            
        rlst.append(st)
        
    return rlst
               

######################################################################################
# Função DiagSW:                                                                    
#   Função que retorna uma matriz onde as linhas correspomdem as linhas diagonais de
#   outra matriz(do canto superior direito para o canto inferior esquerdo)
# Argumentos:
#   lst: Lista->matriz de strings a converter
#         Tipo: Lista
# Retorno:
#   Retorna uma lista de strings onde cada linha corresponde a sequencia da diagonal
#   da lista incerida
######################################################################################
def DiagSW(lst):
    rlst=list()
    
    for c in range(len(lst)):
        st=''
        x=0
        y=c
        
        while True:
            l=lst[y]
            st+=l[x]
            x+=1
            y-=1
            if x>=len(lst[y-1]) or y<0:
                break
            
        rlst.append(st)
    
    for c in range(1,len(lst[0])):
        st=str()
        x=c
        y=len(lst)-1
        
        while True:
            l=lst[y]
            st+=l[x]
            x+=1
            y-=1
            if x>=len(lst[y-1]) or y<0:
                break
            
        rlst.append(st)
        
    return rlst

######################################################################################
# Função DataForm:                                                                    
#   Função que formata um conjunto de cordenadas para que sejam mais facilmente lidas
#   pelo utilisador
# Argumentos:
#   data: Data->Lista de coordenadas
#          Tipo: lista
# Retorno:
#   Lista de coordenadas formatadas e um ponto cardeal. Exemplo: ['B1',C3','sudeste']
######################################################################################
def DataForm(data):
    lst=list()
    
    for c in data:
        if c[0]>26:
            l=chr(64+c[0]//26)
            lst.append(l+chr(c[0]-(c[0]//26)*26+64)+str(c[1]))
        else:
            lst.append(chr(c[0]+64)+str(c[1]))
        
    c1=data[0]
    c2=data[1]
    x=c1[0]-c2[0]
    y=c1[1]-c2[1]
    
    if x==0 and y>0:
        lst.append('norte')
    elif x==0 and y<0:
        lst.append('sul')
    elif x<0 and y==0:
        lst.append('este')
    elif x>0 and y==0:
        lst.append('oeste')
    elif x<0 and y>0:
        lst.append('nordeste')
    elif x<0 and y<0:
        lst.append('sudeste')
    elif x>0 and y>0:
        lst.append('nordoeste')
    else:
        lst.append('sudoeste')
        
    return lst
        

    
#FindMain
def MainFind():
    while True:
        filename=input('Nome do ficheiro:')+'.txt'
        chk=Extract(filename)
        if chk!=(dict(),list()):
            break
    palavras,matriz=chk
    matrizDiagSw=DiagSW(matriz)
    matrizDiagSe=DiagSE(matriz)
    matrizTransposta=Transpos(matriz)

    for p in palavras:
        reverseP=Reverse(p)
        cords=palavras[p]
        le=max(len(matriz),len(matriz[0]))
        for c in range(1,le*2):
            if c<le+1:
                
                n=Find(p,matriz[c-1])+1
                if n!=0:
                    cords=[[n,c],[n+len(p)-1,c]]
                    break
                
                n=Find(reverseP,matriz[c-1])+1
                if n!=0:
                    cords=[[n+len(p)-1,c],[n,c]]
                    break

                n=Find(p,matrizTransposta[c-1])+1
                if n!=0:
                    cords=[[c,n],[c,n+len(p)-1]]
                    break

                n=Find(reverseP,matrizTransposta[c-1])+1
                if n!=0:
                    cords=[[c,n+len(p)-1],[c,n]]
                    break
                       
            n=Find(p,matrizDiagSe[c-1])+1
            if n!=0:
                if c<=le:
                    x=n
                    y=le-c+n
                else:
                    x=c-le+n
                    y=n
                cords=[[x,y],[x+len(p)-1,y+len(p)-1]]
                break

            n=Find(reverseP,matrizDiagSe[c-1])+1
            if n!=0:
                if c<=le:
                    x=n
                    y=le-c+n
                else:
                    x=c-le+n
                    y=n
                cords=[[x+len(p)-1,y+len(p)-1],[x,y]]
                break

            n=Find(p,matrizDiagSw[c-1])+1
            if n!=0:
                if c<=le:
                    x=n
                    y=c-n+1
                else:
                    x=c-le+n
                    y=le-n+1
                cords=[[x,y],[x+len(p)-1,y-len(p)+1]]
                break

            n=Find(reverseP,matrizDiagSw[c-1])+1
            if n!=0:
                if c<=le:
                    x=n
                    y=c-n+1
                else:
                    x=c-le+n
                    y=le-n+1
                cords=[[x+len(p)-1,y-len(p)+1],[x,y]]
                break
    
        palavras[p]=cords

    print('------------------')
    for p in palavras:
        lst=DataForm(palavras[p])
        print(p,':',lst[0],'-',lst[1],':',lst[2])
    print('\n')

################################################################################################

######################################################################################
# Função Import:                                                                    
#   Função que extrai os valores de um fichero e coloca-os em listas para que possam 
#   ser manipulados mais facilmente pelo programa                                   
# Argumentos:
#   file: nome do ficheiro de onde extrair os valores
#           Tipo: Str
# Retorno:
#   Tuplo formado por duas listas:
#       Lista1->Lista com as dimenções da matriz a gerar 
#       Lista2->Lista com as palavras a colocar na matriz
######################################################################################
def Import(file):
    try:
        f=open(file)
    except IOError:
        print('Ficheiro',file,'não encontrado')
        return list(),list()
    
    lst=list()
    f.seek(0)
    size=f.readline()
    size=size[:len(size)-1]
    if ' 'in size:
        s=size.split()
    else:
        s=size.split(',')
    for l in f:
        if l !='' or l!='\n':
            if l[len(l)-1].isalpha():
                l=l[:len(l)]
            else:
                l=l[:len(l)-1]    
            lst.append(l.lower())
    f.close()
    return s,lst

######################################################################################
# Função Export:                                                                    
#   Função que compõe o ficheiro de output do programa                                    
# Argumentos:
#   wl: WordList->Lista com as palavras da matriz
#           Tipo: List
#   nxn: Matriz->Lista com listas correspondentes a cada linha da matriz gerada
#           Tipo:List
#   file: Ficheiro->nome do ficheiro para o qual se pretende dar output
#           Tipo:String
# Retorno:
#   Ficheiro de texto com as palavras e a matriz gerada
######################################################################################
def Export(wl,nxn,file):
    f=open(file,'w+')
    f.write(str(len(wl))+'\n')
    for w in wl:
        f.write(w+'\n')
    for y in nxn:
        f.write(''.join(y)+'\n')
    f.close()

######################################################################################
# Função Gerar:                                                                    
#   Função que gera uma matriz vazia                                    
# Argumentos:
#   n,m: ->correspondem respetivamente ao comprimento e largura da matriz a gerar
#           Tipo: Int
# Retorno:
#   Lista de Listas costituidas por espaços correspondem aos elementos da matriz
######################################################################################
def Gerar(n,m):
    lsty=list()
    for y in range(m):
        lstx=list()
        for x in range(n):
            lstx.append(' ')
        lsty.append(lstx)
    return lsty

######################################################################################
# Função Seth:                                                                    
#   Função que verifica e ao mesmo tempo coloca uma palavra numa matriz na horizontal                                 
# Argumentos:
#   x,y: correspondem respetivamente a distancia horisontal e vertical o centro 0 da
#    matriz.
#       Tipo: Int
#   w: Word:palavra a colocar na matriz
#       Tipo: Str
#   l: matriz onde se pretende colocar a palavra
#       Tipo: List
# Retorno:
#   Matriz com a palavra colocada nas coordenadas x,y se a palavra couber nessa
#   direção e deve retornar a matriz inalterada se a palavra não couber na posição
######################################################################################
def Seth(x,y,w,l):
    lst=list(l[y])
    rl=list(l)
    for xx in range(len(w)):
        if lst[x+xx]==' ' or lst[x+xx]==w[xx]:
            lst[x+xx]=w[xx]
        else:
            return rl
    l[y]=lst
    return l
            
######################################################################################
# Função Setv:                                                                    
#   Função que verifica e ao mesmo tempo coloca uma palavra numa matriz na vertical                                 
# Argumentos:
#   x,y: correspondem respetivamente a distancia horisontal e vertical da posição 0 da
#    matriz.
#       Tipo: Int
#   w: Word:palavra a colocar na matriz
#       Tipo: Str
#   l: matriz onde se pretende colocar a palavra
#       Tipo: List
# Retorno:
#   Matriz com a palavra colocada nas coordenadas x,y se a palavra couber nessa
#   direção e deve retornar a matriz inalterada se a palavra não couber na posição
######################################################################################
def Setv(x,y,w,l):
    rl=list(l)
    for yy in range(len(w)):
        lst=list(l[y+yy])
        if lst[x]==' ' or lst[x]==w[yy]:
            lst[x]=w[yy]
            l[y+yy]=lst
        else:
            return rl
    return l

######################################################################################
# Função Setse:                                                                    
#   Função que verifica e ao mesmo tempo coloca uma palavra numa matriz na diagonal
#   descendente
# Argumentos:
#   x,y: correspondem respetivamente a distancia horisontal e vertical o centro 0 da
#    matriz.
#       Tipo: Int
#   w: Word:palavra a colocar na matriz
#       Tipo: Str
#   l: matriz onde se pretende colocar a palavra
#       Tipo: List
# Retorno:
#   Matriz com a palavra colocada nas coordenadas x,y se a palavra couber nessa
#   direção e deve retornar a matriz inalterada se a palavra não couber na posição
######################################################################################
def Setse(x,y,w,l):
    rl=list(l)
    for p in range(len(w)):
        lst=list(l[y+p])
        if lst[x+p]==' ' or lst[x+p]==w[p]:
            lst[x+p]=w[p]
            l[y+p]=lst
        else:
            return rl
    return l

######################################################################################
# Função Setsw:                                                                    
#   Função que verifica e ao mesmo tempo coloca uma palavra numa matriz na diagonal
#   ascendente
# Argumentos:
#   x,y: correspondem respetivamente a distancia horisontal e vertical o centro 0 da
#    matriz.
#       Tipo: Int
#   w: Word:palavra a colocar na matriz
#       Tipo: Str
#   l: matriz onde se pretende colocar a palavra
#       Tipo: List
# Retorno:
#   Matriz com a palavra colocada nas coordenadas x,y se a palavra couber nessa
#   direção e deve retornar a matriz inalterada se a palavra não couber na posição
######################################################################################
def Setsw(x,y,w,l):
    rl=list(l)
    for p in range(len(w)):
        lst=list(l[y+p])
        if lst[x-p]==' ' or lst[x-p]==w[p]:
            lst[x-p]=w[p]
            l[y+p]=lst
        else:
            return rl
    return l

######################################################################################
# Função Fill:                                                                    
#   Função que preenche a matriz com letras geradas aleatoriamente
# Argumentos:
#   nxn:Matriz a preencher
#       Tipo:List
# Retorno:
#   Matriz preenchida
######################################################################################            
def Fill(nxn):
    for y in range(len(nxn)):
        lst=nxn[y]
        for x in range(len(lst)) :
            if lst[x]==' ':
                lst[x]=chr(random.randint(ord('A'),ord('Z')))
    return nxn

######################################################################################
# Função Position:                                                                    
#   Função que preenche a matriz com palavras aleatoriamente
# Argumentos:
#   size:Lista com o coprimento e largura da matriz a gerar respetivamente
#       Tipo:List
#   lst:Lista de palavras a colocar na matriz
# Retorno:
#   Matriz preenchida de palavras
######################################################################################           
def Position(size,lst):
    n=int(size[0])
    m=int(size[1])
    
    nxn=Gerar(n,m)
    
    for palavra in lst:
        while True:
            x=random.randint(0,n-1)
            y=random.randint(0,m-1)
            d=random.randint(1,8)
            if (d==1 or d==2) and x+len(palavra)-1<n:
                ver=list(nxn)
                if d==2:
                    palavra=Reverse(palavra)
                nxn=Seth(x,y,palavra.upper(),nxn)
                if ver!=nxn:
                    break

            if (d==3 or d==4) and y+len(palavra)-1<m:
                ver=list(nxn)
                if d==4:
                    palavra=Reverse(palavra)
                nxn=Setv(x,y,palavra.upper(),nxn)
                if ver!=nxn:
                    break

            if (d==5 or d==6) and y+len(palavra)-1<m and x+len(palavra)-1<n:
                ver=list(nxn)
                if d==6:
                    palavra=Reverse(palavra)
                nxn=Setse(x,y,palavra.upper(),nxn)
                if ver!=nxn:
                    break
                
            if (d==7 or d==8) and  y+len(palavra)-1<m and x-len(palavra)+1>0:
                ver=list(nxn)
                if d==8:
                    palavra=Reverse(palavra)
                nxn=Setsw(x,y,palavra.upper(),nxn)
                if ver!=nxn:
                    break
    return nxn

#MainGerar
def MainGerar():
    while True:
        fileI=str(input('Nome do ficheiro a importar:'))+'.txt'
        chk=Import(fileI)
        if chk!=(list(),list()):
            size,lst=chk
            break
    fileO=str(input('Nome do ficheiro para exportar:'))+'.txt'
    while True:
        nxn=Position(size,lst)
        for l in nxn:
            print(l)
        resposta=input('Gerar novamente?(S \ N)').lower()
        while resposta!='s' and resposta!='n':
            resposta=input('Invalida:').lower()
        if resposta=='n':
            break
    Fill(nxn)
    Export(lst,nxn,fileO)
    print('Feito\n')

##############################################################################################

#Menu + Corpo do programa
while True:
    while True:
        print('Operações:'  )
        print(' 1-Encontrar')
        print(' 2-Gerar'    )
        print(' 3-sair'     )
        r=input()
        if r=='1'or r=='2' or r=='3':
            res=int(r)
            break
        else:
            print('Resposta invalida')
    if res==1:
        MainFind()
    elif res==2:
        MainGerar()
    else:
        break
