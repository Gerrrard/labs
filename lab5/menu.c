#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "menu.h"


int get_int(int * a) {
	int error;
	do {
		error = scanf("%d", a);
		if (error < 0) return 1;
		if (error == 0) {
			printf("Invalid input. Repeate.\n");
			scanf("%*[^\n]");
		}
	} while (error == 0);
	scanf("%*c");
	return 0;
}

int get_double(double * a) {
	int error;
	do {
		error = scanf("%lf", a);
		if (error < 0) return 1;
		if (error == 0) {
			printf("Invalid input. Repeate.\n");
			scanf("%*[^\n]");
		}
	} while (error == 0);
	scanf("%*c");
	return 0;
}

char * get_str() {
    char buf[81];
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
        	free(res);
        	return NULL;
        } else if (n > 0) {
            int new_len = len + strlen(buf);
            res = realloc(res, new_len + 1);
            memcpy(res + len, buf, strlen(buf));
            len = new_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
    	res[len] = '\0';
    } else {
    	res = (char*)calloc(1, sizeof(char));
    }

    return res;
}

int dial_add(Graph * graph){
    printf("---ADD---\n");

	printf("Enter a number:\n1) Add node\n2) Add edge\n");
	int option;
	if (get_int(&option)) return 1;

	if (option == 1) {
        printf("Enter vertex name:\n");
        char * vert;
        if (!(vert = get_str())) return 1;

        printf("Enter x:\n");
        double x;
        if(get_double(&x)) {
            free(vert);
            return 1;
        }

        printf("Enter y:\n");
        double y;
        if(get_double(&y)) {
            free(vert);
            return 1;
        }

        int err = graph_node_add(graph, vert, x, y);

        free(vert);

        return err;
	} else if (option == 2) {
        printf("Enter 1 vertex name:\n");
        char * vert1;
        if (!(vert1 = get_str())) return 1;

        printf("Enter 2 vertex name:\n");
        char * vert2;
        if (!(vert2 = get_str())) {
            free(vert1);
            return 1;
        }

        printf("Enter weight:\n");
        int w;
        if (get_int(&w)) {
            free(vert1);
            free(vert2);
            return 1;
        }

        int err = graph_edge_add(graph, vert1, vert2, w);

        free(vert1);
        free(vert2);
        return err;
	} else {
		printf("ERROR: No such option");
	}

	return 0;
}

int dial_delete(Graph * graph){
    printf("---DELETE---\n");

    printf("Enter a number:\n1) Delete node\n2) Delete edge\n");
	int option;
	if (get_int(&option)) return 1;

	if (option == 1) {
        printf("Enter vertex name:\n");
        char * vert;
        if (!(vert = get_str())) return 1;

        int err = graph_node_del(graph, vert);

        free(vert);

        return err;
	} else if (option == 2) {
        printf("Enter 1 vertex name:\n");
        char * vert1;
        if (!(vert1 = get_str())) return 1;

        printf("Enter 2 vertex name:\n");
        char * vert2;
        if (!(vert2 = get_str())) {
            free(vert2);
            return 1;
        }
        int err = graph_edge_del(graph, vert1, vert2);

        free(vert1);
        free(vert2);

        return err;
	} else {
		printf("ERROR: No such option");
	}

	return 0;
}

int dial_bf(Graph * graph) {
    printf("---BELLMAN-FORD---\n");

    printf("Enter 1 vertex name:\n");
    char * vert1;
    if (!(vert1 = get_str())) return 1;

    printf("Enter 2 vertex name:\n");
    char * vert2;
    if (!(vert2 = get_str())) {
        free(vert1);
        return 1;
    }

    //int err = graph_bf(graph, vert1, vert2);

    free(vert1);
    free(vert2);
    return /*err*/ 0;
}

int dial_fw(Graph * graph) {
    printf("---FLOYD-WARSHALL---\n");

    printf("Enter 1 vertex name:\n");
    char * vert1;
    if (!(vert1 = get_str())) return 1;

    printf("Enter 2 vertex name:\n");
    char * vert2;
    if (!(vert2 = get_str())) {
        free(vert1);
        return 1;
    }

    //int err = graph_fw(graph, vert1, vert2);

    free(vert1);
    free(vert2);
    return /*err*/ 0;
}

int dial_rnd(Graph * graph) {
    printf("---RANDOM---\n");
    printf("Enter size:\n");
    int s;
    if (get_int(&s)) return 1;

    //int err = graph_rnd(graph, s);

    return /*err*/ 0;
}

int dial_bfs(Graph * graph) {
    printf("---BFS---\n");

	printf("Enter 1 vertex name:\n");

	char * vert1;
	if (!(vert1 = get_str())) return 1;

	printf("Enter 2 vertex name:\n");

	char * vert2;
	if(!(vert2 = get_str())) {
		free(vert2);
		return 1;
	}

	//int err = graph_bfs(graph, vert1, vert2);

	free(vert1);
	free(vert2);
	return /*err*/ 0;
}

int dial_show(Graph * graph) {
	printf("---SHOW---\n");

	printf("Enter a number:\n1) Adj lists\n2) Graphviz (DOT)\n");
	int option;
	if (get_int(&option)) return 1;

	//if (option == 1) graph_adj(graph);
	if (option == 2) graph_graphviz(graph);
	else printf("ERROR: No such option");

	return 0;
}

int dialog(const char *menu[], const int menu_size) {
	char * error_msg = "";
	int opt;

	do {
		printf("%s\n", error_msg);
		error_msg = "Invalid input. Repeate.";

		for (int i = 0; i < menu_size; i++) {
			printf("%s\n", menu[i]);
		}
		printf("%s", "Make your choice: ");

		if (get_int(&opt)) {
			opt = 0;
		}
	} while (opt < 0 || opt >= menu_size);

	return opt;
}

void start(Graph * graph) {
	const char * menu[] = {"0) Quit", "1) Add", "2) Delete", "3) show (BFS)"/*, "4) Bellman-Ford", "5) Floyd-Warshall", "6)Random", "7) Show"*/};
	int menu_size = sizeof(menu)/sizeof(menu[0]);

	int (*dialog_functions[])(Graph*) = {NULL, dial_add, dial_delete/*, dial_bfs, dial_bf, dial_fw, dial_rnd*/, dial_show};

	int opt;
	while ((opt = dialog(menu, menu_size))) {
		if (opt == 0 || dialog_functions[opt](graph)) break;
	}

	printf("\nProgram finished.\n");
}
