all: main.c libqueue.a
	gcc -Wextra -c -std=c11 main.c
	gcc main.o -L. -lqueue -o main

list: queue.c list.c
	gcc -Wextra -D USE_LIST -c -std=c11 queue.c list.c
	ar -rcs libqueue.a queue.o list.o

vector: queue.c vector.c
	gcc -Wextra -c -std=c11 queue.c vector.c
	ar -rcs libqueue.a queue.o vector.o
