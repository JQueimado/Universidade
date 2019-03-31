(*Pintar*)

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


(*verificação*)

(*calcula a potencia de n por k (causa overflow se o valor calculado passar dos 31bits)*)
let rec pot n k = if k=0 then 1 else (n)*(pot n (k-1));;

(*verifica se é possivel pintar o disco*)
let check n m k = let x = Array.length k in (pot x n) >= m ;; 

(*main*)

(*função que pinta n discos com m sectores com a palete k*)
let pintar n m k = if check n m k then pintar_rec n m k [] else [];;
