#ifndef SPACE1
#define SPACE1

typedef struct Info Info;

typedef struct Item1 {
	int key;
	int par;
	Info *info;
} Item1;

typedef struct Space1 {
    int size;
	int msize1;
	Item1 *items;
} Space1;

Space1 * space1_new(int max_size);

void space1_del(Space1 *space);

int space1_find(Space1 *space, int key);
//Space1 * space1_find_par(Space1 *space, int par);

//int space1_insert(Space1 *space, int key, int par, Info *info);

//int space1_remove(Space1 *space, int key);
int space1_remove_all(Space1 *space);

void space1_print(Space1 *space);

#endif
