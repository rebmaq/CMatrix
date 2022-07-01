all: main matrix link

FLAGS=

main: main.c
	gcc $(FLAGS)main.c -o main.o -c

matrix: matrix.c
	gcc $(FLAGS)matrix.c -o matrix.o -c

link:
	gcc $(FLAGS)-o mat main.o matrix.o

clean:
	rm *.o