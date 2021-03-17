#ifndef __LIST_H
#define __LIST_H


typedef struct Item{
   int id, tc, te;
   struct Item* next;
}Item;

typedef struct List{
   Item* head;
   Item* tail;
}List;

List * list_new();

int list_push(List * list, int id, int tc, int te);

Item list_pop(List * list);

void list_delete(List * list);

void list_print(const List * list);

#endif
