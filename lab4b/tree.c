#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "tree.h"

Tree * tree_new(){
	Tree * tree = (Tree *)calloc(1, sizeof(Tree));
	if (!tree) return NULL;

	tree->root = NULL;

	return tree;
}

Node * node_new(char * key, int version, int len, int int1, int int2, char * str, Node * left, Node * right, Node * parent){
	if (!key) return NULL;
	if (!str) return NULL;

	Node * node = (Node *)calloc(1, sizeof(Node));
	if (!node) return NULL;

	node->str = (char *)calloc((int)strlen(str) + 1, sizeof(char));
	if (!node->str) {
		free(node);
		return NULL;
	}

    node->key = (char *)calloc((int)strlen(key) + 1, sizeof(char));
	if (!node->key) {
        free(node->key);
		free(node);
		return NULL;
	}

	node->len = len;
	node->next = NULL;
    node->version = version;
	node->int1 = int1;
	node->int2 = int2;
    node->left = left;
	node->right = right;
	node->parent = parent;

	strcpy(node->key, key);
	strcpy(node->str, str);

	return node;
}

int n_side(Node * ptr){
	if (!ptr) return 0;
	if (!ptr->parent) return 0;

	if (ptr->parent->right == ptr) {
		return 1;
	} else {
		return -1;
	}
}

int n_size(Node * ptr){
	if (!ptr) return 0;

    return n_size(ptr->left) + n_size(ptr->right) + 1;
}

void tree_delete(Node * ptr){
	if (!ptr) return;

	tree_delete(ptr->left);
	tree_delete(ptr->right);
	free(ptr->key);
	free(ptr->str);

	Node * pptr = ptr->next;
	Node * temp;

	while(pptr){
        temp = pptr;
        free(temp->key);
        free(temp->str);
        pptr = temp->next;
        free(temp);
	}

	free(ptr);
}

Node * tree_find_min(Node * ptr){
    if (!ptr) return NULL;

	while (ptr->left) {
		ptr = ptr->left;
	}

	return ptr;
}

Node * tree_find_max(Node * ptr){
	if (!ptr) return NULL;

	while (ptr->right) {
		ptr = ptr->right;
	}

	return ptr;
}

void tree_print(Node * ptr){
    if (!ptr) return;

	tree_print(ptr->right);
	printf("Key: [ %s ], Version: [ %d ], VerCount: [ %d ], Int1: [ %d ], Int2: [ %d ], Str: [ %s ]\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
	if (ptr->next) next_print(ptr);
	tree_print(ptr->left);
}

void next_print(Node * ptr){
    if (!ptr) return;

    printf("Key: \"%s\", Version: \"%d\", VerCount: \"%d\", Int1: \"%d\", Int2: \"%d\", Str: \"%s\"\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
    next_print(ptr->next);
}

void next_delete(Node * ptr){
    if (!ptr) return;

    next_delete(ptr->next);

    free(ptr->key);
    free(ptr->str);
    free(ptr);
}

Node * tree_find_prev(Node * ptr){
    if (!ptr) return NULL;

	if (ptr->left) return tree_find_max(ptr->left);

	while (ptr->parent && n_side(ptr) < 0) {
		ptr = ptr->parent;
	}

	return ptr->parent;
}

Node * tree_find_next(Node * ptr){
	if (!ptr) return NULL;

	if (ptr->right) return tree_find_min(ptr->right);

	while (ptr->parent && n_side(ptr) > 0) {
		ptr = ptr->parent;
	}

	return ptr->parent;
}

Node * tree_find(Tree * tree, char * key, int version){
    if (!tree) return NULL;

	Node * ptr = tree->root;

	while (ptr) {
		if (strcmp(key, ptr->key) == 0) {
            if (version == -1) {
                while (ptr->next) {
                    ptr = ptr->next;
                }
                return ptr;
            } else if (version == 0) {
                    return ptr;
            } else {
                while (ptr->next) {
                    if (ptr->version == version) return ptr;
                    ptr = ptr->next;
                }
                if (ptr->version == version) return ptr;
                printf("ERROR: no such version");
                return NULL;
            }
		} else if (strcmp(key, ptr->key) > 0) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

	return NULL;
}

void tree_show(Node * ptr, int level){
    if (!ptr) return;

    tree_show(ptr->left, level + 1);

    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    char help;
    if (n_side(ptr) < 0) help = '\\';
    else if (n_side(ptr) > 0) help = '/';
    else help = ' ';
    printf("%c ([%s], [%d], [%d], [%d], [%d], [%s])\n", help, ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);

    tree_show(ptr->right, level + 1);
}

void tree_graphviz(Node * node){
    if (!node) return;

    tree_graphviz(node->left);
    if (node->parent) {
        char S;
        if (n_side(node) > 0) {
            S = 'R';
        } else {
            S = 'L';
        }
	    printf("\"%s : %d, %d, %s\" -> \"%s : %d, %d, %s\" [label = %c]\n", node->parent->key, node->parent->int1, node->parent->int2, node->parent->str, node->key, node->int1, node->int2, node->str, S);
    }
    tree_graphviz(node->right);
}

void tree_print_str(Tree * tree, char * substr){
    if (!tree) return;

	Node * ptr = tree->root;
	Node * temp;
    char * p;
	while (ptr) {
	    p = strstr(ptr->key, substr);
        if (p != NULL && ptr->key == p){
            temp = tree_find_prev(ptr);

            if (temp) {
                p = strstr(temp->key, substr);
                while (p != NULL && temp->key == p) {
                    ptr = temp;

                    temp = tree_find_prev(ptr);
                    if (temp == NULL) break;
                    p = strstr(temp->key, substr);
                }
            }
            printf("Key: \"%s\", Version: \"%d\", VerCount: \"%d\", Int1: \"%d\", Int2: \"%d\", Str: \"%s\"\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);

            ptr = tree_find_next(ptr);
            break;
        }
		if (strcmp(substr, ptr->key) > 0) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

    while (ptr) {
        p = strstr(ptr->key, substr);
        if (p == NULL || ptr->key != p) {
            break;
        }
        printf("Key: \"%s\", Version: \"%d\", VerCount: \"%d\", Int1: \"%d\", Int2: \"%d\", Str: \"%s\"\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
        ptr = tree_find_next(ptr);
    }

	return;
}

int tree_load(Tree * tree, char *filep){
    int number1, number2;
    long size;
    char * buffer;

    FILE* file = fopen(filep, "r");

    if (!file) {
        printf("ERROR: Could not open file\n");
        return 1;
    }

    fseek(file, 0L , SEEK_END);
    size = ftell(file);
    rewind(file);
    buffer = calloc(1, size + 1);
    if (!buffer) {
        fclose(file);
        printf("ERROR: Error in buffer alloc\n");
        return 2;
    }

    if (fread( buffer , size, 1 , file) != 1) {
        fclose(file);
        free(buffer);
        printf("ERROR: Error in reading\n");
    }

    char * token;
    char * key;
    char * str;

    if((token = strtok(buffer, ":\n")) != NULL){
        key = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(key, token);
        token = strtok (NULL, ":\n");
        number1 = atoi(token);
        token = strtok (NULL, ":\n");
        number2 = atoi(token);
        token = strtok (NULL, ":\n");
        str = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(str, token);
        tree_add(tree, key, number1, number2, str);
        free(str);
        free(key);
    }


    while (token || (token = strtok(NULL, ":\n")) != NULL) {
        key = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(key, token);
        token = strtok (NULL, ":\n");
        number1 = atoi(token);
        token = strtok (NULL, ":\n");
        number2 = atoi(token);
        token = strtok (NULL, ":\n");
        str = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(str, token);
        tree_add(tree, key, number1, number2, str);
        free(str);
        free(key);
    }

    fclose(file);
    free(buffer);
    return 0;
}

int node_add(Tree * tree, char * key, int int1, int int2, char * str){
	if (!tree) return -1;

	if (!tree->root) {
		tree->root = node_new(key, 0, 1, int1, int2, str, NULL, NULL, NULL);
		return 0;
	}

	int depth = 1;

	Node * ptr = tree->root;

	while (ptr){
		if (strcmp(key, ptr->key) > 0) {
			if (ptr->right){
				ptr = ptr->right;
				depth++;
			} else {
				ptr->right = node_new(key, 0, 1, int1, int2, str, NULL, NULL, ptr);

				return depth;
			}
		} else if (strcmp(key, ptr->key) < 0) {
			if (ptr->left) {
				ptr = ptr->left;
				depth++;
			} else {
				ptr->left = node_new(key, 0, 1, int1, int2, str, NULL, NULL, ptr);

				return depth;
			}
		} else {
		    if (!ptr->next) ptr->len += 1;

            while (ptr->next) {
                ptr->len += 1;
                ptr = ptr->next;
            }

            Node * p = node_new(key, ptr->version + 1, ptr->len + 1, int1, int2, str, ptr->left, ptr->right, ptr->parent);
            ptr->next = p;

            return 0;
		}
	}
}

Node * find_unbal(Node * ptr) {
	Node * Nd = NULL;

	while (ptr->parent) {
	    if (fabs(n_size(ptr->parent->left) - n_size(ptr->parent->right)) > 1) Nd = ptr->parent;

        ptr = ptr->parent;
	}

	return Nd;
}

Node * list_to_node1(Node * ptr, int ind){
	for (int i = 0; i < ind; i++ ) ptr = ptr->right;

	return ptr;
}

Node * tree_to_list1(Node * ptr){
	Node * list_st;
	Node * list_md;
	Node * list_end;

	if (!(ptr->left)) {
        list_st = NULL;
	} else {
        list_st = tree_to_list1(ptr->left);
	}

	if (!(ptr->right)) {
        list_end = NULL;
	} else {
        list_end = tree_to_list1(ptr->right);
	}

    list_md = ptr;

    list_md->right = list_end;
    if (!list_st) return list_md;

    Node * last = list_st;

    while (last->right) {
    	last = last->right;
    }

    last->right = list_md;
    return list_st;
}

Node * tree_rebuild1(Node * ptr, Node * par, int size){
	if (size <= 0) return NULL;

	Node * sub = list_to_node1(ptr, size / 2);

	sub->left = tree_rebuild1(ptr, sub, size / 2);
	sub->right = tree_rebuild1(sub->right, sub, size - size / 2 - 1);

	sub->parent = par;
}

void tree_rebuild2(Tree * tree, Node * unbal, Node * unbal_par){
    int size = n_size(unbal);

    Node ** arr = (Node **)calloc(size, sizeof(Node *));

    tree_to_arr(unbal, arr, 0);

    if (!unbal_par){
        tree->root = arr_to_tree(arr, 0, size);
        tree->root->parent = NULL;
    } else if (n_side(unbal) == 1) {
        unbal_par->right = arr_to_tree(arr, 0, size);
        unbal_par->right->parent = unbal_par;
    } else {
        unbal_par->left = arr_to_tree(arr, 0, size);
        unbal_par->left->parent = unbal_par;
    }

    free(arr);
}

int tree_to_arr(Node * ptr, Node ** arr, int ind){
    if (!ptr) return ind;

    ind = tree_to_arr(ptr->left, arr, ind);
    arr[ind] = ptr;
    ind++;

    return tree_to_arr(ptr->right, arr, ind);
}

Node * arr_to_tree(Node ** arr, int ind, int size){
    if (!size) return NULL;

    int mid = size / 2;

    arr[ind + mid]->left = arr_to_tree(arr, ind, mid);

    if (arr[ind + mid]->left) arr[ind + mid]->left->parent = arr[ind + mid];

    arr[ind + mid]->right = arr_to_tree(arr, ind + mid + 1, size - mid - 1);

    if (arr[ind + mid]->right) arr[ind + mid]->right->parent = arr[ind + mid];

    return arr[ind + mid];
}

int tree_add(Tree * tree, char * key, int int1, int int2, char * str){
	int height = node_add(tree, key, int1, int2, str);
	if (!height) return 0;

	Node * start = tree_find(tree, key, 0);
    Node * unbal = find_unbal(start);

    if (unbal) {
        Node * unbal_par = unbal->parent;
        tree_rebuild2(tree, unbal, unbal_par);
        /*
        list impl

        int unbal_size = n_size(unbal);
        Node * list = tree_to_list1(unbal);

        if (unbal_par) {
            if (n_side(unbal) == -1) {
                unbal_par->left = tree_rebuild1(list, unbal_par, unbal_size);
            } else {
                unbal_par->right = tree_rebuild1(list, unbal_par, unbal_size);
            }
        } else {
            tree->root = tree_rebuild1(list, NULL, unbal_size);

        }*/
    }
	return 0;
}

int node_delete(Tree * tree, Node * ptr){
	if (!tree) return 1;
	if (!ptr) return 2;

	Node * child;

    if (ptr->left && ptr->right) {
		Node * ptr_next = tree_find_min(ptr->right);

		child = ptr_next->right;

		if (n_side(ptr_next) < 0) {
			ptr_next->parent->left = child;
		} else {
			ptr_next->parent->right = child;
		}

		if (child) child->parent = ptr_next->parent;

		if (ptr->next) next_delete(ptr->next);

		ptr->next = ptr_next->next;
        ptr->int1 = ptr_next->int1;
        ptr->int2 = ptr_next->int2;
        ptr->len = ptr_next->len;
        ptr->version = ptr_next->version;

		char * buffer;

		buffer = ptr->str;
		ptr->str = ptr_next->str;
		ptr_next->str = buffer;
		free(ptr_next->str);

		buffer = ptr->key;
		ptr->key = ptr_next->key;
		ptr_next->key = buffer;
		free(ptr_next->key);

		free(ptr_next);
	} else {
		if (ptr->left) {
			child = ptr->left;
		} else if (ptr->right){
			child = ptr->right;
		} else {
			child = NULL;
		}

		if (child) child->parent = ptr->parent;

        if (ptr->next) next_delete(ptr->next);

		int side = n_side(ptr);

		if (side > 0) {
			ptr->parent->right = child;
        } else if (side < 0) {
			ptr->parent->left = child;
		} else {
			tree->root = child;
		}

		free(ptr->str);
		free(ptr->key);
		free(ptr);
	}

	return 0;
}

void tree_remove(Tree * tree, char * key, int version){
	Node * ptr = tree_find(tree, key, 0);
	if (!ptr) return;

	if (version == -1 && ptr->next) {
        Node * prev = ptr;
        Node * pptr = ptr;
        ptr = ptr->next;
        while(ptr->next){
            prev = ptr;
            ptr = ptr->next;
        }
        prev->next = NULL;

        if (n_side(pptr) == 1) {
            pptr->len -= 1;
        } else {
            pptr->len -= 1;
        }

        free(ptr->key);
        free(ptr->str);
        free(ptr);
        return;
	}

    Node * start = ptr->parent;

    int is_r = (ptr == tree->root) ? 1 : 0;

    node_delete(tree, ptr);

    Node * unbal;
    if(!is_r) unbal = find_unbal(start);
    else unbal = tree->root;

    if (unbal) {
        Node * unbal_par = unbal->parent;
        tree_rebuild2(tree, unbal, unbal_par);
        /*
        list impl

        int unbal_size = n_size(unbal);
        Node * list = tree_to_list1(unbal);

        if (unbal_par) {
            if (n_side(unbal) == -1) {
                unbal_par->left = tree_rebuild1(list, unbal_par, unbal_size);
            } else {
                unbal_par->right = tree_rebuild1(list, unbal_par, unbal_size);
            }
        } else {
            tree->root = tree_rebuild1(list, NULL, unbal_size);
        }*/
    }
}

char * rand_str(int len) {
    char * str = (char *)calloc(len + 1, sizeof(char));
    if (!str) return NULL;

    char * cur = str;
    int n = 26;
    int d = 'a';
    for (int i = 0; i < len; i++) {
        int r = rand()%n;
        *cur = d + r;
        cur++;
    }
    *cur = '\0';

    return str;
}

int rand_int(int max) {
    return rand()%max;
}

int tree_test(int count) {
    Tree * tree = tree_new();

    srand(time(NULL));

    char * keys = (char *)calloc(count, sizeof(char *));
    if (!keys) return 1;

    double t_add = 0;
    int len = 16;
    int num = 0;

    while (num < count) {
        if (num % 10000 == 0){
            printf("Number:\t%d\nLength:\t%d\n", num, len);
            printf("Addition: average time\t%.10f\n", (t_add == 0) ? 0 : t_add/num);
        }
        char * key = rand_str(len);
        int int1 = rand_int(100);
        int int2 = rand_int(200);
        char * str = rand_str(len);

        if (!key || !str) {
            free(str);
            free(keys);

            tree_delete(tree->root);

            printf("ERROR: Memory is over\n");
            return 1;
        }

        keys[num] = key;
        num++;

        clock_t t = clock();
        tree_add(tree, key, int1, int2, str);

        t_add += (double)(clock() - t)/CLOCKS_PER_SEC;

        free(key);
        free(str);
    }

    printf("Number:\t%d\nLength:\t%d\n", num, len);
    printf("Addition: average time\t%.10f\n", (t_add == 0) ? 0 : t_add/num);

    free(keys);

    tree_delete(tree->root);
    free(tree);

    return 0;
}
