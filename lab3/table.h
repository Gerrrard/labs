#ifndef TABLE
#define TABLE

typedef struct Space1 Space1;
typedef struct Space2 Space2;

typedef struct Info Info;

typedef struct Table{
	Space1 *space1;
	Space2 *space2;
} Table;

Table * table_new(int sp1msize, int sp2msize, int sp2m_keylen);

void table_del(Table *table);

int table_insert(Table *table, int key1, int par1, char *key2, Info info);

Info * table_find(Table *table, int key1, char *key2);

int table_remove(Table *table, int key1, char *key2);

int table_remove_sp1(Table *table, int inp, int opt);     //if opt == 1 - inp is key, other - inp - parent

int table_remove_sp2(Table *table, char *key2, int release);

int table_remove_all(Table *table);

#endif
