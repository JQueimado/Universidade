
estado_inicial([
	c(1,1,v), c(2,1,v), c(3,1,v), c(4,1,v), c(5,1,v), c(6,1,v), c(7,1,v),
	c(1,2,v), c(2,2,v), c(3,2,v), c(4,2,v), c(5,2,v), c(6,2,v), c(7,2,v),
	c(1,3,v), c(2,3,v), c(3,3,v), c(4,3,v), c(5,3,v), c(6,3,v), c(7,3,v),
	c(1,4,v), c(2,4,v), c(3,4,v), c(4,4,v), c(5,4,v), c(6,4,v), c(7,4,v),
	c(1,5,v), c(2,5,v), c(3,5,v), c(4,5,v), c(5,5,v), c(6,5,v), c(7,5,v),
	c(1,6,v), c(2,6,v), c(3,6,v), c(4,6,v), c(5,6,v), c(6,6,v), c(7,6,v)
	]).

 % [c(1,1,v), c(2,1,v), c(3,1,v), c(4,1,v), c(5,1,v), c(6,1,v), c(7,1,v), c(1,2,v), c(2,2,v), c(3,2,v), c(4,2,v), c(5,2,v), c(6,2,v), c(7,2,v), c(1,3,v), c(2,3,v), c(3,3,v), c(4,3,v), c(5,3,v), c(6,3,v), c(7,3,v), c(1,4,v), c(2,4,v), c(3,4,v), c(4,4,v), c(5,4,v), c(6,4,v), c(7,4,v), c(1,5,v), c(2,5,v), c(3,5,v), c(4,5,v), c(5,5,v), c(6,5,v), c(7,5,v), c(1,6,v), c(2,6,v), c(3,6,v), c(4,6,v), c(5,6,v), c(6,6,v), c(7,6,v)]

random([
	c(1,1,v), c(2,1,p1), c(3,1,v), c(4,1,p1), c(5,1,v), c(6,1,v), c(7,1,v),
	c(1,2,v), c(2,2,v), c(3,2,v), c(4,2,v), c(5,2,v), c(6,2,v), c(7,2,v),
	c(1,3,v), c(2,3,v), c(3,3,v), c(4,3,v), c(5,3,v), c(6,3,v), c(7,3,v),
	c(1,4,v), c(2,4,v), c(3,4,v), c(4,4,v), c(5,4,v), c(6,4,v), c(7,4,v),
	c(1,5,v), c(2,5,v), c(3,5,v), c(4,5,v), c(5,5,v), c(6,5,v), c(7,5,v),
	c(1,6,v), c(2,6,v), c(3,6,v), c(4,6,v), c(5,6,v), c(6,6,v), c(7,6,v)
	]).

mapa(7,6).

terminal(E):-
	check_linhas(E,1),
	check_colunas(E,1).

/* checks */

/* colunas */
check_colunas(E, C):-
	check_colunas(E, C, 0),
	C1 is C+1,
	mapa(_,L),
	C1 < L+1,
	check_colunas(E,C1).

check_colunas([ c(X,Y,p1) |Es], L, C):-
	X = L,
	C1 is C+1,
	check_colunas(Es, L, C1).

check_colunas([ c(X,Y,_) |Es], L, _):-
	Y = L,
	check_colunas(Es, L, 0).

check_colunas(Lis, L, 4):-!.

/* linhas */
check_linhas(E, C):-
	check_linhas(E, C, 0) |
	(C1 is C+1,
	mapa(L,_),
	C1 < L+1,
	check_linhas(E,C1)).

check_linhas(Lis, L, 4):-!.

check_linhas([ c(X,L,p1) |Es], L, C):-
	C1 is C+1,
	check_linhas(Es, L, C1).

check_linhas([ c(X,Y,_) |Es], L, C):-
	check_linhas(Es, L, C).

check_linhas([ c(X,Y,v) |Es], L, _):-
	Y = L,
	check_linhas(Es, L, 0).

check_linhas([], _, _):- false.

test:-
	random(A),
	terminal(E).