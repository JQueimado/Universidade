(*funcao que compara dois sectores do mesmo tamanho*)
let rec match_sector s1 s2 = match s1 with []->true | x::s -> (match s2 with [] -> true | y::ss -> (if x=y then (match_sector s ss) else (false) ));;

(*funcao que cria um sector atravez d uma lista*)
let rec sector n l = if n=0 then [] else ( match l with []->[] | x::c -> x::(sector (n-1) c) );;

(*funcao que pinta um circulo de varios sectores*)
let rec pintar n m k = if m=0 then [] else ( (sector n k)::(pintar n (m-1) k) );;
