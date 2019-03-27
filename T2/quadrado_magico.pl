:-dynamic(diag/1, diag2/1, conta/1).

matriz(3). %(3x3)

estado_inicial(E):-
  matriz(S),
  AA is S * S,
  BB is S * (AA + 1),
  B is BB // 2,
  assertz(conta(B)),

functor(E, e, 2), arg(1, E, T), arg(2, E, []),
  nova_tabela(T2, S),
  flatten(T2, T).

nova_tabela(L, Size):- 
  nova_tabela(L, 1, Size).

nova_tabela([H], N, N):-
  nova_coluna(H, N, N).

nova_tabela([H|T], J, N):-
  J < N, J2 is J+1,
  nova_coluna(H, J, N),
  nova_tabela(T, J2, N).
  
nova_coluna(L, J, NColunas):- 
  nova_coluna(L, 1, J, NColunas).

nova_coluna([H], N, J, N):-
  matriz(S),
  S1 is S * S,
  range(1, S1, D), %cria o dominio da variavel dado um maximo como arg
  H = v(p(N, J), D, _).


nova_coluna([H|T], I, J, N):-
  matriz(S),
  S1 is S * S,
  range(1, S1, D), %cria o dominio da variavel dado um maximo como arg
  I < N, I2 is I+1,
  H = v(p(I, J), D, _),
  nova_coluna(T, I2, J, N).



%devolve uma lista com numeros de I a J
range(I,I,[I]).
range(I,J,[I|L]) :- I < J, I1 is I + 1, range(I1,J,L).    

%Restrições 
ve_restricoes(E):- 
  matriz(T),
  total(E),
  percorrer_linhas(E,L1,T1),
  percorrer_colunas(E,L2,T2),
  percorrer_diagonal_dir(E,L3,T3),
  percorrer_diagonal_esq(E, L4, T4),

  conta(B),
  (=(T, T1)
    -> (=(B, L1)
        -> true; fail); true),

  (=(T, T2)
    -> (=(B, L2)
        -> true; fail); true),

  (=(T, T3)
    -> (=(B, L3)
        -> true; fail); true),

  (=(T, T4)
    -> (=(K, L4)
        -> true; fail); true).



total(e(Nafect,[v(p(_,_), D, V)|R])):-
  findall(V1,member(v(p(_,_),_,V1),R),L),
  todos_diff([V|L]).

percorrer_linhas(e(Nafect,[v(p(X,Y), D, V)|R]),S, T):-
  findall(V1,member(v(p(X,_),_,V1),R),L),
  todos_diff([V|L]), length([V|L],T),
  sum_list([V|L],S).
  
percorrer_colunas(e(Nafect,[v(p(X,Y), D, V)|R]),S, T):-
  findall(V1,member(v(p(_,Y),_,V1),R),L),
  todos_diff([V|L]), length([V|L],T),
  sum_list([V|L],S).

percorrer_diagonal_dir(e(Nafect,[v(p(X,Y), D, V)|R]),S, T):-
  matriz(Tb),
  Ta is Tb * Tb,
  findall((K1,K2,V1),member(v(p(K1,K2),_,V1),R),L),
  length([(X,Y,V)|L],Tc),

  (=(Tc,Ta)
    ->
    (verify_dir([(X,Y,V)|L], Result), diag(Diag), 
      sum_list(Diag,S), length(Diag,T))
  ;
  true).


  percorrer_diagonal_esq(e(Nafect,[v(p(X,Y), D, V)|R]),S, T):-
  matriz(Tb),
  Ta is Tb * Tb,
  findall((K1,K2,V1),member(v(p(K1,K2),_,V1),R),L),
  length([(X,Y,V)|L],Tc),
  (=(Tc,Ta)
    ->
    (verify_esq([(X,Y,V)|L], Result), diag2(Diag),
      sum_list(Diag,S), length(Diag,T))
  ;
  true).

verify_dir([],[X, Y, Z|H]):- retractall(diag(_)), assertz(diag([X, Y, Z])).

verify_dir([(X,Y,V)|Antiga2], []):-
    (=(X,Y)
      ->
      verify_dir(Antiga2,[V])

      ; verify_dir(Antiga2,[])

    ).

verify_dir([(X,Y,V)|Antiga2], Nova):-
    (=(X,Y)
      ->  (merge_list([V], Nova, N),
          verify_dir(Antiga2,N))

      ; verify_dir(Antiga2,Nova)).


verify_esq([],[X, Y, Z|H]):- retractall(diag2(_)), assertz(diag2([X, Y, Z])).

verify_esq([(X,Y,V)|Antiga2], []):-
    matriz(S),
    S1 is S + 1,
    B is X + Y,
    (=(S1, B)
      ->
      verify_esq(Antiga2,[V])

      ; verify_esq(Antiga2,[])).

verify_esq([(X,Y,V)|Antiga2], Nova):-
    matriz(S),
    S1 is S + 1,
    B is X + Y,
    (=(S1, B)
      ->  (merge_list([V], Nova, N), verify_esq(Antiga2,N)); verify_esq(Antiga2,Nova)).

merge_list([],L,L ).
merge_list([H|T],L,[H|M]):-
    merge_list(T,L,M).

todos_diff([]).
todos_diff([X|R]):-
  \+ member(X,R), todos_diff(R).

esc(L):-sort(L, L1), esc_a(L1),nl.
esc_a(L):- matriz(S), esc_l(L, 1, S).

esc_l([H], S, S):-
  H = v(_,_,X), write(X),nl.

esc_l([H|T], S, S):-
  H = v(_,_,X), write(X), nl,
  esc_l(T, 1, S).

esc_l([H|T], I, S):- 
  I<S, I2 is I+1,
  H = v(_,_,X), write(X),write(' . '),
esc_l(T, I2, S).