#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "vector.h"

Vector * vector_new(){
	Vector *vector = (Vector*)malloc(sizeof(Vector));
	vector->items = (Item*)calloc(VECTOR_CAPACITY, sizeof(Item));
	vector->size = 0;
	vector->front = 0;
	vector->end = 0;

	return vector;
}

void vector_delete(Vector * vector){
	free(vector->items);
	free(vector);
}

int vector_push(Vector * vector, int id, int tc, int te){
	if(vector->size == VECTOR_CAPACITY) return 1;

	Item *ptr = vector->items + vector->end;
	ptr->id = id;
	ptr->tc = tc;
	ptr->te = te;

	vector->size++;
    vector->end = (vector->end + 1) % VECTOR_CAPACITY;

	return 0;
}

Item vector_pop(Vector * vector){
	Item result;

	result.id = -1;
	result.tc = -1;
	result.te = -1;

	if(vector->size == 0){
        return result;
	}

	result.id = (vector->items + vector->front)->id;
	result.te = (vector->items + vector->front)->te;
	result.tc = (vector->items + vector->front)->tc;

	vector->size--;
    vector->front = (vector->front + 1) % VECTOR_CAPACITY;

	return result;
}

void vector_print(Vector * vector){
    int index;
	printf("\"");
	for (int i = 0; i < vector->size; i++) {
        index = (vector->front + i) % VECTOR_CAPACITY;
		printf("%d %d %d\n", vector->items[index].id, vector->items[index].tc, vector->items[index].te);
	}
	printf("\"");
	printf("\n");
}
