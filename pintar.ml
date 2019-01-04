
(*funcao que verifica se um elemento l já existe numa lista*)
let rec find_equal = function l -> function [] -> false | s::sl -> if s=l then true else find_equal l sl;;

(*função que procura uma cor aleatoria que não seja a c em uma palete l*)
let rec find_different_colour c l = let cc = l.( Random.int ((Array.length l)) ) in if cc=c then find_different_colour c l else cc;;

(*funcao que cria um sector baseado em s com alteracao na posicao i com a palete l*)
let rec sector l s i = match s with [] -> [] | x::ss -> if i=0 then ( ( find_different_colour x l )::( sector l ss (i-1) ) ) else ( x::( sector l ss (i-1) ) );;

(*função que gera um sector aleatorio de tamanho n e com a palete l*)
let rec rand_sec n l = if n=0 then [] else (l.(Random.int (Array.length l)))::(rand_sec (n-1) l ) ;;

(*funcao recurciva que pinta n discos com m sectores com a palete k (l representa os sectores ja pintados)*)
let rec pintar_rec n m k l = if m=0 then [] else match l with [] -> let x = rand_sec n k in x::(pintar_rec n (m-1) k [x]) | s::sl -> let x = sector k s (Random.int n) in if find_equal x l then (pintar_rec n m k l) else x::(pintar_rec n (m-1) k (x::l)) ;;

(*
let rec factorial n = match n with 0 -> 1 | 1->1 | x -> x*(factorial (n-1)) ;;

let combinacao n k = (factorial n)/( (factorial k)*(factorial ( n-k )));;
*)

(*função que pinta n discos com m sectores com a palete k*)
let pintar n m k = if (* (combinacao (lenght k) n ) > m *) false then [] else pintar_rec n m k [];;
