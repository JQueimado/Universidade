(*funcao que compara dois sectores do mesmo tamanho*)
let rec find_equal = function l -> function [] -> false | s::sl -> if s=l then true else find_equal l sl;;

let rec lenght = function [] -> 0 | _::x -> 1+(lenght x);; 

let rec get_colour_at = function i -> function c::[] -> c | c::cl -> if i=0 then c else get_colour_at (i-1) cl ;;

let pick_colour l = get_colour_at (Random.int ( lenght l ) );;

let rec pop_element = function c -> function [] -> [] | cc::cl -> if c = cc then cl else cc::(pop_element c cl) ;;

let find_different_colour c l = get_colour_at ( Random.int (lenght l)-1 ) ( pop_element c l );;

(*funcao que cria um sector baseado em s com alteracao na posicao i*)
let rec sector l s i = match s with [] -> [] | x::ss -> if i=0 then ( ( find_different_colour x l )::( sector l ss (i-1) ) ) else ( x::( sector l ss (i-1) ) );;

let rec rand_sec n l = if n=0 then [] else (get_colour_at (Random.int (lenght l)) l )::(rand_sec (n-1) l ) ;;

(*funcao que pinta um circulo de varios sectores*)
let rec pintar_rec n m k l = if m=0 then [] else match l with [] -> let x = rand_sec n k in x::(pintar_rec n (m-1) k [x]) | s::sl -> let x = sector k s (Random.int n) in if find_equal x l then x::(pintar_rec n m k l) else x::(pintar_rec n (m-1) k (x::l)) ;;

let pintar n m k = pintar_rec n m k [];;
