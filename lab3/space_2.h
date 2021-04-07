#ifndef SPACE2
#define SPACE2

typedef struct Info Info;

typedef struct Node2 {
	char *key;
	int release;
	struct Node2 *next;

	Info *info;
} Node2;

typedef struct Item2 {
    int busy;
	int release;
	Node2 *head;
} Item2;

typedef struct Space2 {
	int msize2;
	int m_keylen;
	Item2 *items;
} Space2;

Space2 * space2_new(int max_size, int m_keylen);

void node2_del(Node2 *node);

void space2_rem_list(Node2 *head);
void space2_del(Space2 *space);

int space2_check_key(Space2 *space, char *key);
int space2_hash(Space2 *space, char *key);

int space2_insert(Space2 *space, char *key, Info * info);

Info * space2_find(Space2 *space, char *key, int release);
Space2 * space2_find_all(Space_2 *space, char *key);

int space2_remove(Space2 *space, char *key, int release);
//change it: if release = 0 remove all and find first;

void space2_print(Space2 *space);

void collect_garbage(Space2 *space);

#endif
