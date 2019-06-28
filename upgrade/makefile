compile:
	gcc -Wall -g -lm *.c -o Result

testeA: compile
	rm *.cache
	./Result < teste-S-A-1.in
	./Result < teste-S-A-2.in > output.txt
