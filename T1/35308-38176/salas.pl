% limite do mapa %
mapa( 30 ).

% estado inicial e final %
estado_inicial( (18,18) ).

estado_final( (26,26) ).

% avaliadores %
max(A):-
    mapa(C),
    A =< C.

min(A):-
    A > 0.

% movimentos %
% baixo %
op( (A,B), b, (A,D), 1 ):-
    D is B - 1,
    min(D).

% cima %
op( (A,B), c, (A,D), 1 ):-
    D is B + 1,
    max(D).

% esquerda %
op( (A,B), e, (D,B), 1 ):-
    D is A - 1,
    min(D).

% direita %
op( (A,B), d, (D,B), 1 ):-
    D is A + 1,
    max(D).