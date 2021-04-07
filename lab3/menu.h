#ifndef	MENU
#define MENU

int get_int(int inp);
char * get_str();

int dialog(const char *menu[], int menu_size);

int dial_add(Table* table);
int dial_find(Table* table);
int dial_delete(Table* table);
int dial_show(Table* table);

void start(Table *table);

#endif
