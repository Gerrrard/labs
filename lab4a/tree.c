#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

Tree * tree_new(){
	Tree * tree = (Tree *)calloc(1, sizeof(Tree));
	if (!tree) return NULL;

	tree->h = 0;
	tree->n = 0;
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

    node->left = left;
	node->right = right;
	node->parent = parent;
	node->key = key;
	node->version = version;

	strcpy(node->str1, info1);
	strcpy(node->str2, info2);

	return node;
}

int n_side(Node *ptr) {
	if (!ptr) return 0;
	if (!ptr->parent) return 0;
	if (ptr->parent->left == ptr) {
		return -1;
	} else {
		return 1;
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

    ver = &version;

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

	if (ptr->left) return tree_find_min(ptr->left);

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
            if(ptr->version == version || version == -1){
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

    Node * less = tree_find_prev(example);
    while(less != NULL || key != less->key){
        if(less != NULL) less = tree_find_prev(example->left);
    }
    Node * more = tree_find_next(example);
    while(more != NULL || key != more->key){
        if(more != NULL) more = tree_find_next(example->right);
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

	return NULL;
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

		buffer = ptr->str2;
		ptr->str2 = ptr_next->str2;
		ptr_next->str2 = buffer;

		free(ptr_next->str1);
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

		if (side < 0) {
			ptr->parent->left = child;
        } else if (side > 0) {
			ptr->parent->right = child;
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

    tree_show(ptr->right, level + 1);

    for(int i = 0; i < level; i++) {
        printf("\t\t");
    }
    char help;
    if (n_side(ptr) < 0) help = '\\';
    else if (n_side(ptr) > 0) help = '/';
    else help = ' ';
    printf("%c (\"%d\", \"%d\", \"%s\", \"%s\")\n", help, ptr->key, ptr->version, ptr->str1, ptr->str2);

    tree_show(ptr->left, level + 1);
}


void tree_print_range(Tree * tree, int a, int b);

void tree_graphviz(Tree *tree);

int tree_load(char *file);
