
compile: main.c
	gcc -std=gnu99 -g -Wall -lm *.c -o Result

test1: clean compile testes/test1.txt
	time ./Result < testes/test1.txt

testgrafo: Grafo.o hashtable_aeroporto.o
	gcc -g -Wall -std=c99 testgrafo.c -o testgarfo Grafo.o hashtable_aeroporto.o

Grafo.o: Grafo.c Grafo.c
	gcc -c Grafo.c

hashtable_aeroporto.o: hashtable_aeroporto.c hashtable_aeroporto.h
	gcc -c hashtable_aeroporto.c

clean:
	rm -f ficheiro
	rm -f Result
	rm -f Grafo.o hashtable_aeroporto.o testgarfo
