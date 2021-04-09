#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info.h"
#include "table.h"
#include "menu.h"

int get_int(int *num) {
	int err;
	do {
		err = scanf("%d", num);
		if (err < 0) return 1;//EOF
		if (err == 0) {
			printf("Invalid input. Repeate.\n");
			scanf("%*[^\n]");
		}
	} while (err == 0);
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
            if (!res) {
                return NULL;
            }
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
    }
    else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

int dial_add(Table* table) {
	printf("-ADD NEW-\n");

	printf("Enter keys.\n");

	int key1,par1;
	char *key2;

	printf("key1 (int): ");
	if(get_int(&key1)) return 1;


	printf("par1 (int): ");
	if(get_int(&par1)) return 1;


	printf("key2 (char *): ");
	if(!(key2 = get_str())) return 1;

	printf("Enter info.\n");

	char *inf;

	printf("String: ");
	if(!(inf = get_str())) {
		free(key2);
		return 1;
	}

	Info info;
	info.str = inf;

	table_insert(table, key1, par1, key2, info);

	free(key_2);
	free(str);
	return 0;
}

int dial_find(Table* table) {
	printf("-FIND WITH BOTH KEYS-\n");

	printf("Enter keys.\n");

	int key1;
	char *key2;

	printf("key1 (int): \n");
	if(get_int(&key1)) return 1;

	printf("key2 (char *): \n");
	if(!(key2 = get_str())) return 1;

	Info *info = table_find(table, key1, key2);
	info_print(info);
	printf("\n");

	return 0;
}

int dial_delete(Table* table) {
	printf("-DELETE WITH BOTH KEYS-\n");

	printf("Enter keys.\n");

	int key1;
	char *key2;

	printf("key1 (int): ");
	if(get_int(&key1)) return 1;

	printf("key2 (char *): ");
	if(!(key2 = get_str())) return 1;

	table_remove(table, key1, key2);

	free(key2);

	return 0;
}

int dial_show(Table* table) {
	int option;
	printf("-SHOW TABLE-\n");

	printf("Choose 1st or 2nd mode: ");
	if(get_int(&option)) return 1;

	if(option == 1){
        space1_print(table->space1);
    }else if(option == 2){
        space2_print(table->ks2);
	}

	return 0;
}

int dial_del_par_sp1(Table* table){
	printf("-DELETE WITH PARENT FIRST KEY-\n");

	printf("Enter parent key.\n");

	int par;

	printf("parent (int): ");
	if(get_int(&par)) return 1;

	table_remove_sp1(table, par, 1);

	return 0;
}

int dial_find_par_sp1(Table* table){
	printf("-FIND WITH PARENT FIRST KEY-\n");

	printf("Enter parent key\n");

	int par;

	printf("parent (int): \n");
	if(get_int(&par)) return 1;

	Space1 *info = space1_find_par(table->space1, par);
	space1_print(info);
	printf("\n");

	return 0;
}

int dial_find_sp2(Table* table){
	printf("-FIND WITH SECOND KEY-\n");

	printf("Enter 1 to find with release and other if without\n");

	int option;

	printf("option (int): \n");
	if(get_int(&option)) return 1;

	char *key2;
	int release;

	printf("Enter key\n");

	printf("key2 (char *): \n");
	if(!(key2 = get_str())) return 1;

	if(option == 1){
        printf("release (int): \n");
        if(get_int(&release)) return 1;
	}

	if(option != 1){
        Space2 * info = space2_find_all(table->space2, key2);
        space2_print(info);
        printf("\n");
	}

	if(option == 1){
        Info * info = space2_find(table->space2, key2, release);
        info_print(info);
        printf("\n");
	}

	return 0;
}

int dial_delete_sp2(Table* table){
    printf("-DELETE WITH SECOND KEY-\n");

	printf("Enter -1 to find without release or specify the version\n");

	int release;

	printf("release (int): \n");
	if(get_int(&release)) return 1;

	char *key2;

	printf("Enter key\n");

	printf("key2 (char *): \n");
	if(!(key2 = get_str())) return 1;

	table_remove_sp2(table, key2, release);

	return 0;
}

int dialog(const char *menu[], int menu_size){
	char *err_msg = "";
	int option;

	do{
		printf("%s\n", err_msg);
		err_msg = "Invalid input. Repeate.";

		for (int i = 0; i < menu_size; i++) {
			printf("%s\n", menu[i]);
		}
		printf("%s", "Make a choice: ");

		if(get_int(&option)) option = 0;

	}while (option < 0 || option >= menu_size);

	return option;
}

void start(Table *table){
	const char *menu[] = {"0) Quit", "1) Add", "2) Find by two keys",
                          "3) Find by parent key (SP1)", "4) Find by second key (SP2)",
                          "5) Delete by two keys", "6) Delete by parent (SP1)",
                          "7) Delete by second key (SP2)", "8) Show"};
	const int menu_size = sizeof(menu)/sizeof(menu[0]);

	int (*dialog_functions[])(Table*) = {NULL, dial_add, dial_find, dial_find_par_sp1, dial_find_sp2, dial_delete, dial_del_par_sp1, dial_delete_sp2, dial_show};

	int opt;
	while(opt = dialog(menu, menu_size)) {
		if (opt == 0 || dialog_functions[opt](table)) break;
	}

	printf("\nProgram finished.\n");
}
