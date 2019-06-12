
compile: main.c
	gcc -std=gnu99 -g -Wall -lm *.c -o Result

test1: clean compile testes/test1.txt
	time ./Result < testes/test1.txt

clean:
	rm -f ficheiro
	rm -f Result
