#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
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

int dial_add(Tree *tree) {
	printf("---ADD---\n");

	printf("Enter key (string):\n");
	char * key;
	if (!(key = get_str())) return 1;

	printf("Enter info1 (int):\n");
	int int1;
	if (get_int(&int1)) return 1;

    printf("Enter info2 (int):\n");
	int int2;
	if (get_int(&int2)) return 1;

	printf("Enter str (string):\n");
	char * str;
	if (!(str = get_str())) return 1;

	tree_add(tree, key, int1, int2, str);

	free(str);
	free(key);
	return 0;
}

int dial_find(Tree *tree) {
	printf("---FIND---\n");

    printf("Enter key (string):\n");
	char * key;
	if (!(key = get_str())) return 1;

    printf("Enter version of element (int):\n");
	int version;
	if (get_int(&version)) return 1;

	Node * ptr = tree_find(tree, key, version);

	if (!ptr) {
        printf("Not found: key [ %s ] with version [ %d ] not found\n", key, version);
	} else {
        printf("Found: key [ %s ] version [ %d ]\nInfo1: [ %d ]\nInfo2: [ %d ]\nInfo3: [ %s ]\n", ptr->key, ptr->version, ptr->int1, ptr->int2, ptr->str);
	}

	free(key);

	return 0;
}

int dial_find_max(Tree *tree) {
	printf("---MAX KEY---\n");

    Node * ptr = tree_find_max(tree->root);

	if (!ptr) {
        printf("Tree is empty\n");
	} else {
	    printf("Max key: key [ %s ] VerCount [ %d ]\nInfo1: [ %d ]\nInfo2: [ %d ]\nInfo3: [ %s ]\n", ptr->key, ptr->len, ptr->int1, ptr->int2, ptr->str);
	}

	return 0;
}

int dial_delete(Tree *tree) {
	printf("---DELETE---\n");

    printf("Enter key (string):\n");
	char * key;
	if (!(key = get_str())) return 1;

	printf("Enter -1 to delete LAST version or other number if not\n");
	int version;
	if (get_int(&version)) return 1;

	tree_remove(tree, key, version);

	free(key);

	return 0;
}

int dial_show(Tree *tree) {
	printf("---SHOW---\n");

	printf("Enter a number:\n1) Print all\n2) Print from substr\n3) Print as a tree\n4) Graphviz (DOT)\n");
	int option;
	if (get_int(&option)) return 1;

	if (option == 1) {
		tree_print(tree->root);
	} else if (option == 2) {

        printf("Enter substring (string):\n");
        char * subs;
        if (!(subs = get_str())) return 1;

        tree_print_str(tree, subs);
        printf("\n");
        free(sub);

    } else if (option == 3) {
		tree_show(tree->root, 0);
	} else if (option == 4) {
	    printf("\ndigraph G {\n");
		tree_graphviz(tree->root);
		printf("}\n\n");
	} else {
		printf("ERROR: No such option");
	}

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

void start(Tree * tree) {
	const char * menu[] = {"0) Quit", "1) Add", "2) Find", "3) Find max", "4) Delete", "5) Show"};
	int menu_size = sizeof(menu)/sizeof(menu[0]);

	int (*dialog_functions[])(Tree*) = {NULL, dial_add, dial_find, dial_find_max, dial_delete, dial_show};

	int opt;
	while ((opt = dialog(menu, menu_size))) {
		if (opt == 0 || dialog_functions[opt](tree)) break;
	}

	printf("\nProgram finished.\n");
	tree_delete(tree->root);
    free(tree);
}
