#ifndef LIST_H
#define LIST_H

typedef struct Node Node;

typedef struct Item{
   int id, tc, te;
   struct Item* next;
}Item;

typedef struct List{
   Node * head;
   Node * tail;
}List;

List * list_new();

int list_push(List * list, int id, int tc, int te);

Item list_pop(List * list);

void list_delete(List * list);

void list_print(const List * list);

#endif
