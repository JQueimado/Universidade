
compile: main.c Dijkstra.o hashtable_aeroporto.o
	gcc -std=c99 -Wall -g main.c -o Result hashtable_aeroporto.o

test1: clean compile testes/test1.txt
	time ./Result < testes/test1.txt

testdisconas: Dijkstra.o hashtable_aeroporto.o
	gcc -g -Wall discona.c -o Result Dijkstra.o hashtable_aeroporto.o

Dijkstra.o: Dijkstra.c Dijkstra.c
	gcc -c Dijkstra.c

hashtable_aeroporto.o: hashtable_aeroporto.c hashtable_aeroporto.h
	gcc -c hashtable_aeroporto.c

clean:
	rm -f *.cache
	rm -f Result
	rm -f *.o testgarfo
