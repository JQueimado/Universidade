compile:
	gcc -Wall -g -lm *.c -o Result

clean:
	rm -f *.cache
	rm -f output1.txt output2.txt output3.txt

testeA: compile clean
	./Result < teste-S-A-1.in > output1.txt
	./Result < teste-S-A-2.in > output2.txt

testeB: compile clean
	./Result < teste-S-B.in > output1.txt

testeC: compile clean
	./Result < teste-S-C.in > output1.txt

testeD: compile clean
	./Result < teste-S-D-1.in > output1.txt
	./Result < teste-S-D-2.in > output2.txt

testeE: compile clean
	./Result < teste-S-E-1.in > output1.txt
	./Result < teste-S-E-2.in > output2.txt
	./Result < teste-S-E-3.in > output3.txt
