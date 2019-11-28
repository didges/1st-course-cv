all: prog

prog: main.o stream.o funcs.o 
	gcc main.o stream.o funcs.o -o program

main.o: main.c
	gcc -c main.c

stream.o: stream.c
	gcc -c stream.c

funcs.o: funcs.c
	gcc -c funcs.c
	
clean:
	rm -rf *.o 