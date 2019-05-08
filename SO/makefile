.PHONY: OSmake clean

OSmake: main.c Pre_Process.o Process.o Queue.o input1.txt
	gcc -g main.c -o main Pre_Process.o Process.o Queue.o
	./main input1.txt > output.txt
	make clean

Pre_Process.o: Structs/Pre_Process.c Structs/Pre_Process.h
	gcc -c Structs/Pre_Process.c

Process.o: Structs/Process.c Structs/Process.h
	gcc -c Structs/Process.c

Queue.o: Structs/Queue.c Structs/Queue.h
	gcc -c Structs/Queue.c

clean:
	rm -f Pre_Process.o Process.o Queue.o