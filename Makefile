all: main matrix link

main: main.c
	gcc main.c -o main.o -c

matrix: matrix.c
	gcc matrix.c -o matrix.o -c

link:
	gcc -o mat main.o matrix.o