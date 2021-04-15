#ifndef	TREE_H
#define TREE_H

typedef struct Node{
    int key;
    int version;
    struct Node * left;
    struct Node * right;
    struct Node * parent;
    char * str1;
    char * str2;
} Node;

typedef struct Tree{
    Node * root;
    int h;
    int n;
} Tree;

Node * node_new(int key, int version, char * info1, char * info2, Node * left, Node * right, Node *parent);
Node * tree_find_parent(Tree *tree, int key, int * ver);

Tree * tree_new();
void tree_delete(Node * root);

int tree_add(Tree * tree, char * str1, char * str2, int key);
int tree_remove(Tree * tree, int key, int version);
void tree_print_range(Tree * tree, Node * node, int a, int b);
void tree_print(Node * ptr);
void tree_show(Node * ptr, int level);

void tree_graphviz(Tree *tree);

int tree_load(char *file);

Node * tree_find(Tree * tree, int key, int version);
Node * tree_find_close(Tree * tree, int key);

Node * tree_find_next(Node * ptr);
Node * tree_find_prev(Node * ptr);
Node * tree_find_min(Node * ptr);
Node * tree_find_max(Node * ptr);

#endif
