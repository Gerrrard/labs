#ifndef __VECTOR_H
#define __VECTOR_H

#define VECTOR_CAPACITY 10

typedef struct Item{
    int id, tc, te;
}Item;

typedef struct Vector{
    Item *items;
    int size, front, end;
}Vector;

Vector * vector_new();

void vector_delete(Vector * vector);

int vector_push(Vector * vector, int id, int tc, int te);

Item vector_pop(Vector * vector);

void vector_print(Vector * vector);

#endif
