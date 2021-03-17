all: main.c libqueue.a
	gcc -Wextra -c main.c
	gcc main.o -L. -lqueue -o main

list: queue.c list.c
	gcc -Wextra -D USE_LIST -c queue.c list.c
	ar -rcs libqueue.a queue.o list.o

vector: queue.c vector.c
	gcc -Wextra -c queue.c vector.c
	ar -rcs libqueue.a queue.o vector.o
