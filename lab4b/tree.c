#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
	if (!node->str1) {
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
	node->balance = balance;
	node->int1 = int1;
	node->int2 = int2;
    node->left = left;
	node->right = right;
	node->parent = parent;

	strcpy(node->key, key);
	strcpy(node->str, str);

	return node;
}

void tree_delete(Node * ptr){
	if (!ptr) return;

	tree_delete(ptr->left);
	tree_delete(ptr->right);
	free(ptr->key);
	free(ptr->str);

	next_delete(ptr);

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

int node_size(Node * ptr){
	if(!ptr) return 0;

    return node_size(ptr->left) + node_size(ptr->right) + 1;
}

void tree_print(Node * ptr){
    if (!ptr) return;

	tree_print(ptr->right);
	printf("Key: [ %s ], Version: [ %d ], VerCount: [ %d ], Int1: [ %d ], Int2: [ %d ], Str: [ %s ]\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
	next_print(ptr);
	tree_print(ptr->left);
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

void tree_show(Node * ptr, int level){
    if (!ptr) return;

    tree_show(ptr->left, level + 1);

    for(int i = 0; i < level; i++) {
        printf("\t");
    }
    char help;
    if (n_side(ptr) < 0) help = '\\';
    else if (n_side(ptr) > 0) help = '/';
    else help = ' ';
    printf("%c ([%s], [%d], [%d], [%d], [%d], [%s])\n", help, ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);

    tree_show(ptr->right, level + 1);
}

void next_print(Node * ptr){
    if(!ptr) return;

    printf("Key: \"%s\", Version: \"%d\", VerCount: \"%d\", Int1: \"%d\", Int2: \"%d\", Str: \"%s\"\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
    next_print(ptr->next);
}

void next_delete(Node * ptr){
    if(!ptr) return;

    if(n_side(ptr) == 1){
        ptr->parent->right->len -= 1;
    } else {
        ptr->parent->left->len -= 1;
    }

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

	while (ptr){
		if (strcmp(key, ptr->key) == 0){
            if (version  != -1){
                while (ptr->next){
                    ptr = ptr->next;
                }
                return ptr;
            } else {
                while (ptr->next){
                    if (version == ptr->version) return ptr;
                    ptr = ptr->next;
                }
            }
		} else if (strcmp(key, ptr->key) > 0){
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

	return NULL;
}

Node * find_unbal(Node * ptr) {
	int size = 1, height = 1, par_size;

	while(ptr->parent){
        if(n_side(ptr) == -1) {par_size = 1 + size + node_size(ptr->parent->right);}
        else { par_size = 1 + size + node_size(ptr->parent->left); }

		if(height > (logf(2)/logf(par_size))){
			return ptr->parent;
		}

		height++;
		size = par_size;
		ptr = ptr->parent;
	}
}

Node * tree_rebuild(Node * ptr, Node * par, int size){
	if(size <= 0) return NULL;

	Node * sub = list_to_node(ptr, size / 2);

	sub->left = rebuild_tree(ptr, sub, size / 2);
	sub->right = rebuild_tree(sub->right, sub, size - size / 2 - 1);

	sub->par = par;
}

Node * tree_to_list(Node * ptr){
	Node * list_st, list_md, list_ptr;

	if(!(ptr->left)){
        list_st = NULL;
	} else {
        list_st = tree_to_list(ptr->left);
	}

	if(!(ptr->right)){
        list_ptr = NULL;
	} else {
        list_ptr = tree_to_list(ptr->right);
	}

    Node * list_md = ptr;

    list_md->right = list_ptr;
    if (!list_st) return list_md;

    Node * last = list_st;

    while(last->right) {
    	last = last->right;
    }

    last->right = list_md;
    return list_st;
}

Node * list_to_node(Node * ptr, int ind){
	for(int i = 0; i < ind; i++ )ptr = ptr->right;

	return ptr;
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
    buffer = calloc(1, size+1);
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

void tree_graphviz(Node * node){
    if (!node) return;

    tree_graphviz(node->left);
    if (node->parent) {
        char S;
        if(n_side(node) > 0){
            S = 'R';
        } else {
            S = 'L';
        }
	    printf("\"%s : %d, %d, &s\" -> \"%s : %d, %d, &s\" [label = %c]\n", node->parent->key, node->parent->int1, node->parent->int2, node->parent->str, node->key, node->int1, node->int2, node->str);
    }
    tree_graphviz(node->right);
}

void tree_print_str(Tree * tree, char * substr){
    if (!tree) return NULL;

	Node * ptr = tree->root;

	while (ptr){
	    char * p = strstr(ptr->key, substr);
        if (p != NULL && ptr->key == p){
            printf("Key: \"%s\", Version: \"%d\", VerCount: \"%d\", Int1: \"%d\", Int2: \"%d\", Str: \"%s\"\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
            ptr = tree_find_next(ptr);
            break;
        }
		if (strcmp(key, ptr->key) > 0){
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

    while(ptr){
        p = strstr(ptr->key, substr);
        if (p == NULL || ptr->key != p){
            break;
        }
        printf("Key: \"%s\", Version: \"%d\", VerCount: \"%d\", Int1: \"%d\", Int2: \"%d\", Str: \"%s\"\n", ptr->key, ptr->version, ptr->len, ptr->int1, ptr->int2, ptr->str);
        ptr = tree_find_next(ptr);
    }

	return NULL;
}

int node_add(Tree * tree, char * key, int int1, int int2, char * str){
	if(!tree) return;

	if(!tree->root){
		tree->root = node_new(key, 0, 1, int1, int2, str, NULL, NULL, NULL);
		return 0;
	}

	int depth = 1;

	Node * ptr = tree->root;

	while(ptr){
		if (strcmp(key, ptr->key) > 0){
			if (ptr->right){
				ptr = ptr->right;
				depth++;
			} else {
				ptr->right = node_new(key, 0, ptr->right->len + 1, int1, int2, str, NULL, NULL, ptr->right);

				return depth;
			}
		} else if (strcmp(key, ptr->key) < 0){
			if (ptr->left){
				ptr = ptr->left;
				depth++;
			} else {
				ptr->left = node_new(key, 0, ptr->left->len + 1, int1, int2, str, NULL, NULL, ptr->left);

				return depth;
			}
		} else {
		    if(!ptr_next) ptr->len += 1;

            while(ptr->next){
                ptr->len += 1;
                ptr = ptr->next;
            }

            Node * p = node_new(key, ptr->version + 1, ptr->len + 1, int1, int2, str, ptr->left, ptr->right, ptr->parent);
            ptr->next = p;

            return 0;
		}
	}
}

int tree_add(Tree * tree, char * key, int int1, int int2, char * str){
	int height = node_add(tree->root, key, info);
	if(!height){
		return 0;
	}

	if(height > (logf(2)/logf(node_size(tree->root)))){
		Node * unbal = find_unbal(tree_find(tree, key, 0));
		int unbal_size = node_size(unbal);
		Node * list = tree_to_list(unbal);

		Node * unbal_par = unbal->par;
		if(unbal_par){
			if(unbal == unbal_par->left){
				unbal_par->left = tree_rebuild(list, unbal_par, goat_size);
			} else {
				unbal_par->right = tree_rebuild(list, unbal_par, goat_size);
			}
		} else {
			tree_root = tree_rebuild(list, NULL, unbal_size);
		}
	}

	return 0;
}

int tree_remove(Tree * tree, char * key, int version){}
