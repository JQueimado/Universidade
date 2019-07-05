soma(L,S) :-
    pot2(L,LP2),
    ordena(LP2,LO),
    tiraParesIguais(LO,LOS),
    calcula(LOS,S), !.

pot2([],[]).
pot2([0|R],RE) :-
    pot2(R,RE).
pot2([X|R],[X|RE]) :-
    potencia2(X),
    pot2(R,RE).
pot2([X|R],[N1|RE]) :-
    decompoe(X,N1,N2),
    pot2([N2|R],RE).

potencia2(1).
potencia2(N) :-
    0 is N mod 2,
    R is N // 2,
    potencia2(R).

decompoe(N1,N1,0) :-
    potencia2(N1).
decompoe(N1,P1,P2) :-
    N is N1 - 1,
    decompoe(N,P1,P),
    P2 is P + 1.

ordena(L,L) :-
    ordenada(L).
ordena(L,LO) :-
    bb(L,L1),
    ordena(L1,LO).

ordenada([]).
ordenada([_]).
ordenada([X,Y|R]) :-
    X =< Y, 
    ordenada([Y|R]).

bb([X],[X]).
bb([X,Y|R],[X|O]) :-
    X =< Y,bb([Y|R],O).
bb([X,Y|R],[Y|O]) :-
    bb([X|R],O).

tiraParesIguais(L,R) :-
    membro2(X,L),
    divideLista(L,L1,[X,X],L3),
    junta(L1,L3,J),
    tiraParesIguais(J,R).
tiraParesIguais(L,L).

membro2(X,[X,X|_]). membro2(X,[_,Y|R]) :- membro2(X,[Y|R]).

divideLista(L,L1,L2,L3) :-
    junta(L1,L2,J),
    junta(J,L3,L).

junta([],L,L). 
junta([X|R],L,[X|J]) :- 
    junta(R,L,J).

calcula([],0).
calcula([X],X).
calcula([X,Y|R],S) :-
    S1 is X + Y,calcula([S1|R],S).

%%%%%%%%%%%%%% EXEMPLO %%%%%%%%%%%%%%

proximaSituacao(S,PS) :-
    soma(S,N),
    proxS(N,S,PS).

proxS(N,[X|R],[V|R]) :-
    soma([N,X],V),
    V =< X.
proxS(N,[X|R1],[X|R2]) :-
    proxS(N,R1,R2).

%%%%%%%%%%%% PREDICADO PRINCIPAL %%%%%%%%%%%
nim(SI):-
    soma(SI,S),
    S =:= 0,
    joga(utilizador,SI),!.

nim(SI) :-
    joga(computador,SI),!.
% nao fazemos verificacoes de validade

joga(utilizador,_) :- 
    write('\nUtilizador joga para:\n'),
    read( NS),
    joga(computador,NS).

joga(computador,SA) :-
    proximaSituacao(SA,PS),
    write('\nComputador joga para: \n'),write(PS), nl,continua(PS).

continua(PS) :-
    nao_acabou(PS),
    joga(utilizador,PS).

continua(_) :-
    write('\nGanhei! \n'), nl.

nao_acabou(L) :-
    membro(X,L),X =\= 0.

membro(X,[X|_]).
membro(X,[_|R]) :- 
    membro(X,R).

