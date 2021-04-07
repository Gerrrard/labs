#include <stdlib.h>
#include <stdio.h>

#include "space_1.h"
#include "info.h"


Space1* space1_new(int max_size) {
	Space1 *space = (Space1 *)calloc(1, sizeof(Space1));
	Item1 *items = (Item_1 *)calloc(max_size, sizeof(Item1));

	space->msize1 = max_size;
	space->size = 0;
	space->items = items;

	return space;
}


void space1_del(Space1 *space) {
	if (!space) return;

	free(space->items);
	free(space);
}


int space1_insert(Space1 *space, int key, int par, Info * info) {
	if (space1_find(space, key)) return 1;     //1 if found
	if ((par != 0) && !space1_find(space, par)) return 2;     //2 if no such parent
	if (space->size >= space->msize1) return 3;     //3 if full

	//insertion is sorted by parent

	space->items[space->size].key = key;
	space->items[space->size].par= par;
	space->items[space->size].info = info;

	space->size++;

	return 0;
}


int space1_remove(Space1 *space, int key) {
	int index = space1_find_index(space, key);
	if (index < 0) return 1;     //1 if no such element

	//deletion with moving because of parent

	space->items[i].info = NULL;

	for(int i = 0; i < space->size; i++) {
		if (space->items[i].par == key) space->items[i].par = 0;
	}

	return 0;
}

int space1_remove_all(Space1 *space) {
	for(int i = 0; i < space->size; i++) space->items[i].info = NULL;
	return 0;
}

int space1_find(Space1 *space, int key) {
    Item1 item;
	for(int i = 0; i < space->size; i++) {
		item = space->items[i];
		if (item.key == key) return i;
	}
	return -1;     //-1 if not found
}

Space1 * space1_find_par(Space1 *space, int par){
    //finding all by parent
}

void space1_print(Space1 *space) {
    printf("\n- SPACE1 -\n");
    printf("Key/tParent key\nInfo\n");
	for (int i = 0; i < space->size; i++) {
		printf("%d\t%d\t\n", space->items[i].key, space->items[i].par);
		info_print(space->items[i].info);
		printf("\n");
	}
	printf("---------\n\n");
}
