#ifndef	MENU
#define MENU

int get_int(int *num);
char * get_str();

int dialog(const char *menu[], int menu_size);

int dial_add(Table* table);
int dial_find(Table* table);
int dial_delete(Table* table);
int dial_show(Table* table);

int dial_del_par_sp1(Table* table);
int dial_find_par_sp1(Table* table);

int dial_find_sp2(Table* table);
int dial_delete_sp2(Table* table);

void start(Table *table);

#endif
