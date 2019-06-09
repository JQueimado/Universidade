
compile: main.c
	gcc -std=gnu99 -g -Wall -lm *.c -o Result

test1: compile testes/test1.txt
	./Result < testes/test1.txt

clean:
	rm -f ficheiro
	rm -f Result
