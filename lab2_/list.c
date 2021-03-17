#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List * list_new(){
    List* list = (List *)calloc(1, sizeof(List));

    list->head = NULL;
    list->tail = NULL;

    return list;
}

int list_push(List * list, int id, int tc, int te){
    Item* item = (Item *)malloc(sizeof(Item));

    item->id = id;
    item->tc = tc;
    item->te = te;
    item->next = NULL;

    if(list->head && list->tail){
        list->tail->next = item;
        list->tail = item;
    }else{
        list->head = list->tail = item;
    }

    return 0;
}

Item list_pop(List * list){
    Item item;
    item.id = -1;
    item.tc = -1;
    item.te = -1;

    Item *old_head = list->head;

    if(list->head){
        item.id = list->head->id;
        item.tc = list->head->tc;
        item.te = list->head->te;
        list->head = list->head->next;
    }

    free(old_head);

    return item;
}

void list_delete(List * list){
    while(list->head){
        list_pop(list);
    }
    list->head = list->tail = NULL;
}

void list_print(const List * list){
    const Item* item = list->head;

    for(; item; item = item->next){
        printf("%d %d %d", item->id, item->tc, item->te);
    }
    printf("\n");
}
