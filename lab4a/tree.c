#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

Tree * tree_new(){
	Tree * tree = (Tree *)calloc(1, sizeof(Tree));
	if (!tree) return NULL;

	tree->n = 0;
	tree->h = 0;
	tree->root = NULL;

	return tree;
}

void tree_delete(Node *ptr) {
	if (!ptr) return;

	tree_delete(ptr->left);
	tree_delete(ptr->right);
	free(ptr->str1);
	free(ptr->str2);
	free(ptr);
}

Node * node_new(int key, int version, char * info1, char * info2, Node * left, Node * right, Node * parent){
	if (!info1) return NULL;
	if (!info2) return NULL;

	Node * node = (Node *)calloc(1, sizeof(Node));
	if (!node) return NULL;

	node->str1 = (char *)calloc((int)strlen(info1) + 1, sizeof(char));
	if (!node->str1) {
		free(node);
		return NULL;
	}

    node->str2 = (char *)calloc((int)strlen(info2) + 1, sizeof(char));
	if (!node->str2) {
        free(node->str1);
		free(node);
		return NULL;
	}

    node->key = key;
	node->version = version;
    node->left = left;
	node->right = right;
	node->parent = parent;

	strcpy(node->str1, info1);
	strcpy(node->str2, info2);

	return node;
}

int n_side(Node *ptr) {
	if (!ptr) return 0;
	if (!ptr->parent) return 0;

	if (ptr->parent->right == ptr) {
		return 1;
	} else {
		return -1;
	}
}

Node * tree_find_parent(Tree * tree, int key, int * ver) {
	Node * parent = NULL;
	Node * ptr = tree->root;
	int version = 0;

	while (ptr) {
		parent = ptr;

		if (key == ptr->key){
            version += 1;
		}

		if (key < ptr->key){
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}

    *ver = version;

	return parent;
}

Node * tree_find_min(Node * ptr){
    if (!ptr) return NULL;

	while (ptr->left) {
		ptr = ptr->left;
	}

	return ptr;
}

Node * tree_find_max(Node * ptr) {
	if (!ptr) return NULL;

	while (ptr->right) {
		ptr = ptr->right;
	}

	return ptr;
}

Node * tree_find_prev(Node * ptr){
    if (!ptr) return NULL;

	if (ptr->left) return tree_find_max(ptr->left);

	while (ptr->parent && n_side(ptr) < 0) {
		ptr = ptr->parent;
	}

	return ptr->parent;
}

Node* tree_find_next(Node *ptr) {
	if (!ptr) return NULL;

	if (ptr->right) return tree_find_min(ptr->right);

	while (ptr->parent && n_side(ptr) > 0) {
		ptr = ptr->parent;
	}

	return ptr->parent;
}

Node * tree_find(Tree * tree, int key, int version){
    if (!tree) return NULL;

	Node * ptr = tree->root;
	while (ptr) {
		if (key == ptr->key){
            if (ptr->version == version || version == -1) {
                return ptr;
            }
            ptr = ptr->right;
		} else if (key > ptr->key){
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

	return NULL;
}

Node * tree_find_close(Tree * tree, int key){
    if (!tree) return NULL;

    Node * example = tree_find(tree, key, -1);
    Node * more = NULL;
    Node * less = NULL;

    if (!example) {
        int i = 1;
        while(!example && !more && !less){
            key += i;
            more = tree_find(tree, key, -1);
            key -= i*2;
            less = tree_find(tree, key, -1);
            key += i;
            i++;
        }
    } else {
        less = tree_find_prev(example);
        more = tree_find_next(example);
    }

	if (!less && !more) {
		return NULL;
	} else if (!more){
        return less;
	} else if (!less){
        return more;
	} else {
        if(key - less->key >= more->key - key){
            return more;
        } else{
            return less;
        }
	}
}

int tree_add(Tree * tree, char * str1, char * str2, int key){
    if (!tree) return 1;

	if (!tree->root) {
		Node * root= node_new(key, 0, str1, str2, NULL, NULL, NULL);

		if (!root) return 1;

		tree->root = root;
	} else {
	    int version = 0;
		Node * par = tree_find_parent(tree, key, &version);
		Node * node = node_new(key, version, str1, str2, NULL, NULL, par);

		if (!node) return 1;

		if (key < par->key){
			par->left = node;
		} else {
			par->right = node;
		}
	}

	return 0;
}

int tree_remove(Tree * tree, int key, int version){
	if (!tree) return 1;

	Node * ptr = tree_find(tree, key, version);
	if (!ptr) return 2;

	if (ptr->left && ptr->right) {
		Node * ptr_next = tree_find_min(ptr->right);

		Node * child = ptr_next->right;

		int side = n_side(ptr_next);

		if (side < 0) {
			ptr_next->parent->left = child;
		} else {
			ptr_next->parent->right = child;
		}

		if (child) child->parent = ptr_next->parent;

		ptr->key = ptr_next->key;
		ptr->version = ptr_next->version;

		char * buffer;

		buffer = ptr->str1;
		ptr->str1 = ptr_next->str1;
		ptr_next->str1 = buffer;
		free(ptr_next->str1);

		buffer = ptr->str2;
		ptr->str2 = ptr_next->str2;
		ptr_next->str2 = buffer;
		free(ptr_next->str2);

		free(ptr_next);

	} else {
		Node * child;

		if (ptr->left) {
			child = ptr->left;
		} else if (ptr->right){
			child = ptr->right;
		} else {
			child = NULL;
		}

		if (child) child->parent = ptr->parent;

		int side = n_side(ptr);

		if (side > 0) {
			ptr->parent->right = child;
        } else if (side < 0) {
			ptr->parent->left = child;
		} else {
			tree->root = child;
		}

		free(ptr->str1);
		free(ptr->str2);
		free(ptr);
	}

	return 0;
}

void tree_print(Node * ptr){
    if (!ptr) return;

	tree_print(ptr->right);
	printf("Key: \"%d\", Version: \"%d\", Info1: \"%s\", Info2: \"%s\"\n", ptr->key, ptr->version, ptr->str1, ptr->str2);
	tree_print(ptr->left);
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
    printf("%c (\"%d\", \"%d\", \"%s\", \"%s\")\n", help, ptr->key, ptr->version, ptr->str1, ptr->str2);

    tree_show(ptr->right, level + 1);
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
	    printf("\"%d : %s, %s\" -> \"%d : %s, %s\" [label = %c]\n", node->parent->key, node->parent->str1, node->parent->str2, node->key, node->str1, node->str2, );
    }
    tree_graphviz(node->right);
}

void tree_print_range(Tree * tree, Node * node, int a, int b){
    if(a >= b){
        if (!node) return;

        node = tree_find(tree, a, -1);
        if (!node) {
        int key = a;
        while (!node && key >= b){
            key -= 1;
            node = tree_find(tree, key, -1);
            }
        }

        while(node && node->key >= b){
            printf("Key: \"%d\", Version: \"%d\", Info1: \"%s\", Info2: \"%s\"\n", node->key, node->version, node->str1, node->str2);
            node = tree_find_prev(node);
        }
    } else {
        if (!node) return;

        node = tree_find(tree, a, -1);
        if (!node) {
        int key = a;
        while (!node && key <= b){
            key += 1;
            node = tree_find(tree, key, -1);
            }
        }

        while(node && node->key >= a){
            printf("Key: \"%d\", Version: \"%d\", Info1: \"%s\", Info2: \"%s\"\n", node->key, node->version, node->str1, node->str2);
            node = tree_find_next(node);
        }
    }
}

int tree_load(Tree * tree, char *filep){
    int number;
    long size;
    char *buffer;

    FILE* file = fopen(filep, "r");

    if (!file ) {
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
    char * str1;
    char * str2;

    if((token = strtok(buffer, ":\n")) != NULL){
        number = atoi(token);
        token = strtok (NULL, ":\n");
        str1 = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(str1, token);
        token = strtok (NULL, ":\n");
        str2 = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(str2, token);
        tree_add(tree, str1, str2, number);
        free(str1);
        free(str2);
    }


    while ((token = strtok(NULL, ":\n")) != NULL) {
        number = atoi(token);
        token = strtok (NULL, ":\n");
        str1 = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(str1, token);
        token = strtok (NULL, ":\n");
        str2 = (char *)calloc((int)strlen(token) + 1, sizeof(char));
        strcpy(str2, token);
        tree_add(tree, str1, str2, number);
        free(str1);
        free(str2);
    }

    fclose(file);
    free(buffer);
    return 0;
}
