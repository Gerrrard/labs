#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "queue.h"

#ifdef USE_LIST

#include "list.h"

#else

#include "vector.h"

#endif

struct Container{
	#ifdef USE_LIST
	List *list;
	#else
	Vector *vector;
	#endif
};

Queue * queue_new(){
	Queue * q = (Queue *)malloc(sizeof(Queue));
	Container * cont = (Container *)malloc(sizeof(Container));

	#ifdef USE_LIST

	cont->list = list_new();
	printf("List\n");

	#else

	cont->vector = vector_new();
    printf("Vector\n");

	#endif

	q->cont = cont;
	return q;
}

int queue_delete(Queue * q){
	#ifdef USE_LIST

	list_delete(q->cont->list);

	#else

	vector_delete(q->cont->vector);

	#endif

	free(q->cont);
	free(q);

	return 0;
}

int queue_push(Queue * q, int id, int tc, int te){
	#ifdef USE_LIST

	int status = list_push(q->cont->list, id, tc, te);

	#else

	int status = vector_push(q->cont->vector, id, tc, te);

	#endif

	return status;
}

data queue_pop(Queue * q){

    data result;

	#ifdef USE_LIST

	Item item = list_pop(q->cont->list);
	result.id = item.id;
	result.tc = item.tc;
	result.te = item.te;

	#else

	Item item = vector_pop(q->cont->vector);
	result.id = item.id;
	result.tc = item.tc;
	result.te = item.te;

	#endif

	return result;
}

int queue_print(Queue * q){
	#ifdef USE_LIST

	list_print(q->cont->list);

	#else

	vector_print(q->cont->vector);

	#endif

	return 0;
}

int get_int(int * addr){
	int temp;
	do{
		temp = scanf("%d", addr);
		if(temp < 0){
                return 1;
		}
		if(temp == 0){
			printf("Invalid input. Try again.\n");
			scanf("%*[^\n]");
		}
		if(temp == 1 && *addr < 0){
            printf("Invalid input, number is lower than 0. Try again.\n");
		}
	}while(temp == 0 || (temp == 1 && *addr < 0));
	return 0;
}
