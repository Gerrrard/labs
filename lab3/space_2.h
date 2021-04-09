#ifndef SPACE2
#define SPACE2

typedef struct Info Info;

typedef struct Item2 {
    int busy;
	int release;
	char *key;
	Info *info;
} Item2;

typedef struct Space2 {
	int msize2;
	int m_keylen;
	Item2 *items;
} Space2;

Space2 * space2_new(int max_size, int m_keylen);

void space2_del(Space2 *space);

int space2_check_key(Space2 *space, char *key);
int space2_hash(Space2 *space, char *key);

int space2_insert(Space2 *space, char *key, Info * info);

Info * space2_find(Space2 *space, char *key, int release);
Space2 * space2_find_all(Space_2 *space, char *key);

int space2_remove_with_release(Space2 *space, char *key, int release);
int space2_remove(Space2 *space, char *key);

void space2_print(Space2 *space);

void collect_garbage(Space2 *space);

#endif
