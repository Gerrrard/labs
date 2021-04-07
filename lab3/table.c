#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "table.h"
#include "space_1.h"
#include "space_2.h"
#include "info.h"


Table * table_new(int sp1msize, int sp2msize, int sp2m_keylen) {
	Table *table = (Table *)calloc(1, sizeof(Table));
	Space1 *space1 = space1_new(sp1msize);
	Space2 *space2 = space2_new(sp2msize, sp2m_keylen);

	table->space1 = space1;
	table->space2 = space2;

	return table;
}

void table_del(Table *table) {
	table_remove_all(table);

	space1_del(table->space1);
	space2_del(table->space2);
	free(table);
}

Info * table_find(Table *table, int key1, char *key2) {
    int ind = space1_find(table->space1, key1, key2);

    if(ind == -1) return NULL;

	Info *info = space->items[i].info;

	if (!info || strcmp(Item1->key2, key2) != 0) return NULL;
	else return info;
}

int table_insert(Table *table, int key1, int par1, char *key2, Info info) {

}

int table_remove(Table *table, int key1, char *key2) {

}

int table_remove_all(Table *table) {

}
