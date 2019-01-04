(*funcao que verifica se um elemento l já existe numa lista*)
let rec find_equal = function l -> function [] -> false | s::sl -> if s=l then true else find_equal l sl;;

(*função que calcula o tamanho de uma lista*)
let rec lenght = function [] -> 0 | _::x -> 1+(lenght x);; 

(*função que procura uma cor i numa palete*)
let rec get_colour_at = function i -> function c::[] -> c | c::cl -> if i=0 then c else get_colour_at (i-1) cl ;;

(*função que escolhe uma cor aleatoria de uma palete l*)
let pick_colour l = get_colour_at (Random.int ( lenght l ) );;

(*função que retira o elemento c de uma lista *)
let rec pop_element = function c -> function [] -> [] | cc::cl -> if c = cc then cl else cc::(pop_element c cl) ;;

(*função que procura uma cor aleatoria que não seja a c em uma palete l*)
let find_different_colour c l = get_colour_at ( Random.int (lenght l)-1 ) ( pop_element c l );;

(*funcao que cria um sector baseado em s com alteracao na posicao i com a palete l*)
let rec sector l s i = match s with [] -> [] | x::ss -> if i=0 then ( ( find_different_colour x l )::( sector l ss (i-1) ) ) else ( x::( sector l ss (i-1) ) );;

(*função que gera um sector aleatorio de tamanho n e com a palete l*)
let rec rand_sec n l = if n=0 then [] else (get_colour_at (Random.int (lenght l)) l )::(rand_sec (n-1) l ) ;;

(*funcao recurciva que pinta n discos com m sectores com a palete k (l representa os sectores ja pintados)*)
let rec pintar_rec n m k l = if m=0 then [] else match l with [] -> let x = rand_sec n k in x::(pintar_rec n (m-1) k [x]) | s::sl -> let x = sector k s (Random.int n) in if find_equal x l then (pintar_rec n m k l) else x::(pintar_rec n (m-1) k (x::l)) ;;

(*
let rec factorial n = match n with 0 -> 1 | 1->1 | x -> x*(factorial (n-1)) ;;

let combinacao n k = (factorial n)/( (factorial k)*(factorial ( n-k )));;
*)

(*função que pinta n discos com m sectores com a palete k*)
let pintar n m k = if (* (combinacao (lenght k) n ) > m *) false then [] else pintar_rec n m k [];;
