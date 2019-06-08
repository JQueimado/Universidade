
compile: main.c
	gcc -std=gnu99 -g -Wall -lm *.c -o Result

clean:
	rm -f ficheiro
	rm -f Result
