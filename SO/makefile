.PHONY: compile run clean

all: main run clean

compile: main

testBestfit: clean Structs/BestFit.c Process.o
	gcc -Wall Structs/BestFit.c Process.o -o main -g

run: main input1.txt
	./main input1.txt > output.txt

clean:
	rm -f Pre_Process.o Process.o Queue.o Disk.o process.cache BestFit.o

main: main.c Pre_Process.o Process.o Queue.o Disk.o BestFit.o
	gcc -g main.c -o main Pre_Process.o Process.o Queue.o Disk.o BestFit.o

Pre_Process.o: Structs/Pre_Process.c Structs/Pre_Process.h
	gcc -c Structs/Pre_Process.c

Process.o: Structs/Process.c Structs/Process.h
	gcc -c Structs/Process.c

Queue.o: Structs/Queue.c Structs/Queue.h
	gcc -c Structs/Queue.c

Disk.o: Structs/Disk.c Structs/Disk.h
	gcc -c Structs/Disk.c

BestFit.o: Structs/BestFit.c Structs/MemoryManager.h
	gcc -c Structs/BestFit.c