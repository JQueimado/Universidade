
compile: main.c Grafo.o hashtable_aeroporto.o
	gcc -std=c99 -Wall -g main.c -o Result Grafo.o hashtable_aeroporto.o

test1: clean compile testes/test1.txt
	time ./Result < testes/test1.txt

testgrafo: Grafo.o hashtable_aeroporto.o
	gcc -g -Wall -std=c99 testgrafo.c -o testgarfo Grafo.o hashtable_aeroporto.o

Grafo.o: Grafo.c Grafo.c
	gcc -c Grafo.c

hashtable_aeroporto.o: hashtable_aeroporto.c hashtable_aeroporto.h
	gcc -c hashtable_aeroporto.c

clean:
	rm -f *.cache
	rm -f Result
	rm -f *.o testgarfo
