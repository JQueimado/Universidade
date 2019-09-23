
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
	c(1,1,v), c(2,1,v), c(3,1,v), c(4,1,v), c(5,1,v), c(6,1,v), c(7,1,v),
	c(1,2,v), c(2,2,v), c(3,2,v), c(4,2,v), c(5,2,v), c(6,2,v), c(7,2,v),
	c(1,3,v), c(2,3,v), c(3,3,v), c(4,3,v), c(5,3,v), c(6,3,v), c(7,3,v),
	c(1,4,v), c(2,4,v), c(3,4,v), c(4,4,v), c(5,4,v), c(6,4,v), c(7,4,v),
	c(1,5,v), c(2,5,v), c(3,5,v), c(4,5,p1), c(5,5,p1), c(6,5,p1), c(7,5,p1),
	c(1,6,v), c(2,6,v), c(3,6,v), c(4,6,v), c(5,6,v), c(6,6,v), c(7,6,v)
	]).

mapa(7,6).

terminal(E):-
	check_colunas(E);
	check_linhas(E).
	

/* checks */

/* colunas */
check_colunas(E):-
	( findall( V , member( c(1,_,V) , E), L), check(L, 0) );
	( findall( V , member( c(2,_,V) , E), L), check(L, 0) );
	( findall( V , member( c(3,_,V) , E), L), check(L, 0) );
	( findall( V , member( c(4,_,V) , E), L), check(L, 0) );
	( findall( V , member( c(5,_,V) , E), L), check(L, 0) );
	( findall( V , member( c(6,_,V) , E), L), check(L, 0) );
	( findall( V , member( c(7,_,V) , E), L), check(L, 0) ).

check_linhas(E):-
	( findall( V , member( c(_,1,V) , E), L), check(L, 0) );
	( findall( V , member( c(_,2,V) , E), L), check(L, 0) );
	( findall( V , member( c(_,3,V) , E), L), check(L, 0) );
	( findall( V , member( c(_,4,V) , E), L), check(L, 0) );
	( findall( V , member( c(_,5,V) , E), L), check(L, 0) );
	( findall( V , member( c(_,6,V) , E), L), check(L, 0) ).

diagonal(E):-
	( findall( V , ( member(c(X,Y,V), E) ), L ), check(L, 0) ).

diagonal_direita_1(X,Y, L):-
	diagonal_direita_1(X, Y, 1, 1, [(X,Y)|L]).

diagonal_direita_1(XLim, YLim, X, Y, [(X,Y)|L]):-

/* check lists */
check(_,4):-!.

check([p1|Es], C):-
	C1 is C+1,
	check(Es, C1).

check([_|Es], _):-
	check(Es, 0).

test:-
	random(A),
	terminal(A).