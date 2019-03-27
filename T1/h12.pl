%estado inicial (posição do branco, lista de listas com linhas colunas)
%estado_inicial(((2,2),[[2,1,4],[3,b,6],[5,7,8]])).
estado_inicial(((2,1),[[1,b,3],[4,2,5],[6,7,8]])).

%estado final
estado_final(((1,1),[[b,1,3],[4,2,5],[6,7,8]])).

%op(Estado_act,operador,Estado_seg,Custo)
op(((X,Y),L),sobe,((X,Z),L1),1):- Y<3, Z is Y+1, substitui(V,b,(X,Z),L,L0),
                                substitui(b,V,(X,Y),L0,L1).  
op(((X,Y),L),desce,((X,Z),L1),1):- Y>1, Z is Y-1, substitui(V,b,(X,Z),L,L0),
                                substitui(b,V,(X,Y),L0,L1).  
op(((X,Y),L),esq,((Z,Y),L1),1):-  X>1, Z is X-1, substitui(V,b,(Z,Y),L,L0),
                                substitui(b,V,(X,Y),L0,L1).  
op(((X,Y),L),dir,((Z,Y),L1),1):-  X<3, Z is X+1, substitui(V,b,(Z,Y),L,L0),
                                substitui(b,V,(X,Y),L0,L1).  

substitui(Vi,Vf,(Y,X),Li,Lf):- retira(X,Fi,Ff,Li,Lf), retira(Y,Vi,Vf,Fi,Ff).

retira(1,X,Y,[X|R],[Y|R]).
retira(N,X,Y,[A|R],[A|S]):- M is N-1, retira(M,X,Y,R,S).

%heuristica para estimar distancia h(Estado,Valor)

h1((_,E),Val):- estado_final((_,Ef)), distancia_h11(E,Ef,0,Val).


h2((_,E),Val):- estado_final((_,Ef)), distancia_h22(E,Ef,Val).

distancia_h11([],[],Nc,Nc). %h1 origem - fim
distancia_h11([X|Ec],[X|Ef],Nc,Nf):- !,distancia_h11(Ec,Ef,Nc,Nf). 
distancia_h11([X|Ec],[Y|Ef],Nc,Nf):- distintas(X,Y,Nc,Nf0),
                                        distancia_h11(Ec,Ef,Nf0,Nf). 
distintas([],[],Nc,Nc).
distintas([b|R],[_|S],Nc,Nf):- !,distintas(R,S,Nc,Nf).
distintas([X|R],[X|S],Nc,Nf):- distintas(R,S,Nc,Nf).
distintas([X|R],[Y|S],Nc,Nf):- X\=Y, Nc1 is Nc + 1, distintas(R,S,Nc1,Nf).%%

distancia_h22(Ec,Ef,Nf):-transf((1,1),Ec,Ect),transf((1,1),Ef,Eft),
                            sort(Ect,Ect1),sort(Eft,Eft1),
                            disth22(Ect1,Eft1,0,Nf).


disth22([],[],Dc,Dc).
disth22([b-(X,Y)|R],[b-(W,Z)|S],Dc,Df):- disth22(R,S,Dc,Df). 
disth22([A-(X,Y)|R],[A-(W,Z)|S],Dc,Df):- A\=b, dist(X,W,D1), dist(Y,Z,D2), 
                                         Dc1 is Dc+ D1+D2, disth22(R,S,Dc1,Df).

transf(_,[],[]).
transf((X,Y),[A|R],S1):- transfl((X,Y),A,B), Y1 is Y+1, transf((X,Y1),R,S),append(B,S,S1).

transfl(_,[],[]).
transfl((X,Y),[A|R],[A-(X,Y)|S]):- X1 is X+1, transfl((X1,Y),R,S). 

testa(Op,F):- estado_inicial(E0),ope(E0,Op,F,_).
testa2(E0,E1,D):-estado_inicial(E0),op(E0,Op,E1,C), h1(E0,D).
testa3(E0,E1,D):-estado_inicial(E0),op(E0,Op,E1,C), h2(E0,D).

dist(X,Y,K):- X>Y,!, K is X -Y.
dist(X,Y,K):-  K is Y - X.