% limite do mapa %
mapa( 3 ).

% estado inicial e final %
estado_inicial( (1,1) ).

estado_final( (3,3) ).

% avaliadores %
max(A):-
    mapa(C),
    A =< C.

min(A):-
    A > 0.

% portas %
porta( (0,0), (0,0) ).
porta( (1,1), (1,2) ).

% movimentos %
% baixo %
op( (A,B), b, (A,D), 1 ):-
    D is B - 1,
    min(D),
    \+ porta( (A,B), (A,D) ).

% cima %
op( (A,B), c, (A,D), 1 ):-
    D is B + 1,
    max(D),
    \+ porta( (A,B), (A,D) ).

% esquerda %
op( (A,B), e, (D,B), 1 ):-
    D is A - 1,
    min(D),
    \+ porta( (A,B), (D,B) ).

% direita %
op( (A,B), d, (D,B), 1 ):-
    D is A + 1,
    max(D),
    \+ porta( (A,B), (D,B) ).