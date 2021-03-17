#ifndef STACK_H
#define STACK_H

typedef struct Container Container;

typedef struct data{
    int id, tc, te;
}data;

typedef struct Queue{
	Container *cont;
}Queue;

Queue * queue_new();

int queue_delete(Queue * q);

int queue_push(Queue * q, int id, int tc, int te);

data queue_pop(Queue * q);

int queue_print(Queue * q);

int get_int(int * addr);

#endif
