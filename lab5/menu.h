#ifndef	MENU_H
#define MENU_H

int get_int(int * a);
int get_double(double * a);
char * get_str();

int dialog(const char * menu[], const int menu_size);

int dial_add(Graph * graph);
int dial_delete(Graph * graph);

int dial_bfs(Graph * graph);
int dial_bf(Graph * graph);
int dial_fw(Graph * graph);

int dial_rnd(Graph * graph);
int dial_show(Graph * graph);

void start(Graph * graph);

#endif
