.PHONY: all
all: OSmake

OSmake: main.c Pre_Process.o Process.o Queue.o input1.txt
	gcc -g main.c -o MAIN Pre_Process.o Process.o Queue.o
	./MAIN > output.txt
	make clean

Pre_Process.o: Structs/Pre_Process.c Structs/Pre_Process.h
	gcc -c Structs/Pre_Process.c

Process.o: Structs/Process.c Structs/Process.h
	gcc -c Structs/Process.c

Queue.o: Structs/Queue.c Structs/Queue.h
	gcc -c Structs/Queue.c

.PHONY: clean
clean:
	rm -f Pre_Process.o MAIN Process.o Queue.o