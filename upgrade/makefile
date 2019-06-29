compile:
	gcc -Wall -g -lm *.c -o Result

clean:
	rm -f *.cache

testeA: compile clean
	./Result < teste-S-A-1.in
	./Result < teste-S-A-2.in > output.txt

testeB: compile clean
	./Result < teste-S-B.in > output.txt
