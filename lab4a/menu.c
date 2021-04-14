#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "test.h"
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

char* get_str() {
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

	printf("Enter key (int):\n");
	int key;
	if(get_int(&key)) return 1;

	printf("Enter info1 (string):\n");
	char * str1;
	if(!(str1 = get_str())) return 1;

    printf("Enter info2 (string):\n");
	char * str2;
	if(!(str2 = get_str())) return 1;

	tree_add(tree, str1, str2, key);

	free(str1);
	free(str2);
	return 0;
}

int dial_find(Tree *tree) {
	printf("---FIND---\n");

    printf("Enter key (int):\n");
	int key;
	if(get_int(&key)) return 1;

    printf("Enter version of element (int):\n");
	int version;
	if(get_int(&version)) return 1;

	Node * ptr = tree_find(tree, key, version);

	if (!ptr){
        printf("Not found: key \"%d\" with version \"%d\" not found\n", key, version);
	} else {
        printf("Found: key \"%d\" version \"%d\"\nInfo1: \"%s\"\nInfo2: \"%s\"\n", ptr->key, ptr->version, ptr->str1, ptr->str2);
	}

	return 0;
}

int dial_find_close(Tree *tree) {
	printf("---CLOSEST KEY---\n");

    printf("Enter key (int):\n");
	int key;
	if(get_int(&key)) return 1;

	Node * ptr = tree_find_close(tree, key);

	if (!ptr){
        printf("Tree is empty or only input key's node is in\n");
	} else {
	    printf("Closest key: key \"%d\" version \"%d\"\nInfo1: \"%s\"\nInfo2: \"%s\"\n", ptr->key, ptr->version, ptr->str1, ptr->str2);
	}

	return 0;
}

int dial_delete(Tree *tree) {
	printf("---DELETE---\n");

    printf("Enter key (int):\n");
	int key;
	if(get_int(&key)) return 1;

    printf("Enter version of element (int):\n");
	int version;
	if(get_int(&version)) return 1;

	tree_remove(tree, key, version);

	return 0;
}

int dial_show(Tree *tree) {
	printf("---SHOW---\n");

	printf("Enter a number:\n1) order by key\n2) order by key in range\n3) print as a tree\n4) graphviz (DOT)\n");
	int option;
	if(get_int(&option)) return 1;

	if (option == 1) {
		tree_print(tree->root);
	} else if (option == 2) {
        int a,b;

        printf("Enter first key (int):\n");
        if(get_int(&a)) return 1;

        printf("Enter second key (int):\n");
        if(get_int(&b)) return 1;

		tree_print_range(tree, a, b);
    } else if (option == 3) {
		tree_show(tree->root, 0);
	} else if (option == 4) {
		tree_graphviz(tree);
	} else {
		printf("ERROR: No such option");
	}

	return 0;
}

int dial_test(Tree *tree) {
	printf("---TEST---\n");

	printf("Enter the number of elements\n");
	int num;
	if(get_int(&num)) return 1;

	if (test(num)) return 1;

	return 0;
}

int dialog(const char *menu[], const int menu_size) {
	char *error_msg = "";
	int opt;

	do{
		printf("%s\n", error_msg);
		error_msg = "Invalid input. Repeate.";

		for (int i = 0; i < menu_size; i++) {
			printf("%s\n", menu[i]);
		}
		printf("%s", "Make your choice: ");

		if(get_int(&opt)) {
			opt = 0;
		}
	} while (opt < 0 || opt >= menu_size);

	return opt;
}

void start(Tree *tree) {
	const char *menu[] = {"0) Quit", "1) Add", "2) Find", "3) Find closest", "4) Delete", "5) Show", "6) Test"};
	const int menu_size = sizeof(menu)/sizeof(menu[0]);

	int (*dialog_functions[])(Tree*) = {NULL, dial_add, dial_find, dial_find_close, dial_delete, dial_show, dial_test};

	int opt;
	while((opt = dialog(menu, menu_size))) {
		if (opt == 0 || dialog_functions[opt](tree)) break;
	}

	printf("\nProgram finished.\n");
}
