#ifndef	MENU_H
#define MENU_H

int get_int(int * a);
char * get_str();

int dialog(const char *menu[], const int menu_size);

int dial_add(Tree *tree);
int dial_delete(Tree *tree);
int dial_find(Tree *tree);
int dial_find_max(Tree *tree);
int dial_show(Tree *tree);
void start(Tree *tree);

#endif
