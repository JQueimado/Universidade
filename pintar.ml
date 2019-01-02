(*funcao que compara dois sectores do mesmo tamanho*)
let rec match_sector s1 s2 = match s1 with []->true | x::s -> (match s2 with [] -> true | y::ss -> (if x=y then (match_sector s ss) else (false) ));;

let rec lenght = function [] -> 0 | _::x -> 1+(lenght x);; 

let rec get_colour_at i l = match l with c::cl -> if i=0 then c else get_colour_at (i-1) cl ;;

let rec find_different_colour c l = let cc = get_colour_at (Random.int ( lenght l ) ) in (if cc = c then find_different_colour c l else cc );;

(*funcao que cria um sector baseado em s com alteracao na posicao i*)
let rec sector l s i = match s with [] -> [] | x::ss -> if i=1 then ( ( find_different_colour l x )::( sector l ss (i-1) ) ) else ( x::( sector l ss (i-1) ) );;

(*funcao que pinta um circulo de varios sectores*)
let rec pintar n m k s = if m=0 then [] else let x = ( sector k s (Random.int n ) ) in x::( pintar n (m-1) k x );;
