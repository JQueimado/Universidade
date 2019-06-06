
compile: main.c
	gcc -std=gnu99 -Wall -lm *.c -o Result

clean:
	rm -f ficheiro